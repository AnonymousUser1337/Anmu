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
#include "strings.h"
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
unsigned int location = VIDEO_MEM;
unsigned int x_pos = 0;
unsigned int y_pos = 0;
unsigned const int Cols = 80;


inline void itoa(int, int);
inline void putch(unsigned char c,int color );
inline void htoa(int n, int color);




inline void kPrintf(const char *s,int color, ...)
{
	
	va_list list;
    va_start( list, color );
	int j = 0;
	location =  VIDEO_MEM+(((Cols*2) * y_pos )+ (x_pos * 2));//calculate the location
	for(int i = 0;i< strlen_Const(s)*2;i+=2)
	{
		x_pos++;
		
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
					itoa(va_arg(list, int), color);
				break;
				case 's':
				x_pos-=1;//set it to correct location 
					kPrintf(va_arg(list,const char*), color);//print out the string
				break;
				case 'c':
				putch((unsigned char)va_arg(list, int), color);//print out char 
				break;
				
				case 'X':
				case 'x':
					htoa(va_arg(list,int),color);
				break;
			}
			x_pos++;//increment x
			j+=2;//skip the format e.g %d, %c
		}
		
		else// if no format detected just print char
		{	//Write Letter to Video Memory 
			unsigned char * c = (unsigned char*)location;
			c[i] = s[j];
			c[i+1] = color; 
			j++;
		
		}
		
	}
	va_end(list);
	
}
inline void itoa(int n, int color)
{
	int remainder = 0;
	int i = 0;

	char *s = 0;
	while(n>=1)
	{
		
		remainder = n%10;
		n = n/10;
		s[i] = remainder + 0x30;
		i++;
	}
	int j = i - 1;
	x_pos--;
	location =  VIDEO_MEM+(((Cols*2) * y_pos )+ (x_pos * 2));
	for(int i = 0;i< strlen(s)*2;i+=2)
	{
		unsigned char *c = (unsigned char*)location;
		c[i] = s[j];
		c[i+1] = color;
		j--;
	}
	
	
}
inline void putch(unsigned char c,int color )
{
	//write one letter to the screen
	location =  VIDEO_MEM+(((Cols*2) * y_pos )+ (x_pos * 2));
	unsigned char * s = (unsigned char*)location - 2;
	s[0] = c;
	s[1] = color;
}

inline void htoa(int n, int color)
{
	int remainder = 0;
	int i = 0;

	char *s = 0;
	while(n>=1)
	{
		
		remainder = n%16;//get the remainder
		n = n/16;//divide by 10 to go through the while loop
		
		s[i] = remainder;//convert to ascii and store in s
		i++;//get ready for the next number
	}
	int j = i - 1;//set j to the end of the string -1
	x_pos--;
	kPrintf("0x0",color);
	location =  VIDEO_MEM+(((Cols*2) * y_pos )+ (x_pos * 2));//calculate the new location
	for(int i = 0;i< strlen(s)*2;i+=2)
	{
		unsigned char *c = (unsigned char*)location;//set the location
		//write it to the screen
		if(s[j] >=0 && s[j] <10)
		{
			c[i] = s[j] + 0x30;
			c[i+1] = color;
		}
		else
		{
			switch(s[j])
			{
				case 10:
				putch('A',color);
				break;
				case 11:
				putch('B',color);
				break;
				case 12:
				putch('C',color);
				break;
				case 13:
				putch('D',color);
				break;
				case 14:
				putch('E',color);
				break;
				case 15:
				putch('F',color);
				break;
				
				
			}

		
		}
		j--;
	}
}
	

