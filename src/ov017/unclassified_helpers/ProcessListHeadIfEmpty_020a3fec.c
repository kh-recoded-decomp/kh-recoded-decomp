#include "nitro/types.h"

typedef struct ListNode {
    u8 pad_00[4];
    struct ListNode *next;
} ListNode;

typedef struct {
    u8 pad_00[0x60];
    ListNode *listHead;
} OverlayObject;

extern void func_ov017_020a4f20(ListNode **head);
extern void func_ov017_020a4100(OverlayObject *obj);

void ProcessListHeadIfEmpty_020a3fec(OverlayObject *obj)
{
    func_ov017_020a4f20(&obj->listHead);
    if (obj->listHead->next == obj->listHead) {
        func_ov017_020a4100(obj);
    }
}
