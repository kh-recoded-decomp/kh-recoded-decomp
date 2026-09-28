#include "nitro/types.h"

typedef struct Node {
    u8 pad_00[0xc];
    struct Node *next;
} Node;

extern int func_02004938(void);
extern void func_0200494c(int state);

void func_02010a74(Node **listHead, Node *target)
{
    Node *prev;
    Node *node;
    int state;

    if (listHead != NULL) {
        state = func_02004938();
        node = *listHead;
        prev = node;
        while (node != NULL) {
            if (node == target) {
                if (node == prev) {
                    *listHead = node->next;
                } else {
                    prev->next = node->next;
                }
                break;
            }
            prev = node;
            node = node->next;
        }
        func_0200494c(state);
    }
}
