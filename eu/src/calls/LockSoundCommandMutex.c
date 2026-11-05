struct OSMutex;
extern struct OSMutex data_02057c38;
extern void OS_LockMutex(struct OSMutex *mutex);

void LockSoundCommandMutex(void)
{
    OS_LockMutex(&data_02057c38);
}
