extern void func_01ffcedc(int operation, unsigned char encoded_byte);

void func_01ffe394(int *text_cursor) {
    int text_flags = text_cursor[2];

    if ((text_flags & 0x200) == 0 && (text_flags & 1) != 0 && (text_flags & 0x100) == 0) {
        func_01ffcedc(0x14, *(unsigned char *)(text_cursor[0] + 1));
    }

    text_cursor[0] += 2;
}
