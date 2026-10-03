#include "nitro/types.h"

typedef struct {
    u8 data[0x134];
} SceneModel;

typedef struct {
    u8 enabled;
    u8 pad_001[0x30 - 0x1];
    s32 phase;
    s32 counter;
    void *buffer;
    u8 pad_03c[0x154 - 0x3c];
    s32 (*maskCallback)(s32 value);
    u8 pad_158[0x2a8 - 0x158];
    SceneModel models[3];
    u8 pad_644[0x798 - 0x644];
    u8 cameraPath[4];
} SceneModelBlock;

extern SceneModelBlock data_ov058_020d8a24;
extern u8 data_ov058_020d8a60[];
extern const char data_ov058_020d89e0[];
extern const char data_ov058_020d89f4[];
extern const char data_ov058_020d8a04[];
extern SceneModel data_ov058_020d8b98;
extern SceneModel data_ov058_020d9068;

extern void InitAnimatedModel_020ac864(void *model, const char *source, int slot);
extern s32 ToBoolMask_020d7e1c(s32 value);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void LoadArchiveEffectSlot_020d7510(SceneModel *slot, u32 fileIndex);
extern void CameraPath_Load_020c2ec0(void *path, const char *file);
extern void LoadManagerSpriteSlots_0206dbb4(void);

void LoadSceneModelResources_020d7e30(void)
{
    SceneModelBlock *block = &data_ov058_020d8a24;
    int i = 0;

    block->enabled = 0;
    block->phase = 0;
    block->counter = 0;
    InitAnimatedModel_020ac864(data_ov058_020d8a60, data_ov058_020d89e0, 0);
    block->maskCallback = ToBoolMask_020d7e1c;
    block->buffer = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov058_020d89f4, 6, FALSE);
    LoadArchiveEffectSlot_020d7510(&data_ov058_020d8b98, 2);
    LoadArchiveEffectSlot_020d7510(&data_ov058_020d9068, 4);
    for (; i < 3; i++) {
        LoadArchiveEffectSlot_020d7510(&block->models[i], 3);
    }
    CameraPath_Load_020c2ec0(block->cameraPath, data_ov058_020d8a04);
    LoadManagerSpriteSlots_0206dbb4();
}
