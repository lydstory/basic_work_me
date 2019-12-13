CC = gcc
C++ = g++
LINK = g++
 
LIBS = 
#must add -fPIC option
CCFLAGS = $(COMPILER_FLAGS) -c -g -fPIC
C++FLAGS = $(COMPILER_FLAGS) -fpermissive -std=c++11 -c -g -fPIC
 
TARGET=libfxcodec.so
 
INCLUDES = -Icore/include -Ifpdfsdk/include  -I/home/songyu/work/pdfium_so/core/src/fxcodec/lcms2/include -I/home/songyu/work/pdfium_so/core/src/fxcodec/fx_libopenjpeg/include   -I/home/songyu/work/pdfium_so/core/src/fxcodec/fx_zlib/include -I/home/songyu/work/pdfium_so/core/src/fxcodec/fx_libopenjpeg/libopenjpeg20      -I/home/songyu/work/pdfium_so/core/src/fxcodec/lcms2/lcms2-2.6/include   -I/home/songyu/work/pdfium_so/core/src/fxcodec/fx_zlib/zlib_v128  -I/home/songyu/work/pdfium_so/core/src/fxcodec/fx_zlib/include 
 
CFILES =  core/src/fxcodec/fx_zlib/src/fx_zlib_zutil.c    core/src/fxcodec/fx_libopenjpeg/src/fx_bio.c        core/src/fxcodec/fx_libopenjpeg/src/fx_cio.c        core/src/fxcodec/fx_libopenjpeg/src/fx_dwt.c        core/src/fxcodec/fx_libopenjpeg/src/fx_event.c        core/src/fxcodec/fx_libopenjpeg/src/fx_function_list.c        core/src/fxcodec/fx_libopenjpeg/src/fx_image.c        core/src/fxcodec/fx_libopenjpeg/src/fx_invert.c        core/src/fxcodec/fx_libopenjpeg/src/fx_j2k.c        core/src/fxcodec/fx_libopenjpeg/src/fx_j2k_lib.c        core/src/fxcodec/fx_libopenjpeg/src/fx_jpt.c        core/src/fxcodec/fx_libopenjpeg/src/fx_mct.c        core/src/fxcodec/fx_libopenjpeg/src/fx_mqc.c        core/src/fxcodec/fx_libopenjpeg/src/fx_openjpeg.c        core/src/fxcodec/fx_libopenjpeg/src/fx_openjpeg_jp2.c        core/src/fxcodec/fx_libopenjpeg/src/fx_opj_clock.c        core/src/fxcodec/fx_libopenjpeg/src/fx_pi.c        core/src/fxcodec/fx_libopenjpeg/src/fx_raw.c        core/src/fxcodec/fx_libopenjpeg/src/fx_t1.c        core/src/fxcodec/fx_libopenjpeg/src/fx_t1_generate_luts.c        core/src/fxcodec/fx_libopenjpeg/src/fx_t2.c        core/src/fxcodec/fx_libopenjpeg/src/fx_tcd.c        core/src/fxcodec/fx_libopenjpeg/src/fx_tgt.c        core/src/fxcodec/fx_zlib/src/fx_zlib_adler32.c        core/src/fxcodec/fx_zlib/src/fx_zlib_compress.c        core/src/fxcodec/fx_zlib/src/fx_zlib_crc32.c        core/src/fxcodec/fx_zlib/src/fx_zlib_deflate.c        core/src/fxcodec/fx_zlib/src/fx_zlib_gzclose.c        core/src/fxcodec/fx_zlib/src/fx_zlib_gzlib.c        core/src/fxcodec/fx_zlib/src/fx_zlib_gzread.c        core/src/fxcodec/fx_zlib/src/fx_zlib_gzwrite.c        core/src/fxcodec/fx_zlib/src/fx_zlib_infback.c        core/src/fxcodec/fx_zlib/src/fx_zlib_inffast.c        core/src/fxcodec/fx_zlib/src/fx_zlib_inflate.c        core/src/fxcodec/fx_zlib/src/fx_zlib_inftrees.c        core/src/fxcodec/fx_zlib/src/fx_zlib_trees.c        core/src/fxcodec/fx_zlib/src/fx_zlib_uncompr.c  core/src/fxcodec/lcms2/src/fx_cmserr.c        core/src/fxcodec/lcms2/src/fx_cmsgamma.c        core/src/fxcodec/lcms2/src/fx_cmsgmt.c     core/src/fxcodec/lcms2/src/fx_cmshalf.c        core/src/fxcodec/lcms2/src/fx_cmsintrp.c        core/src/fxcodec/lcms2/src/fx_cmsio0.c        core/src/fxcodec/lcms2/src/fx_cmsio1.c        core/src/fxcodec/lcms2/src/fx_cmslut.c        core/src/fxcodec/lcms2/src/fx_cmsmd5.c        core/src/fxcodec/lcms2/src/fx_cmsmtrx.c        core/src/fxcodec/lcms2/src/fx_cmsnamed.c        core/src/fxcodec/lcms2/src/fx_cmsopt.c     core/src/fxcodec/lcms2/src/fx_cmspack.c        core/src/fxcodec/lcms2/src/fx_cmspcs.c        core/src/fxcodec/lcms2/src/fx_cmsplugin.c      core/src/fxcodec/lcms2/src/fx_cmsps2.c        core/src/fxcodec/lcms2/src/fx_cmssamp.c        core/src/fxcodec/lcms2/src/fx_cmssm.c        core/src/fxcodec/lcms2/src/fx_cmstypes.c        core/src/fxcodec/lcms2/src/fx_cmsvirt.c        core/src/fxcodec/lcms2/src/fx_cmswtpnt.c      core/src/fxcodec/lcms2/src/fx_cmsxform.c        core/src/fxcodec/libjpeg/fpdfapi_jcapimin.c        core/src/fxcodec/libjpeg/fpdfapi_jcapistd.c        core/src/fxcodec/libjpeg/fpdfapi_jccoefct.c        core/src/fxcodec/libjpeg/fpdfapi_jccolor.c        core/src/fxcodec/libjpeg/fpdfapi_jcdctmgr.c        core/src/fxcodec/libjpeg/fpdfapi_jchuff.c core/src/fxcodec/libjpeg/fpdfapi_jcinit.c        core/src/fxcodec/libjpeg/fpdfapi_jcmainct.c        core/src/fxcodec/libjpeg/fpdfapi_jcmarker.c        core/src/fxcodec/libjpeg/fpdfapi_jcmaster.c        core/src/fxcodec/libjpeg/fpdfapi_jcomapi.c        core/src/fxcodec/libjpeg/fpdfapi_jcparam.c        core/src/fxcodec/libjpeg/fpdfapi_jcphuff.c        core/src/fxcodec/libjpeg/fpdfapi_jcprepct.c        core/src/fxcodec/libjpeg/fpdfapi_jcsample.c        core/src/fxcodec/libjpeg/fpdfapi_jctrans.c        core/src/fxcodec/libjpeg/fpdfapi_jdapimin.c        core/src/fxcodec/libjpeg/fpdfapi_jdapistd.c        core/src/fxcodec/libjpeg/fpdfapi_jdcoefct.c        core/src/fxcodec/libjpeg/fpdfapi_jdcolor.c        core/src/fxcodec/libjpeg/fpdfapi_jddctmgr.c        core/src/fxcodec/libjpeg/fpdfapi_jdhuff.c        core/src/fxcodec/libjpeg/fpdfapi_jdinput.c        core/src/fxcodec/libjpeg/fpdfapi_jdmainct.c        core/src/fxcodec/libjpeg/fpdfapi_jdmarker.c        core/src/fxcodec/libjpeg/fpdfapi_jdmaster.c        core/src/fxcodec/libjpeg/fpdfapi_jdmerge.c        core/src/fxcodec/libjpeg/fpdfapi_jdphuff.c        core/src/fxcodec/libjpeg/fpdfapi_jdpostct.c        core/src/fxcodec/libjpeg/fpdfapi_jdsample.c        core/src/fxcodec/libjpeg/fpdfapi_jdtrans.c        core/src/fxcodec/libjpeg/fpdfapi_jerror.c        core/src/fxcodec/libjpeg/fpdfapi_jfdctfst.c    core/src/fxcodec/libjpeg/fpdfapi_jfdctint.c        core/src/fxcodec/libjpeg/fpdfapi_jidctfst.c        core/src/fxcodec/libjpeg/fpdfapi_jidctint.c core/src/fxcodec/libjpeg/fpdfapi_jidctred.c        core/src/fxcodec/libjpeg/fpdfapi_jmemmgr.c        core/src/fxcodec/libjpeg/fpdfapi_jmemnobs.c        core/src/fxcodec/libjpeg/fpdfapi_jutils.c core/src/fxcodec/lcms2/src/fx_cmscam02.c        core/src/fxcodec/lcms2/src/fx_cmscgats.c        core/src/fxcodec/lcms2/src/fx_cmscnvrt.c
C++FILES =core/src/fxcodec/codec/fx_codec.cpp     core/src/fxcodec/jbig2/JBig2_ArithIntDecoder.cpp        core/src/fxcodec/jbig2/JBig2_Context.cpp        core/src/fxcodec/jbig2/JBig2_GeneralDecoder.cpp        core/src/fxcodec/jbig2/JBig2_HuffmanDecoder.cpp        core/src/fxcodec/jbig2/JBig2_HuffmanTable.cpp        core/src/fxcodec/jbig2/JBig2_Image.cpp        core/src/fxcodec/jbig2/JBig2_Object.cpp       core/src/fxcodec/jbig2/JBig2_PatternDict.cpp   core/src/fxcodec/jbig2/JBig2_Segment.cpp        core/src/fxcodec/jbig2/JBig2_SymbolDict.cpp        core/src/fxcodec/codec/fx_codec_fax.cpp        core/src/fxcodec/codec/fx_codec_flate.cpp        core/src/fxcodec/codec/fx_codec_icc.cpp core/src/fxcodec/codec/fx_codec_jbig.cpp        core/src/fxcodec/codec/fx_codec_jbig_enc.cpp        core/src/fxcodec/codec/fx_codec_jpeg.cpp        core/src/fxcodec/codec/fx_codec_jpx_opj.cpp
 
OBJFILE = $(CFILES:.c=.o) $(C++FILES:.cpp=.o)
 
all:$(TARGET)
 
$(TARGET): $(OBJFILE)
	$(LINK) $^ $(LIBS) -Wall -fPIC -shared -o $@
 
%.o:%.c
	$(CC) -o $@ $(CCFLAGS) $< $(INCLUDES)
 
%.o:%.cpp
	$(C++) -o $@ $(C++FLAGS) $< $(INCLUDES)
 
install:
	tsxs -i -o $(TARGET)
 
clean:
	rm -rf $(TARGET)
	rm -rf $(OBJFILE)
 
