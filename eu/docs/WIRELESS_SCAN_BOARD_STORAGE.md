# EU wireless scan and board storage

These identities complete the observed scan-parameter field spans and the board/minigame owner. They retain the existing split storage and opaque tails.

| EU identity | Name | Physical bytes | Definition |
| --- | --- | --- | --- |
| ov015 `0x207ea6a` | `gWirelessScanAddressAndModeStorage` | 10 | `src/overlays/ov015/data/bss/Bss_ov015_0207ea6a.c` |
| ov015 `0x207ea74` | `gWirelessScanSsidStorage` | 76 | `src/overlays/ov015/data/bss/Bss_ov015_0207ea74.c` |
| ov015 `0x20812e0` | `gWirelessBoardGlobals` | 32 | `src/overlays/ov015/data/bss/Bss_ov015_020812e0.c` |

## `gWirelessScanAddressAndModeStorage`

Physical 10-byte segment at gWhScanExParam +0x0a. The active WH_StateInStartScan view places bssid[6], scanType u16 and ssidLength u16 here; the body writes scanType=1 and ssidLength=0 before WM_StartScanEx. The leading 10-byte named gWhScanExParam definition and this segment remain separate.

Only the observed scan fields are identified; no complete standalone SDK object or independent allocation is claimed. Preserve the cross-symbol parameter view.

Evidence: `src/overlays/ov015/calls/WH_StateInStartScan.c`.

## `gWirelessScanSsidStorage`

Physical 76-byte segment at gWhScanExParam +0x14. WH_StateInStartScan fills the first 32 bytes (its ssid member) with 0xff and passes the parameter view to WM_StartScanEx.

The first 32 bytes are proved SSID storage. Remaining 44 bytes are retained with no new field semantics; do not shrink this definition or claim its full 76 bytes are an SSID payload.

Evidence: `src/overlays/ov015/calls/WH_StateInStartScan.c`.

## `gWirelessBoardGlobals`

First word points to the 0x20138-byte board/minigame context allocated aligned 4 and cleared by SetupResultPanel. GeneratePanelRound, SetupPanelBoard, board masks, tracing, touch and result text all use that context. ReleaseWorkBuffer releases subordinate graphics/text resources, frees the context and clears the first word.

The BSS definition is 32 bytes. Only its first-word pointer is characterized; remaining 28 bytes are opaque physical storage. The heap context is a different allocation and must not be confused with this global.

Evidence: `src/overlays/ov015/calls/SetupResultPanel.c`, `src/overlays/ov015/calls/ReleaseWirelessPanelResources.c`, `src/overlays/ov015/calls/ReleaseWorkBuffer.c`, `src/overlays/ov015/calls/UpdatePanelBoard.c`.


## Byte-exact validation

44 DATA identities retain their source paths, native sizes and storage.
247/248 affected official function checks pass; the remaining
1 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 283 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
