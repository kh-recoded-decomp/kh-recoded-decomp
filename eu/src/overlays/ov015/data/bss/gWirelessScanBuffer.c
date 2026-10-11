#include "src/overlays/ov015/WirelessScanBuffer.h"

/* The wireless manager and cache maintenance operate on the whole buffer. */
u8 gWirelessScanBuffer[WIRELESS_SCAN_BUFFER_SIZE] __attribute__((aligned(32)));
