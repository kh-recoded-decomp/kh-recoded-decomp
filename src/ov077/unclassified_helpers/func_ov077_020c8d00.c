#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nnsys/g2d.h"

#define ARCHIVE_FILE_ID(handle, index) ((((u32)(handle) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct ObjManagerConfig {
    u32 cellFileId;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
} ObjManagerConfig;

typedef struct BgGraphicsData {
    NNSG2dScreenData *screen;
    NNSG2dCharacterData *character;
    NNSG2dPaletteData *palette;
} BgGraphicsData;

typedef struct ElementPos {
    fx32 x;
    fx32 y;
} ElementPos;

typedef struct IconSlot {
    u8 data[0xc];
} IconSlot;

typedef struct MenuPanel {
    u8 pad_00000[4];
    s32 state;
    u8 pad_00008[0x8];
    int buffer10;
    int buffer14;
    void *container;
    int recordIndex;
    u16 unk_20;
    u8 pad_00022[0x12];
    u8 unk_34[0x63c];
    IconSlot icons[11];
    u8 model[0x4690];
    u8 cursor[0xc];
    s32 cursorActive;
    u8 pad_04D94[0x14];
    u16 cursorX;
    u16 cursorY;
    u8 pad_04DAC[0xb0];
    void *messages;
    u8 pad_04E60[0x8];
    u8 charBuffer[0x2400];
    NNSG2dCharCanvas charCanvas;
    NNSG2dTextCanvas textCanvas;
    u16 screen[0x680];
    void *unk_7F90;
    u8 pad_07F94[0x8];
    u8 unk_7F9C[0x9c64];
    NNSG2dCharacterData *charData;
    u8 pad_11C04[0x23c];
    void *elements[7];
    u8 pad_11E5C[0x4c];
    void *messageEntries[3];
    u8 pad_11EB4[0x4];
    int unk_11EB8;
} MenuPanel;

extern const ObjManagerConfig data_ov076_020ca150;
/* Matrix message path follows this wide format string. */
extern const char data_ov076_020ca304[];
extern char data_ov076_020ca328[];
extern char data_ov076_020ca33c[];
extern MenuPanel *data_ov076_020ca38c;

