# Field objects, timers, target references and stage service contracts

This block covers 114 EU overlay 001 Thumb entrypoints: 112 numeric functions
receive descriptive names, and two existing scene-entry setters receive corrected
BGM names. Every identity and mode is listed below. The names describe observed
behavior, not original source spelling. The validation section records the existing official checks
after integration on top of `6de3f45462283358b4dff672e0e533972146f1a8`.

The source column identifies the accepted EU wrappers. Interpret each shared
included body through its EU aliases. Root US addresses and inherited SDK template types
do not establish EU identity or logical signatures. The input/output contracts
below come from actual bodies, consumers, writers and native register flow.

## Owners and storage boundaries

| Owner/global | Demonstrated storage and ownership |
|---|---|
| `data_ov001_020a048c` | Scene-entry context; its table owns indexed entries. Entry bytes +0x18/+0x19 supply field BGM selection. |
| `data_ov001_020a0490` | Stage-event context: definition pointer at +0, queued u16 pairs at +8 and count byte +0x108. Reset retains it; destroy frees it. |
| `data_ov001_020a0494` | Task-owned 0x2c-byte timer work: eight counters, active mask, rate, running state and timestamp baseline. Clearing its global pointer is not freeing task work. |
| `data_ov001_020a0498` | Field-task manager work; nested node-list allocation at +0x34. Node cleanup, nested-list free and outer task ownership are separate operations. |
| `data_ov001_020a04a0` | Task-owned field screen-transition work, including buffer state +0x30 and a resource handle +0x60. |
| `data_ov001_020a04a4` | Target-selection manager with flags, tagged reference/cache and fade state. |
| `data_ov001_020a04a8` | Inline session-callback record: first word is a task handle and the callback list follows. It is not simply a global pointer to an allocated record. |
| `data_ov001_020a04b8` | Heap-owned 0xa4-byte message-loader manager. Its destructor explicitly frees the outer allocation. |
| `data_ov001_020a04bc` | Task-owned event work; managed-actor lookup/count, resource handles and tracked MAIN brightness. Partial header arrays do not prove its full layout. |
| `data_ov001_020a04f8` | Field-object class manager. Object list links use next +4. |
| `data_ov001_020a04fc` | Separate entry-pool/cache manager. Its entry list links use next +0. |
| `gStageManager` | Stage groups, event records, party slots, lock/flags/busy state. This partial native layout is distinct from the service-state sentinel. |

The field-object and entry-pool APIs must remain distinct even when their table
accessors look alike. A FieldObjectClass uses u16 stride +0x44 and entries +0x48;
an EntryPool uses u16 stride +0x3c and entries +0x40. Both manager counts at +4
are read as signed bytes, whereas a registered pool's index at +0x59 is u8.
Class animation buffers +0x58/+0x60 have different ownership from shared model
pointers +0x54/+0x5c. Per-entry actor work is allocated separately from the
inline pool slot returned to the caller.

Resource request adapters preserve real resource-ID inputs and native returns
that incomplete declarations hide. Their legacy load option is not a proved heap
selector: allocation uses loader state, and the extra value can flow through an
unused downstream argument. Do not manufacture a heap-selection API from the
old local parameter label. Requests can precede completion; the model-loading
consumer separately checks pointers and completion records.

## Field-object classes and entry pools

| Native identity | Mode | Name | New EU wrapper source | Logical inputs/result and effects |
|---|---|---|---|---|
| ov001:0x0207ee00 | THUMB | `InitFieldObjectClassTable` | `src/overlays/ov001/calls/InitFieldObjectClassTable.c` | `void(int count)`. Allocates and zeroes count*4 class-pointer bytes, stores the count as a signed byte at manager +4, then calls the related mode-table loader. Does not allocate the manager itself. |
| ov001:0x0207ee2c | THUMB | `SetFieldObjectClassAtIndex` | `src/overlays/ov001/calls/SetFieldObjectClassAtIndex.c` | `void(int index, FieldObjectClass *objectClass)`. Stores the supplied class pointer in the indexed class table. No bounds/null guard or ownership change is added by this setter. |
| ov001:0x0207ef44 | THUMB | `RefreshFieldObjectsAndEntryActorSlots` | `src/overlays/ov001/calls/RefreshFieldObjectsAndEntryActorSlots.c` | `void(void)`. Traverses the field-object list through next +4, refreshing each object, then updates actor-slot bindings for the separate entry-pool list. Preserve callback/traversal order. |
| ov001:0x0207f040 | THUMB | `GetFieldObjectClassCount` | `src/overlays/ov001/calls/GetFieldObjectClassCount.c` | `int(void)`. Returns manager +4 with signed-byte extension. A host size/count type must not erase negative native values. |
| ov001:0x0207f050 | THUMB | `GetFieldObjectClassAtIndex` | `src/overlays/ov001/calls/GetFieldObjectClassAtIndex.c` | `FieldObjectClass *(int index)`. Returns the indexed class pointer from manager.table. Borrowed pointer; no bounds/null guard. |
| ov001:0x0207f060 | THUMB | `GetFieldObjectByClassAndIndex` | `src/overlays/ov001/calls/GetFieldObjectByClassAndIndex.c` | `FieldObject *(int classIndex, int objectIndex)`. Passes classIndex to the class getter, then returns class.entries + objectIndex*class.stride, or null for a null class. Legacy omitted first call argument is real; the object index is unchecked. |
| ov001:0x0207f0b4 | THUMB | `GetFieldObjectListHead` | `src/overlays/ov001/auto/GetFieldObjectListHead.c` | `FieldObject *(void)`. Returns the borrowed field-object list head at manager +8. This list uses next +4. |
| ov001:0x0207f0d0 | THUMB | `RequestFieldObjectAnimationBuffer` | `src/overlays/ov001/calls/RequestFieldObjectAnimationBuffer.c` | `void *(int resourceId, u32 legacyLoadArg)`. Maps the resource ID to its animation parameter and requests a file buffer, forwarding the legacy load argument. The native returned buffer is stored by FieldObject_EnsureModelsLoaded in class animation slots. Request issue and load completion are separate. |
| ov001:0x0207f0e0 | THUMB | `RequestFieldObjectModelResource` | `src/overlays/ov001/calls/RequestFieldObjectModelResource.c` | `int(int resourceId, ModelResource **out, u32 legacyLoadArg)`. Maps the resource ID to its model parameter and calls AcquireSharedRecord with the output pointer and legacy load argument. Returns 1 regardless of immediate availability; the consumer checks output/completion separately. |
| ov001:0x0207f210 | THUMB | `FreeFieldObjectClassAnimationBuffers` | `src/overlays/ov001/calls/FreeFieldObjectClassAnimationBuffers.c` | `void(FieldObject *object)`. From object +8, finds its class; frees nonnull animation buffers at class +0x58/+0x60 and clears those pointers. Does not release model references +0x54/+0x5c or the class/object allocation. |
| ov001:0x0207f26c | THUMB | `FreeFieldObjectShapeStorage` | `src/overlays/ov001/calls/FreeFieldObjectShapeStorage.c` | `void(FieldObject *object)`. Frees nonnull shape-storage pointer at object +0x18 and clears it. Does not free the outer object; do not substitute another overlay's shape offset. |
| ov001:0x0207f898 | THUMB | `CallFieldObjectHook13IfPresent` | `src/overlays/ov001/calls/CallFieldObjectHook13IfPresent.c` | `u32(FieldObject *object)`. Calls class hook 13 at +0x34 with the object and returns its raw word, or zero when absent. Known installers return positions, but the common API is not promoted to a position type from those installers alone. |
| ov001:0x0207f8ac | THUMB | `CallFieldObjectHook14IfSavedFlagClear` | `src/overlays/ov001/calls/CallFieldObjectHook14IfSavedFlagClear.c` | `u32(FieldObject *object, u32 value)`. If the object's saved flag mask 1 is clear, calls present class hook 14 at +0x38 with object/value and returns its raw result; otherwise zero. This is not a generic live/active-object test. |
| ov001:0x02086330 | THUMB | `ActivateEntryPoolSlot` | `src/overlays/ov001/calls/ActivateEntryPoolSlot.c` | `PoolEntry *(EntryPool *pool, u8 index)`. Uses pool/index to find an inline slot; returns null if its +0x30 active halfword is nonzero. Otherwise initializes it, stores the byte index/owner and sentinels, allocates and clears 0x1d0 bytes of actor work, and returns the slot. No allocation-failure guard. |
| ov001:0x02086384 | THUMB | `GetEntryPoolObjectAtIndex` | `src/overlays/ov001/auto/GetEntryPoolObjectAtIndex.c` | `PoolEntry *(EntryPool *pool, int index)`. Returns pool.entries at +0x40 plus index times u16 stride at +0x3c. No bounds/null guard. The result is inline pool storage, not a new allocation. |
| ov001:0x0208645c | THUMB | `SetFieldEntryActorAnimationGroup` | `src/overlays/ov001/calls/SetFieldEntryActorAnimationGroup.c` | `void(PoolEntry *entry, u8 group)`. Stores group as a byte at entry +0x47; when entry +0x30 mask 0x4 is set, resolves actor ID +0x32 and rebinds tracks. The stored group is sign-extended on readback. |
| ov001:0x020869a0 | THUMB | `SetSessionFlagEnabled` | `src/overlays/ov001/calls/SetSessionFlagEnabled.c` | `void(u32 id, u32 unused, BOOL enabled)`. Third argument nonzero sets the session bit identified by the first argument; zero clears it. The second argument is unused by the real bit helpers; retain the three-slot native ABI without inventing a bit-width argument. |
| ov001:0x02086de0 | THUMB | `DestroyFieldEntryPoolManager` | `src/overlays/ov001/calls/DestroyFieldEntryPoolManager.c` | `void(void)`. Destroys all pools with notification disabled, frees eight nonnull cache pointers at manager +0x13c+i*8, frees the manager and clears its global pointer. Do not replace the false notification argument with TRUE. |
| ov001:0x02086e58 | THUMB | `InitFieldEntryPoolTable` | `src/overlays/ov001/calls/InitFieldEntryPoolTable.c` | `void(int count)`. Allocates/zeroes count*4 pool pointers and stores a byte count. Conditionally invalidates cached resources from session/cache state, preserving the original predicate and order. Assumes prior table lifecycle is handled by its caller. |
| ov001:0x02086fb8 | THUMB | `RegisterFieldEntryPool` | `src/overlays/ov001/calls/RegisterFieldEntryPool.c` | `void(int index, EntryPool *pool)`. Writes pool into the full integer table index, then stores that index narrowed to a byte at pool +0x59. No index guard. |
| ov001:0x02086fcc | THUMB | `GetFieldEntryPoolIndex` | `src/overlays/ov001/auto/GetFieldEntryPoolIndex.c` | `u8(const EntryPool *pool)`. Returns pool +0x59 as u8. It is the registration/list index, not the signed manager count. |
| ov001:0x02087010 | THUMB | `StopAndClearFieldEntryList` | `src/overlays/ov001/calls/StopAndClearFieldEntryList.c` | `void(void)`. Walks entry next +0, invoking stop hooks, then clears list head, tail and count. Does not free entries or pools. Preserve traversal after callbacks. |
| ov001:0x02087038 | THUMB | `ApplyActorSlotsToFieldEntryList` | `src/overlays/ov001/calls/ApplyActorSlotsToFieldEntryList.c` | `void(void)`. Walks entry next +0, applying actor-slot selection and the optional pool refresh hook to each entry. This is the second-manager pass used after field-object refresh. |
| ov001:0x0208722c | THUMB | `GetFieldEntryPoolCount` | `src/overlays/ov001/calls/GetFieldEntryPoolCount.c` | `int(void)`. Returns the entry-pool manager's signed-byte count at +4. Distinct from the field-object class count despite the identical load pattern. |
| ov001:0x0208723c | THUMB | `GetFieldEntryPoolAtIndex` | `src/overlays/ov001/calls/GetFieldEntryPoolAtIndex.c` | `EntryPool *(int index)`. Returns the indexed borrowed pool pointer from its manager table. No bounds guard. |
| ov001:0x0208724c | THUMB | `GetFieldEntryByPoolAndIndex` | `src/overlays/ov001/calls/GetFieldEntryByPoolAndIndex.c` | `PoolEntry *(int poolIndex, int objectIndex)`. Passes poolIndex to the pool getter, then indexes its inline entries using objectIndex; returns null for a null pool. The preserved first argument must not disappear because of a legacy no-argument declaration. |
| ov001:0x02087264 | THUMB | `GetFieldEntryListHead` | `src/overlays/ov001/auto/GetFieldEntryListHead.c` | `PoolEntry *(void)`. Returns the borrowed entry-list head at pool manager +8. Entry next is +0, unlike field-object next +4. |

