extern unsigned short data_02056e90;

void OSi_ClearAlarmBit_02003ec8(int bit) {
    int mask = ~(1 << bit);
    data_02056e90 &= mask;
}
