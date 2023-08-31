

#include "ywin.h"


#if defined( YOU_WIN_GRAPHICAL ) && defined( ANDROID )


class Android {

    public:

        static int32_t HandleInput( struct android_app * app, AInputEvent * event );
        static void HandleCmd( struct android_app * app, int32_t cmd );

//        static void ProcessDisplay( ANativeWindow * pWnd );

    private:

        static void HandleKeyPress( struct android_app * app, int32_t iKey, int32_t iAction, int32_t iRepeatCount, int32_t iMetaState );
        static void PostMessage( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam );

};


__thread protoBitmap<COLORREF> * pframebuffer = NULL;


#if 0
static uint16_t  make565( int iRed, int iGreen, int iBlue ) {

    int red   = ( ( iRed   / 255.0 ) * 32.0 );
    int green = ( ( iGreen / 255.0 ) * 64.0 );
    int blue  = ( ( iBlue  / 255.0 ) * 32.0 );

    return (uint16_t)( ((red   << 8) & 0xf800) |
                       ((green << 2) & 0x03e0) |
                       ((blue  >> 3) & 0x001f) );

}


static uint16_t make565( int red, int green, int blue ) {

    return (uint16_t)( ((red   << 8) & 0xf800) |
                       ((green << 2) & 0x03e0) |
                       ((blue  >> 3) & 0x001f) );

}


static uint16_t make565( int red, int green, int blue ) {

    return (uint16_t)( ((red   << 8) & 0xf800) |
                       ((green << 2) & 0x07e0) |
                       ((blue  >> 3) & 0x001f) );

}
#endif


