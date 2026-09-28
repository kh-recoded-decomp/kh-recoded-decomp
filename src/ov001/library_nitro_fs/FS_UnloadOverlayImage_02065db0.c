extern void FS_EndOverlay(void *p);

int FS_UnloadOverlayImage_02065db0(void *p) {
    FS_EndOverlay(p);
    return 1;
}
