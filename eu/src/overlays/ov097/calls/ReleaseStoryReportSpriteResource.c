extern int NNSi_FndFreeFromDefaultHeap(int block);

int ReleaseStoryReportSpriteResource(int obj) {
    if (*(int *)(obj + 40) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(obj + 40));
        *(int *)(obj + 40) = 0;
    }
    *(unsigned char *)(obj + 38) &= ~0xe0;
    return 1;
}
