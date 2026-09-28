#include "nitro/types.h"

typedef struct SignedBlob {
    s32 magic;
    u8 hash[0x14];
    u8 data[0x3760];
} SignedBlob;

typedef struct {
    u8 blockCounter;
    u8 slot;
    u8 pad_02[6];
    SignedBlob *buffer;
    void *payload;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern int func_02026c3c(void);
extern BOOL VerifySha1Signature_02026c9c(SignedBlob *blob);
extern void StartCardTransferThread_02026be0(void *src, void *dst, u32 length);
extern void DecrementBusyCounterIfPositive_02025494(void);

int PollCardThreadResult_02027060(void)
{
    int status;
    int *word;
    u32 i;
    int result;

    status = func_02026c3c();
    if (status < 0) {
        goto busy;
    }
    if (status != 0) {
        result = 3;
    } else {
        word = (int *)g_cardThreadState_0205fe00.buffer;
        for (i = 0; i < 8; i++) {
            if (*word++ != 0) {
                break;
            }
        }
        if (i == 8) {
            result = 2;
        } else if (VerifySha1Signature_02026c9c(g_cardThreadState_0205fe00.buffer) != 0) {
            result = 0;
            g_cardThreadState_0205fe00.payload = (u8 *)g_cardThreadState_0205fe00.buffer + 0x18;
        } else {
            g_cardThreadState_0205fe00.blockCounter = g_cardThreadState_0205fe00.blockCounter + 1;
            if (g_cardThreadState_0205fe00.blockCounter >= 2) {
                result = 4;
            } else {
                StartCardTransferThread_02026be0(
                    (void *)((g_cardThreadState_0205fe00.blockCounter + g_cardThreadState_0205fe00.slot * 2) * 0x3c18 + 0x20),
                    g_cardThreadState_0205fe00.buffer, 0x3c18);
                return 1;
            }
        }
    }
    goto tail;
busy:
    return 1;
tail:
    DecrementBusyCounterIfPositive_02025494();
    return result;
}
