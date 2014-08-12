


#if defined(__cplusplus)
extern "C" /* Use C linkage for kMain. */
#endif
#define VIDEO_MEM 0xB8000
void kMain(void)
{	

	char * s;
	;prints an A to the top left of the screen
	s	= ( char*)VIDEO_MEM;
	s[0] = 'A';
	s[1] = 0x03;color attribute
	
	
	
}
