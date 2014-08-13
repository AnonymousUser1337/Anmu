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
unsigned int location = VIDEO_MEM;
unsigned int x_pos = 0;
unsigned int y_pos = 0;
unsigned const int Cols = 80;





inline void kPrintf(const char *s, int color)
{
	
	location  = VIDEO_MEM+(((Cols*2) * y_pos )+ ((x_pos *2)));
	char * c;
	c = (char*)location;
	int j = 0;
	for(int i = 0;i< strlen_Const(s)*2;i+=2)
	{
		x_pos++;
		//Write Letter to Video Memory which writes the letter to the screen
		if(s[j] == '\n' || x_pos == Cols)
		{
			x_pos = 0;
			y_pos++;
			
			
			
			j++;//skip the new line character
		}
		
		location = VIDEO_MEM+(((Cols*2) * y_pos )+ (x_pos * 2));
		c[i] = s[j];
		c[i+1] = color; 
		j++;
		c = (char*)location;/*Point the string to the VIDEO MEMORY */
		
		
	}
	
}
