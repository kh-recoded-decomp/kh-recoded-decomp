# Field script, object and actor command contracts

These 31 EU overlay 001 entrypoints extend the field script documentation with
27 run handlers, two resume handlers and two ordinary helpers. The identities
below are native EU addresses, all in Thumb mode. Names describe demonstrated
behavior; they do not claim original source spelling. Source, table and instruction evidence support the contracts below. The
validation section records the official checks for this naming block.

## The interpreter and the three handler groups

These tables use the same MAIN `ScriptVm_RunFrame` discussed in
`SCRIPT_SKIP_SOUND_CONTRACTS.md`. This is established by writes and reads of the
same global, rather than by similar command names:

- `StoreGlobalArrayEntry(index, value)` writes
  `gScriptHandlerTables[index]` directly.
- `EnterPendingRoom` registers `gFieldScriptCommandHandlers` at group 2.
- `CreateFieldObjectManager` registers `gFieldObjectScriptCommandHandlers` at
  group 4.
- `InitOverlayObjectSystem` registers `gActorScriptCommandHandlers` at group 1.
- `ScriptVm_RunFrame` reads `gScriptHandlerTables[command[0]]` and selects entry
  `command[1]` from that table. An entry consists of a run pointer and a resume
  pointer, with a native stride of eight bytes.

The existing overlay declarations are flat arrays of erased function pointers:
190 pointers in the field table, 78 in the field-object table and 186 in the
actor table. They represent 95, 39 and 93 run/resume pairs, respectively. A flat
pointer index is not the command number. The tables below give group and entry
in hexadecimal; `2/40`, for example, means group 2, entry 0x40.

The logical run ABI is `int run(ScriptVm *vm, u8 *operands)` and the resume ABI
is `int resume(ScriptVm *vm, s32 argument)`. Several native wrappers consume
neither argument, or declare an unused pointer that is forwarded to a no-input
callee. Those declarations do not establish an additional script operand.
This document does not repair erased function types or change matched wrappers.

The command header occupies four bytes. The low 11 bits of its halfword at +2
encode its length in words; operands start at +4. Integer descriptors used here
are eight bytes apart. `ScriptVm_ReadOperandInt` first resolves a descriptor,
then reads its signed word payload only when the resolved tag is 1, otherwise
returning zero. `ByteCode_ResolveOperand` produces an address within the current
script buffer; tag 0x40 selects a language-specific relative address. An address
resolved this way remains borrowed from the script buffer unless a callee
explicitly copies it.

For the main command stream, run result 1 advances by the encoded command
length. Result 0 suspends the command and installs its paired resume pointer;
the command is retried on later frames when that pointer is null. A resume
result 0 continues waiting, while result 1 advances the suspended command.
These are interpreter control results, not resource-loading or camera-success
booleans. The interpreter's auxiliary-slot path has a different policy: it
advances the command after issuing it, retains the paired callback only for a
zero run result, and polls occupied auxiliary slots separately. Preserve the
header's slot/skip handling when porting the interpreter; do not turn every zero
result into a generic blocking call.

Evidence: EU wrappers `src/calls/StoreGlobalArrayEntry.c`,
`src/calls/ScriptVm_RunFrame.c`, `src/calls/ScriptCommandTables.h`,
`src/calls/ScriptVm_ReadOperandInt.c`, `src/calls/ByteCode_ResolveOperand.c`,
`src/data/gScriptCommandTables.c`, and overlay 001 wrappers
`src/overlays/ov001/calls/EnterPendingRoom.c`,
`src/overlays/ov001/calls/CreateFieldObjectManager.c` and
`src/overlays/ov001/calls/InitOverlayObjectSystem.c`. The three overlay tables
are under `src/overlays/ov001/data/tables/` with the names given above. Shared
included bodies must be interpreted through these EU aliases.

## Field table: resources, menu values and panel work

The operands column describes decoded values in their original order. A dash
means no operand is read by the handler or its no-input callee.

