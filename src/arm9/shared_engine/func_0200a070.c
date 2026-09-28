#include "nitro/types.h"

typedef int (*StateCallback)(void);

typedef struct {
    s32 counter;
    u32 flag;
    StateCallback callback;
} EngineState;

extern EngineState data_020578e0;
extern void DispatchToListeners_02009300(u32 arg1, u32 arg2);
extern void func_0200a0d0(void);
extern void RunResetCallbackAndIdle_02004cf0(void);

void func_0200a070(int param1, u32 code, int param3, int param4) {
    int result;

    if ((code & 0x3f) == 0x11) {
        if (data_020578e0.flag == 0) {
            result = 1;
            data_020578e0.flag = 1;
            DispatchToListeners_02009300(1, 0);
            if (data_020578e0.callback != 0) {
                result = data_020578e0.callback();
            }
            if (result != 0) {
                func_0200a0d0();
            }
        }
    } else if ((code & 0x3f) == 2) {
        data_020578e0.counter = data_020578e0.counter + 1;
        data_020578e0.flag = 0;
        DispatchToListeners_02009300(2, 0);
    } else {
        RunResetCallbackAndIdle_02004cf0();
    }
}
