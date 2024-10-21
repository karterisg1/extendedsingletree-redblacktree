typedef int Key;
typedef struct node *RedBlackTree;

void Initialize(Key key);
void InsertKey(Key key);
void PrintElements(void);
int Search(Key key);
void RemoveKey(Key key);