void displayKeyboard( struct android_app * app, bool bShow ) {

    // Attaches the current thread to the JVM.
    jint lResult;
    jint lFlags = 0;

    JavaVM * lJavaVM = app->activity->vm;
    JNIEnv * lJNIEnv = app->activity->env;

    JavaVMAttachArgs lJavaVMAttachArgs;

    lJavaVMAttachArgs.version = JNI_VERSION_1_6;
    lJavaVMAttachArgs.name    = "NativeThread";
    lJavaVMAttachArgs.group   = NULL;

    lResult = lJavaVM->AttachCurrentThread( &lJNIEnv, &lJavaVMAttachArgs );

    if ( JNI_ERR == lResult ) {

        return;

    }

    // Retrieves NativeActivity.
    jobject lNativeActivity    = app->activity->clazz;
    jclass ClassNativeActivity = lJNIEnv->GetObjectClass( lNativeActivity );

    // Retrieves Context.INPUT_METHOD_SERVICE.
    jclass ClassContext = lJNIEnv->FindClass( "android/content/Context" );

    jfieldID FieldINPUT_METHOD_SERVICE = lJNIEnv->GetStaticFieldID( ClassContext, "INPUT_METHOD_SERVICE", "Ljava/lang/String;" );
    jobject INPUT_METHOD_SERVICE       = lJNIEnv->GetStaticObjectField( ClassContext, FieldINPUT_METHOD_SERVICE );

//    jniCheck( INPUT_METHOD_SERVICE );

    // Runs getSystemService( Context.INPUT_METHOD_SERVICE )
    jclass ClassInputMethodManager   = lJNIEnv->FindClass( "android/view/inputmethod/InputMethodManager" );
    jmethodID MethodGetSystemService = lJNIEnv->GetMethodID( ClassNativeActivity, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;" );
    jobject lInputMethodManager      = lJNIEnv->CallObjectMethod( lNativeActivity, MethodGetSystemService, INPUT_METHOD_SERVICE );

    // Runs getWindow().getDecorView().
    jmethodID MethodGetWindow    = lJNIEnv->GetMethodID( ClassNativeActivity, "getWindow", "()Landroid/view/Window;" );
    jobject lWindow              = lJNIEnv->CallObjectMethod( lNativeActivity, MethodGetWindow );
    jclass ClassWindow           = lJNIEnv->FindClass( "android/view/Window" );
    jmethodID MethodGetDecorView = lJNIEnv->GetMethodID( ClassWindow, "getDecorView", "()Landroid/view/View;" );
    jobject lDecorView           = lJNIEnv->CallObjectMethod( lWindow, MethodGetDecorView );

    if ( bShow ) {

        // Runs lInputMethodManager.showSoftInput(...).
        jmethodID MethodShowSoftInput = lJNIEnv->GetMethodID( ClassInputMethodManager, "showSoftInput", "(Landroid/view/View;I)Z" );
        lJNIEnv->CallBooleanMethod( lInputMethodManager, MethodShowSoftInput, lDecorView, lFlags );

    } else {

        // Runs lWindow.getViewToken()
        jclass ClassView               = lJNIEnv->FindClass( "android/view/View" );
        jmethodID MethodGetWindowToken = lJNIEnv->GetMethodID( ClassView, "getWindowToken", "()Landroid/os/IBinder;" );
        jobject lBinder                = lJNIEnv->CallObjectMethod( lDecorView, MethodGetWindowToken );

        // lInputMethodManager.hideSoftInput(...).
        jmethodID MethodHideSoftInput = lJNIEnv->GetMethodID( ClassInputMethodManager, "hideSoftInputFromWindow", "(Landroid/os/IBinder;I)Z" );
        lJNIEnv->CallBooleanMethod( lInputMethodManager, MethodHideSoftInput, lBinder, lFlags );

    }

    // Finished with the JVM.
    lJavaVM->DetachCurrentThread();

}


void DC::Out( const POINT & pt, COLORREF c ) {

    if ( NULL == pframebuffer ) {

        return;

    }

    pframebuffer->SetPixel( pt, c );

}


void Android::PostMessage( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    MetaMSG Msg;

    Msg.Msg.hwnd    = hWnd;
    Msg.Msg.message = uiMsg;
    Msg.Msg.wParam  = wParam;
    Msg.Msg.lParam  = lParam;

    g.Q.PostToQ( g.Q.MsgQ, &Msg );

}


#define KEY_UPDOWN( up, hWnd, c, repeatcount, state, f ) up ? FORWARD_WM_KEYUP( hWnd, c, repeatcount, state, f ) : FORWARD_WM_KEYDOWN( hWnd, c, repeatcount, state, f )


void Android::HandleKeyPress( struct android_app * app, int32_t iKey, int32_t iAction, int32_t iRepeatCount, int32_t iMetaState ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "key %d, action %d, repeat count %d, meta state %d" ), iKey, iAction, iRepeatCount, iMetaState );

    if ( AKEY_EVENT_ACTION_MULTIPLE == iAction ) {

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "MULTIPLE key %d, action %d, repeat count %d, meta state %d, not ready yet" ), iKey, iAction, iRepeatCount, iMetaState );
        return;

    }

    switch( iKey ) {

        case AKEYCODE_0:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '0', iRepeatCount, PostMessage ); break;
        case AKEYCODE_1:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '1', iRepeatCount, PostMessage ); break;
        case AKEYCODE_2:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '2', iRepeatCount, PostMessage ); break;
        case AKEYCODE_3:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '3', iRepeatCount, PostMessage ); break;
        case AKEYCODE_4:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '4', iRepeatCount, PostMessage ); break;
        case AKEYCODE_5:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '5', iRepeatCount, PostMessage ); break;
        case AKEYCODE_6:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '6', iRepeatCount, PostMessage ); break;
        case AKEYCODE_7:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '7', iRepeatCount, PostMessage ); break;
        case AKEYCODE_8:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '8', iRepeatCount, PostMessage ); break;
        case AKEYCODE_9:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '9', iRepeatCount, PostMessage ); break;

        case AKEYCODE_A:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'A' : 'a', iRepeatCount, PostMessage ); break;
        case AKEYCODE_B:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'B' : 'b', iRepeatCount, PostMessage ); break;
        case AKEYCODE_C:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'C' : 'c', iRepeatCount, PostMessage ); break;
        case AKEYCODE_D:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'D' : 'd', iRepeatCount, PostMessage ); break;
        case AKEYCODE_E:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'E' : 'e', iRepeatCount, PostMessage ); break;
        case AKEYCODE_F:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'F' : 'f', iRepeatCount, PostMessage ); break;
        case AKEYCODE_G:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'G' : 'g', iRepeatCount, PostMessage ); break;
        case AKEYCODE_H:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'H' : 'h', iRepeatCount, PostMessage ); break;
        case AKEYCODE_I:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'I' : 'i', iRepeatCount, PostMessage ); break;
        case AKEYCODE_J:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'J' : 'j', iRepeatCount, PostMessage ); break;
        case AKEYCODE_K:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'K' : 'k', iRepeatCount, PostMessage ); break;
        case AKEYCODE_L:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'L' : 'l', iRepeatCount, PostMessage ); break;
        case AKEYCODE_M:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'M' : 'm', iRepeatCount, PostMessage ); break;
        case AKEYCODE_N:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'N' : 'n', iRepeatCount, PostMessage ); break;
        case AKEYCODE_O:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'O' : 'o', iRepeatCount, PostMessage ); break;
        case AKEYCODE_P:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'P' : 'p', iRepeatCount, PostMessage ); break;
        case AKEYCODE_Q:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'Q' : 'q', iRepeatCount, PostMessage ); break;
        case AKEYCODE_R:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'R' : 'r', iRepeatCount, PostMessage ); break;
        case AKEYCODE_S:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'S' : 's', iRepeatCount, PostMessage ); break;
        case AKEYCODE_T:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'T' : 't', iRepeatCount, PostMessage ); break;
        case AKEYCODE_U:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'U' : 'u', iRepeatCount, PostMessage ); break;
        case AKEYCODE_V:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'V' : 'v', iRepeatCount, PostMessage ); break;
        case AKEYCODE_W:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'W' : 'w', iRepeatCount, PostMessage ); break;
        case AKEYCODE_X:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'X' : 'x', iRepeatCount, PostMessage ); break;
        case AKEYCODE_Y:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'Y' : 'y', iRepeatCount, PostMessage ); break;
        case AKEYCODE_Z:               if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ( AMETA_SHIFT_ON & iMetaState ) ? 'Z' : 'z', iRepeatCount, PostMessage ); break;

        case AKEYCODE_STAR:            if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '*', iRepeatCount, PostMessage ); break;
        case AKEYCODE_POUND:           if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '#', iRepeatCount, PostMessage ); break;
        case AKEYCODE_AT:              if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '@', iRepeatCount, PostMessage ); break;

        case AKEYCODE_COMMA:           if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ',', iRepeatCount, PostMessage ); break;
        case AKEYCODE_PERIOD:          if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '.', iRepeatCount, PostMessage ); break;

        case AKEYCODE_EQUALS:          if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '=', iRepeatCount, PostMessage ); break;

        case AKEYCODE_BACKSLASH:       if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '\\', iRepeatCount, PostMessage ); break;
        case AKEYCODE_SLASH:           if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '/', iRepeatCount, PostMessage ); break;

        case AKEYCODE_SEMICOLON:       if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, ';', iRepeatCount, PostMessage ); break;
        case AKEYCODE_APOSTROPHE:      if ( AKEY_EVENT_ACTION_UP == iAction ) FORWARD_WM_CHAR( NULL, '\'', iRepeatCount, PostMessage ); break;

        case AKEYCODE_SPACE:           KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_SPACE, iRepeatCount, 0, PostMessage ); break;

        case AKEYCODE_ENTER:           KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_RETURN, iRepeatCount, 0, PostMessage ); break;

        case AKEYCODE_TAB:             KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, ( AMETA_SHIFT_ON & iMetaState ) ? VK_BACKTAB : VK_TAB, iRepeatCount, 0, PostMessage ); break;

        case AKEYCODE_PAGE_UP:         KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_PRIOR, iRepeatCount, 0, PostMessage ); break;
        case AKEYCODE_PAGE_DOWN:       KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_NEXT, iRepeatCount, 0, PostMessage ); break;

        case AKEYCODE_DPAD_UP:         KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_UP, iRepeatCount, 0, PostMessage ); break;
        case AKEYCODE_DPAD_DOWN:       KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_DOWN, iRepeatCount, 0, PostMessage ); break;
        case AKEYCODE_DPAD_LEFT:       KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_LEFT, iRepeatCount, 0, PostMessage ); break;
        case AKEYCODE_DPAD_RIGHT:      KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_RIGHT, iRepeatCount, 0, PostMessage ); break;

