extern void FS_EndOverlay(void *p);

int FS_UnloadOverlayImage_020658b8(void *p) {
    FS_EndOverlay(p);
    return 1;
}
