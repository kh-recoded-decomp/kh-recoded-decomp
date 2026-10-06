#include "nitro/types.h"

extern int FieldObject_UpdateFall(void);
extern int func_ov001_02063838(void);
extern int IsNearFirstEntity(int arg);
extern int ConfigureChannelSlot(int a, int b, int c);

int func_ov009_020a0ab0(int arg) {
    int result;

    FieldObject_UpdateFall();
    result = func_ov001_02063838();
    if ((result == 0) && (result = IsNearFirstEntity(arg), result != 0)) {
        ConfigureChannelSlot(0, 1, 0);
    }
    return 0;
}
