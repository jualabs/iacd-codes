#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAXLINES 	20
#define MAXCHARS 	80
#define MAXSTR		(MAXCHARS-1)
#define MIDPNT		((MAXCHARS/2)-1)
#define SCALEDIV	10

int main() {
	int i;
	int offset;
	char sinstr[MAXCHARS];
	
	memset(sinstr, 0x20, MAXCHARS);
	sinstr[MAXSTR] = '\0';
	
	for(i = 0; i < MAXLINES; i++) {
		offset = MIDPNT + (int)(MIDPNT * sin(M_PI * (float) i/SCALEDIV));
		sinstr[offset] = '*';
		printf("%s\n", sinstr);
		sinstr[offset] = ' ';
	} 
}