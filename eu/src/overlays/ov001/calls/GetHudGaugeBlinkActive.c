extern int gFieldHudGaugeState;

int GetHudGaugeBlinkActive(int arg0) {
    return *(int *)(*(int *)&gFieldHudGaugeState + arg0 * 0x18 + 0x7c);
}
