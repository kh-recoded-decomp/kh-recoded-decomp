char *strchr_020220f0(char *s, int c)
{
    unsigned char target = (unsigned char)c;
    unsigned char ch;

    ch = *s++;
    while (ch != 0) {
        if (ch == target) {
            return s - 1;
        }
        ch = *s++;
    }

    if (target != 0) {
        return 0;
    }
    return s - 1;
}
