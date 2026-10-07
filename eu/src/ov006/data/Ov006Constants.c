#include "nitro/types.h"

const s32 sOv006GridSteps[8][2] = {
    {  0,  1 },
    { -1,  1 },
    { -1,  0 },
    { -1, -1 },
    {  0, -1 },
    {  1, -1 },
    {  1,  0 },
    {  1,  1 },
};

const s32 sOv006CardinalStepIndices[4] = { 0, 2, 4, 6 };
const s32 sOv006JointRotation[4] = { 0, 0xB50, 0xB50, 0 };

const u32 sOv006ElevatorFrameData[4] = {
    0x10061401,
    0x0000F000,
    0x10000000,
    0,
};