| Native address | Function | Group/entry and role | Operands; behavior and result |
|---|---|---|---|
| 0x02065218 | `ScriptCmd_LoadLevelTableFile` | 2/0c run | None. Calls `LoadLevelTableFile`; returns 1. The callee loads the session archive's level table, fixes its relative pointers, derives the item-price list outside mode 900 and forwards nonempty entries to the actor setup helper. |
| 0x02065454 | `ScriptCmd_LoadOffsetTableFile` | 2/18 run | None. Calls `LoadOffsetTableFile`; returns 1. That callee allocates a holder, loads the offset table from the session archive and rebases each counted offset within its file. |
| 0x020656a0 | `ScriptCmd_LoadSceneData` | 2/2c run | Two resolved addresses at +0 and +8: area-file name, then record-file name. Calls `LoadSceneData`; returns 1. The ov031 callee frees previous scene records, creates owned copies of areas, steps and per-record arrays, sizes object groups and resets scene cursors. |
| 0x020659f4 | `ScriptCmd_SetOv043CameraFlags8` | 2/3f run | None. Replaces the ov043 camera flags word with 8, through `Ov043Camera_SetFlags`; returns 1. It does not OR the value into the old flags. The broader meaning of value 8 is not established here. |
| 0x02065a00 | `ScriptCmd_EnterPanelModeThree` | 2/40 run | One resolved name address. Calls `EnterPanelModeThree`; returns 0. The ov036 callee snapshots cached screen brightness, opens the panel message archive, writes panel state 3, sets flags mask 0x10, clears session bits 0x3309/0x3527 and starts timer 0x14. |
| 0x02065a10 | `ScriptCmd_TestSceneFlag10Clear` | 2/40 resume | No decoded operands. Returns 1 exactly when `IsSceneFlag10Clear` observes ov036 panel-work flags mask 0x10 clear; returns 0 while that mask is set. This is the resume partner of the preceding run handler. |
| 0x02065a64 | `ScriptCmd_ForwardSubModeStart` | 2/45 run | None. Calls `ForwardSubModeStart`; returns 1. The ov021 callee refreshes the camera heading only for submode 0 and has no operation for submodes 1, 2 or 3. |
| 0x02065c5c | `ScriptCmd_SetSessionTableName` | 2/4d run | Integer index at +0, resolved name address at +8. Calls `SetSessionTableName`; returns 1. The callee allocates `strlen(name)+1` bytes and copies the byte string into the indexed session name slot. |
| 0x02065e34 | `ScriptCmd_SetSessionFlag35e3` | 2/1d run | None. Sets packed session bit 0x35e3; returns 1. No gameplay meaning is assigned to this bit. |
| 0x02065e50 | `ScriptCmd_SetupSlotPanelMode` | 2/54 run | Integer mode at +0 and integer enable at +8. Calls `SetupSlotPanelMode`; returns 1. Modes 0/1 initialize layouts when needed and toggle packed bits 0x3716/0x3714. Mode 2 can mark slots ready. All paths forward the original enable value to the panel helper, including unhandled mode values. |
| 0x02065518 | `ScriptCmd_SetMenuItemKind` | 2/20 run | Integer item index, replacement kind and refresh flag at +0/+8/+16. Normalizes only the third value to zero/nonzero, calls `SetMenuItemKind` and discards its previous-kind result; returns 1. |
| 0x02065f2c | `ScriptCmd_InvokeSessionCallback` | 2/5a run | None. Invokes the optional no-input callback at session +0x2838 through its existing adapter; returns 0 regardless of whether the callback exists. |
| 0x02065f38 | `ScriptCmd_TestSessionCheckCallback` | 2/5a resume | No decoded operands. Returns the normalized result of `RunSessionCheckCallback`: 1 when the callback at session +0x2834 is absent or returns zero, and 0 when that callback returns nonzero. |

