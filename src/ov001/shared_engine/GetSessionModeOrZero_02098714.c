#include "nitro/types.h"

extern BOOL Session_Exists_02063a24(void);
extern s32 func_ov001_02063a38(void);

s32 GetSessionModeOrZero_02098714(void)
{
    if (Session_Exists_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}
