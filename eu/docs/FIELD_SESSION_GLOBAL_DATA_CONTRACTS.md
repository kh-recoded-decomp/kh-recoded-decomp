# EU ov001 service and UI state owners

These names identify the physical BSS storage and the code that establishes each owner. They do not change field layout, calling conventions, allocation behavior, or task lifetime. A task-work pointer borrows the work owned by the task system; an explicitly allocated manager has a separate heap lifetime. Existing translation units often expose only a prefix or an extended view of a global, so those declarations are evidence of accessed offsets, not complete interchangeable structure definitions.

## Identity and source map

| EU identity | Name | Physical storage | Definition |
| --- | --- | --- | --- |
| ov001 `0x020a0480` | `gFieldSessionWork` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a0480.c` |
| ov001 `0x020a0484` | `gFieldEffectPool` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a0484.c` |
| ov001 `0x020a0488` | `gSubScene9Work` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a0488.c` |
| ov001 `0x020a048c` | `gFieldSceneEntryContext` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a048c.c` |
| ov001 `0x020a0490` | `gStageEventContext` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a0490.c` |
| ov001 `0x020a0494` | `gSessionTimerWork` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a0494.c` |
| ov001 `0x020a0498` | `gFieldTaskManagerWork` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a0498.c` |
| ov001 `0x020a049c` | `gFieldOffsetTableHolder` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a049c.c` |
| ov001 `0x020a04a0` | `gFieldScreenTransitionWork` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04a0.c` |
| ov001 `0x020a04a4` | `gFieldTargetSelectionWork` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04a4.c` |
| ov001 `0x020a04a8` | `gSessionCallbackTaskHandle` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04a8.c` |
| ov001 `0x020a04ac` | `gSessionCallbackListStorage` | 12 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04a8.c` |
| ov001 `0x020a04b8` | `gFieldMessageSpriteManager` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04b8.c` |
| ov001 `0x020a04bc` | `gManagedActorGlobals` | 8 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04b8.c` |
| ov001 `0x020a04c4` | `gFieldSceneGlobals` | 8 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04c4.c` |
| ov001 `0x020a04cc` | `gFieldHudGaugeState` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04cc.c` |
| ov001 `0x020a04d0` | `gFieldCommandMenuGlobals` | 12 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04cc.c` |
| ov001 `0x020a04dc` | `gFieldMenuFadePalette` | 8 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04dc.c` |
| ov001 `0x020a04e4` | `gMessageWindowWork` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04e4.c` |
| ov001 `0x020a04e8` | `gSubscenePanelWork` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04e8.c` |
| ov001 `0x020a04ec` | `gCounterHudWork` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04ec.c` |
| ov001 `0x020a04f0` | `gArrowPromptWork` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04f0.c` |
| ov001 `0x020a04f4` | `gFieldMinigameWork` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04f4.c` |
| ov001 `0x020a04f8` | `gFieldObjectClassManager` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04f8.c` |
| ov001 `0x020a04fc` | `gFieldEntryPoolManager` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a04fc.c` |
| ov001 `0x020a0500` | `gActorSceneManager` | 4 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a0500.c` |
| ov001 `0x020a0504` | `gModelDictionaryNameScratch` | 16 bytes | `src/overlays/ov001/data/bss/Bss_ov001_020a0500.c` |

## Contracts and lifetime

### `gFieldSessionWork` (0x020a0480)

Pointer to the running field-session task work. StartFieldSession stores GetRunningTaskWork(); session flags, saved placement, scene callbacks and owned buffers are reached through it.

Task-owned work. ShutdownFieldSession releases subordinate buffers/tasks/services, then clears this pointer; the global does not own a separate heap allocation.

The many local FieldSession views are partial and not interchangeable complete structure definitions.

Evidence: `src/overlays/ov001/calls/StartFieldSession.c`, `src/overlays/ov001/calls/ShutdownFieldSession.c`, `src/overlays/ov001/calls/GetFieldSessionState.c`.

### `gFieldEffectPool` (0x020a0484)

Pointer to the field effect pool containing effect/orb slots, nested slot data and the persistent actor slot. EnsureFieldEffectPool allocates and clears 0x3694 bytes when absent.

