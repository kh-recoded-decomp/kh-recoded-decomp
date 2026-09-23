/* Behavior: Calls the currently selected menu callback when a valid selection exists.
 * Inputs/outputs and evidence: Uses dispatch index 1 to select a table entry; returns 1 for no selection, otherwise callback result.
 * Uncertainty: Callback semantics are unknown; table and selected index are identified from code structure.
 * Source: khdays-decomp/src/overlays/ov008/calls/func_ov008_02051458.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
typedef int (*MenuHandlerCallback)(int event);

typedef struct {
    void *callbackObject;
    int padding;
} MenuHandlerEntry;

extern int data_020bea84[];
extern MenuHandlerEntry data_020be8d0[];

int dispatchSelectedMenuCallback_020bcfcc(int event)
{
    int handled = 1;
    int selectedIndex = data_020bea84[1];

    if (selectedIndex != -1) {
        handled = (*(MenuHandlerCallback *)data_020be8d0[selectedIndex].callbackObject)(event);
    }

    return handled;
}
