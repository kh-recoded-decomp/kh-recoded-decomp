extern int data_ov039_020bea00;

unsigned int BuildSlotImageParams_020bc220(int slot, unsigned int low)
{
    int address = *(int *)(data_ov039_020bea00 + slot * 4 + 0xcab4);

    if (address == 0) {
        return 0;
    }
    return (low & 0x1ff) | (0x80000000 | (((address + 0x8000) & 0xfffffc) << 7));
}