Heap-owned pool, allocated on demand; DestroyFieldEffectPool releases associated resources, frees the pool and clears the global.

A pool owner is established; individual effect IDs and all internal fields are not renamed by this block.

Evidence: `src/overlays/ov001/calls/EnsureFieldEffectPool.c`, `src/overlays/ov001/calls/DestroyFieldEffectPool.c`, `src/overlays/ov001/calls/FindFreeEffectSlot.c`, `src/overlays/ov001/calls/ReleaseFieldEffectSlot.c`.

### `gSubScene9Work` (0x020a0488)

Pointer to the task work used by the subscene-9 state/tween callbacks. Its constructor stores the current work pointer, sets byte 0 to zero and initializes the tween at +8.

Borrowed task work; the destroy callback clears this global.

The numeric subscene identity is retained: no gameplay name is inferred from its state values.

Evidence: `src/overlays/ov001/calls/SubScene9_Create_02066c80.c`, `src/overlays/ov001/calls/ClearSubScene9WorkOnDestroy.c`, `src/overlays/ov001/calls/SubScene9_Request.c`, `src/overlays/ov001/calls/SubScene9_StartFade.c`.

### `gFieldSceneEntryContext` (0x020a048c)

Pointer to the 0x10f4-byte scene-entry context allocated by CreateSceneContext. It owns scene/group/entry resources and current/pending/previous identifiers initialized with -1 sentinels.

Heap-owned context, released by DestroySceneEntryContext, which clears the global.

Existing gSceneEntryContext macro is an alias for this address; descriptive names of every nested record remain outside this change.

Evidence: `src/overlays/ov001/calls/CreateSceneContext.c`, `src/overlays/ov001/calls/DestroySceneEntryContext.c`, `src/overlays/ov001/calls/GetActiveSceneSlot.c`, `src/overlays/ov001/calls/FindRecordGroupByEntryId.c`.

### `gStageEventContext` (0x020a0490)

Pointer to a cleared 0x138-byte context. Word 0 holds the loaded stage-entry file, +4/+6 hold the pending entry ID and signed kind, and +8 begins the queued stage-event pairs.

Heap-owned context. Destruction resets pending work, releases record slot 4/services, frees word-0 file and the context, then clears the global.

The gStageObjectList header alias exposes a partial view only. Mapped entry IDs and pending kinds do not establish an enemy, price or music owner for the whole allocation.

Evidence: `src/overlays/ov001/calls/CreateStageDataAndStart.c`, `src/overlays/ov001/calls/DestroyStageEventContext.c`, `src/overlays/ov001/calls/GetLoadedStageEntryFile.c`, `src/overlays/ov001/calls/TriggerQueuedStageEventPairs.c`.

### `gSessionTimerWork` (0x020a0494)

Pointer to timer task work, cleared for 0x2c bytes in SubScene9_Create_02068c0c. Elapsed-time getters and counter allocation read this same owner; +0x22 starts at 0x1000.

Borrowed task work; ClearSessionTimerStatePointer clears the pointer.

The two constructor names containing SubScene9 refer to different task-work owners. This is the timer owner at 020a0494, not the state/tween owner at 020a0488.

Evidence: `src/overlays/ov001/calls/SubScene9_Create_02068c0c.c`, `src/overlays/ov001/calls/ClearSessionTimerStatePointer.c`, `src/overlays/ov001/calls/GetSessionElapsedMilliseconds.c`, `src/overlays/ov001/calls/AllocateFieldTimerCounter.c`.

### `gFieldTaskManagerWork` (0x020a0498)

Pointer to task-manager work. InitEventTriggerScene uses current task work, clears 0x38 bytes and allocates the subordinate queue block stored at +0x34. Node creation/release and low/high-ID groups use it.

Borrowed task work with an owned queue allocation; ReleaseFieldTaskManagerWork releases nodes, frees the +0x34 block and clears the global.

The node ID partition is observed; no event meaning is assigned to arbitrary IDs.

