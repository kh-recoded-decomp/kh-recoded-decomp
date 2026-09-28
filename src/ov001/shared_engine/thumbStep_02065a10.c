extern int Ov012_IsGlobalByte8be1Clear();
int thumbStep_02065a10(void) {
    if (Ov012_IsGlobalByte8be1Clear() != 0) return 1;
    return 0;
}
