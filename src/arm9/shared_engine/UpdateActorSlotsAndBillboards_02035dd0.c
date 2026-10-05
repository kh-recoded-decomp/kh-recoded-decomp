#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;
typedef void (*ActorSlotCallback)(ActorSlot *slot, int pass);

struct ActorSlot {
    ActorSlot *next;
    u8 pad_04[4];
    u16 flags;
    u8 pad_0a[0xb8 - 0x0a];
    u8 cullSphere[0x140 - 0xb8];
    u8 cullBox[0x15c - 0x140];
    int cullBoxState;
    u8 pad_160[0x1c0 - 0x160];
    int cullPlanes;
    u8 pad_1c4[2];
    s8 warmupTimer;
    u8 pad_1c7;
    ActorSlotCallback callback;
};

typedef struct BillboardNode {
    struct BillboardNode *next;
    u8 pad_04[0xc];
    void *list;
} BillboardNode;

typedef struct {
    u8 pad_00[0xc];
    ActorSlot *primarySlots;
    u8 pad_10[4];
    ActorSlot *secondarySlots;
    u8 pad_18[4];
    BillboardNode *billboards;
} ActorRegistry;

extern ActorRegistry *g_actorRegistry_0206083c;
extern u32 func_0202a9d0(u32 range);
extern int func_ov021_020af738(void *point, int planes);
extern int func_ov021_020af778(void *point, int planes);
extern void ResetGraphicsTransform_0202fdf4(void);
extern void Billboard_DrawList_0202fe70(void *list);

static inline void UpdateSlotList(ActorSlot *slot)
{
    for (; slot != NULL; slot = slot->next) {
        u16 flags = slot->flags;
        if ((flags & 8) && slot->callback != NULL) {
            BOOL active;
            if ((flags & 0x1000) && slot->warmupTimer < 15) {
                slot->warmupTimer++;
                active = TRUE;
            } else if (flags & 0x200) {
                active = TRUE;
                slot->flags |= 0x1000;
            } else {
                BOOL visible;
                if (flags & 0x400) {
                    visible = func_ov021_020af778(slot->cullSphere, slot->cullPlanes);
                } else if (slot->cullBoxState == -1 || func_ov021_020af738(slot->cullBox, slot->cullPlanes)) {
                    visible = TRUE;
                } else {
                    visible = FALSE;
                }
                if (visible) {
                    if (!(slot->flags & 0x200)) {
                        slot->warmupTimer = -(s8)func_0202a9d0(5);
                    }
                    active = TRUE;
                    slot->flags |= 0x1000;
                } else {
                    active = FALSE;
                    slot->flags &= ~0x1000;
                }
            }
            if (active) {
                slot->callback(slot, 0);
            }
        }
    }
}

void UpdateActorSlotsAndBillboards_02035dd0(void)
{
    ActorSlot *slot;
    BillboardNode *node;

    UpdateSlotList(g_actorRegistry_0206083c->primarySlots);
    for (slot = g_actorRegistry_0206083c->secondarySlots; slot != NULL; slot = slot->next) {
        if ((slot->flags & 0x18) == 0x18 && slot->callback != NULL) {
            slot->callback(slot, 1);
        }
    }
    UpdateSlotList(g_actorRegistry_0206083c->secondarySlots);
    node = g_actorRegistry_0206083c->billboards;
    if (node != NULL) {
        ResetGraphicsTransform_0202fdf4();
        do {
            Billboard_DrawList_0202fe70(&node->list);
            node = node->next;
        } while (node != NULL);
    }
}