The two 2/40 handlers operate on ov036 work reached through
`data_ov036_020c3940.work`. In `Flag10`, 10 is hexadecimal mask **0x10**, not
decimal state 10. The run handler's state is the separate integer value 3.
Likewise `SetOv043CameraFlags8` addresses ov043 work, a separate owner; it must
not be applied to the ov036 flags merely because both are camera/panel paths.

The resource loaders place their allocations in global subsystem holders;
their script wrappers return no owned pointer. The no-input loader ABI does not
mean that a VM or operand pointer becomes archive ownership. The area and record
names passed to ov031 are borrowed; `LoadSceneData` allocates its own content
arrays and releases its temporary loaded files. Allocation failures and malformed
archive data are not checked by these wrappers.

`SetSessionTableName` stores a newly allocated copy, so the input string can
remain script-owned. Its body shows no index validation and no release of the
previous slot value before assignment. This is not evidence that repeatedly
replacing an occupied slot is safe. The complete name-table teardown contract
must be checked before changing that lifecycle.

The raw helper and menu setter account for the two non-command functions in
this block:

| Native address | Function | Logical contract and limits |
|---|---|---|
| 0x02067ee4 | `SetMenuItemKind` | `u8 (int index, u8 kind, int refresh)`. Reads and returns the previous first byte of the menu item at the indexed table pointer, stores the replacement byte, and calls `HighlightSelectedMenuPanels` when refresh is nonzero. `EnterMenuItem` and the highlight consumer establish that this byte selects the kind passed to `OpenFieldMenuForMode`. There is no local index/null guard and no pointer ownership transfer. |
| 0x02064490 | `InvokeSessionCheckCallbackOrDefault` | `u32 (void)`. Calls the session +0x2834 callback when present and returns its raw word; otherwise returns 1. This differs from `RunSessionCheckCallback`, which inverts the callback's zero/nonzero result. Installed callbacks can return masks such as 0x20 or 0x60, so the raw helper must not be replaced with a boolean predicate. |

The session +0x2838 callback's gameplay purpose is not established by invocation
alone. It must not be assumed to share the +0x2834 callback's signature or return
contract. Both belong to the installed session callback table; neither script
wrapper takes ownership of that table or of its scene work.

Additional evidence is in the matching EU callees
`src/overlays/ov001/calls/LoadLevelTableFile.c`,
`src/overlays/ov001/calls/LoadOffsetTableFile.c`,
`src/overlays/ov001/calls/SetSessionTableName.c`,
`src/overlays/ov001/calls/SetupSlotPanelMode.c`,
`src/overlays/ov001/calls/RunSessionCheckCallback.c`,
`src/overlays/ov031/calls/LoadSceneData.c`,
`src/overlays/ov036/calls/EnterPanelModeThree.c`,
`src/overlays/ov036/calls/IsSceneFlag10Clear.c`,
`src/overlays/ov043/auto/Ov043Camera_SetFlags.c` and
`src/overlays/ov021/calls/ForwardSubModeStart.c`. The indexed kind operation is
confirmed by `src/overlays/ov001/calls/EnterMenuItem.c` and
`src/overlays/ov001/calls/HighlightSelectedMenuPanels.c`.

## Field-object table: two distinct managers

All five handlers below return 1. That advances the main stream; it does not
report a successful allocation, lookup or activation.

