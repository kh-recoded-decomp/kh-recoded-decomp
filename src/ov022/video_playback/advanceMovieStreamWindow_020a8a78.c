/* advanceMovieStreamWindow_020a8a78: move the movie stream window forward and request more data when the window limit is
 * exceeded. The routine computes a step from the base step plus a stream-header value, rolls
 * back and requests refill if the new position exceeds the limit, then updates stream lead time.
 * Observed stream fields in this overlay are limit +0x38, base step +0x48 and position +0x50.
 *
 * Adapted from CC0 MobiClip source in Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, src/overlays/ov024/calls/func_ov024_02083600.c.
 */
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
extern void updateMovieStreamLeadTime_020a8efc(MobiClipStream *pStream);

int advanceMovieStreamWindow_020a8a78(MobiClipStream *pStream) {
    int nPosition;
    int nStep;

    nStep = pStream->nBaseStep + readSubtitleStreamStep_020019f4(pStream);
    nPosition = (pStream->nWindowPosition += nStep);
    if (nPosition + nStep - pStream->nBaseStep > pStream->nStepLimit) {
        pStream->nWindowPosition -= nStep;
        requestSubtitleStreamData_02001b20(pStream, nStep);
    }
    updateMovieStreamLeadTime_020a8efc(pStream);
    return 1;
}
