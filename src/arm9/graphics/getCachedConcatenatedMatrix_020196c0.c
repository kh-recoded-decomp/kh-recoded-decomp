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
