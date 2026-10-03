#include "nitro/types.h"

typedef struct {
    u8 data[0x70];
} PlayerCard;

typedef struct {
    u8 pad_0000[0xe0];
    u8 flags0Low : 2;
    u8 inputLocked : 1;
    u8 flags0High : 5;
    u8 flags1Low : 3;
    u8 promptShown : 1;
    u8 resultShown : 1;
    u8 flags1Mid : 2;
    u8 confirmShown : 1;
    u8 flags2Low : 1;
    u8 cursorShown : 1;
    u8 flags2High : 6;
    u8 pad_00E3[9];
    int selectedCard;
    u8 pad_00F0[0xce68];
    PlayerCard cards[1];
} PanelContext;

extern PanelContext *data_ov015_0207e960;

extern int DispatchContextCommand_02066c78(u32 command, int a, int b, void *c);
extern void StopSeqArcOrDefault_0204d960(int player, int fadeFrames, int arg);
extern void func_ov015_0206fa98(void);
extern void UpdatePlayerCounter_0206f5d8(void);
extern int RollPanelBonus_02070674(void);
extern void InitPanelMainScreen_0206e730(void);
extern void ShowPlayerCardSummary_0206f048(int bonus);
extern void func_ov002_020621e4(void);
extern void SetupResultPanel_0207509c(int bonus, int rank, PlayerCard *card);

void OpenResultPanel_02071ab4(void) {
    int bonus;
    int rank;

    data_ov015_0207e960->promptShown = FALSE;
    data_ov015_0207e960->cursorShown = FALSE;
    data_ov015_0207e960->resultShown = FALSE;
    data_ov015_0207e960->confirmShown = FALSE;
    if (DispatchContextCommand_02066c78(5, 0, 0, NULL)) {
        StopSeqArcOrDefault_0204d960(2, 0xd, 4);
    }
    func_ov015_0206fa98();
    UpdatePlayerCounter_0206f5d8();
    DispatchContextCommand_02066c78(0x80000001, (int)&data_ov015_0207e960->cards[data_ov015_0207e960->selectedCard], 0, NULL);
    bonus = RollPanelBonus_02070674();
    InitPanelMainScreen_0206e730();
    ShowPlayerCardSummary_0206f048(bonus);
    func_ov002_020621e4();
    rank = DispatchContextCommand_02066c78(8, 0, 0, NULL);
    if (DispatchContextCommand_02066c78(5, 0, 0, NULL)) {
        rank = 0;
    }
    SetupResultPanel_0207509c(bonus, rank, &data_ov015_0207e960->cards[data_ov015_0207e960->selectedCard]);
    data_ov015_0207e960->inputLocked = FALSE;
}
