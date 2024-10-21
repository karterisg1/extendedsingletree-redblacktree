/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

struct STnode {Item item; nlink l, r; Item N; };

nlink NEW(Item item, nlink l, nlink r, int N)
{
	nlink x = malloc(sizeof *x);
	x->item = item; x->l = l; x->r = r; x->N = N;
	return x;
}

/* initialization operation */  
nlink STinit(nlink *z)
{
	return ((*z) = NEW(NULLitem, NULL, NULL, 0));
}

/* count operation */
int STcount(nlink head) { return head->N; }

/* search operation */
Item STsearch(nlink h, nlink z, Key v)
{
	Key t = key(h->item);
	if (h == z) return NULLitem;
	if eq(v, t) return h->item;
	if less(v, t) return STsearch(h->l, z, v);
			 else return STsearch(h->r, z, v);
}

/* code for rotations */

nlink rotR(nlink h)
  { nlink x = h->l; h->l = x->r; x->r = h;
    return x; }
nlink rotL(nlink h)
  { nlink x = h->r; h->r = x->l; x->l = h;
    return x; }
	
/* recursive insert operation */
nlink STinsert(nlink h, nlink z, Item item)
{
	Key v = key(item), t = key(h->item);
    if (h == z) return NEW(item, z, z, 1);
    if less(v, t)
         h->l = STinsert(h->l, z, item);
    else h->r = STinsert(h->r, z, item);
    (h->N)++; return h;
}

/* sort operation */
void STsort(nlink h, nlink z, void (*visit)(Item))
{
	if (h == z) return;
	STsort(h->l, z, visit);
	visit(h->item);
	STsort(h->r, z, visit);
}

/* select operation */
Item STselect(nlink h, nlink z, int k)
{ 
	int t;
	if (h == z) return NULLitem;
	t = (h->l == z) ? 0 : h->l->N;
	if (t > k) return STselect(h->l, z, k);
	if (t < k) return STselect(h->r, z, k-t-1);
	return h->item;
}

/* partition auxiliary function */
nlink partR(nlink h, int k)
  { int t = h->l->N;
    if (t > k )
      { h->l = partR(h->l, k); h = rotR(h); }
    if (t < k )
      { h->r = partR(h->r, k-t-1); h = rotL(h); }
    return h;
  }

/* recursive deletion operation */
nlink joinLR(nlink a, nlink z, nlink b)
  {
    if (b == z) return a;
    b = partR(b, 0); b->l = a;
    return b;
  }
  
nlink STdelete(nlink h, nlink z, Key v)
  { nlink x; Key t = key(h->item);
    if (h == z) return z;
    if (less(v, t)) h->l = STdelete(h->l, z, v);
    if (less(t, v)) h->r = STdelete(h->r, z, v);
    if (eq(v, t))
      { x = h; h = joinLR(h->l, z, h->r); free(x); }
    return h;
  }