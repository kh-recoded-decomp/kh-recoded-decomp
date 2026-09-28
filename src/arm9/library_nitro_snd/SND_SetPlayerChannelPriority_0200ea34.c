extern void *SNDi_SetPlayerParam();

void *SND_SetPlayerChannelPriority_0200ea34(int player, int prio) {
    return SNDi_SetPlayerParam(player, 4, prio, 1);
}
