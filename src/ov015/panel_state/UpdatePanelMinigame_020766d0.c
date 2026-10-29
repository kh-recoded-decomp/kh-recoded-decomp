#pragma opt_loop_invariants off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 x;
    s16 y;
} PanelPosition;

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} PanelRect;

typedef struct {
    s16 kind;
    s16 id;
    s16 count;
    u8 pad_06[6];
} PanelDescriptor;

typedef struct {
    s16 state;
    u16 flags;
    u8 pad_04[0x0c];
    int recordSource;
    int recordIndex;
} PanelSlot;

typedef struct {
    u8 pad_00[0x14];
    int recordIndex;
} ContainerItem;

typedef struct {
    u8 pad_0000[8];
    int state;
    int nextState;
    int timer;
    int delay;
    u32 flags;
    u8 pad_001c[0x18];
    s16 touchX;
    s16 touchY;
    u8 pad_0038[0x1a];
    s8 opponentKind;
    u8 pad_0053;
    s8 playerKind;
    s8 panelCount;
    s8 addCount;
    s8 filledCount;
    u8 pad_0058;
    s8 lockedCount;
    s8 openedCount;
    s8 hoverIndex;
    s8 hintIndex;
    s8 blendA;
    s8 blendB;
    u8 pad_005f;
    u16 angle;
    u8 pad_0062[2];
    fx32 scaleX;
    fx32 scaleY;
    PanelDescriptor playerDesc;
    PanelDescriptor opponentDesc;
    PanelSlot slots[9];
    u8 pad_015c[4];
    u8 container[0x647c];
    void *records;
    u8 textTable[0x5758];
    u8 touchPoint[4];
} PanelScene;

extern PanelScene *data_ov015_020812e0;
extern PanelPosition *data_ov015_0207e884[];
extern s16 data_0205356c[];
extern u8 data_ov015_0207a554[];

