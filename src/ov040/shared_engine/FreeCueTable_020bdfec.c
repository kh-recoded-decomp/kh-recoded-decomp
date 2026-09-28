extern void NNSi_FndFreeFromDefaultHeap();
extern int func_020be264;

void FreeCueTable_020bdfec(void) {
    if (func_020be264 != 0) {
        NNSi_FndFreeFromDefaultHeap(func_020be264);
    }
    func_020be264 = 0;
}
