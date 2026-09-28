extern int data_02057c0c;
void WH_ChangeSysState_0200e8c0(int state) {
    *(int *)((char *)&data_02057c0c + 0x24) = state;
}
