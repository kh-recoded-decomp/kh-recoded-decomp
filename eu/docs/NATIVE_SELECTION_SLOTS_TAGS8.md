# Selection header, saved slots and tagged-entry DATA (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

## Runtime views and native partitions

The selection header has two different counts: a selection-record count byte and a registered-pointer count word. The packed selection block has a separate twelve-byte tail. Session slots form one 96-byte logical range split into native objects of 4,1 and 91 bytes. Registered tagged-entry pointers have capacity 32, while the packed entry pool has capacity 64. Three 0x144-byte selection records are separate from those arrays. Naming preserves all boundaries, casts, bit widths and current bounds behavior.

## Inventory and evidence

### `main:020608c8` → `gSelectionRuntimeHeader`

Previous label `data_020608c8`; existing ELF size **8 bytes**. Source: `eu/src/data/bss/Bss_main_020608c8.c`.

8-byte BSS header: selection-record count byte 0 (remaining first-word bytes unspecified) and registered tagged-entry count int+4.

InitPlayerData sets the first byte to 1. RegisterTaggedEntry appends a pointer using the count at+4 and increments it; MarkTaggedEntry/ClearHandleActiveFlags iterate that count. Selection/party consumers use the first byte as their record count.

Limits: Larger native views rooted here also reach gSelectionPackedValues and its tail. Do not treat the eight-byte header as the whole selection state or infer that both counts always match.

Pinned references:

