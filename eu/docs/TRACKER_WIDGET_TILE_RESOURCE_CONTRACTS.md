# Tracker, widget and tile resource contracts

This document records 32 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

The tag-tracker owner manages distinct pools: 0x38-byte tracker records at owner +0x0c, 0x30-byte timed tag sequences at +0x10 and 0x10-byte screen-resource records at +0x14. A screen-resource record holds its halfword ID, owned file payload, unpacked screen pointer and active word. A sequence owns its allocated tag-pointer array. These are not interchangeable generic Entry layouts despite the private source typedefs.

The section loaders trust counted, length-prefixed records. Screen payloads are copied after an eight-byte record header into allocations transferred to the screen pool. The tag-sequence constructor receives a u64 frame interval; the final native zero is its upper word, not a seventh logical field. File-loading helpers free temporary descriptor/resource buffers after constructing persistent records; copied screen payloads and tag arrays remain alive. The existing code consumes the loaded pointer before its final NULL check, so this documentation adds no failure policy.

Pool searches return a one-past-end sentinel when exhausted or absent, not NULL. Creation assumes capacity and valid IDs. Releasing a screen resource clears active, frees and nulls the owned file pointer, but leaves the unpacked pointer stale while inactive. Pool teardown releases members and the three arrays, does not free the enclosing owner and does not null its array pointers. Deactivation clears record activity and optionally invokes an owner callback; it does not free an individual slot.

Touch samples contain four halfwords (x, y, down, status) in eight bytes. The recent-sample helper scans newest to oldest for status zero, falling back to the newest sample if none is valid; it assumes at least one sample. Injected-sample consumption can clear its current bit. Touch rectangles include both upper edges. Priming saved touch-down state at owner +0x20 is a deliberate state write, not a hardware sample or a proven debounce algorithm.

Widget creation makes every descriptor first, then links neighbors by ID. The 0x58-byte descriptor count comes from the caller. The focused-widget getter returns a borrowed pointer at root +0x646c. Confirmation callback +0xa8 receives the widget; root input callback +0x644c receives focused widget and key mask. Base position +0x34 and mutable offset +0x3c are distinct; base assignment does not immediately reposition indexed records. The source's void setter view hides a returned base-position address, so retain that ABI question explicitly.