Evidence: `src/overlays/ov001/calls/InitEventTriggerScene.c`, `src/overlays/ov001/calls/CreateFieldTaskNode.c`, `src/overlays/ov001/calls/ReleaseAllTaskNodes.c`, `src/overlays/ov001/calls/ReleaseFieldTaskManagerWork.c`.

### `gFieldOffsetTableHolder` (0x020a049c)

Pointer to a four-byte heap holder containing the loaded im resource. LoadOffsetTableFile rebases its counted file-relative offsets; PlayWeightedRandomEntry consumes records through the holder.

Both holder and loaded file are owned heap allocations. ReleaseOffsetTableFile frees both if present and clears the global.

Offset-table and weighted-selection behavior are established; the original asset format name and every record field are not.

Evidence: `src/overlays/ov001/calls/LoadOffsetTableFile.c`, `src/overlays/ov001/calls/ReleaseOffsetTableFile.c`, `src/overlays/ov001/calls/PlayWeightedRandomEntry.c`.

### `gFieldScreenTransitionWork` (0x020a04a0)

Pointer to screen-transition task work, cleared for 0x68 bytes. Mode/flag callbacks, brightness fades, iris and centered-screen resource work all use it.

Borrowed task work; destruction releases its sprite resource at +0x30 and archive at +0x60, then clears the pointer.

Screen-mode numeric values retain their observed values; fields privately labeled x/y can carry brightness rather than geometry.

Evidence: `src/overlays/ov001/calls/InitScreenFadeContext.c`, `src/overlays/ov001/calls/BeginFieldScreenModeTransition.c`, `src/overlays/ov001/calls/StepBrightnessFade.c`, `src/overlays/ov001/calls/ReleaseFieldScreenTransitionWork.c`.

### `gFieldTargetSelectionWork` (0x020a04a4)

Pointer to target-selection task work. InitSceneWork initializes its target reference, selected index -1, target-range values and paired cursor resources; nearest/side-target scans use the same work.

Borrowed task work with acquired sprite resources; ShutdownSceneWork releases the two resource groups, removes its callback and clears the global.

Target providers return borrowed references/positions. No ownership transfer of target objects is established by selection.

Evidence: `src/overlays/ov001/calls/InitSceneWork.c`, `src/overlays/ov001/calls/ResolveSelectedTargetPosition.c`, `src/overlays/ov001/calls/ScanObjectsForNearestTarget.c`, `src/overlays/ov001/calls/ShutdownSceneWork.c`.

### `gSessionCallbackTaskHandle` (0x020a04a8)

Physical four-byte task handle at the base of the legacy session-callback view. CreateSessionTask stores CreateTaskObject(gSessionTaskClassDescriptor, NULL) here.

The task handle occupies +0; the callback list occupies the separate symbol at +4. Callback entries are allocated individually by RegisterSessionCallback.

Several translation units declare a combined 16-byte SessionState at this base. Preserve their existing declarations and offsets; renaming does not make the four-byte BSS definition a complete SessionState.

Evidence: `src/overlays/ov001/calls/CreateSessionTask.c`, `src/overlays/ov001/calls/InitSessionCallbackList.c`, `src/overlays/ov001/calls/RunSessionCallbacks.c`, `src/overlays/ov001/calls/RegisterSessionCallback.c`.

### `gSessionCallbackListStorage` (0x020a04ac)

Physical 12-byte NNSFndList storage immediately after the session-callback task handle. InitSessionCallbackList initializes base 020a04a8 +4 with link offset 4; callback append and traversal use that list.

Static list header; list entries are separate allocations, not inline elements of this BSS array.

It has no direct named call-site reference because current declarations reach it as the preceding global's callbackList member. The address and storage boundary are independent identities and must remain separate.

Evidence: `src/overlays/ov001/calls/InitSessionCallbackList.c`, `src/overlays/ov001/calls/RegisterSessionCallback.c`, `src/overlays/ov001/calls/RunSessionCallbacks.c`.

### `gFieldMessageSpriteManager` (0x020a04b8)

Pointer to the 0xa4-byte manager containing a control word, one common 0x28-byte animated message-sprite set and three localized sets. InitMessageLoaders loads ba/ef/info and language resources; RefreshMenuWindows updates those four sets.

