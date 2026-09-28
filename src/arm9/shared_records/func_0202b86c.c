#include "nitro/types.h"

typedef struct Node {
    struct Node *next;
} Node;

extern int func_02004938(void);
extern void func_0200494c(int state);
extern int data_02060564;

void func_0202b86c(Node *node)
{
    int state = func_02004938();
    node->next = *(Node **)((char *)&data_02060564 + 0x18);
    *(Node **)((char *)&data_02060564 + 0x18) = node;
    func_0200494c(state);
}
