CC = g++
CC_INCLUDES = -I/usr/include -I/usr/local/include -I.
CPPFLAGS    =  -Wall -O0 -g -fno-default-inline -pipe $(CC_INCLUDES)
CPPFLAGS_D  =  -Wall -g -O0 -fno-default-inline -pipe $(CC_INCLUDES) 
CC_COMPLIE  = $(CC) $(CPPFLAGS)
CC_COMPLIE_D  = $(CC) $(CPPFLAGS_D)
CC_LINK     = $(CC) -L/usr/lib/ -L/usr/local/lib/ -L./
CC_LINK_FLAGS = -ldl 

CC_TARGET   = MachMonitor
CC_TARGETD = MachMonitord
SRCS_CPP = $(wildcard ./*.cpp) 
OBJS_CPP = $(patsubst %.cpp,%.o,$(SRCS_CPP))
SRCS_C = $(wildcard ./*.c) 
OBJS_C = $(patsubst %.c,%.o,$(SRCS_C))
OBJS=$(OBJS_CPP) $(OBJS_C) 

LIBS= 

all:$(CC_TARGET)
%.d:%.cpp
	@set -e; rm -f $@; \
	$(CC_COMPLIE) -MM  $< > $@.$$$$; \
	sed 's,/($*/)/.o[ :]*,/1.o $@:,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

sinclude $(SRCS_CPP:.cpp=.d)
sinclude $(SRCS_C:.c=.d)

$(CC_TARGET):${OBJS} $(LIBS)
	$(CC_LINK)   $^ -o $@ $(CC_LINK_FLAGS)

clean:
	rm -f $(OBJS) $(CC_TARGET) ./*.d   
