/* Lazily computes and returns a cached inverse 4x3 matrix. Evidence: Source implementation directly performs the described operations; see src/calls/func_020158e0.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/calls/func_020158e0.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
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
