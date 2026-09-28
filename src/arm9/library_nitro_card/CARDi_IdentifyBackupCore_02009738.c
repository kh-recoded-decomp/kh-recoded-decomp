#include "nitro/types.h"

typedef struct CardBackupSpec {
    u32 totalSize;
    u32 sectorSize;
    u32 subsectorSize;
    u32 pageSize;
    u32 addrWidth;
    u32 programPage;
    u32 writePage;
    u32 writePageTotal;
    u32 eraseChip;
    u32 eraseChipTotal;
    u32 eraseSector;
    u32 eraseSectorTotal;
    u32 eraseSubsector;
    u32 eraseSubsectorTotal;
    u32 erasePage;
    u8 initialStatus;
    u8 pad_55[3];
    u32 caps;
    u8 pad_5c[4];
} CardBackupSpec;

typedef struct CardCommandArg {
    int result;
    int type;
    u32 id;
    u32 src;
    u32 dst;
    u32 len;
    CardBackupSpec spec;
} CardCommandArg;

extern CardCommandArg *data_02056fe0;
extern void func_01ff8830(void *dst, int value, int size);

void CARDi_IdentifyBackupCore_02009738(int type) {
    CardCommandArg *const p = data_02056fe0;

    func_01ff8830(&p->spec, 0, sizeof(p->spec));
    p->type = type;
    p->spec.caps = 0x203f;
    if (type != 0) {
        const u32 size = (u32)(1 << ((type >> 8) & 0xff));
        const int device = (type >> 0) & 0xff;
        const int vendor = (type >> 16) & 0xff;

        p->spec.totalSize = size;
        p->spec.initialStatus = 0xff;
        if (device == 1) {
            switch (size) {
            default:
                goto invalid_type;
            case 0x200:
                p->spec.pageSize = 0x10;
                p->spec.addrWidth = 1;
                p->spec.programPage = 5;
                p->spec.initialStatus = 0xf0;
                break;
            case 0x2000:
                p->spec.pageSize = 0x20;
                p->spec.addrWidth = 2;
                p->spec.programPage = 5;
                p->spec.initialStatus = 0;
                break;
            case 0x10000:
                p->spec.pageSize = 0x80;
                p->spec.addrWidth = 2;
                p->spec.programPage = 10;
                p->spec.initialStatus = 0;
                break;
            case 0x20000:
                p->spec.pageSize = 0x100;
                p->spec.addrWidth = 3;
                p->spec.programPage = 5;
                p->spec.initialStatus = 0;
                break;
            }
            p->spec.sectorSize = p->spec.pageSize;
            p->spec.caps |= 0x40;
            p->spec.caps |= 0x100;
            p->spec.caps |= 0x200;
            p->spec.caps |= 0x4000;
        } else if (device == 2) {
            switch (size) {
            default:
                goto invalid_type;
            case 0x40000:
            case 0x80000:
            case 0x100000:
                p->spec.writePage = 25;
                p->spec.writePageTotal = 300;
                p->spec.erasePage = 300;
                p->spec.eraseSector = 5000;
                p->spec.caps |= 0x80;
                p->spec.caps |= 0x400;
                break;
            case 0x200000:
                p->spec.writePage = 23;
                p->spec.writePageTotal = 300;
                p->spec.eraseSector = 500;
                p->spec.eraseSectorTotal = 5000;
                p->spec.eraseChip = 10000;
                p->spec.eraseChipTotal = 60000;
                p->spec.initialStatus = 0;
                p->spec.caps |= 0x80;
                p->spec.caps |= 0x400;
                p->spec.caps |= 0x1000;
                p->spec.caps |= 0x4000;
                break;
            case 0x400000:
                p->spec.eraseSector = 600;
                p->spec.eraseSectorTotal = 3000;
                p->spec.eraseSubsector = 70;
                p->spec.eraseSubsectorTotal = 150;
                p->spec.eraseChip = 23000;
                p->spec.eraseChipTotal = 800000;
                p->spec.initialStatus = 0;
                p->spec.subsectorSize = 0x1000;
                p->spec.caps |= 0x8000;
                p->spec.caps |= 0x1000;
                p->spec.caps |= 0x4000;
                break;
            case 0x800000:
                if (vendor == 0) {
                    p->spec.eraseSector = 1000;
                    p->spec.eraseSectorTotal = 3000;
                    p->spec.eraseChip = 68000;
                    p->spec.eraseChipTotal = 160000;
                    p->spec.initialStatus = 0;
                    p->spec.caps |= 0x1000;
                    p->spec.caps |= 0x4000;
                } else if (vendor == 1) {
                    p->spec.eraseSector = 1000;
                    p->spec.eraseSectorTotal = 3000;
                    p->spec.eraseChip = 68000;
                    p->spec.eraseChipTotal = 160000;
                    p->spec.initialStatus = 0x84;
                    p->spec.caps |= 0x1000;
                    p->spec.caps |= 0x4000;
                }
                break;
            }
            p->spec.sectorSize = 0x10000;
            p->spec.pageSize = 0x100;
            p->spec.addrWidth = 3;
            p->spec.programPage = 5;
            p->spec.caps |= 0x40;
            p->spec.caps |= 0x100;
            p->spec.caps |= 0x200;
            p->spec.caps |= 0x800;
        } else if (device == 3) {
            switch (size) {
            default:
                goto invalid_type;
            case 0x2000:
            case 0x8000:
                break;
            }
            p->spec.pageSize = size;
            p->spec.sectorSize = size;
            p->spec.addrWidth = 2;
            p->spec.initialStatus = 0;
            p->spec.caps |= 0x40;
            p->spec.caps |= 0x100;
            p->spec.caps |= 0x200;
            p->spec.caps |= 0x4000;
        } else {
        invalid_type:
            p->type = 0;
            p->spec.totalSize = 0;
            data_02056fe0->result = 3;
            return;
        }
    }
}
