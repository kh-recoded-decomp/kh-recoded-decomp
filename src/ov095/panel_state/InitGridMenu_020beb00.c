#include "nitro/types.h"

typedef struct {
    int x;
    int y;
} GridPoint;

typedef struct {
    int rows[9];
} GroupRowTable;

typedef struct {
    u32 header;
    int selected;
    void *containers[3];
    u8 pad0[0xf7bc - 0x14];
    GridPoint positions[0xef];
    u8 pad1[0x11100 - 0xf7bc - 0xef * 8];
    int direction;
    int state;
    int refreshPending;
    int mode;
    int timer;
    int step;
    int unk11118;
    int unk1111c;
    u8 pad2[0x11144 - 0x11120];
    int unk11144;
    int frameCounter;
    int blinkPhase;
} GridWork;

extern void *data_ov095_020c28c0;
extern const char *data_ov095_020c1768[];
extern const GroupRowTable data_ov095_020c1724;
extern u8 data_ov095_020c1774[];
extern int data_ov095_020c1788[];
extern const int data_ov095_020c17ac[];
extern char data_ov095_020c2888[];

extern void SetStateFlagBits_020bc688(u8 clearMask, u8 setBits);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern u32 func_ov039_020bc828(void);
extern void ClearEntryFlag_020c137c(int useSecondSet, int bitIndex);
extern int *AcquireMapLayout_020506dc(BOOL reload, BOOL discard);
extern void GrantUnlockedEntries_020c13a4(GridWork *work);
extern void AcquireRecordManager_02051c80(void);
extern int AcquireRecordSlot_02051d3c(int i, int param);
extern void SetupGridMenuDisplay_020bf084(GridWork *work);
extern void LoadMenuBackgrounds_020bf550(GridWork *work);
extern void func_ov095_020bf824(GridWork *work);
extern void RefreshSecondaryPanelList_020c0128(GridWork *work);
extern void InitGridTable_020c08e8(void *config, GridWork *work);
extern void func_ov095_020c09f8(int column, int row, int value, int x, int y, GridWork *work);
extern void func_ov095_020bfa18(int mode, GridWork *work);
extern void InitGridSprites_020c0504(GridWork *work);
extern void InvokeForChannelOrBoth_0200110c(u32 arg0, const char *name, void (*callback)(void), int channel);
extern void func_ov095_020c1608(void);
extern void LayoutTabEntries_020c0478(GridWork *work);
extern void SetPanelMode_020c11f0(int mode, GridWork *work);

BOOL InitGridMenu_020beb00(GridWork *work) {
    int rows[9];
    int cellIndex;
    int i;
    int group;
    int container;
    int index;

    data_ov095_020c28c0 = work;
    SetStateFlagBits_020bc688(5, 0);
    MIi_CpuClearFast_01ff8740(0, work, 0x1150c);
    for (container = 0; container < 3; container++) {
        work->containers[container] = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov095_020c1768[container], 0xe, FALSE);
    }
    work->header = func_ov039_020bc828();
    work->direction = 0;
    work->state = 1;
    work->selected = 0;
    work->refreshPending = 0;
    work->unk11118 = 0;
    work->unk1111c = 0;
    work->unk11144 = 0;
    work->frameCounter = 0;
    work->blinkPhase = 0;
    work->mode = 0;
    work->step = 0;
    work->timer = 0;
    for (index = 0; index < 0x100; index++) {
        ClearEntryFlag_020c137c(0, index);
    }
    AcquireMapLayout_020506dc(FALSE, FALSE);
    GrantUnlockedEntries_020c13a4(work);
    AcquireRecordManager_02051c80();
    AcquireRecordSlot_02051d3c(0, 1);
    AcquireRecordSlot_02051d3c(5, 1);
    AcquireRecordSlot_02051d3c(1, 1);
    SetupGridMenuDisplay_020bf084(work);
    LoadMenuBackgrounds_020bf550(work);
    func_ov095_020bf824(work);
    RefreshSecondaryPanelList_020c0128(work);
    *(GroupRowTable *)rows = data_ov095_020c1724;
    InitGridTable_020c08e8(data_ov095_020c1774, work);
    cellIndex = 0;
    for (group = 0; group < 9; group++) {
        int baseY = data_ov095_020c17ac[group];

        i = 0;
        if (i < data_ov095_020c1788[group]) {
            index = rows[group];
            do {
                int column = i % 13;
                int row = i / 13;
                int x = column * 16 + 0x24;
                int y = baseY + row * 16;

                func_ov095_020c09f8(column, row + index, cellIndex, x, y, work);
                work->positions[cellIndex].x = x;
                work->positions[cellIndex].y = y;
                i++;
                cellIndex++;
            } while (i < data_ov095_020c1788[group]);
        }
    }
    func_ov095_020bfa18(-1, work);
    InitGridSprites_020c0504(work);
    InvokeForChannelOrBoth_0200110c(1, data_ov095_020c2888, func_ov095_020c1608, 0);
    LayoutTabEntries_020c0478(work);
    SetPanelMode_020c11f0(1, work);
    return TRUE;
}
