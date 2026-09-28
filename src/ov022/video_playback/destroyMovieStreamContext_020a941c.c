/* Ghidra-derived original C for ov022:0x020a941c.
 * Delegates resource release, then returns the original context pointer.
 */
extern void releaseMovieDecodeContext_020a99dc(void *context);

void *destroyMovieStreamContext_020a941c(void *context)
{
    releaseMovieDecodeContext_020a99dc(context);
    return context;
}
