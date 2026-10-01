extern int data_020c3560;

int GetPlayerFlagRecord_020c2800(int arg0) {
    return (int)&data_020c3560 + arg0 * 12;
}
