#include "nitro/types.h"

typedef struct FieldManagerHandle {
    u32 unk_00;
    void *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;

extern u32 func_ov001_0206ea08(int layer);
extern int UpdateWidgetLayerDefault_020b9df0(void *widget, int layer);

void UpdateFieldWidgetLayer_020736b4(int layer)
{
    if (func_ov001_0206ea08(layer) == 0) {
        UpdateWidgetLayerDefault_020b9df0(data_ov001_020a04a4.manager, layer);
    }
}
