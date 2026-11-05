extern void *GetMenuWork(void);
extern void DestroyAllContainerElements(void *context);
extern void ReleaseIfMarked(void *context);
void DestroyOverlay089RootElements(void *unusedContext) {
    DestroyAllContainerElements(GetMenuWork());
    ReleaseIfMarked(GetMenuWork());
}
