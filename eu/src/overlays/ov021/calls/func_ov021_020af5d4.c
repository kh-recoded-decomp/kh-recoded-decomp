#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56c0;

extern int Camera_GetActiveController(void);
extern int Camera_GetGoalPosition(void);
extern int Ov043Camera_GetActiveController(void);
extern int Panel_GetActiveController(void);

int func_ov021_020af5d4(void)
{
    switch (data_ov021_020b56c0->mode) {
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
