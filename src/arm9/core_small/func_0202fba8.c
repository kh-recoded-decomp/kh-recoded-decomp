extern void func_0202f808(void *mtx);
extern void MTX_MultVec33(void *out, void *mtx, void *in);

void func_0202fba8(void *in_vec, int unused, void *out_vec)
{
    int mtx_local[9];
    func_0202f808(&mtx_local);
    MTX_MultVec33(out_vec, &mtx_local, in_vec);
}
