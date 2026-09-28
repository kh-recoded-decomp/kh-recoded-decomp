extern int func_020baaf8();
extern int data_020be79c;

void func_ov039_020bb6e8(void) {
    int (*f)(void) = ((int (**)(void))&data_020be79c)[func_020baaf8()];
    if (f != 0) {
        f();
    }
}
