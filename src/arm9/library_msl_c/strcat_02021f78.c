char *strcat_02021f78(char *dest, const char *src)
{
    unsigned char *p = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    while (*p++ != 0) {
    }
    p--;

    while ((*p++ = *s++) != 0) {
    }

    return dest;
}
