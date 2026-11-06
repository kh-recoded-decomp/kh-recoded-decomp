# Current field entry and stored values

`GetCurrentFieldStageCode` (ov001:020644b0) reads signed session halfword +0x208. `GetCurrentFieldEntryKey` (ov001:020644c0) reads signed halfword +0x20a. The request constructor initializes both to -1 and fills pending +0x20c/+0x20e from its signed argument halfwords. EnterPendingRoom commits the pending pair before loading. The stage code selects the Mi container path; the entry key is passed to LookupSessionKeyValue and saved when nonnegative. Preserve negative sentinels and current/pending distinctions. Legacy TrackState and ConfigureFieldTracks labels do not establish music semantics.

`StoreFieldSessionContainerSlot` (ov001:02063560) stores a raw word at session+0x25b0+4*index. Known producers pass opened message/resource containers in slots 0 and 1. The store neither dereferences nor retains/frees them. These producers establish the value domain, but not capacity two, a downstream reader or a portable pointer declaration. Keep the native signed unchecked index and u32 value.

`StoreFieldSessionEntryPayloadPair` (ov001:02063848) stores its two u8 arguments at +0x2744/+0x2745. Scene adapters supply pending-entry bytes +1/+3 through signed-byte helpers; narrowing preserves the low eight bits, so -1 becomes 0xff. Individual byte meanings and later readers remain unproved. Do not infer room/world IDs or normalize the sentinel.


## Active EU sources

- [GetCurrentFieldStageCode](../src/overlays/ov001/calls/GetCurrentFieldStageCode.c).
- [GetCurrentFieldEntryKey](../src/overlays/ov001/calls/GetCurrentFieldEntryKey.c).
- [StoreFieldSessionContainerSlot](../src/overlays/ov001/calls/StoreFieldSessionContainerSlot.c).
- [StoreFieldSessionEntryPayloadPair](../src/overlays/ov001/calls/StoreFieldSessionEntryPayloadPair.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/GetCurrentFieldStageCode.c GetCurrentFieldStageCode --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetCurrentFieldEntryKey.c GetCurrentFieldEntryKey --thumb
python tools/verify_idx.py src/overlays/ov001/calls/StoreFieldSessionContainerSlot.c StoreFieldSessionContainerSlot --thumb
python tools/verify_idx.py src/overlays/ov001/calls/StoreFieldSessionEntryPayloadPair.c StoreFieldSessionEntryPayloadPair --thumb
bash tools/gate.sh
```
