#include "libs/nitro/card/card_rom_internal.h"

typedef char CardRomStateMustBe44Bytes[sizeof(CARDRomState) == 44 ? 1 : -1];
typedef char CardDmaInfoMustStartAt16Bytes[
    (u32)&((CARDRomState *)0)->dmaReadInfo == 16 ? 1 : -1];

/* sCardDmaReadInfo is the existing linker alias of the embedded transfer. */
CARDRomState sCardRomState;
