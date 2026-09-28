extern void SNDi_SetTrackParam(int player, unsigned int trackMask, int param, int value, int immediate);

void SND_SetTrackPan_0200ea90(int player, unsigned int trackMask, int pan) {
    SNDi_SetTrackParam(player, trackMask, 9, pan, 1);
}
