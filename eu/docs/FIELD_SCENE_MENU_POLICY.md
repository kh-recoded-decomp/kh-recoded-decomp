# Scene-entry overrides and field-menu advance policy

These overlay 001 helpers control scene-entry values, scene-slot resource loading, a patrol surface filter and eligibility for advancing the field-command menu. Their names describe the operations demonstrated by callers and readers. Existing source signatures and native behavior are preserved.

| EU identity | Name | Source after rename |
| --- | --- | --- |
| `ov001:02065f5c` | `ScriptCmd_SetSceneEntryValueOverride` | `eu/src/overlays/ov001/calls/ScriptCmd_SetSceneEntryValueOverride.c` |
| `ov001:020681b0` | `SetSceneEntryValueOverride` | `eu/src/overlays/ov001/calls/SetSceneEntryValueOverride.c` |
| `ov001:02067d0c` | `SetSceneSlotResourceLoadingEnabled` | `eu/src/overlays/ov001/calls/SetSceneSlotResourceLoadingEnabled.c` |
| `ov001:02068344` | `GetSceneEntryPatrolSurfaceFilterByte` | `eu/src/overlays/ov001/calls/GetSceneEntryPatrolSurfaceFilterByte.c` |
| `ov001:02077118` | `MatchesFieldMenuAutoAdvanceClass` | `eu/src/overlays/ov001/calls/MatchesFieldMenuAutoAdvanceClass.c` |
| `ov001:02077148` | `IsFieldMenuAutoAdvanceCandidate` | `eu/src/overlays/ov001/calls/IsFieldMenuAutoAdvanceCandidate.c` |

## Scene-entry owner and value override

`gFieldSceneEntryContext` is the pointer at `ov001:020a048c`. `CreateSceneContext` allocates and clears 0x10f4 bytes, installs that pointer, and initializes the byte at context +0x10c0 to 0xff. This allocation is distinct from the field-command menu work. The private source label `pendingId` for +0x10c0 does not establish a pending scene transition.

`SetSceneEntryValueOverride` stores its first input as a byte at context +0x10c0 and its full second input word at +0x10c4. The two existing getters establish the override contract:

| Getter | Matching-index result | Nonmatching result |
| --- | --- | --- |
| `GetSlotEntryValue(index)` | Word at context +0x10c4 | Word at selected table entry +0x10 |
| `GetMenuItemValue(index)` | Five times the word at context +0x10c4 | Word at selected table entry +0x14 |

Both getters compare the input index with a **signed-byte** read of +0x10c0. Byte 0xff therefore prevents a match for ordinary nonnegative indexes. Both getters fetch the table-entry pointer before this comparison; the override does not make an invalid table index safe. The setter has no index or NULL checks.

Native proof: `020681b8` stores the byte and `020681bc` stores the word. `02068012` and `0206803e` use `LDRSB`; `02068048/4a` performs the multiply by five. `CreateSceneContext` stores -1 to +0x10c0 at `0206745e`.

Source proof: `src/ov001/shared_engine/GetSlotEntryValue_02068000.c:23`, `src/ov001/shared_engine/GetMenuItemValue_0206802c.c:23`, and `src/ov001/shared_engine/CreateSceneContext_02067438.c:21`. The EU wrappers bind their shared global spelling to `gFieldSceneEntryContext`. `StageStateStartMusic` feeds the two getter results to `SetCachedSoundParams` (`eu/src/overlays/ov041/calls/StageStateStartMusic.c:23`), but that use alone does not define a common physical unit or an enumeration for the stored word.

`ScriptCmd_SetSceneEntryValueOverride` reads an integer operand and an FX32-decoded operand from successive 8-byte operand slots, forwards them to the setter, and returns literal 1. The original `gFieldScriptCommandHandlers` table registers it at index 184: native word `0209e9f8` is `02065f5d`, including the Thumb bit. `EnterPendingRoom` installs this table in global command-table slot 2 (`src/ov001/field_manager/EnterPendingRoom_02061e54.c:59`; EU binding at `eu/src/overlays/ov001/calls/EnterPendingRoom.c:14`). The handler's full native range is `02065f5c..02065f7d`.

