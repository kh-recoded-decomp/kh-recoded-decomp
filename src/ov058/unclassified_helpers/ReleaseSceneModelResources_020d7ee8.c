#include "nitro/types.h"

typedef struct {
    u8 data[0x134];
} SceneModel;

typedef struct {
    u8 pad_000[0x38];
    void *buffer;
    u8 pad_03c[0x2a8 - 0x3c];
    SceneModel models[3];
    u8 pad_644[0x798 - 0x644];
    u8 cameraPath[4];
} SceneModelBlock;

extern u8 data_ov058_020d8a60[];
extern SceneModelBlock data_ov058_020d8a24;
extern SceneModel data_ov058_020d8b98;
extern SceneModel data_ov058_020d9068;

extern void TeardownBigObj_020ac8cc(void *obj);
extern void ReleaseRecordEntry_020d75e0(SceneModel *model);
extern void StopSeqArcOrDefault_0204d960(int seqArcNo, int unused1, int unused2);
extern void CameraPath_Free_020c2f90(void *path);
extern void ZeroHalfThenFree_0202cd78(void *buffer);

void ReleaseSceneModelResources_020d7ee8(void)
{
    SceneModelBlock *block = &data_ov058_020d8a24;
    int i;

    TeardownBigObj_020ac8cc(data_ov058_020d8a60);
    ReleaseRecordEntry_020d75e0(&data_ov058_020d8b98);
    ReleaseRecordEntry_020d75e0(&data_ov058_020d9068);
    for (i = 0; i < 3; i++) {
        ReleaseRecordEntry_020d75e0(&block->models[i]);
    }
    StopSeqArcOrDefault_0204d960(0xc2, 0, 0);
    CameraPath_Free_020c2f90(block->cameraPath);
    ZeroHalfThenFree_0202cd78(block->buffer);
}
