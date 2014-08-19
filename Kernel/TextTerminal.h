#define BLACK 0x0
#define BLUE 0x01
#define GREEN 0x02
#define CYAN 0x03
#define RED 0x04
#define MAGENTA 0x05
#define BROWN 0x06
#define LIGHT_GRAY 0x07
#define DARK_GREY 0x08
#define LIGHT_BLUE 0x09
#define LIGHT_GREEN 0xA
#define LIGHT_CYAN 0xB
#define LIGHT_RED 0xC
#define LIGHT_MAGENTA 0xD
#define LIGHT_BROWN 0xE
#define WHITE 0xF
//0 - Black
//1 - Blue
//2 - Green
//3 - Cyan
//4 - Red
//5 - Magenta
//6 - Brown
//7 - Light Gray
//8 - Dark Gray
//9 - Light Blue
//10 - Light Green
//11 - Light Cyan
//12 - Light Red
//13 - Light Magenta
//14 - Light Brown
//15 - White

#define ASM_LINK extern "C"
#define VIDEO_MEM 0xB8000
#define Cols 80
#include <stdarg.h>
#include "HAL.h"
ASM_LINK void runTerm();
ASM_LINK void itoa(int, int, int);
ASM_LINK void putch(char c,int color );
ASM_LINK void kPrintf(const char *s,int color, ...);
ASM_LINK int strlen_Const(const char * s);
ASM_LINK int strlen(char * s);
ASM_LINK void update_cursor();
