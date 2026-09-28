extern int WM_EndKeySharing_0x02032444();
extern void func_0204f480();
extern void func_0204f378();

int end_key_share_and_register_result_02063558(int context, int argument) {
    int resultObject = WM_EndKeySharing_0x02032444(context, argument, 0);
    func_0204f480(context, resultObject, 0);
    func_0204f378(context, resultObject, 0);
    return resultObject;
}
