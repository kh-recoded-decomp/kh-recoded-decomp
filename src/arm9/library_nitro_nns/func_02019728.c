/* Returns optional x/y/width/height bytes from cached viewport word.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/func_02015ca0.c.
 * Original routine: func_02015ca0. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct NNSG3dGlb {
    u8 pad00_8c[0x8c];
    u32 prmViewPort;
} NNSG3dGlb;

extern NNSG3dGlb data_0205a924;

void GetGeometryViewport_02019728(int *px1, int *py1, int *px2, int *py2)
{
    if (px1)
        *px1 = (int)(data_0205a924.prmViewPort & 0xff);
    if (py1)
        *py1 = (int)((data_0205a924.prmViewPort >> 8) & 0xff);
    if (px2)
        *px2 = (int)((data_0205a924.prmViewPort >> 16) & 0xff);
    if (py2)
        *py2 = (int)((data_0205a924.prmViewPort >> 24) & 0xff);
}
