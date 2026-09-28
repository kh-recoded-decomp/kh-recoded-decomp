extern void releaseMovieDecodeContext_020aa124(void *context);

void *destroyMovieStreamContext_020a9274(void *context)
{
    releaseMovieDecodeContext_020aa124(context);
    return context;
}