The shared body remains `src/ov001/shared_engine/ScriptCmd_SetLinkMode_02065f5c.c:4`; the EU wrapper supplies the names. Its legacy `SetLinkMode` / `Ov002` spellings describe neither the proven owner nor the reader contract. The FX32 operand decoder is provenance, not proof of a distance, duration or count. The existing `u8`/`u32` setter declaration, two-int script handler and void setter result are retained; no extra cast, parameter or fluent return is introduced.

## Scene-slot resource-loading eligibility

`SetSceneSlotResourceLoadingEnabled(index, enable)` addresses a slot at context +0x18 + index Ã—0x108 and changes mask 0x08 of its flags byte at slot +0x104:

- Nonzero `enable` clears mask 0x08.
- Zero `enable` sets mask 0x08.

`LoadNextSceneSlotResources` reads this exact bit. When clear, it can acquire the primary and secondary resources and populate a load request. When set, it skips that slot and writes literal 8 back to its flags byte. The setter preserves other bits; that later skip path does not. `ResetSceneSlots` and `UpdateMenuItemLoading` pass this same scene context to the loader.

Native proof: the setter computes the 0x108 stride at `02067d14/16`, adds the +0x18 array base at `02067d18`, then clears mask 0x08 at `02067d26/28` or sets it at `02067d36/38`. The loader tests the bit at `020672da..020672e0`; its skip path writes flags 8 at `02067362`. `ResetSceneSlots` passes the owner in R2 at `02067738` and calls the loader at `0206773a`.

Source proof: `src/ov001/unclassified_helpers/LoadNextSceneSlotResources_020672a0.c:47`, `src/ov001/shared_engine/ResetSceneSlots_02067704.c:43`, and `src/ov001/field_manager/UpdateMenuItemLoading_02067750.c:51`. Callers configure opposite slot policies in `eu/src/overlays/ov041/calls/StageStateSetupSlots.c:15` and `eu/src/overlays/ov040/calls/ConfigureAreaSceneSlotsAndReset.c:17`.

The function controls eligibility for a load scan. It does not immediately load, unload or draw a slot. `SetSceneSlotDrawingEnabled` changes a separate mask 0x01. Existing bounds behavior and the void return remain unchanged.

## Patrol surface-filter byte

`GetSceneEntryPatrolSurfaceFilterByte(groupIndex, entryIndex)` follows context â†’ table â†’ entry pointer at table +8 + groupIndex Ã—4 â†’ definition pointer at entry +0x20. It returns the **signed first byte** of the 8-byte definition selected by `entryIndex`. Native `02068354` is `LDRSB`.

`EnterMenuItem` passes this same definition array, at stride 8, to `SyncMenuPanelDefinition` and `UpdatePointTriggerBox` (`src/ov001/field_manager/EnterMenuItem_02067618.c:66`). This does not establish a material, route, direction, actor ID or other gameplay enumeration for its first byte.

The name comes from the demonstrated patrol consumer. `UpdatePatrolMove` installs `FilterPatrolMoveSurface` as a surface callback (`src/ov001/field_objects/UpdatePatrolMove_02083f9c.c:364`; the EU wrapper binds that callback at `eu/src/overlays/ov001/calls/UpdatePatrolMove.c:38`). Under its record-kind, negative slot-index and kind-1-payload guards, the callback:

1. Uses the current scene-entry index and `-1 - signed object slotIndex` to select this byte.
2. Finds a candidate world-mesh entry and reads its signed byte at +2.
3. Returns false when those bytes are equal.

Native proof: `02084648..02084652` derives and narrows the definition index; `02084654` calls the getter; `02084676` obtains the mesh byte; `0208467a/7e` compares and rejects equality. Source: `eu/src/overlays/ov001/calls/FilterPatrolMoveSurface.c:38`.

The getter is an unchecked table accessor. Its existing int input types and the caller's signed-byte narrowing are preserved. Its name describes this proven consumer, without asserting that the byte has no other use.

## Field-menu auto-advance classification

`MatchesFieldMenuAutoAdvanceClass(record)` returns canonical 1 when either record word +0x10 equals 3 or record word +0 equals one of `0xa0`, `0xa2`, `0xa1`, `0xb1`; it returns 0 otherwise. The native body at `02077118..02077147` implements exactly those tests. No gameplay family name is assigned to those constants.

The real owner is an indexed command record returned by `GetRecordSlotPair1Entry`, as shown by `InitFieldCommandMenu`. The base predicate's old private parameter name `actor` does not identify an individual actor. The source type remains `s32 *`; the policy helper's four-word private struct is a partial view, not a complete record layout.

