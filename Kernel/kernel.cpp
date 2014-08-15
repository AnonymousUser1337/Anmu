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
static inline void outb(unsigned port, unsigned char value);
void update_cursor();
void enable_cursor();
static inline unsigned char inb(unsigned short port);
//inline void outb(unsigned int port,unsigned char value);
//void update_cursor();
#if defined(__cplusplus)
extern "C" /* Use C linkage for kMain. */
#endif
void kMain(void)
{	
	int Color = LIGHT_BLUE;
	int Color2 = LIGHT_RED;
	int Color3 = LIGHT_GREEN;
	int Color4 = LIGHT_CYAN;
	const char *dir = "~/root";
	int year = 2014;
	enable_cursor();
	kPrintf("Anmu OS v0.01 Alpha CLI \n",Color);
	kPrintf("CopyRight (c) %d Yeshua Colon\n",Color2, year);
	putch('[',Color3);
	kPrintf("Anmu@Computer ",Color);
	kPrintf("%s",Color2, dir);
	putch(']',Color3);
	kPrintf("#",Color4);
	kPrintf("\n", 0);
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
	update_cursor();
}

void itoa(int n, int color,int base)
{
	int remainder = 0;
	int i = 0;
	char s[100];
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
	char * s = (char*)location;
	s[0] = c;
	s[1] = color;
	//update_cursor();//Not working should be updating the position of the cursor
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
	unsigned char cursor_loc = (y_pos*Cols)+x_pos;
	 // cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(cursor_loc));
    // cursor HIGH port to vga INDEX register
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((cursor_loc>>8)));
	
	
}
static inline void outb(unsigned int port, unsigned char value)
{
	asm volatile("out %%al, %%dx"::"d"(port),"a"(value));
	
}
void enable_cursor()
{
	outb(0x3D4, 0x0A);
	char curstart = inb(0x3D5) & 0x1F; // get cursor scanline start
	//kPrintf("%d\n", LIGHT_GREEN, curstart);
	outb(0x3D4, 0x0A);
	outb(0x3D5, curstart | 0x20); // set enable bit

}
static inline unsigned char inb(unsigned short port)
{
    unsigned char ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    /* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
    /* TODO: Should %1 be %w1? */
    /* TODO: Is there any reason to force the use of eax and edx? */
    return ret;
}
