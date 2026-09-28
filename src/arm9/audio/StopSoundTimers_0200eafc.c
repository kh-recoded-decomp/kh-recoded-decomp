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
