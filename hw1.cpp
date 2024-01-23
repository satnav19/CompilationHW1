#include "tokens.hpp"
#include <stdio.h>
int main()
{
	int token;
	while(token = yylex()) {
	  printf(" %d worked \n" ,token);
	}  

	return 0;
}
