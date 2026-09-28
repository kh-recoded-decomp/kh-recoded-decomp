extern void ReleaseOverlay088Graphics(void);
extern void ClearOverlay088Grid(void *context);
extern void func_ov088_020bedd0(void *context);
void ShutdownOverlay088(void *context) {
    ReleaseOverlay088Graphics();
    ClearOverlay088Grid(context);
    func_ov088_020bedd0(context);
}