- `eu/src/calls/ClearHandleActiveFlags.c` → `src/arm9/resource_management/ClearHandleActiveFlags_0204ffd0.c`; reference line(s) 8, 15.
- `eu/src/calls/DetachHandle.c` → `src/arm9/resource_management/DetachHandle_0204fdf8.c`; reference line(s) 13, 21.
- `eu/src/calls/GetParamWord20.c` → `src/arm9/shared_engine/GetParamWord20_02050650.c`; reference line(s) 3, 8.
- `eu/src/calls/InitPlayerData.c` → `src/arm9/shared_engine/InitPlayerData_0204f718.c`; reference line(s) 11, 23.
- `eu/src/calls/LoadSelectionPackedValues.c` → `src/arm9/overlay_selection/LoadSelectionPackedValues_0205053c.c`; reference line(s) 26, 37.
- `eu/src/calls/MarkTaggedEntry.c` → `src/arm9/overlay_selection/MarkTaggedEntry_0204ff7c.c`; reference line(s) 10, 17.
- `eu/src/calls/RegisterTaggedEntry.c` → `src/arm9/overlay_selection/RegisterTaggedEntry_0204ff18.c`; reference line(s) 21, 37, 38.
- `eu/src/calls/ResetParamWord8.c` → `src/arm9/shared_engine/ResetParamWord8_02050528.c`; reference line(s) 3, 7.
- `eu/src/calls/SetParamHalf18.c` → `src/arm9/shared_engine/SetParamHalf18_02050630.c`; reference line(s) 3, 7.
- `eu/src/calls/SetParamWord20.c` → `src/arm9/shared_engine/SetParamWord20_02050640.c`; reference line(s) 3, 7.
- `eu/src/calls/SetParamWord8.c` → `src/arm9/shared_engine/SetParamWord8_02050620.c`; reference line(s) 1, 3.
- `eu/src/calls/SetupFlaggedSelectionRecords.c` → `src/arm9/overlay_selection/SetupFlaggedSelectionRecords_0204f778.c`; reference line(s) 12, 21, 23, 24, 25, 28, 29, 30, 32.
- `eu/src/data/bss/Bss_main_020608c8.c`; reference line(s) 3.
- `eu/src/overlays/ov001/calls/FieldObject_UpdateZoneTrigger.c` → `src/ov001/field_objects/FieldObject_UpdateZoneTrigger_02081728.c`; reference line(s) 35, 98.
- `eu/src/overlays/ov001/calls/InitPartyState.c`; reference line(s) 27, 51, 65, 67, 74.
- `eu/src/overlays/ov001/calls/LoadModeSprites.c` → `src/ov001/unclassified_helpers/LoadModeSprites_0206d308.c`; reference line(s) 41, 73, 105.
- `eu/src/overlays/ov001/calls/StartFieldSession.c` → `src/ov001/field_manager/StartFieldSession_02061468.c`; reference line(s) 109, 368.
- `eu/src/overlays/ov021/calls/LoadCharacterSoundCueTable.c` → `src/ov021/object_state/LoadPathGraph_020a7cc8.c`; reference line(s) 71, 112.
- `eu/src/overlays/ov028/calls/InitFieldOverlayState.c` → `src/ov028/overlay_state/InitFieldOverlayState_020ba3e0.c`; reference line(s) 32, 82, 84, 88, 91.
- `eu/src/overlays/ov028/calls/SetupSceneFromParams.c` → `src/ov028/overlay_state/SetupSceneFromParams_020bb0a4.c`; reference line(s) 21, 43, 45.
- `eu/src/overlays/ov032/calls/InitSceneOverlayState.c` → `src/ov032/unclassified_helpers/InitSceneOverlayState_020ba3e0.c`; reference line(s) 59, 99, 101.
- `eu/src/overlays/ov032/calls/StartMoviePlayback.c` → `src/ov032/shared_engine/StartMoviePlayback_020bb4e0.c`; reference line(s) 21, 39, 41.
- `eu/src/overlays/ov053/calls/StartAreaMusic.c` → `src/ov053/unclassified_helpers/StartAreaMusic_020d294c.c`; reference line(s) 28, 47.
- `eu/src/overlays/ov054/calls/InitOverlay054Entity.c` → `src/ov054/object_factory/InitOverlay054Entity_020d21f4.c`; reference line(s) 44, 74.
- `eu/src/overlays/ov075/calls/AddToSelectionCounters.c` → `src/ov075/unclassified_helpers/AddToSelectionCounters_020ce700.c`; reference line(s) 10, 15.
- `eu/src/overlays/ov075/calls/AreItemPickerSessionStatesZero.c`; reference line(s) 8, 16.
- `eu/src/overlays/ov075/calls/IsItemPickerPartyHpFull.c`; reference line(s) 9, 17.
- `eu/src/overlays/ov076/calls/AddToSelectionCounters_020ca530.c` → `src/ov076/unclassified_helpers/AddToSelectionCounters_020ca510.c`; reference line(s) 10, 15.
- `eu/src/overlays/ov076/calls/AreSlotMenuSessionStatesZero.c`; reference line(s) 8, 16.
- `eu/src/overlays/ov076/calls/IsSlotMenuPartyHpFull.c`; reference line(s) 9, 17.
- `eu/src/overlays/ov077/calls/AddToSelectionCounters_020c7564.c` → `src/ov077/unclassified_helpers/AddToSelectionCounters_020c7544.c`; reference line(s) 10, 15.
- `eu/src/overlays/ov077/calls/AreItemScreenSessionStatesZero.c`; reference line(s) 8, 16.
- `eu/src/overlays/ov077/calls/IsItemScreenPartyHpFull.c`; reference line(s) 9, 17.

### `main:020608d4` → `gSelectionPackedValueTail`

Previous label `data_020608d4`; existing ELF size **12 bytes**. Source: `eu/src/data/bss/Bss_main_020608d0.c`.

12-byte BSS continuation after the already-named four-byte gSelectionPackedValues base: three u16 saved values at+0/+2/+4, additional halfword at+6 and raw word at+8.

StoreSelectionPackedValues copies six bytes to this address and persists the three halfwords. LoadSelectionPackedValues fills them from packed bits. SetParamHalf18 writes global headerBase+0x12, which is tail+6; Get/SetParamWord20 read/write headerBase+0x14, which is tail+8.

