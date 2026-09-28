extern int func_020bcd98(void *method, int handler_argument);
extern int active_handler_indices[];
struct ov008_disp { char *obj; int _pad; };
extern struct ov008_disp primary_handler_table[];
extern struct ov008_disp secondary_handler_table[];

int DispatchOverlayEventPairC_020bd3cc(int first_event, int second_event) {
    int handled = 0;
    void *first_handler_method = *(void **)(primary_handler_table[active_handler_indices[0]].obj + 0x30);
    if (first_event != 0) {
        handled = func_020bcd98(first_handler_method, first_event);
    }
    if (handled == 0) {
        void *second_handler_method = *(void **)(secondary_handler_table[active_handler_indices[1]].obj + 0x2c);
        if (second_event != 0) {
            handled = func_020bcd98(second_handler_method, second_event);
        }
    }
    return handled;
}
