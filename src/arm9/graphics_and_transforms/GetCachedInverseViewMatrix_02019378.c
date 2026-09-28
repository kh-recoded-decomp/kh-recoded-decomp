extern void MTX_Inverse43(const void *src, void *dst);

extern struct { char _0[0xd4]; int dirty_flags; } graphics_state;
extern char view_matrix;
extern char inverse_view_matrix;

void *GetCachedInverseViewMatrix_02019378(void) {
    if (!(graphics_state.dirty_flags & 8)) {
        MTX_Inverse43(&view_matrix, &inverse_view_matrix);
        graphics_state.dirty_flags |= 8;
    }
    return &inverse_view_matrix;
}
