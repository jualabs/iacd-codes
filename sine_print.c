/* sine_print.c
Print a sideways sine wave pattern using ASCII characters
Outputs an 80-byte array of ASCII characters (otherwise known as a string) 20 times, each time replacing elements in the array with an asterisk ('*') character to create a sideways plot of a sine function.
*/
#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
	int i;
	int offset;
	char sinstr[80];

	memset(sinstr,0x20, 80);
	sinstr[79] = '\0';

	for(i = 0; i < 20; i++) {
		offset = 39 + (int)(39 * cos(M_PI * (float) i/10));
		sinstr[offset] = '*';
		printf("%s\n", sinstr);
		sinstr[offset] = ' ';
	} 	
}