## Scene entries, queued events and timer/task work

`PlayFieldBgm` and `UpdateFieldBgm` read the same scene-entry bytes +0x18/+0x19,
store them as the selected BGM track, and pass them to `QueueSoundKind4`.
The matching setters index that exact same owner/table. Accordingly this block
uses `PrimaryBgmId`/`SecondaryBgmId` rather than the misleading prior `DisplayId`
labels. The member correction is restricted to `SceneEntry.primaryBgmId` and
`secondaryBgmId` in `SceneEntryContext.h` and the two setter bodies. Other owners'
display fields are not included. Both setters return the previous byte.

The timer units are milliseconds, demonstrated by `OS_GetTick()*64/0x82ea` in
the baseline/updater and by the saved-seconds consumer's division by 1000.

| Timer-work offset | Native value |
|---:|---|
| +0x00..+0x1f | Eight u32 counters: channel 0 session elapsed, 1 unassigned counter, 2 post-intro elapsed, 3 field counter, 4..7 task timers |
| +0x20 | u16 active-channel mask |
| +0x22 | 16-bit field-counter rate, read as s16; 0x1000 is the default |
| +0x24 | u8 running state |
| +0x28 | u32 last millisecond timestamp |

`AdvanceTweenChannels` updates active counters using unsigned timestamp delta;
only channel 3 multiplies by the rate and shifts by 12. Preserve the native
signed/unsigned multiplication and 32-bit wrap behavior. Pausing retains active
bits and values. Resuming takes the callback path that establishes a new baseline;
it does not simply add all paused time. Automatic allocation has one field slot
and four task slots, while explicit nonnegative indices remain unchecked.

The queued-event context is another owner. Reset clears its 64 u16-pair storage
and count, while triggering iterates without consuming or clearing that queue.
Field-task nodes are another owner again; high/low IDs partition at 0xf8. The
signed result byte at task +0x10 must not be widened into an invented enum or
restricted to boolean values from a few consumers.

