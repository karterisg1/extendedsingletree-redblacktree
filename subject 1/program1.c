#include <stdio.h>
#include <ctype.h>
#include "bt.h"

int main()
{
	link root = NULL, p = NULL, q1, q2, q3, q4, q7, q8, f;
	Item t;
	
	root = MakeTree(10);
	root->l = InsertLeft(root, 100);
	root->r = InsertRight(root, 1000);
	root->l->l = InsertLeft(root->l, 23);
	root->l->r = InsertRight(root->l, 32);
	root->r->l = InsertLeft(root->r, 123);
	root->r->r = InsertRight(root->r, 324);
	root->l->l->l = InsertLeft(root->l->l, 1232);
	root->l->l->r = InsertRight(root->l->l, 3244);

    printf("Level order traversal of the given tree \n");
    Levelorder(root, visit);
    printf("Size:\t%d\n", Size(root));
	printf("Height:\t%d\n", Height(root));
	printf("Root item:\t%d\n", Root(root));
	q1 = Search(root, 23);
	t = Parent(root, q1);
	printf("Parent of %d is %d\n", q1->item, t);
	printf("Simbling of %d is %d\n", q1->item, Sibling(root, q1));
	printf("internal %d, external %d\n", IsInternal(root, q1), IsExternal(root, q1));
	
	q2 = Search(root, 324);
	t = Parent(root, q2);
	printf("Parent of %d is %d\n", q2->item, t);
	printf("Simbling of %d is %d\n", q2->item, Sibling(root, q2));
	
	q3 = Search(root, 1232);
	t = Parent(root, q3);
	printf("Parent of %d is %d\n", q3->item, t);
	printf("Simbling of %d is %d\n", q3->item, Sibling(root, q3));
	printf("internal %d, external %d\n", IsInternal(root, q3), IsExternal(root, q3));
	
	root = Remove(root, q3);
	printf("Level order traversal AFTER REMOVAL of 1232\n");
    Levelorder(root, visit);
	
	root = Remove(root, q1);
	printf("Level order traversal AFTER REMOVAL of 23\n");
    Levelorder(root, visit);
	
	q7 = Search(root, 32);
	root = Remove(root, q7);
	printf("Level order traversal AFTER REMOVAL of 32\n");
    Levelorder(root, visit);
	
	q8 = Search(root, 100);
	root = Remove(root, q8);
	printf("Level order traversal AFTER REMOVAL of 100\n");
    Levelorder(root, visit);
	
	root->l->l = InsertLeft(root->l, 181);
	root->l->r = InsertRight(root->l, 1810);
	printf("Level order traversal AFTER InsertLeft of 181 & InsertRight of 1810\n");
	Levelorder(root, visit);
		
	p = MakeTree(80);
	p->l = InsertLeft(p, 99);
	p->r = InsertRight(p, 999);
	p->l->l = InsertLeft(p->l, 237);
	p->l->r = InsertRight(p->l, 329);
 
 	printf("Level order traversal of the given tree \n");
    Levelorder(p, visit);
    printf("Size:\t%d\n", Size(p));
	printf("Height:\t%d\n", Height(p));
	printf("Root item:\t%d\n", Root(p));
	
	f = MakeTree(987);
	f = Attach(f, root, p);
	printf("Level order traversal of the given tree \n");
    Levelorder(f, visit);
	
	f = Destroy(f);
	Levelorder(f, visit);
	printf("\nRoot item is %d\n", Root(f));
    return 0;
}
