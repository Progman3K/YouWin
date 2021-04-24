#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE           := test

LOCAL_SRC_FILES        := ../main.cpp \
                          ../resource.s

LOCAL_C_INCLUDES       := ../include /opt/youwin/include


$(LOCAL_PATH)/../resource.rc: $(LOCAL_PATH)/../strings.rc


resource.res: $(LOCAL_PATH)/../resource.rc
	windres --target=pe-i386 -I/opt/youwin/include -i resource.rc -o resource.res


$(LOCAL_PATH)/../resource.s: resource.res


LOCAL_LDLIBS           := -llog -landroid -ldl
LOCAL_STATIC_LIBRARIES := twindows

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,../../)
$(call import-module,twindows)
