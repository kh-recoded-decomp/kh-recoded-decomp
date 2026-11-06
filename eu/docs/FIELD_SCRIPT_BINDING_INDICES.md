# Recorded script-handler binding indices

`GetScriptHandlerSlot7Index` (ov001:02064784) and `GetScriptHandlerSlot8Index` (ov001:02064794) read session+0x18/+0x19. Both retain `int ...(void)` and the native signed-byte load, including the initial -1 sentinel and other negative values.

The actual producers, BindScriptHandlersSlot7/8, select a handler table and an optional overlay from their binding records. Slot 7 records its selected index unconditionally. Slot 8 records its index only when the selected overlay ID differs from -1, after loading that overlay. Handler storage can change without updating the latter byte. Preserve this distinction; neither getter is a readiness or visibility test.

These are engine script-handler slots 7 and 8, separate from the session callback array and actor modes. BeginStageEntries uses slot-7 indices 2/6 for motion bindings; ProbeNearestFacingTarget uses slot-8 indices 0..4 for its filtering policy. Those consumers do not establish a universal gameplay enum. Existing table lengths do not add bounds checks to the getters.


## Active EU sources

- [GetScriptHandlerSlot7Index](../src/overlays/ov001/calls/GetScriptHandlerSlot7Index.c).
- [GetScriptHandlerSlot8Index](../src/overlays/ov001/calls/GetScriptHandlerSlot8Index.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/GetScriptHandlerSlot7Index.c GetScriptHandlerSlot7Index --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetScriptHandlerSlot8Index.c GetScriptHandlerSlot8Index --thumb
bash tools/gate.sh
```
