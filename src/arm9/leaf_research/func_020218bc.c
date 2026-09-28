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
