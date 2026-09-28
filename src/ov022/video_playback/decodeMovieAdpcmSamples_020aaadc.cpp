/* Adapted from CC0-1.0 source Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov024/calls/func_ov024_02086800.cpp.
 * Decodes the low and high IMA ADPCM nibbles from each input byte, updates
 * the predictor and step index, clamps them, and packs two samples per word.
 */
/* MobiClip: IMA ADPCM, two nibbles per input byte.
 *
 * Standard four-bit IMA: the low three bits scale the current step by
 * 1/8 + 1/2 + 1/4 + 1, bit 3 is the sign, and the index walks the step table
 * by the table of deltas, clamped to 0..0x58. The predictor is clamped to
 * signed 16 bits.
 *
 * Each input byte yields two samples, packed low half first into one output
 * word, so the caller gets a stereo-shaped pair per byte.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned short u16;
typedef unsigned int u32;

#define INDEX_MAX   0x58
#define SAMPLE_MIN  (-0x8000)
#define SAMPLE_MAX  0x7fff

struct MobiClipAdpcmState {
    int nSample;
    int nIndex;
};

extern "C" {

extern const s16 data_ov022_020b7b18[];
extern const s8 data_ov022_020b7b08[];

void decodeMovieAdpcmSamples_020aaadc(MobiClipAdpcmState *pState, const u8 *pSrc, int nCount,
                         u32 *pDst)
{
    int i;
    int nCode;
    int nPrev;
    int nDiff;
    int nFirst;
    int nStep;

    for (i = 0; i < nCount; i++) {
        nCode = pSrc[i];

        nPrev = pState->nIndex;
        nStep = data_ov022_020b7b18[nPrev];
        pState->nIndex = pState->nIndex + data_ov022_020b7b08[nCode & 7];
        if (pState->nIndex < 0) {
            pState->nIndex = 0;
        }
        if (pState->nIndex > INDEX_MAX) {
            pState->nIndex = INDEX_MAX;
        }
        nDiff = nStep >> 3;
        if (nCode & 4) {
            nDiff += nStep;
        }
        if (nCode & 2) {
            nDiff += nStep >> 1;
        }
        if (nCode & 1) {
            nDiff += nStep >> 2;
        }
        if (nCode & 8) {
            pState->nSample = pState->nSample - nDiff;
        } else {
            pState->nSample = pState->nSample + nDiff;
        }
        nCode = nCode >> 4;
        if (pState->nSample < SAMPLE_MIN) {
            pState->nSample = SAMPLE_MIN;
        }
        if (pState->nSample > SAMPLE_MAX) {
            pState->nSample = SAMPLE_MAX;
        }

        nFirst = pState->nSample;
        nPrev = pState->nIndex;
        nStep = data_ov022_020b7b18[nPrev];
        pState->nIndex = pState->nIndex + data_ov022_020b7b08[nCode & 7];
        if (pState->nIndex < 0) {
            pState->nIndex = 0;
        }
        if (pState->nIndex > INDEX_MAX) {
            pState->nIndex = INDEX_MAX;
        }
        nDiff = nStep >> 3;
        if (nCode & 4) {
            nDiff += nStep;
        }
        if (nCode & 2) {
            nDiff += nStep >> 1;
        }
        if (nCode & 1) {
            nDiff += nStep >> 2;
        }
        if (nCode & 8) {
            pState->nSample = pState->nSample - nDiff;
        } else {
            pState->nSample = pState->nSample + nDiff;
        }
        if (pState->nSample < SAMPLE_MIN) {
            pState->nSample = SAMPLE_MIN;
        }
        if (pState->nSample > SAMPLE_MAX) {
            pState->nSample = SAMPLE_MAX;
        }

        *pDst++ = (u32)(pState->nSample * 0x10000) | (u32)(u16)nFirst;
    }
}

}
