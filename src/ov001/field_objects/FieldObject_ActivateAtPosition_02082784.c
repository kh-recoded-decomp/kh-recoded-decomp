#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject FieldObject;

extern void FieldObject_SetPhaseMode_02082714(FieldObject *object, int mode);
extern void FieldObject_PlaceActor_02082330(FieldObject *object, const VecFx32 *position);

void FieldObject_ActivateAtPosition_02082784(FieldObject *object, const VecFx32 *position)
{
    FieldObject_SetPhaseMode_02082714(object, 1);
    FieldObject_PlaceActor_02082330(object, position);
}
