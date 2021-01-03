#include <string.h>
#include <stdarg.h>
 #include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <wchar.h>
#include <wctype.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <new>
#define	VOLATILE	volatile
#define _str_t RefCntStr
typedef	int32_t			LONG;
typedef	int32_t		INT32;
#define STR_NULL RefCntStr()
__inline	INT32	InterlockedIncrement(VOLATILE INT32* pAddend) {
	INT32	Value;
#if	defined(__INTEL_COMPILER)
	_asm {
		mov	ecx,	pAddend;
		mov	eax,	1;
		lock	xadd	[ecx],	eax;
		inc	eax;
		mov	Value,	eax;
	}
#else
	__asm__ __volatile__(
		"movl	$1,	%0	\n"
	"	lock			\n"
	"	xaddl	%0,	%1	\n"
	"	incl	%0		\n"
	:	"=r"(Value), "+m"(*pAddend)
	:
	:	"cc");
#endif
	return Value;
}
__inline	INT32	InterlockedDecrement(VOLATILE INT32* pAddend) {
#if defined(__i386)
	INT32	Value;
#if	defined(__INTEL_COMPILER)
	_asm {
		mov	ecx,	pAddend;
		mov	eax,	-1;
		lock	xadd	[ecx],	eax;
		dec	eax;
		mov	Value,	eax;
	}
#else
	__asm__ __volatile__(
		"movl	$-1,	%0	\n"
	"	lock			\n"
	"	xaddl	%0,	%1	\n"
	"	decl	%0		\n"
	:	"=r"(Value), "+m"(*pAddend)
	:
	:	"cc");
#endif
	return Value;
#else // or "__arm__" or "__mips__"?
    return --(*pAddend);
#endif
}
class RefCntStr{
private: 
	class RefCountStr{
	public:
		RefCountStr(size_t dwCapacity):m_dwCapacity(dwCapacity), m_dwRefCount(1){}
		virtual ~RefCountStr(){}
		virtual unsigned int release(){
			unsigned int r = InterlockedDecrement((INT32 *)(&m_dwRefCount));
			if (!r){
				this->~RefCountStr();
				delete [] (char *)this;
			}
			return r;
		}
		inline unsigned int addRef(){
			return InterlockedIncrement((INT32 *)(&m_dwRefCount));
		}
		inline size_t getCapacity() const { return m_dwCapacity;}
	private:
		size_t m_dwCapacity;
		unsigned int m_dwRefCount;
	};

protected:
	inline static const char * copyString(const char * src, size_t l){
		char * p = createString(l);
		strncpy(p, src, l);
		return p;
	}

	inline static RefCountStr * getStrHeader(const char * s){
		return (RefCountStr *)(s - (sizeof(RefCountStr) / sizeof(char)));
	}
public:
  inline RefCntStr():m_sStr(NULL){}
	inline RefCntStr(const char * sStr):m_sStr(NULL){
		if (sStr) m_sStr = copyString(sStr, strlen(sStr));
	}
	inline RefCntStr(const char * sStr, size_t l):m_sStr(NULL){
		if (sStr) m_sStr = copyString(sStr, l);
	}	
	inline RefCntStr(const RefCntStr& s){
		m_sStr = s.m_sStr;
		if (m_sStr)	addRef(m_sStr);
	}
	inline RefCntStr(const wchar_t * wsStr):m_sStr(NULL){
		if (wsStr){
			size_t ll = wcstombs(NULL, wsStr, 0);
			if (ll == (size_t)-1) return;
			char * p = createString(ll);
			if (wcstombs(p, wsStr, ll) == (size_t)-1)
				release(p);
			else
				m_sStr = p;
		}
	}
	inline RefCntStr(const wchar_t * wsStr, size_t l):m_sStr(NULL){
		if (wsStr){
			wchar_t buf[l + 1];
			wcsncpy(buf, wsStr, l);
			buf[l] = 0;
			size_t ll = wcstombs(NULL, buf, 0);
			if (ll == (size_t)-1)
				return;
			char * p = createString(ll);
			if (wcstombs(p, buf, ll) == (size_t)-1)
				release(p);
			else
				m_sStr = p;
		}
	}
	//这个构造函数仅仅用于常数定义，x变量没有用的，仅是为了区分和复制const char * 的构造函数
	//参数不同。
	//这个构造函数不要使用
	inline RefCntStr(int /*x*/, const char * sStr):m_sStr(sStr){}

	inline ~RefCntStr(){if (m_sStr)	release(m_sStr);}

	inline RefCntStr & attach(const char * s){release(m_sStr); m_sStr = s; return *this; }

