#include "nitro/types.h"

typedef struct SubModeLaunchArgs {
    s32 mode;
    void **heap;
    void *arg;
} SubModeLaunchArgs;

extern void StartSubMode_020af260(void *arg, void **heap, s32 mode);
extern BOOL RunSubModeUpdate_020af364(void);

u32 BeginSubModeTask_020af248(SubModeLaunchArgs *arguments)
{
    StartSubMode_020af260(arguments->arg, arguments->heap, arguments->mode);
    return (u32)RunSubModeUpdate_020af364;
}
