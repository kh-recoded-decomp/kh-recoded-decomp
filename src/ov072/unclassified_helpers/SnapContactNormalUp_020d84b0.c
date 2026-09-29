#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 distance;
    VecFx32 normal;
} ContactPlane;

extern BOOL Contact_IsFacingNormal_020349d8(void *contact, VecFx32 *normal);
extern void ContactPlane_SetNormal_0203f040(ContactPlane *plane, const VecFx32 *normal);
extern const VecFx32 data_ov072_020d9bbc;

BOOL SnapContactNormalUp_020d84b0(void *contact, ContactPlane *plane)
{
    if (!Contact_IsFacingNormal_020349d8(contact, &plane->normal)) {
        return FALSE;
    }
    if (plane->normal.y < 0x165) {
        return FALSE;
    }
    ContactPlane_SetNormal_0203f040(plane, &data_ov072_020d9bbc);
    return TRUE;
}
