#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include"my_wrong_printf.h"
int main()
{
	printf(".%12f %-12f.\n", 1231.1231231231, 136.87978686);
	//my_printf(". %-.10f %-.0f.\n", 12.5, 12.4);
	//printf(".%-.10f.\n", 12.5);
	my_printf(".%0.5f. .%-+20.5f.\n", 1231.5601234, 999.999444);
	printf(".%0.5f. .%-+20.5f.\n", 1231.5601234, 999.999444);

	printf(".%+12.5f.\n", 12.5);
	printf(".%+12.10f.\n", 12.5);

	//printf("%d\n", (int)10.99);
	//   printf(".qwerty 12 %+-12.01ld%-12ld 2131 fwer .\n", 1231, 136);
	//my_printf(".qwerty 12 %+-12.01ld%-12ld 2131 fwer .\n", 1231, 136);


	return 0;
}