Image-entry and tile-row adapters preserve incoming register forwarding despite old no-argument/PXI labels. Tile-row clearing returns the row index or the all-ones -1 sentinel, clears rowLength halfwords, and neither removes its ID nor marks it dirty. No generated four-register declaration in this block proves four logical portable parameters.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov027:020b77a0` | THUMB | `func_ov027_020b77a0` | `LoadTrackerScreenResourcesFromSection` | [eu/src/overlays/ov027/calls/LoadTrackerScreenResourcesFromSection.c](../src/overlays/ov027/calls/LoadTrackerScreenResourcesFromSection.c) |
| `ov027:020b7848` | THUMB | `func_ov027_020b7848` | `CreateTrackerTagSequencesFromSection` | [eu/src/overlays/ov027/calls/CreateTrackerTagSequencesFromSection.c](../src/overlays/ov027/calls/CreateTrackerTagSequencesFromSection.c) |
| `ov027:020b7880` | ARM | `func_ov027_020b7880` | `IsPointInTrackerTouchBounds` | [eu/src/overlays/ov027/auto/IsPointInTrackerTouchBounds.c](../src/overlays/ov027/auto/IsPointInTrackerTouchBounds.c) |
| `ov027:020b78bc` | ARM | `func_ov027_020b78bc` | `FindActiveTrackerScreenResourceById` | [eu/src/overlays/ov027/auto/FindActiveTrackerScreenResourceById.c](../src/overlays/ov027/auto/FindActiveTrackerScreenResourceById.c) |
| `ov027:020b7954` | ARM | `func_ov027_020b7954` | `FindFreeTrackerTagSequence` | [eu/src/overlays/ov027/calls/FindFreeTrackerTagSequence.c](../src/overlays/ov027/calls/FindFreeTrackerTagSequence.c) |
| `ov027:020b79a0` | ARM | `func_ov027_020b79a0` | `FindFreeTrackerScreenResource` | [eu/src/overlays/ov027/auto/FindFreeTrackerScreenResource.c](../src/overlays/ov027/auto/FindFreeTrackerScreenResource.c) |
| `ov027:020b79dc` | ARM | `func_ov027_020b79dc` | `CopyLatestValidTouchSample` | [eu/src/overlays/ov027/calls/CopyLatestValidTouchSample.c](../src/overlays/ov027/calls/CopyLatestValidTouchSample.c) |
| `ov027:020b7a50` | ARM | `func_ov027_020b7a50` | `GetTrackerTouchSample` | [eu/src/overlays/ov027/calls/GetTrackerTouchSample.c](../src/overlays/ov027/calls/GetTrackerTouchSample.c) |
| `ov027:020b7df4` | ARM | `func_ov027_020b7df4` | `UpdateTagTrackerAndTouch` | [eu/src/overlays/ov027/calls/UpdateTagTrackerAndTouch.c](../src/overlays/ov027/calls/UpdateTagTrackerAndTouch.c) |
| `ov027:020b7e1c` | THUMB | `func_ov027_020b7e1c` | `FreeTagTrackerPools` | [eu/src/overlays/ov027/calls/FreeTagTrackerPools.c](../src/overlays/ov027/calls/FreeTagTrackerPools.c) |
| `ov027:020b7e44` | THUMB | `func_ov027_020b7e44` | `LoadTagTrackerResourceFile` | [eu/src/overlays/ov027/calls/LoadTagTrackerResourceFile.c](../src/overlays/ov027/calls/LoadTagTrackerResourceFile.c) |
| `ov027:020b7e7c` | ARM | `func_ov027_020b7e7c` | `CreateTrackerRecord` | [eu/src/overlays/ov027/calls/CreateTrackerRecord.c](../src/overlays/ov027/calls/CreateTrackerRecord.c) |
| `ov027:020b7f80` | ARM | `func_ov027_020b7f80` | `DeactivateTrackerRecord` | [eu/src/overlays/ov027/auto/DeactivateTrackerRecord.c](../src/overlays/ov027/auto/DeactivateTrackerRecord.c) |
| `ov027:020b7fac` | THUMB | `func_ov027_020b7fac` | `DeactivateAllTrackerRecords` | [eu/src/overlays/ov027/calls/DeactivateAllTrackerRecords.c](../src/overlays/ov027/calls/DeactivateAllTrackerRecords.c) |
| `ov027:020b8110` | ARM | `func_ov027_020b8110` | `RegisterTrackerScreenResource` | [eu/src/overlays/ov027/calls/RegisterTrackerScreenResource.c](../src/overlays/ov027/calls/RegisterTrackerScreenResource.c) |
| `ov027:020b8154` | ARM | `func_ov027_020b8154` | `ReleaseTrackerScreenResource` | [eu/src/overlays/ov027/calls/ReleaseTrackerScreenResource.c](../src/overlays/ov027/calls/ReleaseTrackerScreenResource.c) |
| `ov027:020b817c` | THUMB | `func_ov027_020b817c` | `ReleaseAllTrackerScreenResources` | [eu/src/overlays/ov027/calls/ReleaseAllTrackerScreenResources.c](../src/overlays/ov027/calls/ReleaseAllTrackerScreenResources.c) |
| `ov027:020b81f8` | ARM | `func_ov027_020b81f8` | `SetTrackerRecordX` | [eu/src/overlays/ov027/auto/SetTrackerRecordX.c](../src/overlays/ov027/auto/SetTrackerRecordX.c) |
| `ov027:020b8200` | ARM | `func_ov027_020b8200` | `SetTrackerRecordY` | [eu/src/overlays/ov027/auto/SetTrackerRecordY.c](../src/overlays/ov027/auto/SetTrackerRecordY.c) |
| `ov027:020b8208` | ARM | `func_ov027_020b8208` | `SetTrackerRecordPosition` | [eu/src/overlays/ov027/calls/SetTrackerRecordPosition.c](../src/overlays/ov027/calls/SetTrackerRecordPosition.c) |
| `ov027:020b824c` | ARM | `func_ov027_020b824c` | `InvokeTrackerRecordAtPosition` | [eu/src/overlays/ov027/calls/InvokeTrackerRecordAtPosition.c](../src/overlays/ov027/calls/InvokeTrackerRecordAtPosition.c) |
| `ov027:020b8578` | ARM | `func_ov027_020b8578` | `FindActiveBackgroundScreenResourceById` | [eu/src/overlays/ov027/auto/FindActiveBackgroundScreenResourceById.c](../src/overlays/ov027/auto/FindActiveBackgroundScreenResourceById.c) |
| `ov027:020b85e4` | ARM | `func_ov027_020b85e4` | `MarkTrackerPreviousTouchDown` | [eu/src/overlays/ov027/auto/MarkTrackerPreviousTouchDown.c](../src/overlays/ov027/auto/MarkTrackerPreviousTouchDown.c) |
| `ov027:020b8f7c` | THUMB | `func_ov027_020b8f7c` | `CreateAndLinkWidgetDescriptors` | [eu/src/overlays/ov027/calls/CreateAndLinkWidgetDescriptors.c](../src/overlays/ov027/calls/CreateAndLinkWidgetDescriptors.c) |
| `ov027:020b8fb8` | THUMB | `func_ov027_020b8fb8` | `LoadWidgetDescriptorsFromFile` | [eu/src/overlays/ov027/calls/LoadWidgetDescriptorsFromFile.c](../src/overlays/ov027/calls/LoadWidgetDescriptorsFromFile.c) |
| `ov027:020b9098` | THUMB | `func_ov027_020b9098` | `CreateWidgetImageEntry` | [eu/src/overlays/ov027/calls/CreateWidgetImageEntry.c](../src/overlays/ov027/calls/CreateWidgetImageEntry.c) |
| `ov027:020b90a0` | THUMB | `func_ov027_020b90a0` | `SetWidgetConfirmCallback` | [eu/src/overlays/ov027/auto/SetWidgetConfirmCallback.c](../src/overlays/ov027/auto/SetWidgetConfirmCallback.c) |
| `ov027:020b90b8` | THUMB | `func_ov027_020b90b8` | `SetWidgetRootInputCallback` | [eu/src/overlays/ov027/calls/SetWidgetRootInputCallback.c](../src/overlays/ov027/calls/SetWidgetRootInputCallback.c) |
| `ov027:020b9114` | ARM | `func_ov027_020b9114` | `GetFocusedWidget` | [eu/src/overlays/ov027/auto/GetFocusedWidget.c](../src/overlays/ov027/auto/GetFocusedWidget.c) |
| `ov027:020b91d0` | ARM | `func_ov027_020b91d0` | `SetWidgetBasePosition` | [eu/src/overlays/ov027/calls/SetWidgetBasePosition.c](../src/overlays/ov027/calls/SetWidgetBasePosition.c) |
| `ov027:020b9cf8` | ARM | `func_ov027_020b9cf8` | `ClearTileTableRowById` | [eu/src/overlays/ov027/calls/ClearTileTableRowById.c](../src/overlays/ov027/calls/ClearTileTableRowById.c) |
| `ov027:020b9d68` | ARM | `func_ov027_020b9d68` | `ClearTileTableRowByIdAdapter` | [eu/src/overlays/ov027/calls/ClearTileTableRowByIdAdapter.c](../src/overlays/ov027/calls/ClearTileTableRowByIdAdapter.c) |

## LoadTrackerScreenResourcesFromSection

Identity: `ov027:020b77a0`, THUMB, native extent 62 bytes (including any configured pool). Previous symbol: `func_ov027_020b77a0`.

EU entrypoint: [eu/src/overlays/ov027/calls/LoadTrackerScreenResourcesFromSection.c](../src/overlays/ov027/calls/LoadTrackerScreenResourcesFromSection.c).

```c
void LoadTrackerScreenResourcesFromSection(int param_1, int param_2);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Walks length-prefixed records, copies each payload after its 8-byte header into an owned allocation, then registers it by halfword ID. Source: [src/ov027/reviewed_helpers/func_ov027_020b7780.c:1-14](../../src/ov027/reviewed_helpers/func_ov027_020b7780.c).
- Registration unpacks each copied resource as NNS G2d screen data. Source: [src/ov027/record_management/func_ov027_020b80f0.c:1-12](../../src/ov027/record_management/func_ov027_020b80f0.c).

Contract limits:

- The section starts with a record count; helper trusts recorded lengths.
- Allocated payload ownership is transferred to the screen-resource record.

## CreateTrackerTagSequencesFromSection

Identity: `ov027:020b7848`, THUMB, native extent 56 bytes (including any configured pool). Previous symbol: `func_ov027_020b7848`.

