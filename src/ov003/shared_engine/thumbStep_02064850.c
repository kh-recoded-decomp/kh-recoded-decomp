extern int Ov012_IsGlobalByte8be1Clear();
int thumbStep_02064850(void) {
    if (Ov012_IsGlobalByte8be1Clear() != 0) return 1;
    return 0;
}
