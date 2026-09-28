extern void WaitByLoop(int n);
extern void OS_WaitIrq(int clear, int mask);

void OS_WaitVBlankIntr_020049d0(void) {
    int one = 1;
    WaitByLoop(one);
    OS_WaitIrq(one, one);
}