EU entrypoint: [eu/src/overlays/ov027/calls/CreateTrackerTagSequencesFromSection.c](../src/overlays/ov027/calls/CreateTrackerTagSequencesFromSection.c).

```c
void CreateTrackerTagSequencesFromSection(int param_1, int param_2);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Walks counted variable-length records and forwards ID, tag array/count, user parameter and frame interval to CreateTagRecord. Source: [src/ov027/reviewed_helpers/func_ov027_020b7828.c:1-11](../../src/ov027/reviewed_helpers/func_ov027_020b7828.c).
- The real callee takes a u64 frame interval, allocates the tag-pointer array and resolves each tag record. Source: [src/ov027/record_management/CreateTagRecord_020b7fc0.c:1-44](../../src/ov027/record_management/CreateTagRecord_020b7fc0.c).

Contract limits:

- The final zero supplies the upper word of the interval argument; do not invent an extra seventh logical field.

## IsPointInTrackerTouchBounds

Identity: `ov027:020b7880`, ARM, native extent 60 bytes (including any configured pool). Previous symbol: `func_ov027_020b7880`.

EU entrypoint: [eu/src/overlays/ov027/auto/IsPointInTrackerTouchBounds.c](../src/overlays/ov027/auto/IsPointInTrackerTouchBounds.c).

```c
int IsPointInTrackerTouchBounds(int px, int py, struct Box *b);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Tests inclusive point containment using byte x/y/width/height at element+0x1c..0x1f. Source: [src/ov027/reviewed_helpers/func_ov027_020b7860.c:1-15](../../src/ov027/reviewed_helpers/func_ov027_020b7860.c).
- The touch-tracking loop uses this predicate before invoking a hit callback. Source: [src/ov027/pointer_entries/UpdateTrackedPointerEntry_020b7c30.c:1-45](../../src/ov027/pointer_entries/UpdateTrackedPointerEntry_020b7c30.c).

Contract limits:

- Both upper edges are included.
- No coordinate scaling or clipping is performed.

## FindActiveTrackerScreenResourceById

Identity: `ov027:020b78bc`, ARM, native extent 80 bytes (including any configured pool). Previous symbol: `func_ov027_020b78bc`.

EU entrypoint: [eu/src/overlays/ov027/auto/FindActiveTrackerScreenResourceById.c](../src/overlays/ov027/auto/FindActiveTrackerScreenResourceById.c).

```c
struct Entry * FindActiveTrackerScreenResourceById(struct EntryArrayOwner *owner, int entryId);
```

The returned record pointer is borrowed; absence is the pool's one-past-end pointer.

Demonstrated behavior and evidence:

- Searches the 0x10-byte array at owner+0x14 for active records with the requested halfword ID. Source: [src/ov027/record_management/func_ov027_020b789c.c:1-26](../../src/ov027/record_management/func_ov027_020b789c.c).
- Registration creates this exact 0x10-byte ID/resource/unpacked-screen/active layout. Source: [src/ov027/record_management/func_ov027_020b80f0.c:1-12](../../src/ov027/record_management/func_ov027_020b80f0.c).

Contract limits:

- If absent, returns one-past-end rather than NULL.
- Caller must know capacity/existence; do not silently replace the result with NULL.

## FindFreeTrackerTagSequence

Identity: `ov027:020b7954`, ARM, native extent 76 bytes (including any configured pool). Previous symbol: `func_ov027_020b7954`.

EU entrypoint: [eu/src/overlays/ov027/calls/FindFreeTrackerTagSequence.c](../src/overlays/ov027/calls/FindFreeTrackerTagSequence.c).

```c
struct Entry * FindFreeTrackerTagSequence(struct EntryArrayOwner *owner);
```

The returned slot pointer is borrowed, including the one-past-end exhaustion sentinel.

Demonstrated behavior and evidence:

- Searches the 0x30-byte tag-sequence array at owner+0x10 until flag bit 1 at sequence+0x24 is clear. Source: [eu/src/overlays/ov027/calls/FindFreeTrackerTagSequence.c:1-22](../src/overlays/ov027/calls/FindFreeTrackerTagSequence.c).
- CreateTagRecord obtains this record and sets armed after initializing the sequence. Source: [src/ov027/record_management/CreateTagRecord_020b7fc0.c:1-44](../../src/ov027/record_management/CreateTagRecord_020b7fc0.c).
- The native tag-sequence view identifies armed bit 1 at +0x24. Source: [src/ov027/record_management/TickTagRecords_020b7aa0.c:1-82](../../src/ov027/record_management/TickTagRecords_020b7aa0.c).

Contract limits:

- This is the armed flag in the actual tag-sequence view, not a generic available bit.
- Exhaustion returns one-past-end rather than NULL.

## FindFreeTrackerScreenResource

Identity: `ov027:020b79a0`, ARM, native extent 60 bytes (including any configured pool). Previous symbol: `func_ov027_020b79a0`.

EU entrypoint: [eu/src/overlays/ov027/auto/FindFreeTrackerScreenResource.c](../src/overlays/ov027/auto/FindFreeTrackerScreenResource.c).

```c
struct Element * FindFreeTrackerScreenResource(struct Obj *obj);
```

The returned slot pointer is borrowed, including the one-past-end exhaustion sentinel.

Demonstrated behavior and evidence:

- Finds the first 0x10-byte screen-resource record whose active word +0x0c is zero. Source: [src/ov027/reviewed_helpers/func_ov027_020b7980.c:1-23](../../src/ov027/reviewed_helpers/func_ov027_020b7980.c).
- Registration uses this free-slot finder, clears the record, stores resource/unpacked screen and sets active. Source: [src/ov027/record_management/func_ov027_020b80f0.c:1-12](../../src/ov027/record_management/func_ov027_020b80f0.c).

Contract limits:

- Exhaustion returns one-past-end rather than NULL.

## CopyLatestValidTouchSample

Identity: `ov027:020b79dc`, ARM, native extent 116 bytes (including any configured pool). Previous symbol: `func_ov027_020b79dc`.

EU entrypoint: [eu/src/overlays/ov027/calls/CopyLatestValidTouchSample.c](../src/overlays/ov027/calls/CopyLatestValidTouchSample.c).

