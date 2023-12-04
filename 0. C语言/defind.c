#include <stdio.h>
#include <stdlib.h>
 
#define X   5
#define Y   X+1
#define Z   Y*X/2  // Z = X + 1 * X / 2
void defind1() {
    int a = Y; // a = X + 1
    printf("%d,%d", Z, --a); 
}

