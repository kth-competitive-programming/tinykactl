/* endian.c
 * Demonstrates endian ordering
 */

#include <stdio.h>

void main( void )
{
	short   Data_16; 
	long    Data_32;
	char far *p;

	Data_16 = 0x1234;
	Data_32 = 0x56789abc;

	p = (char far *)&Data_16;
	printf("16-bit quantity, data=%04x\n", Data_16);
	printf("address %Fp = %02x\n", p, (int)(*p) & 0xff);
	p++ ;
	printf("address %Fp = %02x\n", p, (int)(*p) & 0xff);
	p++ ;


	p = (char far *)&Data_32;
	printf("32-bit quantity, data=%08lx\n", Data_32);
	printf("address %Fp = %02x\n", p, (int)(*p) & 0xff);
	p++ ;
	printf("address %Fp = %02x\n", p, (int)(*p) & 0xff);
	p++ ;
	printf("address %Fp = %02x\n", p, (int)(*p) & 0xff);
	p++ ;
	printf("address %Fp = %02x\n", p, (int)(*p) & 0xff);

}
