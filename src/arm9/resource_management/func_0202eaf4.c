extern int WM_EndKeySharing_0x0201696c();
extern void func_0202c8a8(int unknownValue);
extern void func_0202ca18(void);
extern void NNSi_FndFreeFromDefaultHeap(int allocationAddress);
extern int NNSi_FndGetAllocatorForDefaultHeap(int heapId);

void func_0202eaf4(int *resourceState) {
    int listIndex, resourceIndex;
    int lastAllocation = 0;
    for (listIndex = 4; listIndex >= 0; listIndex--) {
        for (resourceIndex = ((short *)resourceState)[listIndex] - 1; resourceIndex >= 0; resourceIndex--) {
            WM_EndKeySharing_0x0201696c(NNSi_FndGetAllocatorForDefaultHeap(0), ((int *)resourceState[listIndex + 4])[resourceIndex]);
        }
        if (resourceState[listIndex + 4]) lastAllocation = resourceState[listIndex + 4];
    }
    if (lastAllocation) NNSi_FndFreeFromDefaultHeap(lastAllocation);
    if (resourceState[3]) {
        func_0202ca18();
        func_0202c8a8(resourceState[3]);
    }
    resourceState[3] = 0;
}
