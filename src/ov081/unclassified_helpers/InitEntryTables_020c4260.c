#include "nitro/types.h"

typedef struct ValueEntry {
    u8 kind;
    u8 value;
} ValueEntry;

typedef struct BreakEntry {
    u8 kind;
} BreakEntry;

typedef struct ListEntry {
    u8 kind;
    u8 count;
    u8 pad_02[2];
    u8 *ids;
} ListEntry;

extern ListEntry MakeIdList_020c5190(int count, ...);
extern void CopyEntryLists_020c51d8(void *state, ...);

static inline ValueEntry MakeValueEntry(u8 value)
{
    ValueEntry entry;
    entry.kind = 0;
    entry.value = value;
    return entry;
}

static inline BreakEntry MakeBreakEntry(void)
{
    BreakEntry entry;
    entry.kind = 2;
    return entry;
}

void InitEntryTables_020c4260(void *state)
{
    CopyEntryLists_020c51d8(state,
        &MakeBreakEntry(),
        &MakeValueEntry(0x02),
        &MakeValueEntry(0x03),
        &MakeValueEntry(0x04),
        &MakeValueEntry(0x05),
        &MakeValueEntry(0x06),
        &MakeValueEntry(0x07),
        &MakeValueEntry(0x08),
        &MakeValueEntry(0x09),
        &MakeValueEntry(0x0a),
        &MakeBreakEntry(),
        &MakeValueEntry(0x0b),
        &MakeIdList_020c5190(2, 0x0c, 0x0d),
        &MakeValueEntry(0x0e),
        &MakeIdList_020c5190(2, 0x0f, 0x10),
        &MakeBreakEntry(),
        &MakeIdList_020c5190(2, 0x11, 0x12),
        &MakeValueEntry(0x13),
        &MakeValueEntry(0x14),
        &MakeValueEntry(0x15),
        &MakeValueEntry(0x16),
        &MakeBreakEntry(),
        &MakeValueEntry(0x17),
        &MakeValueEntry(0x18),
        &MakeValueEntry(0x19),
        &MakeValueEntry(0x1a),
        &MakeValueEntry(0x1b),
        &MakeValueEntry(0x1c),
        &MakeValueEntry(0x1d),
        &MakeValueEntry(0x1e),
        &MakeValueEntry(0x1f),
        &MakeValueEntry(0x20),
        &MakeValueEntry(0x21),
        &MakeValueEntry(0x22),
        &MakeValueEntry(0x23),
        &MakeBreakEntry(),
        &MakeValueEntry(0x24),
        &MakeValueEntry(0x25),
        &MakeValueEntry(0x26),
        &MakeValueEntry(0x27),
        &MakeValueEntry(0x28),
        &MakeValueEntry(0x29),
        &MakeBreakEntry(),
        &MakeValueEntry(0x2a),
        &MakeValueEntry(0x2b),
        &MakeIdList_020c5190(2, 0x2c, 0x2d),
        &MakeIdList_020c5190(2, 0x2e, 0x2f),
        &MakeValueEntry(0x30),
        &MakeValueEntry(0x31),
        &MakeValueEntry(0x32),
        &MakeValueEntry(0x33),
        &MakeValueEntry(0x34),
        &MakeBreakEntry(),
        &MakeValueEntry(0x35),
        &MakeValueEntry(0x36),
        &MakeValueEntry(0x37),
        &MakeValueEntry(0x38),
        &MakeBreakEntry(),
        &MakeValueEntry(0x39),
        &MakeValueEntry(0x3a),
        &MakeValueEntry(0x3b),
        &MakeValueEntry(0x3c),
        &MakeValueEntry(0x3d),
        &MakeBreakEntry(),
        &MakeValueEntry(0x3e),
        &MakeIdList_020c5190(2, 0x3f, 0x40),
        &MakeValueEntry(0x41),
        &MakeValueEntry(0x42),
        &MakeValueEntry(0x43),
        &MakeValueEntry(0x44),
        &MakeValueEntry(0x45),
        &MakeValueEntry(0x46),
        &MakeValueEntry(0x47),
        &MakeBreakEntry(),
        &MakeIdList_020c5190(2, 0x48, 0x49),
        &MakeValueEntry(0x4a),
        &MakeValueEntry(0x4b),
        &MakeIdList_020c5190(2, 0x4d, 0x4e),
        &MakeIdList_020c5190(5, 0x4f, 0x50, 0x51, 0x52, 0x53),
        &MakeIdList_020c5190(4, 0x54, 0x55, 0x56, 0x57),
        &MakeIdList_020c5190(3, 0x58, 0x59, 0x5a),
        &MakeIdList_020c5190(4, 0x5b, 0x5c, 0x5d, 0x5e),
        &MakeIdList_020c5190(3, 0x5f, 0x60, 0x61),
        &MakeIdList_020c5190(16, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71),
        &MakeValueEntry(0x72),
        &MakeValueEntry(0x73),
        &MakeIdList_020c5190(2, 0x74, 0x75),
        &MakeIdList_020c5190(2, 0x76, 0x77),
        &MakeValueEntry(0x78),
        &MakeValueEntry(0x79),
        &MakeIdList_020c5190(3, 0x7a, 0x7b, 0x7c),
        &MakeIdList_020c5190(2, 0x7d, 0x7e),
        &MakeValueEntry(0x7f),
        &MakeIdList_020c5190(3, 0x80, 0x81, 0x82),
        &MakeBreakEntry(),
        &MakeValueEntry(0x83),
        &MakeValueEntry(0x84),
        &MakeValueEntry(0x85),
        &MakeValueEntry(0x86),
        &MakeValueEntry(0x87),
        &MakeValueEntry(0x88),
        &MakeIdList_020c5190(2, 0x89, 0x8a),
        &MakeValueEntry(0x8b),
        &MakeValueEntry(0x8c),
        &MakeBreakEntry(),
        &MakeValueEntry(0x8d),
        &MakeValueEntry(0x8e),
        &MakeValueEntry(0x8f),
        &MakeValueEntry(0x90),
        &MakeValueEntry(0x91));
}
