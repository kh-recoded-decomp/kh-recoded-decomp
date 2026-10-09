extern void NNSi_FndFreeFromDefaultHeap();
extern int gMenuCursorState;

void ReleaseMenuCursorState(void) {
    int p = *(int *)&gMenuCursorState;
    if (p == 0) {
        return;
    }
    NNSi_FndFreeFromDefaultHeap(p);
    gMenuCursorState = 0;
}
