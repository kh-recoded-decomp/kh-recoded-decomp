#include "nitro/types.h"

extern void CARD_Init(void);
extern u32 OS_GetLockID(void);
extern void FS_InitArchive(void *arc);
extern void FS_RegisterArchiveName(void *arc, void *name, u32 nameLen);
extern u16 OS_GetBootType(void);
extern u32 CARD_GetOwnRomHeader(void);
extern void FS_SetArchiveProc(void *arc, void *proc, u32 flags);
extern u32 FSi_RomArchiveProc(void *unused, int mode);
extern u32 FSi_EmptyArchiveProc(void *unused, int mode);
extern int FSi_ReadRomCallback(void *arc, u32 src, u32 dst, u32 length);
extern u32 FSi_ReadDummyCallback(u32 a, u32 b, u32 c, u32 d);
extern u32 FSi_WriteDummyCallback(u32 a, u32 b, u32 c, u32 d);
extern u32 FSi_OverrideRomArchive(void *arc);
extern void FS_LoadArchive(void *arc, u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, void *pRead, void *pWrite);
extern void FS_SetCurrentDirectory(void *context);

typedef struct {
    void *target;
    u32 value;
} RomState;

typedef struct {
    u8 pad_00[0x14];
    u32 flags;
} Arc;

typedef struct {
    u8 pad_00[0x40];
    u32 field_40;
    u32 field_44;
    u32 field_48;
    u32 field_4c;
} RomHeader;

extern RomState fsi_default_dma_no;
extern Arc fsi_arc_rom;
extern u8 fsi_rom_archive_name;
extern u8 fsi_rom_root_path;

void FSi_InitRomArchive(void *param1)
{
    RomHeader *header;
    RomHeader *header2;
    u32 status;

    CARD_Init();
    fsi_default_dma_no.target = param1;
    fsi_default_dma_no.value = OS_GetLockID();

    FS_InitArchive(&fsi_arc_rom);
    FS_RegisterArchiveName(&fsi_arc_rom, &fsi_rom_archive_name, 3);

    if (OS_GetBootType() == 1) {
        header = (RomHeader *)CARD_GetOwnRomHeader();
        header2 = (RomHeader *)CARD_GetOwnRomHeader();
        FS_SetArchiveProc(&fsi_arc_rom, (void *)FSi_RomArchiveProc, 0x682);
        if (header->field_40 != -1 && header->field_40 != 0) {
            status = header2->field_48;
            if (status != -1 && status != 0) {
                FS_LoadArchive(&fsi_arc_rom, 0, header2->field_48, header2->field_4c, header->field_40,
                              header->field_44, (void *)FSi_ReadRomCallback, 0);
            }
        }
    } else {
        FSi_OverrideRomArchive(&fsi_arc_rom);
    }

    u32 flagSet = (fsi_arc_rom.flags & 2) ? 1 : 0;
    if (flagSet == 0) {
        FS_SetArchiveProc(&fsi_arc_rom, (void *)FSi_EmptyArchiveProc, 0xffffffff);
        FS_LoadArchive(&fsi_arc_rom, 0, 0, 0, 0, 0, (void *)FSi_ReadDummyCallback, (void *)FSi_WriteDummyCallback);
    }

    FS_SetCurrentDirectory(&fsi_rom_root_path);
}
