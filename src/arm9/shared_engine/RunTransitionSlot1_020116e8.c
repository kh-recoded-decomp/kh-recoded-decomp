extern int Ov105_PollDeviceStatus(void);
extern void Ov105_SetCommandArg(int slot, int arg);
extern int Ov105_WMi_SendCommand(int slot, int flag);

int RunTransitionSlot1_020116e8(int arg) {
    int r = Ov105_PollDeviceStatus();
    if (r != 0) {
        return r;
    }
    Ov105_SetCommandArg(1, arg);
    r = Ov105_WMi_SendCommand(1, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
