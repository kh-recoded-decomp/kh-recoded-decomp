typedef int BOOL;

#define OS_ARENA_MAIN       0
#define OS_ARENA_MAINEX     2
#define OS_ARENA_ITCM       3
#define OS_ARENA_DTCM       4
#define OS_ARENA_SHARED     5
#define OS_ARENA_WRAM_MAIN  6

extern void *func_020029d0(int nArena);
extern void *func_02002ab4(int nArena);
extern void OS_SetArenaHi(int nArena, void *pAddress);
extern void OS_SetArenaLo(int nArena, void *pAddress);

extern BOOL data_02044588;

void OS_InitArena(void)
{
    if (data_02044588) {
        return;
    }
    data_02044588 = 1;

    OS_SetArenaHi(OS_ARENA_MAIN, func_020029d0(OS_ARENA_MAIN));
    OS_SetArenaLo(OS_ARENA_MAIN, func_02002ab4(OS_ARENA_MAIN));

    OS_SetArenaLo(OS_ARENA_MAINEX, (void *)0);
    OS_SetArenaHi(OS_ARENA_MAINEX, (void *)0);

    OS_SetArenaHi(OS_ARENA_ITCM, func_020029d0(OS_ARENA_ITCM));
    OS_SetArenaLo(OS_ARENA_ITCM, func_02002ab4(OS_ARENA_ITCM));

    OS_SetArenaHi(OS_ARENA_DTCM, func_020029d0(OS_ARENA_DTCM));
    OS_SetArenaLo(OS_ARENA_DTCM, func_02002ab4(OS_ARENA_DTCM));

    OS_SetArenaHi(OS_ARENA_SHARED, func_020029d0(OS_ARENA_SHARED));
    OS_SetArenaLo(OS_ARENA_SHARED, func_02002ab4(OS_ARENA_SHARED));

    OS_SetArenaHi(OS_ARENA_WRAM_MAIN, func_020029d0(OS_ARENA_WRAM_MAIN));
    OS_SetArenaLo(OS_ARENA_WRAM_MAIN, func_02002ab4(OS_ARENA_WRAM_MAIN));
}
