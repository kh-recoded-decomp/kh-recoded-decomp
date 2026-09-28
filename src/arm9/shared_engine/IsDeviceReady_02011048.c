extern char data_020597fc[];

int IsDeviceReady_02011048(void) {
    if (*(unsigned short *)data_020597fc != 0) {
        return 0;
    }
    return 3;
}
