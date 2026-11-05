# Field-object kind, pose and phase helpers

This block resolves the eight held EU ov016 functions using per-entry writers, drawing/update consumers, the pool constructor and actual callback dispatch. The entry pool and its 0xf8-byte object entries are different owners. Names do not create one shared complete layout or assign gameplay meanings to numerical kinds.

## Exact entry fields

Per-entry VecFx32 position begins at +0x38, so +0x3c is Y. Animation pose/group selection is the signed byte at +0x47; SetFieldEntryActorAnimationGroup stores it and binds tracks through the corresponding actor. The raw kind selector is the unsigned byte at +0x77, used by both update and draw switches. Phase is the high nibble of byte +0xbe in the actual HasFieldUnitPhase leaf. These fields are not the pool category at +0x5a or one interchangeable mode/state word. Older private structs use overlapping labels; a port must follow the exact offsets and writers documented here.

`UpdateFieldObjectPoolHeightHighlights` gets the pool from input object +4, iterates its count at pool +0x3e and obtains each entry. The native active predicate receives the entry still live in r0 even though the generated C omits that argument. For each eligible entry, the exact signed comparison is `entryY + 0x1800 < 0x80`. The low side disables the highlight helper and sets flags +0xc0 mask 0x1000000; the other side enables it and clears that mask. The highlight worker manipulates attribute bits 0x10/8 with phase/link/kind conditions. Do not call this Z/depth culling or unconditional hiding of all geometry, and do not simplify arithmetic in a way that changes native overflow behavior.

`GetFieldObjectKind` returns the raw unsigned +0x77 byte. The generic Object_GetKindValue delegates here for pool category 9; that category is separate from this per-entry kind. Kind values 5/11 select distinct draw/update paths. No original enum names or bounds normalization are recovered.

## Drawing and touch predicate

The draw path calls ShouldSkipKind11FieldObjectDraw only for kind 11 and returns before rendering when its result is nonzero. This implementation returns literal FALSE, so it never requests that skip. The native leaf reads no input; an object register passed by the caller does not justify inventing a parameter or a file-system role.

For kind 5 the draw path passes a local VecFx32 position to AdjustKind5FieldObjectDrawY. If pose +0x47 equals 1, it adds 45 to vector Y (+4). Those are native fixed-point units, not 45 pixels. The helper does not modify the object's world position; drawing later restores the model position.

IsFieldObjectPoseNot1 returns FALSE only for signed byte +0x47 equal 1 and TRUE otherwise. The actual object is the third register argument (r2), retained by ForwardModeCheck. InstallFieldObjectHitCallbacks registers that forwarding callback for kind 5 with this object as touchContext. This name states the exact pose comparison without assigning a new ability, physical acceptance code or named enum to value 1. Other incoming argument slots are not consumed by the leaf.

## Reset, phase thunk and refresh hook

ResetFieldObjectPoseAndPhase writes pose zero, clears byte +0xbe's high nibble and stores flags +0xc0 exactly 1. If actor-binding flag 4 is present, it rebinds the actor animation, clears its flag and conditionally applies a record entry according to slot state. It does not reset position or every motion field; ResetUnitToBasePosition performs the wider reset around it. UpdateStageManager also calls it directly. No lifetime/free operation or extra NULL guard is introduced.

HasFieldUnitPhaseThunk is a separate Thumb literal forwarding entrypoint to the real high-nibble predicate. FlushMarkerPosition consumes its BOOL result at two calls. Its old void-pointer library template is not evidence of allocation or ownership. Preserve the target Thumb bit, pool and forwarding arguments exactly.

CreateFieldUnit installs FieldObject_OnActorSlotRefreshNoop at pool callback +0x0c. FieldObject_ApplyActorSlotIndex tests entry flag 4, scans the actor's five slots and stores a slot value into entry +0x47 if available, then invokes that callback with the entry even if no slot was found. It is distinct from the stop hook at +8 and entry/pool destructors at +0x10/+0x14. The empty body preserves incoming r0; the dispatcher propagates it through its epilogue. This block does not assert universal discard or convert that residual word into BOOL/owned storage.