//      case AKEYCODE_DPAD_CENTER: KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_CENTER, iRepeatCount, 0, PostMessage ); break;

        case AKEYCODE_DEL:              KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_BACK, iRepeatCount, 0, PostMessage ); break;

        case AKEYCODE_PLUS:             KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_ADD, iRepeatCount, 0, PostMessage ); break;
        case AKEYCODE_MINUS:            KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_SUBTRACT, iRepeatCount, 0, PostMessage ); break;

        case AKEYCODE_SHIFT_LEFT:       KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_LSHIFT, iRepeatCount, 0, PostMessage ); break;
        case AKEYCODE_SHIFT_RIGHT:      KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_RSHIFT, iRepeatCount, 0, PostMessage ); break;

        case AKEYCODE_VOLUME_UP:        KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_VOLUME_UP, iRepeatCount, 0, PostMessage ); break;
        case AKEYCODE_VOLUME_DOWN:      KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_VOLUME_DOWN, iRepeatCount, 0, PostMessage ); break;
        case AKEYCODE_MUTE:             KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_VOLUME_MUTE, iRepeatCount, 0, PostMessage ); break;

        case AKEYCODE_MEDIA_PLAY_PAUSE: KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_MEDIA_PLAY_PAUSE, iRepeatCount, 0, PostMessage ); break;
        case AKEYCODE_MEDIA_STOP:       KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_MEDIA_STOP, iRepeatCount, 0, PostMessage ); break;
        case AKEYCODE_MEDIA_NEXT:       KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_MEDIA_NEXT_TRACK, iRepeatCount, 0, PostMessage ); break;
        case AKEYCODE_MEDIA_PREVIOUS:   KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_MEDIA_PREV_TRACK, iRepeatCount, 0, PostMessage ); break;
