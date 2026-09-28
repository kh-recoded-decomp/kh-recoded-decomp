int Strlen_02021e44(const unsigned char *str)
{
    int length = -1;
    unsigned char c;

    do {
        c = *str;
        length++;
        str++;
    } while (c != 0);

    return length;
}
