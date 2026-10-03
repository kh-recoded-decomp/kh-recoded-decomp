#include "nitro/types.h"

typedef struct {
    u8 data[0x134];
} SceneModel;

typedef struct {
    u8 pad_000[0x2a8];
    SceneModel models[3];
} SceneModelBlock;

extern u8 data_ov058_020d8b98[];
extern u8 data_ov058_020d9068[];
extern SceneModelBlock data_ov058_020d8a24;

extern void func_ov058_020d7720(void *node);
extern void func_ov058_020d7980(void *node);
extern void ApplyModelPolygonId_020d78bc(SceneModel *object, int polygonBase);

void DrawSceneModels_020d8774(void)
{
    SceneModelBlock *block = &data_ov058_020d8a24;
    int i;

    func_ov058_020d7720(data_ov058_020d8b98);
    func_ov058_020d7980(data_ov058_020d9068);
    for (i = 0; i < 3; i++) {
        ApplyModelPolygonId_020d78bc(&block->models[i], i);
    }
}
