# Managed-actor queries, field policies and event-header values

These six overlay 001 helpers reset a collision-query cursor, record command bookkeeping, test recorded script-handler bindings, pause patrol progression and read a stage-event header value. Their existing source signatures, return behavior and native operations are preserved.

| EU identity | Name | Source after rename |
| --- | --- | --- |
| `ov001:0206dc98` | `ResetManagedActorOverlapCursor` | `eu/src/overlays/ov001/calls/ResetManagedActorOverlapCursor.c` |
| `ov001:0206df78` | `RecordCategory4CommandDispatch` | `eu/src/overlays/ov001/calls/RecordCategory4CommandDispatch.c` |
| `ov001:0206e2b0` | `IsSlot7HandlerIndex7Flag370dSet` | `eu/src/overlays/ov001/calls/IsSlot7HandlerIndex7Flag370dSet.c` |
| `ov001:0206e31c` | `IsSlot7HandlerIndex6Flag3715Set` | `eu/src/overlays/ov001/calls/IsSlot7HandlerIndex6Flag3715Set.c` |
| `ov001:020846b8` | `PatrolFieldObject_PausePhase4Updates` | `eu/src/overlays/ov001/calls/PatrolFieldObject_PausePhase4Updates.c` |
| `ov001:02087784` | `ReadStageObjectEventHeaderValuePlusOne` | `eu/src/overlays/ov001/calls/ReadStageObjectEventHeaderValuePlusOne.c` |

## Managed-actor overlap cursor

`ResetManagedActorOverlapCursor` clears work +0xf8 if `gManagedActorGlobals` exists. The owner is the pointer at `ov001:020a04bc`. This word is an iteration cursor, established by the reader and incrementing writer in `FindNextOverlappingEntry`:

- The query starts at `manager->cursor` and stops at managed-actor count +0x7c.
- Before testing each actor, it increments the stored cursor, including when that actor has no usable volume or does not overlap.
- A successful call returns that actor while retaining the cursor for the next call. Resetting to zero starts a later query from the first entry.

Source: `src/ov001/shared_engine/FindNextOverlappingEntry_0206dcac.c:22` defines count +0x7c, padding through +0xf7 and cursor +0xf8; the query loop begins at line 42 and increments the cursor at line 47. The EU wrapper binds this shared owner to `gManagedActorGlobals` (`eu/src/overlays/ov001/calls/FindNextOverlappingEntry.c:4`).

Native proof: `0206dcca/0206dccc` reads +0xf8, `0206dcd0` reads +0x7c, and `0206dcea/0206dcee` increments the stored cursor before the actor volume callback at `0206dd00`. The reset guards the owner at `0206dc9c/0206dc9e` and writes zero at `0206dca4`.

The separate `RefreshStageEntriesIfLoaded` wrapper checks `gStageManager` before calling this reset (`src/ov001/shared_engine/RefreshStageEntriesIfLoaded_020992cc.c:6`). That legacy name does not establish actor refresh, resource reload or timer work. The reset changes only the query cursor, preserving its void return and NULL-safe behavior.

## Category-4 command bookkeeping

`RecordCategory4CommandDispatch` performs three independent actions:

1. If `GetCtxModeByte()` returns zero, set session flag `0x3707`.
2. Always call `AddSessionCounter(6, 1)`.
3. Read 17 packed save bits starting at bit offset `0xb26`; increment and write only when the unsigned value is below 99999.

The third action is a conditional increment, not a clamp: a value already at or above 99999 remains unchanged. `GetCtxModeByte` reads the scene-context signed byte at +0x0c; it is distinct from the session phase and script-handler binding index (`src/ov001/shared_engine/GetCtxModeByte_02068084.c:3`). No gameplay meaning is assigned to that byte or to flag `0x3707`.

The narrow command-category name comes from `SelectMenuMember`: its category-4 case invokes this bookkeeping before the selected command handler (`src/ov021/object_state/SelectMenuMember_020ad980.c:89`, `src/ov021/object_state/SelectMenuMember_020ad980.c:99`). Invocation therefore does not prove successful command execution. The second caller is command `0x1f` in `HandleRewardActorCommand`, after its optional reset callback (`src/ov054/unclassified_helpers/HandleRewardActorCommand_020d2774.c:147`, `src/ov054/unclassified_helpers/HandleRewardActorCommand_020d2774.c:165`). Neither caller proves a localized statistic name or a gameplay action family.

Native proof: `0206df88/0206df8a` supplies counter index 6 and amount 1; `0206dfa2` skips the save write when the unsigned value is at least 99999. Calls are independently present in original overlay 021 at `020ada6e` and overlay 054 at `020d2a70`.

