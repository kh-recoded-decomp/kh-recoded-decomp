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
