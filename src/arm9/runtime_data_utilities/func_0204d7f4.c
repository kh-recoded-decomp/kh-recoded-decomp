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