## Recorded slot-7 handler predicates

| Predicate | True exactly when |
| --- | --- |
| `IsSlot7HandlerIndex7Flag370dSet()` | Recorded slot-7 binding index is 7 and session flag `0x370d` is set |
| `IsSlot7HandlerIndex6Flag3715Set()` | Recorded slot-7 binding index is 6 and session flag `0x3715` is set |

Both return canonical 0 or 1. `BindScriptHandlersSlot7` selects a handler-table/overlay record, installs a non-NULL table in engine slot 7, optionally loads its overlay, and records the selected index at session +0x18. `GetScriptHandlerSlot7Index` reads that byte with signed extension. These are recorded binding selections, not universal session-kind, character or form enums. See `FIELD_SCRIPT_BINDING_INDICES.md` for the producer contract.

Source: `eu/src/overlays/ov001/calls/BindScriptHandlersSlot7.c:9` and `eu/src/overlays/ov001/calls/GetScriptHandlerSlot7Index.c:5`. Native `02064724` stores the binding index, and `0206478a` uses `LDRSB`. The predicates compare against 7 at `0206e2b6` and 6 at `0206e322`, then test their distinct literal flags.

The index-7 predicate suppresses gauge gain in `IsPartyGaugeGainAllowed` and participates in ledge-climb policy (`eu/src/overlays/ov001/calls/IsPartyGaugeGainAllowed.c:22`; `eu/src/overlays/ov052/calls/TryLedgeClimb.c:352`). The index-6 predicate changes installed callbacks in `InitOverlay053Entity` (`eu/src/overlays/ov053/calls/InitOverlay053Entity.c:77`). These different consumers do not supply a common gameplay name for either flag. Existing unchecked getter behavior remains unchanged.

## Type-9 patrol pause hook

`CreateFieldObjectClassType9` allocates an 0x84-byte **class descriptor** and 0x1bc-byte **instances**, then installs `PatrolFieldObject_PausePhase4Updates` in class hook 14, at +0x38. `CallFieldObjectHook14IfSavedFlagClear` resolves the instance's class pointer at +8, reads that hook and invokes it as `(object, value)` after its saved-flag guard.

The target callback reads only its first input. It:

1. Forces the low bit of the object's logical saved value to one through `SetPackedStateLowBit`.
2. Writes instance byte +0x82 to one.
3. Returns literal zero.

Native proof: constructor `020849e4` installs the hook, loading Thumb pointer `020846b9` from literal `02084a24`. Dispatcher `0207f8bc` reads class +0x38, `0207f8c2/0207f8c4` supplies object/value and `0207f8c6` calls it. The callback calls the saved-value helper at `020846c0`, writes instance +0x82 at `020846c6` and returns zero at `020846c8`.

The instance byte has a demonstrated pause role. `UpdatePatrolIdle` and `UpdatePatrolMove` enter their normal progression branches only when `GetFieldSessionPhase() == 4` and this byte is zero. If the phase is no longer 4, they clear the byte. Source: `src/ov001/field_objects/UpdatePatrolIdle_02083e70.c:68` and `src/ov001/field_objects/UpdatePatrolMove_02083f9c.c:300`. Native guards are at `02083ed2..02083ee2` and `02084000..02084010`; the clearing stores are `02083efc` and `0208402a`.

This pauses the normal phase-4 idle/movement branches, not every object operation. Sound checks and common basis updates can still run. The callback does not replace the object's current update handler. Phase 4 is the exact field-session phase word read at session +0x1c; no gameplay mode or lifecycle name is assigned to it.

Two storage distinctions matter for a port:

- Class descriptor +0x82, initialized to 2 by the constructor, is a different allocation from the instance pause byte +0x82. Do not merge their roles.
- `FieldObject_GetSavedValue` extracts `(packed & 0xfffe) >> 1`, and the setter writes `(value << 1) | (packed & 0xffff0001)`. The callback sets logical value bit 0, which corresponds to packed-storage bit 1. Packed-storage bit 0 is preserved. Source: `src/ov001/unclassified_helpers/FieldObject_GetSavedValue_0207f9a8.c:12`, `src/ov001/unclassified_helpers/FieldObject_SetSavedValue_0207f9c8.c:12`.

The current callback declaration remains `u32 (void *actor)`. The dispatcher's second word is not read by this target, so no synthetic parameter or request structure is added. Its literal-zero result remains intact.

## Stage-event header value plus one

`ReadStageObjectEventHeaderValuePlusOne(objectIndex, entryIndex)` retains the complete native formula:

