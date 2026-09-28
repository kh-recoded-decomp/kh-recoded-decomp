#include "nitro/types.h"

extern void func_01ffb12c(int arg);
extern int func_ov001_02080a78(void);
extern int func_ov001_020870bc(void);

typedef void (*Callback)(int);

void func_ov001_02086aec(int param1, int useCallback) {
    int obj = func_ov001_02080a78();
    if (useCallback == 0 && func_ov001_020870bc() == 0) {
        Callback cb = *(Callback *)(*(int *)(obj + 4) + 0x38);
        if (cb != 0) {
            cb(obj);
            return;
        }
        func_01ffb12c(param1 + 0x14);
    }
}
