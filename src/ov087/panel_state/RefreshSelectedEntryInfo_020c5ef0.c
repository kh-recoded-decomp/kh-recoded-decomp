#include "nitro/types.h"

typedef struct {
    int firstItem;
    int itemCount;
} ItemRange;

typedef struct {
    int unlockLevels[25];
    u16 nameFormat[6];
} ItemUnlockData;

typedef struct {
    u32 id;
    u8 pad_004[0x104];
} ListEntry;

typedef struct {
    int kind;
    int unk_04;
} PanelMode;

typedef struct {
    u32 unk_00;
    int cursor;
    u8 pad_008[0x110];
    ListEntry entries[8];
    u8 pad_958[0x6c];
    u8 textLayer[0x1a0];
    int messageTable[3];
    PanelMode modes[6];
    int modeIndex;
    int unk_ba4;
    BOOL hasAvailableItem;
    u8 pad_bac[0x1c];
    u32 lockedId;
    u32 exclusiveId;
} PanelScene;

typedef struct {
    u8 pad_00[0xc];
    int state;
} ContainerFocus;

extern ItemRange data_ov087_020c7d3c[];
extern ItemUnlockData data_ov087_020c7e0c;

extern void *func_ov039_020bc1bc(void);
extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern const u16 *func_02051f48(u32 id, int variant);
extern void *func_ov027_020ba2a8(int *table, int index);
extern int OS_SNPrintf_0202e080(u16 *dst, u32 len, const u16 *fmt, ...);
extern void DrawTextAnchored_020015a0(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void Text_UploadTileBuffer_02001520(void *layer);
extern int func_02050050(int category, int index);
extern BOOL func_ov001_020645c8(int flagId);
extern ContainerFocus *func_ov027_020b90f4(void *container);
extern void func_ov087_020c431c(PanelScene *scene, BOOL enabled);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, void *element, BOOL visible);
extern void func_ov086_020c2060(u32 id);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void RefreshSelectedEntryInfo_020c5ef0(PanelScene *scene, BOOL playSound)
{
    u32 id = scene->entries[scene->cursor].id;
    void *container = func_ov039_020bc1bc();
    int itemIndex;
    int progressLevel;
    BOOL available;
    int itemCount;
    int itemEnd;
    u16 label[0x40];

    available = FALSE;
    CallVirtualHandlerSlot1_02001574(scene->textLayer, 0);
    if (id - 5 <= 1) {
        int suffixId = 0x1d;
        if (id != 5) {
            suffixId = 0x1e;
        }
        OS_SNPrintf_0202e080(label, 0x40, data_ov087_020c7e0c.nameFormat, func_02051f48(id, -1),
                             func_ov027_020ba2a8(scene->messageTable, suffixId));
        DrawTextAnchored_020015a0(scene->textLayer, 0x40, 2, 2, 0x411, label);
    } else {
        DrawTextAnchored_020015a0(scene->textLayer, 0x40, 2, 2, 0x411, func_02051f48(id, -1));
    }
    Text_UploadTileBuffer_02001520(scene->textLayer);

    itemIndex = data_ov087_020c7d3c[id].firstItem;
    itemCount = data_ov087_020c7d3c[id].itemCount;
    progressLevel = func_02050050(0, 9);
    if (id != 6 && id != scene->lockedId) {
        if (scene->modes[scene->modeIndex].kind != 2 || id != scene->exclusiveId) {
            for (itemEnd = itemIndex + itemCount; itemIndex < itemEnd; itemIndex++) {
                if (!func_ov001_020645c8(itemIndex + 0x581) &&
                    data_ov087_020c7e0c.unlockLevels[itemIndex] <= progressLevel) {
                    available = TRUE;
                    break;
                }
            }
        }
    }

    switch (scene->modes[scene->modeIndex].kind) {
    case 1:
    case 2:
    case 3:
        if (func_ov027_020b90f4(container)->state == 2) {
            func_ov087_020c431c(scene, available);
        } else {
            func_ov087_020c431c(scene, FALSE);
        }
        func_ov027_020b9580(container, func_ov027_020b90a4(container, 0xc), scene->hasAvailableItem);
        break;
    }
    if (playSound) {
        func_ov086_020c2060(id);
        PlaySoundEffect_0204d924(0, 0);
    }
    scene->hasAvailableItem = available;
}
