extern void DC_InvalidateRange(void *addr, unsigned size);
extern char *data_02059780;

short readInvalidatedHalfwordEntry_0200f5c4(int rowIndex, int columnIndex) {
    DC_InvalidateRange(data_02059780 + 0x20 + rowIndex * 0x24 + columnIndex * 2, 2);
    return *(short *)(data_02059780 + 0x20 + rowIndex * 0x24 + columnIndex * 2);
}
