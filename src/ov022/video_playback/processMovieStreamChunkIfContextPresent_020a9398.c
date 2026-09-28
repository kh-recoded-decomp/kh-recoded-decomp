/* Dispatches a movie context's pending stream chunk when the context is present.
 * Evidence: Ghidra shows this wrapper calls the chunk processor and returns whether it reports success.
 * Uncertainty: The caller-specific meaning of the four arguments is not established here.
 * Source: Reconstructed from build/ghidra/decompiled/ov022_func_ov022_020a9398.c; no upstream body copied.
 */
extern int processMovieStreamChunk_020a9f68(int movieContext, unsigned int outputBuffer,
                                            int unusedArgument, int copyOption);
int processMovieStreamChunkIfContextPresent_020a9398(int movieContext, unsigned int outputBuffer,
                                                      int unusedArgument, int copyOption)
{
    if (movieContext == 0) {
        return 0;
    }
    return processMovieStreamChunk_020a9f68(movieContext, outputBuffer,
                                            unusedArgument, copyOption) == 1;
}
