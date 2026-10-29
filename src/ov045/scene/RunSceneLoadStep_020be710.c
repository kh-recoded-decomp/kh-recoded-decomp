#pragma opt_lifetimes off
#include "nitro/types.h"
#include "nnsys/g3d.h"

typedef struct Record {
    u16 recordId;
    u8 pad_02[2];
    s16 value;
} Record;

typedef struct RecordPool RecordPool;

typedef struct PoolConfig {
    u32 counts[5];
} PoolConfig;

typedef struct TextFrame {
    u16 values[8];
} TextFrame;

typedef struct TexEntry {
    u32 imageParam;
    u32 extraParam;
} TexEntry;

typedef struct PlttEntry {
    u16 offset;
    u16 flag;
} PlttEntry;

typedef struct TexLoad {
    u32 imageParam;
    u32 plttBase;
    u16 width;
    u16 height;
    NNSG3dResTex *tex;
    u32 remaining;
    u32 vramOffset;
    const void *source;
    BOOL isPalette;
    u16 state;
    u8 alpha : 5;
    void *file;
} TexLoad;

typedef struct SceneWork {
    u16 mode;
    u16 count;
    int id;
    u8 pad_08[8];
    s16 step;
    u16 timer;
    u8 pad_14[8];
    BOOL done;
    void *scene;
    void *header0;
    void *header1;
    void *file0;
    void *file1;
    RecordPool *tracker;
    union {
        u8 pool[0x4c];
        struct {
            Record *first[10];
            Record *second[10];
            Record *third[10];
            Record *fourth[10];
        } labels;
    } records;
    u8 pad_d8[0x17ac];
    u8 resultLayer[0x34];
    u8 resultSlot[0xc];
    void *resultFile;
    u8 pad_18c8[0xc0];
    u8 iconValue;
    Record *icons[12];
    u8 textLayer[0x48];
    void *header2;
    TexLoad texLoad;
} SceneWork;

typedef int (*SceneStep)(void);

extern SceneWork *data_ov045_020c0880;
extern char data_ov045_020c0838[];
extern char data_ov045_020c0848[];
extern char data_ov045_020c085c[];
extern PoolConfig data_ov045_020c0794;
extern PoolConfig data_ov045_020c07a8;
extern TextFrame data_ov045_020c0784;
extern TextFrame data_ov045_020c0774;
extern u32 (*data_02055c4c)(u32 size, BOOL is4x4comp, u32 opt);
extern u32 (*data_02055c54)(u32 size, BOOL is4pltt, u32 opt);

extern BOOL IsRecordIdFree_0202c38c(void *file);
extern void OpenMessageContainer_020be668(void **outHeader, void **outHandle, const char *name, u32 slot);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void *func_0202c364(u32 fileId, u32 param2);
extern RecordPool *GetSceneTagTracker_020711b0(void);
extern void LoadBg3Graphics_020be5e0(void *archive, int characterIndex, int paletteIndex, BOOL loadPalette,
                                     void *characterFile, u32 characterOffset);
