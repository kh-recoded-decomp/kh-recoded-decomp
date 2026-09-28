#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    int threadResult;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern BOOL CARDi_RequestStreamCommand_02009a0c(u32 src, u32 dst, u32 length, void *callback, void *arg,
                                                BOOL async, s32 requestType, s32 requestRetry, s32 requestMode);
extern int func_02009128(void);

int ReadCardBackupSync_02026b00(u32 src, u32 dst, u32 length)
{
    CARDi_RequestStreamCommand_02009a0c(src, dst, length, NULL, NULL, FALSE, 6, 1, 0);
    return g_cardThreadState_0205fe00.threadResult = func_02009128();
}
