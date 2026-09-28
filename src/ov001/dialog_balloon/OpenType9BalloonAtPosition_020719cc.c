#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int ProjectWorldPositionToScreen_02028c24(const VecFx32 *worldPos, int *screenX, int *screenY);
extern BOOL func_ov001_0207a504(int balloonType, int style, int arg2, int arg3, int screenX, int screenY,
                                void *message, void *options);

void OpenType9BalloonAtPosition_020719cc(const VecFx32 *worldPos, void *message)
{
    int screenX;
    int screenY;

    screenX = 0x7FFFFFFF;
    screenY = 0x7FFFFFFF;
    if (worldPos != NULL) {
        ProjectWorldPositionToScreen_02028c24(worldPos, &screenX, &screenY);
        if (screenX < 0 || screenX > 0xFF) {
            screenX = 0x7FFFFFFF;
        }
    }
    func_ov001_0207a504(9, 0, 0, 0, screenX, screenY, message, NULL);
}