| Native identity | Mode | Name | New EU wrapper source | Logical inputs/result and effects |
|---|---|---|---|---|
| ov001:0x02068094 | THUMB | `GetSceneEntryPrimaryBgmId` | `src/overlays/ov001/calls/GetSceneEntryPrimaryBgmId.c` | `u8(int index)`. Reads scene-entry byte +0x18, or returns 0xff for a null entry. PlayFieldBgm and UpdateFieldBgm use it as a BGM track ID, then queue sound kind 4. Table/global/index are not guarded. |
| ov001:0x020680b0 | THUMB | `GetSceneEntrySecondaryBgmId` | `src/overlays/ov001/calls/GetSceneEntrySecondaryBgmId.c` | `u8(int index)`. Reads scene-entry byte +0x19, or 0xff for a null entry. The same BGM consumers select this alternate track. Preserve the unsigned-byte sentinel. |
| ov001:0x020681e8 | THUMB | `WorldNamedEntryHasKind` | `src/overlays/ov001/calls/WorldNamedEntryHasKind.c` | `BOOL(const WorldNamedEntry *entry, u32 kind)`. For a nonnull named world entry, scans up to four bytes at +0x0c. Checks equality before stopping at values 0 or 8, so queries 0/8 may match a sentinel. This is an ordered value list, not a bitmask. |
| ov001:0x02068378 | THUMB | `HasSceneEntryContext` | `src/overlays/ov001/calls/HasSceneEntryContext.c` | `BOOL(void)`. Tests whether the scene-entry context pointer is nonnull. Does not prove scene readiness or resource completion. |
| ov001:0x020685a4 | THUMB | `DestroyStageEventContext` | `src/overlays/ov001/calls/DestroyStageEventContext.c` | `void(void)`. Resets the stage-event context, releases record slot 4 and the service instance, frees the nonnull definition block at context word 0, frees the outer context and clears the global. Requires a valid outer context. |
| ov001:0x020685d4 | THUMB | `ResetStageEventContext` | `src/overlays/ov001/calls/ResetStageEventContext.c` | `void(void)`. Shuts down the active stage manager, clears queued-pair count +0x108 and 0x100 pair bytes at +8, then clears queue/global state. Retains the definition block and outer context. |
| ov001:0x020687b8 | THUMB | `TriggerQueuedStageEventPairs` | `src/overlays/ov001/calls/TriggerQueuedStageEventPairs.c` | `void(void)`. Conditionally clears stage tables according to session state/refresh flags, then triggers every stored u16 pair in order. Does not clear pair storage or count after triggering; state 10 bypasses the refresh branch. |
| ov001:0x0206888c | THUMB | `HasQueuedStageEventValue` | `src/overlays/ov001/calls/HasQueuedStageEventValue.c` | `BOOL(u16 value)`. Returns whether FindPairByValue finds a queued pair whose first u16 matches the input value. Native R0 supplies that real input despite legacy void/no-argument declarations. |
| ov001:0x02068d78 | THUMB | `StartPostIntroElapsedTimer` | `src/overlays/ov001/calls/StartPostIntroElapsedTimer.c` | `void(void)`. Resets channel 2 to zero and sets its active bit. MarkSessionIntroDone starts this counter; result-screen code reads it. Does not globally resume timer updates. |
| ov001:0x02068d8c | THUMB | `AllocateFieldTimerCounter` | `src/overlays/ov001/calls/AllocateFieldTimerCounter.c` | `int(int index)`. Nonnegative index selects channel index+3 without bounds validation. Negative index searches the one automatic field slot. Resets/enables the selected counter, sets rate 0x1000 and returns its field-relative index, or -1 if none. |
| ov001:0x02068dcc | THUMB | `AllocateTaskTimerSlot` | `src/overlays/ov001/calls/AllocateTaskTimerSlot.c` | `int(int index)`. Nonnegative index selects channel index+4 unchecked; negative searches four automatic task slots. Resets/enables that counter and returns its task-relative index, or -1. Does not reset the field rate. |
| ov001:0x02068dfc | THUMB | `StopPostIntroElapsedTimer` | `src/overlays/ov001/auto/StopPostIntroElapsedTimer.c` | `void(void)`. Clears channel-2 active bit while preserving its accumulated value. The inherited native return view is not used as a timer value or allocation result. |
| ov001:0x02068e44 | THUMB | `ResumeSessionTimerUpdates` | `src/overlays/ov001/calls/ResumeSessionTimerUpdates.c` | `void(void)`. Writes running byte +0x24 to 1. Individual active bits remain unchanged; the callback path establishes its time baseline. |
| ov001:0x02068e54 | THUMB | `PauseSessionTimerUpdates` | `src/overlays/ov001/calls/PauseSessionTimerUpdates.c` | `void(void)`. Writes running byte +0x24 to 0. Does not clear counters or active bits; the updater switches to the baseline callback without adding delta while paused. |
| ov001:0x02068e80 | THUMB | `GetSessionElapsedMilliseconds` | `src/overlays/ov001/calls/GetSessionElapsedMilliseconds.c` | `u32(void)`. Returns raw u32 channel 0 in milliseconds. SaveElapsedSeconds separately divides by 1000 and clamps before saving; this getter does not return seconds. |
| ov001:0x02068e8c | THUMB | `GetSessionTimerChannel1Milliseconds` | `src/overlays/ov001/calls/GetSessionTimerChannel1Milliseconds.c` | `u32(void)`. Returns raw u32 channel 1 in milliseconds. Counter-goal code reads it, but no more specific gameplay meaning is assigned. |
| ov001:0x02068e98 | THUMB | `GetPostIntroElapsedMilliseconds` | `src/overlays/ov001/auto/GetPostIntroElapsedMilliseconds.c` | `u32(void)`. Returns raw u32 channel 2, the elapsed counter started after the intro marker. It is not a score value. |
| ov001:0x02068ea4 | THUMB | `GetFieldTimerCounterMilliseconds` | `src/overlays/ov001/calls/GetFieldTimerCounterMilliseconds.c` | `u32(int index)`. Returns raw counter at (index+3)*4. Index is unchecked; channel 3 is rate-scaled and can be set/adjusted by field timer code, so monotonic elapsed time is not guaranteed. |
| ov001:0x02068eb4 | THUMB | `GetTaskTimerElapsedMilliseconds` | `src/overlays/ov001/calls/GetTaskTimerElapsedMilliseconds.c` | `u32(int index)`. Returns raw counter at (index+4)*4, unchecked. PollTimerTask requires elapsed!=0 as well as elapsed>=duration; duration zero must not silently bypass that condition. |
| ov001:0x02068ec4 | THUMB | `SetPostIntroElapsedMilliseconds` | `src/overlays/ov001/auto/SetPostIntroElapsedMilliseconds.c` | `void(u32 value)`. Writes channel 2 without enabling it. Value is the first and only logical input. |
| ov001:0x02068ed0 | THUMB | `SetFieldTimerCounterMilliseconds` | `src/overlays/ov001/calls/SetFieldTimerCounterMilliseconds.c` | `void(u32 value, int index)`. Writes channel index+3. Argument order is (value,index); no active-bit or running-state change. |
| ov001:0x02068ee0 | THUMB | `SetTaskTimerElapsedMilliseconds` | `src/overlays/ov001/calls/SetTaskTimerElapsedMilliseconds.c` | `void(u32 value, int index)`. Writes channel index+4. Argument order is (value,index); no active-bit or running-state change. |
| ov001:0x02068ef0 | THUMB | `SetFieldTimerRateFx12` | `src/overlays/ov001/auto/SetFieldTimerRateFx12.c` | `void(u16 rateFx12)`. Stores the low 16 bits of the field rate at +0x22. Only channel 3 uses it; preserve native signed readback and unsigned-delta multiplication rules rather than adding an unproved negative-rate policy. |
| ov001:0x020691d4 | THUMB | `ReleaseHighIdTaskNodes` | `src/overlays/ov001/calls/ReleaseHighIdTaskNodes.c` | `void(void)`. Releases task nodes whose u16 ID at +0x50 is >=0xf8, using each release result as the next node. Clears the shared eight-u16 ID list/count even while low-ID nodes remain. |
| ov001:0x02069214 | THUMB | `ReleaseAllTaskNodes` | `src/overlays/ov001/calls/ReleaseAllTaskNodes.c` | `void(void)`. Releases low-ID then high-ID task nodes and clears manager byte +0x11. Does not free the list allocation or outer task work itself. |
| ov001:0x02069434 | THUMB | `GetFieldTaskResult` | `src/overlays/ov001/auto/GetFieldTaskResult.c` | `int(const FieldTaskState *task)`. Returns task byte +0x10 with signed extension. Completion callbacks reuse this getter; known 0/1 values do not justify changing the general s8 contract. |
| ov001:0x0206943c | THUMB | `SetSavedTaskFlag` | `src/overlays/ov001/calls/SetSavedTaskFlag.c` | `void(int index, BOOL secondSet, BOOL clearFlag)`. Optionally offsets index by 0xf8, then sets or clears saved bit 0x331f+2*index. Third input nonzero means clear, zero means set. Does not touch the adjacent second bit of each pair. |
| ov001:0x02068c3c | THUMB | `ClearSessionTimerStatePointer` | `src/overlays/ov001/calls/ClearSessionTimerStatePointer.c` | `void(void)`. Calls the current-task work accessor and clears the timer global pointer. No allocation or free occurs here; the forwarded legacy argument is not an ownership parameter. |
| ov001:0x02068ff4 | THUMB | `ReleaseFieldTaskManagerWork` | `src/overlays/ov001/calls/ReleaseFieldTaskManagerWork.c` | `void(void)`. Gets current task work, releases all task nodes, frees its nested list allocation at +0x34 and clears the task-manager global. Does not free the current task-work block here. |

