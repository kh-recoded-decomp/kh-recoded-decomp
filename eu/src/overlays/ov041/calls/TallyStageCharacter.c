#include "nitro/types.h"
#include "src/overlays/ov001/FieldProgressState.h"

extern FieldProgressState *data_ov001_020a0480;
extern u8 LookupMovieCharacterValue(int id);
extern BOOL AddClampedGlobalPackedBits(u32 bitOffset, u32 bitCount, u32 amount, u32 maximum);
extern void SetGlobalPackedBit(int bitIndex);

/*
 * Counts one more of a character (a 17-bit tally per character, up to 99999); counted ones also add one to the
 * pending region progress. Character 0x1a also sets packed flag 0xbe5.
 */
void TallyStageCharacter(int character, BOOL counted)
{
    int slot = LookupMovieCharacterValue(character);
    int progress;

    if (slot == 0x28) {
        return;
    }
    progress = 1;
    AddClampedGlobalPackedBits(slot * 17 + 0x680, 17, 1, 99999);
    if (!counted) {
        progress = 0;
    }
    data_ov001_020a0480->pendingRegionProgress += (s16)progress;
    if (character == 0x1a) {
        SetGlobalPackedBit(0xbe5);
    }
}
