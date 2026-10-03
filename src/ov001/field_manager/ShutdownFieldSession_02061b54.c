#include "nitro/types.h"

typedef struct {
    void *data;
    int size;
} SessionBuffer;

typedef struct {
    u8 pad_0000[8];
    void *heapB;
    u8 pad_000c[4];
    int overlayId;
    u8 pad_0014[4];
    s8 overlaySlot;
    u8 pad_0019[0x1f0c - 0x19];
    void *scratch;
    u8 pad_1f10[0x272c - 0x1f10];
    void *halfBuffer;
    u8 pad_2730[0xc];
    void *workBuffer;
    void *heapA;
    u8 pad_2744[0x27f2 - 0x2744];
    s8 entryCount;
    u8 pad_27f3;
    void **entries;
    u8 pad_27f8[0x283c - 0x27f8];
    SessionBuffer buffers[13];
} Session;

extern void *data_ov001_020a0460;
extern Session *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void ShutdownSessionOverlays_02062a54(void);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_02029f98(int processor, int overlayId);
extern int ZeroHalfThenFree_0202cd78(void *block);
extern void func_0202a638(void *heap);
extern void ShutdownPanelState_02028854(void);
extern void func_ov001_02066e18(void);
extern void func_ov001_02066454(void);
extern void DestroyFieldObjectManager_0207ed6c(void);
extern void func_ov001_02069214(void);
extern void ReleaseServiceInstance_020690ac(void);
extern void func_ov001_020685a4(void);
extern void ReleaseServiceInstance_02068e64(void);
extern void func_ov001_02069508(void);
extern void func_ov001_0206747c(void);
extern void DeferredDraw_Release_02036b20(void);
extern void func_02035774(void);
extern void func_ov001_02063c54(void);
extern void TP_RequestAutoSamplingStopAsync_0200fe84(void);
extern void TP_WaitBusy_0201018c(unsigned int mask);
extern int TP_CheckError_0201019c(int mask);
extern void ReleaseRecordManager_02051cdc(void);
extern void LoadSeqArcIfChanged_0204d5f0(int seqArcNo);
extern void func_02050a44(void);

void ShutdownFieldSession_02061b54(void)
{
    Session *session = NNSi_FndGetCurrentRootHeap_0202a764();
    int i;

    ShutdownSessionOverlays_02062a54();
    for (i = 0; i < 13; i++) {
        if (session->buffers[i].data != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(session->buffers[i].data);
        }
    }
    if (session->overlayId != -1) {
        func_02029f98(0, session->overlayId);
        session->overlayId = -1;
        session->overlaySlot = -1;
    }
    if (session->entries != NULL) {
        for (i = 0; i < session->entryCount; i++) {
            if (session->entries[i] != NULL) {
                NNSi_FndFreeFromDefaultHeap_0202a1c4(session->entries[i]);
            }
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(session->entries);
    }
    if (session->workBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(session->workBuffer);
    }
    if (session->halfBuffer != NULL) {
        ZeroHalfThenFree_0202cd78(session->halfBuffer);
    }
    func_0202a638(session->heapA);
    func_0202a638(session->heapB);
    ShutdownPanelState_02028854();
    func_ov001_02066e18();
    func_ov001_02066454();
    DestroyFieldObjectManager_0207ed6c();
    func_ov001_02069214();
    ReleaseServiceInstance_020690ac();
    func_ov001_020685a4();
    ReleaseServiceInstance_02068e64();
    func_ov001_02069508();
    func_ov001_0206747c();
    DeferredDraw_Release_02036b20();
    func_02035774();
    func_ov001_02063c54();
    TP_RequestAutoSamplingStopAsync_0200fe84();
    TP_WaitBusy_0201018c(4);
    TP_CheckError_0201019c(4);
    ReleaseRecordManager_02051cdc();
    LoadSeqArcIfChanged_0204d5f0(0);
    func_02050a44();
    if (session->scratch != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(session->scratch);
        session->scratch = NULL;
    }
    data_ov001_020a0460 = NULL;
}
