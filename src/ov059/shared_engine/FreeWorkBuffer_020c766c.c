extern void NNSi_FndFreeFromDefaultHeap();
extern int func_020cffa0;

void FreeWorkBuffer_020c766c(void) {
    int p = *(int *)&func_020cffa0;
    if (p == 0) {
        return;
    }
    NNSi_FndFreeFromDefaultHeap(p);
    func_020cffa0 = 0;
}
