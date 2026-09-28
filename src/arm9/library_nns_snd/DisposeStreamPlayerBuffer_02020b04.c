#include "nitro/types.h"

typedef struct {
    u32 unk_00;
    u8 *prepareThread;
} PrepareThreadHolder;

extern u8 g_streamMutex_0205fd98[];
extern PrepareThreadHolder g_prepareThreadHolder_0205e324;
extern void func_02003158(void *mutex);
extern void func_020031a8(void *mutex);
extern void func_02020810(int player);
extern void NNS_SndStrmFreeChannel_0201e030(int stream);

void DisposeStreamPlayerBuffer_02020b04(int mem, u32 arg1, int player)
{
    if (mem != *(int *)(player + 0x134)) {
        return;
    }

    func_02003158(g_streamMutex_0205fd98);
    if (g_prepareThreadHolder_0205e324.prepareThread != 0) {
        func_02003158(g_prepareThreadHolder_0205e324.prepareThread + 0x10c8);
    }

    func_02020810(player);

    *(int *)(player + 0x134) = 0;
    *(int *)(player + 0x138) = 0;
    *(u8 *)(player + 0x12c) = 0;

    if (0 < *(int *)(player + 0x128)) {
        NNS_SndStrmFreeChannel_0201e030(player);
        *(int *)(player + 0x128) = 0;
    }

    func_020031a8(g_streamMutex_0205fd98);
    if (g_prepareThreadHolder_0205e324.prepareThread == 0) {
        return;
    }
    func_020031a8(g_prepareThreadHolder_0205e324.prepareThread + 0x10c8);
}
