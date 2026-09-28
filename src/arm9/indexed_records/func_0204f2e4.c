struct IndexedRecord { char pad[0x7c]; int flags; char pad2[0x8c - 0x80]; };

void func_0204f2e4(struct IndexedRecord *recordBase, int recordIndex)
{
    if (recordIndex < 0) return;
    recordBase[recordIndex].flags &= ~2;
}
