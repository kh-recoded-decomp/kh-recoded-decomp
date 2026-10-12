/* Adapted from the shared US main; EU supports all five western languages. */
#include "nitro/types.h"
#include "src/calls/MainLoopState.h"

typedef struct {
    u8 language;
    u8 favoriteColor;
    u8 birthdayMonth, birthdayDay;
    u16 nickname[10];
    u16 nicknameTerminator, nicknameLength;
    u16 comment[26];
    u16 commentTerminator, commentLength;
} OwnerInfo;

typedef struct {
    void *head;
    u8 pad_04[0x300];
} RootWork;

typedef struct {
    u8 frameSkipMode;
} ObjectSystem;

extern void InitEngine(void);
extern void InitializeArchiveBackend(void);
extern void func_0202abbc(void);
extern void OS_GetOwnerInfo(OwnerInfo *owner);
extern void func_0202b774(int language, int unused);
extern void func_02019cf4(RootWork *work);
extern u32 FS_TryLoadTable(void *table, u32 size);
extern void *NNSi_FndAllocFromExpHeapEx(u32 size, void *heap);
extern void func_0202a438(void);
extern void ResetCallbackTable(void);
extern void InitSoundSystem(void);
extern void *func_0202a45c(void *descriptor, void *userData);
extern void Pad_Sample(void);
extern void OS_WaitVBlankIntr(void);
extern u32 func_01ff80d4(void);
extern void NNS_GfdDoVramTransfer(void);
extern void G3X_Reset(void);
extern BOOL UpdatePanelActivation(void);
extern int InvokeCallbackSlot(int index);
extern void Obj_UpdateAll(int flags);
extern void SoundMgr_Update(void);
extern void NNS_GfdClearVramTransferManagerTask(void);
extern void GXi_FlushCommandList(void);
extern BOOL IsBusyFlagSet(void);
extern void GX_DispOff(void);
extern BOOL PM_SetLCDPower(BOOL on);
extern int func_02029f5c(void);
extern void SetBrightnessAndSyncMain(int brightness);
extern int func_02029f6c(void);
extern void SetSecondaryBrightness(int brightness);
extern void GX_DispOn(void);
extern BOOL IsBusyCounterZero(void);
extern void NNS_SndPlayerPauseAll(BOOL pause);
extern void PauseBgm(BOOL pause);
extern int PM_GoSleepMode(int mode, int wakeTrigger, int logic);
extern int PM_GetLCDPower(void);
extern void OS_Sleep(u32 milliseconds);

extern void *data_02060394;
extern struct SceneSystemClassDescriptor gSceneSystemClassDescriptor;
extern ObjectSystem gTaskManager;

#define LID_CLOSED ((*(volatile u16 *)0x02ffffa8 & 0x8000) >> 15)

enum OwnerLanguage {
    LANGUAGE_JAPANESE,
    LANGUAGE_ENGLISH,
    LANGUAGE_FRENCH,
    LANGUAGE_GERMAN,
    LANGUAGE_ITALIAN,
    LANGUAGE_SPANISH
};

int main(void)
{
    RootWork rootWork;
    OwnerInfo owner;
    BOOL wasActive;
    BOOL isActive;
    u32 frameTarget;
    int language;

    wasActive = FALSE;
    InitEngine();
    InitializeArchiveBackend();
    func_0202abbc();
    OS_GetOwnerInfo(&owner);
    language = owner.language;
    switch (language) {
    case LANGUAGE_ENGLISH:
    case LANGUAGE_FRENCH:
    case LANGUAGE_GERMAN:
    case LANGUAGE_ITALIAN:
    case LANGUAGE_SPANISH:
        func_0202b774(language, 0);
        break;
    default:
        func_0202b774(LANGUAGE_ENGLISH, 0);
        break;
    }
    func_02019cf4(&rootWork);
    gMainDisplayState.resourceTable = NNSi_FndAllocFromExpHeapEx(FS_TryLoadTable(NULL, 0), data_02060394);
    FS_TryLoadTable(gMainDisplayState.resourceTable, FS_TryLoadTable(NULL, 0));
    func_0202a438();
    ResetCallbackTable();
    InitSoundSystem();
    func_0202a45c(&gSceneSystemClassDescriptor, (void *)1);
    Pad_Sample();

    for (;;) {
        OS_WaitVBlankIntr();
        frameTarget = func_01ff80d4();
        NNS_GfdDoVramTransfer();
        Pad_Sample();
        G3X_Reset();
        isActive = UpdatePanelActivation();
        if (gPanelActive != FALSE && isActive == FALSE) {
            gPanelActive = FALSE;
            gPreviousPanelActive = FALSE;
        } else {
            gPanelActive = isActive;
        }
        if (wasActive != FALSE && isActive != FALSE) {
            InvokeCallbackSlot(1);
            frameTarget = func_01ff80d4();
        }
        if (wasActive == FALSE) {
            Obj_UpdateAll(0);
        }
        SoundMgr_Update();
        if (gPanelActive != FALSE && gPreviousPanelActive == FALSE) {
            NNS_GfdClearVramTransferManagerTask();
        }
        if (gTaskManager.frameSkipMode != 2) {
            frameTarget += (gTaskManager.frameSkipMode == 1) ? 2 : 1;
            while (func_01ff80d4() < frameTarget) {
                OS_WaitVBlankIntr();
                NNS_GfdDoVramTransfer();
            }
        }
        if (wasActive == FALSE) {
            GXi_FlushCommandList();
            *(volatile u32 *)0x04000540 = 1;
        }
        if (IsBusyFlagSet() != FALSE) {
            u8 displaysOff = gMainDisplayState.displaysOff;
            if (displaysOff == 0 && LID_CLOSED != 0) {
                GX_DispOff();
                PM_SetLCDPower(FALSE);
                gMainDisplayState.displaysOff = 1;
            } else if (displaysOff != 0 && LID_CLOSED == 0 && PM_SetLCDPower(TRUE) != FALSE) {
                gMainDisplayState.displaysOff = 0;
                SetBrightnessAndSyncMain(func_02029f5c());
                SetSecondaryBrightness(func_02029f6c());
                GX_DispOn();
            }
        } else if (IsBusyCounterZero() != FALSE && LID_CLOSED != 0) {
            if (wasActive == FALSE) {
                NNS_SndPlayerPauseAll(TRUE);
            } else {
                PauseBgm(TRUE);
            }
            PM_GoSleepMode(0xc, 0, 0);
            if (wasActive == FALSE) {
                NNS_SndPlayerPauseAll(FALSE);
            } else {
                PauseBgm(FALSE);
            }
            if (PM_GetLCDPower() == 0) {
                if (PM_SetLCDPower(TRUE) == FALSE) {
                    do {
                        OS_Sleep(100);
                    } while (PM_SetLCDPower(TRUE) == FALSE);
                }
                GX_DispOn();
                gMainDisplayState.displaysOff = 0;
            }
            SetBrightnessAndSyncMain(func_02029f5c());
            SetSecondaryBrightness(func_02029f6c());
        }
        gPreviousPanelActive = wasActive;
        wasActive = isActive;
    }
}
