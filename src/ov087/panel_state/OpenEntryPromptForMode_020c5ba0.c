#include "nitro/types.h"

typedef struct {
    u32 id;
    u8 pad_004[0x104];
} ListEntry;

typedef struct {
    u32 unk_00;
    int cursor;
    u8 pad_008[0x110];
    ListEntry entries[8];
    u8 pad_958[0x274];
    u32 exclusiveId;
} PanelScene;

extern void *func_ov039_020bc1bc(void);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern int func_ov087_020c4758(PanelScene *scene, int headerMessageId, int footerMessageId);
extern void func_ov087_020c4c70(PanelScene *scene);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, void *element, BOOL visible);

void OpenEntryPromptForMode_020c5ba0(PanelScene *scene, int mode)
{
    int frameId;
    void *frame;
    void *container = func_ov039_020bc1bc();
    u32 id = scene->entries[scene->cursor].id;

    if (mode == 3) {
        if (IsGlobalPackedBitSet_02027304(0x4436) && scene->exclusiveId == id) {
            frameId = func_ov087_020c4758(scene, 0xf, 0x16);
        } else {
            frameId = func_ov087_020c4758(scene, 0xf, 0x15);
        }
    } else {
        frameId = func_ov087_020c4758(scene, 0xd, 0x16);
    }
    func_ov087_020c4c70(scene);
    frame = func_ov027_020b90a4(container, frameId);
    func_ov027_020b9580(container, frame, TRUE);
}