The corrected existing setters belong to the same scene-entry contract:

| Native identity | Mode | Name | New EU wrapper source | Logical inputs/result and effects |
|---|---|---|---|---|
| ov001:0x020680cc | THUMB | `SetSceneEntryPrimaryBgmId` | `src/overlays/ov001/calls/SetSceneEntryPrimaryBgmId.c` | `u8(int index, u8 value)`. Replaces scene-entry byte +0x18 and returns its previous u8 value. Same indexed owner/offset read by PrimaryBgmId and consumed by field BGM selection. No null/index guard. |
| ov001:0x020680e4 | THUMB | `SetSceneEntrySecondaryBgmId` | `src/overlays/ov001/calls/SetSceneEntrySecondaryBgmId.c` | `u8(int index, u8 value)`. Replaces scene-entry byte +0x19 and returns its previous u8 value. Same indexed owner/offset read by SecondaryBgmId. No null/index guard. |

## Screen transitions, target references and event work

Screen-transition +8/+0x0c cache MAIN/SUB brightness shifted by 12. Those fields
are not x/y coordinates despite the current partial struct labels. Hardware MAIN
brightness and cached MAIN brightness are also the two independent comparisons
in tracked brightness control; the second check is not SUB brightness. The input
brightness is stored as a byte and later compared with signed-byte extension.
`InvokeSessionCheckCallbackOrDefault` contributes a raw callback result to the
blocker check, rather than a normalized or inverted predicate.

| Record | Size and role |
|---|---|
| TargetReference | First eight bytes: u32 kind plus four-byte pointer or two-u16 payload. Constructors return the supplied record and do not allocate. |
| Resolved target | The same tag/payload prefix plus VecFx32 cached position at +8, total 20 bytes in the demonstrated view. Reference constructors leave that cache untouched. |
| Target score | Separate 12-byte signed distance/priority/valid record. No target pointer. |

Kinds are 0 none, 1 event ID/slot, 2 FieldObject pointer, 3 PoolEntry pointer and
4 managed-actor pointer. Their position accessors differ; merging their pointer
types would hide class/pool callback boundaries. The score comparator orders by
higher priority then smaller signed distance, with an invalid current best always
replaceable. It does not reject an invalid candidate itself.

Selected-target and managed-actor position APIs return borrowed VecFx32 pointers.
An absent callback can use a fallback position; a present callback returning null
does not trigger the fallback. A native BOOL/int declaration that preserves raw
R0 is not evidence that these pointer returns should be normalized.

Event work remains a partial view. Resource cleanup visits nine handles beginning
at +0xb8; a five-element local header cannot shorten that loop. Managed-actor count
is read at +0x7c, while the current partial player array overlaps that region.
No four-actor capacity or complete host layout is inferred from that declaration.
The bounded lookup checks its upper index limit; this naming block adds no missing
lower-bound or context guard.

