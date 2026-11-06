# Field menu and message-window operations

These operations belong to three separate owners: the field menu, message-window work and subscene panel. Tag IDs refer to the tracker embedded in the field-scene manager, rather than independent menu allocations. Existing native signatures and forwarding remain unchanged.

`RefreshFieldSlotCellOrLinkedEntries` (ov001:02078710) accepts slot indices 0/1. With field flag 8 set it redraws the corresponding slot cell, restoring the prior text node and refreshing the page count when necessary. Otherwise, its alternate policy scans active command entries: kind 2 selects link +0x18 and kind 3 selects +0x14. A link other than -1 marks entry+0x24 and ORs flags 6. Constructor and redraw consumers establish presentation invalidation, not immediate drawing in that alternate path. Individual slot values and links retain their raw meanings.

`SetFieldMenuGaugeDrawingEnabled` (02078938) writes the full input word at menu+0x118. InitFieldMenu initializes it to 1; DrawPartyGauges tests it before any camera/draw work, alongside another policy gate. This controls that drawing guard, rather than every menu activity. Preserve the word without BOOL normalization.

`DisarmFieldMenuTag15AndInvokeRecord36` (02078ac4) acts only when menu+0x130 is nonzero. It disarms loaded tag 15, invokes tracker callback +0x3c on active record 36 (0x24), then clears the guard. The guard's activating writer and asset purpose remain opaque. No object is freed.

`DisarmMessageWindowTag5AndInvokeRecord60` (020795c4) disarms tag 5 and invokes the distinct tracker callback +0x40 on active record 60 (0x3c). CloseModeWindow calls it before selecting phase 7 on its non-kind-1 path. The helper obtains the tracker itself and never reads the caller's forwarded window pointer; its existing void(void) definition stays unchanged. This is a specific tracker operation, not a complete window destructor.

`SetMessageWindowDispatchSuspended` (0207a880) stores the full input at work+0xf8, always clears word 0, and clears work+0xc only for nonzero input. RunActiveModeHandler skips its input/state dispatch while suspended. UploadMessageWindowPaletteCallback also discards a pending request without uploading or opening layers in that state. Slide-in setup/completion pass 1/0. Preserve the unconditional and conditional resets; the guard does not suspend every UI subsystem.

`RequestPanelModeWithConditionalTimerMode2` (0207b360) selects panel timer policy 2 when GetScriptHandlerSlot7Index returns 0 and packed flag 0x370b is set, then always requests the input panel mode. The policy store precedes possible request rejection and survives it. UpdatePanelScene interprets policies 0/1/2 with a separate flag override; policy 2 does not universally skip timers.

The last helper forwards RequestPanelModeChange's native BOOL in R0, and callers consume it. Its current definition and local callee declaration say void while callers say BOOL. This naming block preserves those declarations and instructions; a coherent portable ABI still requires a separate correction across all callers. The other setters' residual R0 values do not establish fluent return APIs.


## Active EU sources

- [RefreshFieldSlotCellOrLinkedEntries](../src/overlays/ov001/calls/RefreshFieldSlotCellOrLinkedEntries.c).
- [SetFieldMenuGaugeDrawingEnabled](../src/overlays/ov001/calls/SetFieldMenuGaugeDrawingEnabled.c).
- [DisarmFieldMenuTag15AndInvokeRecord36](../src/overlays/ov001/calls/DisarmFieldMenuTag15AndInvokeRecord36.c).
- [DisarmMessageWindowTag5AndInvokeRecord60](../src/overlays/ov001/calls/DisarmMessageWindowTag5AndInvokeRecord60.c).
- [SetMessageWindowDispatchSuspended](../src/overlays/ov001/calls/SetMessageWindowDispatchSuspended.c).
- [RequestPanelModeWithConditionalTimerMode2](../src/overlays/ov001/calls/RequestPanelModeWithConditionalTimerMode2.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/RefreshFieldSlotCellOrLinkedEntries.c RefreshFieldSlotCellOrLinkedEntries --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetFieldMenuGaugeDrawingEnabled.c SetFieldMenuGaugeDrawingEnabled --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DisarmFieldMenuTag15AndInvokeRecord36.c DisarmFieldMenuTag15AndInvokeRecord36 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DisarmMessageWindowTag5AndInvokeRecord60.c DisarmMessageWindowTag5AndInvokeRecord60 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetMessageWindowDispatchSuspended.c SetMessageWindowDispatchSuspended --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RequestPanelModeWithConditionalTimerMode2.c RequestPanelModeWithConditionalTimerMode2 --thumb
bash tools/gate.sh
```
