extern void func_0202a1c4();
extern int gMenuCursorState;

void ReleaseMenuCursorState_02066a68(void) {
    int p = *(int *)&gMenuCursorState;
    if (p == 0) {
        return;
    }
    func_0202a1c4(p);
    gMenuCursorState = 0;
}