extern void *func_ov039_020bc1bc(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void func_ov076_020c9dd0(void *object);
extern void QueueSoundCommandForArc_0204d670(u32 seqArcNo);
extern int func_0204d8b8(int arg0, int arg1);
extern void G2D_InitializeLinearCanvas_02017a2c(NNSG2dCharCanvas *pCC, void *charBase, int areaWidth, int areaHeight,
                                               NNSG2dCharaColorMode colorMode);
extern NNSG2dFont *func_ov039_020bc994(void);
extern void FillBackgroundTileRectangle_02017adc(u16 *dst, int width, int height, int x, int y, int mapW, int tile,
                                                 int palette);
extern void func_ov027_020ba25c(void *target, const char *path, int compressed);
extern void *func_ov027_020ba2a8(void *messages, int index);
extern void *func_ov039_020bca00(void);
extern int func_0202cc6c(const char *path, u32 kind, u32 fromTop);
extern void InitObjManagerAndMark_020b9060(void *container, ObjManagerConfig *config);
extern void func_ov027_020b9078(void *container, u32 fileId);
extern void func_ov027_020b8f98(void *container, u32 fileId, int count);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b95e4(void *container, void *element);
extern void func_ov027_020b96a0(void *container, void *element, u16 mode);
extern void func_ov027_020b91c8(void *container, void *element, ElementPos *pos, int flag);
extern void func_ov034_020bde84(void *cursor, void *container, int elementId, int arg3, int arg4, int arg5, int arg6,
                                int arg7, int arg8);
extern void *func_0202c478(u32 fileId, u32 heapId);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_01ff8ad8(const void *src, void *dst, u32 len);
extern void func_ov076_020c81d8(void *object, NNSG2dCharacterData *charData);
extern void func_0202c690(int mode);
extern void func_ov076_020c66cc(int buffer, int index, IconSlot *slot);
extern void InitPanelModel_020c9c78(void *model, u32 resourceId, u32 trackMask);
extern void func_ov076_020c6c48(MenuPanel *panel, int mode);

static inline void InitTextCanvas(NNSG2dTextCanvas *pTxn, NNSG2dCharCanvas *pCC, NNSG2dFont *pFont, int hSpace, int vSpace)
{
    pTxn->pCanvas = pCC;
    pTxn->pFont = pFont;
    pTxn->hSpace = hSpace;
    pTxn->vSpace = vSpace;
}

void func_ov077_020c8d00(MenuPanel *panel, int recordIndex, int param)
{
    BgGraphicsData bgData;
    ObjManagerConfig config = data_ov076_020ca150;
    ElementPos pos;
    void *container;
    void *element;
    void *archive;
    NNSG2dCharacterData *charData;

    container = func_ov039_020bc1bc();
    AcquireRecordSlot_02051d3c(0, 0);
    AcquireRecordSlot_02051d3c(1, 0);
    func_ov076_020c9dd0(panel->unk_34);
    QueueSoundCommandForArc_0204d670(1);
    func_0204d8b8(0x1a, 10);
    G2D_InitializeLinearCanvas_02017a2c(&panel->charCanvas, panel->charBuffer, 0x10, 0x12, NNS_G2D_CHARA_COLORMODE_16);
    InitTextCanvas(&panel->textCanvas, &panel->charCanvas, func_ov039_020bc994(), 0, 1);
    FillBackgroundTileRectangle_02017adc(panel->screen, 0x10, 0x12, 0xd, 3, 0x20, 10, 0xf);
    func_ov027_020ba25c(&panel->messages, data_ov076_020ca304 + 8, 0);
    panel->messageEntries[0] = func_ov027_020ba2a8(&panel->messages, 0x32);
    panel->messageEntries[1] = func_ov027_020ba2a8(&panel->messages, 0x33);
    panel->messageEntries[2] = func_ov027_020ba2a8(&panel->messages, 0);
    panel->unk_7F90 = func_ov039_020bca00();
    panel->buffer10 = func_0202cc6c(data_ov076_020ca328, 0xe, 0);
    panel->buffer14 = func_0202cc6c(data_ov076_020ca33c, 0xe, 0);

    config.cellFileId = ARCHIVE_FILE_ID(panel->buffer10, 0);
    InitObjManagerAndMark_020b9060(container, &config);
    func_ov027_020b9078(container, ARCHIVE_FILE_ID(panel->buffer14, 0));
    func_ov027_020b8f98(container, ARCHIVE_FILE_ID(panel->buffer10, 1), 0x3b);
    element = func_ov027_020b90a4(container, 2);
    func_ov027_020b95e4(container, element);
    func_ov027_020b96a0(container, element, recordIndex);
    func_ov027_020b95e4(container, func_ov027_020b90a4(container, 0x1b));
    panel->elements[0] = func_ov027_020b90a4(container, 5);
    panel->elements[1] = func_ov027_020b90a4(container, 0);
    panel->elements[2] = func_ov027_020b90a4(container, 1);
    panel->elements[3] = func_ov027_020b90a4(container, 0x23);
    panel->elements[4] = func_ov027_020b90a4(container, 0x24);
    panel->elements[5] = func_ov027_020b90a4(container, 0x25);
    panel->elements[6] = func_ov027_020b90a4(container, 0x26);
    pos.x = (u16)recordIndex * 0xe000;
    func_ov027_020b91c8(container, func_ov027_020b90a4(container, 4), &pos, 4);

    panel->container = container;
    panel->recordIndex = recordIndex;
    panel->state = 0;
    panel->unk_20 = 1;
    func_ov034_020bde84(panel->cursor, container, 0x1d, 8, 0x10, 0, 0x10, 1, 0);

    archive = func_0202c478(ARCHIVE_FILE_ID(panel->buffer10, 2), 0xf);
    GetBgDataFromArchive_0202b554(&bgData, archive, 0, recordIndex, -1);
    charData = NNSi_FndAllocFromDefaultHeap_0202a178(bgData.character->szByte + sizeof(NNSG2dCharacterData));
    panel->charData = charData;
    *charData = *bgData.character;
    panel->charData->pRawData = panel->charData + 1;
    func_01ff8ad8(bgData.character->pRawData, panel->charData->pRawData, bgData.character->szByte);
    func_ov076_020c81d8(panel->unk_7F9C, panel->charData);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);

    panel->cursorX = 0x58;
    panel->cursorY = 0xf8;
    panel->cursorActive = 1;
    panel->unk_11EB8 = param;

    func_0202c690(0);
    func_ov076_020c66cc(panel->buffer10, 3, &panel->icons[0]);
    func_ov076_020c66cc(panel->buffer10, 4, &panel->icons[1]);
    func_ov076_020c66cc(panel->buffer14, 1, &panel->icons[2]);
    func_ov076_020c66cc(panel->buffer10, 5, &panel->icons[3]);
    func_ov076_020c66cc(panel->buffer14, 2, &panel->icons[4]);
    func_ov076_020c66cc(panel->buffer10, 6, &panel->icons[5]);
    func_ov076_020c66cc(panel->buffer10, 7, &panel->icons[6]);
    func_ov076_020c66cc(panel->buffer10, 8, &panel->icons[7]);
    func_ov076_020c66cc(panel->buffer10, 9, &panel->icons[8]);
    func_ov076_020c66cc(panel->buffer10, 10, &panel->icons[9]);
    func_ov076_020c66cc(panel->buffer10, 11, &panel->icons[10]);
    func_0202c690(1);

    InitPanelModel_020c9c78(panel->model, ARCHIVE_FILE_ID(panel->buffer10, 0xc), 0x15);
    func_ov076_020c6c48(panel, 0);
    data_ov076_020ca38c = panel;
}
