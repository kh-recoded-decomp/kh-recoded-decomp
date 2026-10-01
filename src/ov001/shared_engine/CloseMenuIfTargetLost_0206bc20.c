#include "nitro/types.h"

typedef struct MenuRequest {
    u32 kind;
    union {
        struct {
            s16 eventId;
            s16 slot;
        } event;
        void *object;
    } target;
} MenuRequest;

typedef struct MenuContext {
    u32 flags;
    MenuRequest request;
    u8 pad_0c[0x3c];
    s32 range;
} MenuContext;

extern MenuContext *data_ov001_020a0484;
extern BOOL IsEventSlotInRange_0206b800(int context, int eventId, int slot, s32 range);
extern BOOL IsActorTargetable_0206b4a4(s32 playerIndex, void *object, s32 range);
extern BOOL func_ov001_0206b614(void *origin, void *object, s32 range);
extern BOOL IsActorNearLeader_0206b8d4(void *actor, s32 range);
extern void SetMenuOpenState_0206bb74(int open, BOOL withSound);

void CloseMenuIfTargetLost_0206bc20(void)
{
    MenuContext *menu = data_ov001_020a0484;
    BOOL lost = FALSE;
    BOOL withSound = TRUE;
    MenuRequest *request = &menu->request;

    switch (request->kind) {
    case 1:
        if (!(menu->flags & 0x80)) {
            lost = TRUE;
        }
        if (!IsEventSlotInRange_0206b800(0, request->target.event.eventId, request->target.event.slot, menu->range)) {
            lost = TRUE;
        }
        if (lost) {
            withSound = FALSE;
        }
        break;
    case 2:
        if (!IsActorTargetable_0206b4a4(0, request->target.object, menu->range)) {
            lost = TRUE;
        }
        break;
    case 3:
        if (!(menu->flags & 0x40)) {
            lost = TRUE;
        }
        if (!func_ov001_0206b614(NULL, request->target.object, menu->range)) {
            lost = TRUE;
        }
        break;
    case 4:
        if (!IsActorNearLeader_0206b8d4(request->target.object, menu->range)) {
            lost = TRUE;
        }
        break;
    }
    if (lost) {
        SetMenuOpenState_0206bb74(0, withSound);
    }
}
