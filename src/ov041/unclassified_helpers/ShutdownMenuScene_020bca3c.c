#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x14];
    void *buffer;
    u8 slotCount;
    u8 pad_019[0x7];
    u32 unk_20;
    u8 pad_024[0x514];
    u32 heapHandle;
    u8 pad_53c[0x1dd8];
    void *table;
} Scene;

typedef struct {
    s16 kind;
} PlayerFlagRecord;

extern void func_ov041_020bdf00(void);
extern void func_ov041_020bdc08(void);
extern void func_ov041_020c0aac(int slot);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void ZeroHalfThenFree_0202cd78(u32 value);
extern void FreeManagerRecordTable_020be204(void);
extern void PXI_Init_0202a638(u32 value);
extern void func_ov041_020ce1e0(void *object);
extern void PXI_Init_020be070(void);
extern PlayerFlagRecord *GetPlayerFlagRecord_0205036c(int index);
extern void SetMenuEntryHighlight_0207830c(int menu, int index, int highlighted);
extern u8 *GetOverlaySelectionRecord(int index);
extern void func_ov001_0207d658(void);
extern void PopVramState_020365f0(void);

void ShutdownMenuScene_020bca3c(Scene **scenePtr) {
    int i;
    Scene *scene = *scenePtr;

    func_ov041_020bdf00();
    func_ov041_020bdc08();
    for (i = 0; i < scene->slotCount; i++) {
        func_ov041_020c0aac((u8)i);
    }
    if (scene->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(scene->buffer);
        scene->buffer = NULL;
    }
    ZeroHalfThenFree_0202cd78(scene->heapHandle);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(scene->table);
    FreeManagerRecordTable_020be204();
    PXI_Init_0202a638(scene->unk_20);
    func_ov041_020ce1e0((u8 *)scene + 0x53c);
    if (scene != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(scene);
        *scenePtr = NULL;
    }
    PXI_Init_020be070();
    for (i = 0; i < 8; i++) {
        if (GetPlayerFlagRecord_0205036c(i) != NULL) {
            switch (GetPlayerFlagRecord_0205036c(i)->kind) {
            case 0xd0:
            case 0xd1:
            case 0xd2:
                SetMenuEntryHighlight_0207830c(1, i, 1);
                break;
            default:
                SetMenuEntryHighlight_0207830c(1, i, 0);
                break;
            }
        }
    }
    for (i = 0; i < *(int *)(GetOverlaySelectionRecord(0) + 300); i++) {
        GetOverlaySelectionRecord(0);
        SetMenuEntryHighlight_0207830c(0, i, 0);
    }
    func_ov001_0207d658();
    PopVramState_020365f0();
}
