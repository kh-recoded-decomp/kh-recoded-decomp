/* Raises both movie PCM channel volumes to 127 and flushes the sound commands.
 * Installed as the sound alarm callback by startStereoPcmStream_020a7db4. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov024/calls/func_ov024_02084084.c. */

extern void func_0200ebe0(int ch, int vol, int flags);
extern void func_0200f080(int);
void EnableMovieAudioChannels_020a7d94(void) {
    func_0200ebe0(3, 0x7f, 0);
    func_0200f080(1);
}
