#include "nitro/types.h"

extern void BeginStageEntries(int arg);
extern int g_stageEventsState;

void func_ov001_020876d8(int arg) {
    if (g_stageEventsState != -1 && arg != 0) {
        BeginStageEntries(arg);
    }
}
