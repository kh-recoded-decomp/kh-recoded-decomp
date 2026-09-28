typedef unsigned char u8;

typedef struct MobiClipStream {
    u8 _pad00[0x38];
    int nStepLimit;
    u8 _pad48[0x0c];
    int nBaseStep;
    u8 _pad58[0x04];
    int nWindowPosition;
} MobiClipStream;

extern u8 readSubtitleStreamStep_020019f4(MobiClipStream *pStream);
extern void requestSubtitleStreamData_02001b20(MobiClipStream *pStream, int nStep);
extern void updateMovieStreamLeadTime_02064e2c(MobiClipStream *pStream);

int advanceMovieStreamWindow_020649a8(MobiClipStream *pStream) {
    int nPosition;
    int nStep;

    nStep = pStream->nBaseStep + readSubtitleStreamStep_020019f4(pStream);
    nPosition = (pStream->nWindowPosition += nStep);
    if (nPosition + nStep - pStream->nBaseStep > pStream->nStepLimit) {
        pStream->nWindowPosition -= nStep;
        requestSubtitleStreamData_02001b20(pStream, nStep);
    }
    updateMovieStreamLeadTime_02064e2c(pStream);
    return 1;
}
