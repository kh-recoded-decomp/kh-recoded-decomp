extern void *SetPackedBit();
extern int data_ov101_020c5920;

void *SetStateFlag(int setIndex, int value)
{
    return SetPackedBit(data_ov101_020c5920 + 0xC + setIndex * 8, value);
}
