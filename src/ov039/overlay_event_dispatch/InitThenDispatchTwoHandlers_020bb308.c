extern int data_ov039_020bea00;
extern void func_ov039_020baf1c(void);
extern void func_ov039_020bcf20(int arg0);
extern void func_ov039_020bd054(int arg0);

void InitThenDispatchTwoHandlers_020bb308(void)
{
    func_ov039_020baf1c();
    func_ov039_020bcf20(*(int *)(data_ov039_020bea00 + 0xc998));
    func_ov039_020bd054(*(int *)(data_ov039_020bea00 + 0xc99c));
}
