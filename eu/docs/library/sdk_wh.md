# NitroSDK wireless helper

Routines from NitroSDK's wireless helper (`wh.c`, the `wireless_shared` module
that games link to drive the WM library) in overlay 15. They are the SDK's C,
but `MATH_CountLeadingZeros` inlines the ARM9 `clz` instruction, which no
compiler of this project emits from C, so they are reported as verified library
code under the four gates in [PROGRESS_POLICY.md](../PROGRESS_POLICY.md). Each
section below is checked by `tools/sdklib/verify_sdklib.py`, which runs the ROM's
own instructions against the Python model in `tools/sdklib/families/sdk_wh.py`.

The tests replace the WM library calls with stubs that return chosen values and
log their arguments, so they check what the helper asks WM to do, not what the
wireless firmware does with it; the Hardware bullets say what that is.

### `WH_StateInStartScan`

- **Interface:** `BOOL WH_StateInStartScan(void)`, ARM, standard procedure call
  standard: no arguments, `r0` = `TRUE` (1) when the scan request was accepted
  and `FALSE` (0) otherwise; `r4`-`r11` and `sp` are preserved, `r1`-`r3`, `ip`
  and the flags are clobbered. It reads `gWhState.channel` (u16 at +0xE, the
  channel the game asked for, 0 = any) and writes the scan parameter block
  `gWhScanExParam` (`WMScanExParam`).
- **Behavior:** `WM_GetAllowedChannel()` returns the mask of channels the
  console may use, bit *n* for channel *n* + 1. A result of 0x8000 means the WM
  library is not ready: the helper records `WM_ERRCODE_ILLEGAL_STATE` (3) with
  `WH_SetError` and returns `FALSE`. A mask of 0 means the radio is disabled: it
  records `WH_ERRCODE_NO_RADIO` (0x16) and returns `FALSE`. In both cases nothing
  else is written. Otherwise it picks the channel to scan:
  - with a requested channel *c*, `channelList` = `1 << (c - 1)` truncated to 16
    bits; *c* is not checked against the allowed mask, and a value above 16
    leaves `channelList` = 0;
  - with none, it takes the lowest set bit of the previous `channelList` (its
    channel number is the trailing zero count + 1, computed as
    `32 - clz(~x & (x - 1)) + 1`), then steps up one channel at a time, wrapping
    from 16 to 1, until it reaches a channel in the allowed mask, and stores that
    channel's bit. Consecutive calls therefore cycle through the allowed channels;
    a previous `channelList` of 0 starts the cycle at channel 1. The loop ends
    because the mask is non-zero and only has bits for channels 1-16.

  It then fills the rest of the block: `maxChannelTime` =
  `GetDispersionScanPeriod()`, `scanBuf` = `gWirelessScanBuffer`, `scanBufSize` =
  0x400, `scanType` = 1 (`WM_SCANTYPE_PASSIVE`), `ssidLength` = 0 and the 32
  `ssid` bytes = 0xFF (with a zero length, no SSID filter); `bssid`,
  `ssidMatchLength` and the reserved words keep whatever the caller set. It calls
  `WM_StartScanEx(WH_StateOutStartScanEx, &gWhScanExParam)`. A result of
  `WM_ERRCODE_OPERATING` (2), the request queued, returns `TRUE`; any other result
  is passed to `WH_SetError` and returns `FALSE`. `gWhState` is never written.
- **Hardware:** none directly. `WM_StartScanEx` hands the request to the ARM7
  wireless firmware through the PXI FIFO and returns at once; the firmware scans
  the one channel for up to `maxChannelTime` ms, writes the parent beacons it
  hears into `gWirelessScanBuffer` (`WMBssDesc` records) and later calls
  `WH_StateOutStartScanEx` from the WM callback. The buffer is written by the
  ARM7, so the code that reads it must not rely on stale data-cache lines;
  `WH_StateOutStartScanEx` calls `DC_InvalidateRange` before parsing the
  results. `GetDispersionScanPeriod` returns 30 to 39 ms: 30 + (13 x (the sum of
  the six MAC address bytes + the low 16 bits of the V-blank counter at
  0x02FFFC3C), kept to 16 bits) mod 10, so that two consoles scanning at once do
  not stay in step.
