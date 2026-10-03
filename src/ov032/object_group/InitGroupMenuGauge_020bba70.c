#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    void *pixels;
} CharacterData;

typedef struct {
    u8 *gaugeSource;
    u8 *gaugeTiles;
    void *mainCharFile;
    void *subCharFile;
    CharacterData *mainChar;
    CharacterData *subChar;
    u8 pad_18[0x10];
    BOOL snap;
} GaugeMenu;

typedef u32 (*MenuStateFunc)(void);

extern struct {
    int reserved;
    GaugeMenu *menu;
} menuState_020c0068;

extern void *GetSceneTagTracker_020711b0(void);
extern GaugeMenu *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern unsigned int MakePrimaryVramKey_020711ec(unsigned int slot);
extern unsigned int MakePrimaryVramKey_02071214(unsigned int slot);
extern void *func_0202c48c(unsigned int key, u32 heapId);
extern BOOL func_02014d38(void *file, CharacterData **out);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void MIi_CpuCopyFast_01ff878c(const void *src, void *dst, u32 size);
extern void UploadGroupMenuTiles_020bbba8(int arg);
extern void SetGroupMenuProgress_020bb9b8(int percent);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void func_ov027_020b822c(void *pool, void *record, int arg2, int arg3);
extern u32 UpdateGroupMenuCounter_020bbb4c(void);

MenuStateFunc InitGroupMenuGauge_020bba70(void)
{
    GaugeMenu *menu;
    void *file;
    CharacterData *charData;
    void *tracker;

    GetSceneTagTracker_020711b0();
    menu = NNSi_FndGetCurrentRootHeap_0202a764();
    menuState_020c0068.menu = menu;
    menu->snap = TRUE;
    file = func_0202c48c(MakePrimaryVramKey_020711ec(7), 0xe);
    func_02014d38(file, &charData);
    menu->gaugeSource = NNSi_FndAllocFromDefaultHeap_0202a178(0x160);
    menu->gaugeTiles = NNSi_FndAllocFromDefaultHeap_0202a178(0x160);
    MIi_CpuCopyFast_01ff878c(charData->pixels, menu->gaugeSource, 0x160);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
    menu->mainCharFile = func_0202c48c(MakePrimaryVramKey_02071214(3), 0xe);
    menu->subCharFile = func_0202c48c(MakePrimaryVramKey_02071214(4), 0xe);
    func_02014d38(menu->mainCharFile, &menu->mainChar);
    func_02014d38(menu->subCharFile, &menu->subChar);
    UploadGroupMenuTiles_020bbba8(0);
    SetGroupMenuProgress_020bb9b8(0);
    tracker = GetSceneTagTracker_020711b0();
    func_ov027_020b822c(tracker, FindActiveRecordById_020b8184(tracker, 5), -2, 1);
    return UpdateGroupMenuCounter_020bbb4c;
}
