#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Panel Panel;
typedef void (*PanelCallback)(Panel *panel);

struct Panel {
    u8 pad_00[4];
    void *owner;
    u8 pad_08[0x28];
    u16 stateFlags;
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[4];
    u8 *model;
    union {
        PanelCallback callback;
        struct {
            s8 eventId;
            s8 itemId;
        } ids;
    } action;
    u8 activated;
    u8 pad_51[3];
    u16 flags;
    u8 pad_56[4];
    s16 linkIndex;
};

typedef struct {
    u8 pad_00[0x54];
    u16 flags;
} LinkedPanel;

typedef struct {
    u8 pad_00[0xc];
    u8 mode;
} PanelEvent;

extern void Flags16_ClearBit1(void *model);
extern u8 *ActorRegistry_GetEntityByIndex(int actorId);
extern void RebindAnimTracks(void *model, int track, int flags);
extern LinkedPanel *func_ov001_02086384(void *owner, int index);
extern int FindLivePrevBlock(Panel *panel);
extern void func_ov020_020a2914(int value, Panel *panel);
extern int FindLiveNextBlock(Panel *panel);
extern void func_ov020_020a2920(int value, Panel *panel);
extern void PlayWeightedRandomEntry(int itemId, VecFx32 *position);
extern void RollRewardOrbDrop(int eventId, VecFx32 *position);
extern void SpawnSoundSlot(int a, int b, VecFx32 *position, int c);
extern int func_ov001_02063a38(void);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

int ActivatePanel(Panel *panel, PanelEvent *event)
{
    int result;
    u32 count;

    if (event->mode == 0xff && (panel->flags & 0x200)) {
        return 0x10;
    }
    panel->activated = 1;
    if (!(panel->flags & 0x200)) {
        *(VecFx32 *)(panel->model + 0xa4) = panel->position;
        Flags16_ClearBit1(panel->model);
        panel->flags |= 0x20;
    }
    RebindAnimTracks(ActorRegistry_GetEntityByIndex(panel->actorId) + 4, 1, 0);
    Flags16_ClearBit1(ActorRegistry_GetEntityByIndex(panel->actorId) + 4);
    panel->flags |= 0x10;
    func_ov001_02086384(panel->owner, panel->linkIndex)->flags |= 4;
    result = FindLivePrevBlock(panel);
    if (result != 0) {
        func_ov020_020a2914(result, panel);
    }
    result = FindLiveNextBlock(panel);
    if (result != 0) {
        func_ov020_020a2920(result, panel);
    }
    panel->flags |= 0x8000;
    panel->stateFlags &= ~0x10;
    panel->stateFlags &= ~0x8;
    if (panel->flags & 0x100) {
        panel->action.callback(panel);
    } else if (event->mode != 0xff) {
        if (panel->action.ids.itemId >= 0) {
            PlayWeightedRandomEntry(panel->action.ids.itemId, &panel->position);
        } else if (panel->action.ids.eventId >= 0) {
            RollRewardOrbDrop(panel->action.ids.eventId, &panel->position);
        }
    }
    SpawnSoundSlot(0, 0x2d, &panel->position, 0);
    if (func_ov001_02063a38() == 0) {
        count = ReadSessionPackedBits(0x3ee6, 10);
        if (count < 0xff) {
            WriteSessionPackedBits(0x3ee6, 10, count + 1);
        }
    }
    return 0;
}
