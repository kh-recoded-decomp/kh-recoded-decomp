extern int func_020bcd98(void *method, int event);
extern int data_020bea84[];
struct MenuHandlerEntry { char *object; int padding; };
extern struct MenuHandlerEntry data_020be930[];
extern struct MenuHandlerEntry data_020be8d0[];

int dispatchMenuHandlerPairAt1c_020bd174(int firstEvent, int secondEvent) {
    int handled = 0;
    void *firstMethod = *(void **)(data_020be930[data_020bea84[0]].object + 0x1c);
    if (firstEvent != 0) {
        handled = func_020bcd98(firstMethod, firstEvent);
    }
    if (handled == 0) {
        void *secondMethod = *(void **)(data_020be8d0[data_020bea84[1]].object + 0x18);
        if (secondEvent != 0) {
            handled = func_020bcd98(secondMethod, secondEvent);
        }
    }
    return handled;
}
