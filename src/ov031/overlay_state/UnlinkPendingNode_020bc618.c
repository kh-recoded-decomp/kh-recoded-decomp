#include "nitro/types.h"

typedef struct ListNode {
    struct ListNode *next;
} ListNode;

typedef struct {
    u8 pad_00[0x404];
    ListNode *pending;
} OverlayState;

extern OverlayState *g_activeState_020bc800;

void UnlinkPendingNode_020bc618(ListNode *node)
{
    ListNode *prev = NULL;
    ListNode *it;

    for (it = g_activeState_020bc800->pending; it != NULL; it = it->next) {
        if (it == node) {
            if (prev != NULL) {
                prev->next = node->next;
            } else {
                g_activeState_020bc800->pending = NULL;
            }
            return;
        }
        prev = it;
    }
}
