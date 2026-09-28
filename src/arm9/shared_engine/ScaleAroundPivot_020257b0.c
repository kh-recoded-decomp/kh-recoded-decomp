extern int FX_Mul();

int ScaleAroundPivot_020257b0(int arg0, int arg1, int arg2) {
    return FX_Mul(arg1 - arg2, arg0) + arg2;
}
