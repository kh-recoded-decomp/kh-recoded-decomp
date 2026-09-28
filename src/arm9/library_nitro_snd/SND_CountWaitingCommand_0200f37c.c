extern int SND_CountReservedCommand(void);
extern int func_0200f340(void);

int SND_CountWaitingCommand_0200f37c(void) {
    int reserved = SND_CountReservedCommand();
    return 0x100 - reserved - func_0200f340();
}
