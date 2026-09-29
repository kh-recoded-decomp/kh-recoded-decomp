#include "nitro/types.h"

extern s32 func_ov001_02063a38(void);
extern void *func_ov030_020bb354(void);
extern void *GetSubStruct1C_020bbfe0(void);

static inline BOOL IsGameMode(s32 mode)
{
    return func_ov001_02063a38() == mode;
}

void *GetModeContext_02036cd8(void)
{
    if (IsGameMode(4)) {
        return func_ov030_020bb354();
    }
    if (IsGameMode(7)) {
        return GetSubStruct1C_020bbfe0();
    }
    return NULL;
}