Heap allocation created on demand; destructor releases channel/set resources, frees the manager and clears the global.

Legacy function/type labels use loader, channel and probe for the same owner. Its state bytes describe active animation/scroll selection, not proven asynchronous I/O readiness.

Evidence: `src/overlays/ov001/calls/EnsureFieldMessageLoaderManager.c`, `src/overlays/ov001/calls/InitMessageLoaders.c`, `src/overlays/ov001/calls/RefreshMenuWindows.c`, `src/overlays/ov001/calls/DestroyFieldMessageLoaderManager.c`.

### `gManagedActorGlobals` (0x020a04bc)

Two physical words: +0 points to the managed party-actor task work; +4 stores the current overlay-object factory callback. InitPartyState clears/loads the factory and invokes it for each managed entry.

The first word borrows task work; managed actors/resources are released by their paired cleanup path. ReleaseEventContextWork clears the first word. The factory remains a separate stored callback word.

Do not change this definition into a single pointer. Some consumers intentionally declare only its first-word view; factory signatures are still legacy declarations in places.

Evidence: `src/overlays/ov001/calls/CreatePartyState.c`, `src/overlays/ov001/calls/InitPartyState.c`, `src/overlays/ov001/calls/SetOverlayObjectFactory.c`, `src/overlays/ov001/calls/ReleaseEventContextWork.c`.

### `gFieldSceneGlobals` (0x020a04c4)

Two physical words: active/control word at +0 and field-scene task-work pointer at +4. InitFieldManager assigns both, clears 0x1358 bytes of scene work and creates HUD/text resources.

Scene work belongs to the task; ShutdownFieldScene releases its subordinate resources and sets the +4 pointer to NULL.

The first word is not part of the scene allocation. This block preserves its existing active/control semantics without inventing a broader enum.

Evidence: `src/overlays/ov001/calls/InitFieldManager.c`, `src/overlays/ov001/calls/GetFieldSceneManager.c`, `src/overlays/ov001/calls/ShutdownFieldScene.c`.

### `gFieldHudGaugeState` (0x020a04cc)

Pointer to the HUD gauge task work. CreateTimedSceneState clears the work, loads gauge resources and initializes timers and five tag records; gauge-range/value and counter updates use it.

Borrowed task work with owned subordinate gauge/tag resources; the paired destructor releases resources and clears the pointer.

Gauge records, current/maximum values and FX12 animation values retain their separate widths and units.

Evidence: `src/overlays/ov001/calls/CreateTimedSceneState.c`, `src/overlays/ov001/calls/SetHudGaugeRange.c`, `src/overlays/ov001/calls/UpdateHudGauges.c`, `src/overlays/ov001/calls/DestroyFieldHudGaugeState.c`.

### `gFieldCommandMenuGlobals` (0x020a04d0)

Three physical words: menu state/control, field command-menu task-work pointer, and the currently selected three-colour palette pointer. InitFieldMenu stores work at +4; UpdateFieldMenuPalette stores a palette pointer at +8.

Task work at +4 is borrowed; its entries/layout/object lists are released by DestroyFieldMenu, which clears the menu pointer. Palette pointers borrow static or adjacent fade storage.

The legacy FieldMenuPaletteHandleView extends beyond this 12-byte symbol. Its fade[3] begins at the distinct symbol 020a04dc; do not merge or enlarge either definition.

Evidence: `src/overlays/ov001/calls/InitFieldMenu.c`, `src/overlays/ov001/calls/DestroyFieldMenu.c`, `src/overlays/ov001/calls/UpdateFieldMenuPalette.c`.

### `gFieldMenuFadePalette` (0x020a04dc)

Eight-byte physical storage beginning at command-menu base +0x0c. UpdateFieldMenuPalette writes three RGB555 u16 colours there and queues exactly six bytes to menu palette destinations 0x138 and 0x158.

Static storage, borrowed by the palette pointer at command-menu base +8. No heap ownership.

Only the first six bytes are observed as three palette colours; the last two bytes are padding/otherwise uncharacterized. Access is through a neighboring symbol's extended view, not a direct reference to this symbol.

