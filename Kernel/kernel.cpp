
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
#define VIDEO_MEM 0xB8000
#include <stdarg.h>
#include "strings.h"
unsigned int location = VIDEO_MEM;
unsigned int x_pos = 0;
unsigned int y_pos = 0;
unsigned const int Cols = 80;
void itoa(int, int, int);
void putch(char c,int color );
void kPrintf(const char *s,int color, ...);

#if defined(__cplusplus)
extern "C" /* Use C linkage for kMain. */
#endif
void kMain(void)
{	
	int Color = LIGHT_BLUE;
	int Color2 = LIGHT_RED;

	kPrintf("Anmu@Computer",Color1);
	kPrintf("~/root#\n", Color2);
	
}


void kPrintf(const char *s,int color, ...)
{
	
	va_list list;
    va_start( list, color );
	int j = 0;
	location =  VIDEO_MEM+(((Cols*2) * y_pos )+ (x_pos * 2));
	for(int i = 0;i< strlen_Const(s)*2;i+=2)
	{
		
		
		if(s[j] == '\n' || x_pos == Cols)
		{
			x_pos = 0;//
			y_pos++;//go to the next line
			
			
			
			j++;//skip the new line character
		}
		if(s[j] == '%')
		{
			
			switch(s[j+1])//find what format it is in 
			{
				case 'i':
				case 'd':
					
					itoa(va_arg(list, int), color, 10);
				break;
				case 's':
					 
					kPrintf(va_arg(list,const char*), color);//print out the string
				break;
				case 'c':
					
					putch((unsigned char)va_arg(list, int), color);//print out char 
				break;
				case 'x':
					
					kPrintf("0x",color);
					
					itoa(va_arg(list,int), color, 16);
				break;
			}
			j+=2;
		}
		
		else// if no format detected just print char
		{	//Write Letter to Video Memory 
			putch(s[j],color);
			j++;
		
		}
		
	}
	va_end(list);
	
}

void itoa(int n, int color,int base)
{
	int remainder = 0;
	int i = 0;
	char s[100];
	unsigned char * c ;
	location =  VIDEO_MEM+(((Cols*2) * y_pos )+ (x_pos * 2));
	while(n != 0)
	{
		
		remainder = n%base;
		n/=base;
		
		s[i] = (remainder > 9)? (remainder-10) + 'A' : remainder + '0';
		i++;
	}
	
	for(int j = strlen(s) - 1; j >= 0 ;j--)
	{
		putch(s[j],color);
		
	}
	

	
	
}
void putch(char c,int color )
{
	location =  VIDEO_MEM+(((Cols*2) * y_pos )+ (x_pos * 2));
	unsigned char * s = (unsigned char*)location;
	s[0] = c;
	s[1] = color;
	x_pos++;
}



