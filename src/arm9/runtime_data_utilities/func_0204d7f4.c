/* Updates a 16-bit value in a type-3 record or creates/sets a record when absent. Evidence: Source implementation directly performs the described operations; see src/calls/func_020336a4.c. Uncertainty: The exact game-specific role is unresolved. Recovered from Days source src/calls/func_020336a4.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern unsigned char *func_0204cf58(int new_value);
extern void func_0204ce84(int input_value, int arg1, int arg2);

void func_0204d7f4(int new_value) {
    unsigned char *current_record = func_0204cf58(0);

    if (current_record == 0 || current_record[0] != 3) {
        func_0204ce84(3, 0, (unsigned short)new_value);
        return;
    }

    *(unsigned short *)(current_record + 2) = new_value;
}
