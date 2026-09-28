extern int SoundMgr_IsState1();
extern void Loader_SleepIfBusy();

void SoundMgr_WaitLoaderIfState1_0204d6c0(void)
{
    if (SoundMgr_IsState1()) Loader_SleepIfBusy();
}