//      case AKEYCODE_MEDIA_REWIND:
//      case AKEYCODE_MEDIA_FAST_FORWARD:

        case AKEYCODE_HOME:             KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_BROWSER_HOME, iRepeatCount, 0, PostMessage ); break;
        case AKEYCODE_BACK:             KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_BROWSER_BACK, iRepeatCount, 0, PostMessage ); break;
        case AKEYCODE_SEARCH:           KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_BROWSER_SEARCH, iRepeatCount, 0, PostMessage ); break;

        case AKEYCODE_ENVELOPE:         KEY_UPDOWN( AKEY_EVENT_ACTION_UP == iAction, NULL, VK_LAUNCH_MAIL, iRepeatCount, 0, PostMessage ); break;

        case AKEYCODE_LEFT_BRACKET:
        case AKEYCODE_RIGHT_BRACKET:

        case AKEYCODE_GRAVE:

        case AKEYCODE_POWER:
        case AKEYCODE_CAMERA:
        case AKEYCODE_CLEAR:

        case AKEYCODE_ALT_LEFT:
        case AKEYCODE_ALT_RIGHT:

        case AKEYCODE_SOFT_LEFT:
        case AKEYCODE_SOFT_RIGHT:

        case AKEYCODE_CALL:
        case AKEYCODE_ENDCALL:
        case AKEYCODE_HEADSETHOOK:

        case AKEYCODE_SYM:
        case AKEYCODE_EXPLORER:

        case AKEYCODE_NUM:
        case AKEYCODE_FOCUS:
        case AKEYCODE_MENU:
        case AKEYCODE_NOTIFICATION:

        case AKEYCODE_PICTSYMBOLS:
        case AKEYCODE_SWITCH_CHARSET:

        case AKEYCODE_BUTTON_A:
        case AKEYCODE_BUTTON_B:
        case AKEYCODE_BUTTON_C:
        case AKEYCODE_BUTTON_X:
        case AKEYCODE_BUTTON_Y:
        case AKEYCODE_BUTTON_Z:
        case AKEYCODE_BUTTON_L1:
        case AKEYCODE_BUTTON_R1:
        case AKEYCODE_BUTTON_L2:
        case AKEYCODE_BUTTON_R2:
        case AKEYCODE_BUTTON_THUMBL:
        case AKEYCODE_BUTTON_THUMBR:
        case AKEYCODE_BUTTON_START:
        case AKEYCODE_BUTTON_SELECT:
        case AKEYCODE_BUTTON_MODE:

        case AKEYCODE_UNKNOWN:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "UNKNOWN key %d, action %d, repeat count %d, meta state %d, not ready yet" ), iKey, iAction, iRepeatCount, iMetaState );
            break;

    }

}


