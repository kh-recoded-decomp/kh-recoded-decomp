# Native runtime views and handoff DATA (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

The equipment cache is the important portability boundary: the native named array holds twelve records, while four more records are split across the following two numeric objects. The sixteen-record reader/writer span is 192 bytes. Its two-byte fragment is part of a four-byte state word, not a new field to insert into a portable struct.

The wireless object is removed from a pre-sleep callback list, despite its caller being named SNDi_LockMutex. The field-session argument block is separate from the phase-dependent scene-result/profile header and cached strings. These names do not resolve every private view into a single host layout.

## Inventory and evidence

### `main:02059804` → `gWmPreSleepCallbackStorage`

Previous label `data_02059804`; size **16 bytes**; source `eu/src/data/bss/Bss_main_020597fc.c`.

16 BSS bytes used as a PMSleepCallbackInfo-compatible list node, with four bytes beyond the native twelve-byte node retained opaque.

The function currently named SNDi_LockMutex passes this address to PM_DeletePreSleepCallback, whose actual body removes that node from PMi_PreSleepCallbackList. WmReceiveFifo calls the wrapper on wireless disable/end or initialization failure paths.

Limits: This is not a sound mutex. No registration writer, installed callback or extra-tail field is inferred from the removal path; preserve all 16 bytes.

Direct pinned references:

- `eu/src/calls/SNDi_LockMutex.c` → `src/arm9/library_nitro_snd/SNDi_LockMutex_02011404.c`; line(s) 2, 5.
- `eu/src/data/bss/Bss_main_020597fc.c`; line(s) 5.

Additional base-view proof:

- `eu/libs/nitro/spi/calls/PM_DeletePreSleepCallback.c`.
- `eu/src/calls/WmReceiveFifo.c`.
- `include/nitro/spi.h`.

### `main:02060058` → `gEquipmentSlotCacheEntry12StateLow`

Previous label `data_02060058`; size **2 bytes**; source `eu/src/data/bss/EquipmentSlotWorkTail.c`.

2 BSS bytes: low halfword of cached equipment entry 12 state.

RefreshSlotRecordCache processes sixteen twelve-byte CachedSlot records starting at 0205ffc8. The separately defined gEquipmentSlotWork contains only the first twelve native records (144 bytes), so entry 12 begins exactly at 02060058.

Limits: This is a fragment of a four-byte state word, not a standalone equipment flag. Keep the native two-byte split and the remaining 46 bytes; a host cache needs the full logical span used by sixteen-record consumers.

Direct pinned references:

- `eu/src/data/bss/EquipmentSlotWorkTail.c`; line(s) 4.

Additional base-view proof:

- `eu/src/calls/RefreshSlotRecordCache.c`.
- `eu/src/calls/RebuildRecordCounters.c`.
- `eu/src/calls/MoveEquipmentSlot.c`.
- `eu/src/calls/AddSlotLevelProgress.c`.
- `eu/src/calls/ConsumeSlotItemUse.c`.
- `eu/src/data/bss/gEquipmentSlotWork.c`.

### `main:0206005a` → `gEquipmentSlotCacheExtraEntriesTail`

Previous label `data_0206005a`; size **46 bytes**; source `eu/src/data/bss/Bss_main_0206005a.c`.

46 BSS bytes: high halfword of entry 12 state, its value/packed record and complete entries 13..15.

Together with the two-byte prefix this completes four additional cached records. RefreshSlotRecordCache writes their state/value/entry; MoveEquipmentSlot and level/item-use helpers reach cached records through the gEquipmentSlotWork base with twelve-byte stride.

Limits: The native declaration gEquipmentSlotWork[12] does not prove that the logical cache stops there. Preserve 144+2+46=192 bytes and do not allocate only twelve host records.

Direct pinned references:

- `eu/src/data/bss/Bss_main_0206005a.c`; line(s) 3.

Additional base-view proof:

- `eu/src/calls/RefreshSlotRecordCache.c`.
- `eu/src/calls/RebuildRecordCounters.c`.
- `eu/src/calls/MoveEquipmentSlot.c`.
- `eu/src/calls/AddSlotLevelProgress.c`.
- `eu/src/calls/ConsumeSlotItemUse.c`.
- `eu/src/data/bss/gEquipmentSlotWork.c`.

