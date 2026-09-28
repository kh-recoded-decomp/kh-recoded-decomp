#include "nitro/types.h"
#include "nnsys/snd.h"

typedef struct {
    u8 pad_00000[0xb44c0];
    NNSSndStrmHandle streamHandles[2];
    u8 pad_b44c8[0xb47d8 - 0xb44c8];
    u8 currentStrmNo;
} SoundWork;

extern SoundWork *g_soundWork_0206084c;
extern BOOL func_020202b8(NNSSndStrmHandle *handle, int strmNo, u32 offset);

void StartSoundStreamAtOffset_0204df50(int handleIndex, u32 offset)
{
    func_020202b8(&g_soundWork_0206084c->streamHandles[handleIndex], g_soundWork_0206084c->currentStrmNo, offset);
}
