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

extern PanelState *g_panelState_0206c460;
extern u8 data_ov002_0206c35c[];
extern char OVERLAY_27_ID_0000001b[];

extern void TP_RequestAutoSamplingStopAsync_0200fe84(void);
extern void TP_WaitBusy_0201018c(u32 mask);
extern u32 TP_CheckError_0201019c(u32 mask);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void func_0202a638(void *handle);
extern void FreePointerIfSet_020ba294(void **ptr);
extern BOOL DestroyFndObjectList_020014f0(TextLayer *layer);
extern BOOL FreeResourceBufferAndProbeHeap_02001474(FontResource *resource);
extern void NotifyBothOrOne_02001154(u32 a, void *b, int index);
extern void func_02029f98(int processor, int overlayId);
extern void func_0204f5d8(void *keyRepeat);
extern void func_02051cdc(void);

void ShutdownPanelScene_02061854(void)
{
    TP_RequestAutoSamplingStopAsync_0200fe84();
    TP_WaitBusy_0201018c(4);
    TP_CheckError_0201019c(4);
    ReleaseRecordSlot_02051dfc(9);
    ReleaseRecordSlot_02051dfc(0xb);
    func_0202a638(g_panelState_0206c460->unk_04);
    FreePointerIfSet_020ba294(&g_panelState_0206c460->messages[0].file);
    FreePointerIfSet_020ba294(&g_panelState_0206c460->messages[1].file);
    DestroyFndObjectList_020014f0(&g_panelState_0206c460->layers[0]);
    DestroyFndObjectList_020014f0(&g_panelState_0206c460->layers[1]);
    DestroyFndObjectList_020014f0(&g_panelState_0206c460->layers[2]);
    DestroyFndObjectList_020014f0(&g_panelState_0206c460->layers[3]);
    FreeResourceBufferAndProbeHeap_02001474(&g_panelState_0206c460->fonts[0]);
    FreeResourceBufferAndProbeHeap_02001474(&g_panelState_0206c460->fonts[1]);
    NotifyBothOrOne_02001154(1, data_ov002_0206c35c, 0);
    func_02029f98(0, (int)OVERLAY_27_ID_0000001b);
    func_0204f5d8(g_panelState_0206c460->keyRepeat);
    func_02051cdc();
}
