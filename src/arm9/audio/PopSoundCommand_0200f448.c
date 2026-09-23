/* Pops and returns the first node from a free list with interrupts disabled. Evidence: Source implementation directly performs the described operations; see src/calls/func_02008ba4.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/calls/func_02008ba4.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int interrupt_state);
extern int *sound_command_manager[];

int *PopSoundCommand_0200f448(void) {
    int interrupt_state;
    int *free_node;
    int *next_free_node;
    interrupt_state = OS_DisableInterrupts();
    free_node = sound_command_manager[0];
    if (free_node == 0) {
        OS_RestoreInterrupts(interrupt_state);
        return 0;
    }
    next_free_node = (int *)*free_node;
    sound_command_manager[0] = next_free_node;
    if (next_free_node == 0) sound_command_manager[4] = 0;
    OS_RestoreInterrupts(interrupt_state);
    return free_node;
}
