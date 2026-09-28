/* updateMovieStreamLeadTime_020a8efc: update a movie stream's presentation lead according to its synchronization mode.
 *
 * Mode 0 clears the lead; mode 1 either adopts the shared lead or computes half of the
 * difference between the stream stamp and current clock, clamped at zero; mode 2 uses the full
 * stamp-to-clock difference. Observed BK9E fields are mode +0x64, follower flag +0x50, stream
 * stamp +0x34, and lead +0x4c.
 *
 * Adapted from CC0 MobiClip source in Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, src/overlays/ov024/calls/func_ov024_02083a9c.c.
 */
extern int func_ov022_020a8ce0(int stream);
extern int data_ov022_020b7df0[];

void updateMovieStreamLeadTime_020a8efc(int stream) {
    int lead;

    switch (*(int *)(stream + 0x64)) {
    case 0:
        *(int *)(stream + 0x4c) = 0;
        break;
    case 1:
        if (*(int *)(stream + 0x50) == 0) {
            lead = (*(int *)(stream + 0x34) - func_ov022_020a8ce0(stream)) / 2;
            *(int *)(stream + 0x4c) = lead;
            if (lead < 0) {
                *(int *)(stream + 0x4c) = 0;
            }
            data_ov022_020b7df0[0] = *(int *)(stream + 0x4c);
        } else {
            *(int *)(stream + 0x4c) = data_ov022_020b7df0[0];
        }
        break;
    case 2:
        *(int *)(stream + 0x4c) = *(int *)(stream + 0x34) - func_ov022_020a8ce0(stream);
        break;
    }
}
