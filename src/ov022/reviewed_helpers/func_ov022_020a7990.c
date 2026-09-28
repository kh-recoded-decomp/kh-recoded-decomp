extern int func_020a73d8(void);
extern int func_020a8918(void);

int func_ov022_020a7990(int unused, int frames) {
    int buffered;

    if (func_020a73d8() == 0) {
        return 1;
    }
    if (frames == 0) {
        return 0;
    }

    buffered = func_020a8918();
    if (buffered < frames) {
        return 0;
    }
    if (buffered >= frames) {
        return 1;
    }
    return 1;
}
