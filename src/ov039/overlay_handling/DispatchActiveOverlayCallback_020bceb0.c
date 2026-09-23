/* Calls the callback at the active overlay index, or returns the default success value. Evidence: Source implementation directly performs the described operations; see src/overlays/ov008/calls/func_ov008_0205137c.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/overlays/ov008/calls/func_ov008_0205137c.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
typedef int (*OverlayEventCallback)(int event_argument);

typedef struct {
    void *object;
    int unused;
} OverlayCallbackEntry;

extern int active_handler_indices[];
extern OverlayCallbackEntry handler_table[];

int DispatchActiveOverlayCallback_020bceb0(int event_argument)
{
    int callback_result = 1;
    int active_callback_index = active_handler_indices[0];

    if (active_callback_index != -1) {
        callback_result = (*(OverlayEventCallback *)handler_table[active_callback_index].object)(event_argument);
    }

    return callback_result;
}
