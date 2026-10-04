#include "nitro/types.h"

typedef struct SoundSlot {
    struct SoundSlot *next;
    struct SoundSlot *prev;
    u8 pad_08[0xe];
    s16 id;
    u8 pad_18[4];
    u8 queue[4];
} SoundSlot;

extern u8 *data_0206084c;
extern char data_02056134[];

extern void SoundMgr_WaitLoaderIfState1_0204d6c0(void);
extern void func_0201d5a0(int arg);
extern void SndInit_0201d214(void);
extern void OpenSoundArchive_0201e780(void *archive, const char *path, void *heap, BOOL loadSymbols);
extern void func_0201ee6c(u32 size);
extern void func_0201fc9c(void *heap);
extern void func_0201d698(void *list);
extern void func_01ff8830(void *dest, u32 value, u32 size);
extern void NNS_SndArcStrmInit_02020074(int priority, void *heap);
extern void func_020202fc(void *handle);
extern BOOL NNS_SndArcLoadSeq_0201f378(int seqNo, void *heap);
extern int func_0201f154(void *heap);

void SoundMgr_Init_0204d4ac(const char *path, BOOL loadSymbols)
{
    u8 *base = data_0206084c;
    SoundSlot *slots;
    int i;

    if (path == NULL) {
        path = data_02056134;
    }
    SoundMgr_WaitLoaderIfState1_0204d6c0();
    func_0201d5a0(0);
    SndInit_0201d214();
    OpenSoundArchive_0201e780(base, path, *(void **)(base + 0xb04b4), loadSymbols);
    func_0201ee6c(0x400);
    func_0201fc9c(*(void **)(base + 0xb04b4));
    func_0201d698(base + 0xb44d8);
    func_0201d698(base + 0xb44dc);
    func_01ff8830(base + 0xb4518, 0, sizeof(SoundSlot) * 16);
    slots = (SoundSlot *)(base + 0xb4518);
    for (i = 0; i < 16; i++) {
        *(SoundSlot **)(base + i * 0x20 + 0xb4518) = i < 15 ? &slots[i + 1] : NULL;
        *(SoundSlot **)(base + i * 0x20 + 0xb451c) = i > 0 ? &slots[i - 1] : NULL;
        *(s16 *)(base + i * 0x20 + 0xb452e) = i + 6;
        func_0201d698(base + 0xb4534 + i * 0x20);
    }
    *(SoundSlot **)(base + 0xb4718) = (SoundSlot *)(base + 0xb4518);
    NNS_SndArcStrmInit_02020074(10, *(void **)(base + 0xb44bc));
    func_020202fc(base + 0xb44c0);
    func_020202fc(base + 0xb44c4);
    *(s16 *)(base + 0xb472a) = -1;
    *(s16 *)(base + 0xb472c) = -1;
    *(s16 *)(base + 0xb4736) = -1;
    *(u16 *)(base + 0xb4734) = 0;
    NNS_SndArcLoadSeq_0201f378(0x29, *(void **)(base + 0xb04b4));
    *(int *)(base + 0xa8) = func_0201f154(*(void **)(data_0206084c + 0xb04b4));
    *(int *)(base + 0xa0) = *(int *)(base + 0xa8);
    *(int *)(base + 0xa4) = -1;
}
