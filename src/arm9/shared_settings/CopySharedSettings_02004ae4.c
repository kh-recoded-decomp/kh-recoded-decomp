/* Copies selected fields and UTF-16-sized blocks from the shared settings record at 0x02fffc80 into a caller buffer.
 * The BK9E literal is 0x02fffc80; fixed field loads, bit masks, and two 16-bit copy calls establish the copy operation.
 * Adapted CC0 C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, src/calls/func_02003a20.c. */
extern void func_01ff869c(const void *src, void *dst, unsigned int size);

typedef struct {
    unsigned char pad0[0x64];
    unsigned short bits : 3;
    unsigned short : 13;
} SrcA;

typedef struct {
    unsigned char pad0[2];
    unsigned char bits4 : 4;
    unsigned char : 4;
} SrcB;

void CopySharedSettings_02004ae4(unsigned char *r0) {
    unsigned char *p = (unsigned char *)0x02fffc80;
    r0[0] = (unsigned char)((SrcA *)p)->bits;
    r0[1] = ((SrcB *)p)->bits4;
    r0[2] = p[3];
    r0[3] = p[4];
    *(unsigned short *)(r0 + 0x1a) = (unsigned short)p[0x1a];
    *(unsigned short *)(r0 + 0x52) = (unsigned short)p[0x50];
    func_01ff869c(p + 6, r0 + 4, 0x14);
    func_01ff869c(p + 0x1c, r0 + 0x1c, 0x34);
    *(unsigned short *)(r0 + 0x18) = 0;
    *(unsigned short *)(r0 + 0x50) = 0;
}