| Native address | Function | Group/entry | Operands; demonstrated effects |
|---|---|---|---|
| 0x0207fad0 | `ScriptCmd_InitFieldObjectClassTable` | 4/00 run | Integer count at +0. Allocates and zeroes a `count*4` pointer table for the manager at `data_ov001_020a04f8`, stores the count in a byte and loads its mode tables. |
| 0x0207fae0 | `ScriptCmd_ActivateFieldObject` | 4/01 run | Integer class index, object index and activation argument at +0/+8/+16. `PrependListNode` resolves the class/object pair, sets object flag mask 0x2, links the node into the active list and calls `FieldObject_Activate` with the third value. That value's meaning remains opaque. |
| 0x0207ffd4 | `ScriptCmd_InitFieldEntryPoolTable` | 4/0d run | Integer count at +0. Allocates and zeroes another `count*4` pointer table for `data_ov001_020a04fc`, stores a byte count and conditionally frees the previous cached resources according to session/cache state. This is a different manager from +04f8. |
| 0x02080020 | `ScriptCmd_ReallocFieldEntryCacheRecord` | 4/0f run | Integer entry index and ID at +0/+8. `ReallocTableEntry` releases an existing pointer, allocates a replacement 12-byte record, stores the ID as `u16`, clears active/value/timer and sets manager flags mask 0x2. |
| 0x020807a4 | `ScriptCmd_SetFieldEntryCachePaused` | 4/26 run | Integer pause value at +0. Any nonzero value sets manager byte +5 mask 0x10 and deactivates all currently linked entries; zero clears that mask and activates the entries. |

These operations retain their tables and records in their respective managers;
the VM receives no owned storage. None of these wrappers adds bounds checking.
The allocation uses the full decoded count while the stored count narrows to a
byte. Preserve that boundary rather than assuming the field is a host `size_t`.
Do not merge the two tables into one pool because their initialization commands
have similar bodies. Reallocating the cache record is replacement of one record,
not resizing an object pool. Activation retains all three inputs; a legacy
incomplete declaration of the lookup helper must not remove the object index.

Evidence: the group-4 table, the five wrappers, and
`src/overlays/ov001/calls/func_ov001_0207ee00.c`,
`src/overlays/ov001/calls/func_ov001_02086e58.c`,
`src/overlays/ov001/calls/PrependListNode.c`,
`src/overlays/ov001/calls/FieldObject_Activate.c`,
`src/overlays/ov001/calls/ReallocTableEntry.c` and
`src/overlays/ov001/calls/SetCachePaused.c`.

## Actor table: probes, camera, VRAM and persistent records

All rows return 1 after issuing their effects except the explicitly polling
camera handler. The table pairs every handler in this section with a null
resume pointer.

| Native address | Function | Group/entry | Operands; demonstrated effects and limits |
|---|---|---|---|
| 0x0208cbbc | `ScriptCmd_DisableResolvedActorProbeSphere` | 1/11 run | Integer descriptor at +0, followed by `ScriptCmd_ReturnValue(vm, value)` resolution. Passes the resolved low 16 bits as actor index to `SetWorldObjectProbeSphere(index, 0, 0)`. The disabled backend clears object flags mask 0x10; it neither builds a zero-radius sphere nor frees one. |
| 0x0208d55c | `ScriptCmd_ResetFieldCameraChannel` | 1/2a run | None. `ActorChannel_ResetAndInvalidate` resets fields in `gActorChannelContext` and writes -1 to its word at +0x1e0. The wrapper's pointer argument is unused by the real callee. |
| 0x0208d568 | `ScriptCmd_RestoreSavedFieldCamera` | 1/2b run | None. `RestoreSavedCameraState` restores saved target, position and angles and clears its timer. Its hold-mode-1 path only clears the embedded object's word +0x58 and returns early. Anchor handling and this early return remain part of the callee contract. |
| 0x0208d574 | `ScriptCmd_WaitForFieldCameraTransition` | 1/29 run | None. Returns 1 when `IsTransitionStateDone` is nonzero, otherwise 0. With null resume, the main interpreter retries this run handler while pending. The predicate checks active state, mode, pending count, target and tracker; inactive or mode -1/0 is already done. |
| 0x0208d5c8 | `ScriptCmd_PushActorVramState` | 1/02 run | None. `PushVramState` snapshots both frame texture and palette allocator states into the actor registry's 16-entry stacks and increments depth. The wrapper discards the returned depth. Overflow calls `OS_Terminate`; it is not a recoverable zero result. |
| 0x0208eba8 | `ScriptCmd_BeginEventCameraAndFreezeSubMode` | 1/4c run | None. Calls `InitFieldCameraFromPreset`, then `SetSubModeFrozen(1)`. The first loads the event camera resource and schedules its update. Freeze is dispatched to a mode-specific camera/panel helper; submode 1 deliberately does nothing. |
| 0x0208ebb8 | `ScriptCmd_FinishEventCameraAndUnfreezeSubMode` | 1/4d run | None. Calls `FinishEventCameraCut`, then `SetSubModeFrozen(0)`. The explicit unfreeze still occurs if the finish helper returns early because no cut is active. |
| 0x0208ecec | `ScriptCmd_GrantRecordPair` | 1/50 run | Two integer categories at +0/+8, kept in order. Calls the existing `GrantStarterRecordPair` helper: creates two active kind-0, level-0 records, stores insertion IDs +0x200 in save slots +0x2d84/+0x2d88, sets per-category flags/counters, then clears both nibbles at save +0x28d7. No asset or consumer evidence establishes the word "starter"; the command name omits it. |
| 0x0208ee58 | `ScriptCmd_FrameCameraOnActor` | 1/55 run | Integer actor index at +0. `FrameCameraOnActor` uses that actor and managed actor 0, computes heading and midpoint focus, adjusts distance/height, then requests a field-camera target. A blocked-angle path can return early; the command still returns 1. |
| 0x0208ee68 | `ScriptCmd_SetActorAngleDegrees` | 1/56 run | Integer actor ID and degrees at +0/+8. Resolves the low 16 bits of the ID, performs signed native `(degrees << 16) / 360`, stores the low halfword at actor-node +0x82 and sets node flags at +4 mask 0x20. The rotation axis and the wider policy of this flag remain unproved. |
| 0x0208efd4 | `ScriptCmd_RefreshFieldHudIconRecords` | 1/5b run | None. Its no-input helper invokes active-record callbacks for decimal IDs 10 and 11 (0x0a/0x0b), then calls `BlendIconTiles` with the field manager's blend value. |

