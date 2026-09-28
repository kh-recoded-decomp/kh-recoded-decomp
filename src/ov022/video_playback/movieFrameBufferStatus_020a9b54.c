int movieFrameBufferStatus_020a9b54(const unsigned char *movieContext)
{
    if (*(const int *)(movieContext + 0x20) == 0) {
        return 0;
    }
    if (*(const int *)(movieContext + 0x28) != 0) {
        return 0x80;
    }
    return 0x100;
}
