#include "nitro/types.h"

extern void func_01ffb12c(int arg);
extern int QueryLinkTarget(void);
extern int func_ov001_020870e4(void);

typedef void (*Callback)(int);

void func_ov001_02086b14(int param1, int useCallback) {
    int obj = QueryLinkTarget();
    if (useCallback == 0 && func_ov001_020870e4() == 0) {
        Callback cb = *(Callback *)(*(int *)(obj + 4) + 0x38);
        if (cb != 0) {
            cb(obj);
            return;
        }
        func_01ffb12c(param1 + 0x14);
    }
}
