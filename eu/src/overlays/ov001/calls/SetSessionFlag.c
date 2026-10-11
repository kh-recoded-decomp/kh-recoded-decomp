#include "src/overlays/ov001/SessionFlags.h"

void SetSessionFlag(int bitOffset)
{
    WriteSessionPackedBits(bitOffset, 1, 1);
}
