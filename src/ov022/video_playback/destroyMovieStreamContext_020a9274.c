/* Ghidra-derived original C for ov022:0x020a941c.
 * Delegates resource release, then returns the original context pointer.
 */
extern void releaseMovieDecodeContext_020aa124(void *context);

void *destroyMovieStreamContext_020a9274(void *context)
{
    releaseMovieDecodeContext_020aa124(context);
    return context;
}
