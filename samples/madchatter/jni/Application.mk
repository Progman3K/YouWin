APP_PLATFORM := android-16
APP_STL      := c++_static

MY_APP       := Android.mk

.SUFFIXES: .res .rc
.rc.res:
	windres --target=pe-i386 $(ALLINCLUDES) $(ALLDEFINES) -i $< -o $(basename $(notdir $<)).res




