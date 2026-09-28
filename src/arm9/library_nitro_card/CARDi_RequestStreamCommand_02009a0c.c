#include "nitro/types.h"

typedef struct CardCommon CardCommon;
typedef void (*CardTaskFunc)(CardCommon *common);
typedef void (*CardCallback)(void *arg);

struct CardCommon {
    u8 pad_00[0x4fc];
    u32 src;
    u32 dst;
    u32 length;
    u8 pad_508[0x510 - 0x508];
    s32 requestType;
    s32 requestRetry;
    s32 requestMode;
};

extern CardCommon data_02056fe0;
extern void func_020099d4(u32 accessMask, CardCallback callback, void *arg);
extern BOOL CARDi_ExecuteOldTypeTask_02009344(CardTaskFunc task, BOOL async);
extern void CARDi_RequestStreamCommandCore_020095e0(CardCommon *common);

BOOL CARDi_RequestStreamCommand_02009a0c(u32 src, u32 dst, u32 length, CardCallback callback, void *arg,
                                         BOOL async, s32 requestType, s32 requestRetry, s32 requestMode)
{
    func_020099d4(requestMode == 0 ? 1 : 2, callback, arg);
    data_02056fe0.src = src;
    data_02056fe0.dst = dst;
    data_02056fe0.length = length;
    data_02056fe0.requestType = requestType;
    data_02056fe0.requestRetry = requestRetry;
    data_02056fe0.requestMode = requestMode;
    return CARDi_ExecuteOldTypeTask_02009344(CARDi_RequestStreamCommandCore_020095e0, async);
}
