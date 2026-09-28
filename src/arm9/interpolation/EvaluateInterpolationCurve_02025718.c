/* Computes one of four fixed-point interpolation curves using division and a signed 16-bit sine table.
 * BK9E indexes the sine table at two bytes per entry, unlike the paired sine/cosine reference table.
 * Adapted CC0 C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, src/calls/func_0202136c.c. */


typedef struct {
    short sin;
    short cos;
} SinCos;

extern int   func_01ff9c84(int a, int b);
extern int   func_02023dbc(int a, int b);
extern short data_0205356c[];

int EvaluateInterpolationCurve_02025718(int param_1, unsigned int param_2, int param_3)
{
    int iVar1;

    iVar1 = param_2 - param_3;
    switch (param_1) {
    case 2:
        return func_01ff9c84(iVar1 * 0x1000, param_2 << 0xc);
    case 3:
        iVar1 = func_02023dbc(iVar1 * 0x8000, param_2) - 0x4000;
        if (iVar1 < 0) {
            iVar1 = iVar1 + 0x10000;
        }
        return (data_0205356c[iVar1 >> 4] + 0x1000) / 2;
    case 4:
        iVar1 = func_02023dbc(iVar1 * 0x8000, param_2 << 1) - 0x4000;
        if (iVar1 < 0) {
            iVar1 = iVar1 + 0x10000;
        }
        return data_0205356c[iVar1 >> 4] + 0x1000;
    case 5:
        iVar1 = func_02023dbc(param_3 << 0xf, param_2 << 1) + 0x4000;
        if (iVar1 < 0) {
            iVar1 = iVar1 + 0x10000;
        }
        param_1 = data_0205356c[iVar1 >> 4];
    }
    return param_1;
}