### `main:02060574` → `gResourcePaletteUploadCallbackStorage`

Previous label `data_02060574`; size **16 bytes**; source `eu/src/data/bss/Bss_main_02060570.c`.

16 BSS bytes whose first word is the palette upload callback used by SubmitResourcePaletteUpload; the other twelve bytes remain opaque.

SubmitResourcePaletteUpload invokes the leading function with source record+relativeOffset38, destination derived from key word+2c and byte count halfword30<<3, then sets the loaded bit at record+32.

Limits: No initializer or default callback target is assigned here. Preserve the complete storage, callback ABI and tail; this is not itself palette color data.

Direct pinned references:

- `eu/src/calls/SubmitResourcePaletteUpload.c` → `src/arm9/runtime/func_0202d204.c`; line(s) 3, 6.
- `eu/src/data/bss/Bss_main_02060570.c`; line(s) 6.

### `main:02060848` → `gContactProjectionFallbackEnabled`

Previous label `data_02060848`; size **4 bytes**; source `eu/src/data/bss/Bss_main_02060848.c`.

4 BSS bytes enabling the fallback contact-normal projection path.

When ResolveContactPushOut finds no candidate in its contact-selection loop, zero returns immediately; nonzero calls ProjectMotionAgainstContactNormals and returns. SpawnGroupMemberGrid sets the word to 1. StartFieldSession and HandleSessionScriptResult reset it to 0.

Limits: This is a global mode flag, not state owned by one group or a general disable-collision flag. The name describes only the demonstrated fallback branch.

Direct pinned references:

- `eu/src/calls/ResolveContactPushOut.c` → `src/arm9/spatial_queries/ResolveContactPushOut_020382b0.c`; line(s) 96, 262.
- `eu/src/data/bss/Bss_main_02060848.c`; line(s) 3.
- `eu/src/overlays/ov001/calls/HandleSessionScriptResult.c` → `src/ov001/unclassified_helpers/HandleSessionScriptResult_0206269c.c`; line(s) 50, 138.
- `eu/src/overlays/ov001/calls/StartFieldSession.c` → `src/ov001/field_manager/StartFieldSession_02061468.c`; line(s) 110, 379.
- `eu/src/overlays/ov032/calls/SpawnGroupMemberGrid.c` → `src/ov032/object_group/SpawnGroupMemberGrid_020bf468.c`; line(s) 78, 108.

### `main:02060850` → `gPendingFieldSessionArgs`

Previous label `data_02060850`; size **12 bytes**; source `eu/src/data/bss/Bss_main_0206084c.c`.

12 BSS bytes consumed through the native FieldSessionArgs view: two leading halfwords, kind byte, two additional bytes, mode/options byte and final word.

Title/panel/session-exit writers fill this record before switching scenes. EnterSceneSlotAtSpawn writes bytes 5/6. StartFieldSession selects this global when no explicit argument is supplied and clears all twelve bytes after initializing the field session. InitDifficultyConfigBlock also prepares it from persistent packed bits.

Limits: The private field labels differ across paths; preserve exact widths and bits rather than imposing rank/spawn/difficulty meanings for every case. This is not the separate scene-result/profile handoff header.

Direct pinned references:

- `eu/src/calls/InitDifficultyConfigBlock.c` → `src/arm9/packed_bits/func_02027558.c`; line(s) 12, 23, 24, 25, 26, 28.
- `eu/src/data/bss/Bss_main_0206084c.c`; line(s) 4.
- `eu/src/overlays/ov000/calls/FinishTitlePanel.c`; line(s) 16, 38, 39, 40.
- `eu/src/overlays/ov001/calls/EnterSceneSlotAtSpawn.c` → `src/ov001/unclassified_helpers/EnterSceneSlotAtSpawn_02064828.c`; line(s) 23, 41, 42.
- `eu/src/overlays/ov001/calls/ExitSessionAndCommitSave.c`; line(s) 63, 85, 86, 87, 88, 89, 90, 91, 92.
- `eu/src/overlays/ov001/calls/StartFieldSession.c` → `src/ov001/field_manager/StartFieldSession_02061468.c`; line(s) 108, 220, 376.
- `eu/src/overlays/ov004/calls/ReleaseScrollTextWork.c` → `src/ov004/scroll_text/ReleaseScrollTextWork_020616d4.c`; line(s) 55, 84, 85, 86, 87.
- `eu/src/overlays/ov013/calls/LeavePanelScene.c` → `src/ov013/panel_state/LeavePanelScene_0206f978.c`; line(s) 57, 75, 76, 77, 78, 79, 80.

