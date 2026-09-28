extern int NNSi_FndGetCurrentRootHeap();
extern int Ov002_ResetLinkState();
extern int data_020a049c;

void DestroyEventContext_0206cbb8(int arg0) {
    NNSi_FndGetCurrentRootHeap(arg0);
    Ov002_ResetLinkState();
    data_020a049c = 0;
}
