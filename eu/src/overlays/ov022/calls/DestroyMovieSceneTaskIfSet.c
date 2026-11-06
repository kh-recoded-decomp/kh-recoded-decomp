extern void DestroyTaskObjectWrapper();
extern int gMovieSceneTaskHandle;

void DestroyMovieSceneTaskIfSet(void) {
    int v = gMovieSceneTaskHandle;
    if (v == -1) {
        return;
    }
    DestroyTaskObjectWrapper(v);
}
