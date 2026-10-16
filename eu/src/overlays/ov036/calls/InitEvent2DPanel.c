#include "src/overlays/ov036/Event2DPanel.h"

#define GetCurrentTaskWork NNSi_FndGetCurrentRootHeap
#define InitPcmChannel func_020257d8
#define CreateTask func_0202a45c
#define LoadOverlaySync func_02029f8c
#define UnloadOverlaySync func_02029fac

typedef void (*ProtectionCallback)(void);
typedef u32 (*ProtectionCallbackRunner)(ProtectionCallback callback);
typedef int (*ProtectionDetector)(ProtectionCallbackRunner runner, ProtectionCallback callback, void *userData);

extern void *data_ov036_020c392c[5];
extern const char sOv036_Ev2DBgP2_020c3718[];
extern const char sOv036_Ev2DChtexP2_020c3724[];
extern const char sOv036_Ev2DObjP2_020c3734[];
extern Event2DPanelWork *GetCurrentTaskWork(void);
extern void InitPcmChannel(void *channel, u32 bytes, u32 parameter);
extern void *CreateTask(void *descriptor, void *userData);
extern void InitPanelDisplay(void);
extern void ClearStageManagerFlags31IfActive(void);
extern void *Msg_OpenContainerAndReadHeader(const char *path, int kind, BOOL fromEnd);
extern void *NNSi_FndAllocFromDefaultHeap(u32 bytes);
extern void ResetSlotScene(void);
extern void LoadDefaultProjectionValues(u32 *projection);
extern char OVERLAY_104_ID[];
extern void LoadOverlaySync(int processor, int overlayId);
extern void UnloadOverlaySync(int processor, int overlayId);
extern u32 InvokeOptionalCallback_020ba400(ProtectionCallback callback);
extern int __DSProt_DetectDummy(ProtectionCallbackRunner runner, ProtectionCallback callback, void *userData);
extern int __DSProt_DetectNotEmulator(ProtectionCallbackRunner runner, ProtectionCallback callback, void *userData);
extern int __DSProt_DetectFlashcart(ProtectionCallbackRunner runner, ProtectionCallback callback, void *userData);
extern int RunPanelStateMachine(void);

static inline BOOL ProtectionCheckFailed(ProtectionDetector detector)
{
    ProtectionCallback callback = NULL;
    return detector(InvokeOptionalCallback_020ba400, callback, NULL) == ~(u32)callback;
}

Event2DPanelStateFn InitEvent2DPanel(Event2DPanelArgs *args)
{
    data_ov036_020c3940.work = GetCurrentTaskWork();
    InitPcmChannel(data_ov036_020c3940.work->channels[0], 0x8000, 13);
    InitPcmChannel(data_ov036_020c3940.work->channels[1], 0x10000, 13);
    data_ov036_020c3940.work->value00 = args->value01;
    data_ov036_020c3940.work->value02 = args->value02;
    data_ov036_020c3940.work->value04 = args->value04;
    data_ov036_020c3940.work->flags = 3;
    data_ov036_020c3940.work->pxiHandle = CreateTask(data_ov036_020c392c, NULL);
    InitPanelDisplay();
    ClearStageManagerFlags31IfActive();
    data_ov036_020c3940.work->backgroundArchive = Msg_OpenContainerAndReadHeader(
        sOv036_Ev2DBgP2_020c3718, 13, FALSE);
    data_ov036_020c3940.work->characterArchive = Msg_OpenContainerAndReadHeader(
        sOv036_Ev2DChtexP2_020c3724, 13, FALSE);
    data_ov036_020c3940.work->objectArchive = Msg_OpenContainerAndReadHeader(
        sOv036_Ev2DObjP2_020c3734, 13, FALSE);
    data_ov036_020c3940.work->layers = NNSi_FndAllocFromDefaultHeap(2 * sizeof(Event2DScreenLayer));
    data_ov036_020c3940.work->slots = NNSi_FndAllocFromDefaultHeap(8 * sizeof(Event2DPanelSlot));
    data_ov036_020c3940.work->actors = NNSi_FndAllocFromDefaultHeap(5 * sizeof(Event2DPanelActor));
    ResetSlotScene();
    LoadDefaultProjectionValues(data_ov036_020c3940.work->projection);
    data_ov036_020c3940.work->projection[3] = 0;
    data_ov036_020c3940.work->projection[4] = 300 << 12;
    LoadOverlaySync(0, (int)OVERLAY_104_ID);
    BOOL failed = ProtectionCheckFailed(__DSProt_DetectDummy);
    if (failed) {
        NNSi_FndAllocFromDefaultHeap(0xc00);
    }
    if (!ProtectionCheckFailed(__DSProt_DetectNotEmulator) ||
        ProtectionCheckFailed(__DSProt_DetectFlashcart)) {
        NNSi_FndAllocFromDefaultHeap(0x100fc);
    }
    UnloadOverlaySync(0, (int)OVERLAY_104_ID);
    data_ov036_020c3940.work->state = 0;
    return RunPanelStateMachine;
}