| Native identity | Mode | Name | New EU wrapper source | Logical inputs/result and effects |
|---|---|---|---|---|
| ov001:0x0206a118 | THUMB | `ReleaseFieldScreenTransitionWork` | `src/overlays/ov001/calls/ReleaseFieldScreenTransitionWork.c` | `void(void)`. Releases buffer state +0x30 and resource handle +0x60, then clears the screen-transition global. Does not free the outer task-owned work. |
| ov001:0x0206a714 | THUMB | `DestroyScreenFadeTaskAndClearHandle` | `src/overlays/ov001/calls/DestroyScreenFadeTaskAndClearHandle.c` | `void(void)`. Destroys the screen-fade task handle through DestroyTaskObjectWrapper, then stores 0xffffffff. Does not test validity; 0xffffffff is the handle sentinel, not null. |
| ov001:0x0206a72c | THUMB | `BeginFieldScreenModeTransition` | `src/overlays/ov001/calls/BeginFieldScreenModeTransition.c` | `void(int mode)`. Always calls SetScreenModeFlags(1,mode). Mode 3 then returns; otherwise caches MAIN/SUB brightness shifted by 12, resets transition fields, conditionally draws black/schedules a restore callback and clears session mask 0x40000 when requested. |
| ov001:0x0206ad1c | THUMB | `DrawSpriteFrameQuadWithDepthUpdate` | `src/overlays/ov001/calls/DrawSpriteFrameQuadWithDepthUpdate.c` | `void(SpriteQuad *sprite)`. Calls DrawSpriteFrameQuad with depth-update selector 1. The real quad callee controls polygon attribute mask 0x800. Borrowed sound-stream types/enums are unrelated template artifacts. |
| ov001:0x0206ad28 | THUMB | `DrawSpriteFrameQuadWithoutDepthUpdate` | `src/overlays/ov001/calls/DrawSpriteFrameQuadWithoutDepthUpdate.c` | `void(SpriteQuad *sprite)`. Calls the same sprite-quad callee with selector 0, omitting translucent depth update. Does not operate on a linked list despite an inherited local variable name. |
| ov001:0x0206b930 | THUMB | `InitNoTargetReference` | `src/overlays/ov001/auto/InitNoTargetReference.c` | `TargetReference *(TargetReference *target)`. Writes kind 0 and zero payload into the first eight bytes of the supplied reference; returns that same pointer. Leaves cached resolved position beyond those bytes untouched. |
| ov001:0x0206b938 | THUMB | `InitFieldObjectTargetReference` | `src/overlays/ov001/auto/InitFieldObjectTargetReference.c` | `TargetReference *(TargetReference *target, FieldObject *object)`. Writes kind 2 and the borrowed FieldObject pointer; returns the reference pointer. No allocation and no write beyond eight bytes. |
| ov001:0x0206b940 | THUMB | `InitFieldEntryTargetReference` | `src/overlays/ov001/auto/InitFieldEntryTargetReference.c` | `TargetReference *(TargetReference *target, PoolEntry *entry)`. Writes kind 3 and the borrowed PoolEntry pointer; returns the reference pointer. This object family differs from kind 2. |
| ov001:0x0206b948 | THUMB | `InitStageSlotTargetReference` | `src/overlays/ov001/auto/InitStageSlotTargetReference.c` | `TargetReference *(TargetReference *target, u16 eventId, u16 slot)`. Writes kind 1 with two u16 payload fields: event ID and slot. Returns the reference pointer. Preserve narrowing and sentinels. |
| ov001:0x0206b954 | THUMB | `InitManagedActorTargetReference` | `src/overlays/ov001/auto/InitManagedActorTargetReference.c` | `TargetReference *(TargetReference *target, ManagedActor *actor)`. Writes kind 4 with the borrowed managed-actor pointer; returns the reference pointer. Its position is at actor +0xbc, distinct from the other families. |
| ov001:0x0206ba18 | THUMB | `InitTargetSearchScore` | `src/overlays/ov001/calls/InitTargetSearchScore.c` | `TargetScore *(TargetScore *score)`. Initializes the separate 12-byte score to distance INT_MAX, priority -1 and valid 0; returns the score pointer. The record contains no target pointer. |
| ov001:0x0206bb48 | THUMB | `IsTargetSearchScoreBetter` | `src/overlays/ov001/calls/IsTargetSearchScoreBetter.c` | `BOOL(const TargetScore *best, const TargetScore *candidate)`. Accepts when best.valid==0, or candidate priority is higher, or equal priority has smaller signed distance. Does not independently reject an invalid candidate; an equal tie does not replace a valid best. |
| ov001:0x0206bc0c | THUMB | `IsManagedActorSlot0Empty` | `src/overlays/ov001/calls/IsManagedActorSlot0Empty.c` | `BOOL(void)`. Returns whether managed actor slot 0 lookup is null. Does not test all actor/party slots. |
| ov001:0x0206c284 | THUMB | `ResolveSelectedTargetPosition` | `src/overlays/ov001/calls/ResolveSelectedTargetPosition.c` | `VecFx32 *(void)`. Requires target manager and a nonzero active mask, resolves its reference, then returns the cached position pointer; otherwise null. Native pointer return must not be normalized because of the reconstructed BOOL declaration. |
| ov001:0x0206c2b8 | THUMB | `GetTargetSelectionActiveMask` | `src/overlays/ov001/calls/GetTargetSelectionActiveMask.c` | `u32(void)`. Calls flag-2 then flag-1 getters and ORs their results. Returns raw mask 0..3, not a normalized boolean. |
| ov001:0x0206c2c8 | THUMB | `GetTargetSelectionFlag2` | `src/overlays/ov001/calls/GetTargetSelectionFlag2.c` | `u32(void)`. Returns manager flags &0x2, or zero when manager is null. Raw 0/2; does not revalidate the selected target. |
| ov001:0x0206c2e0 | THUMB | `GetTargetSelectionFlag1` | `src/overlays/ov001/calls/GetTargetSelectionFlag1.c` | `u32(void)`. Returns manager flags &0x1, or zero when manager is null. No inferred gameplay-mode enum. |
| ov001:0x0206c504 | THUMB | `GetTargetSelectionFadeLevel2` | `src/overlays/ov001/calls/GetTargetSelectionFadeLevel2.c` | `fx32(void)`. Returns the third fade level at manager +0x34, or INT_MAX when manager is null or flags mask 0x4 is set. It is not target distance or a search score. |
| ov001:0x0206c634 | THUMB | `SetEventSlotAndEntryTargetSearchEnabled` | `src/overlays/ov001/calls/SetEventSlotAndEntryTargetSearchEnabled.c` | `void(BOOL eventSlots, BOOL poolEntries)`. For a nonnull manager, replaces search masks 0x80/0x40 from event-slot/pool-entry enable inputs, then searches for player index 0. A failed search can leave the existing reference unchanged. |
| ov001:0x0206c6f4 | THUMB | `DestroySessionCallbackTask` | `src/overlays/ov001/calls/DestroySessionCallbackTask.c` | `TaskObject *(void)`. Destroys the task stored in the first word of the inline session callback record and returns the native next-task result. Does not clear that handle word. |
| ov001:0x0206c768 | THUMB | `HasSessionCallbackTaskHandle` | `src/overlays/ov001/calls/HasSessionCallbackTaskHandle.c` | `BOOL(void)`. Tests whether the inline callback record's handle word is nonzero. This is bookkeeping, not proof of task liveness after destruction. |
| ov001:0x0206c9c0 | THUMB | `EnsureFieldMessageLoaderManager` | `src/overlays/ov001/calls/EnsureFieldMessageLoaderManager.c` | `void(void)`. If null, allocates 0xa4 bytes, stores the pointer and initializes that manager. The allocation return in R0 is the real initializer input despite its incomplete declaration. |
| ov001:0x0206c9dc | THUMB | `DestroyFieldMessageLoaderManager` | `src/overlays/ov001/calls/DestroyFieldMessageLoaderManager.c` | `void(void)`. If present, releases message-loader resources/removes its refresh callback, frees the heap manager and clears the global. This outer allocation is explicitly owned and freed here. |
| ov001:0x0206cab4 | THUMB | `SetFieldMessageLoaderUpdatesPaused` | `src/overlays/ov001/calls/SetFieldMessageLoaderUpdatesPaused.c` | `void(BOOL paused)`. For a nonnull manager, nonzero input sets flags mask 1 and zero clears it. RefreshMenuWindows returns early while that mask is set: nonzero means paused, not enabled. |
| ov001:0x0206cbb8 | THUMB | `ReleaseEventContextWork` | `src/overlays/ov001/calls/ReleaseEventContextWork.c` | `void(void)`. Gets current task work, releases event-context resources and clears its global pointer. Does not allocate/free the outer work; the inherited integer argument is unused. |
| ov001:0x0206d718 | THUMB | `ReleaseEventContextResources` | `src/overlays/ov001/calls/ReleaseEventContextResources.c` | `void(void)`. Releases nine resource handles at event work +0xb8+i*4. The five-entry partial header view is not the real loop capacity; do not truncate cleanup to five. |
| ov001:0x0206dc38 | THUMB | `GetManagedActorCount` | `src/overlays/ov001/calls/GetManagedActorCount.c` | `u32(void)`. Returns word +0x7c as actor count, or zero when context is null. The partial player-array view overlaps this region and does not prove a four-actor capacity. |
| ov001:0x0206dc60 | THUMB | `GetManagedActorPositionWithCallback` | `src/overlays/ov001/calls/GetManagedActorPositionWithCallback.c` | `VecFx32 *(int index)`. Looks up the indexed actor; null lookup returns null. If callback +0x224 exists, calls it with the actor and returns its pointer result, including null. Only an absent callback uses position at actor +0xbc. |
| ov001:0x0206e6f4 | THUMB | `TryBeginTrackedMainBrightness` | `src/overlays/ov001/calls/TryBeginTrackedMainBrightness.c` | `BOOL(int brightness)`. Requires context, zero hardware MAIN brightness, zero cached MAIN brightness, zero raw session check and inactive panel. On success stores the low-byte brightness and applies MAIN brightness; records/returns the success flag. Input is brightness, not owner ID. |
| ov001:0x0206e750 | THUMB | `UpdateTrackedMainBrightness` | `src/overlays/ov001/calls/UpdateTrackedMainBrightness.c` | `int(int brightness)`. Requires the tracking flag, hardware MAIN and cached MAIN both equal to the previous signed-byte brightness, and no session/panel blocker. If valid, applies/stores the new brightness. Returns and stores the surviving raw tracking status. |
| ov001:0x0206e7c0 | THUMB | `ResetTrackedMainBrightness` | `src/overlays/ov001/calls/ResetTrackedMainBrightness.c` | `void(void)`. Always requests MAIN brightness 0, then clears tracked value/status if context exists. Preserve the setter call even for null context. |

## Stage service adapters, locks and event iteration

`g_stageEventsState != -1` is the service-active guard. `gStageManager != NULL`
is a different precondition. The adapters below check one, both or neither;
names ending `IfActive` do not promise that an event is currently executing or
that every supplied handle is valid.

Stage event handles are one-based at lookup boundaries, with zero as an iterator
end sentinel. Public slot indices and `RequestSceneEvent` indices are zero-based.
Keep every explicit +1/-1 conversion, u16 narrowing and wrap. Stage records use
native stride 0x1c8; groups use 0x28. These offsets do not establish complete
portable structures or allocation sizes.

The two logical slot lock bits (masks 1/2) occupy byte +9 bits 2/3. Adding and
releasing them can also change active/pending state and spawn/reset a state-6
slot. The borrowed sound-stream enum seen in some wrappers merely supplies
integer 1; these are stage-slot operations.

`QueryStageEventState` mode 0 checks the busy word and an existential state-2
condition; mode 1 accepts enabled matching groups in states 0/6/7; mode 2 accepts
states 0/7. A negative group filter includes every group. Unknown modes return
TRUE. The separate group-state aggregate accepts ignored result zero only in
its all-group path, not its specific-slot path.

The party-slot configuration stores raw words at event +0x70/+0x74. Earlier
local labels call them hit points/max hit points, but this block does not claim
that gameplay meaning without the relevant stat consumers. Its optional position
copy and target-height adjustment are independently established.

