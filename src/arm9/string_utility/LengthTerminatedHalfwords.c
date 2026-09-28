int LengthTerminatedHalfwords(unsigned short *text) {
    int length = -1;
    unsigned short character;
    do {
        character = *text++;
        length++;
    } while (character != 0);
    return length;
}
