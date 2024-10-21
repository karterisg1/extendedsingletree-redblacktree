#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

struct node
{
	int key;
	char color;
	struct node *l, *r, *p;
};

RedBlackTree Tree;

void Initialize(Key key)
{
    Tree = (RedBlackTree) malloc(sizeof(*Tree));
	if (Tree == NULL)
	{
		printf("Cannot allocate memory...\n");
		exit(1);
	}
    Tree->l = Tree->r = Tree->p = NULL;
    Tree->color = 'b';
    Tree->key = key;
}


void RL(RedBlackTree x)
{
	RedBlackTree y;

	y = x->r;
	x->r = y->l;

	if (y->l != NULL)
	{
		y->l->p = x;
	}
	y->p = x->p;

	if (x->p == NULL)
	{
		Tree = y;
	}
	else if ((x->p->l != NULL) && (x->key == x->p->l->key))
	{
		x->p->l = y;
	}
	else 
	{
		x->p->r = y;
	}
	y->l = x;
	x->p = y;
}

void RR(RedBlackTree y)
{
	RedBlackTree x;

	x = y->l;
	y->l = x->r;

	if (x->r != NULL)
	{
		x->r->p = y;
	}
	x->p = y->p;
	if (y->p == NULL)
	{
		Tree = x;
	} 
	else if ((y->p->l != NULL) && (y->key == y->p->l->key))
	{
		y->p->l = x;
	}
	else
	{
		y->p->r = x;
	}
	x->r = y;
	y->p = x;
}

void color_insert(RedBlackTree z)
{
	RedBlackTree y = NULL;

	while ((z->p != NULL) && (z->p->color == 'r'))
	{
		if ((z->p->p->l != NULL) && (z->p->key == z->p->p->l->key))
		{
			if (z->p->p->r != NULL)
			{
				y = z->p->p->r;
			}
			if ((y != NULL) && (y->color == 'r'))
			{
				z->p->color = 'b';
				y->color = 'b';
				z->p->p->color = 'r';
				if (z->p->p != NULL)
				{
					z = z->p->p;
				}
			} 
			else
			{
				if ((z->p->r != NULL) && (z->key == z->p->r->key))
				{
					z = z->p;
					RL(z);
				}
				z->p->color = 'b';
				z->p->p->color = 'r';
				RR(z->p->p);
			}
		} 
		else
		{
			if (z->p->p->l != NULL)
			{
				y = z->p->p->l;
			}
			if ((y != NULL) && (y->color == 'r'))
			{
				z->p->color = 'b';
				y->color = 'b';
				z->p->p->color = 'r';
				if (z->p->p != NULL)
				{
					z = z->p->p;
				}
			} 
			else
			{
				if ((z->p->l != NULL) && (z->key == z->p->l->key))
				{
					z = z->p;
					RR(z);
				}
				z->p->color = 'b';
				z->p->p->color = 'r';
				RL(z->p->p);
			}
		}
	}
	Tree->color = 'b';
}

void InsertKey(Key key)
{
	RedBlackTree x, y, z;

	z = (RedBlackTree)malloc(sizeof(*z));
	if (z == NULL)
	{
		printf("Cannot allocate memory...\n");
		exit(1);
	}
	z->key = key;
	z->l = NULL;
	z->r = NULL;
	z->color = 'r';
	x = Tree;

	if (Search(key) == 1)
	{
		printf("\n%d already exists in the tree\n", key);
		return;
	}
	if (Tree == NULL)
	{
		Tree = z;
		Tree->color = 'b';
		return;
	}
	while (x != NULL)
	{
		y = x;

		if (z->key < x->key)
		{
			x = x->l;
		} 
		else
		{
			x = x->r;
		}
	}
	z->p = y;
	if (y == NULL)
	{
		Tree = z;
	} 
	else if (z->key < y->key)
	{
		y->l = z;
	}
	else
	{
		y->r = z;
	}
	color_insert(z);
	return;
}

void Print(RedBlackTree Tree)
{
	if (Tree != NULL)
	{
		Print(Tree->l);
		printf(" %d-%c ", Tree->key, Tree->color);
		Print(Tree->r);
	}
	return;
}

