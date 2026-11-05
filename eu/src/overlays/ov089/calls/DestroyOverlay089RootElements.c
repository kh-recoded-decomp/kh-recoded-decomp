extern void *func_ov039_020bc1dc(void);
extern void DestroyAllContainerElements(void *context);
extern void ReleaseIfMarked(void *context);
void DestroyOverlay089RootElements(void *unusedContext) {
    DestroyAllContainerElements(func_ov039_020bc1dc());
    ReleaseIfMarked(func_ov039_020bc1dc());
}
