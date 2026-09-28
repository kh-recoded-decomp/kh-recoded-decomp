extern void releaseMovieDecodeContext_020a99dc(void *context);

void *destroyMovieStreamContext_020a941c(void *context)
{
    releaseMovieDecodeContext_020a99dc(context);
    return context;
}
