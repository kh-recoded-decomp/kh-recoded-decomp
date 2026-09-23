/* Behavior: Lazily composes two matrices and returns the cached result.
 * Inputs/outputs and evidence: When the cache flag is clear, expands a 4 by 3 matrix, concatenates it with another matrix, sets the flag, and returns the result buffer.
 * Uncertainty: Matrix order follows the call arguments; the associated transform's purpose is unknown.
 * Source: khdays-decomp/src/calls/func_02015c38.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
extern void *func_02019378(void);
extern void *func_020195b4(void);
extern void MTX_Copy43To44_(const void *src, void *dst);
extern void MTX_Concat44(const void *firstMatrix, const void *secondMatrix, void *out);

extern struct { char padding[0xd4]; int flags; } data_0205a924;
extern char data_0205aafc[];

void *getCachedConcatenatedMatrix_020196c0(void) {
    int expandedMatrix[0x10];

    if (!(data_0205a924.flags & 0x40)) {
        void *sourceMatrix43 = func_02019378();
        void *sourceMatrix = func_020195b4();

        MTX_Copy43To44_(sourceMatrix43, expandedMatrix);
        MTX_Concat44(sourceMatrix, expandedMatrix, data_0205aafc);
        data_0205a924.flags |= 0x40;
    }

    return data_0205aafc;
}
