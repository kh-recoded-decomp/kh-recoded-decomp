#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SceneObjectDef {
    u8 pad_00[0x7d];
    u8 type;
} SceneObjectDef;

typedef struct SceneObject SceneObject;

struct SceneObject {
    u32 unk_00;
    SceneObject *next;
    SceneObjectDef *def;
};

extern SceneObject *func_ov001_0207f08c(void);
extern BOOL SceneObject_IsPointWithinOneUnit_02081a88(SceneObject *object, const VecFx32 *point);

BOOL IsPointNearPortal_02064e2c(const VecFx32 *point)
{
    SceneObject *object;

    for (object = func_ov001_0207f08c(); object != NULL; object = object->next) {
        if (object->def->type == 2 && SceneObject_IsPointWithinOneUnit_02081a88(object, point)) {
            return TRUE;
        }
    }
    return FALSE;
}