## Identities and sources

Paths are relative to `eu/` after name-only integration; evidence shared suffixes retain their reference-region names.

| Original EU identity | Descriptive name | Mode / bytes | Planned EU source | Evidence |
|---|---|---|---|---|
| `UpdateFieldObjectPoolHeightHighlights` | `UpdateFieldObjectPoolHeightHighlights` | THUMB / 0x68 | `src/overlays/ov016/calls/UpdateFieldObjectPoolHeightHighlights.c` | `src/ov016/field_objects/DrawFieldUnitObject_020a537c.c` |
| `ShouldSkipKind11FieldObjectDraw` | `ShouldSkipKind11FieldObjectDraw` | THUMB / 0x4 | `src/overlays/ov016/auto/ShouldSkipKind11FieldObjectDraw.c` | `src/ov016/field_objects/DrawFieldUnitObject_020a537c.c` |
| `IsFieldObjectPoseNot1` | `IsFieldObjectPoseNot1` | THUMB / 0x10 | `src/overlays/ov016/calls/IsFieldObjectPoseNot1.c` | `src/ov016/field_objects/InstallFieldObjectHitCallbacks_020a25c4.c` |
| `AdjustKind5FieldObjectDrawY` | `AdjustKind5FieldObjectDrawY` | THUMB / 0x10 | `src/overlays/ov016/calls/AdjustKind5FieldObjectDrawY.c` | `src/ov016/field_objects/DrawFieldUnitObject_020a537c.c` |
| `FieldObject_OnActorSlotRefreshNoop` | `FieldObject_OnActorSlotRefreshNoop` | THUMB / 0x2 | `src/overlays/ov016/auto/FieldObject_OnActorSlotRefreshNoop.c` | `src/ov001/field_objects/FieldObject_ApplyActorSlotIndex_02086384.c` |
| `ResetFieldObjectPoseAndPhase` | `ResetFieldObjectPoseAndPhase` | THUMB / 0x68 | `src/overlays/ov016/calls/ResetFieldObjectPoseAndPhase.c` | `eu/src/overlays/ov001/calls/SetFieldEntryActorAnimationGroup.c` |
| `HasFieldUnitPhaseThunk` | `HasFieldUnitPhaseThunk` | THUMB / 0x8 | `src/overlays/ov016/calls/HasFieldUnitPhaseThunk.c` | `src/ov016/field_objects/HasFieldUnitPhase_020a5c28.c` |
| `GetFieldObjectKind` | `GetFieldObjectKind` | THUMB / 0x6 | `src/overlays/ov016/auto/GetFieldObjectKind.c` | `src/ov001/unclassified_helpers/Object_GetKindValue_0208744c.c` |


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov016/calls/UpdateFieldObjectPoolHeightHighlights.c UpdateFieldObjectPoolHeightHighlights --thumb
python tools/verify_idx.py src/overlays/ov016/auto/ShouldSkipKind11FieldObjectDraw.c ShouldSkipKind11FieldObjectDraw --thumb
python tools/verify_idx.py src/overlays/ov016/calls/IsFieldObjectPoseNot1.c IsFieldObjectPoseNot1 --thumb
python tools/verify_idx.py src/overlays/ov016/calls/AdjustKind5FieldObjectDrawY.c AdjustKind5FieldObjectDrawY --thumb
python tools/verify_idx.py src/overlays/ov016/auto/FieldObject_OnActorSlotRefreshNoop.c FieldObject_OnActorSlotRefreshNoop --thumb
python tools/verify_idx.py src/overlays/ov016/calls/ResetFieldObjectPoseAndPhase.c ResetFieldObjectPoseAndPhase --thumb
python tools/verify_idx.py src/overlays/ov016/calls/HasFieldUnitPhaseThunk.c HasFieldUnitPhaseThunk --thumb
python tools/verify_idx.py src/overlays/ov016/auto/GetFieldObjectKind.c GetFieldObjectKind --thumb
bash tools/gate.sh
```
