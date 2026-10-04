#include "nitro/types.h"

typedef struct {
    u8 pad[0x180];
    u8 layers[2][0x6434];
} GridWork;

extern int *GetGridEntry_020c045c(int layer, int index, GridWork *work);
extern void func_0204f378(void *base, int index, int value);

void SetGridEntryVisible_020c01d8(int layer, int index, int visible, GridWork *work) {
    int *entry = GetGridEntry_020c045c(layer, index, work);
    func_0204f378(work->layers[layer], *entry, visible);
}