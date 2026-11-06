struct OSMutex;
extern struct OSMutex gSoundCommandMutex;
extern void OS_LockMutex(struct OSMutex *mutex);

void LockSoundCommandMutex(void)
{
    OS_LockMutex(&gSoundCommandMutex);
}
