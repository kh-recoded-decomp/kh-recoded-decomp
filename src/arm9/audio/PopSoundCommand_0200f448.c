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
