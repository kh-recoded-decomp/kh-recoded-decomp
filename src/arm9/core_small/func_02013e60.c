/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern void GX_BeginLoadTex(void);
extern void GX_LoadTex(void *src, unsigned offset, unsigned size);
extern void GX_EndLoadTex(void);

void func_02013e60(void *src, unsigned offset, unsigned size) {
    GX_BeginLoadTex();
    GX_LoadTex(src, offset, size);
    GX_EndLoadTex();
}
