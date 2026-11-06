#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *gActiveSubModeState;

extern int GetCameraManagerWork(void);
extern int Ov042Camera_GetState(void);
extern int Ov043Camera_GetState(void);
extern int GetPanelCameraState(void);

int GetActiveSubModeCameraWork(void)
{
    switch (gActiveSubModeState->mode) {
    case 0:
        return GetCameraManagerWork();
    case 1:
        return Ov042Camera_GetState();
    case 2:
        return Ov043Camera_GetState();
    case 3:
        return GetPanelCameraState();
    }
    return 0;
}
