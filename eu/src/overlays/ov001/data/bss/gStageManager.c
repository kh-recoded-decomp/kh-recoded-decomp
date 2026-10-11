#include "src/overlays/ov001/StageMotionState.h"

StageMotionManager *gStageManager;

/* Tail alignment after the final named BSS object in this overlay. */
static u32 sStageManagerBssTail[5];