extern Record *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void func_ov027_020b7d58(void *pool, PoolConfig *config);
extern void func_ov027_020b7e24(void *pool, u32 fileId);
extern void *GetFieldFont3_020711e0(void);
extern BOOL InitTextLayerAt_020014b0(void *layer, int index, u16 *screenBase, void *font, TextFrame *frame);
extern BOOL AcquireRecordManager_02051c80(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern NNSG3dResTex *FindTextureResourceBlock_0201ac70(void *file);
extern u32 GetTextureImageBytes_020188cc(NNSG3dResTex *tex);
extern u32 GetCompressedTextureBytes_020188e0(NNSG3dResTex *tex);
extern u32 GetPaletteBytes_02018964(NNSG3dResTex *tex);
extern void ReleaseTextureResourceKeys_020188f4(NNSG3dResTex *tex, u32 texKey, u32 tex4x4Key);
extern void func_02018978(NNSG3dResTex *tex, u32 plttKey);
extern BOOL StepTextureUpload_020c02dc(void *upload);
extern void OS_WaitVBlankIntr_020049d0(void);
extern void GX_BeginLoadTexPltt_020081e0(void);
extern void GX_LoadTexPltt_02008214(const void *src, u32 destSlotAddr, u32 size);
extern void GX_EndLoadTexPltt_02008284(void);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *memory);
extern void FinishTextureSlotLoad_020c0214(void *slot);
extern u16 GetByteCounterOrDefault_020291cc(int index);
extern void func_02029240(int id, int count);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern int RunIntroSequenceStep_020bfea0(void);
extern int UpdateResultFadeOut_020c0044(void);
extern int func_ov045_020bf3d0(void);
extern int RunNameRevealStep_020bfc30(void);

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_BG0CNT (*(vu16 *)0x04000008)
#define REG_BG1CNT (*(vu16 *)0x0400000a)
#define REG_BG2CNT (*(vu16 *)0x0400000c)
#define REG_BG3CNT (*(vu16 *)0x0400000e)

#define FILE_ID(header, slot) (0x80000000 | ((((u32)(header) + 0x8000) & 0xfffffc) << 7) | ((slot) & 0x1ff))

static inline void *GetResDataByIdx(const NNSG3dResDict *dict, u32 idx)
{
    const NNSG3dResDictEntryHeader *entries;

    if (dict != NULL && idx < dict->numEntry) {
        entries = (const NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)((u8 *)entries->data + entries->sizeUnit * idx);
    }
    return NULL;
}

static inline const NNSG3dResDictTexData *GetTexDataByIdx(const NNSG3dResTex *tex, u32 idx)
{
    if (tex != NULL) {
        return GetResDataByIdx(&tex->dict, idx);
    }
    return NULL;
}

static inline BOOL DictHasIndex(const NNSG3dResDict *dict, u32 idx)
{
    return idx < dict->numEntry;
}

