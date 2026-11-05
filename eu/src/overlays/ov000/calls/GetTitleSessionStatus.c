extern int data_ov000_02063a08;

int GetTitleSessionStatus(void) {
    return *(int *)(*(int *)&data_ov000_02063a08 + 4);
}
