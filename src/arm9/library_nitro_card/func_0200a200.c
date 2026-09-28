#include "nitro/types.h"

extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern void OS_WakeupThread(void *queue);
extern int func_0200a1d8(u32 priority);

void func_0200a200(u32 *node, u32 value) {
    u32 *found;
    u32 *cur;
    u32 *prevCell;
    u32 state;
    int hasHigher;
    int owner;
    u32 priority;

    state = func_02004938();
    owner = node[2];
    if (owner != 0) {
        cur = *(u32 **)(owner + 8);
        prevCell = (u32 *)(owner + 8);
        while (found = cur, found != 0) {
            if (found == node) {
                *prevCell = *node;
                break;
            }
            prevCell = found;
            cur = (u32 *)*found;
        }
        *node = 0;
    }
    priority = (u32)node[3] >> 8 & 0xff;
    hasHigher = func_0200a1d8(priority);
    if ((hasHigher == 0) && (owner != 0)) {
        *(u32 *)(owner + 0x18) = priority;
        *(u32 *)(owner + 0x1c) = value;
    }
    node[5] = value;
    node[3] = node[3] & 0xffffff30;
    OS_WakeupThread(node + 6);
    func_0200494c(state);
}
