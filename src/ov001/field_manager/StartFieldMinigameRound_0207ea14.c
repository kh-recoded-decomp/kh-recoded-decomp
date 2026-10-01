#include "nitro/types.h"

typedef struct LevelTable {
    int values[4];
} LevelTable;

typedef struct FieldMinigame {
    int mode;
    u8 pad_04[0x1c];
    int active;
    u8 pad_24[0xac - 0x24];
    int score;
    int level;
} FieldMinigame;

extern FieldMinigame *data_ov001_020a04d4;
extern LevelTable data_ov001_0209e060;
extern LevelTable data_ov001_0209e070;
extern void *GetSceneTagTracker_020711b0(void);
extern int func_ov001_0207123c(void);
extern s32 GetClampedPaletteSlot_02073598(void);
extern void func_ov001_0207df44(u32 param, int level);
extern void InitFieldSpriteSlots_0207e130(FieldMinigame *game, BOOL useBlocks);
extern void func_ov001_0207e244(FieldMinigame *game, s32 flag);
extern void RandomizeFacing_0207e270(FieldMinigame *game, BOOL apply);
extern void func_ov027_020b9d54(int widgets, int layer, int x, int y, int width, int height);

void StartFieldMinigameRound_0207ea14(void)
{
    FieldMinigame *game = data_ov001_020a04d4;
    int widgets;
    LevelTable levels;
    LevelTable times;
    int scale;

    GetSceneTagTracker_020711b0();
    widgets = func_ov001_0207123c();
    levels = data_ov001_0209e060;
    times = data_ov001_0209e070;
    game->active = 1;
    scale = 20;
    game->score = 0;
    game->level = (levels.values[GetClampedPaletteSlot_02073598()] * 10 + 9) / 10;
    switch (game->mode) {
    case 1:
        InitFieldSpriteSlots_0207e130(game, FALSE);
        scale = 15;
        break;
    case 2:
        func_ov001_0207e244(game, 0);
        break;
    case 3:
        RandomizeFacing_0207e270(game, FALSE);
        break;
    }
    func_ov027_020b9d54(widgets, 11, 0, 8, 11, 16);
    func_ov001_0207df44(((scale * times.values[GetClampedPaletteSlot_02073598()] + 9) / 10) * 1000, game->level);
}
