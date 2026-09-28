/* Unlinks cleanup records whose callback or argument lies inside the overlay image, invokes the collected callbacks, and repeats until none remain.
 * Uncertainty: This identifies a shared library operation; the particular scene, asset or gameplay caller using it is not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fs/calls/FS_EndOverlay.c.
 * Original routine: FS_EndOverlay. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern char *data_0205fdc0;

/* Runs (and unregisters) every destructor whose entry lives inside the overlay being unloaded.
 * Rescans from scratch after each pass because a destructor may register more of them. */
void FS_RunOverlayCleanupCallbacks_0200bc64(char *overlay) {
    char *collected;
    char *last;
    unsigned int start;
    unsigned int end;
    char *prev;
    char *listHead;
    char *node;
    char *next;
    int enabled;
    for (;;) {
        start = *(unsigned int *)(overlay + 4);
        end = start + (*(int *)(overlay + 8) + *(int *)(overlay + 0xc));
        collected = 0;
        last = collected;
        enabled = OS_DisableInterrupts();
        prev = collected;
        listHead = *(char **)&data_0205fdc0;
        node = listHead;
        while (node != 0) {
            unsigned int arg = *(unsigned int *)(node + 8);
            unsigned int fn;
            next = *(char **)node;
            fn = *(unsigned int *)(node + 4);
            if ((arg == 0 && fn >= start && fn < end) || (arg >= start && arg < end)) {
                if (last != 0) {
                    *(char **)last = node;
                } else {
                    collected = node;
                }
                if (listHead == node) {
                    *(char **)&data_0205fdc0 = next;
                    listHead = next;
                }
                *(char **)node = 0;
                last = node;
                if (prev != 0) {
                    *(char **)prev = next;
                }
            } else {
                prev = node;
            }
            node = next;
        }
        OS_RestoreInterrupts(enabled);
        if (collected == 0) {
            return;
        }
        do {
            void (*fn)(void *) = *(void (**)(void *))(collected + 4);
            next = *(char **)collected;
            if (fn != 0) {
                fn(*(void **)(collected + 8));
            }
            collected = next;
        } while (next != 0);
    }
}
