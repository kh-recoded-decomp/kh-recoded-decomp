extern int FS_SeekFile(int file, int filePosition, int whence);
extern int FS_ReadFileAsync(int file, void *destination, unsigned int requestedLength);

int beginAlignedFileReadAhead_020aa224(int streamCursor, void *destination, unsigned int requestedLength) {
    int filePosition = *(int *)(streamCursor + 8);
    int alignedPosition = filePosition & -0x200;
    int leadingOffset = filePosition - alignedPosition;
    unsigned int alignedLength = requestedLength + leadingOffset;

    if (alignedLength & 0x1ff) {
        alignedLength = (alignedLength & -0x200) + 0x200;
    }
    FS_SeekFile(*(int *)(streamCursor + 0xc), alignedPosition, 0);
    if (FS_ReadFileAsync(*(int *)(streamCursor + 0xc), destination, alignedLength) == -1) {
        return 0;
    }
    *(int *)(streamCursor + 8) += requestedLength;
    *(unsigned char *)(streamCursor + 0x10) = 1;
    return leadingOffset;
}
