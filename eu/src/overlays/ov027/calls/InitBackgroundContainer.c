#include "src/overlays/ov027/BackgroundContainer.h"

extern void MI_CpuFill8(void *destination, int value, int size);
extern void NNS_FndInitList(int list, int linkOffset);
extern void *NNSi_FndAllocFromDefaultHeap(int size);

void InitBackgroundContainer(BackgroundContainer *container,
                             BackgroundContainerConfig *config)
{
    MI_CpuFill8(container, 0, sizeof(*container));
    NNS_FndInitList((int)container, 0x2c);
    container->config.entryCapacity = config->entryCapacity;
    container->config.spriteCapacity = config->spriteCapacity;
    container->config.tagCapacity = config->tagCapacity;
    container->config.parameter0c = config->parameter0c;
    container->config.parameter10 = config->parameter10;
    container->entryRecords = NNSi_FndAllocFromDefaultHeap(config->entryCapacity * 0x38);
    container->spriteRecords = NNSi_FndAllocFromDefaultHeap(config->spriteCapacity * 0x30);
    container->tagRecords = NNSi_FndAllocFromDefaultHeap(config->tagCapacity * 16);
    MI_CpuFill8(container->entryRecords, 0, config->entryCapacity * 0x38);
    MI_CpuFill8(container->spriteRecords, 0, config->spriteCapacity * 0x30);
    MI_CpuFill8(container->tagRecords, 0, config->tagCapacity * 16);
}
