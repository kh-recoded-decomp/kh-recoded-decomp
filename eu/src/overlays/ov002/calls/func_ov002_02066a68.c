extern void NNSi_FndFreeFromDefaultHeap();
extern int data_ov002_0206c46c;

void func_ov002_02066a68(void) {
    int p = *(int *)&data_ov002_0206c46c;
    if (p == 0) {
        return;
    }
    NNSi_FndFreeFromDefaultHeap(p);
    data_ov002_0206c46c = 0;
}
