extern int data_020a0460;

int Session_Exists_02063a24(void) {
    return *(int *)&data_020a0460 != 0;
}
