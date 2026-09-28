/* Clears a stream fader before its target and duration are configured.
 * Field interpretation is supported by the stream preparation caller and
 * CC0 Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e,
 * libs/nns/snd/auto/func_0201e12c.c. */
typedef struct StreamFader {
    int origin;
    int target;
    int counter;
    int frame;
} StreamFader;

void InitializeStreamFader_020218bc(StreamFader *fader) {
    fader->origin = fader->target = 0;
    fader->counter = fader->frame = 0;
}
