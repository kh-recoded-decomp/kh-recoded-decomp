extern int Ov002_RebindSlotToCell();

int Slot_SetCellData_0206a93c(int arg0, int arg1, int nStop, int nIndex) {
    *(int *)(arg0 + 0x2c) = arg1;
    Ov002_RebindSlotToCell(arg0, 0, nStop, nIndex);
    return 1;
}