int32_t Android::HandleInput( android_app * app, AInputEvent * event ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "android input event type %d received" ), AInputEvent_getType( event ) );

    switch( AInputEvent_getType( event ) ) {

        case AINPUT_EVENT_TYPE_KEY:

            HandleKeyPress( app, AKeyEvent_getKeyCode( event ), AKeyEvent_getAction( event ), AKeyEvent_getRepeatCount( event ), AKeyEvent_getMetaState( event ) );
            break;

        case AINPUT_EVENT_TYPE_MOTION:

            g.Q.PostMouseMsg( false, AMotionEvent_getX( event, 0 ), AMotionEvent_getY( event, 0 ), VK_LBUTTON, MK_LBUTTON );

            break;

        default:

            break;

    }

    return 0;

}


const char * orientation( int32_t iOrientation ) {

    switch( iOrientation ) {

        case ACONFIGURATION_ORIENTATION_ANY:    return "ANY";
        case ACONFIGURATION_ORIENTATION_PORT:   return "PORTRAIT";
        case ACONFIGURATION_ORIENTATION_LAND:   return "LANDSCAPE";
        case ACONFIGURATION_ORIENTATION_SQUARE: return "SQUARE";

    }

    return "UNKNOWN";

}


const char * CMD( int32_t cmd ) {

    switch( cmd ) {

        case APP_CMD_INPUT_CHANGED:        return "APP_CMD_INPUT_CHANGED";
        case APP_CMD_INIT_WINDOW:          return "APP_CMD_INIT_WINDOW";
        case APP_CMD_TERM_WINDOW:          return "APP_CMD_TERM_WINDOW";
        case APP_CMD_WINDOW_RESIZED:       return "APP_CMD_WINDOW_RESIZED";
        case APP_CMD_WINDOW_REDRAW_NEEDED: return "APP_CMD_WINDOW_REDRAW_NEEDED";
        case APP_CMD_CONTENT_RECT_CHANGED: return "APP_CMD_CONTENT_RECT_CHANGED";
        case APP_CMD_GAINED_FOCUS:         return "APP_CMD_GAINED_FOCUS";
        case APP_CMD_LOST_FOCUS:           return "APP_CMD_LOST_FOCUS";
        case APP_CMD_CONFIG_CHANGED:       return "APP_CMD_CONFIG_CHANGED";
        case APP_CMD_LOW_MEMORY:           return "APP_CMD_LOW_MEMORY";
        case APP_CMD_START:                return "APP_CMD_START";
        case APP_CMD_RESUME:               return "APP_CMD_RESUME";
        case APP_CMD_SAVE_STATE:           return "APP_CMD_SAVE_STATE";
        case APP_CMD_PAUSE:                return "APP_CMD_PAUSE";
        case APP_CMD_STOP:                 return "APP_CMD_STOP";
        case APP_CMD_DESTROY:              return "APP_CMD_DESTROY";

    }

    return "UNKNOWN";

}


static uint16_t make565( int red, int green, int blue ) {

    return (uint16_t)( blue >> 3 ) | ( ( green >> 2 ) << 5 ) | ( ( red >> 3 ) << 11 );

}


void android_repaint( HWND, UINT, UINT_PTR, DWORD ) {

    /* Copy over the bitmap */
    COLORREF c;

    ANativeWindow_Buffer buffer;

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "android painting" ) );

    if ( 0 > ANativeWindow_lock( g.app->window, &buffer, NULL ) ) {

        DBG_MSG( DBG_ERROR, TEXT( "ERROR LOCKING WINDOW SURFACE!!!" ) );
        return;

    }

    if ( ( pframebuffer->Width() != (unsigned)buffer.width ) || ( pframebuffer->Height() != (unsigned)buffer.height ) ) {

        DBG_MSG( DBG_ERROR, TEXT( "ERROR - BITMAP (%dx%d) AND FRAMEBUFFER (%dx%d) NOT THE SAME DIMENSIONS!!! REPAINTING" ), pframebuffer->Width(), pframebuffer->Height(), buffer.width, buffer.height );

        g.iCX = buffer.width;
        g.iCY = buffer.height;
//        ANativeWindow_unlockAndPost( pWnd );

//        Android::ProcessDisplay( pWnd );
//        return;
        pframebuffer->Create( buffer.width, buffer.height, GetSysColor( COLOR_BACKGROUND ) );

        FORWARD_WM_DISPLAYCHANGE( GetDesktopWindow(), 24, buffer.width, buffer.height, SendMessage );


    }

