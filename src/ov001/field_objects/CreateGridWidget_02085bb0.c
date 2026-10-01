#include "nitro/types.h"

typedef void (*GridCallback)(void);

typedef struct GridObject {
    GridCallback onInit;
    GridCallback onDestroy;
    GridCallback onUpdate;
    GridCallback onDraw;
    GridCallback onEnter;
    GridCallback unused14;
    GridCallback onLeave;
    GridCallback handler1c;
    GridCallback onTouch;
    GridCallback onRelease;
    GridCallback onDrag;
    GridCallback onSelect;
    GridCallback onCancel;
    GridCallback handler34;
    GridCallback handler38;
    GridCallback onFinish;
    u8 pad_40[0xc];
    int target;
    int depth;
    u8 pad_54[0x10];
    u16 priority;
    u8 pad_66[0xa];
    int color;
    int offsetX;
    int offsetY;
    u8 layer;
    u8 slotCount;
    u8 pad_7e[4];
    u8 group;
    u8 pad_83;
    u8 state;
    s8 selection;
    s16 hoverId;
    int value;
    u8 pad_8c[4];
    u16 counter;
} GridObject;

extern GridObject *CreateByteGrid_0207f380(int headerSize, int width, int height);
extern void func_ov001_0207f0d0(void);
extern void func_ov001_0207f128(void);
extern void func_ov001_02084bcc(void);
extern void func_ov001_0207f1e8(void);
extern void func_ov001_02084d7c(void);
extern void func_ov001_02084d5c(void);
extern void func_ov001_02084da4(void);
extern void func_ov001_02084da8(void);
extern void func_ov001_02084dac(void);
extern void func_ov001_02084de0(void);
extern void func_ov001_02084de8(void);
extern void func_ov001_02085b68(void);

GridObject *CreateGridWidget_02085bb0(int height, int *value)
{
    GridObject *grid = CreateByteGrid_0207f380(0x94, 0xd0, height);

    grid->state = 0;
    grid->selection = -1;
    grid->depth = 0x10;
    grid->layer = 2;
    grid->color = 0x14cd;
    grid->offsetX = 0;
    grid->offsetY = 0;
    grid->priority = 0x7d;
    grid->group = 0xff;
    grid->target = -1;
    grid->onInit = func_ov001_0207f0d0;
    grid->onDestroy = func_ov001_0207f128;
    grid->onUpdate = func_ov001_02084bcc;
    grid->onDraw = func_ov001_0207f1e8;
    grid->onEnter = func_ov001_02084d7c;
    grid->onLeave = func_ov001_02084d5c;
    grid->handler1c = NULL;
    grid->onTouch = func_ov001_02084da4;
    grid->onDrag = func_ov001_02084da8;
    grid->onRelease = func_ov001_02084dac;
    grid->onSelect = func_ov001_02084de0;
    grid->handler38 = NULL;
    grid->onCancel = func_ov001_02084de8;
    grid->handler34 = NULL;
    grid->onFinish = func_ov001_02085b68;
    grid->slotCount = 10;
    grid->hoverId = -1;
    grid->counter = 0;
    grid->value = *value;
    return grid;
}