	//匹配一个常数，仅用于DEFINE_CONST_STR宏，其他地方不要用。
	inline RefCntStr & attachConst(const char * s1, size_t l){
		release(m_sStr); 
		m_sStr = NULL;
		RefCountStr * p = (RefCountStr *)s1;
		if (!p) return *this;
		new(p) RefCountStr(l);
		m_sStr = (char *)&p[1];
		p->addRef();//保证不释放，因为那个s1的空间是一个常数字符串。
		return *this; 
	}

	inline RefCntStr & reference(const char * s){addRef(s); release(m_sStr); m_sStr = s; return *this; }

	inline static char * createString(size_t l){
		RefCountStr * p = (RefCountStr *)new char[l + 1 + (sizeof(RefCountStr) / sizeof(char))];
		if (p == NULL) return NULL;
		new(p) RefCountStr(l);
		char * s = (char *)&p[1];
		s[l] = 0;
		return s; //p->m_sContent;
	}
	inline static unsigned int addRef(const char * s){
		if (!s) return 0;
		RefCountStr * p = getStrHeader(s);
		return p->addRef();
	}
	inline static unsigned int release(const char * s){
		if (!s) return 0;
		RefCountStr * p = getStrHeader(s);
		return p->release();
	}

	inline size_t capacity()const{
		if (!m_sStr) return 0;
		RefCountStr * p = getStrHeader(m_sStr);
		return p->getCapacity();
	}
	inline int compare(const char * str) const {
		return compare(m_sStr, str);
	}
	inline static int compare(const char * s1, const char * s2){
		if (NULL == s1){
			return (NULL == s2)?0:-1;
		} else {
			return (NULL == s2)?1:((s1 == s2)?0:strcmp(s1, s2));
		}
	}
	inline static int compareToIgnoreCase(const char * s1, const char * s2) {
		if (NULL == s1){
			return (NULL == s2)?0:-1;
		} else {
			return (NULL == s2)?1:((s1 == s2)?0:strcasecmp(s1, s2));
		}
	}
	inline int compareToIgnoreCase(const char * str) const {
		return compareToIgnoreCase(m_sStr, str);
	}
	inline int find(const char* str) const { 
		return (int)indexOf(str); 
	}
	inline bool equalsIgnoreCase(const char * str) const {return compareToIgnoreCase(str) == 0;}
	inline bool equals(const char * str) const {return compare(str) == 0;}
	inline operator const char * () const {	return m_sStr;}
	inline const char * data() const {
		if(m_sStr) addRef(m_sStr);
		return m_sStr;
	}
	inline size_t length() const{return m_sStr?strlen(m_sStr):0;}
	inline static size_t length(const char * p){return p?strlen(p):0;}
	inline RefCntStr & operator = (const char * sStr){
		if (m_sStr != sStr){
			if (m_sStr) release(m_sStr);
			m_sStr = NULL;		
			if (sStr) m_sStr = copyString(sStr, strlen(sStr));
		}
		return *this;
	}
	inline RefCntStr & operator = (const RefCntStr& s){
		if (m_sStr != s.m_sStr){
			if (m_sStr) release(m_sStr);
			m_sStr = s.m_sStr;
			if (m_sStr) addRef(m_sStr);
		}
		return *this;
	}
	inline const char ** operator & ()const{return (const char **)this;}
	inline operator bool () const {return m_sStr && m_sStr[0];}
	inline bool operator == (const RefCntStr & s) const { return compare(s.m_sStr) == 0;};
	inline bool operator != (const RefCntStr & s) const { return compare(s.m_sStr) != 0;};
	inline bool operator >= (const RefCntStr & s) const { return compare(s.m_sStr) >= 0;};
	inline bool operator <= (const RefCntStr & s) const { return compare(s.m_sStr) <= 0;};
	inline bool operator > (const RefCntStr & s) const { return compare(s.m_sStr) > 0;};
	inline bool operator < (const RefCntStr & s) const { return compare(s.m_sStr) < 0;};
	inline bool operator == (const char * s) const { return compare(s) == 0;};
	inline bool operator != (const char * s) const { return compare(s) != 0;};
	inline bool operator >= (const char * s) const { return compare(s) >= 0;};
	inline bool operator <= (const char * s) const { return compare(s) <= 0;};
	inline bool operator > (const char * s) const { return compare(s) > 0;};
	inline bool operator < (const char * s) const { return compare(s) < 0;};
	inline friend bool operator == (const char * s, const RefCntStr& str){return str.compare(s) == 0;};
	inline friend bool operator != (const char * s, const RefCntStr& str){return str.compare(s) != 0;};
	inline friend bool operator >= (const char * s, const RefCntStr& str){return str.compare(s) <= 0;};
	inline friend bool operator <= (const char * s, const RefCntStr& str){return str.compare(s) >= 0;};
	inline friend bool operator > (const char * s, const RefCntStr& str){return str.compare(s) < 0;};
	inline friend bool operator < (const char * s, const RefCntStr& str){return str.compare(s) > 0;};
	inline RefCntStr & operator += (const char * s) {
		if (NULL == s)
			return *this;
		size_t l2 = strlen(s);
		if (NULL == m_sStr){
			return *this = RefCntStr(s, l2);
		}
		if (0 == l2)
			return *this;
		size_t l1 = strlen(m_sStr);
		if (0 == l1)
			return *this = RefCntStr(s, l2);
		const char * temp = m_sStr;
		char * p = createString(l1 + l2);
		m_sStr = p;
		strncpy(p, temp, l1);
		p += l1;
		strncpy(p, s, l2); 
		release(temp); 
		return *this;
	}
	inline RefCntStr & operator += (const RefCntStr & s) {
		if (NULL == s.m_sStr)
			return *this;
		if (NULL == m_sStr){
			return *this = s;
		}
		size_t l2 = strlen(s.m_sStr);
		if (0 == l2)
			return *this;
		size_t l1 = strlen(m_sStr);
		if (0 == l1)
			return *this = s;
		const char * temp = m_sStr;
		char * p = createString(l1 + l2);
		m_sStr = p;
		strncpy(p, temp, l1);
		p += l1;
		strncpy(p, s.m_sStr, l2); 
		release(temp); 
		return *this;
	}
	inline RefCntStr operator + (const RefCntStr & s2)const {
		return RefCntStr(*this) += s2;
	}