```text
if stage service is inactive: return 0
header = GetStageObjectHandle(u16(objectIndex + 1))
if header is NULL: return 0
count = u16(s16(header[+0x0c]) - s16(header[+0x0a]) + 1)
if u32(entryIndex) >= count: return 0
return u16(s16(header[+0x0a + 2 * entryIndex]) + 1)
```

Here bracketed offsets mean halfword reads from the header, not an array of event IDs. The service sentinel is -1. `GetStageObjectHandle` resolves a pointer from the separate table at `gStageManager +0x20c`; it applies the existing one-based-to-zero-based u16 conversion and has no table-index bound check.

The owner chain is concrete. `BeginStageEntries` allocates 0x28-byte headers and a separate pointer table (`src/ov001/shared_engine/BeginStageEntries_02099aec.c:74`; native stores at `02099bd6/02099be6`). `StartStageEvent` initializes a header with the first and last allocated event indexes and installs its pointer (`src/ov001/shared_engine/StartStageEvent_0209a174.c:134`; native `0209a2e6/0209a2fe`). `InitStageEventHeader` writes those bounds at +0x0a/+0x0c (native `02098948/0209894c`). `SpawnStageEventGroups` uses the same fields as first/last event bounds (`src/ov001/shared_engine/SpawnStageEventGroups_0209895c.c:204`; native signed loads `020989b4/020989b8`). The initializer's private `objectId`/`actorId` labels alone do not establish that relationship; its real caller and range consumer do.

The two observed callers both pass `entryIndex = 0`, so they consume the first-event boundary plus one as an event-record ID:

- `RunSpawnCommand` passes the result directly to `GetStageEventRecord` (`eu/src/overlays/ov011/calls/RunSpawnCommand.c:89`; native `020a0b80` supplies zero, `020a0b82` calls the reader and `020a0b86` resolves the event record).
- `UpdateWanderActor` passes it to `GetStageEventTargetInfo` (`eu/src/overlays/ov007/calls/UpdateWanderActor.c:136`; native `020a123c` initializes R6 to zero, the R6=1 branch skips this call, and `020a1274/020a1278` supplies the zero index).

The general function does **not** enumerate `firstEvent + entryIndex`. Index 1 reads the last boundary if admitted by `count`. If `count` admits indexes at least 2, subsequent header halfwords are read and are not proved event IDs. The neutral name describes this full native domain. Preserve its signed halfword reads, unsigned bound comparison, u16 narrowing and legacy `int`/`u32` inputs with `u16` return. A rename does not repair the existing int-based pointer arithmetic or create a portable header ABI.

## Validation record

Research captured all six complete native functions and 28 supporting functions from the original BK9P ROM. All seven involved decompressed overlays match their extracted modules byte for byte. Each candidate has an exact complete delink owner and an object input in the active final Ninja graph. The 104 research checks cover source evidence, native instructions/literals and owner identity. Official integration results follow below.


## Active EU sources

- [ResetManagedActorOverlapCursor](../src/overlays/ov001/calls/ResetManagedActorOverlapCursor.c).
- [RecordCategory4CommandDispatch](../src/overlays/ov001/calls/RecordCategory4CommandDispatch.c).
- [IsSlot7HandlerIndex7Flag370dSet](../src/overlays/ov001/calls/IsSlot7HandlerIndex7Flag370dSet.c).
- [IsSlot7HandlerIndex6Flag3715Set](../src/overlays/ov001/calls/IsSlot7HandlerIndex6Flag3715Set.c).
- [PatrolFieldObject_PausePhase4Updates](../src/overlays/ov001/calls/PatrolFieldObject_PausePhase4Updates.c).
- [ReadStageObjectEventHeaderValuePlusOne](../src/overlays/ov001/calls/ReadStageObjectEventHeaderValuePlusOne.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/ResetManagedActorOverlapCursor.c ResetManagedActorOverlapCursor --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RecordCategory4CommandDispatch.c RecordCategory4CommandDispatch --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IsSlot7HandlerIndex7Flag370dSet.c IsSlot7HandlerIndex7Flag370dSet --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IsSlot7HandlerIndex6Flag3715Set.c IsSlot7HandlerIndex6Flag3715Set --thumb
python tools/verify_idx.py src/overlays/ov001/calls/PatrolFieldObject_PausePhase4Updates.c PatrolFieldObject_PausePhase4Updates --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReadStageObjectEventHeaderValuePlusOne.c ReadStageObjectEventHeaderValuePlusOne --thumb
bash tools/gate.sh
```
