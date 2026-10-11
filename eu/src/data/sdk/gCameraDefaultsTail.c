#include "nitro/types.h"
#include "nitro/fx.h"

/* The default target and position precede this block at 0x0205fe28 and
 * 0x0205fe34. ResetCameraToDefaults copies these exact vectors/matrix. */
typedef struct CameraDefaultsTail {
    VecFx32 up;
    MtxFx44 projection;
} CameraDefaultsTail;

typedef char CameraDefaultsTailMustBe76Bytes[
    sizeof(CameraDefaultsTail) == 76 ? 1 : -1];
typedef char CameraDefaultProjectionMustStartAt12Bytes[
    (u32)&((CameraDefaultsTail *)0)->projection == 12 ? 1 : -1];

CameraDefaultsTail gCameraDefaultsTail;
