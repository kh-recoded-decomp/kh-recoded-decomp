/* Ends a key-sharing operation, then passes its returned object to two follow-up helpers and returns it.
 * Evidence: Call sequence and result flow in source.
 * Uncertainty: Exact role of the two follow-up calls is opaque.
 * Source: src/overlays/ov011/calls/func_ov011_0205d664.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern int WM_EndKeySharing_0x02032444();
extern void func_0204f480();
extern void func_0204f378();

int end_key_share_and_register_result_02063558(int context, int argument) {
    int resultObject = WM_EndKeySharing_0x02032444(context, argument, 0);
    func_0204f480(context, resultObject, 0);
    func_0204f378(context, resultObject, 0);
    return resultObject;
}