| Native identity | Mode | Name | New EU wrapper source | Logical inputs/result and effects |
|---|---|---|---|---|
| ov001:0x020876d8 | THUMB | `BeginStageEntriesIfActive` | `src/overlays/ov001/calls/BeginStageEntriesIfActive.c` | `void(StageSource *source)`. When service state is not -1 and source is nonnull, calls BeginStageEntries, which allocates source-count groups/references and installs the spawn updater. Does not create the stage manager itself. |
| ov001:0x02087890 | THUMB | `QueryAllStageEventStateIfActive` | `src/overlays/ov001/calls/QueryAllStageEventStateIfActive.c` | `BOOL(int mode)`. When the service is active, returns QueryStageEventState(mode,-1), selecting all groups; otherwise 0. Unknown modes return TRUE in the real callee, so this is not one generic busy predicate. |
| ov001:0x020878c4 | THUMB | `TriggerNextStageEventFromSource1IfActive` | `src/overlays/ov001/calls/TriggerNextStageEventFromSource1IfActive.c` | `u16(u32 value, u32 extra, u16 *outHandle)`. With active service, forwards both input values and optional output handle through TriggerNextStageEventFromSource1; otherwise returns 0. The result is a raw event handle, not normalized BOOL. |
| ov001:0x020878e0 | THUMB | `StartStageEventInstanceIfActive` | `src/overlays/ov001/calls/StartStageEventInstanceIfActive.c` | `u32(u32 eventId, int first, int second, u16 *outHandle)`. With active service, forwards one-based event ID, two values and optional output handle. The callee returns the input event ID on successful instance creation, otherwise 0. No added record-null guard. |
| ov001:0x0208796c | THUMB | `FindNextActiveStageEventIfActive` | `src/overlays/ov001/calls/FindNextActiveStageEventIfActive.c` | `u16(u16 currentHandle)`. With active service, returns the next eligible one-based event handle; otherwise zero. Preserves the lower-level iterator's u16 narrowing and zero end sentinel. |
| ov001:0x02087df8 | THUMB | `GetStageSlotLock1IfActive` | `src/overlays/ov001/calls/GetStageSlotLock1IfActive.c` | `BOOL(s16 slotIndex)`. With active service, looks up slotIndex+1 and returns low logical lock bit 1 from byte +9 bit 2; otherwise FALSE. Does not return the whole two-bit mask or null-check the slot. |
| ov001:0x02087e24 | THUMB | `ResetStageGroupRowsAndRestoreDefaultIfActive` | `src/overlays/ov001/calls/ResetStageGroupRowsAndRestoreDefaultIfActive.c` | `void(u32 groupIndex)`. With active service, resets group rows, then restores the slot default in that order. No manager creation/index validation. |
| ov001:0x020880b4 | THUMB | `SetStageEventGroupAnimationIfPresent` | `src/overlays/ov001/calls/SetStageEventGroupAnimationIfPresent.c` | `void(u32 eventId, u32 track, int animationId, u32 blendFrames, BOOL enable)`. Looks up event record; if present, forwards track, animation, blend frames and enable. The real group callee applies animation to leader and following members and consumes animation ID as u8, despite the wrapper's s16 declaration. |
| ov001:0x020880f8 | THUMB | `AddStageScoreWrapper` | `src/overlays/ov001/calls/AddStageScoreWrapper.c` | `void(int scoreKind)`. Tail veneer preserving score-kind input. AddStageScore maps kinds 0/1/2 to +1/+10/+100 when scoring is enabled and clamps negative total to zero. No logical pointer result. |
| ov001:0x02088100 | THUMB | `GetFocusEventActorPositionWrapper` | `src/overlays/ov001/calls/GetFocusEventActorPositionWrapper.c` | `BOOL(VecFx32 *out)`. Tail veneer preserving an optional VecFx32 output pointer and boolean result. The callee checks focus event/record/actor before copying; null output asks only whether a focus actor resolves. |
| ov001:0x020881a8 | THUMB | `ClearStagePartySlot` | `src/overlays/ov001/calls/ClearStagePartySlot.c` | `void(u32 slotIndex)`. Only with active service and at least one eligible event, repeatedly fetches the same selected party slot, clears record flag 0x200 and zeroes its 0x2c bytes when occupied. Preserve the event-loop condition; no eligible event means no clearing. |
| ov001:0x02088204 | THUMB | `ConfigureStagePartySlot` | `src/overlays/ov001/calls/ConfigureStagePartySlot.c` | `void(u32 slotIndex, u8 kind, u8 subKind, s32 value70, s32 value74, const VecFx32 *position)`. Gets one of three party slots; assigns an event only when its handle is zero, then writes raw event values +0x70/+0x74 if the record exists. Optional position copies current/target, adds 0xc00 to target y and resets timer. HP meanings are not proved here. |
| ov001:0x02088270 | THUMB | `SetStageBusyValueWrapper` | `src/overlays/ov001/calls/SetStageBusyValueWrapper.c` | `void(u32 value)`. Tail veneer preserving the input word, stored as stage-manager busy value +0x18f40. QueryStageEventState mode 0 tests this word. No boolean normalization or owned result. |
| ov001:0x02095904 | THUMB | `SetStageEventKindWrapper` | `src/overlays/ov001/calls/SetStageEventKindWrapper.c` | `void(StageEvent *event, u32 kind)`. Tail veneer preserving event pointer and kind input. The callee stores kind +0x0c, resets progression fields, updates related actors and sends kind-specific notifications. No allocated-object result. |
| ov001:0x0209b5e0 | THUMB | `ReleaseStageSlotLock1` | `src/overlays/ov001/calls/ReleaseStageSlotLock1.c` | `void(u32 slotIndex)`. Calls ReleaseStageSlotLocks with zero-based slot index and logical mask 1. Actual slot lookup adds 1; unlocking a state-6 slot may spawn/reset it. Not a sound callback. |
| ov001:0x0209b5ec | THUMB | `ReleaseStageSlotLock2` | `src/overlays/ov001/calls/ReleaseStageSlotLock2.c` | `void(u32 slotIndex)`. Same operation with logical mask 2. Real API is void despite inherited pointer-return declaration. |
| ov001:0x0209b660 | THUMB | `AddStageSlotLock1` | `src/overlays/ov001/calls/AddStageSlotLock1.c` | `void(u32 slotIndex)`. Calls AddStageSlotLocks with zero-based slot index and logical mask 1. ORs the mask; state 2 can clear active and set pending. The borrowed sound enum merely supplied integer 1. |
| ov001:0x0209b66c | THUMB | `AddStageSlotLock2` | `src/overlays/ov001/calls/AddStageSlotLock2.c` | `void(u32 slotIndex)`. Same lock operation with logical mask 2. No pointer ownership or sound-stream operation. |
| ov001:0x0209c440 | THUMB | `ClearStageManagerFlags31` | `src/overlays/ov001/calls/ClearStageManagerFlags31.c` | `void(void)`. For a nonnull manager, clears flags mask 0x31 (bits 0,4,5), preserving other bits. Purpose of the individual bits is not assigned. |
| ov001:0x0209c520 | THUMB | `ClearStageManagerFlags42` | `src/overlays/ov001/calls/ClearStageManagerFlags42.c` | `void(void)`. For a nonnull manager, clears flags mask 0x42. The number is hexadecimal mask 0x42, not decimal state 42. |
| ov001:0x0209c538 | THUMB | `ClearStageManagerFlag40000000` | `src/overlays/ov001/calls/ClearStageManagerFlag40000000.c` | `void(void)`. For a nonnull manager, clears mask 0x40000000. The bit's gameplay purpose remains unproved. |
| ov001:0x0209c554 | THUMB | `SetStageManagerFlag40000000` | `src/overlays/ov001/calls/SetStageManagerFlag40000000.c` | `void(void)`. For a nonnull manager, sets mask 0x40000000 without replacing other flags. Paired with its clear operation. |
| ov001:0x0209c56c | THUMB | `RequestSceneEventWhenSessionState6` | `src/overlays/ov001/calls/RequestSceneEventWhenSessionState6.c` | `BOOL(u32 eventId, u32 value)`. Requires the session-ready check and session state 6 plus a nonnull manager. Nonzero event ID requests zero-based id-1 with flags 0. Returns TRUE even for ID zero, when no request is made. |
| ov001:0x0209c5f0 | THUMB | `CheckStageEventGroupStates` | `src/overlays/ov001/calls/CheckStageEventGroupStates.c` | `BOOL(u32 slotIndex, u32 groupId, u32 flags)`. Specific slot requires GetEventGroupState==1. Wildcard slot 0xffff scans all groups and rejects only -1; ignored result 0 and an empty table are accepted. Preserves u16 group/index conversions. |
| ov001:0x0209c9c4 | THUMB | `FindNextActiveStageEvent` | `src/overlays/ov001/calls/FindNextActiveStageEvent.c` | `u16(u16 currentHandle)`. Scans subsequent records for activeCount!=0 OR kind==99, returning index+1 as u16 or zero at end. Input is a one-based current handle; preserve its wrapped start calculation and kind-99 exception. |

