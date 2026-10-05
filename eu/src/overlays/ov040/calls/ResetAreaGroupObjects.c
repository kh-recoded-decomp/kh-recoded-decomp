#include "nitro/types.h"

typedef struct AreaObject AreaObject;

typedef struct AreaObjectVtbl {
    u8 pad_00[0x30];
    BOOL (*isBusy)(AreaObject *object);
} AreaObjectVtbl;

struct AreaObject {
    u8 pad_00[4];
    AreaObjectVtbl *vtbl;
};

typedef struct AreaGroup {
    u8 pad_00[5];
    u8 count;
    u8 pad_06[0x12];
    u16 *objectIds;
} AreaGroup;

typedef struct AreaContext {
    u8 pad_00[0x43];
    s8 layer;
    u8 pad_44[0xc];
    AreaGroup *groups;
} AreaContext;

extern AreaContext *data_ov035_020bc4e0;
extern int func_ov035_020bae84(void);
extern u32 func_ov001_0208723c(int index);
extern AreaObject *func_ov001_02086384(u32 layer, u16 id);
extern void SendStateEvent10(AreaObject *object);

void ResetAreaGroupObjects(void)
{
    int groupIndex = func_ov035_020bae84();

    if (groupIndex >= 0) {
        AreaContext *context = data_ov035_020bc4e0;
        if (context->layer >= 0) {
            int i;
            AreaGroup *group = &context->groups[groupIndex];
            u32 layer = func_ov001_0208723c(context->layer);

            for (i = 0; i < group->count; i++) {
                AreaObject *object = func_ov001_02086384(layer, group->objectIds[i]);
                BOOL busy;

                if (object->vtbl->isBusy != NULL) {
                    busy = object->vtbl->isBusy(object);
                } else {
                    busy = FALSE;
                }
                if (!busy) {
                    SendStateEvent10(object);
                }
            }
        }
    }
}
