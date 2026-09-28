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
