#include "nitro/types.h"

extern unsigned int sOv073_OCBGOFSFUNC_020c41a8;
extern unsigned int NNS_G2dGetUnpackedScreenData();
extern unsigned int MIi_CpuCopy16();
extern unsigned int InvokeForChannelOrBoth();
extern unsigned int NNS_G2dGetUnpackedBGCharacterData();
extern unsigned int NNSi_FndFreeFromDefaultHeap();
extern unsigned int GetBgDataFromArchive();
extern unsigned int func_0202c4a0();
extern unsigned int func_ov027_020b9e10();
extern unsigned int ClearScreenLayerDirty();
extern unsigned int UpdateScreenWidgetLayer();
extern unsigned int BuildSlotImageParams();
extern unsigned int AllocateListEntry();
extern void RestoreStatusSubScreen(void);
extern void ApplyListScrollRegs(void);

void LoadStatusScreenResources(unsigned int event, int work)
{
    unsigned int file;
    unsigned int destination;
    unsigned int size;
    int firstScreen;
    int secondScreen;

    if (*(int *)(work + 0x188) == 0) {
        file = func_0202c4a0(
            ((*(int *)(work + 0x140) + 0x8000U & 0xfffffc) << 7) |
                0x8000000b,
            0xe
        );
        *(unsigned int *)(work + 0x188) = file;
        GetBgDataFromArchive(
            work + 0x18c,
            *(unsigned int *)(work + 0x188),
            0xffffffff,
            0xffffffff,
            0
        );
    }
    if (*(int *)(work + 0x184) == 0) {
        file = BuildSlotImageParams(0, 9);
        file = func_0202c4a0(file, 0xe);
        *(unsigned int *)(work + 0x184) = file;
        NNS_G2dGetUnpackedBGCharacterData(file, work + 0x180);
    }
    file = BuildSlotImageParams(0, 10);
    file = func_0202c4a0(file, 0xe);
    NNS_G2dGetUnpackedScreenData(file, &firstScreen);
    size = *(unsigned int *)(firstScreen + 8);
    destination = func_ov027_020b9e10(work + 0x148, 0x1b);
    MIi_CpuCopy16(firstScreen + 0xc, destination, size);
    NNSi_FndFreeFromDefaultHeap(file);
    file = BuildSlotImageParams(0, 0xb);
    file = func_0202c4a0(file, 0xe);
    NNS_G2dGetUnpackedScreenData(file, &secondScreen);
    size = *(unsigned int *)(secondScreen + 8);
    destination = UpdateScreenWidgetLayer(0x19);
    MIi_CpuCopy16(secondScreen + 0xc, destination, size);
    NNSi_FndFreeFromDefaultHeap(file);
    ClearScreenLayerDirty(0x18);
    ClearScreenLayerDirty(0x19);
    ClearScreenLayerDirty(0x1a);
    ClearScreenLayerDirty(0x1b);
    AllocateListEntry((u32)RestoreStatusSubScreen);
    *(unsigned int *)(work + 0x204) = 2;
    if (*(int *)(work + 0x164) == 0) {
        InvokeForChannelOrBoth(
            1,
            &sOv073_OCBGOFSFUNC_020c41a8,
            (u32)ApplyListScrollRegs,
            0
        );
        *(unsigned int *)(work + 0x164) = 1;
    }
}
