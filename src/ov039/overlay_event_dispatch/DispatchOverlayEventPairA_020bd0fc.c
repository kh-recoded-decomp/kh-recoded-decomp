/* Tries one selected handler for an event, then a second handler if the first returns unhandled. Evidence: Source implementation directly performs the described operations; see src/overlays/ov008/calls/func_ov008_02051578.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/overlays/ov008/calls/func_ov008_02051578.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern int func_020bcd98(void *method, int handler_argument);
extern int active_handler_indices[];
struct ov008_disp { char *obj; int _pad; };
extern struct ov008_disp primary_handler_table[];
extern struct ov008_disp secondary_handler_table[];

int DispatchOverlayEventPairA_020bd0fc(int first_event, int second_event) {
    int handled = 0;
    void *first_handler_method = *(void **)(primary_handler_table[active_handler_indices[0]].obj + 0x18);
    if (first_event != 0) {
        handled = func_020bcd98(first_handler_method, first_event);
    }
    if (handled == 0) {
        void *second_handler_method = *(void **)(secondary_handler_table[active_handler_indices[1]].obj + 0x14);
        if (second_event != 0) {
            handled = func_020bcd98(second_handler_method, second_event);
        }
    }
    return handled;
}
