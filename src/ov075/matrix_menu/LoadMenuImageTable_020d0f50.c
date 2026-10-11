#include "nitro/types.h"

typedef struct IconCell {
    u16 width;
    u16 height;
    u32 texImageParam;
    u32 plttBase;
} IconCell;

typedef struct ResDict {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy;
    u16 ofsEntry;
} ResDict;

typedef struct TexResource {
    u8 header[8];
    u32 texKey;
    u8 pad_0c[0xc];
    u32 tex4x4Key;
    u8 pad_1c[0x10];
    u32 plttKey;
    u8 pad_30[4];
    u16 plttDictOfs;
    u8 pad_36[6];
    ResDict texDict;
} TexResource;

extern char data_ov075_020d18b4[];
extern char data_ov075_020d18c4[];

extern void func_0202c690(int enable);
extern u32 Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern u8 *func_0202c48c(u32 fileId, u32 mode);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern s32 func_0202d098(void *resource, void *heap);
extern TexResource *FindTextureResourceBlock_0201ac70(void *header);
extern int ZeroHalfThenFree_0202cd78(u32 container);

#define CONTAINER_FILE_ID(container, index) ((((container) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

static inline BOOL DictHasIndex(ResDict *dict, u32 index)
{
    return index < dict->numEntry;
}

void LoadMenuImageTable_020d0f50(IconCell *cells)
{
    s16 fallback = 0;
    u32 primary;
    u32 secondary;
    u8 *block;
    s16 i;
    u32 *texEntry;
    u16 *plttEntry;
    u16 plttBase;
    u16 plttOffset;
    TexResource *tex;
    u16 texBase;
    ResDict *dict;

    func_0202c690(0);
    primary = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov075_020d18b4, 0xe, 1);
    secondary = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov075_020d18c4, 0xe, 1);
    for (i = 0; i < 0x85; i++) {
        block = func_0202c48c(CONTAINER_FILE_ID(primary, i), 0xe);
        if (*block == 0) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
            block = func_0202c48c(CONTAINER_FILE_ID(secondary, fallback), 0xe);
            fallback++;
        }
        func_0202d098(block, NULL);
        tex = FindTextureResourceBlock_0201ac70(block);
        if (tex != NULL) {
            if (&tex->texDict != NULL && DictHasIndex(&tex->texDict, 0)) {
                texEntry = (u32 *)((u8 *)&tex->texDict + tex->texDict.ofsEntry + 4);
            } else {
                texEntry = NULL;
            }
        } else {
            texEntry = NULL;
        }
        if (tex != NULL && tex->plttDictOfs != 0) {
            dict = (ResDict *)((u8 *)tex + tex->plttDictOfs);
            if (dict != NULL && DictHasIndex(dict, 0)) {
                plttEntry = (u16 *)((u8 *)dict + dict->ofsEntry + 4);
            } else {
                plttEntry = NULL;
            }
        } else {
            plttEntry = NULL;
        }
        plttOffset = plttEntry[0];
        plttBase = tex->plttKey;
        texBase = (u8)((texEntry[0] & 0x1c000000) >> 26) == 5 ? tex->tex4x4Key : tex->texKey;
        if (!(plttEntry[1] & 1)) {
            plttOffset >>= 1;
            plttBase >>= 1;
        }
        cells[i].width = texEntry[1] & 0x7ff;
        cells[i].height = (texEntry[1] >> 11) & 0x7ff;
        cells[i].texImageParam = (texEntry[0] + texBase) | 0x20000000;
        cells[i].plttBase = (u16)(plttOffset + plttBase);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
    }
    ZeroHalfThenFree_0202cd78(secondary);
    ZeroHalfThenFree_0202cd78(primary);
    func_0202c690(1);
}
