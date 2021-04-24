make distclean;configure . "-DYOU_WIN_GRAPHICAL -DDEBUG" "EXTRA_DEFINES=-DDEBUG -UNDEBUG -DYOU_WIN_GRAPHICAL"

time make "CXXDEBUGFLAGS=-DDEBUG -UNDEBUG -DYOU_WIN_GRAPHICAL -g" "CDEBUGFLAGS=-DDEBUG -UNDEBUG -g"

reset;LD_LIBRARY_PATH=..:$LD_LIBRARY_PATH valgrind --leak-check=full --show-leak-kinds=all ./test

reset;LD_LIBRARY_PATH=..:$LD_LIBRARY_PATH ddd ./test 
