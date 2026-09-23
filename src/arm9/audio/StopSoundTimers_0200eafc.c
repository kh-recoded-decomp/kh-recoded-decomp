/* Invalidates selected alarm IDs and queues a sound timer stop command. Evidence: Source implementation directly performs the described operations; see src/calls/SND_StopTimer.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/calls/SND_StopTimer.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void SNDi_IncAlarmId(int unknown_argument_n);
extern void PushCommand_impl(int cmd, int unknown_argument_a, int unknown_argument_b, int unknown_argument_c, int unknown_argument_d);

void StopSoundTimers_0200eafc(unsigned int channel_mask, unsigned int capture_mask, unsigned int alarm_mask, unsigned int reserved_value) {
    int alarm_index;
    unsigned int remaining_alarm_mask = alarm_mask;

    for (alarm_index = 0; alarm_index < 8 && remaining_alarm_mask != 0; alarm_index++, remaining_alarm_mask >>= 1) {
        if (remaining_alarm_mask & 1) {
            SNDi_IncAlarmId(alarm_index);
        }
    }

    PushCommand_impl(0xd, channel_mask, capture_mask, alarm_mask, reserved_value);
}
