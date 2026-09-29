#include "nitro/types.h"

typedef void (*CardDoneSetter)(void);
typedef u32 (*CallbackInvoker)(CardDoneSetter setter);

typedef struct {
    u8 pad_00[2];
    u16 resourceId;
    u8 pad_04[4];
    void *buffer;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern void **g_mainHeap_02060394;
extern u8 g_saveCheckOverlayId_00000068[];
extern void func_02029f78(int processor, int overlayId);
extern void func_02029f98(int processor, int overlayId);
extern void func_ov104_020d1f18(CallbackInvoker invoker, CardDoneSetter setter, int flags);
extern u32 func_ov104_020d1edc(CallbackInvoker invoker, CardDoneSetter setter, int flags);
extern u32 func_ov104_020d1fcc(CallbackInvoker invoker, CardDoneSetter setter, int flags);
extern u32 InvokeOptionalCallback_02026ac8(CardDoneSetter callback);
extern void SetCardThreadDoneCallback_02026ae0(void);
extern void SetCardThreadDoneCallback_02026af0(void);
extern s32 func_020023a0(void);
extern void RunResetCallbackAndIdle_02004cf0(void);
extern void *AllocFromHeapOrDefaultEx_0202a210(u32 size, int align, void **heap);
extern void *CARD_UnlockBackup_020091ac(int id);
extern void CardUnlockAfterKeyShare_020091b8(int id);
extern BOOL func_02009a54(int backupType);
extern int func_02026ce0(void);
extern void InitSaveData_02026ee0(u32 mode);

int InitSaveSystem_02026dc0(void)
{
    int result = 0;
    BOOL verified;
    CardDoneSetter setter;

    if (g_cardThreadState_0205fe00.buffer != NULL) {
        return result;
    }
    func_02029f78(0, (int)g_saveCheckOverlayId_00000068);
    func_ov104_020d1f18(InvokeOptionalCallback_02026ac8, SetCardThreadDoneCallback_02026af0, 0);
    verified = func_ov104_020d1edc(InvokeOptionalCallback_02026ac8, SetCardThreadDoneCallback_02026ae0, 0) ==
               ~(u32)SetCardThreadDoneCallback_02026ae0;
    if (!verified) {
        setter = NULL;
        verified = func_ov104_020d1fcc(InvokeOptionalCallback_02026ac8, setter, 0) == ~(u32)setter;
        if (verified) {
            result = 0;
        }
        SetCardThreadDoneCallback_02026af0();
    }
    func_02029f98(0, (int)g_saveCheckOverlayId_00000068);
    g_cardThreadState_0205fe00.resourceId = func_020023a0();
    if (g_cardThreadState_0205fe00.resourceId == -3) {
        RunResetCallbackAndIdle_02004cf0();
    }
    g_cardThreadState_0205fe00.buffer = AllocFromHeapOrDefaultEx_0202a210(0x3c18, 0x20, g_mainHeap_02060394);
    CARD_UnlockBackup_020091ac(g_cardThreadState_0205fe00.resourceId);
    if (func_02009a54(0x1001) == 0) {
        result = 3;
    } else if (func_02026ce0() == 0) {
        result = 5;
    }
    CardUnlockAfterKeyShare_020091b8(g_cardThreadState_0205fe00.resourceId);
    InitSaveData_02026ee0(1);
    return result;
}
