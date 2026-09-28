int InvokeIfPresent(void *callback, void *argument) {
    int r = 0;
    if (callback) {
        ((void (*)(void *))callback)(argument);
        r = 1;
    }
    return r;
}