`IsFieldMenuAutoAdvanceCandidate(menu, record)` applies this classification with the following policy:

| Condition | Result |
| --- | --- |
| `IsFieldFlag13OrSessionFlagSet()` is false | Base classification |
| Policy active, record +8 is not -1 | False if session flag `0x360a` is set; otherwise base classification |
| Policy active, record +8 is -1, record +0x0c is not -1 | False if session flag `0x3609` is set; otherwise base classification |
| Policy active, both links equal -1 | Base classification |

The +8 link has priority. When it is present, +0x0c and flag `0x3609` are not checked. Native `02077156/5c` selects the first branch; `02077174/78` reaches the second only after the first link is -1. The first legacy `menu` argument is not read by this native helper, but its existing two-argument declaration remains intact. All return paths yield canonical 0 or the base predicate's canonical 0/1.

The consumer chain establishes **eligibility for automatic forward selection**, rather than command readiness or cooldown exemption:

1. `InitFieldCommandMenu` resolves the command record and stores the predicate result at menu-entry +0x2c (`eu/src/overlays/ov001/calls/InitFieldCommandMenu.c:260`, `eu/src/overlays/ov001/calls/InitFieldCommandMenu.c:272`; native `020774f0/020774fa`). For non-kind-5 entries, it separately counts false results (`eu/src/overlays/ov001/calls/InitFieldCommandMenu.c:225`; native `020773d4..020773dc`).
2. `RefreshFieldMenuSlots` tests stored entry +0x2c along with menu +0x134 and its progress condition, then calls `FieldMenu_TryEnterState3` (`src/ov001/field_manager/RefreshFieldMenuSlots_0207651c.c:132`, `src/ov001/field_manager/RefreshFieldMenuSlots_0207651c.c:153`; native `0207668c..02076694`, `02076724..0207672c`).
3. The callee applies its own count and policy guards, writes phase 3, saves the previous selection and calls `CycleMenuEntry` with direction 0 (`src/ov001/field_manager/FieldMenu_TryEnterState3_02075db8.c:20`; native `02075dea/02075e06`). For primary entries, direction 0 advances to `(index + 1) % count` (`src/ov001/field_manager/CycleMenuEntry_02075348.c:55`; native `0207537e/80`).

A true result alone does not change selection. The private `gauge.ready` and `menu.readyCount` names do not prove that the command is ready, available, on cooldown or exempt from cooldown. The exact predicate, link priority and additional transition guards are part of the porting contract.

## Validation record

Research captured all six complete native function ranges from the original BK9P ROM and checked that the decompressed overlay matches the extracted overlay byte for byte. The six source owners cover those exact ranges in active delinks and are inputs to the current final Ninja link. Official integration results follow below.


## Active EU sources

- [ScriptCmd_SetSceneEntryValueOverride](../src/overlays/ov001/calls/ScriptCmd_SetSceneEntryValueOverride.c).
- [SetSceneEntryValueOverride](../src/overlays/ov001/calls/SetSceneEntryValueOverride.c).
- [SetSceneSlotResourceLoadingEnabled](../src/overlays/ov001/calls/SetSceneSlotResourceLoadingEnabled.c).
- [GetSceneEntryPatrolSurfaceFilterByte](../src/overlays/ov001/calls/GetSceneEntryPatrolSurfaceFilterByte.c).
- [MatchesFieldMenuAutoAdvanceClass](../src/overlays/ov001/calls/MatchesFieldMenuAutoAdvanceClass.c).
- [IsFieldMenuAutoAdvanceCandidate](../src/overlays/ov001/calls/IsFieldMenuAutoAdvanceCandidate.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetSceneEntryValueOverride.c ScriptCmd_SetSceneEntryValueOverride --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetSceneEntryValueOverride.c SetSceneEntryValueOverride --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetSceneSlotResourceLoadingEnabled.c SetSceneSlotResourceLoadingEnabled --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSceneEntryPatrolSurfaceFilterByte.c GetSceneEntryPatrolSurfaceFilterByte --thumb
python tools/verify_idx.py src/overlays/ov001/calls/MatchesFieldMenuAutoAdvanceClass.c MatchesFieldMenuAutoAdvanceClass --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IsFieldMenuAutoAdvanceCandidate.c IsFieldMenuAutoAdvanceCandidate --thumb
bash tools/gate.sh
```
