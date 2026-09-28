extern int data_ov039_020bea00;
extern void func_ov039_020bcf20(int arg0);
extern void func_ov039_020bd00c(int arg0);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_ov039_020bac24(void);
extern void func_ov039_020bcf88(void);
extern void func_ov039_020baae0(int value);

void CleanupHandlersAndSetPhase5_020bb680(void)
{
    int base = data_ov039_020bea00;

    func_ov039_020bcf20(*(int *)(base + 0xc998));
    func_ov039_020bd00c(*(int *)(base + 0xc99c));
    if (*(int *)(base + 0xc99c) != 0) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4((void *)*(int *)(base + 0xc99c));
        *(int *)(base + 0xc99c) = 0;
    }
    *(int *)(base + 0xca30) = 0;
    func_ov039_020bac24();
    func_ov039_020bcf88();
    func_ov039_020baae0(5);
}
