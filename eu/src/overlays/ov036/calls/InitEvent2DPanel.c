#include "src/overlays/ov036/Event2DPanel.h"

#define GetCurrentTaskWork GetRunningTaskWork
#define InitPcmChannel AllocateScriptVmBuffer
#define CreateTask CreateTaskObject
#define LoadOverlaySync LoadOverlayAfterGeometryTransfer
#define UnloadOverlaySync UnloadOverlayAfterGeometryTransfer

typedef void (*ProtectionCallback)(void);
typedef u32 (*ProtectionCallbackRunner)(ProtectionCallback callback);
typedef int (*ProtectionDetector)(ProtectionCallbackRunner runner, ProtectionCallback callback, void *userData);

extern void *gTextWindowControllerTaskClass[5];
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
    gEvent2DPanelManager.work = GetCurrentTaskWork();
    InitPcmChannel(gEvent2DPanelManager.work->channels[0], 0x8000, 13);
    InitPcmChannel(gEvent2DPanelManager.work->channels[1], 0x10000, 13);
    gEvent2DPanelManager.work->value00 = args->value01;
    gEvent2DPanelManager.work->value02 = args->value02;
    gEvent2DPanelManager.work->value04 = args->value04;
    gEvent2DPanelManager.work->flags = 3;
    gEvent2DPanelManager.work->pxiHandle = CreateTask(gTextWindowControllerTaskClass, NULL);
    InitPanelDisplay();
    ClearStageManagerFlags31IfActive();
    gEvent2DPanelManager.work->backgroundArchive = Msg_OpenContainerAndReadHeader(
        sOv036_Ev2DBgP2_020c3718, 13, FALSE);
    gEvent2DPanelManager.work->characterArchive = Msg_OpenContainerAndReadHeader(
        sOv036_Ev2DChtexP2_020c3724, 13, FALSE);
    gEvent2DPanelManager.work->objectArchive = Msg_OpenContainerAndReadHeader(
        sOv036_Ev2DObjP2_020c3734, 13, FALSE);
    gEvent2DPanelManager.work->layers = NNSi_FndAllocFromDefaultHeap(2 * sizeof(Event2DScreenLayer));
    gEvent2DPanelManager.work->slots = NNSi_FndAllocFromDefaultHeap(8 * sizeof(Event2DPanelSlot));
    gEvent2DPanelManager.work->actors = NNSi_FndAllocFromDefaultHeap(5 * sizeof(Event2DPanelActor));
    ResetSlotScene();
    LoadDefaultProjectionValues(gEvent2DPanelManager.work->projection);
    gEvent2DPanelManager.work->projection[3] = 0;
    gEvent2DPanelManager.work->projection[4] = 300 << 12;
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
    gEvent2DPanelManager.work->state = 0;
    return RunPanelStateMachine;
}
