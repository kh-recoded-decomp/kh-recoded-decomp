/* Mutes and releases the movie audio channel, waiting for queued sound commands. Evidence: Source implementation directly performs the described operations; see src/overlays/ov024/calls/func_ov024_020841c4.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/overlays/ov024/calls/func_ov024_020841c4.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void SND_SetChannelVolume(int ch, int unknown_argument_a, int unknown_argument_b);
extern unsigned int func_0200f288(void);
extern void func_0200f080(int unknown_argument_a);
extern void SND_WaitForCommandProc(unsigned int sound_command_tag);
extern void SND_StopTimer(int ch, int unknown_argument_a, int unknown_argument_b, int unknown_argument_c);
extern void SND_UnlockChannel(int ch, int unknown_argument_a);

void StopMovieAudio_020a7ed8(void) {
    unsigned int sound_command_tag;

    SND_SetChannelVolume(3, 0, 0);
    sound_command_tag = func_0200f288();
    func_0200f080(1);
    SND_WaitForCommandProc(sound_command_tag);
    SND_StopTimer(3, 0, 0, 0);
    SND_UnlockChannel(3, 0);
    func_0200f080(1);
}