/* Incoming register slot reused for the palette size. */
SceneStep RunSceneLoadStep_020be710(u32 plttSize)
{
    SceneWork *work = data_ov045_020c0880;
    u32 texKey;
    NNSG3dResTex *tex;
    u32 texSize;
    u32 tex4x4Size;
    u32 tex4x4Key;
    u32 plttKey;
    const NNSG3dResDictTexData *texData;
    const NNSG3dResDictPlttData *plttData;
    u32 plttKey6;
    u32 plttOffset;
    NNSG3dResTex *tex6;
    u32 texKey6;
    const NNSG3dResDict *dict;
    const NNSG3dResDictEntryHeader *entries;

    switch (work->step) {
    case 0: {
        const char *name;
        u32 slot;

        if (!IsRecordIdFree_0202c38c(work->file0)) {
            break;
        }
        if (work->mode == 3) {
            name = data_ov045_020c0838;
            slot = 0;
        } else {
            slot = 0x1b;
            name = data_ov045_020c0848;
            if (work->mode != 2) {
                slot = 0x1c;
            }
        }
        OpenMessageContainer_020be668(&work->header1, &work->file1, name, slot);
        work->step = 1;
        break;
    }
    case 1:
        if (!IsRecordIdFree_0202c38c(work->file1)) {
            break;
        }
        if (work->mode == 0) {
            int count = work->count;
            void *header;

            if (count >= 6) {
                count -= 2;
            } else if (count > 3) {
                count = 3;
            }
            if (count >= 6) {
                count -= 1;
            }
            if (count > 6) {
                count = 6;
            }
            header = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov045_020c085c, 0xe, FALSE);
            work->header2 = header;
            work->texLoad.file = func_0202c364(FILE_ID(header, count), 0x11);
            work->step = 2;
        } else if (work->mode == 3) {
            int id = work->id;
            int slot;

            if (id >= 0xd0 && id <= 0x10f) {
                slot = (id - 0xd0) / 5 + 1;
            } else {
                slot = id - 400;
            }
            work->resultFile = func_0202c364(FILE_ID(work->header0, slot), 0x11);
            work->step = 8;
        } else {
            BOOL isMode2 = work->mode == 2;

            work->tracker = GetSceneTagTracker_020711b0();
            work->step = 0;
            if (work->mode == 2) {
                int i;

                LoadBg3Graphics_020be5e0(work->file0, -(isMode2 != FALSE), 1, isMode2, work->file1, 0);
                for (i = 0; i < 10; i++) {
                    work->records.labels.first[i] = FindActiveRecordById_020b8184(work->tracker, 500 + i);
                    work->records.labels.second[i] = FindActiveRecordById_020b8184(work->tracker, 510 + i);
                    work->records.labels.third[i] = FindActiveRecordById_020b8184(work->tracker, 520 + i);
                    work->records.labels.fourth[i] = FindActiveRecordById_020b8184(work->tracker, 530 + i);
                }
                work->done = TRUE;
                return RunIntroSequenceStep_020bfea0;
            }
            LoadBg3Graphics_020be5e0(work->file0, isMode2 != FALSE, 0, isMode2, NULL, 0);
            work->done = TRUE;
            return UpdateResultFadeOut_020c0044;
        }
        break;
    case 2: {
        PoolConfig config;

        if (!IsRecordIdFree_0202c38c(work->texLoad.file)) {
            break;
        }
        config = data_ov045_020c0794;
        work->step = 0;
        REG_BG3CNT = (u16)((REG_BG3CNT & 0x43) | 0x1d80);
        REG_BG2CNT = (u16)((REG_BG2CNT & 0x43) | 0x1e80);
        REG_BG0CNT = (u16)((REG_BG0CNT & ~3) | 3);
        REG_BG1CNT = (u16)((REG_BG1CNT & ~3) | 0);
        REG_BG2CNT = (u16)((REG_BG2CNT & ~3) | 1);
        REG_BG3CNT = (u16)((REG_BG3CNT & ~3) | 2);
        LoadBg3Graphics_020be5e0(work->file0, -1, 0, TRUE, work->file1, 0);
        func_ov027_020b7d58(work->records.pool, &config);
        func_ov027_020b7e24(work->records.pool, FILE_ID(work->header0, 1));
        work->iconValue = FindActiveRecordById_020b8184(work->records.pool, 0x173)->value;
        work->step = 3;
        break;
    }
    case 3: {
        TextFrame frame = data_ov045_020c0784;
        int i;

        InitTextLayerAt_020014b0(work->textLayer, 2, NULL, GetFieldFont3_020711e0(), &frame);
        for (i = 0; i < 12; i++) {
            work->icons[i] = FindActiveRecordById_020b8184(work->records.pool, 300 + i);
        }
        REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0xf00;
        REG_DISPCNT &= ~0xe000;
        work->timer = 0;
        work->step = 4;
        break;
    }
    case 4:
        if (work->timer == 0) {
            AcquireRecordManager_02051c80();
            AcquireRecordSlot_02051d3c(0, 0);
        }
        work->timer++;
        if (work->timer < 2) {
            break;
        }
        work->timer = 0;
        work->step = 5;
        break;
    case 5:
        if (work->texLoad.state == 0) {
            tex = FindTextureResourceBlock_0201ac70(work->texLoad.file);
            texSize = GetTextureImageBytes_020188cc(tex);
            tex4x4Size = GetCompressedTextureBytes_020188e0(tex);
            plttSize = GetPaletteBytes_02018964(tex);

            if (texSize) {
                texKey = data_02055c4c(texSize, FALSE, 0);
            } else {
                texKey = 0;
            }
            if (tex4x4Size) {
                tex4x4Size = data_02055c4c(tex4x4Size, TRUE, 0);
            } else {
                tex4x4Size = 0;
            }
            if (plttSize) {
                texSize = data_02055c54(plttSize, tex->tex4x4Info.flag & 0x8000, 0);
            } else {
                texSize = 0;
            }
            ReleaseTextureResourceKeys_020188f4(tex, texKey, tex4x4Size);
            func_02018978(tex, texSize);
            work->texLoad.remaining = tex->texInfo.sizeTex << 3;
            if (work->texLoad.remaining != 0) {
                work->texLoad.source = (u8 *)tex + tex->texInfo.ofsTex;
                work->texLoad.vramOffset = (u16)tex->texInfo.vramKey << 3;
                work->texLoad.isPalette = FALSE;
                work->texLoad.state = 1;
            } else {
                work->texLoad.state = 2;
            }
            work->texLoad.tex = tex;
        }
        if (work->texLoad.state == 1 && StepTextureUpload_020c02dc(&work->texLoad)) {
            work->texLoad.state = 2;
            work->texLoad.tex->texInfo.flag |= 1;
        }
        if (work->texLoad.state == 2) {
            tex = work->texLoad.tex;
            work->texLoad.remaining = tex->tex4x4Info.sizeTex << 3;
            if (work->texLoad.remaining != 0) {
                work->texLoad.source = (u8 *)tex + tex->tex4x4Info.ofsTex;
                work->texLoad.vramOffset = (u16)tex->tex4x4Info.vramKey << 3;
                work->texLoad.isPalette = FALSE;
            } else {
                work->texLoad.state = 5;
            }
        }
        if (work->texLoad.state == 3 && StepTextureUpload_020c02dc(&work->texLoad)) {
            tex = work->texLoad.tex;
            u32 addr;

            work->texLoad.source = (u8 *)tex + tex->tex4x4Info.ofsTexPlttIdx;
            addr = (u16)tex->tex4x4Info.vramKey << 3;
            work->texLoad.vramOffset = ((addr & 0x1ffff) >> 1) + 0x20000 + ((addr & 0x40000) >> 2);
            work->texLoad.remaining = tex->tex4x4Info.sizeTex << 2;
            work->texLoad.isPalette = FALSE;
            work->texLoad.state = 4;
        }
        if (work->texLoad.state == 4 && StepTextureUpload_020c02dc(&work->texLoad)) {
            work->texLoad.state = 5;
            work->texLoad.tex->tex4x4Info.flag |= 1;
        }
        if (work->texLoad.state == 5) {
            tex = work->texLoad.tex;
            work->texLoad.remaining = tex->plttInfo.sizePltt << 3;
            work->texLoad.source = (u8 *)tex + tex->plttInfo.ofsPlttData;
            work->texLoad.vramOffset = (u16)tex->plttInfo.vramKey << 3;
            work->texLoad.isPalette = TRUE;
            work->texLoad.state = 6;
        }
        if (work->texLoad.state == 6) {
            OS_WaitVBlankIntr_020049d0();
            GX_BeginLoadTexPltt_020081e0();
            GX_LoadTexPltt_02008214(work->texLoad.source, work->texLoad.vramOffset, work->texLoad.remaining);
            GX_EndLoadTexPltt_02008284();
            OS_WaitVBlankIntr_020049d0();
            work->texLoad.state = 100;
            work->texLoad.tex->plttInfo.flag |= 1;
        }
        if (work->texLoad.state != 100) {
            break;
        }
        work->timer = 0;
        work->step = 6;
        break;
    case 6: {
        work->timer++;
        if (work->timer < 2) {
            break;
        }
        tex6 = FindTextureResourceBlock_0201ac70(work->texLoad.file);
        if (tex6 != NULL) {
            if (&tex6->dict != NULL && DictHasIndex(&tex6->dict, 0)) {
                entries = (const NNSG3dResDictEntryHeader *)((u8 *)&tex6->dict + tex6->dict.ofsEntry);
                texData = (const NNSG3dResDictTexData *)entries->data;
            } else {
                texData = NULL;
            }
        } else {
            texData = NULL;
        }
        if (tex6 != NULL && tex6->plttInfo.ofsDict != 0) {
            dict = (const NNSG3dResDict *)((u8 *)tex6 + tex6->plttInfo.ofsDict);
            if (dict != NULL && DictHasIndex(dict, 0)) {
                entries = (const NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
                plttData = (const NNSG3dResDictPlttData *)entries->data;
            } else {
                plttData = NULL;
            }
        } else {
            plttData = NULL;
        }
        plttOffset = plttData->offset;
        plttKey6 = (u16)tex6->plttInfo.vramKey;
        if ((u8)((texData->texImageParam & 0x1c000000) >> 26) == 5) {
            texKey6 = (u16)tex6->tex4x4Info.vramKey;
        } else {
            texKey6 = (u16)tex6->texInfo.vramKey;
        }
        if ((plttData->flag & 1) == 0) {
            plttOffset = (plttOffset << 15) >> 16;
            plttKey6 = (plttKey6 << 15) >> 16;
        }
        work->texLoad.width = texData->extraParam & 0x7ff;
        work->texLoad.height = (texData->extraParam >> 11) & 0x7ff;
        work->texLoad.imageParam = (texData->texImageParam + texKey6) | 0x20000000;
        work->texLoad.plttBase = (u16)(plttOffset + plttKey6);
        work->texLoad.alpha = 0x1f;
        NNSi_FndFreeFromDefaultHeap_0202a1c4(work->texLoad.file);
        work->texLoad.file = NULL;
        work->timer = 0;
        work->step = 7;
        break;
    }
    case 7:
        work->timer++;
        if (work->timer < 2) {
            break;
        }
        work->step = 0;
        work->done = TRUE;
        work->timer = 0;
        return func_ov045_020bf3d0;
    case 8: {
        PoolConfig config;

        if (!IsRecordIdFree_0202c38c(work->resultFile)) {
            break;
        }
        config = data_ov045_020c07a8;
        work->step = 0;
        REG_BG3CNT = (u16)((REG_BG3CNT & 0x43) | 0x1d80);
        REG_BG2CNT = (u16)((REG_BG2CNT & 0x43) | 0x1e00);
        REG_BG0CNT = (u16)((REG_BG0CNT & ~3) | 2);
        REG_BG1CNT = (u16)((REG_BG1CNT & ~3) | 0);
        REG_BG2CNT = (u16)((REG_BG2CNT & ~3) | 1);
        REG_BG3CNT = (u16)((REG_BG3CNT & ~3) | 3);
        LoadBg3Graphics_020be5e0(work->file0, 0, 0, TRUE, work->file1, 0x4800);
        func_ov027_020b7d58(work->records.pool, &config);
        func_ov027_020b7e24(work->records.pool, FILE_ID(work->header0, 1));
        work->step = 9;
        break;
    }
    case 9: {
        TextFrame frame = data_ov045_020c0774;
        BOOL unlock = FALSE;
        int id;

        work->step = 0;
        InitTextLayerAt_020014b0(work->resultLayer, 2, NULL, GetFieldFont3_020711e0(), &frame);
        FinishTextureSlotLoad_020c0214(work->resultSlot);
        REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0xd00;
        REG_DISPCNT &= ~0xe000;
        AcquireRecordManager_02051c80();
        AcquireRecordSlot_02051d3c(0, 0);
        id = work->id;
        if (id >= 0xd0 && id <= 0x10f) {
            int base = (id - 0xd0) / 5 * 5 + 0xd0;
            int i;

            for (i = 0; i < 5; i++) {
                unlock += GetByteCounterOrDefault_020291cc(base + i);
            }
            if (unlock == 0) {
                unlock = TRUE;
            } else {
                unlock = FALSE;
            }
        } else if (id >= 0x19c && id <= 0x1ad) {
            unlock = GetByteCounterOrDefault_020291cc(id) == 0;
        }
        if (unlock) {
            func_02029240(work->id, 0);
            SetGlobalPackedBit_02027320(work->id);
        }
        work->done = TRUE;
        return RunNameRevealStep_020bfc30;
    }
    }
    return NULL;
}