```c
int CopyLatestValidTouchSample(int unusedArgument, int sourceRecord);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Reads the recent touch-sample ring, scans newest to oldest for validity halfword zero, and copies eight bytes to the caller output. Source: [eu/src/overlays/ov027/calls/CopyLatestValidTouchSample.c:1-24](../src/overlays/ov027/calls/CopyLatestValidTouchSample.c).
- Native ListTouchInput identifies x/y/down/status as four halfwords in eight bytes. Source: [eu/src/overlays/ov025/SlotListTouch.h:1-52](../src/overlays/ov025/SlotListTouch.h).

Contract limits:

- If no sample is valid, copies the newest sample anyway.
- The implementation assumes at least one sample; no empty-ring policy is added.

## GetTrackerTouchSample

Identity: `ov027:020b7a50`, ARM, native extent 112 bytes (including any configured pool). Previous symbol: `func_ov027_020b7a50`.

EU entrypoint: [eu/src/overlays/ov027/calls/GetTrackerTouchSample.c](../src/overlays/ov027/calls/GetTrackerTouchSample.c).

```c
int GetTrackerTouchSample(int record, int sourceTarget);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Uses an injected sample when pending/current flags permit it; otherwise tries the captured touch record and falls back to the recent-ring helper. Source: [src/ov027/record_management/func_ov027_020b7a30.c:1-20](../../src/ov027/record_management/func_ov027_020b7a30.c).
- Copies the globally captured eight-byte touch sample when its pointer exists. Source: [src/ov027/shared_engine/CopySourceBlock_020b9f7c.c:1-8](../../src/ov027/shared_engine/CopySourceBlock_020b9f7c.c).
- The touch tracker consumes this result before detecting press/release changes. Source: [src/ov027/pointer_entries/UpdateTrackedPointerEntry_020b7c30.c:1-45](../../src/ov027/pointer_entries/UpdateTrackedPointerEntry_020b7c30.c).

Contract limits:

- A pending sample that is not current returns failure.
- Consuming an injected sample clears only its current bit.
- This getter has state-changing consumption semantics.

## UpdateTagTrackerAndTouch

Identity: `ov027:020b7df4`, ARM, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov027_020b7df4`.

EU entrypoint: [eu/src/overlays/ov027/calls/UpdateTagTrackerAndTouch.c](../src/overlays/ov027/calls/UpdateTagTrackerAndTouch.c).

```c
void UpdateTagTrackerAndTouch(int param_1);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Ticks timed tag sequences, then updates touch tracking when owner flag bit 0 at +0x2c is set. Source: [src/ov027/reviewed_helpers/func_ov027_020b7dd4.c:1-8](../../src/ov027/reviewed_helpers/func_ov027_020b7dd4.c).
- Ticks armed/active sequences from elapsed OS ticks and applies the selected tag. Source: [src/ov027/record_management/TickTagRecords_020b7aa0.c:1-82](../../src/ov027/record_management/TickTagRecords_020b7aa0.c).
- Handles the touch snapshot and element callback dispatch. Source: [src/ov027/pointer_entries/UpdateTrackedPointerEntry_020b7c30.c:1-45](../../src/ov027/pointer_entries/UpdateTrackedPointerEntry_020b7c30.c).

Contract limits:

- Touch dispatch is conditional; tag-sequence ticking always runs.

## FreeTagTrackerPools

Identity: `ov027:020b7e1c`, THUMB, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov027_020b7e1c`.

EU entrypoint: [eu/src/overlays/ov027/calls/FreeTagTrackerPools.c](../src/overlays/ov027/calls/FreeTagTrackerPools.c).

```c
void FreeTagTrackerPools(int param_1);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Sweeps record/sequence/screen resources, then frees the three allocated arrays at owner+0x14,+0x10,+0x0c. Source: [src/ov027/reviewed_helpers/func_ov027_020b7dfc.c:1-9](../../src/ov027/reviewed_helpers/func_ov027_020b7dfc.c).
- The sweep deactivates records, releases sequence-owned buffers and frees screen-resource payloads. Source: [src/ov027/shared_engine/SweepElements_020b831c.c:1-8](../../src/ov027/shared_engine/SweepElements_020b831c.c).

Contract limits:

- Does not null the three owner pointers after freeing.
- Does not free the owner itself.

## LoadTagTrackerResourceFile

Identity: `ov027:020b7e44`, THUMB, native extent 56 bytes (including any configured pool). Previous symbol: `func_ov027_020b7e44`.

EU entrypoint: [eu/src/overlays/ov027/calls/LoadTagTrackerResourceFile.c](../src/overlays/ov027/calls/LoadTagTrackerResourceFile.c).

```c
void LoadTagTrackerResourceFile(int ctx, int param2);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Loads a resource allocation from heap tail, dispatches its three offset sections to screen-resource, record and tag-sequence loaders, then frees the temporary file buffer. Source: [src/ov027/reviewed_helpers/func_ov027_020b7e24.c:1-15](../../src/ov027/reviewed_helpers/func_ov027_020b7e24.c).
- The middle section builds tracker records and sets their positions. Source: [src/ov027/runtime/build_and_place_record_sprites_020b77c0.c:1-21](../../src/ov027/runtime/build_and_place_record_sprites_020b77c0.c).

Contract limits:

- The helper dereferences the loaded pointer before its final null check; no new failure behavior is inferred.
- Screen payload copies and tag arrays outlive the temporary file allocation.

## CreateTrackerRecord

Identity: `ov027:020b7e7c`, ARM, native extent 112 bytes (including any configured pool). Previous symbol: `func_ov027_020b7e7c`.

EU entrypoint: [eu/src/overlays/ov027/calls/CreateTrackerRecord.c](../src/overlays/ov027/calls/CreateTrackerRecord.c).

```c
int CreateTrackerRecord(int owner_id, int related_id, unsigned short record_type, unsigned short first_id, unsigned short second_id, short first_value, short second_value, int record_data);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Obtains and clears a 0x38-byte record; stores kind, IDs, two short parameters, caller data and a related screen-resource pointer, then marks the record active. Source: [src/ov027/overlay_handling/func_ov027_020b7e5c.c:1-17](../../src/ov027/overlay_handling/func_ov027_020b7e5c.c).
- The pool at owner+0x0c consists of 0x38-byte records with active word+0x14. Source: [src/ov027/record_management/FindFreeRecordSlot_020b78ec.c:1-25](../../src/ov027/record_management/FindFreeRecordSlot_020b78ec.c).

Contract limits:

- The free-record finder returns one-past-end on exhaustion; no allocation failure protection is present.
- Keep opaque kind/ID fields until their consumers establish meaning.

