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
#define Cols 80
#include <stdarg.h>

int location = VIDEO_MEM;
int x_pos = 0;
int y_pos = 0;

void itoa(int, int, int);
void putch(char c,int color );
void kPrintf(const char *s,int color, ...);
int strlen_Const(const char * s);
int strlen(char * s);
static inline void outb(unsigned int port,unsigned char value);
void update_cursor();
#if defined(__cplusplus)
extern "C" /* Use C linkage for kMain. */
#endif
void kMain(void)
{	
	int Color = LIGHT_BLUE;
	int Color2 = LIGHT_RED;
	const char *dir = "~/root";
	
	kPrintf("Anmu OS v0.01 Alpha\n",LIGHT_GREEN);
	kPrintf("CopyRight (c) 2014 Yeshua Colon\n",LIGHT_GREEN);
	putch('[',LIGHT_GREEN);
	kPrintf("Anmu@Computer ",Color);
	kPrintf("%s", Color2,dir);
	putch(']',LIGHT_GREEN);
	putch('#',LIGHT_CYAN );
	kPrintf("\n", 0);
	
}


void kPrintf(const char *s,int color, ...)
{
	
	va_list list;
    va_start( list, color );
	int j = 0;
	location =  VIDEO_MEM+(((Cols*2) * y_pos )+ (x_pos * 2));
	int k = 0;
	for(int i = 0;i< strlen_Const(s)*2;i+=2)
	{
		
		
		
		if(s[j] == '%')//see if there is something to be formated into the string 
		{
			
			switch(s[j+1])//find what format it is in 
			{
				case 'i':
				case 'd':
					itoa(va_arg(list, int), color, 10);//print out an integer
				break;
				
				case 's':
					k++;//increments if there is a formatted string
					kPrintf((const char*)va_arg(list,const char*), color);//print out the string
				break;
				
				case 'c':
					putch((char)va_arg(list, int), color);//print out char 
				break;
				
				case 'X':
				case 'x':
					itoa(va_arg(list,int), color, 16);//print out number in hex
				break;
			}
			j+=2;//skip the format types
		}
		else if(s[j] == '\n' || x_pos == Cols)
		{
			/*for some reason formatted strings with a new line in the same print make 
			the next print print in the wrong location Note: Must come back to this*/
			if(k!=0)//if there is a formatted string set the location back
			{
				x_pos = -2;//sets the location
				y_pos++;//go to the next line
				j++;
				putch(s[j],color);
			}
			else
			{
				x_pos = -1;//
				y_pos++;//go to the next line
				j++;
				putch(s[j],color);
			}
			
			
			
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
	if(base == 16)
	{
		kPrintf("0x",color);
	
	}
	while(n != 0)
	{
		
		remainder = n%base;
		n/=base;
		
		s[i] = (remainder > 9)? (remainder-10) + 'A' : remainder + '0';
		i++;
	}
	
	for(int j = strlen(s) - 1; j >= 0 ;j--)//Print the string in reverse to get the right number on the screen
	{
		putch(s[j],color);
		
	}
	

	
	
}
void putch(char c,int color)
{
	//Print a character to the video memory
	location =  VIDEO_MEM+(((Cols*2) * y_pos )+ (x_pos * 2));
	char * s = (char*)location;
	s[0] = c;
	s[1] = color;
	x_pos++;
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
    unsigned char cursor_loc=(y_pos*Cols) + x_pos;

    outb(0x3D4, 14);
    outb(0x3D5, cursor_loc>> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursor_loc);
}
static inline void outb(unsigned int port,unsigned char value)
{
   asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value));
}


