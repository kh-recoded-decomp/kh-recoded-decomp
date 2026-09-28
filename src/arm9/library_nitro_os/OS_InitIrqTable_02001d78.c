extern int data_027e00a0;

void OS_InitIrqTable_02001d78(void) {
    *(int *)((int)&data_027e00a0 + 4) = 0;
    data_027e00a0 = 0;
}