## DeactivateTrackerRecord

Identity: `ov027:020b7f80`, ARM, native extent 44 bytes (including any configured pool). Previous symbol: `func_ov027_020b7f80`.

EU entrypoint: [eu/src/overlays/ov027/auto/DeactivateTrackerRecord.c](../src/overlays/ov027/auto/DeactivateTrackerRecord.c).

```c
void DeactivateTrackerRecord(struct A *a, void *b, int c);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Optionally invokes owner callback +0x40 when requested, then clears record.active at +0x14. Source: [src/ov027/reviewed_helpers/func_ov027_020b7f60.c:1-11](../../src/ov027/reviewed_helpers/func_ov027_020b7f60.c).

Contract limits:

- Does not free the 0x38-byte record allocation.
- Callback execution depends on both request and nonnull callback.

## DeactivateAllTrackerRecords

Identity: `ov027:020b7fac`, THUMB, native extent 52 bytes (including any configured pool). Previous symbol: `func_ov027_020b7fac`.

EU entrypoint: [eu/src/overlays/ov027/calls/DeactivateAllTrackerRecords.c](../src/overlays/ov027/calls/DeactivateAllTrackerRecords.c).

```c
void DeactivateAllTrackerRecords(int ctx_, int arg);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Clears the intrusive element list, then deactivates each active 0x38-byte record using the caller callback option. Source: [eu/src/overlays/ov027/calls/DeactivateAllTrackerRecords.c:1-14](../src/overlays/ov027/calls/DeactivateAllTrackerRecords.c).
- Marks/removes list elements and clears the tracked element pointer. Source: [src/ov027/shared_engine/ClearElementList_020b8334.c:1-30](../../src/ov027/shared_engine/ClearElementList_020b8334.c).

Contract limits:

- The clear-list action occurs before record iteration.
- Does not free the record array.

## RegisterTrackerScreenResource

Identity: `ov027:020b8110`, ARM, native extent 68 bytes (including any configured pool). Previous symbol: `func_ov027_020b8110`.

EU entrypoint: [eu/src/overlays/ov027/calls/RegisterTrackerScreenResource.c](../src/overlays/ov027/calls/RegisterTrackerScreenResource.c).

```c
int RegisterTrackerScreenResource(int recordPool, int ownerId, unsigned short recordId);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Initializes a free 0x10-byte record, stores its ID and owned file pointer, unpacks screen data into +8, then sets active. Source: [src/ov027/record_management/func_ov027_020b80f0.c:1-12](../../src/ov027/record_management/func_ov027_020b80f0.c).

Contract limits:

- Registration result from NNS_G2dGetUnpackedScreenData is not checked.
- Payload is released by the paired screen-resource release helper.

## ReleaseTrackerScreenResource

Identity: `ov027:020b8154`, ARM, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov027_020b8154`.

EU entrypoint: [eu/src/overlays/ov027/calls/ReleaseTrackerScreenResource.c](../src/overlays/ov027/calls/ReleaseTrackerScreenResource.c).

```c
void ReleaseTrackerScreenResource(int a0, struct S *a1);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Clears record.active, frees its owned file buffer if nonnull and nulls that pointer. Source: [eu/src/overlays/ov027/calls/ReleaseTrackerScreenResource.c:1-16](../src/overlays/ov027/calls/ReleaseTrackerScreenResource.c).

Contract limits:

- Leaves the unpacked screen pointer at +8 stale while active is zero.
- Does not free the record slot itself.

## ReleaseAllTrackerScreenResources

Identity: `ov027:020b817c`, THUMB, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov027_020b817c`.

EU entrypoint: [eu/src/overlays/ov027/calls/ReleaseAllTrackerScreenResources.c](../src/overlays/ov027/calls/ReleaseAllTrackerScreenResources.c).

```c
void ReleaseAllTrackerScreenResources(int ctx_);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Visits every active 0x10-byte resource record and invokes its release helper. Source: [eu/src/overlays/ov027/calls/ReleaseAllTrackerScreenResources.c:1-12](../src/overlays/ov027/calls/ReleaseAllTrackerScreenResources.c).

Contract limits:

- The resource-record array itself is retained.

## SetTrackerRecordX

Identity: `ov027:020b81f8`, ARM, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov027_020b81f8`.

EU entrypoint: [eu/src/overlays/ov027/auto/SetTrackerRecordX.c](../src/overlays/ov027/auto/SetTrackerRecordX.c).

```c
u32 SetTrackerRecordX(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Stores a halfword at trackerRecord+2. Source: [src/ov027/leaf_research/func_ov027_020b81d8.c:1-5](../../src/ov027/leaf_research/func_ov027_020b81d8.c).
- Record construction passes signed X/Y from descriptor+8/+0x0a to the paired position setter. Source: [src/ov027/runtime/build_and_place_record_sprites_020b77c0.c:1-21](../../src/ov027/runtime/build_and_place_record_sprites_020b77c0.c).

Contract limits:

- Caller behavior proves position X; signedness of the storage should remain consistent with coordinate readers.

## SetTrackerRecordY

Identity: `ov027:020b8200`, ARM, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov027_020b8200`.

EU entrypoint: [eu/src/overlays/ov027/auto/SetTrackerRecordY.c](../src/overlays/ov027/auto/SetTrackerRecordY.c).

```c
u32 SetTrackerRecordY(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Stores a halfword at trackerRecord+4. Source: [src/ov027/leaf_research/func_ov027_020b81e0.c:1-5](../../src/ov027/leaf_research/func_ov027_020b81e0.c).
- Record construction passes signed X/Y to the paired position setter. Source: [src/ov027/runtime/build_and_place_record_sprites_020b77c0.c:1-21](../../src/ov027/runtime/build_and_place_record_sprites_020b77c0.c).

Contract limits:

- Caller behavior proves position Y; no bounds clamp exists.

## SetTrackerRecordPosition

Identity: `ov027:020b8208`, ARM, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov027_020b8208`.

EU entrypoint: [eu/src/overlays/ov027/calls/SetTrackerRecordPosition.c](../src/overlays/ov027/calls/SetTrackerRecordPosition.c).

