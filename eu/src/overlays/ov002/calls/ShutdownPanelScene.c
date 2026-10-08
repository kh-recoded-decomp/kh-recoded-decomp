#include "nitro/types.h"

typedef struct FontResource {
    u8 pad_00[8];
    void *buffer;
} FontResource;

typedef struct TextLayer {
    u8 pad_00[0x34];
} TextLayer;

typedef struct MessageFile {
    void *file;
    u8 pad_04[8];
} MessageFile;

typedef struct PanelState {
    u8 pad_00[4];
    void *unk_04;
    u8 pad_08[0xa];
    u8 keyRepeat[0x1e];
    FontResource fonts[2];
    TextLayer layers[4];
    MessageFile messages[2];
} PanelState;

extern PanelState *data_ov002_0206c460;
extern u8 sOv002_WXCVB_0206c35c[];
extern char OVERLAY_27_ID[];

extern void TP_RequestAutoSamplingStopAsync(void);
extern void TP_WaitBusy(u32 mask);
extern u32 TP_CheckError(u32 mask);
extern BOOL ReleaseRecordSlot(s32 slot);
extern void PXI_Init_0202a64c(void *handle);
extern void FreePointerIfSet(void **ptr);
extern BOOL DestroyFndObjectList(TextLayer *layer);
extern BOOL FreeResourceBufferAndProbeHeap(FontResource *resource);
extern void NotifyBothOrOne(u32 a, void *b, int index);
extern void func_02029fac(int processor, int overlayId);
extern void FSi_DefaultStepDoneB(void *keyRepeat);
extern void ReleaseRecordManager(void);

void ShutdownPanelScene(void)
{
    TP_RequestAutoSamplingStopAsync();
    TP_WaitBusy(4);
    TP_CheckError(4);
    ReleaseRecordSlot(9);
    ReleaseRecordSlot(0xb);
    PXI_Init_0202a64c(data_ov002_0206c460->unk_04);
    FreePointerIfSet(&data_ov002_0206c460->messages[0].file);
    FreePointerIfSet(&data_ov002_0206c460->messages[1].file);
    DestroyFndObjectList(&data_ov002_0206c460->layers[0]);
    DestroyFndObjectList(&data_ov002_0206c460->layers[1]);
    DestroyFndObjectList(&data_ov002_0206c460->layers[2]);
    DestroyFndObjectList(&data_ov002_0206c460->layers[3]);
    FreeResourceBufferAndProbeHeap(&data_ov002_0206c460->fonts[0]);
    FreeResourceBufferAndProbeHeap(&data_ov002_0206c460->fonts[1]);
    NotifyBothOrOne(1, sOv002_WXCVB_0206c35c, 0);
    func_02029fac(0, (int)OVERLAY_27_ID);
    FSi_DefaultStepDoneB(data_ov002_0206c460->keyRepeat);
    ReleaseRecordManager();
}
