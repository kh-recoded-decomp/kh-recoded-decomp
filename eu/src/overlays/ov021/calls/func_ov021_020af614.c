#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56c0;

extern int GetCameraManagerWork(void);
extern int Ov042Camera_GetState(void);
extern int Ov043Camera_GetState(void);
extern int func_ov044_020d0130(void);

int func_ov021_020af614(void)
{
    switch (data_ov021_020b56c0->mode) {
    case 0:
        return GetCameraManagerWork();
    case 1:
        return Ov042Camera_GetState();
    case 2:
        return Ov043Camera_GetState();
    case 3:
        return func_ov044_020d0130();
    }
    return 0;
}