Probe disabling and angle writes resolve borrowed actor objects; they transfer
no ownership. Actor-node +4 flags and the probe object's flags are separate
views and should not be unified by coincident bit values. Preserve the probe's
second resolution stage and its `u16` boundary. Preserve native signed angle
arithmetic, division and halfword storage rather than silently introducing
floating-point conversion or angle normalization.

Camera and HUD commands access global subsystem state. They do not consume a
script-provided camera/HUD pointer. These commands do not make global gameplay
freeze or successful camera movement claims. `PushActorVramState` saves allocator
state rather than copying textures or allocating new VRAM; its matching restore
and nesting lifecycle must be retained by a port.

The pair-grant operation mutates persistent save state. Each stored record
category narrows to a byte, but the original integer category is also used for
bit/counter indexing. Do not mask the original category before those operations.
The wrapper checks neither category range nor record-insertion failure and
returns no inserted ID to the VM. The native save offsets establish two assigned
slots, without proving the gameplay label "starter" or a new-game-only use.

Evidence: the group-1 table and the listed wrappers, plus
`src/calls/SetWorldObjectProbeSphere.c`, `src/calls/SetObjectProbeSphere.c`,
`src/calls/PushVramState.c`, `src/calls/GrantStarterRecordPair.c`, and overlay 001
callees `src/overlays/ov001/calls/ActorChannel_ResetAndInvalidate.c`,
`src/overlays/ov001/calls/RestoreSavedCameraState.c`,
`src/overlays/ov001/calls/IsTransitionStateDone.c`,
`src/overlays/ov001/calls/InitFieldCameraFromPreset.c`,
`src/overlays/ov001/calls/FinishEventCameraCut.c`,
`src/overlays/ov001/calls/FrameCameraOnActor.c` and
`src/overlays/ov001/calls/func_ov001_02073718.c`, together with
`src/overlays/ov021/calls/SetSubModeFrozen.c`. EU instruction bytes additionally
confirm the callback default branches and the angle conversion/narrowing.

## Remaining boundaries for a port

