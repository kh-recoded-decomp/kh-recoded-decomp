#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct CharacterSet {
    u8 pad_00[0x38];
    void *file;
    NNSG2dCharacterData *character;
    void *frames[3];
} CharacterSet;

extern u32 func_ov001_020711ec(u32 index);
extern u32 func_ov001_02071214(u32 index);
extern void *func_0202c48c(u32 fileId, u32 heapId);
extern void *func_0202c478(u32 fileId, u32 heapId);
extern BOOL func_02014d38(void *file, NNSG2dCharacterData **character);
extern void func_0200344c(void *buffer, u32 size);
extern void GX_LoadBG2Char_02007a90(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void LoadBg2CharAndFrames_0207d728(CharacterSet *set)
{
    void *file;
    NNSG2dCharacterData *character;

    file = func_0202c48c(func_ov001_020711ec(6), 0xe);
    func_02014d38(file, &character);
    func_0200344c(character->pRawData, character->szByte);
    GX_LoadBG2Char_02007a90(character->pRawData, 0, character->szByte);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
    set->file = func_0202c478(func_ov001_02071214(2), 0xe);
    func_02014d38(set->file, &set->character);
    set->frames[0] = set->character->pRawData;
    set->frames[1] = (u8 *)set->character->pRawData + 0x300;
    set->frames[2] = (u8 *)set->character->pRawData + 0x600;
}
