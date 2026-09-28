/* Ghidra-derived original C for ov022:0x020a941c.
 * Delegates resource release, then returns the original context pointer.
 */
extern void releaseMovieDecodeContext_020253e4(void *context);

void *destroyMovieStreamContext_020a93c0(void *context)
{
    releaseMovieDecodeContext_020253e4(context);
    return context;
}