### `main:0206085c` → `gSceneHandoffSharedHeader`

Previous label `data_0206085c`; size **28 bytes**; source `eu/src/data/bss/Bss_main_0206084c.c`.

28 BSS bytes preceding the cached owner nickname and message allocations, with several phase-specific native views.

ExitSessionAndCommitSave passes this address as the argument to pending scene 3. Panel exit/profile code stores and reads checksum, mode and selection fields through the header and following cached strings; results code uses a separate mode/rank/seed view before SetupStageParams consumes it.

Limits: This is shared phase-dependent storage, not one proved universal C struct. Keep the 28-byte native header, following 22-byte nickname and 58-byte message allocations, and each actual reader/writer contract; do not merge incompatible private typedefs.

Direct pinned references:

- `eu/src/data/bss/Bss_main_0206084c.c`; line(s) 3.
- `eu/src/overlays/ov001/calls/ExitSessionAndCommitSave.c`; line(s) 64, 96.
- `eu/src/overlays/ov002/calls/InitProfilePanel.c`; line(s) 32, 75, 87, 101.
- `eu/src/overlays/ov013/calls/ConfigureOv013PlayerCardPageMode.c`; line(s) 9, 21.
- `eu/src/overlays/ov013/calls/DrawPanelHeaderTexts.c` → `src/ov013/panel_state/DrawPanelHeaderTexts_0206eef4.c`; line(s) 19, 28, 34.
- `eu/src/overlays/ov013/calls/InitPanelScene_0206c480.c` → `src/ov013/panel_state/InitPanelScene_0206c480.c`; line(s) 59, 101, 103, 107, 116, 117, 134.
- `eu/src/overlays/ov013/calls/InitRecordResultScreen.c` → `src/ov013/panel_state/InitRecordResultScreen_0206df40.c`; line(s) 128, 218, 238, 249, 263, 274, 275, 276, 281, 282, 285, 293.
- `eu/src/overlays/ov013/calls/InitRecordScreenGraphics.c` → `src/ov013/panel_state/InitRecordScreenGraphics_0206da20.c`; line(s) 103, 207.
- `eu/src/overlays/ov013/calls/LeavePanelScene.c` → `src/ov013/panel_state/LeavePanelScene_0206f978.c`; line(s) 58, 81, 83, 84, 86, 89, 93, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104.
- `eu/src/overlays/ov013/calls/ResolvePanelExitMode.c` → `src/ov013/panel_state/ResolvePanelExitMode_020717c0.c`; line(s) 68, 91, 97, 102, 110.
- `eu/src/overlays/ov013/calls/UpdatePanelEntryState.c` → `src/ov013/panel_state/UpdatePanelEntryState_020718e0.c`; line(s) 28, 79.
- `eu/src/overlays/ov013/calls/UpdatePanelResultState.c` → `src/ov013/panel_state/UpdatePanelResultState_020724c0.c`; line(s) 15, 47.
- `eu/src/overlays/ov034/calls/CloseResultsSession.c`; line(s) 28, 67.
- `eu/src/overlays/ov034/calls/FinishResultsScreen.c` → `src/ov034/reviewed_helpers/FinishResultsScreen_020bdc3c.c`; line(s) 6, 7.
- `eu/src/overlays/ov034/calls/HandleResultsInput.c`; line(s) 96, 249, 306, 311, 312, 398, 399.
- `eu/src/overlays/ov034/calls/InitResultsScene.c`; line(s) 199, 283, 284, 285, 287, 288, 289, 293, 297, 298, 305, 306, 308, 382, 384, 386, 389, 396, 409, 410.
- `eu/src/overlays/ov034/calls/SetupStageParams.c` → `src/ov034/unclassified_helpers/SetupStageParams_020bdf10.c`; line(s) 105, 146, 162, 163, 164, 165, 173, 174, 176, 178, 193, 194.


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
