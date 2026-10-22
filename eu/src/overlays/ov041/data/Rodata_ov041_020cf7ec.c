#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

const u32 data_ov041_020cf82c[24] = {
    0xFFFFB000, 0xFFFFD000, 0xFFFFF000, 0x00001000,
    0x00003000, 0x00005000, 0xFFFF7000, 0xFFFFA99A,
    0xFFFFE333, 0x00001CCD, 0x00005666, 0x00009000,
    0xFFFFB000, 0xFFFFC000, 0xFFFFD000, 0x00001000,
    0x00000000, 0x00005000, 0xFFFFB000, 0xFFFFC000,
    0xFFFFE000, 0x00004000, 0x00005000, 0x00006000,
};

const StageOrbShares gNoOrbShares = {
    {{-1, -1}, {-1, -1}, {-1, -1}},
};

/* Fractions of an entry's maximum hp (0.8, 0.6, 0.4, 0.2) whose crossing forces its second action. */
const StageHpThresholds gEntryHpThresholds = {
    {0xccd, 0x99a, 0x666, 0x333},
};

const StageOrbAmounts gNoOrbAmounts = {
    {-1, -1, -1},
};

const StageSoundChoices gStageStatusSounds = {
    {0, 1},
};

const StageActionChoices gEmptyActionChoices = {
    {-1, -1, -1, -1},
};
