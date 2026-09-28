#include "nitro/types.h"

typedef struct {
    u8 bootMode;
    u8 pad_01[0x53];
} SharedSettings;

typedef struct {
    void *head;
    u8 pad_04[0x300];
} RootWork;

typedef struct {
    u8 displaysOff;
    u8 pad_01[3];
    void *resourceTable;
} DisplayPowerState;

typedef struct {
    u8 frameSkipMode;
} ObjectSystem;

extern void InitEngine_02029b54(void);
extern void InitializeArchiveBackend_0203a858(void);
extern void func_0202aba8(void);
extern void CopySharedSettings_02004ae4(SharedSettings *settings);
extern void func_0202b760(int mode, int unused);
extern void func_02019ce0(RootWork *work);
extern u32 FS_TryLoadTable_0200d510(void *table, u32 size);
extern void *NNSi_FndAllocFromExpHeapEx_0202a1e4(u32 size, void *heap);
extern void func_0202a424(void);
extern void ResetCallbackTable_020253f8(void);
extern void func_0204d050(void);
extern void *func_0202a448(void *descriptor, void *userData);
extern void func_0202abc8(void);
extern void OS_WaitVBlankIntr_020049d0(void);
extern u32 func_01ff80d4(void);
extern void func_02014008(void);
extern void func_020069d8(void);
extern BOOL func_020288a0(void);
extern int InvokeCallbackSlot_02025464(int index);
extern void Obj_UpdateAll_0202a644(int flags);
extern void func_0204d150(void);
extern void func_02013ff4(void);
extern void func_01ff80e4(void);
extern BOOL func_020254e8(void);
extern void GX_DispOff_02006640(void);
extern BOOL func_020109e4(BOOL on);
extern int func_02029f48(void);
extern void SetBrightnessAndSyncMain_02029e7c(int brightness);
extern int func_02029f58(void);
extern void SetSecondaryBrightness_02029ed0(int brightness);
extern void apply_pending_display_vram_mode_02006680(void);
extern BOOL IsBusyCounterZero_020254b8(void);
extern void func_0201d648(BOOL pause);
extern void func_0204d9e4(BOOL pause);
extern int func_02010690(int mode, int wakeTrigger, int logic);
extern int PM_GetLCDPower_02010a08(void);
extern void OS_Sleep_02002c78(u32 milliseconds);

extern void *g_mainHeap_02060394;
extern DisplayPowerState g_displayPower_020561c0;
extern u8 g_rootTaskClass_02055d8c[];
extern BOOL g_currentActive_0205fde4;
extern BOOL g_previousActive_0205fde0;
extern ObjectSystem g_objectSystem_020603c8;

#define LID_CLOSED ((*(volatile u16 *)0x02ffffa8 & 0x8000) >> 15)

int main(void)
{
    RootWork rootWork;
    SharedSettings settings;
    BOOL wasActive;
    BOOL isActive;
    u32 frameTarget;
    int mode;

    wasActive = FALSE;
    InitEngine_02029b54();
    InitializeArchiveBackend_0203a858();
    func_0202aba8();
    CopySharedSettings_02004ae4(&settings);
    mode = settings.bootMode;
    if (mode == 1 || mode == 2 || mode == 5) {
        func_0202b760(mode, 0);
    } else {
        func_0202b760(1, 0);
    }
    func_02019ce0(&rootWork);
    g_displayPower_020561c0.resourceTable = NNSi_FndAllocFromExpHeapEx_0202a1e4(FS_TryLoadTable_0200d510(NULL, 0), g_mainHeap_02060394);
    FS_TryLoadTable_0200d510(g_displayPower_020561c0.resourceTable, FS_TryLoadTable_0200d510(NULL, 0));
    func_0202a424();
    ResetCallbackTable_020253f8();
    func_0204d050();
    func_0202a448(g_rootTaskClass_02055d8c, (void *)1);
    func_0202abc8();

    for (;;) {
        OS_WaitVBlankIntr_020049d0();
        frameTarget = func_01ff80d4();
        func_02014008();
        func_0202abc8();
        func_020069d8();
        isActive = func_020288a0();
        if (g_currentActive_0205fde4 != FALSE && isActive == FALSE) {
            g_currentActive_0205fde4 = FALSE;
            g_previousActive_0205fde0 = FALSE;
        } else {
            g_currentActive_0205fde4 = isActive;
        }
        if (wasActive != FALSE && isActive != FALSE) {
            InvokeCallbackSlot_02025464(1);
            frameTarget = func_01ff80d4();
        }
        if (wasActive == FALSE) {
            Obj_UpdateAll_0202a644(0);
        }
        func_0204d150();
        if (g_currentActive_0205fde4 != FALSE && g_previousActive_0205fde0 == FALSE) {
            func_02013ff4();
        }
        if (g_objectSystem_020603c8.frameSkipMode != 2) {
            frameTarget += (g_objectSystem_020603c8.frameSkipMode == 1) ? 2 : 1;
            while (func_01ff80d4() < frameTarget) {
                OS_WaitVBlankIntr_020049d0();
                func_02014008();
            }
        }
        if (wasActive == FALSE) {
            func_01ff80e4();
            *(volatile u32 *)0x04000540 = 1;
        }
        if (func_020254e8() != FALSE) {
            u8 displaysOff = g_displayPower_020561c0.displaysOff;
            if (displaysOff == 0 && LID_CLOSED != 0) {
                GX_DispOff_02006640();
                func_020109e4(FALSE);
                g_displayPower_020561c0.displaysOff = 1;
            } else if (displaysOff != 0 && LID_CLOSED == 0 && func_020109e4(TRUE) != FALSE) {
                g_displayPower_020561c0.displaysOff = 0;
                SetBrightnessAndSyncMain_02029e7c(func_02029f48());
                SetSecondaryBrightness_02029ed0(func_02029f58());
                apply_pending_display_vram_mode_02006680();
            }
        } else if (IsBusyCounterZero_020254b8() != FALSE && LID_CLOSED != 0) {
            if (wasActive == FALSE) {
                func_0201d648(TRUE);
            } else {
                func_0204d9e4(TRUE);
            }
            func_02010690(0xc, 0, 0);
            if (wasActive == FALSE) {
                func_0201d648(FALSE);
            } else {
                func_0204d9e4(FALSE);
            }
            if (PM_GetLCDPower_02010a08() == 0) {
                if (func_020109e4(TRUE) == FALSE) {
                    do {
                        OS_Sleep_02002c78(100);
                    } while (func_020109e4(TRUE) == FALSE);
                }
                apply_pending_display_vram_mode_02006680();
                g_displayPower_020561c0.displaysOff = 0;
            }
            SetBrightnessAndSyncMain_02029e7c(func_02029f48());
            SetSecondaryBrightness_02029ed0(func_02029f58());
        }
        g_previousActive_0205fde0 = wasActive;
        wasActive = isActive;
    }
}