These are contracts for the matched target. Partial structures show only fields
accessed by a particular function; they are not allocation-size or portable
layout declarations. A host port should separate VM descriptors, native archive
offsets and save encodings from host pointers while preserving these observed
effects and callback polarities. This block does not add range checks, new
ownership rules or invented arguments to the target implementation.

Outstanding meanings are limited explicitly: the activation argument, packed
bit 0x35e3, ov043 flags value 8, the session +0x2838 callback's gameplay role,
and the actor angle's axis/flag policy still require their writers, consumers
or asset formats. The earlier table comments that called these adapters phase
changes or overlay unloads do not establish their behavior.

## Reproducible byte-exact validation

Run these existing verifier commands from `eu/`. All 31 renamed entrypoints
and the unchanged `RunSessionCheckCallback` pass. The latter additionally
checks the documented null/default polarity. No instruction changes are needed.

```sh
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_LoadLevelTableFile.c ScriptCmd_LoadLevelTableFile --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_LoadOffsetTableFile.c ScriptCmd_LoadOffsetTableFile --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_LoadSceneData.c ScriptCmd_LoadSceneData --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptCmd_SetOv043CameraFlags8.c ScriptCmd_SetOv043CameraFlags8 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_EnterPanelModeThree.c ScriptCmd_EnterPanelModeThree --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_TestSceneFlag10Clear.c ScriptCmd_TestSceneFlag10Clear --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_ForwardSubModeStart.c ScriptCmd_ForwardSubModeStart --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetSessionTableName.c ScriptCmd_SetSessionTableName --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetSessionFlag35e3.c ScriptCmd_SetSessionFlag35e3 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetupSlotPanelMode.c ScriptCmd_SetupSlotPanelMode --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_TestSessionCheckCallback.c ScriptCmd_TestSessionCheckCallback --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_InvokeSessionCallback.c ScriptCmd_InvokeSessionCallback --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetMenuItemKind.c ScriptCmd_SetMenuItemKind --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetMenuItemKind.c SetMenuItemKind --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InvokeSessionCheckCallbackOrDefault.c InvokeSessionCheckCallbackOrDefault --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_InitFieldObjectClassTable.c ScriptCmd_InitFieldObjectClassTable --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_ActivateFieldObject.c ScriptCmd_ActivateFieldObject --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_InitFieldEntryPoolTable.c ScriptCmd_InitFieldEntryPoolTable --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_ReallocFieldEntryCacheRecord.c ScriptCmd_ReallocFieldEntryCacheRecord --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetFieldEntryCachePaused.c ScriptCmd_SetFieldEntryCachePaused --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_DisableResolvedActorProbeSphere.c ScriptCmd_DisableResolvedActorProbeSphere --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_ResetFieldCameraChannel.c ScriptCmd_ResetFieldCameraChannel --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_RestoreSavedFieldCamera.c ScriptCmd_RestoreSavedFieldCamera --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_WaitForFieldCameraTransition.c ScriptCmd_WaitForFieldCameraTransition --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_PushActorVramState.c ScriptCmd_PushActorVramState --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_BeginEventCameraAndFreezeSubMode.c ScriptCmd_BeginEventCameraAndFreezeSubMode --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_FinishEventCameraAndUnfreezeSubMode.c ScriptCmd_FinishEventCameraAndUnfreezeSubMode --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_GrantRecordPair.c ScriptCmd_GrantRecordPair --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_FrameCameraOnActor.c ScriptCmd_FrameCameraOnActor --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetActorAngleDegrees.c ScriptCmd_SetActorAngleDegrees --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_RefreshFieldHudIconRecords.c ScriptCmd_RefreshFieldHudIconRecords --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RunSessionCheckCallback.c RunSessionCheckCallback --thumb
bash tools/gate.sh
```

The fresh official gate passes all 108 linked modules. The affected production
objects retain identical function bytes, resolved relocation targets/types and
addends; all 108 module hashes also match the preserved pre-rename baseline.
