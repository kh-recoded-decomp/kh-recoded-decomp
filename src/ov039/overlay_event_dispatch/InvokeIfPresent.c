/* Recovered from src/overlays/ov008/auto/func_ov008_020512e0.c; CC0-1.0, revision ab832f38b943c15f461228968a89002e1a99c03e. */
int InvokeIfPresent(void *callback, void *argument) {
    int r = 0;
    if (callback) {
        ((void (*)(void *))callback)(argument);
        r = 1;
    }
    return r;
}