extern int func_ov002_02066c78(int id, int a, int b, int c);
extern BOOL IsButtonBPressed_020632c8(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern unsigned int func_0202a9d0(unsigned int range);
extern void *func_0202e060(void *dst, const char *fmt, ...);
extern void G2x_SetBlendAlpha_02006850(unsigned int *reg, unsigned int plane1, unsigned int plane2, unsigned int ev1, unsigned int ev2);
extern int func_0204f0b4(void *records, int a, int b);
extern void func_0204f0c0(void *records, int recordIndex);
extern void *func_0204f160(void *records, int recordSource);
extern void func_0204f178(void *records, int recordIndex, int scale);
extern void func_0204f24c(void *records, int recordIndex, int mode);
extern void SlotTable_SetEntryPair_0204f35c(void *records, int recordIndex, int first, int second);
extern void SlotTable_SetEntryPriority_0204f468(void *records, int recordIndex, int priority);
extern void Slot_SetMode2Bit_0204f480(void *records, int recordIndex, int enabled);
extern ContainerItem *func_ov027_020b90a4(void *container, int itemId);
extern void func_ov027_020b94b4(void *container, ContainerItem *item, int a, int b);
extern void func_ov027_020b94d8(void *container, ContainerItem *item, int a, int b);
extern void func_ov027_020b9580(void *container, ContainerItem *item, int enabled);
extern void func_ov027_020b96a0(void *container, ContainerItem *item, u16 frame);
extern void func_ov027_020b96e4(void *container, ContainerItem *item);
extern void func_ov027_020b984c(void *container, int enabled);
extern void func_ov027_020b9874(void *container, int enabled);
extern char *func_ov027_020ba2a8(void *table, int index);
extern void func_ov015_02077904(void);
extern void func_ov015_0207793c(void);
extern void func_ov015_02077978(int state);
extern void func_ov015_020779a4(int state, int nextState);
extern void func_ov015_020779c4(void);
extern BOOL func_ov015_02077a28(void);
extern BOOL func_ov015_02077fcc(void);
extern BOOL func_ov015_0207815c(int id);
extern BOOL func_ov015_020781dc(void);
extern void SetContainerSubitem1Active_02078228(BOOL active);
extern BOOL func_ov015_0207830c(PanelDescriptor *desc, int kind, PanelDescriptor *other);
extern BOOL func_ov015_02078438(PanelDescriptor *desc, void *source);
extern char *func_ov015_02078554(char *buffer, PanelDescriptor *desc);
extern void SetSceneRecordValue_020785f8(int recordIndex, void *value);
extern void func_ov015_02078638(int slotIndex, int animation);
extern BOOL func_ov015_020786e8(int slotIndex);
extern BOOL func_ov015_02078918(void);
extern void ClearSubBg2Screen_02078f34(void);
extern BOOL func_ov015_020790c0(void);
extern BOOL func_ov015_020790e8(void);
extern BOOL func_ov015_0207913c(PanelRect *rect, int x, int y);
extern int func_ov015_02079194(PanelRect *rect, void *point);
extern BOOL func_ov015_02079318(void);
extern void func_ov015_02079648(int a, int b, char *text);
extern void func_ov015_02079870(void);
extern void func_ov015_02079880(void);
extern void func_ov015_0207989c(int a, int b, char *text);
extern void func_ov015_02079a2c(int a, int b, char *text);

#define REG_DISPCNT_SUB (*(volatile u32 *)0x04001000)
#define REG_BLDALPHA_SUB (*(volatile u16 *)0x04001052)

BOOL UpdatePanelMinigame_020766d0(void) {
    int slot;
    int msgId;
    s16 touchX;
    BOOL result;
    int i;
    PanelPosition *positions;
    int completed;
    s16 touchY;
    int count;
    int remaining;
    s8 wins;
    u32 plane;
    ContainerItem *item;
    PanelRect rect;
    PanelDescriptor desc;
    PanelDescriptor *descPtr;
    char lineD[0x100];
    char lineC[0x100];
    char nameC[0x80];
    char lineA[0x100];
    char nameA[0x80];
    char lineB[0x100];
    char nameB[0x80];

    result = TRUE;
    switch (data_ov015_020812e0->state) {
    case 0:
        if (func_ov002_02066c78(0xf, 0, 0, 0) != 0) {
            func_ov015_02077978(2);
        } else {
            func_ov002_02066c78(0x80000014, 1, 0, 0);
            func_ov015_02079a2c(1, 5, func_ov027_020ba2a8(data_ov015_020812e0->textTable, 0x36));
            func_ov015_02077978(1);
        }
        break;
    case 1:
        if (func_ov015_02078918()) {
            func_ov015_02079880();
            func_ov015_02077978(2);
        }
        break;
    case 2:
        PlaySoundEffect_0204d924(2, 0xe);
        item = func_ov027_020b90a4(data_ov015_020812e0->container, 10);
        func_ov027_020b94b4(data_ov015_020812e0->container, item, 2, 0xa5);
        data_ov015_020812e0->timer = 0;
        func_ov015_02077978(3);
        break;
    case 3:
        data_ov015_020812e0->timer++;
        if (func_ov015_02078918() || data_ov015_020812e0->timer >= 60) {
            PlaySoundEffect_0204d924(2, 1);
            item = func_ov027_020b90a4(data_ov015_020812e0->container, 10);
            func_ov027_020b94d8(data_ov015_020812e0->container, item, 2, 0xa5);
            item = func_ov027_020b90a4(data_ov015_020812e0->container, 1);
            func_ov027_020b94b4(data_ov015_020812e0->container, item, 2, 0xa5);
            SetContainerSubitem1Active_02078228(TRUE);
            data_ov015_020812e0->timer = 0;
            func_ov015_02077978(4);
        }
        break;
    case 4:
        count = data_ov015_020812e0->panelCount;
        positions = data_ov015_0207e884[count];
        completed = 0;
        if (!(data_ov015_020812e0->flags & 0x10000) && func_ov015_020790c0()) {
            data_ov015_020812e0->flags |= 0x10000;
        }
        if (data_ov015_020812e0->flags & 0x10000) {
            if (data_ov015_020812e0->openedCount < data_ov015_020812e0->filledCount && func_ov015_020790e8()) {
                touchX = data_ov015_020812e0->touchX;
                touchY = data_ov015_020812e0->touchY;
                data_ov015_020812e0->hoverIndex = -1;
                for (i = 0; i < count; i++) {
                    rect.x = positions[i].x;
                    rect.y = positions[i].y;
                    rect.width = 0x28;
                    rect.height = 0x28;
                    if (func_ov015_0207913c(&rect, touchX, touchY)) {
                        if (data_ov015_020812e0->slots[i].state <= 1) {
                            data_ov015_020812e0->hoverIndex = i;
                        }
                        if (data_ov015_020812e0->slots[i].state == 0) {
                            if (data_ov015_020812e0->hintIndex >= 0 && func_ov015_020786e8(i)) {
                                data_ov015_020812e0->hintIndex = -1;
                            }
                            data_ov015_020812e0->slots[i].state = 1;
                            func_ov015_02078638(i, 7);
                            data_ov015_020812e0->openedCount++;
                        }
                        break;
                    }
                }
            }
            if (func_ov015_02079318()) {
                func_ov015_02077904();
                for (i = 0; i < count; i++) {
                    if (data_ov015_020812e0->slots[i].state == 1) {
                        rect.x = positions[i].x;
                        rect.y = positions[i].y;
                        rect.width = 0x28;
                        rect.height = 0x28;
                        if (func_ov015_02079194(&rect, data_ov015_020812e0->touchPoint) >= 0x4b) {
                            data_ov015_020812e0->slots[i].state = 2;
                            func_ov015_02078638(i, 4);
                        }
                    }
                }
            } else {
                func_ov015_0207793c();
            }
        }
        if (func_ov015_0207815c(0x3a)) {
            SetContainerSubitem1Active_02078228(FALSE);
            func_ov015_02077978(7);
        } else if (func_ov015_0207815c(0x3b)) {
            SetContainerSubitem1Active_02078228(FALSE);
            func_ov015_02077978(0xb);
        } else if (func_ov015_0207815c(0x3c)) {
            SetContainerSubitem1Active_02078228(FALSE);
            func_ov015_02077978(0x11);
        } else if (func_ov015_02077fcc()) {
            SetContainerSubitem1Active_02078228(FALSE);
            func_ov015_02077978(0x1b);
        } else if (func_ov015_02077a28()) {
            SetContainerSubitem1Active_02078228(FALSE);
            func_ov015_02077978(0x17);
        } else {
            for (i = 0; i < count; i++) {
                if (data_ov015_020812e0->slots[i].state == 3) {
                    completed++;
                }
            }
            if (completed >= data_ov015_020812e0->filledCount || (data_ov015_020812e0->flags & 4)) {
                for (i = 0; i < count; i++) {
                    if ((u16)data_ov015_020812e0->slots[i].state <= 1) {
                        data_ov015_020812e0->slots[i].state = 2;
                    }
                }
                item = func_ov027_020b90a4(data_ov015_020812e0->container, 1);
                func_ov027_020b94d8(data_ov015_020812e0->container, item, 2, 0xa5);
                SetContainerSubitem1Active_02078228(FALSE);
                func_ov015_02077978(5);
            } else {
                if (IsButtonBPressed_020632c8()) {
                    PlaySoundEffect_0204d924(2, 2);
                    func_ov015_02077978(0x20);
                }
            }
        }
        break;
    case 5:
        if (func_ov015_020781dc()) {
            func_ov015_02077978(6);
        }
        break;
    case 6:
        if (func_ov015_02078918()) {
            PlaySoundEffect_0204d924(2, 1);
            result = FALSE;
            func_ov015_02077978(0x29);
        }
        break;
    case 7:
        if (func_ov015_020781dc()) {
            msgId = 0xd;
            if (data_ov015_020812e0->playerKind == 3) {
                remaining = data_ov015_020812e0->panelCount - data_ov015_020812e0->lockedCount - data_ov015_020812e0->filledCount;
            } else {
                remaining = data_ov015_020812e0->panelCount - data_ov015_020812e0->filledCount;
            }
            data_ov015_020812e0->addCount = func_0202a9d0(3) + 1;
            if (data_ov015_020812e0->addCount > remaining) {
                data_ov015_020812e0->addCount = remaining;
            }
            if (data_ov015_020812e0->addCount >= 2) {
                msgId = 0x13;
            }
            PlaySoundEffect_0204d924(2, 10);
            item = func_ov027_020b90a4(data_ov015_020812e0->container, msgId);
            func_ov027_020b94b4(data_ov015_020812e0->container, item, 2, 0xa5);
            data_ov015_020812e0->delay = 4;
            func_ov015_020779a4(0x24, 8);
        }
        break;
    case 8:
        data_ov015_020812e0->filledCount += data_ov015_020812e0->addCount;
        func_ov015_02077978(9);
        break;
    case 9:
        data_ov015_020812e0->angle += 0x666;
        data_ov015_020812e0->scaleX = (data_0205356c[data_ov015_020812e0->angle >> 4] >> 1) + 0x1000;
        data_ov015_020812e0->scaleY = data_ov015_020812e0->scaleX;
        if (data_ov015_020812e0->angle >= 0x8000) {
            data_ov015_020812e0->angle = 0;
            data_ov015_020812e0->scaleY = 0x1000;
            data_ov015_020812e0->scaleX = data_ov015_020812e0->scaleY;
            func_ov015_02077978(10);
        }
        break;
    case 10:
        if (func_ov015_02078918()) {
            msgId = 0xd;
            if (data_ov015_020812e0->addCount >= 2) {
                msgId = 0x13;
            }
            PlaySoundEffect_0204d924(2, 1);
            item = func_ov027_020b90a4(data_ov015_020812e0->container, msgId);
            func_ov027_020b94d8(data_ov015_020812e0->container, item, 2, 0xa5);
            SetContainerSubitem1Active_02078228(TRUE);
            func_ov015_02077978(4);
        }
        break;
    case 11:
        if (func_ov015_020781dc()) {
            item = func_ov027_020b90a4(data_ov015_020812e0->container, 0xb);
            func_ov027_020b94b4(data_ov015_020812e0->container, item, 2, 0xa5);
            data_ov015_020812e0->delay = 4;
            func_ov015_020779a4(0x24, 0xc);
        }
        break;
    case 12:
        wins = func_ov002_02066c78(0x11, 0, 0, 0);
        func_ov002_02066c78(0x80000016, wins + 1, 0, 0);
        func_0202e060(lineD, func_ov027_020ba2a8(data_ov015_020812e0->textTable, 3), wins + 1, 99);
        func_ov015_0207989c(2, 10, lineD);
        func_ov015_02077978(0xd);
        break;
    case 13:
        if (func_ov015_02078918()) {
            wins = func_ov002_02066c78(0x11, 0, 0, 0);
            if (wins >= 99) {
                func_ov015_02077978(0xe);
            } else {
                func_ov015_02077978(0x10);
            }
        }
        break;
    case 14:
        descPtr = &desc;
        if (func_ov015_02078438(descPtr, data_ov015_0207a554)) {
            func_0202e060(lineC, func_ov027_020ba2a8(data_ov015_020812e0->textTable, 8), func_ov015_02078554(nameC, descPtr));
        } else {
            func_0202e060(lineC, func_ov027_020ba2a8(data_ov015_020812e0->textTable, 9), func_ov015_02078554(nameC, descPtr));
        }
        func_ov015_0207989c(2, 10, lineC);
        func_ov015_02077978(0xf);
        break;
    case 15:
        if (func_ov015_02078918()) {
            func_ov015_02077978(0x10);
        }
        break;
    case 16:
        func_ov015_02079880();
        item = func_ov027_020b90a4(data_ov015_020812e0->container, 0xb);
        func_ov027_020b94d8(data_ov015_020812e0->container, item, 2, 0xa5);
        SetContainerSubitem1Active_02078228(TRUE);
        func_ov015_02077978(4);
        break;
    case 17:
        if (func_ov015_020781dc()) {
            PlaySoundEffect_0204d924(2, 10);
            item = func_ov027_020b90a4(data_ov015_020812e0->container, 0xc);
            func_ov027_020b94b4(data_ov015_020812e0->container, item, 2, 0xa5);
            data_ov015_020812e0->delay = 4;
            func_ov015_020779a4(0x24, 0x12);
        }
        break;
    case 18:
        func_ov015_02077978(0x13);
        break;
    case 19:
        if (func_ov015_02078918()) {
            PlaySoundEffect_0204d924(2, 1);
            data_ov015_020812e0->blendA = 0x10;
            data_ov015_020812e0->blendB = 0;
            G2x_SetBlendAlpha_02006850((unsigned int *)0x04001050, 8, 0x10, data_ov015_020812e0->blendA, data_ov015_020812e0->blendB);
            item = func_ov027_020b90a4(data_ov015_020812e0->container, 0xc);
            func_ov027_020b94d8(data_ov015_020812e0->container, item, 2, 0xa5);
            func_ov015_02077978(0x14);
        }
        break;
    case 20:
        data_ov015_020812e0->blendA--;
        data_ov015_020812e0->blendB++;
        REG_BLDALPHA_SUB = (u16)(data_ov015_020812e0->blendA | (data_ov015_020812e0->blendB << 8));
        if (data_ov015_020812e0->blendA == 8) {
            func_ov015_02077978(0x15);
        }
        break;
    case 21:
        data_ov015_020812e0->timer++;
        if (data_ov015_020812e0->timer >= 30) {
            data_ov015_020812e0->timer = 0;
            func_ov015_02077978(0x16);
        }
        break;
    case 22:
        data_ov015_020812e0->blendA++;
        data_ov015_020812e0->blendB--;
        REG_BLDALPHA_SUB = (u16)(data_ov015_020812e0->blendA | (data_ov015_020812e0->blendB << 8));
        if (data_ov015_020812e0->blendA == 0x10) {
            G2x_SetBlendAlpha_02006850((unsigned int *)0x04001050, 0, 0, 0, 0);
            SetContainerSubitem1Active_02078228(TRUE);
            func_ov015_02077978(4);
        }
        break;
    case 23:
        if (func_ov015_020781dc()) {
            if (!func_ov015_0207830c(&data_ov015_020812e0->playerDesc, data_ov015_020812e0->playerKind, &data_ov015_020812e0->opponentDesc)) {
                data_ov015_020812e0->flags |= 0x100;
            }
            func_ov015_020779a4(0x25, 0x18);
        }
        break;
    case 24:
        item = func_ov027_020b90a4(data_ov015_020812e0->container, 0xe);
        func_ov027_020b94b4(data_ov015_020812e0->container, item, 2, 0xa5);
        data_ov015_020812e0->delay = 4;
        func_ov015_020779a4(0x24, 0x19);
        break;
    case 25:
        descPtr = &data_ov015_020812e0->playerDesc;
        if (!(data_ov015_020812e0->flags & 0x100) || descPtr->kind == 9) {
            func_0202e060(lineA, func_ov027_020ba2a8((*(PanelScene *volatile *)&data_ov015_020812e0)->textTable, 8), func_ov015_02078554(nameA, descPtr));
        } else {
            func_0202e060(lineA, func_ov027_020ba2a8(data_ov015_020812e0->textTable, 9), func_ov015_02078554(nameA, descPtr));
        }
        func_ov015_0207989c(2, 10, lineA);
        func_ov015_02077978(0x1a);
        break;
    case 26:
        if (func_ov015_02078918()) {
            func_ov015_02079880();
            item = func_ov027_020b90a4(data_ov015_020812e0->container, 0xe);
            func_ov027_020b94d8(data_ov015_020812e0->container, item, 2, 0xa5);
            SetContainerSubitem1Active_02078228(TRUE);
            func_ov015_02077978(4);
        }
        break;
    case 27:
        if (func_ov015_020781dc()) {
            if (!func_ov015_0207830c(&data_ov015_020812e0->opponentDesc, data_ov015_020812e0->opponentKind, &data_ov015_020812e0->playerDesc)) {
                data_ov015_020812e0->flags |= 0x200;
            }
            func_ov015_020779a4(0x25, 0x1c);
        }
        break;
    case 28:
        item = func_ov027_020b90a4(data_ov015_020812e0->container, 0xe);
        func_ov027_020b94b4(data_ov015_020812e0->container, item, 2, 0xa5);
        data_ov015_020812e0->delay = 4;
        func_ov015_020779a4(0x24, 0x1d);
        break;
    case 29:
        descPtr = &data_ov015_020812e0->opponentDesc;
        if (!(data_ov015_020812e0->flags & 0x200) || descPtr->kind == 9) {
            func_0202e060(lineB, func_ov027_020ba2a8((*(PanelScene *volatile *)&data_ov015_020812e0)->textTable, 8), func_ov015_02078554(nameB, descPtr));
        } else {
            func_0202e060(lineB, func_ov027_020ba2a8(data_ov015_020812e0->textTable, 9), func_ov015_02078554(nameB, descPtr));
        }
        func_ov015_0207989c(2, 10, lineB);
        func_ov015_02077978(0x1e);
        break;
    case 30:
        if (func_ov015_02078918()) {
            func_ov015_02079880();
            item = func_ov027_020b90a4(data_ov015_020812e0->container, 0xe);
            func_ov027_020b94d8(data_ov015_020812e0->container, item, 2, 0xa5);
            SetContainerSubitem1Active_02078228(TRUE);
            func_ov015_02077978(4);
        }
        break;
    case 31:
        item = func_ov027_020b90a4(data_ov015_020812e0->container, 1);
        if (item != NULL) {
            func_0204f24c(data_ov015_020812e0->records, item->recordIndex, 0);
        }
        func_ov015_02077978(0x20);
        break;
    case 32:
        SetContainerSubitem1Active_02078228(FALSE);
        func_ov015_02079648(3, 7, func_ov027_020ba2a8(data_ov015_020812e0->textTable, 4));
        func_ov027_020b9874(data_ov015_020812e0->container, 1);
        func_ov027_020b984c(data_ov015_020812e0->container, 1);
        item = func_ov027_020b90a4(data_ov015_020812e0->container, 0x10);
        func_ov027_020b9580(data_ov015_020812e0->container, item, 1);
        item = func_ov027_020b90a4(data_ov015_020812e0->container, 0x11);
        func_ov027_020b9580(data_ov015_020812e0->container, item, 1);
        item = func_ov027_020b90a4(data_ov015_020812e0->container, 0x11);
        func_ov027_020b96e4(data_ov015_020812e0->container, item);
        func_ov015_02077978(0x21);
        break;
    case 33:
        if (IsButtonBPressed_020632c8()) {
            PlaySoundEffect_0204d924(2, 2);
            func_ov015_02077978(0x23);
        }
        break;
    case 34:
        result = FALSE;
        func_ov015_02077978(0x29);
        goto close_menu;
    case 35:
        SetContainerSubitem1Active_02078228(TRUE);
        func_ov015_02077978(4);
    close_menu:
        func_ov015_02079870();
        func_ov027_020b9874(data_ov015_020812e0->container, 1);
        func_ov027_020b984c(data_ov015_020812e0->container, 1);
        item = func_ov027_020b90a4(data_ov015_020812e0->container, 0x10);
        func_ov027_020b9580(data_ov015_020812e0->container, item, 0);
        item = func_ov027_020b90a4(data_ov015_020812e0->container, 0x11);
        func_ov027_020b9580(data_ov015_020812e0->container, item, 0);
        break;
    case 36:
        if (data_ov015_020812e0->delay != 0) {
            data_ov015_020812e0->delay--;
        } else {
            func_ov015_020779c4();
            data_ov015_020812e0->delay = 0;
        }
        break;
    case 37:
    {
        u16 mask;
        int k;
        mask = 0;
        if (data_ov015_020812e0->nextState == 0x18) {
            mask = 2;
        } else if (data_ov015_020812e0->nextState == 0x1c) {
            mask = 4;
        }
        if (mask != 0) {
            for (k = 0; k < data_ov015_020812e0->panelCount; k++) {
                if (mask & data_ov015_020812e0->slots[k].flags) {
                    data_ov015_020812e0->slots[k].recordIndex = func_0204f0b4(data_ov015_020812e0->records, 0, 0);
                    func_0204f24c(data_ov015_020812e0->records, data_ov015_020812e0->slots[k].recordIndex, 0xb);
                    func_0204f178(data_ov015_020812e0->records, data_ov015_020812e0->slots[k].recordIndex, 0x65);
                    Slot_SetMode2Bit_0204f480(data_ov015_020812e0->records, data_ov015_020812e0->slots[k].recordIndex, 1);
                    SlotTable_SetEntryPriority_0204f468(data_ov015_020812e0->records, data_ov015_020812e0->slots[k].recordIndex, 0);
                    SetSceneRecordValue_020785f8(data_ov015_020812e0->slots[k].recordIndex,
                                                 func_0204f160(data_ov015_020812e0->records, data_ov015_020812e0->slots[k].recordSource));
                }
            }
        }
    }
        PlaySoundEffect_0204d924(2, 9);
        plane = (REG_DISPCNT_SUB & 0x1f00) >> 8;
        REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | ((plane | 4) << 8);
        data_ov015_020812e0->blendA = 0;
        data_ov015_020812e0->blendB = 0x10;
        G2x_SetBlendAlpha_02006850((unsigned int *)0x04001050, 4, 0x10, data_ov015_020812e0->blendA, data_ov015_020812e0->blendB);
        func_ov015_02077978(0x26);
    case 38:
        data_ov015_020812e0->blendA++;
        REG_BLDALPHA_SUB = (u16)(data_ov015_020812e0->blendA | (data_ov015_020812e0->blendB << 8));
        if (data_ov015_020812e0->blendA == 10) {
            func_ov015_02077978(0x27);
        }
        break;
    case 39:
        data_ov015_020812e0->timer++;
        if (data_ov015_020812e0->timer >= 8) {
            data_ov015_020812e0->timer = 0;
            func_ov015_02077978(0x28);
        }
        break;
    case 40:
        data_ov015_020812e0->blendA--;
        REG_BLDALPHA_SUB = (u16)(data_ov015_020812e0->blendA | (data_ov015_020812e0->blendB << 8));
        if (data_ov015_020812e0->blendA == 0) {
            for (slot = 0; slot < data_ov015_020812e0->panelCount; slot++) {
                if (data_ov015_020812e0->slots[slot].recordIndex >= 0) {
                    func_0204f0c0(data_ov015_020812e0->records, data_ov015_020812e0->slots[slot].recordIndex);
                    data_ov015_020812e0->slots[slot].recordIndex = -1;
                }
            }
            G2x_SetBlendAlpha_02006850((unsigned int *)0x04001050, 0, 0, 0, 0);
            ClearSubBg2Screen_02078f34();
            func_ov015_020779c4();
        }
        break;
    case 41:
        break;
    }
    item = func_ov027_020b90a4(data_ov015_020812e0->container, 2);
    if (item != NULL) {
        SlotTable_SetEntryPair_0204f35c(data_ov015_020812e0->records, item->recordIndex, data_ov015_020812e0->scaleX, data_ov015_020812e0->scaleY);
    }
    item = func_ov027_020b90a4(data_ov015_020812e0->container, 4);
    if (item != NULL) {
        SlotTable_SetEntryPair_0204f35c(data_ov015_020812e0->records, item->recordIndex, data_ov015_020812e0->scaleX, data_ov015_020812e0->scaleY);
    }
    func_ov027_020b96a0(data_ov015_020812e0->container, func_ov027_020b90a4(data_ov015_020812e0->container, 2), data_ov015_020812e0->filledCount);
    func_ov027_020b96a0(data_ov015_020812e0->container, func_ov027_020b90a4(data_ov015_020812e0->container, 4),
                        data_ov015_020812e0->filledCount - data_ov015_020812e0->openedCount);
    return result;
}
