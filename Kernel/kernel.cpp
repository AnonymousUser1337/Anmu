#include "stdio.h"

#if defined(__cplusplus)
extern "C" /* Use C linkage for kMain. */
#endif
void kMain(void)
{	

	int Color = LIGHT_BLUE;
	int Color2 = LIGHT_RED;
	kPrintf("Anmu@Computer", Color);
	kPrintf(" ~/root #\n", Color2);
}


