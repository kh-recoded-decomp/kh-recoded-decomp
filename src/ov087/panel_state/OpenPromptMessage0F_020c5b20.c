#include "nitro/types.h"

typedef struct {
    u32 id;
    u8 pad_004[0x104];
} ListEntry;

typedef struct {
    u32 unk_00;
    int cursor;
    u8 pad_008[0x110];
    ListEntry entries[10];
    u8 pad_b68[0x64];
    u32 activeId;
} EntryList;

extern void *func_ov039_020bc1bc(void);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern int func_ov087_020c4758(void *scene, int headerMessageId, int footerMessageId);
extern void func_ov087_020c4c70(void *scene);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, void *element, BOOL visible);

void OpenPromptMessage0F_020c5b20(EntryList *list)
{
    u32 selectedId;
    int frameId;
    void *frame;
    void *container;

    container = func_ov039_020bc1bc();
    selectedId = list->entries[list->cursor].id;

    if (IsGlobalPackedBitSet_02027304(0x4436) && list->activeId != selectedId) {
        frameId = func_ov087_020c4758(list, 0xf, 0x16);
    } else {
        frameId = func_ov087_020c4758(list, 0xf, 0x15);
    }
    func_ov087_020c4c70(list);
    frame = func_ov027_020b90a4(container, frameId);
    func_ov027_020b9580(container, frame, TRUE);
}
