extern void *SetPackedBit();
extern int gListMenuGlobalStorage;

void *SetStateFlag(int setIndex, int value)
{
    return SetPackedBit(gListMenuGlobalStorage + 0xC + setIndex * 8, value);
}
