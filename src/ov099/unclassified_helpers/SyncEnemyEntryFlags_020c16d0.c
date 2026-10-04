#include "nitro/types.h"

typedef struct EnemyBitInfo {
  u32 id;
  u32 bitOffset;
} EnemyBitInfo;

extern EnemyBitInfo data_ov099_020c241c[];
extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void SetEntryFlag_020c16b4(int list, int index);

void SyncEnemyEntryFlags_020c16d0(void) {
  int index;

  for (index = 0; index < 0x28; index++) {
    if (ReadGlobalPackedBits_02027348(data_ov099_020c241c[index].bitOffset, 0x11) != 0) {
      SetEntryFlag_020c16b4(0, index);
      SetGlobalPackedBit_02027320(index + 0x1172);
    }
    if (!IsGlobalPackedBitSet_02027304(index + 0x1222) && IsGlobalPackedBitSet_02027304(index + 0x1172)) {
      SetEntryFlag_020c16b4(1, index);
    }
  }
}