```c
void SetTrackerRecordPosition(int param_1, int param_2, int param_3, int param_4);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Calls the X and Y halfword setters in order. Source: [src/ov027/reviewed_helpers/func_ov027_020b81e8.c:1-6](../../src/ov027/reviewed_helpers/func_ov027_020b81e8.c).

Contract limits:

- Only coordinates change; the record callback is not invoked.

## InvokeTrackerRecordAtPosition

Identity: `ov027:020b824c`, ARM, native extent 60 bytes (including any configured pool). Previous symbol: `func_ov027_020b824c`.

EU entrypoint: [eu/src/overlays/ov027/calls/InvokeTrackerRecordAtPosition.c](../src/overlays/ov027/calls/InvokeTrackerRecordAtPosition.c).

```c
void InvokeTrackerRecordAtPosition(int arg0, int arg1, unsigned short arg2, unsigned short arg3);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Saves old signed X/Y, temporarily assigns supplied coordinates, invokes the tracker callback and restores old coordinates. Source: [src/ov027/reviewed_helpers/func_ov027_020b822c.c:1-10](../../src/ov027/reviewed_helpers/func_ov027_020b822c.c).

Contract limits:

- The callback observes temporary coordinates.
- Restores coordinates even if callback changed them; does not promise exception/reentrancy safety.

## FindActiveBackgroundScreenResourceById

Identity: `ov027:020b8578`, ARM, native extent 80 bytes (including any configured pool). Previous symbol: `func_ov027_020b8578`.

EU entrypoint: [eu/src/overlays/ov027/auto/FindActiveBackgroundScreenResourceById.c](../src/overlays/ov027/auto/FindActiveBackgroundScreenResourceById.c).

```c
struct Entry * FindActiveBackgroundScreenResourceById(struct EntryArrayOwner *owner, int entryId);
```

The returned record pointer is borrowed; absence is the pool's one-past-end pointer.

Demonstrated behavior and evidence:

- Searches owner+0x14 array of 0x10-byte screen-resource records for a matching active ID. Source: [src/ov027/record_management/func_ov027_020b8558.c:1-26](../../src/ov027/record_management/func_ov027_020b8558.c).
- The caller uses the returned record.screen->rawData as the background screen upload source. Source: [src/ov002/panel_state/AnimateMenuBgFrames_02064b34.c:1-60](../../src/ov002/panel_state/AnimateMenuBgFrames_02064b34.c).
- Native typed initialization obtains background screen resources through this entrypoint. Source: [eu/src/overlays/ov002/calls/InitMenuContext.c:1-396](../src/overlays/ov002/calls/InitMenuContext.c).

Contract limits:

- Returns the one-past-end sentinel when no active ID matches.
- This separate entrypoint duplicates the tracker screen lookup implementation; preserve its address and match.

## MarkTrackerPreviousTouchDown