## Evidence paths and native limitations

The listed native bodies, modes and EU aliases establish each table row.
Important writer and consumer cross-checks beyond those row bodies are:

- `src/overlays/ov001/calls/FieldObject_EnsureModelsLoaded.c` stores the two
  request results in model/animation slots and polls completion separately.
  `src/overlays/ov001/calls/GetStridedBufferEntry.c` establishes class stride
  +0x44/entries +0x48. Pool creation and destruction use the distinct +0x3c/+0x40
  accessor. Free calls with omitted pointer parameters are checked against native
  R0 loads, rather than interpreted as parameterless deallocation.
- `src/overlays/ov001/calls/PlayFieldBgm.c`,
  `src/overlays/ov001/calls/UpdateFieldBgm.c` and
  `src/overlays/ov001/SceneEntryContext.h` bind the two BGM getters/setters to one
  owner and offsets. Only that type's two byte members are renamed; their offsets and layout remain unchanged.
- `src/overlays/ov001/calls/AdvanceTweenChannels.c`,
  `src/overlays/ov001/calls/StartTimerState.c`,
  `src/overlays/ov001/calls/PollTimerTask.c` and
  `src/overlays/ov001/calls/SaveElapsedSeconds.c` establish time units, baseline,
  per-channel rate and timer-completion policy. A zero duration still requires
  nonzero elapsed in the existing poller.
- `libs/nitro/nns/calls/GetRunningTaskWork.c` and task construction/update establish that
  the former heap-named accessor returns current task work. It does not allocate
  or release a heap. `src/calls/DestroyTaskObjectWrapper.c` establishes the former
  PXI-named wrapper's task-destruction/next-task result.
- `src/overlays/ov001/calls/ResolveWaitTarget.c`,
  `src/overlays/ov001/calls/GetWaitTargetPosition.c`,
  `src/overlays/ov001/calls/GetManagedActorPosition.c` and
  `src/overlays/ov001/calls/GetBoundedEntryField.c` establish tag resolution,
  cached borrowed positions and managed-actor lookup. Search producers and the
  comparator establish score ordering and per-family gates.
- `src/overlays/ov001/calls/QueryStageEventState.c`,
  `src/overlays/ov001/calls/GetEventGroupState.c`,
  `src/overlays/ov001/calls/GetStageEventRecord.c`,
  `src/overlays/ov001/calls/StartStageEventInstance.c` and
  `src/overlays/ov001/calls/SetGroupAnimationTrack.c` establish guard semantics,
  aggregation, handle conversion, raw event results and the u8 animation boundary.
  Lock setters and `StageSlotState.h` establish the logical/physical lock masks.

Task destruction that leaves a global handle intact does not make its presence
predicate a liveness check. Resetting a subsystem pointer does not free task work.
Stopping a linked entry is distinct from freeing its inline pool storage. Pool
counts, slot IDs, saved flag indices, resource handles, animation bytes and
pointer-sized logical returns must keep their distinct native boundaries.

No API here adds general range checks or a successful-allocation guarantee.
The task and event partial structs need further layout work before a host port
can adopt them as complete layouts. Higher-level meanings remain deliberately
unassigned for generic hooks, timer channel 1, tracked raw state values and
individual stage-manager flag bits. Hexadecimal masks 0x31, 0x42 and
0x40000000 are not decimal state numbers.

## Reproducible byte-exact validation

