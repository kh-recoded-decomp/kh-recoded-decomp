extern void *func_ov039_020bc1dc(void);
extern void DestroyAllContainerElements(void *context);
extern void ReleaseIfMarked(void *context);
void func_ov089_020bfaf0(void *unusedContext) {
    DestroyAllContainerElements(func_ov039_020bc1dc());
    ReleaseIfMarked(func_ov039_020bc1dc());
}