Limits: The combined base+tail logical range is sixteen bytes, while some native views describe only savedByte plus three halfwords. Preserve the split and raw extra halfword/word; do not infer HP, level or BOOL from private labels alone.

Pinned references:

- `eu/src/calls/StoreSelectionPackedValues.c` → `src/arm9/overlay_selection/StoreSelectionPackedValues_020505b4.c`; reference line(s) 13, 23.
- `eu/src/data/bss/Bss_main_020608d0.c`; reference line(s) 3.

### `main:020608e0` → `gSessionSlotEntriesPrefix`

Previous label `data_020608e0`; existing ELF size **4 bytes**. Source: `eu/src/data/bss/Bss_main_020608e0.c`.

4-byte BSS prefix of a logical eight-record array, stride 12 bytes: first record signed ID halfword at+0 and two padding bytes.

ResetSlotEntries, LoadSlotEntriesFromBits and SaveSlotEntriesToBits all index from this base with a twelve-byte record stride and loop count 8. The following one-byte and 91-byte native objects complete the 96-byte logical range.

Limits: Do not resize this four-byte symbol into a 96-byte array or discard padding. GetPlayerFlagRecord returns this base+index*12 through an integer pointer ABI; that inherited name does not define a separate owner.

Pinned references:

- `eu/src/calls/AddToStackSlot.c` → `src/arm9/record_management/AddToStackSlot_02050250.c`; reference line(s) 17, 36, 37, 41, 46, 47.
- `eu/src/calls/GetPlayerFlagRecord.c` → `src/arm9/shared_variants/GetPlayerFlagRecord_0205036c.c`; reference line(s) 1, 4.
- `eu/src/calls/LoadSlotEntriesFromBits.c` → `src/arm9/shared_engine/LoadSlotEntriesFromBits_02050120.c`; reference line(s) 10, 19.
- `eu/src/calls/ResetSlotEntries.c` → `src/arm9/shared_engine/ResetSlotEntries_0205020c.c`; reference line(s) 11, 18, 19, 20.
- `eu/src/calls/SaveSlotEntriesToBits.c` → `src/arm9/shared_engine/SaveSlotEntriesToBits_02050194.c`; reference line(s) 10, 19.
- `eu/src/data/bss/Bss_main_020608e0.c`; reference line(s) 3.

### `main:020608e4` → `gSessionSlotEntriesFirstState`

Previous label `data_020608e4`; existing ELF size **1 bytes**. Source: `eu/src/data/bss/Bss_main_020608e4.c`.

One-byte BSS object at offset 4 of session slot record 0.

ResetSlotEntries clears each record state. The packed loader reads four ID bits and nine state bits per record starting at 0x3729, maps positive IDs to id+0xca and narrows state to this u8 field. SaveSlotEntriesToBits writes the runtime byte as a nine-bit field.

Limits: This is a raw state byte, not a normalized flag. Preserve the nine-bit wire/eight-bit runtime truncation and empty-ID behavior; no field widening is proposed.

Pinned references:

- `eu/src/data/bss/Bss_main_020608e4.c`; reference line(s) 8.

### `main:020608e5` → `gSessionSlotEntriesTail`

Previous label `data_020608e5`; existing ELF size **91 bytes**. Source: `eu/src/data/bss/Bss_main_020608e4.c`.

91-byte BSS continuation: record 0byte+5 and remaining padding, followed by records 1..7. With the preceding 4+1 bytes it completes eight 12-byte records.

ResetSlotEntries writes 99 to each record byte+5, id=-1 and state=0. Load/SaveSlotEntriesFrom/ToBits reach the subsequent records through the twelve-byte array view rooted at 020608e0.

Limits: The byte+5 meaning is not established merely by the native typedef calling it level. Preserve all 91 bytes and eight records; this tail is not an independent seven-record allocation.

Pinned references:

- `eu/src/data/bss/Bss_main_020608e4.c`; reference line(s) 7.

### `main:02060940` → `gRegisteredTaggedEntryPointers`

