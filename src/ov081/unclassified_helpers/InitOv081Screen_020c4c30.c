#include "nitro/types.h"

#define ARCHIVE_FILE_ID(handle, index) ((((u32)(handle) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct StringTable {
    void *buffer;
    u32 count;
    u8 *entries;
} StringTable;

typedef struct ObjManagerConfig {
    u32 cellFileId;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
} ObjManagerConfig;

typedef struct Ov081State {
    u32 archive;
    u32 subArchive;
    StringTable stringsA;
    StringTable stringsB;
    u8 pad_20[0x63c6 - 0x20];
    s8 cursor;
    u8 pad_63c7;
    int page;
    u8 tween[0x18];
    u8 pad_63e4[4];
} Ov081State;

extern Ov081State *data_020c5d80;
extern const char data_020c5ce4[];
extern const char data_020c5cf8[];
extern const char data_020c5d10[];
extern const char data_020c5d28[];
extern const ObjManagerConfig data_020c5c44;
extern const ObjManagerConfig data_020c5c54;

extern void func_01ff88c4(void *dst, int value, u32 size);
extern int Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void LoadPackedFileView_020ba25c(StringTable *table, const char *path, int flags);
extern void *func_ov039_020bc1bc(void);
extern void *func_ov039_020bc1cc(void);
extern void InitObjManagerAndMark_020b9060(void *container, ObjManagerConfig *config);
extern void func_ov027_020b8f98(void *container, u32 fileId, int count);
extern void PXI_Init_020b9078(void *container, u32 fileId);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern void func_ov027_020b97b8(void *container, void *widget, int mode);
extern void func_02052514(void *tween, int a, int b, int c, int duration);
extern void func_0205255c(void *tween);
extern void LoadBitIndexTable_020c5160(Ov081State *state);
extern void func_ov081_020c4260(Ov081State *state);
extern void func_ov081_020c4e98(Ov081State *state);
extern void func_ov081_020c527c(Ov081State *state);

int InitOv081Screen_020c4c30(Ov081State *state)
{
    void *container;
    ObjManagerConfig config;
    ObjManagerConfig subConfig;

    func_01ff88c4(state, 0, sizeof(Ov081State));
    data_020c5d80 = state;
    *(vu16 *)0x04000304 = (u16)(*(vu16 *)0x04000304 & ~0x8000);
    state->archive = Msg_OpenContainerAndReadHeader_0202cc6c(data_020c5ce4, 0xe, FALSE);
    state->subArchive = Msg_OpenContainerAndReadHeader_0202cc6c(data_020c5cf8, 0xe, FALSE);
    LoadPackedFileView_020ba25c(&state->stringsA, data_020c5d10, 0);
    LoadPackedFileView_020ba25c(&state->stringsB, data_020c5d28, 0);

    container = func_ov039_020bc1bc();
    config = data_020c5c44;
    config.cellFileId = ARCHIVE_FILE_ID(state->archive, 2);
    InitObjManagerAndMark_020b9060(container, &config);
    func_ov027_020b8f98(container, ARCHIVE_FILE_ID(state->archive, 3), 3);
    func_ov027_020b97b8(container, FindWidgetById_020b90a4(container, 0), 2);

    container = func_ov039_020bc1cc();
    subConfig = data_020c5c54;
    subConfig.cellFileId = ARCHIVE_FILE_ID(state->archive, 4);
    InitObjManagerAndMark_020b9060(container, &subConfig);
    PXI_Init_020b9078(container, ARCHIVE_FILE_ID(state->subArchive, 0));
    func_ov027_020b8f98(container, ARCHIVE_FILE_ID(state->archive, 5), 0x15);

    func_02052514(state->tween, 0, 0, 0, 500);
    func_0205255c(state->tween);
    LoadBitIndexTable_020c5160(state);
    func_ov081_020c4260(state);
    func_ov081_020c4e98(state);
    state->cursor = 0;
    state->page = 0;
    func_ov081_020c527c(state);
    return 1;
}
