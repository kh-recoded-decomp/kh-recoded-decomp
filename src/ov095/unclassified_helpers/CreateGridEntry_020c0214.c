#include "nitro/types.h"

typedef struct {
    int spriteId;
    int x;
    int y;
    int visible;
    int mode2;
} GridEntryDesc;

typedef struct {
    int spriteIndex;
    int x;
    int y;
    int width;
    int height;
} GridEntry;

typedef struct {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} SpriteBounds;

typedef struct {
    u8 pad[0x180];
    u8 layers[2][0x6434];
} GridWork;

extern GridEntry *GetGridEntry_020c045c(int layer, int index, GridWork *work);
extern int func_0204f0b4(void *base, int spriteId, int arg);
extern void func_0204f204(void *base, int index, int arg);
extern int func_0204f2c0(void *base, int index);
extern void Slot_SetMode2Bit_0204f480(void *base, int index, int value);
extern void func_0204f378(void *base, int index, int value);
extern void SetGridEntryPosition_020c02fc(int layer, int index, int x, int y, GridWork *work);
extern SpriteBounds *GetGridEntrySpriteData_020c0400(int layer, int index, GridWork *work);

void CreateGridEntry_020c0214(int layer, int index, GridEntryDesc *desc, GridWork *work) {
    u8 *layerBase = work->layers[layer];
    GridEntry *entry = GetGridEntry_020c045c(layer, index, work);
    int sprite;
    SpriteBounds *bounds;

    sprite = func_0204f0b4(layerBase, desc->spriteId, 0);
    func_0204f204(layerBase, sprite, 0);
    func_0204f2c0(layerBase, sprite);
    Slot_SetMode2Bit_0204f480(layerBase, sprite, desc->mode2);
    func_0204f378(layerBase, sprite, desc->visible);
    entry->spriteIndex = sprite;
    entry->x = desc->x;
    entry->y = desc->y;
    SetGridEntryPosition_020c02fc(layer, index, desc->x, desc->y, work);
    bounds = GetGridEntrySpriteData_020c0400(layer, index, work);
    entry->width = bounds->left - bounds->right + 1;
    entry->height = bounds->top - bounds->bottom + 1;
}