Evidence: `src/overlays/ov001/calls/UpdateFieldMenuPalette.c`.

### `gMessageWindowWork` (0x020a04e4)

Pointer to the message/mode window task work, cleared for 0xfc bytes by InitModeHandlerContext. Text paging, message layers, scrolling, fades and active-mode callbacks use it.

Borrowed task work. ReleaseMessageWindowWork releases the optional scene-list object and archive at +0xd0, then clears this pointer.

The same window work supports several modes. This name does not identify a particular dialogue character or message owner.

Evidence: `src/overlays/ov001/calls/InitModeHandlerContext.c`, `src/overlays/ov001/calls/UpdateMessageWindow.c`, `src/overlays/ov001/calls/DrawMessageWindowPage.c`, `src/overlays/ov001/calls/ReleaseMessageWindowWork.c`.

### `gSubscenePanelWork` (0x020a04e8)

Pointer to the 0x114-byte field subscene-panel work. Initialization captures panel options, loads names/messages, obtains four graphics records through ov025 and starts the subscene-overlay load.

Borrowed task work; release unloads/destroys the subscene task, releases buffers and graphics, restores display setting, then clears the pointer.

Loaded mode, panel phase and formation type remain different fields; they are not interchangeable scene IDs.

Evidence: `src/overlays/ov001/calls/InitFieldPanelScene.c`, `src/overlays/ov001/calls/UpdatePanelScene.c`, `src/overlays/ov001/calls/GetLoadedSubsceneMode.c`, `src/overlays/ov001/calls/ReleaseSubscenePanelWork.c`.

### `gCounterHudWork` (0x020a04ec)

Pointer to the 0x910-byte counter-HUD task work. Initialization clears it and loads adnum/w resources; digit, countdown, layout and fade callbacks share it.

Borrowed task work. ReleaseCounterHudWork releases both resource groups and clears the pointer.

The embedded layout and digit resources are subordinate owners; the BSS word is only their task-work reference.

Evidence: `src/overlays/ov001/calls/InitCounterHudWork.c`, `src/overlays/ov001/calls/UpdateAndDrawCounterHud.c`, `src/overlays/ov001/calls/GetCounterHudFadeState.c`, `src/overlays/ov001/calls/ReleaseCounterHudWork.c`.

### `gArrowPromptWork` (0x020a04f0)

Pointer to the 0x4c-byte arrow-prompt work. Initialization loads graphics, allocates two 0x20-byte buffers and copies the source palette/graphics slices into them. Prompt, D-pad and timed-counter callbacks use it.

Borrowed task work with subordinate allocations; release frees buffers at +0x30/+0x34/+0x38 and clears the pointer.

The +0x38 allocation is released here but is not created by the initializer alone; do not imply all three buffers are always allocated during construction.

Evidence: `src/overlays/ov001/calls/InitArrowPromptWork.c`, `src/overlays/ov001/calls/OpenArrowPrompt.c`, `src/overlays/ov001/calls/ArrowPrompt_HandleDpad.c`, `src/overlays/ov001/calls/ReleaseArrowPromptWork.c`.

### `gFieldMinigameWork` (0x020a04f4)

Pointer to task work selected by InitContextForMode: mode 1 initializes falling pieces, modes 2/3 initialize spinning prompts; round-active, start and stop callbacks use the same work.

Borrowed task work. The constructor stores the pointer; an independent clear/free of this global is not established by the reviewed callbacks.

No heap ownership or automatic pointer clearing is claimed. Mode 0 returns a NULL update, and numeric modes are retained.

Evidence: `src/overlays/ov001/calls/InitContextForMode.c`, `src/overlays/ov001/calls/StartFieldMinigameRound.c`, `src/overlays/ov001/calls/StopFieldMinigameRound.c`, `src/overlays/ov001/calls/DispatchByContextMode.c`.

### `gFieldObjectClassManager` (0x020a04f8)

Pointer to the 0x124-byte field-object class manager. Construction registers script group 4 and loads shared object/shadow resources; class-table and class-list consumers use it.

