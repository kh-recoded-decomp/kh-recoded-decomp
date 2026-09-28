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
