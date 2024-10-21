#define NULLitem -1 /* NULLitem is a constant */
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (!less(A, B) && !less(B, A))
#define MAX(A,B) ((!less(A, B)) ? (A): (B))

typedef int Item;
typedef int Key;

typedef struct STnode *link;

struct STnode
{
	Item item; 
	struct STnode *l;
	struct STnode *r;
	int N; 
};

void visit(Item item);
link MakeTree(Item item);
Item Root(link root);
Item Parent(link tree, link node);
Item Sibling(link tree, link node);
int IsInternal(link tree, link node);
int IsExternal(link tree, link node);
link InsertLeft(link node, Item item);
link InsertRight(link node, Item item);
link Attach(link node, link left, link right);
link Remove(link tree, link node);
link Destroy(link tree);
void Preorder(link tree, void (*visit)(Item));
void Inorder(link tree, void (*visit)(Item));
void Postorder(link tree, void (*visit)(Item));
void Levelorder(link tree, void (*visit)(Item));
int Height(link tree);
int Size(link tree);
link Search(link tree, Key key);