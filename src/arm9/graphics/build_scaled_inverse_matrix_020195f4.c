/* Concatenates two matrices, applies the shared scale vector, and computes the inverse matrix.
 * Evidence: Matrix operation calls and data flow in source.
 * Uncertainty: Purpose of the resulting matrix in callers is not established.
 * Source: src/calls/func_02015b70.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void MTX_Concat43(const void *inputMatrixA, const void *inputMatrixB, void *outputMatrix);
extern void MTX_ScaleApply43(const void *sourceMatrix, void *destinationMatrix, int scaleX, int scaleY, int scaleZ);
extern void MTX_Inverse43(const void *sourceMatrix, void *inverseMatrix);

extern char data_0205a9b8[];
extern char data_0205a970[];
extern char data_0205aa2c[];
extern char data_0205aa5c[];
extern struct { char _0[0xc4]; int field_c4; int field_c8; int field_cc; } data_0205a924;

void build_scaled_inverse_matrix_020195f4(void) {
    MTX_Concat43(&data_0205a9b8, &data_0205a970, &data_0205aa2c);
    MTX_ScaleApply43(&data_0205aa2c, &data_0205aa2c, data_0205a924.field_c4, data_0205a924.field_c8, data_0205a924.field_cc);
    MTX_Inverse43(&data_0205aa2c, &data_0205aa5c);
}
