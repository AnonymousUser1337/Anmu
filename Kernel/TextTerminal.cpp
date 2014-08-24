#include "TextTerminal.h"
#include "IDT.h"
int location = VIDEO_MEM;
int x_pos = 0;
int y_pos = 0;


void runTerm()
{
	initIDT();
	int Color = LIGHT_BLUE;
	int Color2 = LIGHT_RED;
	int Color3 = LIGHT_GREEN;
	int Color4 = LIGHT_CYAN;
	const char *dir = "~/root";
	int year = 2014;
	kPrintf("Anmu OS v0.01 Alpha CLI \n",Color);
	kPrintf("CopyRight (c) %d Yeshua Colon\n",Color2, year);
	putch('[',Color3);
	kPrintf("Anmu@Computer ",Color);
	kPrintf("%s",Color2, dir);
	putch(']',Color3);
	kPrintf("#",Color4);
	
	while(1==1);//hang
	

}
void kPrintf(const char *s,int color, ...)
{
	
	va_list list;//create list of arguments
    va_start( list, color );//declare this the start
	for(int i = 0;i< strlen_Const(s);i++)
	{		
			
			if(s[i] == '%')
			{
				switch(s[i+1])//check for the right format
				{
					case 'i':
					case 'd':
						itoa(va_arg(list, int), color, 10);//print integer
						i+=2;//skip the format
					break;
					case 'c':
						putch((char)va_arg(list, int), color);
						i+=2;//skip the format
					break;
					case 's':
						kPrintf(va_arg(list, const char *),color);//print out string
						i+=2;//skip the format
					break;
					case 'X':
					case 'x':
						itoa(va_arg(list, int), color, 16);//print integer in hex
						i+=2;//skip the format
					break;
				}
				
				
			}
			if(x_pos>=Cols || s[i] == '\n' )
			{
				//create a new line
				x_pos = 0;
				y_pos++;
				i++;
				
			}
			if(s[i]!='\0')//if not end then print char 
			{
				putch(s[i],color);//write character to line
			}
			
			
	}
	
	va_end(list);//declare the last

}

void itoa(int n, int color,int base)
{
	int remainder = 0;
	int i = 0;
	char s[100] = {0};
	location =  VIDEO_MEM+(((Cols*2) * y_pos )+ (x_pos * 2));//calculate location
	if(base == 16)
	{
		kPrintf("0x",color);//identify as hex
	
	}
	while(n != 0)//get the number and convert to string
	{
		
		remainder = n%base;
		n/=base;
		
		s[i] = (remainder > 9)? (remainder-10) + 'A' : remainder + '0';
		i++;
	}
	
	for(int j = strlen(s) - 1; j >= 0 ;j--)//Print the string in reverse to get the right number on the screen
	{
		putch(s[j],color);//print character to screen
		
		
	}
	

	
	
}
void putch(char c,int color)
{	
	//Print a character to the video memory
	location =  VIDEO_MEM+(((Cols*2) * y_pos )+ (x_pos * 2));
	char * s = (char*)(intptr_t)location;
	s[0] = c;
	s[1] = color;
	
	x_pos++;
	update_cursor();
}


int strlen_Const(const char * s)//Get the length of the string constant
{	int length = 0;
	for (length = 0;*s != '\0'; ++s)
	{	length++;
	}
	return length;
}

int strlen(char * s)//get the length of the string 
{	int length = 0;
	for (length = 0;*s != '\0'; ++s)
	{	
		length++;
	}
	return length;

}
void update_cursor()
{
	
	unsigned short cursor_loc = (y_pos*Cols)+x_pos;
	 // cursor LOW port to vga INDEX register
 
    // cursor LOW port to vga INDEX register
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(cursor_loc&0xFF));
    // cursor HIGH port to vga INDEX register
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char )((cursor_loc>>8)&0xFF));
	
	
}



