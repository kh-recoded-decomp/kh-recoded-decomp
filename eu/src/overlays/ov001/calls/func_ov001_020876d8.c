#include "nitro/types.h"

extern void BeginStageEntries(int arg);
extern int data_ov001_0209f2e8;

void func_ov001_020876d8(int arg) {
    if (data_ov001_0209f2e8 != -1 && arg != 0) {
        BeginStageEntries(arg);
    }
}
