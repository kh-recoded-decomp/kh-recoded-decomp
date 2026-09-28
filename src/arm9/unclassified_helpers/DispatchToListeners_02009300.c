#include "nitro/types.h"

typedef void (*ListenerFunc)(u32 context, u32 arg1, u32 arg2);

extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern u32 data_02057500;
extern void *_data_02057500;

void DispatchToListeners_02009300(u32 arg1, u32 arg2) {
    u32 state;
    void **headCell;
    void **node;

    state = func_02004938();
    headCell = (void **)&data_02057500;
    node = (void **)_data_02057500;
    while (node != 0) {
        if (((u32 *)node)[2] != 0) {
            ((ListenerFunc)((u32 *)node)[2])(((u32 *)node)[1], arg1, arg2);
        }
        if (*headCell == (void *)node) {
            headCell = (void **)*headCell;
        }
        node = (void **)*headCell;
    }
    func_0200494c(state);
}
