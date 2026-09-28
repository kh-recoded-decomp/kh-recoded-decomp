extern int func_020bcd98(void *method, int arg);
extern int data_020bea84[];
struct HandlerTableEntry { char *handlerObject; int _pad; };
extern struct HandlerTableEntry data_020be930[];
extern struct HandlerTableEntry data_020be8d0[];

int dispatch_input_handler_pair_14_020bd084(int contextA, int contextB) {
    int handled = 0;
    void *primaryHandler = *(void **)(data_020be930[data_020bea84[0]].handlerObject + 0x14);
    if (contextA != 0) {
        handled = func_020bcd98(primaryHandler, contextA);
    }
    if (handled == 0) {
        void *secondaryHandler = *(void **)(data_020be8d0[data_020bea84[1]].handlerObject + 0x10);
        if (contextB != 0) {
            handled = func_020bcd98(secondaryHandler, contextB);
        }
    }
    return handled;
}
