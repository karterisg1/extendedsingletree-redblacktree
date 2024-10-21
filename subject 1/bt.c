// C Program to Construct a Binary root and perform operations

#include <stdio.h>
#include <stdlib.h>
#include "bt.h"

void visit(Item item)
{
	printf("%d\n", item);
}

// create a tree having root value item
link MakeTree(Item item)
{
	link p;

	p = (link) malloc(sizeof(*p));
	if (p == NULL)
    {
       fprintf(stderr, "\nAllocation failed\n");
       exit(1);
    }
	p->l = p->r = NULL;
	p->item = item;

	return p;
}

Item Root(link root)
{
	return (root == NULL) ? NULLitem : root->item;
}


link FindParent(link tree, link node)
{
	link left;
	
   // Base Cases
   if (tree->l == NULL && tree->r == NULL)
	return NULL;

   if (tree->l == node || tree->r == node)
    return tree;

   // Recursion
   left = FindParent(tree->l, node);
   if (left != NULL)
       return left;

   return FindParent(tree->r, node);
}

Item Parent(link tree, link node)
{
	link q;
	
	q = FindParent(tree, node);
	return (q != NULL ? q->item : NULLitem);
}

Item Sibling(link tree, link node)
{
	link p;
	
	p = FindParent(tree, node);
	if (p != NULL)
	{
		if (p->l == node)
			return p->r->item;
		else if (p->r == node)
			return p->l->item;
	}
	return NULLitem;
}

int IsInternal(link tree, link node)
{
	link p;
	
	if (node == NULL)
		return 0;
	p = Search(tree, key(node->item));
	return (p == node && (!IsExternal(tree, node)));
}

int IsExternal(link tree, link node)
{
	link p;
	
	if (node == NULL)
		return 0;
	p = Search(tree, key(node->item));
	return (p == node && p->l == NULL && p->r == NULL);
}

link InsertLeft(link node, Item item)
{
	if (node != NULL)
	{
		Destroy(node->l);
		node->l = MakeTree(item);
	}
	return node->l;
}

link InsertRight(link node, Item item)
{
	if (node != NULL)
	{
		Destroy(node->r);
		node->r = MakeTree(item);
	}
	return node->r;
}

link Attach(link node, link left, link right)
{
	if (IsExternal(node, node))
	{
		node->l = left;
		node->r = right;
	}
	return node;
}
		
link Remove(link tree, link node)
{
	link q;
	q = FindParent(tree, node);
	
	if (IsExternal(tree, node))
	{
		if (q != NULL)
		{
			if (q->l == node)
			{
				q->l = NULL;
			}
			else
			{
				q->r = NULL;
			}
		}
		free(node);
		node = NULL;
	}
	else if (IsExternal(tree, node->l) && node->r == NULL)
	{
		if (q != NULL)
		{
			if (q->l == node)
			{
				q->l = node->l;
			}
			else
			{
				q->r = node->l;
			}
		}
		free(node);
		node = NULL;
	}
	else if (IsExternal(tree, node->r) && node->l == NULL)
	{
		if (q != NULL)
		{
			if (q->l == node)
			{
				q->l = node->r;
			}
			else
			{
				q->r = node->r;
			}
		}
		free(node);
		node = NULL;
	}
	return tree;
}	

link Destroy(link tree)
{
    if (tree == NULL)
		return NULL;
	/* first delete both subtrees */
	tree->l = Destroy(tree->l);
	tree->r = Destroy(tree->r);
	   
	/* then delete the node */
	free(tree);
	tree = NULL;
	return tree;
}
	
// Preorder traversal
void Preorder(link tree, void (*visit)(Item))
{
    if (tree != NULL)
    {
        visit(tree->item);
        Preorder(tree->l, visit);
        Preorder(tree->r, visit);
    }
}

// Inorder traversal
void Inorder(link tree, void (*visit)(Item))
{
    if (tree != NULL)
    {
        Inorder(tree->l, visit);
        visit(tree->item);
        Inorder(tree->r, visit);
    }
}

// Postorder traversal
void Postorder(link tree, void (*visit)(Item))
{
    if (tree != NULL)
    {
        Postorder(tree->l, visit);
        Postorder(tree->r, visit);
        visit(tree->item);
    }
}

/* Print nodes at a current level */
void printCurrentLevel(link tree, int level, void (*visit)(Item))
{
    if (tree == NULL)
        return;
    if (level == 1)
        visit(tree->item);
    else if (level > 1) 
	{
        printCurrentLevel(tree->l, level - 1, visit);
        printCurrentLevel(tree->r, level - 1, visit);
    }
}

/* Function to print level order traversal a tree*/
void Levelorder(link tree, void (*visit)(Item))
{
    int h = Height(tree);
    int i;
	
    for (i = 1; i <= h; i++)
	{
        printCurrentLevel(tree, i, visit);
	}
}

// Number of nodes
int Size(link tree)
{
	if (tree == NULL) 
		return 0;
	return (Size(tree->l) + 1 + Size(tree->r));
}


// Height of a tree
int Height(link tree)
{
	if (tree == NULL) 
		return 0;
	return MAX(Height(tree->l), Height(tree->r)) + 1;
}

link Search(link tree, Key key)
{
	link p;
	
    if (tree == NULL)
        return NULL;
 
    if (key(tree->item) == key)
        return tree;
	
    // then recur on left subtree /
    p = Search(tree->l, key);
   
    // node found, no need to look further
    if (p != NULL) return p;
 
    // node is not found in left,
    // so recur on right subtree /
    p = Search(tree->r, key);
 
    if (p != NULL) return p;
}