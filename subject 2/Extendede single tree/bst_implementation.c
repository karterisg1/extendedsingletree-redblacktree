/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

typedef struct STnode* link;
struct STnode {Item item; link l, r; int N;};

static link head, z;
static Item NULLitem;

link NEW(Item item, link l, link r, int N)
  { link x = malloc(sizeof *x);
    x->item = item; x->l = l; x->r = r; x->N = N;
    return x;
  }

void STinit()
  {  
  NULLitem.ISBN = strdup("");
  NULLitem.title = strdup("");
  NULLitem.authors = strdup("");
  head = (z = NEW(NULLitem, NULL, NULL, 0)); }

int STcount() { return head->N; }

Item searchR(link h, Key v)
  { Key t = key(h->item);
    if (h == z) return NULLitem;
    if eq(v, t) return h->item;
    if less(v, t) return searchR(h->l, v);
             else return searchR(h->r, v);
  }

Item STsearch(Key v)
  { return searchR(head, v); }

link insertR(link h, Item item)
  { Key v = key(item), t = key(h->item);
    if (h == z) return NEW(item, z, z, 1);
    if (less(v, t))
         h->l = insertR(h->l, item);
    else h->r = insertR(h->r, item);
    (h->N)++; return h;
  }

void STinsert(Item item)
  { head = insertR(head, item); }

void sortR(link h, void (*visit)(Item))
  {
    if (h == z) return;
    sortR(h->l, visit);
    visit(h->item);
    sortR(h->r, visit);
  }

void STsort(void (*visit)(Item))
  { sortR(head, visit); }
  
/* code for finding the k-th smallest item in a BST */

Item selectR(link h, int k)
  { int t = h->l->N;
    if (h == z) return NULLitem;
    if (t > k) return selectR(h->l, k);
    if (t < k) return selectR(h->r, k-t-1);
    return h->item;
  }

Item STselect(int k)
  { return selectR(head, k); }