//    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "painting from %dx%d bitmap to %dx%d framebuffer, native API reports %dx%d" ), pframebuffer->getWidth(), pframebuffer->getHeight(), buffer.width, buffer.height, ANativeWindow_getWidth( g.app->window ), ANativeWindow_getHeight( g.app->window ) );

    // ARM looks like it is RED GREEN BLUE
    switch ( buffer.format ) {

        case WINDOW_FORMAT_RGB_565:

            for ( POINT pt = { 0, 0 }; pt.y < buffer.height; pt.y++ ) {

                for ( pt.x = 0; pt.x < buffer.width; pt.x++ ) {

                    if ( pframebuffer->GetPixel( pt, c ) ) {

                        /* Compute correct x,y */

                //    *pPixel = make565( GetRValue( c ), GetGValue( c ), GetBValue( c ) );

                        uint16_t * pPixel = ( (uint16_t *)buffer.bits ) + ( ( pt.y * buffer.stride ) + pt.x );

//                        *pPixel = RGB( GetGValue( c ), GetRValue( c ), GetBValue( c ) );
                        *pPixel = make565( GetRValue( c ), GetGValue( c ), GetBValue( c ) );

                    }

                }

            }
            break;

        case WINDOW_FORMAT_RGBA_8888:
        case WINDOW_FORMAT_RGBX_8888:

            for ( POINT pt = { 0, 0 }; pt.y < buffer.height; pt.y++ ) {

                for ( pt.x = 0; pt.x < buffer.width; pt.x++ ) {

                    if ( pframebuffer->GetPixel( pt, c ) ) {

                        /* Compute correct x,y */

                        COLORREF * pPixelx8888 = ( (COLORREF *)buffer.bits ) + ( ( pt.y * buffer.stride ) + pt.x );

//                        *pPixelx8888 = RGB( GetGValue( c ), GetRValue( c ), GetBValue( c ) );
                        *pPixelx8888 = RGBA( GetRValue( c ), GetGValue( c ), GetBValue( c ), 0 );

                    }

                }

            }
            break;

        default:

            DBG_MSG( DBG_ERROR, TEXT( "UNKNOWN FRAMEBUFFER FORMAT!!! %dx%d (STRIDE %d), FORMAT %d" ), buffer.width, buffer.height, buffer.stride, buffer.format );
            break;

    }

    ANativeWindow_unlockAndPost( g.app->window );

//    g.uDirtyCount = 0;

}


void Android::HandleCmd( android_app * app, int32_t cmd ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Android command '%s'" ), CMD( cmd ) );

    switch ( cmd ) {

        case APP_CMD_DESTROY:

            PostQuitMessage( 0 );
            break;

        case APP_CMD_SAVE_STATE:

            // The system has asked us to save our current state.
            PostMessage( GetDesktopWindow(), WM_POWERBROADCAST, PBT_APMSUSPEND, 0 );
            break;

        case APP_CMD_INIT_WINDOW:

            // The window is being shown, get it ready.
            if ( NULL == app->window ) {

                return;

            }

            if ( NULL == pframebuffer ) {

                pframebuffer = new protoBitmap<COLORREF>;

                if ( NULL == pframebuffer ) {

                    DBG_MSG( DBG_ERROR, TEXT( "Unable to allocate framebuffer" ) );
                    return;

                }

            }

            SetTimer( NULL, 1, 500, android_repaint );

//            android_repaint( app->window );
            break;

        case APP_CMD_CONFIG_CHANGED:

//            ProcessDisplay( app->window );
//            android_repaint( app->window );
            break;

        case APP_CMD_TERM_WINDOW:

            // The window is being hidden or closed, clean it up.
            break;

        case APP_CMD_GAINED_FOCUS:

            // When our app gains focus, we start monitoring the accelerometer.
//            if (engine->accelerometerSensor != NULL) {
//                ASensorEventQueue_enableSensor(engine->sensorEventQueue,
//                        engine->accelerometerSensor);
                // We'd like to get 60 events per second (in us).
//                ASensorEventQueue_setEventRate(engine->sensorEventQueue,
//                        engine->accelerometerSensor, (1000L/60)*1000);
//            }
            break;

        case APP_CMD_LOST_FOCUS:

            // When our app loses focus, we stop monitoring the accelerometer.
            // This is to avoid consuming battery while not being used.
//            if (engine->accelerometerSensor != NULL) {
//                ASensorEventQueue_disableSensor(engine->sensorEventQueue,
//                        engine->accelerometerSensor);
//            }
            // Also stop animating.
            break;

        default:

            DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "UNHANDLED APP_CMD %d (%s)" ), cmd, CMD( cmd ) );
            break;

    }

}


