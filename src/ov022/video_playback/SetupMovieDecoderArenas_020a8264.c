#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    void *codeBackup;
    u32 codeSize;
    void *codeAddress;
} MovieFileBank;

extern MovieFileBank data_ov022_020b7d94;

extern int getMovieDecoderCodeSize_020aa8a0(void);
extern u32 GetTableAEntry_0200367c(int index);
extern u32 GetTableBEntry_02003690(int index);
extern u32 func_02003b3c(void);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff89a8(const void *src, void *dest, u32 size);
extern unsigned int GetMovieCacheTableArenaCapacity_020aa8ac(void);
extern void ResetMovieDecoderCodeArena_020aa8b4(void *arenaBase, unsigned int arenaSize);
extern void ResetMovieLookupTableArena_020aa8d4(void *arenaBase, unsigned int arenaSize);

void SetupMovieDecoderArenas_020a8264(void) {
    MovieFileBank *bank = &data_ov022_020b7d94;
    u32 tableSize;
    u32 tableBase;

    bank->codeSize = getMovieDecoderCodeSize_020aa8a0();
    bank->codeAddress = (void *)(GetTableAEntry_0200367c(3) - bank->codeSize);
    bank->codeBackup = NNSi_FndAllocFromDefaultHeap_0202a178(bank->codeSize);
    func_01ff89a8(bank->codeAddress, bank->codeBackup, bank->codeSize);
    tableBase = GetTableBEntry_02003690(4);
    tableSize = func_02003b3c() + 0x4000 - tableBase;
    if (tableSize >= GetMovieCacheTableArenaCapacity_020aa8ac()) {
        tableSize = GetMovieCacheTableArenaCapacity_020aa8ac();
    }
    ResetMovieDecoderCodeArena_020aa8b4(bank->codeAddress, bank->codeSize);
    ResetMovieLookupTableArena_020aa8d4((void *)GetTableBEntry_02003690(4), tableSize);
}
