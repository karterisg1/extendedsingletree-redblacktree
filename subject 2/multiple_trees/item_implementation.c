/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

int ITEMrand(void)
         { return rand(); }

int ITEMscan(int *x)
         { return scanf("%d", x); }

void ITEMshow(int x)
         { printf("%5d ", x); }
