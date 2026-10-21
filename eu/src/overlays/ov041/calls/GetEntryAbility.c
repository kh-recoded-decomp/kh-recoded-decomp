#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

#define STAGE_PLAYER_KIND 0xff

/* The given ability bit if an entry has it in effect right now, else 0. */
int GetEntryAbility(StageEntry *entry, int ability)
{
    int result;
    StageWork *work = gMovieContextState->stageWork;

    result = 0;

    switch (ability) {
    case 1:
    case 2:
    case 4:
    case 8:
    case 0x10:
        if (entry->kind != STAGE_PLAYER_KIND) {
            return 0;
        }
        if (entry->hp * 4 > entry->maxHp) {
            break;
        }
        result = entry->abilities & ability;
        break;
    case STAGE_ABILITY_LEADER:
        if (entry->flags & STAGE_ENTRY_ENEMY) {
            return 0;
        }
        result = work->entries[0].abilities & ability;
        break;
    case STAGE_ABILITY_PLAYER:
        if (entry->kind != STAGE_PLAYER_KIND) {
            return 0;
        }
        result = entry->abilities & ability;
        break;
    }
    return result;
}
