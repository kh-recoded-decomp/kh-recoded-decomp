#include "src/overlays/ov079/ConfigOption.h"

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern u32 ReadPackedBitField(u32 *words, u32 bitOffset, u32 bitCount);
extern const void *func_ov027_020ba2c8(void *messages, int index);
extern u8 *data_0205fe0c;

ConfigOption *ConfigMenu_CreateOption(void *messages, u16 labelIndex, s8 count, u16 spec)
{
    ConfigOption *option = NNSi_FndAllocFromDefaultHeap(
        sizeof(ConfigOption) + (count - 1) * sizeof(ConfigChoice));
    int bitWidth;
    int bitIndex;
    u16 choice;

    option->count = count;
    bitIndex = spec & 0x1fff;
    bitWidth = spec >> 14;
    option->value = ReadPackedBitField((u32 *)(data_0205fe0c + 0x2878),
        (bitIndex / 32) * 32 + 32 - (bitIndex + bitWidth), bitWidth);
    option->bitWidth = bitWidth;
    option->locked = (spec >> 13) & 1;
    option->bitIndex = bitIndex;
    option->label = func_ov027_020ba2c8(messages, labelIndex);
    choice = 0;
    if (count > 0) {
        int firstName = (u16)(labelIndex + 1);
        int firstDescription = firstName + count;
        do {
            option->choices[choice].name = func_ov027_020ba2c8(messages, firstName + choice);
            option->choices[choice].description = func_ov027_020ba2c8(messages, choice + firstDescription);
            choice++;
        } while (choice < count);
    }
    return option;
}
