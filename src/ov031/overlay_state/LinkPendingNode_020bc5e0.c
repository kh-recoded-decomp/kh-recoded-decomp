#include "nitro/types.h"

typedef struct ListNode {
    struct ListNode *next;
} ListNode;

typedef struct {
    u8 pad_00[0x404];
    ListNode *pending;
} OverlayState;

extern OverlayState *g_activeState_020bc800;

void LinkPendingNode_020bc5e0(ListNode *node)
{
    ListNode *it;
    ListNode *head;

    head = g_activeState_020bc800->pending;

    for (it = head; it != NULL; it = it->next) {
    }
    if (head == NULL) {
        g_activeState_020bc800->pending = node;
        return;
    }
    node->next = head->next;
    g_activeState_020bc800->pending->next = node;
}

