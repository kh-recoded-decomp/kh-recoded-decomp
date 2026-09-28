#include "nitro/types.h"

typedef struct TextureParams {
    u32 imageParam;
    u32 paletteParam;
} TextureParams;

typedef struct PzTextureHost {
    u8 pad_00[4];
    TextureParams textures[7];
} PzTextureHost;

extern char data_ov001_0209e9f4[];
extern PzTextureHost *data_ov001_020a0464;
extern void *RetainOrInitializeSharedRecord_0202c80c(char *path, int heapId);
extern void func_0202c690(int useDefaultHooks);
extern void *func_0202c940(void *slot, void *textureHeader, int flag);
extern int func_0202d3c8(void *resource, int recordIndex);
extern void *func_0202d3e0(void *resource, int recordIndex, int entryIndex);
extern int func_0202fd00(TextureParams *params, void *texture, int reload);
extern int ReleaseSharedRecordSlot_0202c8a8(void *slot);

void LoadPzTextureParams_02066488(void)
{
    void *slot;
    void *resource;
    int textureCount;
    int entryIndex;

    slot = RetainOrInitializeSharedRecord_0202c80c(data_ov001_0209e9f4, 5);
    func_0202c690(0);
    resource = func_0202c940(slot, NULL, 1);
    func_0202c690(1);
    textureCount = func_0202d3c8(resource, 7);
    for (entryIndex = 0; entryIndex < textureCount; entryIndex++) {
        func_0202fd00(&data_ov001_020a0464->textures[entryIndex], func_0202d3e0(resource, 7, entryIndex), 0);
    }
    ReleaseSharedRecordSlot_0202c8a8(slot);
}
