extern void FX_DivAsync(int numer, int denom);
extern int FX_GetDivResult(void);

int FX_Div_01ff9c84(int numer, int denom) {
    FX_DivAsync(numer, denom);
    return FX_GetDivResult();
}
