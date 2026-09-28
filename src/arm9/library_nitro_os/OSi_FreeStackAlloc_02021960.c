extern void OS_FreeToHeap(int heap, int handle, void *ptr);

void OSi_FreeStackAlloc_02021960(void *ptr)
{
    OS_FreeToHeap(0, -1, ptr);
}
