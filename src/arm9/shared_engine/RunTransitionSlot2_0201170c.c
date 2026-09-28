extern int Ov105_WMi_CheckStateEx(int a, int b);
extern void Ov105_SetCommandArg(int slot, int arg);
extern int Ov105_WMi_SendCommand(int slot, int flag);

int RunTransitionSlot2_0201170c(int arg) {
    int r = Ov105_WMi_CheckStateEx(1, 2);
    if (r != 0) {
        return r;
    }
    Ov105_SetCommandArg(2, arg);
    r = Ov105_WMi_SendCommand(2, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
