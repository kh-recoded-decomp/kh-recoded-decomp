extern void NNSi_FndFreeFromDefaultHeap();
extern int data_020b5604;

void FreeCueTable_020a7cac(void) {
    if (data_020b5604 != 0) {
        NNSi_FndFreeFromDefaultHeap(data_020b5604);
    }
    data_020b5604 = 0;
}
