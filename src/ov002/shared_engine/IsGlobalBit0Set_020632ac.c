extern unsigned short data_02060500;

int IsGlobalBit0Set_020632ac(void) {
    return (data_02060500 & 1) != 0;
}