Identity: `ov027:020b85e4`, ARM, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov027_020b85e4`.

EU entrypoint: [eu/src/overlays/ov027/auto/MarkTrackerPreviousTouchDown.c](../src/overlays/ov027/auto/MarkTrackerPreviousTouchDown.c).

```c
u32 MarkTrackerPreviousTouchDown(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Writes halfword 1 to tracker+0x20. Source: [src/ov027/leaf_research/func_ov027_020b85c4.c:1-6](../../src/ov027/leaf_research/func_ov027_020b85c4.c).
- The stored snapshot starts at +0x1c; its third halfword at +0x20 is compared with the current sample touch state to detect changes. Source: [src/ov027/pointer_entries/UpdateTrackedPointerEntry_020b7c30.c:1-45](../../src/ov027/pointer_entries/UpdateTrackedPointerEntry_020b7c30.c).
- Called on the exact main/sub tracker owners after enabling/disabling their interaction flags. Source: [src/ov039/event_state/SetMenuButtonsEnabled_020bae84.c:1-21](../../src/ov039/event_state/SetMenuButtonsEnabled_020bae84.c).

Contract limits:

- Sets only the saved touch-down halfword; does not sample physical touch input.
- Why callers intentionally prime the previous state is not assigned an unproven refresh/debounce meaning.

## CreateAndLinkWidgetDescriptors

Identity: `ov027:020b8f7c`, THUMB, native extent 58 bytes (including any configured pool). Previous symbol: `func_ov027_020b8f7c`.

EU entrypoint: [eu/src/overlays/ov027/calls/CreateAndLinkWidgetDescriptors.c](../src/overlays/ov027/calls/CreateAndLinkWidgetDescriptors.c).

```c
void CreateAndLinkWidgetDescriptors(int ctx, int base, int count);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Creates count widgets from 0x58-byte descriptors, then makes a second pass to resolve their neighbors. Source: [eu/src/overlays/ov027/calls/CreateAndLinkWidgetDescriptors.c:1-11](../src/overlays/ov027/calls/CreateAndLinkWidgetDescriptors.c).
- Creates widget instances from descriptors, allocates records and appends to the root list. Source: [src/ov027/resource_container/CreateWidget_020b8cbc.c:1-152](../../src/ov027/resource_container/CreateWidget_020b8cbc.c).
- Resolves neighbor IDs through the complete widget list. Source: [src/ov027/resource_container/LinkElementNeighbors_020b85d0.c:1-60](../../src/ov027/resource_container/LinkElementNeighbors_020b85d0.c).

Contract limits:

- Neighbor linking occurs only after the entire creation pass.

## LoadWidgetDescriptorsFromFile

Identity: `ov027:020b8fb8`, THUMB, native extent 38 bytes (including any configured pool). Previous symbol: `func_ov027_020b8fb8`.

EU entrypoint: [eu/src/overlays/ov027/calls/LoadWidgetDescriptorsFromFile.c](../src/overlays/ov027/calls/LoadWidgetDescriptorsFromFile.c).

```c
void LoadWidgetDescriptorsFromFile(int param_1, int param_2, int param_3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Loads a temporary descriptor file, creates/links the requested count, then frees the file allocation. Source: [src/ov027/reviewed_helpers/func_ov027_020b8f98.c:1-8](../../src/ov027/reviewed_helpers/func_ov027_020b8f98.c).

Contract limits:

- Descriptor count is supplied by the caller; no file-derived count is invented.
- The load pointer is consumed before final null check.

## CreateWidgetImageEntry

Identity: `ov027:020b9098`, THUMB, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov027_020b9098`.

EU entrypoint: [eu/src/overlays/ov027/calls/CreateWidgetImageEntry.c](../src/overlays/ov027/calls/CreateWidgetImageEntry.c).

```c
void * CreateWidgetImageEntry();
```

The no-argument source view hides live manager and image-key inputs forwarded in registers; the result is the image-entry pointer. Do not publish the native empty argument list as a portable signature.

Demonstrated behavior and evidence:

- Forwards incoming manager and image key through PXI_Init_0204f020 to CreateImageEntry. Source: [src/ov027/library_nitro_pxi/PXI_Init_020b9078.c:1-5](../../src/ov027/library_nitro_pxi/PXI_Init_020b9078.c).
- The actual EU target takes manager,imageKey and returns CreateImageEntry(manager,imageKey). Source: [eu/src/calls/PXI_Init_0204f020.c:1-9](../src/calls/PXI_Init_0204f020.c).

Contract limits:

- This path is image allocation, not PXI FIFO initialization.
- The wrapper relies on register forwarding despite its no-argument declaration.

Additional native ABI observations:

- Recover the two real inputs and image-entry result before exporting a portable interface; preserve matched instructions.

## SetWidgetConfirmCallback

Identity: `ov027:020b90a0`, THUMB, native extent 6 bytes (including any configured pool). Previous symbol: `func_ov027_020b90a0`.

EU entrypoint: [eu/src/overlays/ov027/auto/SetWidgetConfirmCallback.c](../src/overlays/ov027/auto/SetWidgetConfirmCallback.c).

```c
void SetWidgetConfirmCallback(void *obj, u32 value);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Stores a callback word at widget+0xa8. Source: [src/ov027/unclassified_helpers/func_ov027_020b9080.c:1-5](../../src/ov027/unclassified_helpers/func_ov027_020b9080.c).
- FocusNode+0xa8 is onConfirm, invoked for A-key confirmation with the focused widget. Source: [src/ov027/resource_container/MoveFocusByDpad_020b88c0.c:1-144](../../src/ov027/resource_container/MoveFocusByDpad_020b88c0.c).
- The ID-based setter resolves the widget, then delegates this callback store. Source: [src/ov027/shared_engine/ResolveEntryStoreWord_020b9088.c:1-6](../../src/ov027/shared_engine/ResolveEntryStoreWord_020b9088.c).

Contract limits:

- Callback logical input is the widget pointer.
- Does not invoke the callback or change focus.

## SetWidgetRootInputCallback

Identity: `ov027:020b90b8`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov027_020b90b8`.

EU entrypoint: [eu/src/overlays/ov027/calls/SetWidgetRootInputCallback.c](../src/overlays/ov027/calls/SetWidgetRootInputCallback.c).

```c
void SetWidgetRootInputCallback(void *obj, u32 value);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Stores a callback word at widget root+0x644c. Source: [eu/src/overlays/ov027/calls/SetWidgetRootInputCallback.c:1-5](../src/overlays/ov027/calls/SetWidgetRootInputCallback.c).
- The exact field is onInput; dispatch passes focused widget and keys when a nonzero key mask is present. Source: [src/ov027/resource_container/MoveFocusByDpad_020b88c0.c:1-144](../../src/ov027/resource_container/MoveFocusByDpad_020b88c0.c).
- Native typed setup supplies OnPopupElementTouched as this root callback. Source: [eu/src/overlays/ov002/calls/InitMenuContext.c:1-396](../src/overlays/ov002/calls/InitMenuContext.c).

Contract limits:

- Callback uses two logical inputs: focused widget and key mask.
- A zero value clears the callback. No owner-wide reset is performed.

## GetFocusedWidget

Identity: `ov027:020b9114`, ARM, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov027_020b9114`.

EU entrypoint: [eu/src/overlays/ov027/auto/GetFocusedWidget.c](../src/overlays/ov027/auto/GetFocusedWidget.c).

```c
u32 GetFocusedWidget(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

The result is a borrowed widget pointer represented as a native u32; this is not an allocation.

Demonstrated behavior and evidence:

- Returns the pointer at widget root+0x646c. Source: [src/ov027/leaf_research/func_ov027_020b90f4.c:1-6](../../src/ov027/leaf_research/func_ov027_020b90f4.c).
- The focus setter writes that same field and updates previous/current focus animations. Source: [src/ov027/resource_container/SetFocusedWidget_020b96e4.c:1-37](../../src/ov027/resource_container/SetFocusedWidget_020b96e4.c).
- Reads that field as the currently focused widget for navigation and confirmation. Source: [src/ov027/resource_container/MoveFocusByDpad_020b88c0.c:1-144](../../src/ov027/resource_container/MoveFocusByDpad_020b88c0.c).
- The caller stores the returned pointer as focusElement when pushing a menu state. Source: [src/ov087/panel_state/PushPanelState_020c61b0.c:1-30](../../src/ov087/panel_state/PushPanelState_020c61b0.c).

Contract limits:

- Returns a borrowed widget pointer; no allocation or focus change occurs.
- No root/null validation is added.

## SetWidgetBasePosition

Identity: `ov027:020b91d0`, ARM, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov027_020b91d0`.

EU entrypoint: [eu/src/overlays/ov027/calls/SetWidgetBasePosition.c](../src/overlays/ov027/calls/SetWidgetBasePosition.c).

```c
void SetWidgetBasePosition(void *unused, void *dst, const void *src);
```

The current `void` declaration hides the base-position address left as the return value; callers and `GetWidgetPosition` establish the returned pointer view. This rename does not change its ABI.

Demonstrated behavior and evidence:

- Copies eight bytes to widget+0x34. Source: [eu/src/overlays/ov027/calls/SetWidgetBasePosition.c:1-7](../src/overlays/ov027/calls/SetWidgetBasePosition.c).
- Native matched position view identifies the +0x34 base position and +0x3c mutable offset. Source: [eu/src/overlays/ov027/WidgetPosition.h:1-45](../src/overlays/ov027/WidgetPosition.h).
- Returns the address of widget.position at +0x34. Source: [eu/src/overlays/ov027/calls/GetWidgetPosition.c:1-6](../src/overlays/ov027/calls/GetWidgetPosition.c).
- Combined placement derives indexed-record coordinates from this base and the separate offset. Source: [eu/src/overlays/ov027/calls/SetWidgetPosition.c:1-84](../src/overlays/ov027/calls/SetWidgetPosition.c).

Contract limits:

- Changes the base position only; does not immediately update indexed-record positions.
- The old private CreateWidget view calls this anchor; the verified native contract calls it position. Do not extend the old private labels into a public layout.

## ClearTileTableRowById

Identity: `ov027:020b9cf8`, ARM, native extent 64 bytes (including any configured pool). Previous symbol: `func_ov027_020b9cf8`.

EU entrypoint: [eu/src/overlays/ov027/calls/ClearTileTableRowById.c](../src/overlays/ov027/calls/ClearTileTableRowById.c).

```c
u32 ClearTileTableRowById(int pool, u32 key, u32 unused, u32 extra);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Finds the ID row, clears rowLength halfwords, and returns the row index; returns -1 when absent. Source: [eu/src/overlays/ov027/calls/ClearTileTableRowById.c:1-18](../src/overlays/ov027/calls/ClearTileTableRowById.c).
- The row helper supplies both the row pointer and its index, using table.rowLength. Source: [src/ov027/resource_container/GetTileTableRow_020b9948.c:1-28](../../src/ov027/resource_container/GetTileTableRow_020b9948.c).

Contract limits:

- Clears contents but does not remove the ID or mark the row dirty.
- Legacy extra arguments are unused.

## ClearTileTableRowByIdAdapter

Identity: `ov027:020b9d68`, ARM, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov027_020b9d68`.

EU entrypoint: [eu/src/overlays/ov027/calls/ClearTileTableRowByIdAdapter.c](../src/overlays/ov027/calls/ClearTileTableRowByIdAdapter.c).

```c
void * ClearTileTableRowByIdAdapter();
```

The no-argument source view forwards the caller registers. Its logical result is the row index or -1, not an owned pointer despite the private return type.

Demonstrated behavior and evidence:

- Tail-forwards the existing registers to ClearTileTableRowById. Source: [src/ov027/library_nitro_pxi/PXI_Init_020b9d48.c:1-5](../../src/ov027/library_nitro_pxi/PXI_Init_020b9d48.c).

Contract limits:

- Not a PXI function despite the shared source label.
- Preserve the row-index/-1 return contract.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov027/calls/LoadTrackerScreenResourcesFromSection.c LoadTrackerScreenResourcesFromSection --thumb
python tools/verify_idx.py src/overlays/ov027/calls/CreateTrackerTagSequencesFromSection.c CreateTrackerTagSequencesFromSection --thumb
python tools/verify_idx.py src/overlays/ov027/auto/IsPointInTrackerTouchBounds.c IsPointInTrackerTouchBounds
python tools/verify_idx.py src/overlays/ov027/auto/FindActiveTrackerScreenResourceById.c FindActiveTrackerScreenResourceById
python tools/verify_idx.py src/overlays/ov027/calls/FindFreeTrackerTagSequence.c FindFreeTrackerTagSequence
python tools/verify_idx.py src/overlays/ov027/auto/FindFreeTrackerScreenResource.c FindFreeTrackerScreenResource
python tools/verify_idx.py src/overlays/ov027/calls/CopyLatestValidTouchSample.c CopyLatestValidTouchSample
python tools/verify_idx.py src/overlays/ov027/calls/GetTrackerTouchSample.c GetTrackerTouchSample
python tools/verify_idx.py src/overlays/ov027/calls/UpdateTagTrackerAndTouch.c UpdateTagTrackerAndTouch
python tools/verify_idx.py src/overlays/ov027/calls/FreeTagTrackerPools.c FreeTagTrackerPools --thumb
python tools/verify_idx.py src/overlays/ov027/calls/LoadTagTrackerResourceFile.c LoadTagTrackerResourceFile --thumb
python tools/verify_idx.py src/overlays/ov027/calls/CreateTrackerRecord.c CreateTrackerRecord
python tools/verify_idx.py src/overlays/ov027/auto/DeactivateTrackerRecord.c DeactivateTrackerRecord
python tools/verify_idx.py src/overlays/ov027/calls/DeactivateAllTrackerRecords.c DeactivateAllTrackerRecords --thumb
python tools/verify_idx.py src/overlays/ov027/calls/RegisterTrackerScreenResource.c RegisterTrackerScreenResource
python tools/verify_idx.py src/overlays/ov027/calls/ReleaseTrackerScreenResource.c ReleaseTrackerScreenResource
python tools/verify_idx.py src/overlays/ov027/calls/ReleaseAllTrackerScreenResources.c ReleaseAllTrackerScreenResources --thumb
python tools/verify_idx.py src/overlays/ov027/auto/SetTrackerRecordX.c SetTrackerRecordX
python tools/verify_idx.py src/overlays/ov027/auto/SetTrackerRecordY.c SetTrackerRecordY
python tools/verify_idx.py src/overlays/ov027/calls/SetTrackerRecordPosition.c SetTrackerRecordPosition
python tools/verify_idx.py src/overlays/ov027/calls/InvokeTrackerRecordAtPosition.c InvokeTrackerRecordAtPosition
python tools/verify_idx.py src/overlays/ov027/auto/FindActiveBackgroundScreenResourceById.c FindActiveBackgroundScreenResourceById
python tools/verify_idx.py src/overlays/ov027/auto/MarkTrackerPreviousTouchDown.c MarkTrackerPreviousTouchDown
python tools/verify_idx.py src/overlays/ov027/calls/CreateAndLinkWidgetDescriptors.c CreateAndLinkWidgetDescriptors --thumb
python tools/verify_idx.py src/overlays/ov027/calls/LoadWidgetDescriptorsFromFile.c LoadWidgetDescriptorsFromFile --thumb
python tools/verify_idx.py src/overlays/ov027/calls/CreateWidgetImageEntry.c CreateWidgetImageEntry --thumb
python tools/verify_idx.py src/overlays/ov027/auto/SetWidgetConfirmCallback.c SetWidgetConfirmCallback --thumb
python tools/verify_idx.py src/overlays/ov027/calls/SetWidgetRootInputCallback.c SetWidgetRootInputCallback --thumb
python tools/verify_idx.py src/overlays/ov027/auto/GetFocusedWidget.c GetFocusedWidget
python tools/verify_idx.py src/overlays/ov027/calls/SetWidgetBasePosition.c SetWidgetBasePosition
python tools/verify_idx.py src/overlays/ov027/calls/ClearTileTableRowById.c ClearTileTableRowById
python tools/verify_idx.py src/overlays/ov027/calls/ClearTileTableRowByIdAdapter.c ClearTileTableRowByIdAdapter
bash tools/gate.sh
```

All entrypoints in this document pass their official function checks. The
combined106-entrypoint block passes the fresh108-module gate; affected function
bytes, resolved relocation targets/types and addends, and all module hashes
match the preserved pre-rename baseline. No algorithm, signature or native
matching-policy change is included. Verified-library receipts remain current.
