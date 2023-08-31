#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H
#if defined( YOU_WIN_TXT ) || defined( YOU_WIN_GRAPHICAL_LXFB )


#include "eventq.h"


#define LENGTH_OF_TYPICAL_CURSOR_POS_UPDATE 5


void set_console_input_mode( void );
void reset_console_input_mode( void );


bool readconsoleinput( SOCKET s, EventQ * pQ );


#endif /* YOU_WIN_TXT || YOU_WIN_GRAPHICAL_LXFB */
#endif /* CONSOLE_INPUT_H */
