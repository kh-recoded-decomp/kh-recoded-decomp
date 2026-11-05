#include "nitro/types.h"

extern void BeginStageEntries(int arg);
extern int g_stageEventsState;

void BeginStageEntriesIfActive(int arg) {
    if (g_stageEventsState != -1 && arg != 0) {
        BeginStageEntries(arg);
    }
}