void PrintElements(void)
{
	Print(Tree);
}

int Search(Key key)
{
	RedBlackTree t = Tree;

	while (t != NULL)
	{
		if (key > t->key)
		{
			t = t->r;
		} 
		else if (key < t->key) 
		{
			t = t->l;
		} 
		else
		{
			printf("%d found\n", key);
			return 1;
		}
	}
	printf("%d not found\n", key);
	return 0;
}

RedBlackTree min(RedBlackTree x)
{
	while (x->l)
	{
		x = x->l;
	}
	return x;
}

RedBlackTree successor(RedBlackTree x)
{
	RedBlackTree y;

	if (x->r)
	{
		return min(x->r);
	}
	y = x->p;

	while (y && x == y->r)
	{
		x = y;
		y = y->p;
	}
	return y;
}

void color_delete(RedBlackTree x)
{
	while (x != Tree && x->color == 'b')
	{
		RedBlackTree w = NULL;

		if ((x->p->l != NULL) && (x == x->p->l))
		{
			w = x->p->r;
			if ((w != NULL) && (w->color == 'r'))
			{
				w->color = 'b';
				x->p->color = 'r';
				RL(x->p);
				w = x->p->r;
			}
			if ((w != NULL) && (w->r != NULL) && (w->l != NULL) && (w->l->color == 'b') && (w->r->color == 'b'))
			{
				w->color = 'r';
				x = x->p;
			}
			else if ((w != NULL) && (w->r->color == 'b'))
			{
				w->l->color = 'b';
				w->color = 'r';
				RR(w);
				w = x->p->r;
			}
			if (w != NULL)
			{
				w->color = x->p->color;
				x->p->color = 'b';
				w->r->color = 'b';
				RL(x->p);
				x = Tree;
			}
		} 
		else if (x->p != NULL)
		{
			w = x->p->l;
			if ((w != NULL) && (w->color == 'r'))
			{
				w->color = 'b';
				x->p->color = 'r';
				RL(x->p);
				if (x->p != NULL)
				{
					w = x->p->l;
				}
			}	
			if ((w != NULL) && (w->r != NULL) && (w->l != NULL) && (w->r->color == 'b') && (w->l->color == 'b'))
			{
				x = x->p;
			} 
			else if ((w != NULL) && (w->r != NULL) && (w->l != NULL) && (w->l->color == 'b'))
			{
				w->r->color = 'b';
				w->color = 'r';
				RR(w);
				w = x->p->l;
			}
			if (x->p != NULL)
			{
				w->color = x->p->color;
				x->p->color = 'b';
			}
			if (w->l != NULL)
			{
				w->l->color = 'b';
			}
			if (x->p != NULL)
			{
				RL(x->p);
			}
			x = Tree;
		}
	}
	x->color = 'b';
}

void RemoveKey(Key key)
{
	RedBlackTree x = NULL, y = NULL, z;

	z = Tree;

	if ((z->l == NULL) && (z->r == NULL) && (z->key == key))
	{
		Tree = NULL;
		printf("\nRBTREE is empty\n");
		return;
	}
	while (z != NULL && z->key != key)
	{
		if (key < z->key)
		{
			z = z->l;
		}
		else
		{
			z = z->r;
		}
		if (z == NULL)
		{
			return;
		}
	}
	if ((z->l == NULL) || (z->r == NULL))
	{
		y = z;
	}
	else
	{
		y = successor(z);
	}
	if (y->l != NULL)
	{
		x = y->l;
	} 
	else
	{
		if (y->r != NULL)
		{
			x = y->r;
		}
	}

	if ((x != NULL) && (y->p != NULL))
	{
		x->p = y->p;
	}
	if ((y != NULL) && (x != NULL) && (y->p == NULL))
	{
		Tree = x;
	} 
	else if (y == y->p->l)
	{
		y->p->l = x;
	}
	else
	{
		y->p->r = x;
	}
	if (y != z)
	{
		z->key = y->key;
	}
	if ((y != NULL) && (x != NULL) && (y->color == 'b'))
	{
		color_delete(x);
	}
	return;
}