/* MobiClip chunk size helper, hand-written ARM. */

extern void func_020ab444(void);

asm void GetMovieChunkType1Size_020aac34(void)
{
    b         func_020ab444
    andeq     r0, r0, r0
    andeq     r0, r0, r0
    andeq     r0, r0, r0
    mov       r6, #0x20
    add       r7, r3, #0x200
    mov       r8, #0
    mov       r9, #0
    mov       r10, #0
    mov       r11, #0
L028:
    stmia     r7!, {r8, r9, r10, r11}
    subs      r6, r6, #1
    bne       L028
    mov       pc, lr
}