int droidSelect( struct timeval * ptimeout ) {

    int events;

    int iRet;

    struct android_poll_source * source = NULL;

    if ( ptimeout ) {

        iRet = ALooper_pollAll( ( ptimeout->tv_sec * 1000 ) + ( ptimeout->tv_usec / 1000 ),  NULL, &events, (void**)&source );

    } else {

        iRet = ALooper_pollAll( -1, NULL, &events, (void**)&source );

    }

//        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "ALooper_pollAll returned %d" ), iRet );

//        int8_t iCmd;

    switch( iRet ) {

        case LOOPER_ID_MAIN:

//                iCmd = android_app_read_cmd( g.app );

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "android_app_read_cmd returned %d" ), iCmd );

//                android_app_pre_exec_cmd( g.app, iCmd );
//                android_app_post_exec_cmd( g.app, iCmd );

            if ( NULL != source ) {

                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Calling process..." ) );
                source->process( g.app, source );
                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Process returned" ) );

            }

//                iCmd = android_app_read_cmd( g.app );

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "android_app_read_cmd returned %d" ), iCmd );

//                android_app_pre_exec_cmd( g.app, iCmd );
//                android_app_post_exec_cmd( g.app, iCmd );

//                DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "android_app_read_cmd finished command %d" ), iCmd );
            return 0;

        case ALOOPER_POLL_WAKE:

            break;

        case ALOOPER_POLL_TIMEOUT:

            break;

        case ALOOPER_POLL_ERROR:

            return -1;

        default:

            DBG_MSG( DBG_ERROR, TEXT( "UNKNOWN LOOPER RETURN CODE %d" ), iRet );
            break;

    }

    if ( NULL != source ) {

        DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Calling process..." ) );
        source->process( g.app, source );

    }

    return 0;

}


void onNativeWindowResized( ANativeActivity * activity, ANativeWindow * pWnd ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "NATIVEWINDOWRESIZED" ) );

//    int32_t iWidth;
//    int32_t iHeight;

//    if ( ! GetNativeWindowSize( pWnd, &iWidth, &iHeight ) ) {

//        DBG_MSG( DBG_ERROR, TEXT( "Unable to obtain display size" ) );
//        return;

//    }

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Native API reports display set to %dx%d" ), ANativeWindow_getWidth( pWnd ), ANativeWindow_getHeight( pWnd ) );

}


void onNativeWindowRedrawNeeded( ANativeActivity * activity, ANativeWindow * pWnd ) {

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "NATIVEWINDOWREDRAWNEEDED( %lX, %lX )" ) );
//    android_repaint( pWnd );
    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "Native API reports display set to %dx%d" ), ANativeWindow_getWidth( pWnd ), ANativeWindow_getHeight( pWnd ) );

}


int ywDisplay::Init( int cx, int cy, EventQ & Q, int argc, char * argv[], LPARAM lParam ) {

    struct android_app * app = reinterpret_cast<struct android_app *>( lParam );

    g.app                    = app;
    app->userData            = &g;

    app->onAppCmd            = Android::HandleCmd;
    app->onInputEvent        = Android::HandleInput;

    app->activity->callbacks->onNativeWindowResized      = onNativeWindowResized;
    app->activity->callbacks->onNativeWindowRedrawNeeded = onNativeWindowRedrawNeeded;

    DBG_MSG( DBG_GENERAL_INFORMATION, TEXT( "notification functions registered" ) );

//    *ppszPath = app->activity->internalDataPath;

    return 0;

}


void ywDisplay::Destroy( void ) {
}


#endif
