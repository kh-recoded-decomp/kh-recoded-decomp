/* Behavior: Tries two currently selected menu handler methods in order.
 * Inputs/outputs and evidence: Calls the first handler when its argument is nonzero; if unhandled, calls the second handler when its argument is nonzero.
 * Uncertainty: The handler method offsets and tables are known, but event meaning is not.
 * Source: khdays-decomp/src/overlays/ov008/calls/func_ov008_020518c0.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
extern int func_020bcd98(void *method, int event);
extern int data_020bea84[];
struct MenuHandlerEntry { char *object; int padding; };
extern struct MenuHandlerEntry data_020be930[];
extern struct MenuHandlerEntry data_020be8d0[];

int dispatchMenuHandlerPairAt34_020bd444(int firstEvent, int secondEvent) {
    int handled = 0;
    void *firstMethod = *(void **)(data_020be930[data_020bea84[0]].object + 0x34);
    if (firstEvent != 0) {
        handled = func_020bcd98(firstMethod, firstEvent);
    }
    if (handled == 0) {
        void *secondMethod = *(void **)(data_020be8d0[data_020bea84[1]].object + 0x30);
        if (secondEvent != 0) {
            handled = func_020bcd98(secondMethod, secondEvent);
        }
    }
    return handled;
}