Heap-owned manager. Destruction releases the separate entry-pool manager, class instances, archive/buffer/table and this allocation, clears the pointer and unregisters group 4.

This is the FieldObjectClass family with object class at +8; it is distinct from the entry-pool manager at 020a04fc and its operations table.

Evidence: `src/overlays/ov001/calls/CreateFieldObjectManager.c`, `src/overlays/ov001/calls/GetFieldObjectClassAtIndex.c`, `src/overlays/ov001/calls/UpdateFieldObjectStates.c`, `src/overlays/ov001/calls/DestroyFieldObjectManager.c`.

### `gFieldEntryPoolManager` (0x020a04fc)

Pointer to the 0x1c8-byte field-entry pool/resource manager. CreateRecordViewer allocates/clears it and caches record-table E; pool registration, active-entry lists, resource queues and unlock rewards use it.

Heap-owned manager. Destruction shuts down entries, frees eight subordinate resource buffers and the manager, then clears the pointer.

The constructor's legacy RecordViewer label does not describe all consumers. Pool count, active-list count and selected IDs have different fields and widths.

Evidence: `src/overlays/ov001/calls/CreateRecordViewer.c`, `src/overlays/ov001/calls/RegisterFieldEntryPool.c`, `src/overlays/ov001/calls/GetActiveFieldEntryListCount.c`, `src/overlays/ov001/calls/StepResourceSlotLoading.c`, `src/overlays/ov001/calls/DestroyFieldEntryPoolManager.c`.

### `gActorSceneManager` (0x020a0500)

Pointer to actor-scene task work. InitOverlayObjectSystem clears 0x3f20 bytes, registers actor script group 1, allocates the script-VM buffer at +0x140 and creates the root actor-channel task.

Borrowed task work with script-buffer and child-task ownership. Shutdown releases the VM buffer, unregisters group 1, destroys the root task and clears the global.

This pointer is distinct from the current actor-channel context at 020a0514. Script-buffer contents and callbacks do not change ownership by being read here.

Evidence: `src/overlays/ov001/calls/InitOverlayObjectSystem.c`, `src/overlays/ov001/calls/ActorManager_StartScene.c`, `src/overlays/ov001/calls/RunEventScriptFrame.c`, `src/overlays/ov001/calls/ShutdownOverlayObjectSystem.c`.

### `gModelDictionaryNameScratch` (0x020a0504)

Static 16-byte model-dictionary name scratch. FindModelResourceIndexByName clears all 16 bytes, copies the caller name and passes it to NNS_G3dGetResDictIdxByName for the model dictionary at +0x40.

Shared mutable static scratch; no allocation or free. The helper returns an index or -1.

The current strcpy is unbounded; this naming block does not alter behavior or claim an enforced input-length check. Symbol 020a0505 is an interior +1 alias, retained separately without inventing a second allocation.

Evidence: `src/overlays/ov001/calls/FindModelResourceIndexByName.c`.

## Storage boundaries to preserve

The callback task handle at `020a04a8` and the 12-byte callback-list header at `020a04ac` are separate configured BSS identities even though callers declare a combined view at the first address. Likewise, the 12-byte command-menu globals at `020a04d0` are followed by an independent eight-byte fade storage symbol at `020a04dc`. The palette helper writes six colour bytes into that neighboring storage. Neither relationship authorizes enlarging, merging or reordering the physical definitions.

The eight-byte managed-actor globals contain both the work pointer and a factory callback. The eight-byte field-scene globals contain a control word and a work pointer. Turning either into a single pointer would omit live storage.

The symbol at `020a0505` remains unnamed: it is an interior address in the 16-byte model-name scratch at `020a0504`, with no independent owner established. Its configured identity must be retained until relocation evidence supports representing it explicitly as an offset alias.

## Scope of the names

Names are derived from construction, use and cleanup of the EU owner, not from an address-matched US label. Existing pointer/integer declarations and callback prototypes remain legacy interfaces where they have not been repaired separately. This document records demonstrated ownership and accessed fields without asserting complete native structure definitions.


## Byte-exact validation

27 DATA identities retain their source paths, native sizes and storage.
768/777 affected official function checks pass; the remaining
9 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 801 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
