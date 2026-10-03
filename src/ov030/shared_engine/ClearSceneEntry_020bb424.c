#include "nitro/types.h"

typedef struct {
    u16 id;
    u8 pad_02[0x4e];
} SceneEntry;

typedef struct {
    u8 pad_00[0x34];
    SceneEntry *entries;
} SceneState;

extern SceneState *data_ov030_020bd000;

extern void func_ov042_020be49c(int mode);

void ClearSceneEntry_020bb424(int index) {
    data_ov030_020bd000->entries[index].id = 0;
    func_ov042_020be49c(1);
}
