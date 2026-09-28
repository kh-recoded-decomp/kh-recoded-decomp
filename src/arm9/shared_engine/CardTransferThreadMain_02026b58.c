#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x2c0];
    u32 src;
    s32 length;
    u32 dst;
    int result;
} CardThreadBlock;

typedef struct {
    u8 pad_00[2];
    u16 resourceId;
    u8 pad_04[0x10];
    int threadResult;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern void *CARD_UnlockBackup_020091ac(int id);
extern void CardUnlockAfterKeyShare_020091b8(int id);
extern BOOL CARDi_RequestStreamCommand_02009a0c(u32 src, u32 dst, u32 length, void *callback, void *arg,
                                                BOOL async, s32 requestType, s32 requestRetry, s32 requestMode);
extern int func_02009128(void);
extern void OS_RescheduleThread_02002bb4(void);

void CardTransferThreadMain_02026b58(CardThreadBlock *block)
{
    u32 src = block->src;
    s32 remaining = block->length;
    u32 dst = block->dst;
    s32 chunk;

    do {
        chunk = 0x80;
        if (remaining <= 0x80) {
            chunk = remaining;
        }
        CARD_UnlockBackup_020091ac(g_cardThreadState_0205fe00.resourceId);
        if (CARDi_RequestStreamCommand_02009a0c(src, dst, chunk, NULL, NULL, FALSE, 6, 1, 0) == 0) {
            block->result = g_cardThreadState_0205fe00.threadResult = func_02009128();
            CardUnlockAfterKeyShare_020091b8(g_cardThreadState_0205fe00.resourceId);
            return;
        }
        CardUnlockAfterKeyShare_020091b8(g_cardThreadState_0205fe00.resourceId);
        src += chunk;
        dst += chunk;
        remaining -= chunk;
        OS_RescheduleThread_02002bb4();
    } while (remaining > 0);
    block->result = 0;
}