Run from `eu/`. All 114 renamed/corrected entrypoints pass, together with
seven unchanged consumers of the corrected SceneEntry header:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/InitFieldObjectClassTable.c InitFieldObjectClassTable --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetFieldObjectClassAtIndex.c SetFieldObjectClassAtIndex --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RefreshFieldObjectsAndEntryActorSlots.c RefreshFieldObjectsAndEntryActorSlots --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldObjectClassCount.c GetFieldObjectClassCount --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldObjectClassAtIndex.c GetFieldObjectClassAtIndex --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldObjectByClassAndIndex.c GetFieldObjectByClassAndIndex --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetFieldObjectListHead.c GetFieldObjectListHead --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RequestFieldObjectAnimationBuffer.c RequestFieldObjectAnimationBuffer --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RequestFieldObjectModelResource.c RequestFieldObjectModelResource --thumb
python tools/verify_idx.py src/overlays/ov001/calls/FreeFieldObjectClassAnimationBuffers.c FreeFieldObjectClassAnimationBuffers --thumb
python tools/verify_idx.py src/overlays/ov001/calls/FreeFieldObjectShapeStorage.c FreeFieldObjectShapeStorage --thumb
python tools/verify_idx.py src/overlays/ov001/calls/CallFieldObjectHook13IfPresent.c CallFieldObjectHook13IfPresent --thumb
python tools/verify_idx.py src/overlays/ov001/calls/CallFieldObjectHook14IfSavedFlagClear.c CallFieldObjectHook14IfSavedFlagClear --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ActivateEntryPoolSlot.c ActivateEntryPoolSlot --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetEntryPoolObjectAtIndex.c GetEntryPoolObjectAtIndex --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetFieldEntryActorAnimationGroup.c SetFieldEntryActorAnimationGroup --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetSessionFlagEnabled.c SetSessionFlagEnabled --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DestroyFieldEntryPoolManager.c DestroyFieldEntryPoolManager --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InitFieldEntryPoolTable.c InitFieldEntryPoolTable --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RegisterFieldEntryPool.c RegisterFieldEntryPool --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetFieldEntryPoolIndex.c GetFieldEntryPoolIndex --thumb
python tools/verify_idx.py src/overlays/ov001/calls/StopAndClearFieldEntryList.c StopAndClearFieldEntryList --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ApplyActorSlotsToFieldEntryList.c ApplyActorSlotsToFieldEntryList --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldEntryPoolCount.c GetFieldEntryPoolCount --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldEntryPoolAtIndex.c GetFieldEntryPoolAtIndex --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldEntryByPoolAndIndex.c GetFieldEntryByPoolAndIndex --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetFieldEntryListHead.c GetFieldEntryListHead --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSceneEntryPrimaryBgmId.c GetSceneEntryPrimaryBgmId --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSceneEntrySecondaryBgmId.c GetSceneEntrySecondaryBgmId --thumb
python tools/verify_idx.py src/overlays/ov001/calls/WorldNamedEntryHasKind.c WorldNamedEntryHasKind --thumb
python tools/verify_idx.py src/overlays/ov001/calls/HasSceneEntryContext.c HasSceneEntryContext --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DestroyStageEventContext.c DestroyStageEventContext --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ResetStageEventContext.c ResetStageEventContext --thumb
python tools/verify_idx.py src/overlays/ov001/calls/TriggerQueuedStageEventPairs.c TriggerQueuedStageEventPairs --thumb
python tools/verify_idx.py src/overlays/ov001/calls/HasQueuedStageEventValue.c HasQueuedStageEventValue --thumb
python tools/verify_idx.py src/overlays/ov001/calls/StartPostIntroElapsedTimer.c StartPostIntroElapsedTimer --thumb
python tools/verify_idx.py src/overlays/ov001/calls/AllocateFieldTimerCounter.c AllocateFieldTimerCounter --thumb
python tools/verify_idx.py src/overlays/ov001/calls/AllocateTaskTimerSlot.c AllocateTaskTimerSlot --thumb
python tools/verify_idx.py src/overlays/ov001/auto/StopPostIntroElapsedTimer.c StopPostIntroElapsedTimer --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ResumeSessionTimerUpdates.c ResumeSessionTimerUpdates --thumb
python tools/verify_idx.py src/overlays/ov001/calls/PauseSessionTimerUpdates.c PauseSessionTimerUpdates --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSessionElapsedMilliseconds.c GetSessionElapsedMilliseconds --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSessionTimerChannel1Milliseconds.c GetSessionTimerChannel1Milliseconds --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetPostIntroElapsedMilliseconds.c GetPostIntroElapsedMilliseconds --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldTimerCounterMilliseconds.c GetFieldTimerCounterMilliseconds --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetTaskTimerElapsedMilliseconds.c GetTaskTimerElapsedMilliseconds --thumb
python tools/verify_idx.py src/overlays/ov001/auto/SetPostIntroElapsedMilliseconds.c SetPostIntroElapsedMilliseconds --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetFieldTimerCounterMilliseconds.c SetFieldTimerCounterMilliseconds --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetTaskTimerElapsedMilliseconds.c SetTaskTimerElapsedMilliseconds --thumb
python tools/verify_idx.py src/overlays/ov001/auto/SetFieldTimerRateFx12.c SetFieldTimerRateFx12 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseHighIdTaskNodes.c ReleaseHighIdTaskNodes --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseAllTaskNodes.c ReleaseAllTaskNodes --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetFieldTaskResult.c GetFieldTaskResult --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetSavedTaskFlag.c SetSavedTaskFlag --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ClearSessionTimerStatePointer.c ClearSessionTimerStatePointer --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldTaskManagerWork.c ReleaseFieldTaskManagerWork --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldScreenTransitionWork.c ReleaseFieldScreenTransitionWork --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DestroyScreenFadeTaskAndClearHandle.c DestroyScreenFadeTaskAndClearHandle --thumb
python tools/verify_idx.py src/overlays/ov001/calls/BeginFieldScreenModeTransition.c BeginFieldScreenModeTransition --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DrawSpriteFrameQuadWithDepthUpdate.c DrawSpriteFrameQuadWithDepthUpdate --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DrawSpriteFrameQuadWithoutDepthUpdate.c DrawSpriteFrameQuadWithoutDepthUpdate --thumb
python tools/verify_idx.py src/overlays/ov001/auto/InitNoTargetReference.c InitNoTargetReference --thumb
python tools/verify_idx.py src/overlays/ov001/auto/InitFieldObjectTargetReference.c InitFieldObjectTargetReference --thumb
python tools/verify_idx.py src/overlays/ov001/auto/InitFieldEntryTargetReference.c InitFieldEntryTargetReference --thumb
python tools/verify_idx.py src/overlays/ov001/auto/InitStageSlotTargetReference.c InitStageSlotTargetReference --thumb
python tools/verify_idx.py src/overlays/ov001/auto/InitManagedActorTargetReference.c InitManagedActorTargetReference --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InitTargetSearchScore.c InitTargetSearchScore --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IsTargetSearchScoreBetter.c IsTargetSearchScoreBetter --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IsManagedActorSlot0Empty.c IsManagedActorSlot0Empty --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ResolveSelectedTargetPosition.c ResolveSelectedTargetPosition --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetTargetSelectionActiveMask.c GetTargetSelectionActiveMask --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetTargetSelectionFlag2.c GetTargetSelectionFlag2 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetTargetSelectionFlag1.c GetTargetSelectionFlag1 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetTargetSelectionFadeLevel2.c GetTargetSelectionFadeLevel2 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetEventSlotAndEntryTargetSearchEnabled.c SetEventSlotAndEntryTargetSearchEnabled --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DestroySessionCallbackTask.c DestroySessionCallbackTask --thumb
python tools/verify_idx.py src/overlays/ov001/calls/HasSessionCallbackTaskHandle.c HasSessionCallbackTaskHandle --thumb
python tools/verify_idx.py src/overlays/ov001/calls/EnsureFieldMessageLoaderManager.c EnsureFieldMessageLoaderManager --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DestroyFieldMessageLoaderManager.c DestroyFieldMessageLoaderManager --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetFieldMessageLoaderUpdatesPaused.c SetFieldMessageLoaderUpdatesPaused --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseEventContextWork.c ReleaseEventContextWork --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseEventContextResources.c ReleaseEventContextResources --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetManagedActorCount.c GetManagedActorCount --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetManagedActorPositionWithCallback.c GetManagedActorPositionWithCallback --thumb
python tools/verify_idx.py src/overlays/ov001/calls/TryBeginTrackedMainBrightness.c TryBeginTrackedMainBrightness --thumb
python tools/verify_idx.py src/overlays/ov001/calls/UpdateTrackedMainBrightness.c UpdateTrackedMainBrightness --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ResetTrackedMainBrightness.c ResetTrackedMainBrightness --thumb
python tools/verify_idx.py src/overlays/ov001/calls/BeginStageEntriesIfActive.c BeginStageEntriesIfActive --thumb
python tools/verify_idx.py src/overlays/ov001/calls/QueryAllStageEventStateIfActive.c QueryAllStageEventStateIfActive --thumb
python tools/verify_idx.py src/overlays/ov001/calls/TriggerNextStageEventFromSource1IfActive.c TriggerNextStageEventFromSource1IfActive --thumb
python tools/verify_idx.py src/overlays/ov001/calls/StartStageEventInstanceIfActive.c StartStageEventInstanceIfActive --thumb
python tools/verify_idx.py src/overlays/ov001/calls/FindNextActiveStageEventIfActive.c FindNextActiveStageEventIfActive --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetStageSlotLock1IfActive.c GetStageSlotLock1IfActive --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ResetStageGroupRowsAndRestoreDefaultIfActive.c ResetStageGroupRowsAndRestoreDefaultIfActive --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetStageEventGroupAnimationIfPresent.c SetStageEventGroupAnimationIfPresent --thumb
python tools/verify_idx.py src/overlays/ov001/calls/AddStageScoreWrapper.c AddStageScoreWrapper --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFocusEventActorPositionWrapper.c GetFocusEventActorPositionWrapper --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ClearStagePartySlot.c ClearStagePartySlot --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ConfigureStagePartySlot.c ConfigureStagePartySlot --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetStageBusyValueWrapper.c SetStageBusyValueWrapper --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetStageEventKindWrapper.c SetStageEventKindWrapper --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseStageSlotLock1.c ReleaseStageSlotLock1 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseStageSlotLock2.c ReleaseStageSlotLock2 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/AddStageSlotLock1.c AddStageSlotLock1 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/AddStageSlotLock2.c AddStageSlotLock2 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ClearStageManagerFlags31.c ClearStageManagerFlags31 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ClearStageManagerFlags42.c ClearStageManagerFlags42 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ClearStageManagerFlag40000000.c ClearStageManagerFlag40000000 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetStageManagerFlag40000000.c SetStageManagerFlag40000000 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RequestSceneEventWhenSessionState6.c RequestSceneEventWhenSessionState6 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/CheckStageEventGroupStates.c CheckStageEventGroupStates --thumb
python tools/verify_idx.py src/overlays/ov001/calls/FindNextActiveStageEvent.c FindNextActiveStageEvent --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetSceneEntryPrimaryBgmId.c SetSceneEntryPrimaryBgmId --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetSceneEntrySecondaryBgmId.c SetSceneEntrySecondaryBgmId --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetCurrentSceneEntrySlotId.c GetCurrentSceneEntrySlotId --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSceneEntryCameraHeightLimit.c GetSceneEntryCameraHeightLimit --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSceneEntryGroundHeight.c GetSceneEntryGroundHeight --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSceneEntryPatrolPointCount.c GetSceneEntryPatrolPointCount --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSceneEntryResourceId.c GetSceneEntryResourceId --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSceneResourceHandle.c GetSceneResourceHandle --thumb
python tools/verify_idx.py src/overlays/ov041/calls/StageStateFinish.c StageStateFinish --thumb
bash tools/gate.sh
```

The fresh official gate passes all 108 linked modules. Affected function bytes,
resolved relocation targets/types and addends, and all module hashes match the
preserved pre-rename baseline. BGM member names change no field width, offset,
initialization or behavior. No C/DATA reconstruction credit is added.
