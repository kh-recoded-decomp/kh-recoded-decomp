#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *gActiveSubModeState;

extern int Camera_GetActiveController(void);
extern int Camera_GetGoalPosition(void);
extern int Ov043Camera_GetActiveController(void);
extern int Panel_GetActiveController(void);

int GetActiveCameraCullingOrigin(void)
{
    switch (gActiveSubModeState->mode) {
    case 0:
        return Camera_GetActiveController();
    case 1:
        return Camera_GetGoalPosition();
    case 2:
        return Ov043Camera_GetActiveController();
    case 3:
        return Panel_GetActiveController();
    }
    return 0;
}