	inline RefCntStr operator + (const char * s2)const {
		return RefCntStr(*this) += s2;
	}
	inline friend RefCntStr operator + (const char * s1, const RefCntStr & s2) {
		return RefCntStr(s1) += s2;
	}
	inline static RefCntStr format(const char *format, ...){
		va_list argptr;
		va_start(argptr, format);
		size_t l = (size_t)vsnprintf(NULL, 0, format, argptr);
		if (l >= 0x80000000){
			va_end(argptr);
			return STR_NULL;
		}
		char * p = createString(l);
		if (vsnprintf(p, l + 1, format, argptr) < 0){
			release(p); 
			va_end(argptr);
			return STR_NULL;
		}
		va_end(argptr);
		return RefCntStr().attach(p);
	}
	inline RefCntStr substr(size_t start, size_t length)const{
		return RefCntStr(&m_sStr[start], length);
	}
	inline RefCntStr substr(size_t start)const{
		return RefCntStr(&m_sStr[start]);
	}
		inline RefCntStr toLowerCase()const{
		if (NULL == m_sStr) return *this;
		const char * p = m_sStr;
		while (*p){
			if (*p >= 'A' && *p <= 'Z'){
				const char * pp = p;
				while (*pp) pp++;
				size_t l = (pp - m_sStr);
				char * dst = createString(l);
				strncpy(dst, m_sStr, l);
				pp = p;				
				size_t i = p - m_sStr;
				while(*pp){
					dst[i++] = tolower(*(pp++));
				}				
				return RefCntStr().attach(dst);
			}
			p++;
		}
		return *this;
	}
	inline RefCntStr toUpperCase()const{
		if (NULL == m_sStr) return *this;
		const char * p = m_sStr;
		while (*p){
			if (*p >= 'a' && *p <= 'z'){
				const char * pp = p;
				while (*pp) pp++;
				size_t l = (pp - m_sStr);
				char * dst = createString(l);
				strncpy(dst, m_sStr, l);
				pp = p;				
				size_t i = p - m_sStr;
				while(*pp){
					dst[i++] = toupper(*(pp++));
				}				
				return RefCntStr().attach(dst);
			}
			p++;
		}
		return *this;	
	}
	inline size_t indexOf(const char * str) const{
		if (!m_sStr) 
			return (size_t)-1; 
		else if (!str){
			return 0;
		}else{
			const char * p = strstr(m_sStr, str);
			if (NULL == p){
				return (size_t)-1;
			}else {
				return p - m_sStr;
			}
		}
	}
	inline static RefCntStr valueOf(int v) {
			return format("%d", v);
	}
	inline static RefCntStr valueOf(unsigned int v) {
		return format("%u", v);
	}

	inline bool isSame(const RefCntStr & s1)const{
		return m_sStr == s1.m_sStr;
	}

