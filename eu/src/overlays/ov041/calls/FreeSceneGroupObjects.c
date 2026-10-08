#include "nitro/types.h"

extern int data_ov035_020bc500;
extern int NNSi_FndFreeFromDefaultHeap();
extern int func_ov001_0206a918();
extern int RemoveTaggedListEntries();

void FreeSceneGroupObjects(void)
{
    int work;
    int index;
    int group;
    int groupIndex;

    work = *(int *)(data_ov035_020bc500 + 0xb8);
    RemoveTaggedListEntries(0x20bdb75);
    groupIndex = 0;
    do {
        index = 0;
        group = work + groupIndex * 8;
        if (index < (int)(u32)*(u8 *)(group + 0x318)) {
            do {
                func_ov001_0206a918(*(int *)(group + 0x314) + index * 0x34);
                index = index + 1;
            } while (index < (int)(u32)*(u8 *)(group + 0x318));
        }
        NNSi_FndFreeFromDefaultHeap(*(int *)(group + 0x314));
        groupIndex = groupIndex + 1;
    } while (groupIndex < 4);
}
