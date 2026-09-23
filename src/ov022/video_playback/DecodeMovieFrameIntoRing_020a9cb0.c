/* Decodes a movie chunk into a ring buffer and advances six cursors. Evidence: Source implementation directly performs the described operations; see src/overlays/ov024/calls/func_ov024_020859d4.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/overlays/ov024/calls/func_ov024_020859d4.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
int DecodeMovieFrameIntoRing_020a9cb0(int movie_context) {
    int header_skip_bytes;
    int plane_index;

    if ((unsigned int)*(int *)(movie_context + 0x9c) > (unsigned int)*(int *)(movie_context + 0xa0)) {
        return 0;
    }

    if ((*(unsigned short *)**(int **)(movie_context + 0x34) & 0x8000) != 0) {
        *(int *)(movie_context + 0xa4) = 1;
        header_skip_bytes = 4;
    } else {
        header_skip_bytes = 0;
        *(int *)(movie_context + 0xa4) = 0;
    }

    **(int **)(movie_context + 0x34) += (*(int (**)(int))(movie_context + 0x38))(*(int *)(movie_context + 0x34));

    if (*(signed char *)(movie_context + 8) == 0x4e && *(signed char *)(movie_context + 9) == 0x33) {
        **(int **)(movie_context + 0x34) += header_skip_bytes;
    }

    *(int *)(*(int *)(movie_context + 0x64) + *(int *)(movie_context + 0xac) * 4) =
        *(int *)(*(int *)(movie_context + 0x34) + 0x3b4);
    *(int *)(movie_context + 0xcc) = 0;
    *(int *)(movie_context + 0xd0) = 0;

    for (plane_index = 0; plane_index < 6; plane_index++) {
        ((int *)movie_context)[plane_index + 0x2b] = ((int *)movie_context)[plane_index + 0x2b] + 1;
        if (*(int *)(movie_context + 0xa8) == ((int *)movie_context)[plane_index + 0x2b]) {
            ((int *)movie_context)[plane_index + 0x2b] = 0;
        }
    }

    *(int *)(movie_context + 0xa0) = *(int *)(movie_context + 0xa0) + 1;
    return 1;
}
