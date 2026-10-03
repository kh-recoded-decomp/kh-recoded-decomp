#include "nitro/types.h"

typedef struct ResultsWork {
    u8 pad_0000[0x10];
    u8 tagTracker[0x4c];
    u8 objects[0x647c];
    u8 iconLayer[0x20];
    int isActive;
    u8 pad_64fc[0x640];
    u8 messages[0xc];
    u8 font[0xc];
    u8 fontAlt[0xc];
    u8 text[0x68];
    u32 mode;
    u8 pad_6bcc[0x178];
    int badgeEntry;
    int rowEntries[6];
} ResultsWork;

typedef struct ResultsScreen {
    void *params;
    ResultsWork *work;
} ResultsScreen;

typedef struct TextFrame {
    u16 values[8];
} TextFrame;

typedef struct TagConfig {
    u32 values[5];
} TagConfig;

typedef struct ObjConfig {
    u32 fileId;
    u32 values[3];
} ObjConfig;

typedef struct PaletteData {
    u8 pad_00[8];
    u32 size;
    void *data;
} PaletteData;

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharacterData;

typedef struct BgGraphicsData {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

extern ResultsScreen g_resultsScreen_020c0f80;
extern char data_ov034_020c0e88[];
extern char data_ov034_020c0e98[];
extern char data_ov034_020c0eb0[];
extern char data_ov034_020c0ec8[];
extern char data_ov034_020c0edc[];
extern TextFrame data_ov034_020be8bc;
extern TagConfig data_ov034_020be8cc;
extern ObjConfig data_ov034_020be89c;
extern u8 data_ov034_020c0ef0[];

extern void EnterResultsTierMode_020bb290(u32 mode);
extern u32 Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void LoadPackedFileView_020ba25c(void *view, u32 fileId, BOOL fromTail);
extern int ZeroHalfThenFree_0202cd78(u32 container);
extern int func_02001458(void *font, char *path);
extern u16 *UpdateWidgetLayerDefault_020b9df0(void *layer, int id);
extern BOOL InitTextLayerAt_020014b0(void *text, int layer, u16 *screenBase, void *font, TextFrame *frame);
extern void MarkTileTableRowDirty_020b9e00(void *layer, int id);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void func_ov027_020b7d58(void *tracker, TagConfig *config);
extern void func_ov027_020b7e24(void *tracker, u32 fileId);
extern void *func_0202c48c(u32 fileId, u32 mode);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void func_02007250(void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern int InitializeResourceContainer_020b8bd4(void *container, void *params);
extern void InitObjManagerAndMark_020b9060(void *objects, ObjConfig *config);
extern void PXI_Init_020b9078(void *objects, u32 fileId);
extern void func_ov027_020b8f98(void *objects, u32 fileId, int count);
extern void SetAllElementObjectModes_020b97fc(void *objects, int mode);
extern void *func_ov027_020b90a4(void *objects, int id);
extern void func_ov027_020b97b8(void *objects, void *widget, int mode);
extern void SetWidgetRootDpadEnabled_020b9874(void *objects, BOOL enabled);
extern int func_ov034_020bde88(void *manager, int animation, int resource, int x, int y);
extern void func_ov027_020b9098(void *objects, void (*callback)(void));
extern void func_ov034_020bd110(void);
extern void InvokeForChannelOrBoth_0200110c(u32 arg0, void *arg1, void (*callback)(void), int channel);
extern void UpdateResultsFade_020bb094(void);

#define WORK (g_resultsScreen_020c0f80.work)
#define CONTAINER_BASE(container) ((((container) + 0x8000) & 0xfffffc) << 7)

void InitResultsScreen_020bb304(void)
{
    u32 container;
    u32 objContainer;
    u32 iconContainer;
    u32 base;
    void *archive;
    BgGraphicsData bg;
    TagConfig tagConfig;
    ObjConfig objConfig;
    TextFrame frame;
    int i;

    EnterResultsTierMode_020bb290(WORK->mode);
    container = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov034_020c0e88, 0xe, 0);
    LoadPackedFileView_020ba25c(WORK->messages, CONTAINER_BASE(container) | 0x80000007, 1);
    ZeroHalfThenFree_0202cd78(container);
    func_02001458(WORK->font, data_ov034_020c0e98);
    func_02001458(WORK->fontAlt, data_ov034_020c0eb0);
    frame = data_ov034_020be8bc;
    InitTextLayerAt_020014b0(WORK->text, 2, UpdateWidgetLayerDefault_020b9df0(WORK->iconLayer, 10), WORK->font, &frame);
    MarkTileTableRowDirty_020b9e00(WORK->iconLayer, 10);
    AcquireRecordSlot_02051d3c(0, 0);
    objContainer = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov034_020c0ec8, 0xe, 0);
    iconContainer = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov034_020c0edc, 0xe, 0);
    tagConfig = data_ov034_020be8cc;
    func_ov027_020b7d58(WORK->tagTracker, &tagConfig);
    base = CONTAINER_BASE(objContainer);
    func_ov027_020b7e24(WORK->tagTracker, base | 0x80000011);
    archive = func_0202c48c(base | 0x80000012, 0xe);
    GetBgDataFromArchive_0202b554(&bg, archive, -1, 0, 0);
    func_02007250(bg.palette->data, 0, bg.palette->size);
    GX_LoadBG3Char_02007b70(bg.character->data, 0, bg.character->size);
    if (archive != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    }
    objConfig = data_ov034_020be89c;
    objConfig.fileId = base | 0x80000015;
    InitializeResourceContainer_020b8bd4(WORK->objects, NULL);
    InitObjManagerAndMark_020b9060(WORK->objects, &objConfig);
    PXI_Init_020b9078(WORK->objects, CONTAINER_BASE(iconContainer) | 0x8000001a);
    func_ov027_020b8f98(WORK->objects, base | 0x80000016, 0x4a);
    SetAllElementObjectModes_020b97fc(WORK->objects, 1);
    func_ov027_020b97b8(WORK->objects, func_ov027_020b90a4(WORK->objects, 200), 0);
    SetWidgetRootDpadEnabled_020b9874(WORK->objects, TRUE);
    ZeroHalfThenFree_0202cd78(objContainer);
    ZeroHalfThenFree_0202cd78(iconContainer);
    WORK->badgeEntry = func_ov034_020bde88(WORK->objects, 1, 9, 0x80, 100);
    for (i = 0; i < 6; i++) {
        WORK->rowEntries[i] = func_ov034_020bde88(WORK->objects, 1, 0xc, 0xb8, i * 16 + 0x51);
    }
    func_ov027_020b9098(WORK->objects, func_ov034_020bd110);
    InvokeForChannelOrBoth_0200110c(1, data_ov034_020c0ef0, UpdateResultsFade_020bb094, 0);
    WORK->isActive = 1;
}