	inline size_t writeBuffer(char * p, size_t dwMax)const{
		if (!dwMax) return 0;
		if (!m_sStr) return 0;
		size_t l = length();
		if (dwMax > l && strncpy(p, m_sStr, l+1)){
			p[l] = 0;
			return l;
		}else {
			if (dwMax > 0)
				p[0] = 0;
			return 0;
		}	
	}
	inline size_t writeBuffer(char * p, size_t dwStart, size_t dwLength, size_t dwMax)const{
		if (dwLength > dwMax){
			if (dwMax > 0)
				p[0] = 0;
			return 0;
		} else if (strncpy(p, &m_sStr[dwStart], dwLength)){
			p[dwLength] = 0;
			return length(p);
		} else {
			return 0;
		}
	}
	inline RefCntStr trim() const{
		const char * p = m_sStr;
		if(!p) return RefCntStr();
		while (*p && (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')) p++;
		if (!*p) return RefCntStr();
		const char * pStart = p;
		p++;
		const char * pEnd = p;
		while (*p){
			if (*p != ' ' && *p != '\t' && *p != '\r' && *p != '\n')
				pEnd = p + 1;
			p ++;
		}
		if (pStart == m_sStr && !*pEnd)
			return *this;
		return RefCntStr(pStart, pEnd - pStart);
	}
	inline RefCntStr trimLeft(unsigned int c)const{
		const char * p = m_sStr;
		if(!p) return RefCntStr();
		while (*p && (*p == (int)c)) p++;
		if (!*p) return RefCntStr();
		if (p == m_sStr) return *this;
		return RefCntStr(p);
	}

	inline RefCntStr trimLeft()const{
		const char * p = m_sStr;
		if(!p) return RefCntStr();
		while (*p && ((*p == ' ') || (*p == '\t') || (*p == '\r') || (*p == '\n'))) p++;
		if (!*p) return RefCntStr();
		if (p == m_sStr) return *this;
		return RefCntStr(p);
	}
	inline static const char * trimLeft(const char * s, unsigned int c){
		const char * p = s;
		if(!p) return NULL;
		while (*p && (*p == (int)c)) p++;
		return p;
	}

	inline RefCntStr trimRight(unsigned int c)const{
		if(m_sStr == NULL || m_sStr[0] == '\0')
			return RefCntStr();

		const char* p = m_sStr;
		const char* last = NULL;
		while(*p)
		{
			if(*p == (int)c)
			{
				if(!last)last = p;
			}
			else
			{
				last = NULL;
			}
			p++;
		}
		if(last == NULL)
			return RefCntStr(*this);
		int newlen = last - m_sStr;
		if(newlen == 0)
			return RefCntStr();
		return RefCntStr(m_sStr, newlen);
	}
	inline RefCntStr trimRight()const{
		if(m_sStr == NULL || m_sStr[0] == '\0')
			return RefCntStr();
		const char* p = m_sStr;
		const char* last = NULL;
		while(*p)
		{
			if((*p == ' ') || (*p == '\t') || (*p == '\r') || (*p == '\n'))
			{
				if(!last)last = p;
			}
			else
			{
				last = NULL;
			}
			p++;
		}
		if(last == NULL)
			return RefCntStr(*this);
		int newlen = last - m_sStr;
		if(newlen == 0)
			return RefCntStr();
		return RefCntStr(m_sStr, newlen);
	}
	inline bool startWith(const char * s)const{
		const char * p = m_sStr;
		if (!s) return true;
		if (!p) return false;
		while (*s && *p == *s) p++, s++;
		return !(*s);
	}
	inline static bool startWith(const char * s1, const char * s2){
		if (!s2) return true;
		if (!s1) return false;		
		while (*s2 && *s1 == *s2) s1++, s2++;
		return !(*s2);
	}

	inline bool endWith(const char * s)const{
		if (!s) return true;
		if (!m_sStr) return false;
		size_t l = length();
		size_t l2 = length(s);
		if (l < l2) return false;
		const char * p = &m_sStr[l - l2];
		while (*s && *p == *s) p++, s++;
		return !(*s);
	}
	inline static bool endWith(const char * s1, const char * s2){
		if (!s1) return true;
		if (!s2) return false;
		size_t l = length(s1);
		size_t l2 = length(s2);
		if (l < l2) return false;
		const char * p = &s1[l - l2];
		while (*s2 && *p == *s2) p++, s2++;
		return !(*s2);
	}
	inline unsigned int hashCode()const{
		const char * p = m_sStr;
		if (NULL == p) return 0;
		unsigned int l = 0;
		unsigned int r = 0;
		while (( *p != 0) && (l < 16)) {
		  r = 31 * r + (*p);
		  p ++;
		  l ++;
		}
		return r;
	}
private:
	const char * m_sStr;
};

 
#define getCurrentPath _getCurrentPathA
#include <iostream>
using namespace std;
int main()
{
    INT32 campaignId = 198;
    INT32 count = 200;
    _str_t sql = _str_t::format("{call pkg_outbound_api.selectOutboundList(%d, %d)}", campaignId, count);
    printf("%s",sql.data());
    return 0;
}
