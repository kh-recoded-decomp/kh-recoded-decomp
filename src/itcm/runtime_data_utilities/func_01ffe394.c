/* Conditionally emits a text-related operation from flags and advances a byte cursor; exact encoding unknown. Evidence: Source implementation directly performs the described operations; see src/calls/func_01ffbbac.c. Uncertainty: The exact game-specific role is unresolved. Recovered from Days source src/calls/func_01ffbbac.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void func_01ffcedc(int operation, unsigned char encoded_byte);

void func_01ffe394(int *text_cursor) {
    int text_flags = text_cursor[2];

    if ((text_flags & 0x200) == 0 && (text_flags & 1) != 0 && (text_flags & 0x100) == 0) {
        func_01ffcedc(0x14, *(unsigned char *)(text_cursor[0] + 1));
    }

    text_cursor[0] += 2;
}
