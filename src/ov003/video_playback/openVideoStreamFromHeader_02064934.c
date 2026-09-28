extern void func_02064864(int streamContext, unsigned short *dst, unsigned short *sourceHeader);
extern void func_02001494(unsigned int *streamContext, int streamOption, unsigned int streamFlags, unsigned short *preparedHeader);

void openVideoStreamFromHeader_02064934(unsigned int *streamContext, int streamOption, unsigned int streamFlags, unsigned short *sourceHeader) {
    unsigned short preparedHeader[8];
    func_02064864((int)streamContext, preparedHeader, sourceHeader);
    func_02001494(streamContext, streamOption, streamFlags, preparedHeader);
}