Previous label `data_02060940`; existing ELF size **128 bytes**. Source: `eu/src/data/bss/Bss_main_020608e4.c`.

128-byte BSS array of 32 native pointers to tagged entries.

RegisterTaggedEntry obtains/adds an entry for selection record 0 and appends its pointer here using the separate taggedCount. MarkTaggedEntry sets flag bit 31 on a matching entry; ClearHandleActiveFlags clears that bit on every tracked pointee.

Limits: These pointers borrow entries from their table; the array does not own separate entry allocations. No append capacity guard is added; its 32-pointer capacity differs from the 64-entry backing pool.

Pinned references:

- `eu/src/calls/ClearHandleActiveFlags.c` → `src/arm9/resource_management/ClearHandleActiveFlags_0204ffd0.c`; reference line(s) 9, 16.
- `eu/src/calls/MarkTaggedEntry.c` → `src/arm9/overlay_selection/MarkTaggedEntry_0204ff7c.c`; reference line(s) 11, 18.
- `eu/src/calls/RegisterTaggedEntry.c` → `src/arm9/overlay_selection/RegisterTaggedEntry_0204ff18.c`; reference line(s) 22, 37.
- `eu/src/data/bss/Bss_main_020608e4.c`; reference line(s) 6.

### `main:02060a50` → `gTaggedEntryPool`

Previous label `data_02060a50`; existing ELF size **256 bytes**. Source: `eu/src/data/bss/Bss_main_020608e4.c`.

256-byte BSS backing array of 64 packed four-byte records: ID 18 bits, order 6 bits, value 7 bits and high flag bit.

When a table entries pointer is NULL, AddTaggedEntry points it here, clears 0x100 bytes and initializes each ID to 0x3ffff. It reuses an existing ID or appends at table->count, assigns order/value/flag and returns the entry pointer.

Limits: The source has no full-capacity failure guard. Preserve the bitfield widths, shared static backing, sentinel and table count behavior; this is not a 64-pointer pool.

Pinned references:

- `eu/src/calls/AddTaggedEntry.c` → `src/arm9/record_management/AddTaggedEntry_0204fe2c.c`; reference line(s) 15, 26, 27.
- `eu/src/data/bss/Bss_main_020608e4.c`; reference line(s) 4.

### `main:02060b50` → `gOverlaySelectionRecords`

Previous label `data_02060b50`; existing ELF size **972 bytes**. Source: `eu/src/data/bss/Bss_main_020608e4.c`.

972-byte BSS array of three 0x144-byte selection records.

InitPlayerData clears all three records; GetOverlaySelectionRecord returns base+selectionIndex*0x144. GetSelectionSlotPosition uses record byte 0 as overlaySet. RegisterTaggedEntry/GetPlayerEntryCount access the embedded tagged-entry table at+0x13c, with the demonstrated count getter restricted to player 0.

Limits: Most record fields remain opaque. Do not export one full portable actor/player struct from these partial views or add index checks in the naming block. The returned records are borrowed global storage.

Pinned references:

- `eu/src/calls/GetOverlaySelectionRecord.c` → `src/arm9/overlay_selection/GetOverlaySelectionRecord.c`; reference line(s) 7, 10.
- `eu/src/calls/GetPlayerEntryCount.c` → `src/arm9/data_access/GetPlayerEntryCount_02050050.c`; reference line(s) 20, 30.
- `eu/src/calls/InitPlayerData.c` → `src/arm9/shared_engine/InitPlayerData_0204f718.c`; reference line(s) 13, 26.
- `eu/src/calls/IsPlayerEntryFlagSet.c` → `src/arm9/data_access/IsPlayerEntryFlagSet_02050014.c`; reference line(s) 19, 29.
- `eu/src/data/bss/Bss_main_020608e4.c`; reference line(s) 3.


## Byte-exact validation

103 DATA identities retain their source paths, native sizes and storage.
405/410 affected official function checks pass; the remaining
5 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 474 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
