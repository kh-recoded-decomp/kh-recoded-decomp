#include "src/overlays/ov015/WirelessBoardData.h"
#include "src/overlays/ov015/WirelessResourceData.h"

const WirelessBoardSlotPosition *gWirelessModeDataTables[10] = {
    NULL, NULL, NULL,
    gWirelessBoardSlotPositions3,
    gWirelessBoardSlotPositions4,
    gWirelessBoardSlotPositions5,
    gWirelessBoardSlotPositions6,
    gWirelessBoardSlotPositions7,
    gWirelessBoardSlotPositions8,
    gWirelessBoardSlotPositions9,
};

const WirelessResourceData *const *gWirelessResourceTables[7] = {
    NULL,
    gWirelessResourceTableC,
    gWirelessResourceTableC,
    gWirelessResourceTableC,
    gWirelessResourceTableC,
    gWirelessResourceTableB,
    gWirelessResourceTableA,
};
