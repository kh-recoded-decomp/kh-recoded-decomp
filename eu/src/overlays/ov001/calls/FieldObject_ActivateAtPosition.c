#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject FieldObject;

extern void FieldObject_SetPhaseMode(FieldObject *object, int mode);
extern void FieldObject_PlaceActor(FieldObject *object, const VecFx32 *position);

void FieldObject_ActivateAtPosition(FieldObject *object, const VecFx32 *position)
{
    FieldObject_SetPhaseMode(object, 1);
    FieldObject_PlaceActor(object, position);
}
