asm void MTX_Copy43To33(const void *src, void *dst)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9}
    ldmia r0, {r2, r3, r4, r5, r6, r7, r8, r9, r12}
    stmia r1!, {r2, r5, r8}
    stmia r1!, {r3, r6, r9}
    stmia r1!, {r4, r7, r12}
    ldmia sp!, {r4, r5, r6, r7, r8, r9}
    bx lr
}
