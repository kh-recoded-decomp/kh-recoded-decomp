#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void func_ov035_020bc310(const VecFx32 *position, u16 hp, u16 shownHp, u16 maxHp, BOOL enemy);

/* Shows an entry's hp gauge at its feet; enemies of kinds 0x16-0x1a and 0xfd get the enemy style. */
void ShowEntryHpGauge(StageEntry *entry)
{
    BOOL enemy = FALSE;

    switch (entry->kind) {
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0xfd:
        if (entry->flags & STAGE_ENTRY_ENEMY) {
            enemy = TRUE;
        }
        break;
    }
    func_ov035_020bc310(&entry->slot.node.position, entry->hp, entry->shownHp, entry->maxHp, enemy);
}
