extern void NNSi_FndFreeFromDefaultHeap(int arg0);
void FreeSceneModelSlotArray(int arg0) {
    NNSi_FndFreeFromDefaultHeap(*(int *)(arg0 + 0x18c));
}
