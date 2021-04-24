#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE           := chatter

LOCAL_SRC_FILES        := ../src/resource.s \
                          ../src/chatter.cpp \
                          ../src/asyncret.cpp \
                          ../src/ccleanup.cpp \
                          ../src/chatcmd.cpp \
                          ../src/chatdlg.cpp \
                          ../src/chtinit.cpp \
                          ../src/chttimer.cpp \
                          ../src/deleteitem.cpp \
                          ../src/displaychange.cpp \
                          ../src/disptxt.cpp \
                          ../src/dlg_destroy.cpp \
                          ../src/dlg_init.cpp \
                          ../src/dlg_size.cpp \
                          ../src/getwho.cpp \
                          ../src/hostname.cpp \
                          ../src/maperror.cpp \
                          ../src/recvdata.cpp \
                          ../src/tcpxfer.cpp \
                          ../src/win32.cpp \
                          ../src/xfer.cpp

LOCAL_C_INCLUDES       := ../include /opt/youwin/include


$(LOCAL_PATH)/../src/resource/resource.rc: $(LOCAL_PATH)/../src/resource/dialogs.rc $(LOCAL_PATH)/../src/resource/strings.rc $(LOCAL_PATH)/../src/resource/version.rc


resource.res: $(LOCAL_PATH)/../src/resource/resource.rc
	windres --target=pe-i386 -I/opt/youwin/include -i src/resource/resource.rc -o resource.res


$(LOCAL_PATH)/../src/resource.s: resource.res


LOCAL_LDLIBS           := -llog -landroid
LOCAL_STATIC_LIBRARIES := youwin

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,/opt/youwin)
$(call import-module,src)
