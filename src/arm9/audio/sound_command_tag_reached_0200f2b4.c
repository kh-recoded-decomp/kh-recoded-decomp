/* Compares a requested tag with the current sound command tag using wraparound-aware unsigned sequence ordering.
 * Evidence: Interrupt-protected read of command manager tag and half-range comparisons in source.
 * Uncertainty: Return convention is boolean-like but callers determine its label.
 * Source: src/calls/func_02008a14.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int interruptState);
extern unsigned int data_02057c50[];

int sound_command_tag_reached_0200f2b4(unsigned int requestedTag) {
    int interruptState;
    int isReached;
    unsigned int currentTag;
    interruptState = OS_DisableInterrupts();
    currentTag = data_02057c50[1];
    if (requestedTag > currentTag) {
        if ((requestedTag - currentTag) < 0x80000000u) {
            isReached = 0;
        } else {
            isReached = 1;
        }
    } else {
        if ((currentTag - requestedTag) < 0x80000000u) {
            isReached = 1;
        } else {
            isReached = 0;
        }
    }
    OS_RestoreInterrupts(interruptState);
    return isReached;
}
