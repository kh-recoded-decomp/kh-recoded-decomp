#include "nitro/types.h"

typedef struct Panel {
    u8 pad_0000[0x4c];
    s32 usedSlotCount;
    u8 pad_0050[0x6674 - 0x50];
    BOOL sessionFailed;
} Panel;

extern char OVERLAY_104_ID[];

extern BOOL IsSoundStreamActive(int stream);
extern void func_02029f8c(int processor, int overlayId);
extern void func_02029fac(int processor, int overlayId);
extern s32 __DSProt_DetectFlashcart(void *task, void *callback, int arg);
extern s32 __DSProt_DetectEmulator(void *task, void *callback, int arg);
extern s32 __DSProt_DetectNotDummy(void *task, void *callback, int arg);
extern u32 RunProtectionCallback(void (*callback)(void));
extern void DSProt_OnDetection(void);
extern void StartSceneAfterTitle(void);
extern int World_GetField4(void);
extern int func_ov000_0206364c(void);
extern void SetPanelState(Panel *panel, s32 state, u32 param1, u32 param2);
extern void ApplyPanelMenuFlags(Panel *panel, BOOL selectContinue);

/* Wait for the world session to load. Once it reports no session, wait for the
 * stream to stop and run the DS Protect checks; the not-dummy check's callback
 * continues the game. */
int WaitPanelWorldSession(Panel *panel)
{
    int result = -1;

    if (panel->sessionFailed) {
        if (!IsSoundStreamActive(1)) {
            BOOL detected;
            void *callback;

            func_02029f8c(0, (int)OVERLAY_104_ID);
            detected = __DSProt_DetectFlashcart(RunProtectionCallback, DSProt_OnDetection, 0) ==
                       ~(u32)DSProt_OnDetection;
            if (!detected) {
                callback = NULL;
                detected = __DSProt_DetectEmulator(RunProtectionCallback, callback, 0) == ~(u32)callback;
                if (detected) {
                    DSProt_OnDetection();
                } else {
                    detected = __DSProt_DetectNotDummy(RunProtectionCallback, StartSceneAfterTitle, 0) ==
                               ~(u32)StartSceneAfterTitle;
                    if (!detected) {
                        return -2;
                    }
                }
            }
            func_02029fac(0, (int)OVERLAY_104_ID);
            result = -2;
        }
    } else {
        switch (World_GetField4()) {
        case 1:
            SetPanelState(panel, 1, 0, 0x10);
            panel->usedSlotCount = func_ov000_0206364c();
            ApplyPanelMenuFlags(panel, FALSE);
            result = 6;
            break;
        case 2:
            panel->sessionFailed = TRUE;
            break;
        }
    }
    return result;
}
