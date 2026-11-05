extern void DestroyTaskObjectWrapper();
extern int data_ov022_020b7c00;

void DestroyMovieSceneTaskIfSet(void) {
    int v = data_ov022_020b7c00;
    if (v == -1) {
        return;
    }
    DestroyTaskObjectWrapper(v);
}
