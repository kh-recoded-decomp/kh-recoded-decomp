#include "nitro/types.h"

#define reg_OS_IME (*(vu16 *)0x04000208)

typedef struct {
    u8 data[0x1C];
} TickTween;

typedef struct {
    u8 pad_000[0x1C];
    u8 records[0x420];
    void *savedBgScreen;
    void *savedBg2Char;
    void *savedBgPalette;
    u8 pad_448[0x38];
    u32 isSliding : 1;
    u32 unk_480_1 : 3;
    u32 isPaused : 1;
    u32 unk_480_5 : 4;
    u32 showSlotRecords : 1;
    u8 pad_484[0xD0];
    TickTween tickerTween;
    u8 pad_570[0x6C];
    TickTween slideTween;
    void *slotRecords[3];
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;

extern u64 func_02003fd4(void);
extern BOOL func_ov001_02072040(void);
extern void setStopwatchHeld_02052648(TickTween *tween, int hold);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *record);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void *G2_GetBG2CharPtr_02007120(void);
extern void func_ov001_02077b90(int enable, int arg1);
extern void func_ov001_0207a89c(int arg0);

static inline u16 DisableIme(void)
{
    u16 prev = reg_OS_IME;
    reg_OS_IME = 0;
    return prev;
}

static inline u16 EnableIme(void)
{
    u16 prev = reg_OS_IME;
    reg_OS_IME = 1;
    return prev;
}

static inline void CopyBlock(const void *src, void *dst, u32 size)
{
    func_01ff878c(src, dst, size);
}

void SuspendFieldForPause_02071270(void)
{
    FieldManager *manager = data_ov001_020a04a4.manager;
    BOOL overridden;
    u16 savedIme;
    int i;

    func_02003fd4();
    overridden = func_ov001_02072040();
    setStopwatchHeld_02052648(&manager->tickerTween, 1);
    setStopwatchHeld_02052648(&manager->slideTween, 1);
    if (manager->showSlotRecords) {
        InvokeCallback40_020b8268(manager->records, FindActiveRecordById_020b8184(manager->records, 0x52));
        for (i = 0; i < 3; i++) {
            manager->slotRecords[i] = NULL;
        }
    }
    savedIme = DisableIme();
    manager->savedBgScreen = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x5C00, -0x20);
    CopyBlock((void *)0x06000000, manager->savedBgScreen, 0x5C00);
    manager->savedBg2Char = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x1000, -0x20);
    CopyBlock(G2_GetBG2CharPtr_02007120(), manager->savedBg2Char, 0x1000);
    manager->savedBgPalette = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x200, -0x20);
    CopyBlock((void *)0x05000000, manager->savedBgPalette, 0x200);
    if (savedIme) {
        EnableIme();
    }
    func_ov001_02077b90(1, overridden == FALSE);
    func_ov001_0207a89c(1);
}
