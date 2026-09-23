/* Drops the next decoded movie frame by advancing a counter and ring index. Evidence: Source implementation directly performs the described operations; see src/overlays/ov024/calls/func_ov024_02085c3c.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/overlays/ov024/calls/func_ov024_02085c3c.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
int DropDecodedMovieFrame_020a9f18(int movie_context) {
    unsigned int emitted_frame_count = *(unsigned int *)(movie_context + 0x9c);
    int ring_index;

    if (emitted_frame_count >= *(unsigned int *)(movie_context + 0xa0)) {
        return 0;
    }
    *(unsigned int *)(movie_context + 0x9c) = emitted_frame_count + 1;
    ring_index = *(int *)(movie_context + 0xc4) + 1;
    *(int *)(movie_context + 0xc4) = ring_index;
    if (ring_index == *(int *)(movie_context + 0xa8)) {
        *(int *)(movie_context + 0xc4) = 0;
    }
    return 1;
}
