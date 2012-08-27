#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"
#include <stdio.h>

int print_hello (void) {
	return printf("hello\n");
}

int treble (int x){
	x *= 3;
	return x;
}


MODULE = Example		PACKAGE = Example		

int
print_hello()

int
treble( x )
	int x
