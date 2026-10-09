extern void QueueSoundCommandForArc(int soundId);
extern void PlaySoundChecked(int soundId, int index);

void QueueAndPlaySound(int soundId, int index)
{
    QueueSoundCommandForArc(soundId);
    PlaySoundChecked(soundId, index);
}
