/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */

/* Definitions for the interface for the symbol table - file ST.h */

nlink STinit(nlink *);
int STcount(nlink);
nlink STinsert(nlink, nlink, Item);
Item STsearch(nlink, nlink, Key);
nlink STdelete(nlink, nlink, Key);
Item STselect(nlink, nlink, int);
void STsort(nlink h, nlink, void (*visit)(Item));