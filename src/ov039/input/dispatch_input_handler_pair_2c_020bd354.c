/* Dispatches two optional context pointers to selected handler methods at offsets +0x2c and +0x28.
 * Evidence: The Re:coded caller obtains two enabled handler objects and invokes this callback family
 * under input-source/button-mask checks; this function tries the second callback when the first returns zero.
 * Uncertainty: The handler objects' exact UI/page identity is not established by this function.
 * Source: src/overlays/ov008/calls/func_ov008_020517d0.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */

extern int func_020bcd98(void *method, int arg);
extern int data_020bea84[];
struct HandlerTableEntry { char *handlerObject; int _pad; };
extern struct HandlerTableEntry data_020be930[];
extern struct HandlerTableEntry data_020be8d0[];

int dispatch_input_handler_pair_2c_020bd354(int contextA, int contextB) {
    int handled = 0;
    void *primaryHandler = *(void **)(data_020be930[data_020bea84[0]].handlerObject + 0x2c);
    if (contextA != 0) {
        handled = func_020bcd98(primaryHandler, contextA);
    }
    if (handled == 0) {
        void *secondaryHandler = *(void **)(data_020be8d0[data_020bea84[1]].handlerObject + 0x28);
        if (contextB != 0) {
            handled = func_020bcd98(secondaryHandler, contextB);
        }
    }
    return handled;
}
