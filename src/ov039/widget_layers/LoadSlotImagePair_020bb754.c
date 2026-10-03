#include "nitro/types.h"

typedef struct {
    char tags[9][3];
} SlotTagTable;

typedef struct {
    u8 pad_0000[0xcab4];
    void *slots[4];
} Ov039State;

extern const SlotTagTable data_ov039_020be764;
extern const char data_ov039_020be808[];
extern const char data_ov039_020be818[];
extern void *OS_SNPrintf_02002468(char *dst, unsigned int len, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);

void LoadSlotImagePair_020bb754(Ov039State *state, int slot, int kind)
{
    SlotTagTable table = data_ov039_020be764;
    char path[64];

    OS_SNPrintf_02002468(path, sizeof(path), data_ov039_020be808, table.tags[kind + 1]);
    state->slots[slot] = Msg_OpenContainerAndReadHeader_0202cc6c(path, 14, FALSE);
    OS_SNPrintf_02002468(path, sizeof(path), data_ov039_020be818, table.tags[kind + 1]);
    state->slots[slot + 1] = Msg_OpenContainerAndReadHeader_0202cc6c(path, 14, FALSE);
}
