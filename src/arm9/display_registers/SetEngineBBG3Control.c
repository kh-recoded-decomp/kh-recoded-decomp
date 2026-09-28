/* Based on src/auto/func_02024030.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
void SetEngineBBG3Control(int size, int colorMode, int screenBase, int charBase)
{
    volatile unsigned short *backgroundControl = (volatile unsigned short *)0x0400100e;
    unsigned short previousControl = *backgroundControl;
    *backgroundControl = (previousControl & 0x43) | (size << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2);
}
