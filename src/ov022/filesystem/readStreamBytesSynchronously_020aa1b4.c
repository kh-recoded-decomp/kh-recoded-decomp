extern void FS_WaitAsync(int file);
extern int  FS_SeekFile(int file, int pos, int whence);
extern int  OS_UnlockByWord_0x0200ae4c(int file, void *destination, unsigned int requestedLength);

int readStreamBytesSynchronously_020aa1b4(int streamCursor, void *destination, unsigned int requestedLength) {
    if (*(unsigned char *)(streamCursor + 0x10) == 1) {
        FS_WaitAsync(*(int *)(streamCursor + 0xc));
        FS_SeekFile(*(int *)(streamCursor + 0xc), *(int *)(streamCursor + 8), 0);
        *(unsigned char *)(streamCursor + 0x10) = 0;
    }
    if (OS_UnlockByWord_0x0200ae4c(*(int *)(streamCursor + 0xc), destination, requestedLength) == -1) {
        return 0;
    }
    *(int *)(streamCursor + 8) += requestedLength;
    return 1;
}
