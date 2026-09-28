extern int func_02063fe4(void);
extern int func_020a8918(void);

int func_ov003_020647f0(int unused, int frames) {
    int buffered;

    if (func_02063fe4() == 0) {
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
