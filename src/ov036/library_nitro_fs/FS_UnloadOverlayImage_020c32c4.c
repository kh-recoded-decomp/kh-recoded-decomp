extern void FS_EndOverlay(void *p);

int FS_UnloadOverlayImage_020c32c4(void *p) {
    FS_EndOverlay(p);
    return 1;
}
