#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE           := youwin

LOCAL_SRC_FILES        := src/ywresource.s \
                          src/addtext.cpp \
                          src/android.cpp \
                          src/atom.cpp \
                          src/bitblt.cpp \
                          src/bitmap.cpp \
                          src/buttonwndproc.cpp \
                          src/caret.cpp \
                          src/classlong.cpp \
                          src/close.cpp \
                          src/closew.cpp \
                          src/com.cpp \
                          src/comboboxwndproc.cpp \
                          src/console.cpp \
                          src/console_input.cpp \
                          src/dc.cpp \
                          src/defdlgproc.cpp \
                          src/defwndproc.cpp \
                          src/desktopwndproc.cpp \
                          src/dlgres.cpp \
                          src/draw.cpp \
                          src/drawtext.cpp \
                          src/editwndproc.cpp \
                          src/enumw.cpp \
                          src/event.cpp \
                          src/eventq.cpp \
                          src/fillrect.cpp \
                          src/findfile.cpp \
                          src/font.cpp \
                          src/get_topw.cpp \
                          src/getdcex.cpp \
                          src/getmessage.cpp \
                          src/getopenfilename.cpp \
                          src/getsyscolor.cpp \
                          src/gettextextentpoint.cpp \
                          src/getwtxt.cpp \
                          src/gl.cpp \
                          src/guid.cpp \
                          src/handler.cpp \
                          src/icon.cpp \
                          src/is_in.cpp \
                          src/isdialogmsg.cpp \
                          src/iswnd.cpp \
                          src/ldbitmap.cpp \
                          src/ldcursor.cpp \
                          src/ldicon.cpp \
                          src/ldmenu.cpp \
                          src/ldstring.cpp \
                          src/listboxwndproc.cpp \
                          src/lxfb.cpp \
                          src/menu.cpp \
                          src/messagebox.cpp \
                          src/object.cpp \
                          src/open.cpp \
                          src/openw.cpp \
                          src/pen.cpp \
                          src/posix.cpp \
                          src/postmessage.cpp \
                          src/progressbarwndproc.cpp \
                          src/redrawwindow.cpp \
                          src/regions.cpp \
                          src/registerclass.cpp \
                          src/sendmessage.cpp \
                          src/setcolour.cpp \
                          src/setwtxt.cpp \
                          src/show_win.cpp \
                          src/shgetfolderpath.cpp \
                          src/staticwndproc.cpp \
                          src/stretchblt.cpp \
                          src/textout.cpp \
                          src/universe.cpp \
                          src/unregisterclass.cpp \
                          src/winapi.cpp \
                          src/windowlong.cpp \
                          src/wsapi.cpp \
                          src/xwin.cpp

LOCAL_C_INCLUDES       := $(LOCAL_PATH) $(LOCAL_PATH)/include /opt/youwin/include

LOCAL_CFLAGS           := -DYOU_WIN_GRAPHICAL

ifeq ($(NDK_DEBUG),1)
    LOCAL_CFLAGS      += -DDEBUG
endif

$(LOCAL_PATH)/resource/resource.rc: \
               $(LOCAL_PATH)/resource/dialogs.rc \
               $(LOCAL_PATH)/resource/strings.rc


$(LOCAL_PATH)/ywresource.res: $(LOCAL_PATH)/resource/resource.rc
	cd $(LOCAL_PATH)/fntc ; xmkmf; make
	$(LOCAL_PATH)/fntc/fntc $(LOCAL_PATH)/resource/fonts/*.tfnt
	windres --target=pe-i386 -DYOU_WIN_GRAPHICAL -I$(LOCAL_PATH) -I$(LOCAL_PATH)/src -I/opt/youwin/include -i $< -o $(LOCAL_PATH)/yw$(basename $(notdir $<)).res


$(LOCAL_PATH)/src/ywresource.s: $(LOCAL_PATH)/ywresource.res


LOCAL_STATIC_LIBRARIES := android_native_app_glue

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_EXPORT_LDLIBS := -llog -landroid
LOCAL_EXPORT_LDFLAGS := -u android_main

include $(BUILD_STATIC_LIBRARY)

$(call import-module,android/native_app_glue)
