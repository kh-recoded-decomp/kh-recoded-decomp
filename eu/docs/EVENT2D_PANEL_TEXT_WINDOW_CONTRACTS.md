# Event2D panels and text-window services

This document records 58 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

The Event2D scene, text-window task and text-window controller are distinct TaskObject work owners. Their constructors obtain current task work; release callbacks free their child allocations but do not free the TaskObject-owned work. Creation/destruction adapters operate on task handles, which differ from work pointers.

## Event2D scene and panel ScriptVm

The Event2D constructor allocates exactly two screen layers, eight 0x9c-byte actor slots and five scene-model actors. Those capacities apply to this owner only. Actor-slot movement, shake and alpha-fade bits 1, 2 and 4 are stepped independently. Shake uses the saved base positions, amplitude and decay divisor; the divisor is not a destination coordinate. Slot release frees its resource/graphics data, clears the record and restores -1 sentinels at +0x8c/+0x94/+0x98.

The panel uses the field/panel ScriptVm command protocol: return 1 advances the command; return 0 schedules its paired resume callback. This is different from overlay021's stage interpreter result codes. Operand reads retain their left-to-right order. Screen-layer zoom still evaluates all three operands during skip, although it suppresses the actual zoom operation when the VM's skipRequested word at +0x628 is nonzero.

The panel VM is embedded in the exact Event2D/panel owner, not arbitrary actors with coincident offsets. The sound-wait command returns zero; its resume predicate completes on VM skipRequested or when the global sound-work byte +0xb472e is no longer 4. It initializes no resource and assigns no narrative meaning to sound state 4. The close-windows run command already returns 1; its constant-1 resume callback remains a separate paired fallback.

Session callback slot 7 grants scene consent with literal 1, while aggregate session conditions can still block advancement. It is separate from slot 1 startup readiness. The controller readiness hook currently returns literal 1, so the scene wait records that actual implementation rather than claiming asynchronous work completion.

## Text windows, resources and graphics

The text task maintains three 0x110-byte windows. Window state is the word at +8; every state assignment clears the secondary counter at +0x10. The old duration/TimerNode labels are misleading. Empty state 0 and state 7 callbacks are intentional table entries; finished-page advancement explicitly moves state-7 windows to state 8 or 13. State 13 waits for primary state 9 before disabling two sprite records and entering state 9.

Flags at window +0x0c use the shared bit-array convention, index bit `31 - (index & 31)`, rather than a raw 1<<index API. The sound-7 helper sets a cooldown of 2 only when zero; the text update decrements it once per unpaused update. No input-action label or wall-clock duration is inferred.

Background loading pairs an archive allocation with a message-container handle; the release helper frees/clears the archive and releases the handle. Both `eu10.nftr` and `jp10.nftr` font resources are loaded in EU, at owner +0x644c and +0x68a8, and released in reverse order. The language filename is not evidence that the second font is dead data.

Per-window graphics release can free a text buffer, release active canvas/display records, clear its active bit and clear BG2/BG3 tilemap contents; the window itself remains allocated. For kinds 0 or 4, a shared pointed word is cleared after buffer release. Display-list release, queued update and five-record sprite release are distinct operations. The sprite release restores record indices to -1.

Character-upload table entries 0..7 select MAIN BG0..3 then SUB BG0..3 and use the pointer at owner +0x14. Screen-upload entries use the embedded address at owner +0x0c. Both forward their two remaining loader arguments and add no index check. The distinction between a pointed resource and an embedded upload descriptor must survive a port.

The controller installs open/update/close panel callbacks and creates the text task. Opening backs up MAIN BG2/BG3 maps, characters, palette and window masks before opening the requested panel, and returns literal 1. Its registered update invokes prompt input and returns 1. The close adapter closes all three windows and clears history; the finished-window adapter advances waiting windows and adjusts name-record visibility. The four-word wait-state tail at Event2D +0x10ec is cleared after completion/skip, but individual word meanings remain unproven.

`FormatPanelWideText` returns its destination after bounded wide formatting. Its matched va_list construction follows 32-bit stack slots; a host port must use that platform's stdarg ABI rather than copy native pointer arithmetic. The choice-result adapter forwards the owner getter's word at +0x68a0; its private pointer-return label does not prove allocation or ownership.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov036:020ba914` | ARM | `func_ov036_020ba914` | `PanelSceneState_WaitControllerReady` | [eu/src/overlays/ov036/calls/PanelSceneState_WaitControllerReady.c](../src/overlays/ov036/calls/PanelSceneState_WaitControllerReady.c) |
| `ov036:020bb2a4` | ARM | `func_ov036_020bb2a4` | `UpdateEvent2DSceneObjects` | [eu/src/overlays/ov036/calls/UpdateEvent2DSceneObjects.c](../src/overlays/ov036/calls/UpdateEvent2DSceneObjects.c) |
| `ov036:020bb564` | ARM | `func_ov036_020bb564` | `UpdateEvent2DActorSlot` | [eu/src/overlays/ov036/calls/UpdateEvent2DActorSlot.c](../src/overlays/ov036/calls/UpdateEvent2DActorSlot.c) |
| `ov036:020bb8ec` | ARM | `func_ov036_020bb8ec` | `GetActorSlotOffscreenY` | [eu/src/overlays/ov036/calls/GetActorSlotOffscreenY.c](../src/overlays/ov036/calls/GetActorSlotOffscreenY.c) |
| `ov036:020bc3a4` | ARM | `func_ov036_020bc3a4` | `CreateEvent2DPanelTask` | [eu/src/overlays/ov036/calls/CreateEvent2DPanelTask.c](../src/overlays/ov036/calls/CreateEvent2DPanelTask.c) |
| `ov036:020bc4c0` | ARM | `func_ov036_020bc4c0` | `CanEvent2DSceneAdvanceSession` | [eu/src/overlays/ov036/auto/CanEvent2DSceneAdvanceSession.c](../src/overlays/ov036/auto/CanEvent2DSceneAdvanceSession.c) |
| `ov036:020bc8c8` | ARM | `func_ov036_020bc8c8` | `SlideEvent2DActorSlotsOffscreen` | [eu/src/overlays/ov036/calls/SlideEvent2DActorSlotsOffscreen.c](../src/overlays/ov036/calls/SlideEvent2DActorSlotsOffscreen.c) |
| `ov036:020bce7c` | ARM | `func_ov036_020bce7c` | `StartActorSlotShake` | [eu/src/overlays/ov036/calls/StartActorSlotShake.c](../src/overlays/ov036/calls/StartActorSlotShake.c) |
| `ov036:020bd090` | ARM | `func_ov036_020bd090` | `ReleaseEvent2DActorSlot` | [eu/src/overlays/ov036/calls/ReleaseEvent2DActorSlot.c](../src/overlays/ov036/calls/ReleaseEvent2DActorSlot.c) |
| `ov036:020bda00` | ARM | `func_ov036_020bda00` | `ClearPanelWindowWaitState` | [eu/src/overlays/ov036/calls/ClearPanelWindowWaitState.c](../src/overlays/ov036/calls/ClearPanelWindowWaitState.c) |
| `ov036:020bdd08` | THUMB | `func_ov036_020bdd08` | `PanelScriptCmd_SetSlotSharedRecord` | [eu/src/overlays/ov036/calls/PanelScriptCmd_SetSlotSharedRecord.c](../src/overlays/ov036/calls/PanelScriptCmd_SetSlotSharedRecord.c) |
| `ov036:020bdd10` | THUMB | `func_ov036_020bdd10` | `PanelScriptCmd_MoveActorSlotX` | [eu/src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotX.c](../src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotX.c) |
| `ov036:020bdd50` | THUMB | `func_ov036_020bdd50` | `PanelScriptCmd_StartActorSlotShake` | [eu/src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotShake.c](../src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotShake.c) |
| `ov036:020bdd74` | THUMB | `func_ov036_020bdd74` | `PanelScriptCmd_ToggleActorSlotFlip` | [eu/src/overlays/ov036/calls/PanelScriptCmd_ToggleActorSlotFlip.c](../src/overlays/ov036/calls/PanelScriptCmd_ToggleActorSlotFlip.c) |
| `ov036:020bdd84` | THUMB | `func_ov036_020bdd84` | `PanelScriptCmd_StartActorFocusTransition` | [eu/src/overlays/ov036/calls/PanelScriptCmd_StartActorFocusTransition.c](../src/overlays/ov036/calls/PanelScriptCmd_StartActorFocusTransition.c) |
| `ov036:020be098` | THUMB | `func_ov036_020be098` | `PanelScriptCmd_CloseAllTextWindows` | [eu/src/overlays/ov036/calls/PanelScriptCmd_CloseAllTextWindows.c](../src/overlays/ov036/calls/PanelScriptCmd_CloseAllTextWindows.c) |
| `ov036:020be0a4` | THUMB | `func_ov036_020be0a4` | `PanelScriptResume_CloseTextWindowsDone` | [eu/src/overlays/ov036/auto/PanelScriptResume_CloseTextWindowsDone.c](../src/overlays/ov036/auto/PanelScriptResume_CloseTextWindowsDone.c) |
| `ov036:020be0a8` | THUMB | `func_ov036_020be0a8` | `PanelScriptCmd_SetScreenLayerImage` | [eu/src/overlays/ov036/calls/PanelScriptCmd_SetScreenLayerImage.c](../src/overlays/ov036/calls/PanelScriptCmd_SetScreenLayerImage.c) |
| `ov036:020be14c` | THUMB | `func_ov036_020be14c` | `PanelScriptCmd_SetActorSlotPriority` | [eu/src/overlays/ov036/calls/PanelScriptCmd_SetActorSlotPriority.c](../src/overlays/ov036/calls/PanelScriptCmd_SetActorSlotPriority.c) |
| `ov036:020be170` | THUMB | `func_ov036_020be170` | `PanelScriptCmd_StartActorSlotAlphaFade` | [eu/src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotAlphaFade.c](../src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotAlphaFade.c) |
| `ov036:020be1b0` | THUMB | `func_ov036_020be1b0` | `PanelScriptCmd_ReleaseActorSlot` | [eu/src/overlays/ov036/calls/PanelScriptCmd_ReleaseActorSlot.c](../src/overlays/ov036/calls/PanelScriptCmd_ReleaseActorSlot.c) |
| `ov036:020be1c0` | THUMB | `func_ov036_020be1c0` | `PanelScriptCmd_MoveActorSlotY` | [eu/src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotY.c](../src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotY.c) |
| `ov036:020be2f4` | THUMB | `func_ov036_020be2f4` | `FormatPanelWideText` | [eu/src/overlays/ov036/calls/FormatPanelWideText.c](../src/overlays/ov036/calls/FormatPanelWideText.c) |
| `ov036:020be4ec` | THUMB | `func_ov036_020be4ec` | `PanelScriptCmd_StartScreenLayerScroll` | [eu/src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerScroll.c](../src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerScroll.c) |
| `ov036:020be57c` | THUMB | `func_ov036_020be57c` | `PanelScriptResume_LoadEntityModel` | [eu/src/overlays/ov036/calls/PanelScriptResume_LoadEntityModel.c](../src/overlays/ov036/calls/PanelScriptResume_LoadEntityModel.c) |
| `ov036:020be628` | THUMB | `func_ov036_020be628` | `PanelScriptCmd_ReleaseModelSlot` | [eu/src/overlays/ov036/calls/PanelScriptCmd_ReleaseModelSlot.c](../src/overlays/ov036/calls/PanelScriptCmd_ReleaseModelSlot.c) |
| `ov036:020be67c` | THUMB | `func_ov036_020be67c` | `PanelScriptCmd_StartScreenLayerZoom` | [eu/src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerZoom.c](../src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerZoom.c) |
| `ov036:020be78c` | THUMB | `func_ov036_020be78c` | `PanelScriptCmd_BeginWaitSoundState4Clear` | [eu/src/overlays/ov036/auto/PanelScriptCmd_BeginWaitSoundState4Clear.c](../src/overlays/ov036/auto/PanelScriptCmd_BeginWaitSoundState4Clear.c) |
| `ov036:020be790` | THUMB | `IsResourceReadyOrInitialize_020be790` | `IsPanelScriptSoundWaitComplete` | [eu/src/overlays/ov036/calls/IsPanelScriptSoundWaitComplete.c](../src/overlays/ov036/calls/IsPanelScriptSoundWaitComplete.c) |
| `ov036:020be858` | ARM | `func_ov036_020be858` | `InitTextWindowTask` | [eu/src/overlays/ov036/calls/InitTextWindowTask.c](../src/overlays/ov036/calls/InitTextWindowTask.c) |
| `ov036:020be914` | ARM | `func_ov036_020be914` | `DestroyTextWindowTask` | [eu/src/overlays/ov036/calls/DestroyTextWindowTask.c](../src/overlays/ov036/calls/DestroyTextWindowTask.c) |
| `ov036:020beb3c` | ARM | `func_ov036_020beb3c` | `ReleaseTextWindowBackground` | [eu/src/overlays/ov036/calls/ReleaseTextWindowBackground.c](../src/overlays/ov036/calls/ReleaseTextWindowBackground.c) |
| `ov036:020beb7c` | ARM | `func_ov036_020beb7c` | `LoadTextWindowFonts` | [eu/src/overlays/ov036/calls/LoadTextWindowFonts.c](../src/overlays/ov036/calls/LoadTextWindowFonts.c) |
| `ov036:020bebbc` | ARM | `func_ov036_020bebbc` | `ReleaseTextWindowFonts` | [eu/src/overlays/ov036/calls/ReleaseTextWindowFonts.c](../src/overlays/ov036/calls/ReleaseTextWindowFonts.c) |
| `ov036:020bee60` | ARM | `func_ov036_020bee60` | `ReleaseTextWindowGraphics` | [eu/src/overlays/ov036/calls/ReleaseTextWindowGraphics.c](../src/overlays/ov036/calls/ReleaseTextWindowGraphics.c) |
| `ov036:020bf4f4` | ARM | `func_ov036_020bf4f4` | `ReleaseTextWindowDisplayList` | [eu/src/overlays/ov036/calls/ReleaseTextWindowDisplayList.c](../src/overlays/ov036/calls/ReleaseTextWindowDisplayList.c) |
| `ov036:020bf620` | ARM | `func_ov036_020bf620` | `UpdateTextWindowDisplayList` | [eu/src/overlays/ov036/calls/UpdateTextWindowDisplayList.c](../src/overlays/ov036/calls/UpdateTextWindowDisplayList.c) |
| `ov036:020bf63c` | ARM | `func_ov036_020bf63c` | `ReleaseTextWindowSpriteRecords` | [eu/src/overlays/ov036/calls/ReleaseTextWindowSpriteRecords.c](../src/overlays/ov036/calls/ReleaseTextWindowSpriteRecords.c) |
| `ov036:020bf690` | ARM | `func_ov036_020bf690` | `UploadTextWindowBgCharacters` | [eu/src/overlays/ov036/calls/UploadTextWindowBgCharacters.c](../src/overlays/ov036/calls/UploadTextWindowBgCharacters.c) |
| `ov036:020bf6b8` | ARM | `func_ov036_020bf6b8` | `UploadTextWindowBgScreen` | [eu/src/overlays/ov036/calls/UploadTextWindowBgScreen.c](../src/overlays/ov036/calls/UploadTextWindowBgScreen.c) |
| `ov036:020bf6dc` | ARM | `func_ov036_020bf6dc` | `TextWindowState_IdleNoOp` | [eu/src/overlays/ov036/auto/TextWindowState_IdleNoOp.c](../src/overlays/ov036/auto/TextWindowState_IdleNoOp.c) |
| `ov036:020c0e30` | ARM | `func_ov036_020c0e30` | `TextWindowState_WaitPageAdvanceNoOp` | [eu/src/overlays/ov036/auto/TextWindowState_WaitPageAdvanceNoOp.c](../src/overlays/ov036/auto/TextWindowState_WaitPageAdvanceNoOp.c) |
| `ov036:020c1d48` | ARM | `func_ov036_020c1d48` | `TextWindowState_WaitPrimaryFadeOut` | [eu/src/overlays/ov036/calls/TextWindowState_WaitPrimaryFadeOut.c](../src/overlays/ov036/calls/TextWindowState_WaitPrimaryFadeOut.c) |
| `ov036:020c27dc` | ARM | `func_ov036_020c27dc` | `SetTextWindowFlag` | [eu/src/overlays/ov036/calls/SetTextWindowFlag.c](../src/overlays/ov036/calls/SetTextWindowFlag.c) |
| `ov036:020c27ec` | ARM | `func_ov036_020c27ec` | `ClearTextWindowFlag` | [eu/src/overlays/ov036/calls/ClearTextWindowFlag.c](../src/overlays/ov036/calls/ClearTextWindowFlag.c) |
| `ov036:020c27fc` | ARM | `SetTimerDuration` | `SetTextWindowState` | [eu/src/overlays/ov036/calls/SetTextWindowState.c](../src/overlays/ov036/calls/SetTextWindowState.c) |
| `ov036:020c280c` | ARM | `func_ov036_020c280c` | `GetTextWindowState` | [eu/src/overlays/ov036/auto/GetTextWindowState.c](../src/overlays/ov036/auto/GetTextWindowState.c) |
| `ov036:020c2814` | ARM | `func_ov036_020c2814` | `PlayTextWindowSound7WithCooldown` | [eu/src/overlays/ov036/calls/PlayTextWindowSound7WithCooldown.c](../src/overlays/ov036/calls/PlayTextWindowSound7WithCooldown.c) |
| `ov036:020c2854` | ARM | `func_ov036_020c2854` | `CreateTextWindowTask` | [eu/src/overlays/ov036/calls/CreateTextWindowTask.c](../src/overlays/ov036/calls/CreateTextWindowTask.c) |
| `ov036:020c2884` | ARM | `func_ov036_020c2884` | `DestroyTextWindowTaskHandle` | [eu/src/overlays/ov036/calls/DestroyTextWindowTaskHandle.c](../src/overlays/ov036/calls/DestroyTextWindowTaskHandle.c) |
| `ov036:020c2d68` | ARM | `func_ov036_020c2d68` | `InitTextWindowControllerTask` | [eu/src/overlays/ov036/calls/InitTextWindowControllerTask.c](../src/overlays/ov036/calls/InitTextWindowControllerTask.c) |
| `ov036:020c2e10` | ARM | `func_ov036_020c2e10` | `UpdateTextWindowControllerNoOp` | [eu/src/overlays/ov036/auto/UpdateTextWindowControllerNoOp.c](../src/overlays/ov036/auto/UpdateTextWindowControllerNoOp.c) |
| `ov036:020c2f24` | ARM | `func_ov036_020c2f24` | `IsTextWindowControllerReady` | [eu/src/overlays/ov036/auto/IsTextWindowControllerReady.c](../src/overlays/ov036/auto/IsTextWindowControllerReady.c) |
| `ov036:020c30f8` | ARM | `func_ov036_020c30f8` | `GetPanelTextWindowChoiceResult` | [eu/src/overlays/ov036/calls/GetPanelTextWindowChoiceResult.c](../src/overlays/ov036/calls/GetPanelTextWindowChoiceResult.c) |
| `ov036:020c32bc` | ARM | `func_ov036_020c32bc` | `OpenTextPanelWithGraphicsBackup` | [eu/src/overlays/ov036/calls/OpenTextPanelWithGraphicsBackup.c](../src/overlays/ov036/calls/OpenTextPanelWithGraphicsBackup.c) |
| `ov036:020c32e4` | ARM | `func_ov036_020c32e4` | `UpdateTextPanelPromptCallback` | [eu/libs/nitro/fs/calls/UpdateTextPanelPromptCallback.c](../libs/nitro/fs/calls/UpdateTextPanelPromptCallback.c) |
| `ov036:020c3368` | ARM | `func_ov036_020c3368` | `ClosePanelTextWindows` | [eu/src/overlays/ov036/calls/ClosePanelTextWindows.c](../src/overlays/ov036/calls/ClosePanelTextWindows.c) |
| `ov036:020c3374` | ARM | `func_ov036_020c3374` | `AdvancePanelFinishedTextWindows` | [eu/src/overlays/ov036/calls/AdvancePanelFinishedTextWindows.c](../src/overlays/ov036/calls/AdvancePanelFinishedTextWindows.c) |

## PanelSceneState_WaitControllerReady

Identity: `ov036:020ba914`, ARM, native extent 52 bytes (including any configured pool). Previous symbol: `func_ov036_020ba914`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelSceneState_WaitControllerReady.c](../src/overlays/ov036/calls/PanelSceneState_WaitControllerReady.c).

```c
int PanelSceneState_WaitControllerReady(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits for controller readiness; sets immediate dispatch and returns scene state1. Source: [eu/src/overlays/ov036/calls/PanelSceneState_WaitControllerReady.c:1-23](../src/overlays/ov036/calls/PanelSceneState_WaitControllerReady.c).
- Own state dispatcher uses work+8 as state and flag0x8000 for immediate redispatch. Source: [eu/src/overlays/ov036/calls/RunPanelStateMachine.c:1-7](../src/overlays/ov036/calls/RunPanelStateMachine.c).
- Current controller readiness implementation always returns1. Source: [eu/src/overlays/ov036/auto/IsTextWindowControllerReady.c:1-2](../src/overlays/ov036/auto/IsTextWindowControllerReady.c).

## UpdateEvent2DSceneObjects

Identity: `ov036:020bb2a4`, ARM, native extent 420 bytes (including any configured pool). Previous symbol: `func_ov036_020bb2a4`.

EU entrypoint: [eu/src/overlays/ov036/calls/UpdateEvent2DSceneObjects.c](../src/overlays/ov036/calls/UpdateEvent2DSceneObjects.c).

```c
void UpdateEvent2DSceneObjects(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- On exit request advances the slot transition; otherwise updates active screen layers, actor slots, model moves and model animation/blend sequences. Source: [eu/src/overlays/ov036/calls/UpdateEvent2DSceneObjects.c:1-118](../src/overlays/ov036/calls/UpdateEvent2DSceneObjects.c).
- Native constructor allocates exactly two layers, eight actor slots and five scene-model actors for this Event2D owner. Source: [eu/src/overlays/ov036/calls/InitEvent2DPanel.c:1-78](../src/overlays/ov036/calls/InitEvent2DPanel.c).
- Own state dispatcher uses work+8 as state and flag0x8000 for immediate redispatch. Source: [eu/src/overlays/ov036/calls/RunPanelStateMachine.c:1-7](../src/overlays/ov036/calls/RunPanelStateMachine.c).

Contract limits:

- Model count5, actor slot count8, layer count2 are owner-specific. Animation track mask controls sequence progression, not total scene completion.

## UpdateEvent2DActorSlot

Identity: `ov036:020bb564`, ARM, native extent 96 bytes (including any configured pool). Previous symbol: `func_ov036_020bb564`.

EU entrypoint: [eu/src/overlays/ov036/calls/UpdateEvent2DActorSlot.c](../src/overlays/ov036/calls/UpdateEvent2DActorSlot.c).

```c
void UpdateEvent2DActorSlot(int index);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- For selected0x9c slot, independently steps movement, shake and alpha fade according to flags1,2,4. Source: [eu/src/overlays/ov036/calls/UpdateEvent2DActorSlot.c:1-23](../src/overlays/ov036/calls/UpdateEvent2DActorSlot.c).
- Native constructor allocates exactly two layers, eight actor slots and five scene-model actors for this Event2D owner. Source: [eu/src/overlays/ov036/calls/InitEvent2DPanel.c:1-78](../src/overlays/ov036/calls/InitEvent2DPanel.c).

## GetActorSlotOffscreenY

Identity: `ov036:020bb8ec`, ARM, native extent 20 bytes (including any configured pool). Previous symbol: `func_ov036_020bb8ec`.

EU entrypoint: [eu/src/overlays/ov036/calls/GetActorSlotOffscreenY.c](../src/overlays/ov036/calls/GetActorSlotOffscreenY.c).

```c
int GetActorSlotOffscreenY(int blockIndex);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns fx32 Y=(256-height), adding64 pixels for height>192. Source: [eu/src/overlays/ov036/calls/GetActorSlotOffscreenY.c:1-9](../src/overlays/ov036/calls/GetActorSlotOffscreenY.c).
- Uses result as an offscreen endpoint for special start/end Y values. Source: [eu/src/overlays/ov036/calls/MoveActorSlotY.c:1-5](../src/overlays/ov036/calls/MoveActorSlotY.c).
- Native slot height and position roles identify this calculation as offscreen vertical placement. Source: [src/ov036/unclassified_helpers/MoveActorSlotY_020bcd08.c:1-85](../../src/ov036/unclassified_helpers/MoveActorSlotY_020bcd08.c).

Contract limits:

- Does not clamp invalid heights.

## CreateEvent2DPanelTask

Identity: `ov036:020bc3a4`, ARM, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov036_020bc3a4`.

EU entrypoint: [eu/src/overlays/ov036/calls/CreateEvent2DPanelTask.c](../src/overlays/ov036/calls/CreateEvent2DPanelTask.c).

```c
void CreateEvent2DPanelTask(int arg0);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Instantiates the Event2D scene descriptor and stores the TaskObject handle. Source: [eu/src/overlays/ov036/calls/CreateEvent2DPanelTask.c:1-5](../src/overlays/ov036/calls/CreateEvent2DPanelTask.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/reviewed_helpers/func_ov036_020bc384.c:1-7](../../src/ov036/reviewed_helpers/func_ov036_020bc384.c).
- Native constructor allocates exactly two layers, eight actor slots and five scene-model actors for this Event2D owner. Source: [eu/src/overlays/ov036/calls/InitEvent2DPanel.c:1-78](../src/overlays/ov036/calls/InitEvent2DPanel.c).

## CanEvent2DSceneAdvanceSession

Identity: `ov036:020bc4c0`, ARM, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov036_020bc4c0`.

EU entrypoint: [eu/src/overlays/ov036/auto/CanEvent2DSceneAdvanceSession.c](../src/overlays/ov036/auto/CanEvent2DSceneAdvanceSession.c).

```c
u32 CanEvent2DSceneAdvanceSession(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Constant callback returns1. Source: [eu/src/overlays/ov036/auto/CanEvent2DSceneAdvanceSession.c:1-2](../src/overlays/ov036/auto/CanEvent2DSceneAdvanceSession.c).
- Exact constant-return body. Source: [src/ov036/leaf_research/func_ov036_020bc4a0.c:1-5](../../src/ov036/leaf_research/func_ov036_020bc4a0.c).
- Registers this function at callback index7. Source: [eu/src/overlays/ov036/calls/InitPanelCallbackTable.c:1-11](../src/overlays/ov036/calls/InitPanelCallbackTable.c).
- Session progress gate invokes Session+2828 (overlayWork280c+7*4); callback false blocks, then actor-entry flag2 can also block. Source: [eu/src/overlays/ov001/calls/IsSessionScriptEntryReady.c:1-20](../src/overlays/ov001/calls/IsSessionScriptEntryReady.c).
- Only raises session script run flags when aggregate progress gate succeeds. Source: [src/ov001/unclassified_helpers/TryRaiseSessionScriptFlags_02063694.c:1-36](../../src/ov001/unclassified_helpers/TryRaiseSessionScriptFlags_02063694.c).
- Session transition also requires same aggregate gate. Source: [src/ov001/unclassified_helpers/SelectNextSessionState_02062150.c:1-171](../../src/ov001/unclassified_helpers/SelectNextSessionState_02062150.c).

Contract limits:

- Only the scene callback grants consent unconditionally. Other aggregate session conditions may still block progress.
- This is distinct from callback index1 startup readiness.

## SlideEvent2DActorSlotsOffscreen

Identity: `ov036:020bc8c8`, ARM, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov036_020bc8c8`.

EU entrypoint: [eu/src/overlays/ov036/calls/SlideEvent2DActorSlotsOffscreen.c](../src/overlays/ov036/calls/SlideEvent2DActorSlotsOffscreen.c).

```c
void * SlideEvent2DActorSlotsOffscreen();
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Thin adapter forwards to SlideActorSlotsOffscreen. Source: [eu/src/overlays/ov036/calls/SlideEvent2DActorSlotsOffscreen.c:1-3](../src/overlays/ov036/calls/SlideEvent2DActorSlotsOffscreen.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/library_nitro_pxi/PXI_Init_020bc8a8.c:1-5](../../src/ov036/library_nitro_pxi/PXI_Init_020bc8a8.c).
- Exact callee updates the Event2D actor slots. Source: [eu/src/overlays/ov036/calls/SlideActorSlotsOffscreen.c:1-4](../src/overlays/ov036/calls/SlideActorSlotsOffscreen.c).

Additional native ABI observations:

- Shared legacy declaration uses void* return although real callee may be void. Verify actual return consumers before changing ABI.

## StartActorSlotShake

Identity: `ov036:020bce7c`, ARM, native extent 108 bytes (including any configured pool). Previous symbol: `func_ov036_020bce7c`.

EU entrypoint: [eu/src/overlays/ov036/calls/StartActorSlotShake.c](../src/overlays/ov036/calls/StartActorSlotShake.c).

```c
void StartActorSlotShake(unsigned int ownerId,unsigned int target);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Finds owner slot, returns without change if any slot effect is active, then initializes shake amplitude/base coordinates/divisor and enables shake flag2. Source: [eu/src/overlays/ov036/calls/StartActorSlotShake.c:1-24](../src/overlays/ov036/calls/StartActorSlotShake.c).
- Uses+48 offset,+4c amplitude,+50/+54 base positions and+60 decay divisor; clears flag2 when the shake finishes. Source: [eu/src/overlays/ov036/calls/UpdateSpriteShake.c:1-53](../src/overlays/ov036/calls/UpdateSpriteShake.c).

Contract limits:

- Divisor is not a target coordinate and no zero guard is added.

## ReleaseEvent2DActorSlot

Identity: `ov036:020bd090`, ARM, native extent 108 bytes (including any configured pool). Previous symbol: `func_ov036_020bd090`.

EU entrypoint: [eu/src/overlays/ov036/calls/ReleaseEvent2DActorSlot.c](../src/overlays/ov036/calls/ReleaseEvent2DActorSlot.c).

```c
void ReleaseEvent2DActorSlot(int ownerId);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Releases shared/resource slot at+0x74 if present, frees its graphics buffer, clears the0x9c record and restores three -1 sentinels. Source: [eu/src/overlays/ov036/calls/ReleaseEvent2DActorSlot.c:1-27](../src/overlays/ov036/calls/ReleaseEvent2DActorSlot.c).
- Native constructor allocates exactly two layers, eight actor slots and five scene-model actors for this Event2D owner. Source: [eu/src/overlays/ov036/calls/InitEvent2DPanel.c:1-78](../src/overlays/ov036/calls/InitEvent2DPanel.c).

Contract limits:

- Sentinels are at+8c,+94,+98; no owner lookup bounds check is added.

## ClearPanelWindowWaitState

Identity: `ov036:020bda00`, ARM, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov036_020bda00`.

EU entrypoint: [eu/src/overlays/ov036/calls/ClearPanelWindowWaitState.c](../src/overlays/ov036/calls/ClearPanelWindowWaitState.c).

```c
void ClearPanelWindowWaitState(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Clears the four-word tail of Event2D work at+0x10ec. Source: [eu/src/overlays/ov036/calls/ClearPanelWindowWaitState.c:1-9](../src/overlays/ov036/calls/ClearPanelWindowWaitState.c).
- Clears this block after choice completion or skip. Source: [eu/src/overlays/ov036/calls/ScriptCmd_WaitWindowChoice.c:1-7](../src/overlays/ov036/calls/ScriptCmd_WaitWindowChoice.c).
- Clears same block after answer completion. Source: [eu/src/overlays/ov036/calls/ScriptCmd_WaitWindowAnswer.c:1-9](../src/overlays/ov036/calls/ScriptCmd_WaitWindowAnswer.c).

Contract limits:

- The four individual word meanings remain unknown.

## PanelScriptCmd_SetSlotSharedRecord

Identity: `ov036:020bdd08`, THUMB, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov036_020bdd08`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_SetSlotSharedRecord.c](../src/overlays/ov036/calls/PanelScriptCmd_SetSlotSharedRecord.c).

```c
void * PanelScriptCmd_SetSlotSharedRecord();
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Delegates unchanged VM/operand inputs to ScriptCmd_SetSlotSharedRecord. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_SetSlotSharedRecord.c:1-3](../src/overlays/ov036/calls/PanelScriptCmd_SetSlotSharedRecord.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/library_nitro_pxi/PXI_Init_020bdce8.c:1-5](../../src/ov036/library_nitro_pxi/PXI_Init_020bdce8.c).
- Exact EU callee body establishes operation rather than the inherited PXI/FS filename. Source: [eu/src/overlays/ov036/calls/ScriptCmd_SetSlotSharedRecord.c:1-6](../src/overlays/ov036/calls/ScriptCmd_SetSlotSharedRecord.c).

Contract limits:

- VM command return0 schedules its resume callback; return1 advances to the next command.

Additional native ABI observations:

- Thin adapters with legacy no-parameter declarations must retain incoming ARM arguments; changing their prototypes requires ABI verification.

## PanelScriptCmd_MoveActorSlotX

Identity: `ov036:020bdd10`, THUMB, native extent 62 bytes (including any configured pool). Previous symbol: `func_ov036_020bdd10`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotX.c](../src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotX.c).

```c
int PanelScriptCmd_MoveActorSlotX(void *self, char *descs);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Reads four8-byte operands left to right, invokes MoveActorSlotX and returns1. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotX.c:1-4](../src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotX.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/reviewed_helpers/func_ov036_020bdcf0.c:1-12](../../src/ov036/reviewed_helpers/func_ov036_020bdcf0.c).
- Exact EU callee body establishes operation rather than the inherited PXI/FS filename. Source: [eu/src/overlays/ov036/calls/MoveActorSlotX.c:1-4](../src/overlays/ov036/calls/MoveActorSlotX.c).

Contract limits:

- VM command return0 schedules its resume callback; return1 advances to the next command.

## PanelScriptCmd_StartActorSlotShake

Identity: `ov036:020bdd50`, THUMB, native extent 34 bytes (including any configured pool). Previous symbol: `func_ov036_020bdd50`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotShake.c](../src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotShake.c).

```c
int PanelScriptCmd_StartActorSlotShake(int param_1, unsigned short *param_2);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Reads owner ID and decay divisor, starts actor-slot shake and returns1. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotShake.c:1-4](../src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotShake.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/reviewed_helpers/func_ov036_020bdd30.c:1-9](../../src/ov036/reviewed_helpers/func_ov036_020bdd30.c).
- Exact EU callee body establishes operation rather than the inherited PXI/FS filename. Source: [eu/src/overlays/ov036/calls/StartActorSlotShake.c:1-24](../src/overlays/ov036/calls/StartActorSlotShake.c).

Contract limits:

- VM command return0 schedules its resume callback; return1 advances to the next command.

## PanelScriptCmd_ToggleActorSlotFlip

Identity: `ov036:020bdd74`, THUMB, native extent 14 bytes (including any configured pool). Previous symbol: `func_ov036_020bdd74`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_ToggleActorSlotFlip.c](../src/overlays/ov036/calls/PanelScriptCmd_ToggleActorSlotFlip.c).

```c
int PanelScriptCmd_ToggleActorSlotFlip(int arg0, void *cmd);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Reads actor ID, toggles its horizontal flip and returns1. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_ToggleActorSlotFlip.c:1-3](../src/overlays/ov036/calls/PanelScriptCmd_ToggleActorSlotFlip.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/shared_engine/ScriptCmd_EnterPhase_020bdd54.c:1-7](../../src/ov036/shared_engine/ScriptCmd_EnterPhase_020bdd54.c).
- Exact EU callee body establishes operation rather than the inherited PXI/FS filename. Source: [eu/src/overlays/ov036/calls/ToggleActorSlotFlip.c:1-4](../src/overlays/ov036/calls/ToggleActorSlotFlip.c).

Contract limits:

- VM command return0 schedules its resume callback; return1 advances to the next command.

## PanelScriptCmd_StartActorFocusTransition

Identity: `ov036:020bdd84`, THUMB, native extent 48 bytes (including any configured pool). Previous symbol: `func_ov036_020bdd84`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_StartActorFocusTransition.c](../src/overlays/ov036/calls/PanelScriptCmd_StartActorFocusTransition.c).

```c
int PanelScriptCmd_StartActorFocusTransition(void *context, ScriptOperand *operands);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Reads actor ID, direction/mode and duration; starts focus transition and returns0. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_StartActorFocusTransition.c:1-20](../src/overlays/ov036/calls/PanelScriptCmd_StartActorFocusTransition.c).
- Exact EU callee body establishes operation rather than the inherited PXI/FS filename. Source: [eu/src/overlays/ov036/calls/StartActorFocusTransition.c:1-4](../src/overlays/ov036/calls/StartActorFocusTransition.c).

Contract limits:

- VM command return0 schedules its resume callback; return1 advances to the next command.

## PanelScriptCmd_CloseAllTextWindows

Identity: `ov036:020be098`, THUMB, native extent 10 bytes (including any configured pool). Previous symbol: `func_ov036_020be098`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_CloseAllTextWindows.c](../src/overlays/ov036/calls/PanelScriptCmd_CloseAllTextWindows.c).

```c
int PanelScriptCmd_CloseAllTextWindows(void *p);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Invokes panel adapter that closes all text windows, then returns1. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_CloseAllTextWindows.c:1-3](../src/overlays/ov036/calls/PanelScriptCmd_CloseAllTextWindows.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/library_nitro_fs/FS_UnloadOverlayImage_020be078.c:1-6](../../src/ov036/library_nitro_fs/FS_UnloadOverlayImage_020be078.c).
- The delegated adapter calls CloseAllTextWindows. Source: [eu/src/overlays/ov036/calls/ClosePanelTextWindows.c:1-3](../src/overlays/ov036/calls/ClosePanelTextWindows.c).

Contract limits:

- Does not unload a filesystem overlay.

## PanelScriptResume_CloseTextWindowsDone

Identity: `ov036:020be0a4`, THUMB, native extent 4 bytes (including any configured pool). Previous symbol: `func_ov036_020be0a4`.

EU entrypoint: [eu/src/overlays/ov036/auto/PanelScriptResume_CloseTextWindowsDone.c](../src/overlays/ov036/auto/PanelScriptResume_CloseTextWindowsDone.c).

```c
int PanelScriptResume_CloseTextWindowsDone(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- The resume handler paired with close-windows script command returns1 unconditionally. Source: [eu/src/overlays/ov036/auto/PanelScriptResume_CloseTextWindowsDone.c:1-2](../src/overlays/ov036/auto/PanelScriptResume_CloseTextWindowsDone.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/library_nitro_fs/DefaultStepDone_020be084.c:1-1](../../src/ov036/library_nitro_fs/DefaultStepDone_020be084.c).
- Command table pairs close-windows run handler with this resume function. Source: [src/ov036/data/Data_ov036_020c373c.c:1-110](../../src/ov036/data/Data_ov036_020c373c.c).

Contract limits:

- Current run handler already returns1; this callback is a constant completion fallback.

## PanelScriptCmd_SetScreenLayerImage

Identity: `ov036:020be0a8`, THUMB, native extent 34 bytes (including any configured pool). Previous symbol: `func_ov036_020be0a8`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_SetScreenLayerImage.c](../src/overlays/ov036/calls/PanelScriptCmd_SetScreenLayerImage.c).

```c
int PanelScriptCmd_SetScreenLayerImage(int param_1, unsigned short *param_2);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Reads layer index and image ID, sets the layer image and returns1. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_SetScreenLayerImage.c:1-4](../src/overlays/ov036/calls/PanelScriptCmd_SetScreenLayerImage.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/reviewed_helpers/func_ov036_020be088.c:1-9](../../src/ov036/reviewed_helpers/func_ov036_020be088.c).
- Exact EU callee body establishes operation rather than the inherited PXI/FS filename. Source: [eu/src/overlays/ov036/calls/SetScreenLayerImage.c:1-4](../src/overlays/ov036/calls/SetScreenLayerImage.c).

Contract limits:

- VM command return0 schedules its resume callback; return1 advances to the next command.

## PanelScriptCmd_SetActorSlotPriority

Identity: `ov036:020be14c`, THUMB, native extent 34 bytes (including any configured pool). Previous symbol: `func_ov036_020be14c`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_SetActorSlotPriority.c](../src/overlays/ov036/calls/PanelScriptCmd_SetActorSlotPriority.c).

```c
int PanelScriptCmd_SetActorSlotPriority(int param_1, unsigned short *param_2);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Reads actor ID and priority, updates actor-slot priority and returns1. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_SetActorSlotPriority.c:1-4](../src/overlays/ov036/calls/PanelScriptCmd_SetActorSlotPriority.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/reviewed_helpers/func_ov036_020be12c.c:1-9](../../src/ov036/reviewed_helpers/func_ov036_020be12c.c).
- Exact EU callee body establishes operation rather than the inherited PXI/FS filename. Source: [eu/src/overlays/ov036/calls/SetActorSlotPriority.c:1-4](../src/overlays/ov036/calls/SetActorSlotPriority.c).

Contract limits:

- VM command return0 schedules its resume callback; return1 advances to the next command.

## PanelScriptCmd_StartActorSlotAlphaFade

Identity: `ov036:020be170`, THUMB, native extent 62 bytes (including any configured pool). Previous symbol: `func_ov036_020be170`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotAlphaFade.c](../src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotAlphaFade.c).

```c
int PanelScriptCmd_StartActorSlotAlphaFade(void *self, char *descs);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Reads four operands, starts actor-slot alpha fade and returns1. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotAlphaFade.c:1-4](../src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotAlphaFade.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/reviewed_helpers/func_ov036_020be150.c:1-12](../../src/ov036/reviewed_helpers/func_ov036_020be150.c).
- Exact EU callee body establishes operation rather than the inherited PXI/FS filename. Source: [eu/src/overlays/ov036/calls/StartActorSlotAlphaFade.c:1-4](../src/overlays/ov036/calls/StartActorSlotAlphaFade.c).

Contract limits:

- VM command return0 schedules its resume callback; return1 advances to the next command.

## PanelScriptCmd_ReleaseActorSlot

Identity: `ov036:020be1b0`, THUMB, native extent 14 bytes (including any configured pool). Previous symbol: `func_ov036_020be1b0`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_ReleaseActorSlot.c](../src/overlays/ov036/calls/PanelScriptCmd_ReleaseActorSlot.c).

```c
int PanelScriptCmd_ReleaseActorSlot(int arg0, void *cmd);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Reads actor owner ID, releases its slot and returns1. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_ReleaseActorSlot.c:1-3](../src/overlays/ov036/calls/PanelScriptCmd_ReleaseActorSlot.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/shared_engine/ScriptCmd_EnterPhase_020be190.c:1-7](../../src/ov036/shared_engine/ScriptCmd_EnterPhase_020be190.c).
- Exact EU callee body establishes operation rather than the inherited PXI/FS filename. Source: [eu/src/overlays/ov036/calls/ReleaseEvent2DActorSlot.c:1-27](../src/overlays/ov036/calls/ReleaseEvent2DActorSlot.c).

Contract limits:

- VM command return0 schedules its resume callback; return1 advances to the next command.

## PanelScriptCmd_MoveActorSlotY

Identity: `ov036:020be1c0`, THUMB, native extent 62 bytes (including any configured pool). Previous symbol: `func_ov036_020be1c0`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotY.c](../src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotY.c).

```c
int PanelScriptCmd_MoveActorSlotY(void *self, char *descs);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Reads four operands, invokes MoveActorSlotY and returns1. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotY.c:1-4](../src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotY.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/reviewed_helpers/func_ov036_020be1a0.c:1-12](../../src/ov036/reviewed_helpers/func_ov036_020be1a0.c).
- Exact EU callee body establishes operation rather than the inherited PXI/FS filename. Source: [eu/src/overlays/ov036/calls/MoveActorSlotY.c:1-5](../src/overlays/ov036/calls/MoveActorSlotY.c).

Contract limits:

- VM command return0 schedules its resume callback; return1 advances to the next command.

## FormatPanelWideText

Identity: `ov036:020be2f4`, THUMB, native extent 30 bytes (including any configured pool). Previous symbol: `func_ov036_020be2f4`.

EU entrypoint: [eu/src/overlays/ov036/calls/FormatPanelWideText.c](../src/overlays/ov036/calls/FormatPanelWideText.c).

```c
u16 * FormatPanelWideText(const u16 *format, u16 *dest, u32 destLength, ...);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Constructs va_list for arguments after destLength, calls bounded wide-text formatter, returns dest. Source: [eu/src/overlays/ov036/calls/FormatPanelWideText.c:1-15](../src/overlays/ov036/calls/FormatPanelWideText.c).
- EU wrapper uses the bounded Text_VSNPrintfWide backend. Source: [eu/src/overlays/ov036/calls/FormatWideTextV_020be2e0.c:1-3](../src/overlays/ov036/calls/FormatWideTextV_020be2e0.c).

Contract limits:

- The source ABI constructs va_list by32-bit stack slots; a port must use native stdarg conventions.

## PanelScriptCmd_StartScreenLayerScroll

Identity: `ov036:020be4ec`, THUMB, native extent 62 bytes (including any configured pool). Previous symbol: `func_ov036_020be4ec`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerScroll.c](../src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerScroll.c).

```c
int PanelScriptCmd_StartScreenLayerScroll(void *self, char *descs);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Reads four operands, starts screen-layer scroll and returns1. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerScroll.c:1-4](../src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerScroll.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/reviewed_helpers/func_ov036_020be4cc.c:1-12](../../src/ov036/reviewed_helpers/func_ov036_020be4cc.c).
- Exact EU callee body establishes operation rather than the inherited PXI/FS filename. Source: [eu/src/overlays/ov036/calls/StartScreenLayerScroll.c:1-4](../src/overlays/ov036/calls/StartScreenLayerScroll.c).

Contract limits:

- VM command return0 schedules its resume callback; return1 advances to the next command.

## PanelScriptResume_LoadEntityModel

Identity: `ov036:020be57c`, THUMB, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov036_020be57c`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptResume_LoadEntityModel.c](../src/overlays/ov036/calls/PanelScriptResume_LoadEntityModel.c).

```c
void * PanelScriptResume_LoadEntityModel();
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Thin adapter invokes ScriptCmd_LoadEntityModel with the incoming live VM/operand arguments. Source: [eu/src/overlays/ov036/calls/PanelScriptResume_LoadEntityModel.c:1-3](../src/overlays/ov036/calls/PanelScriptResume_LoadEntityModel.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/library_nitro_pxi/PXI_Init_020be55c.c:1-5](../../src/ov036/library_nitro_pxi/PXI_Init_020be55c.c).
- Exact EU callee body establishes operation rather than the inherited PXI/FS filename. Source: [eu/src/overlays/ov036/calls/ScriptCmd_LoadEntityModel.c:1-5](../src/overlays/ov036/calls/ScriptCmd_LoadEntityModel.c).

Contract limits:

- VM command return0 schedules its resume callback; return1 advances to the next command.

Additional native ABI observations:

- Thin adapters with legacy no-parameter declarations must retain incoming ARM arguments; changing their prototypes requires ABI verification.

## PanelScriptCmd_ReleaseModelSlot

Identity: `ov036:020be628`, THUMB, native extent 34 bytes (including any configured pool). Previous symbol: `func_ov036_020be628`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_ReleaseModelSlot.c](../src/overlays/ov036/calls/PanelScriptCmd_ReleaseModelSlot.c).

```c
int PanelScriptCmd_ReleaseModelSlot(int param_1, unsigned short *param_2);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Reads model group handle and force flag, releases model slot and returns1. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_ReleaseModelSlot.c:1-4](../src/overlays/ov036/calls/PanelScriptCmd_ReleaseModelSlot.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/reviewed_helpers/func_ov036_020be608.c:1-9](../../src/ov036/reviewed_helpers/func_ov036_020be608.c).
- Exact EU callee body establishes operation rather than the inherited PXI/FS filename. Source: [eu/src/overlays/ov036/calls/ReleaseModelSlot.c:1-6](../src/overlays/ov036/calls/ReleaseModelSlot.c).

Contract limits:

- VM command return0 schedules its resume callback; return1 advances to the next command.

## PanelScriptCmd_StartScreenLayerZoom

Identity: `ov036:020be67c`, THUMB, native extent 64 bytes (including any configured pool). Previous symbol: `func_ov036_020be67c`.

EU entrypoint: [eu/src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerZoom.c](../src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerZoom.c).

```c
u32 PanelScriptCmd_StartScreenLayerZoom(void *vm,void *operands);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Reads layer index, zoom and duration; starts layer zoom only when VM skipRequested+0x628 is zero; always returns1. Source: [eu/src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerZoom.c:1-19](../src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerZoom.c).
- Exact target handles fixed-point zoom setup and duration. Source: [eu/src/overlays/ov036/calls/StartScreenLayerZoom.c:1-64](../src/overlays/ov036/calls/StartScreenLayerZoom.c).
- Main VM layout identifies+0x628 as skipRequested. Source: [src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c:1-139](../../src/arm9/shared_engine/ScriptVm_RunFrame_02025b18.c).

Contract limits:

- All three operands are still evaluated during skip.

## PanelScriptCmd_BeginWaitSoundState4Clear

Identity: `ov036:020be78c`, THUMB, native extent 4 bytes (including any configured pool). Previous symbol: `func_ov036_020be78c`.

EU entrypoint: [eu/src/overlays/ov036/auto/PanelScriptCmd_BeginWaitSoundState4Clear.c](../src/overlays/ov036/auto/PanelScriptCmd_BeginWaitSoundState4Clear.c).

```c
int PanelScriptCmd_BeginWaitSoundState4Clear(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns0 so the paired resume callback waits until sound state byte is no longer4, unless VM skipRequested is set. Source: [eu/src/overlays/ov036/auto/PanelScriptCmd_BeginWaitSoundState4Clear.c:1-2](../src/overlays/ov036/auto/PanelScriptCmd_BeginWaitSoundState4Clear.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/library_nitro_fs/FSi_CloseFileCommand_020be76c.c:1-1](../../src/ov036/library_nitro_fs/FSi_CloseFileCommand_020be76c.c).
- Pairs constant-zero run handler with IsResourceReadyOrInitialize. Source: [src/ov036/data/Data_ov036_020c373c.c:1-110](../../src/ov036/data/Data_ov036_020c373c.c).
- Resume predicate succeeds for skipRequested or IsSceneState4 false. Source: [eu/src/overlays/ov036/calls/IsPanelScriptSoundWaitComplete.c:1-3](../src/overlays/ov036/calls/IsPanelScriptSoundWaitComplete.c).
- EU wrapper binds tested owner to gSoundWork, not a movie/scene resource. Source: [eu/src/calls/IsSceneState4.c:1-3](../src/calls/IsSceneState4.c).
- Returns whether sound-work byte+0xb472e equals4. Source: [src/arm9/shared_engine/IsSceneState4_0204d6fc.c:1-8](../../src/arm9/shared_engine/IsSceneState4_0204d6fc.c).

Contract limits:

- The helper name historically says IsResourceReadyOrInitialize; actual predicate completes when IsSceneState4 is FALSE. Do not invert its sense.

## IsPanelScriptSoundWaitComplete

Identity: `ov036:020be790`, THUMB, native extent 36 bytes (including any configured pool). Previous symbol: `IsResourceReadyOrInitialize_020be790`.

EU entrypoint: [eu/src/overlays/ov036/calls/IsPanelScriptSoundWaitComplete.c](../src/overlays/ov036/calls/IsPanelScriptSoundWaitComplete.c).

```c
BOOL IsPanelScriptSoundWaitComplete(Resource *resource);
```

The pointer is the panel ScriptVm, whose +0x628 is skipRequested. The private Resource/ready labels are false; the result is TRUE for skipRequested or global sound state not equal to 4.

Demonstrated behavior and evidence:

- EU wrapper binds sound predicate and real shared implementation. Source: [eu/src/overlays/ov036/calls/IsPanelScriptSoundWaitComplete.c:1-3](../src/overlays/ov036/calls/IsPanelScriptSoundWaitComplete.c).
- Input is VM with skipRequested+0x628; succeeds on skipRequested or sound predicate false. It performs no resource initialization. Source: [src/ov036/shared_engine/IsResourceReadyOrInitialize_020be770.c:1-19](../../src/ov036/shared_engine/IsResourceReadyOrInitialize_020be770.c).
- Predicate reads gSoundWork, not scene resource. Source: [eu/src/calls/IsSceneState4.c:1-3](../src/calls/IsSceneState4.c).

Contract limits:

- No state4 narrative meaning inferred.

## InitTextWindowTask

Identity: `ov036:020be858`, ARM, native extent 188 bytes (including any configured pool). Previous symbol: `func_ov036_020be858`.

EU entrypoint: [eu/src/overlays/ov036/calls/InitTextWindowTask.c](../src/overlays/ov036/calls/InitTextWindowTask.c).

```c
code * InitTextWindowTask(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Captures current TaskObject work, clears the text-window owner, initializes three window states and loader, loads background/fonts and object manager, returns UpdateTextWindows. Source: [eu/src/overlays/ov036/calls/InitTextWindowTask.c:1-34](../src/overlays/ov036/calls/InitTextWindowTask.c).
- Returned task update dispatches the three0x110 windows. Source: [eu/src/overlays/ov036/calls/UpdateTextWindows.c:1-9](../src/overlays/ov036/calls/UpdateTextWindows.c).

Contract limits:

- Task work is owned by TaskObject; no extra allocation is inferred from old heap name.

## DestroyTextWindowTask

Identity: `ov036:020be914`, ARM, native extent 52 bytes (including any configured pool). Previous symbol: `func_ov036_020be914`.

EU entrypoint: [eu/src/overlays/ov036/calls/DestroyTextWindowTask.c](../src/overlays/ov036/calls/DestroyTextWindowTask.c).

```c
void DestroyTextWindowTask(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Releases text display records, fonts and background/archive resources; invokes the constant completion hook then clears the text-window owner pointer. Source: [eu/src/overlays/ov036/calls/DestroyTextWindowTask.c:1-15](../src/overlays/ov036/calls/DestroyTextWindowTask.c).
- Frees text-window background archive and message handle. Source: [eu/src/overlays/ov036/calls/ReleaseTextWindowBackground.c:1-13](../src/overlays/ov036/calls/ReleaseTextWindowBackground.c).
- Releases both font resource handles. Source: [eu/src/overlays/ov036/calls/ReleaseTextWindowFonts.c:1-9](../src/overlays/ov036/calls/ReleaseTextWindowFonts.c).

Contract limits:

- Does not free TaskObject-owned work itself.
- FSi_DefaultStepDoneB is a constant return1 hook; this call is not evidence of loader cleanup.

## ReleaseTextWindowBackground

Identity: `ov036:020beb3c`, ARM, native extent 64 bytes (including any configured pool). Previous symbol: `func_ov036_020beb3c`.

EU entrypoint: [eu/src/overlays/ov036/calls/ReleaseTextWindowBackground.c](../src/overlays/ov036/calls/ReleaseTextWindowBackground.c).

```c
void ReleaseTextWindowBackground(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Frees background archive if present and clears it, then releases the message-container handle. Source: [eu/src/overlays/ov036/calls/ReleaseTextWindowBackground.c:1-13](../src/overlays/ov036/calls/ReleaseTextWindowBackground.c).
- Allocates archive and message handle into the matching owner fields. Source: [eu/src/overlays/ov036/calls/LoadTextWindowBackground.c:1-7](../src/overlays/ov036/calls/LoadTextWindowBackground.c).
- Native overlay prefix identifies handle+4 and archive+8. Source: [src/ov036/unclassified_helpers/LoadTextWindowBackground_020bea80.c:1-32](../../src/ov036/unclassified_helpers/LoadTextWindowBackground_020bea80.c).

## LoadTextWindowFonts

Identity: `ov036:020beb7c`, ARM, native extent 64 bytes (including any configured pool). Previous symbol: `func_ov036_020beb7c`.

EU entrypoint: [eu/src/overlays/ov036/calls/LoadTextWindowFonts.c](../src/overlays/ov036/calls/LoadTextWindowFonts.c).

```c
void LoadTextWindowFonts(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Loads main font from eu10.nftr into+0x644c and secondary font from jp10.nftr into+0x68a8. Source: [eu/src/overlays/ov036/calls/LoadTextWindowFonts.c:1-11](../src/overlays/ov036/calls/LoadTextWindowFonts.c).
- Native owner view names two FontResource-sized handles at those exact offsets. Source: [eu/src/overlays/ov036/Ov036TextWindowState.h:1-33](../src/overlays/ov036/Ov036TextWindowState.h).

Contract limits:

- Both language-named font resources are used in EU; do not discard jp10 as region-dead data.

## ReleaseTextWindowFonts

Identity: `ov036:020bebbc`, ARM, native extent 48 bytes (including any configured pool). Previous symbol: `func_ov036_020bebbc`.

EU entrypoint: [eu/src/overlays/ov036/calls/ReleaseTextWindowFonts.c](../src/overlays/ov036/calls/ReleaseTextWindowFonts.c).

```c
void ReleaseTextWindowFonts(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Releases secondary and main font handles in reverse order. Source: [eu/src/overlays/ov036/calls/ReleaseTextWindowFonts.c:1-9](../src/overlays/ov036/calls/ReleaseTextWindowFonts.c).
- Offsets identify exact font handles. Source: [eu/src/overlays/ov036/Ov036TextWindowState.h:1-33](../src/overlays/ov036/Ov036TextWindowState.h).

## ReleaseTextWindowGraphics

Identity: `ov036:020bee60`, ARM, native extent 172 bytes (including any configured pool). Previous symbol: `func_ov036_020bee60`.

EU entrypoint: [eu/src/overlays/ov036/calls/ReleaseTextWindowGraphics.c](../src/overlays/ov036/calls/ReleaseTextWindowGraphics.c).

```c
void ReleaseTextWindowGraphics(int *window);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Frees optional text buffer, releases active window canvas/display objects and clears active bit, then clears its BG2 or BG3 tilemap. Source: [eu/src/overlays/ov036/calls/ReleaseTextWindowGraphics.c:1-38](../src/overlays/ov036/calls/ReleaseTextWindowGraphics.c).

Contract limits:

- If window kind0or4 shares a pointer, the pointed word is cleared after buffer release; owner itself remains allocated.

## ReleaseTextWindowDisplayList

Identity: `ov036:020bf4f4`, ARM, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov036_020bf4f4`.

EU entrypoint: [eu/src/overlays/ov036/calls/ReleaseTextWindowDisplayList.c](../src/overlays/ov036/calls/ReleaseTextWindowDisplayList.c).

```c
void ReleaseTextWindowDisplayList(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Unlinks all records and releases the display list at text owner+0x18. Source: [eu/src/overlays/ov036/calls/ReleaseTextWindowDisplayList.c:1-10](../src/overlays/ov036/calls/ReleaseTextWindowDisplayList.c).
- Initializes the same text display manager. Source: [eu/src/overlays/ov036/calls/InitOverlayObjManager.c:1-30](../src/overlays/ov036/calls/InitOverlayObjManager.c).

## UpdateTextWindowDisplayList

Identity: `ov036:020bf620`, ARM, native extent 28 bytes (including any configured pool). Previous symbol: `func_ov036_020bf620`.

EU entrypoint: [eu/src/overlays/ov036/calls/UpdateTextWindowDisplayList.c](../src/overlays/ov036/calls/UpdateTextWindowDisplayList.c).

```c
void UpdateTextWindowDisplayList(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Queues display-list update for owner+0x18. Source: [eu/src/overlays/ov036/calls/UpdateTextWindowDisplayList.c:1-8](../src/overlays/ov036/calls/UpdateTextWindowDisplayList.c).

Contract limits:

- Underlying UpdateDisplayObjectListQueued was independently audited in the037/038 report; it is not an initialization.

## ReleaseTextWindowSpriteRecords

Identity: `ov036:020bf63c`, ARM, native extent 84 bytes (including any configured pool). Previous symbol: `func_ov036_020bf63c`.

EU entrypoint: [eu/src/overlays/ov036/calls/ReleaseTextWindowSpriteRecords.c](../src/overlays/ov036/calls/ReleaseTextWindowSpriteRecords.c).

```c
void ReleaseTextWindowSpriteRecords(int work);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Queues display-list update then releases five possible indexed records, restoring each record index to-1. Source: [eu/src/overlays/ov036/calls/ReleaseTextWindowSpriteRecords.c:1-21](../src/overlays/ov036/calls/ReleaseTextWindowSpriteRecords.c).

Contract limits:

- Uses entries+0xb4 with stride0x10.

## UploadTextWindowBgCharacters

Identity: `ov036:020bf690`, ARM, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov036_020bf690`.

EU entrypoint: [eu/src/overlays/ov036/calls/UploadTextWindowBgCharacters.c](../src/overlays/ov036/calls/UploadTextWindowBgCharacters.c).

```c
void UploadTextWindowBgCharacters(int handlerIndex, HandlerOwner *owner, u32 arg0, u32 arg1);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Dispatches an engine/BG-specific character loader with owner->target at+0x14 and two forwarded arguments. Source: [eu/src/overlays/ov036/calls/UploadTextWindowBgCharacters.c:1-14](../src/overlays/ov036/calls/UploadTextWindowBgCharacters.c).
- Table0..7 contains MAIN BG0..3 then SUB BG0..3 character uploads. Source: [eu/src/overlays/ov036/data/tables/gTextSceneBgCharacterLoaders.c:1-21](../src/overlays/ov036/data/tables/gTextSceneBgCharacterLoaders.c).

Contract limits:

- No handler-index bounds check is added.

## UploadTextWindowBgScreen

Identity: `ov036:020bf6b8`, ARM, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov036_020bf6b8`.

EU entrypoint: [eu/src/overlays/ov036/calls/UploadTextWindowBgScreen.c](../src/overlays/ov036/calls/UploadTextWindowBgScreen.c).

```c
void UploadTextWindowBgScreen(int handlerIndex, HandlerOwner *owner, u32 arg0, u32 arg1);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Dispatches an engine/BG-specific screen-map loader with embedded owner+0xc and two forwarded arguments. Source: [eu/src/overlays/ov036/calls/UploadTextWindowBgScreen.c:1-14](../src/overlays/ov036/calls/UploadTextWindowBgScreen.c).
- Table0..7 contains MAIN BG0..3 then SUB BG0..3 screen uploads. Source: [eu/src/overlays/ov036/data/tables/gTextSceneBgScreenLoaders.c:1-21](../src/overlays/ov036/data/tables/gTextSceneBgScreenLoaders.c).

Contract limits:

- Character loader uses a pointer at+0x14; screen loader uses address+0xc. Preserve that distinction.

## TextWindowState_IdleNoOp

Identity: `ov036:020bf6dc`, ARM, native extent 4 bytes (including any configured pool). Previous symbol: `func_ov036_020bf6dc`.

EU entrypoint: [eu/src/overlays/ov036/auto/TextWindowState_IdleNoOp.c](../src/overlays/ov036/auto/TextWindowState_IdleNoOp.c).

```c
void TextWindowState_IdleNoOp(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Empty callback occupies window state0. Source: [eu/src/overlays/ov036/auto/TextWindowState_IdleNoOp.c:1-2](../src/overlays/ov036/auto/TextWindowState_IdleNoOp.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/panel_state/func_ov036_020bf6bc.c:1-1](../../src/ov036/panel_state/func_ov036_020bf6bc.c).
- Exact handler table has this function at index0. Source: [eu/src/overlays/ov036/data/tables/gTextWindowStateHandlers.c:1-33](../src/overlays/ov036/data/tables/gTextWindowStateHandlers.c).
- Dispatches by each window state. Source: [eu/src/overlays/ov036/calls/UpdateTextWindows.c:1-9](../src/overlays/ov036/calls/UpdateTextWindows.c).

## TextWindowState_WaitPageAdvanceNoOp

Identity: `ov036:020c0e30`, ARM, native extent 4 bytes (including any configured pool). Previous symbol: `func_ov036_020c0e30`.

EU entrypoint: [eu/src/overlays/ov036/auto/TextWindowState_WaitPageAdvanceNoOp.c](../src/overlays/ov036/auto/TextWindowState_WaitPageAdvanceNoOp.c).

```c
void TextWindowState_WaitPageAdvanceNoOp(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Empty callback occupies window state7. Source: [eu/src/overlays/ov036/auto/TextWindowState_WaitPageAdvanceNoOp.c:1-2](../src/overlays/ov036/auto/TextWindowState_WaitPageAdvanceNoOp.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/panel_state/func_ov036_020c0e10.c:1-1](../../src/ov036/panel_state/func_ov036_020c0e10.c).
- Exact handler table index7. Source: [eu/src/overlays/ov036/data/tables/gTextWindowStateHandlers.c:1-33](../src/overlays/ov036/data/tables/gTextWindowStateHandlers.c).
- Scans windows in state7 and explicitly advances them to8or13. Source: [eu/src/overlays/ov036/calls/AdvanceFinishedTextWindows.c:1-6](../src/overlays/ov036/calls/AdvanceFinishedTextWindows.c).

## TextWindowState_WaitPrimaryFadeOut

Identity: `ov036:020c1d48`, ARM, native extent 84 bytes (including any configured pool). Previous symbol: `func_ov036_020c1d48`.

EU entrypoint: [eu/src/overlays/ov036/calls/TextWindowState_WaitPrimaryFadeOut.c](../src/overlays/ov036/calls/TextWindowState_WaitPrimaryFadeOut.c).

```c
void TextWindowState_WaitPrimaryFadeOut(int work);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Waits until primary window state is9; disables two sprite records of this window and changes it to state9. Source: [eu/src/overlays/ov036/calls/TextWindowState_WaitPrimaryFadeOut.c:1-18](../src/overlays/ov036/calls/TextWindowState_WaitPrimaryFadeOut.c).
- Own callback is state13 and state9 is StepPanelFadeOut. Source: [eu/src/overlays/ov036/data/tables/gTextWindowStateHandlers.c:1-33](../src/overlays/ov036/data/tables/gTextWindowStateHandlers.c).

## SetTextWindowFlag

Identity: `ov036:020c27dc`, ARM, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov036_020c27dc`.

EU entrypoint: [eu/src/overlays/ov036/calls/SetTextWindowFlag.c](../src/overlays/ov036/calls/SetTextWindowFlag.c).

```c
int SetTextWindowFlag(int arg0, int *arg1);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Sets the requested packed bit in window+0xc. Source: [eu/src/overlays/ov036/calls/SetTextWindowFlag.c:1-3](../src/overlays/ov036/calls/SetTextWindowFlag.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/shared_engine/func_ov036_020c27bc.c:1-5](../../src/ov036/shared_engine/func_ov036_020c27bc.c).
- Actual helper accepts bit-array pointer and integer bit index; bits are numbered31-(index&31). Source: [src/arm9/bit_array/SetPackedBit.c:1-5](../../src/arm9/bit_array/SetPackedBit.c).

Additional native ABI observations:

- Legacy arg1 int* is a synthetic type for the integer bitIndex. Do not reinterpret as pointed data.

## ClearTextWindowFlag

Identity: `ov036:020c27ec`, ARM, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov036_020c27ec`.

EU entrypoint: [eu/src/overlays/ov036/calls/ClearTextWindowFlag.c](../src/overlays/ov036/calls/ClearTextWindowFlag.c).

```c
int ClearTextWindowFlag(int arg0, int *arg1);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Clears the requested packed bit in window+0xc. Source: [eu/src/overlays/ov036/calls/ClearTextWindowFlag.c:1-3](../src/overlays/ov036/calls/ClearTextWindowFlag.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/shared_engine/func_ov036_020c27cc.c:1-5](../../src/ov036/shared_engine/func_ov036_020c27cc.c).
- Actual helper takes integer bit index. Source: [src/arm9/bit_array/ClearPackedBit.c:1-5](../../src/arm9/bit_array/ClearPackedBit.c).

Additional native ABI observations:

- Legacy arg1 int* is synthetic; real ABI forwards bit index.

## SetTextWindowState

Identity: `ov036:020c27fc`, ARM, native extent 16 bytes (including any configured pool). Previous symbol: `SetTimerDuration`.

EU entrypoint: [eu/src/overlays/ov036/calls/SetTextWindowState.c](../src/overlays/ov036/calls/SetTextWindowState.c).

```c
void SetTextWindowState(TimerNode *node, int duration);
```

The native TimerNode/duration labels are false. The logical inputs are window and next state; it stores state at +8 and clears the counter at +0x10.

Demonstrated behavior and evidence:

- EU wrapper selects this setter. Source: [eu/src/overlays/ov036/calls/SetTextWindowState.c:1-2](../src/overlays/ov036/calls/SetTextWindowState.c).
- Stores word+8 and clears word+10. Source: [src/ov036/unclassified_helpers/SetTimerDuration_020c27dc.c:1-13](../../src/ov036/unclassified_helpers/SetTimerDuration_020c27dc.c).
- Calls setter(window,10), immediately reads that value and dispatches state10 callback. This is a state setter, not duration. Source: [src/ov036/text_rendering/CloseAllTextWindows_020c2910.c:1-55](../../src/ov036/text_rendering/CloseAllTextWindows_020c2910.c).
- Changes states7to8or13 using this setter. Source: [src/ov036/text_rendering/AdvanceFinishedTextWindows_020c2a9c.c:1-58](../../src/ov036/text_rendering/AdvanceFinishedTextWindows_020c2a9c.c).

Contract limits:

- Secondary counter at+0x10 resets on every state change.

## GetTextWindowState

Identity: `ov036:020c280c`, ARM, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov036_020c280c`.

EU entrypoint: [eu/src/overlays/ov036/auto/GetTextWindowState.c](../src/overlays/ov036/auto/GetTextWindowState.c).

```c
u32 GetTextWindowState(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns word at window+8 used as the state handler table index. Source: [eu/src/overlays/ov036/auto/GetTextWindowState.c:1-2](../src/overlays/ov036/auto/GetTextWindowState.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/leaf_research/func_ov036_020c27ec.c:1-5](../../src/ov036/leaf_research/func_ov036_020c27ec.c).
- Calls this getter, indexes gTextWindowStateHandlers and invokes selected handler. Source: [eu/src/overlays/ov036/calls/UpdateTextWindows.c:1-9](../src/overlays/ov036/calls/UpdateTextWindows.c).

## PlayTextWindowSound7WithCooldown

Identity: `ov036:020c2814`, ARM, native extent 64 bytes (including any configured pool). Previous symbol: `func_ov036_020c2814`.

EU entrypoint: [eu/src/overlays/ov036/calls/PlayTextWindowSound7WithCooldown.c](../src/overlays/ov036/calls/PlayTextWindowSound7WithCooldown.c).

```c
void PlayTextWindowSound7WithCooldown(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- When global cooldown is zero plays sound7 and sets cooldown2. Source: [eu/src/overlays/ov036/calls/PlayTextWindowSound7WithCooldown.c:1-12](../src/overlays/ov036/calls/PlayTextWindowSound7WithCooldown.c).
- Decrements this cooldown once per unpaused text update. Source: [eu/src/overlays/ov036/calls/UpdateTextWindows.c:1-9](../src/overlays/ov036/calls/UpdateTextWindows.c).

Contract limits:

- No speculative navigation/action meaning is assigned to sound7.

## CreateTextWindowTask

Identity: `ov036:020c2854`, ARM, native extent 48 bytes (including any configured pool). Previous symbol: `func_ov036_020c2854`.

EU entrypoint: [eu/src/overlays/ov036/calls/CreateTextWindowTask.c](../src/overlays/ov036/calls/CreateTextWindowTask.c).

```c
unsigned int CreateTextWindowTask(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Instantiates text-window task descriptor, stores its handle in the first owner word and returns it. Source: [eu/src/overlays/ov036/calls/CreateTextWindowTask.c:1-13](../src/overlays/ov036/calls/CreateTextWindowTask.c).
- Construct callback initializes the window engine and returns UpdateTextWindows. Source: [eu/src/overlays/ov036/calls/InitTextWindowTask.c:1-34](../src/overlays/ov036/calls/InitTextWindowTask.c).

## DestroyTextWindowTaskHandle

Identity: `ov036:020c2884`, ARM, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov036_020c2884`.

EU entrypoint: [eu/src/overlays/ov036/calls/DestroyTextWindowTaskHandle.c](../src/overlays/ov036/calls/DestroyTextWindowTaskHandle.c).

```c
void * DestroyTextWindowTaskHandle();
```

The native empty argument list forwards a live TaskObject handle in R0. The destruction wrapper returns the next task-list node as a borrowed pointer; it is not a success flag or newly allocated work.

Demonstrated behavior and evidence:

- Thin adapter forwards to TaskObject destruction wrapper. Source: [eu/src/overlays/ov036/calls/DestroyTextWindowTaskHandle.c:1-3](../src/overlays/ov036/calls/DestroyTextWindowTaskHandle.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/library_nitro_pxi/PXI_Init_020c2864.c:1-5](../../src/ov036/library_nitro_pxi/PXI_Init_020c2864.c).
- Controller destructor passes its saved text-window task handle through this adapter. Source: [eu/src/overlays/ov036/calls/DestroyPxiChannelState.c:1-5](../src/overlays/ov036/calls/DestroyPxiChannelState.c).

Additional native ABI observations:

- Legacy no-parameter declaration preserves incoming R0. Real argument is task handle; use actual ARM ABI when repairing signature.

## InitTextWindowControllerTask

Identity: `ov036:020c2d68`, ARM, native extent 116 bytes (including any configured pool). Previous symbol: `func_ov036_020c2d68`.

EU entrypoint: [eu/src/overlays/ov036/calls/InitTextWindowControllerTask.c](../src/overlays/ov036/calls/InitTextWindowControllerTask.c).

```c
code * InitTextWindowControllerTask(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Captures own TaskObject work, configures display/VRAM, installs open/update/close panel callbacks, creates text-window task, returns no-op update callback. Source: [eu/src/overlays/ov036/calls/InitTextWindowControllerTask.c:1-28](../src/overlays/ov036/calls/InitTextWindowControllerTask.c).
- Creates child text-window task. Source: [eu/src/overlays/ov036/calls/CreateTextWindowTask.c:1-13](../src/overlays/ov036/calls/CreateTextWindowTask.c).
- Third installed callback closes panel and restores backed-up graphics. Source: [eu/src/overlays/ov036/calls/CloseOverlayPanel.c:1-6](../src/overlays/ov036/calls/CloseOverlayPanel.c).

## UpdateTextWindowControllerNoOp

Identity: `ov036:020c2e10`, ARM, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov036_020c2e10`.

EU entrypoint: [eu/src/overlays/ov036/auto/UpdateTextWindowControllerNoOp.c](../src/overlays/ov036/auto/UpdateTextWindowControllerNoOp.c).

```c
u32 UpdateTextWindowControllerNoOp(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Task update callback returns0 without mutation. Source: [eu/src/overlays/ov036/auto/UpdateTextWindowControllerNoOp.c:1-2](../src/overlays/ov036/auto/UpdateTextWindowControllerNoOp.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/leaf_research/func_ov036_020c2df0.c:1-5](../../src/ov036/leaf_research/func_ov036_020c2df0.c).
- Constructor returns this callback as its update method. Source: [eu/src/overlays/ov036/calls/InitTextWindowControllerTask.c:1-28](../src/overlays/ov036/calls/InitTextWindowControllerTask.c).

## IsTextWindowControllerReady

Identity: `ov036:020c2f24`, ARM, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov036_020c2f24`.

EU entrypoint: [eu/src/overlays/ov036/auto/IsTextWindowControllerReady.c](../src/overlays/ov036/auto/IsTextWindowControllerReady.c).

```c
u32 IsTextWindowControllerReady(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Current text-window controller readiness hook always returns1. Source: [eu/src/overlays/ov036/auto/IsTextWindowControllerReady.c:1-2](../src/overlays/ov036/auto/IsTextWindowControllerReady.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/leaf_research/func_ov036_020c2f04.c:1-5](../../src/ov036/leaf_research/func_ov036_020c2f04.c).
- Panel startup waits for this hook before advancing to scene state1. Source: [eu/src/overlays/ov036/calls/PanelSceneState_WaitControllerReady.c:1-23](../src/overlays/ov036/calls/PanelSceneState_WaitControllerReady.c).

## GetPanelTextWindowChoiceResult

Identity: `ov036:020c30f8`, ARM, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov036_020c30f8`.

EU entrypoint: [eu/src/overlays/ov036/calls/GetPanelTextWindowChoiceResult.c](../src/overlays/ov036/calls/GetPanelTextWindowChoiceResult.c).

```c
void * GetPanelTextWindowChoiceResult();
```

The pointer-return source view is a register-forwarding artifact. The underlying getter returns the choice-result word at owner +0x68a0; no ownership or new pointer allocation is established.

Demonstrated behavior and evidence:

- Thin adapter returns GetTextWindowChoiceResult. Source: [eu/src/overlays/ov036/calls/GetPanelTextWindowChoiceResult.c:1-3](../src/overlays/ov036/calls/GetPanelTextWindowChoiceResult.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/library_nitro_pxi/PXI_Init_020c30d8.c:1-5](../../src/ov036/library_nitro_pxi/PXI_Init_020c30d8.c).
- Native owner getter returns choiceResult at0x68a0. Source: [eu/src/overlays/ov036/calls/GetTextWindowChoiceResult.c:1-6](../src/overlays/ov036/calls/GetTextWindowChoiceResult.c).

Additional native ABI observations:

- Legacy void* result carries signed integer choice in R0; use actual typed caller evidence before changing declarations.

## OpenTextPanelWithGraphicsBackup

Identity: `ov036:020c32bc`, ARM, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov036_020c32bc`.

EU entrypoint: [eu/src/overlays/ov036/calls/OpenTextPanelWithGraphicsBackup.c](../src/overlays/ov036/calls/OpenTextPanelWithGraphicsBackup.c).

```c
u32 OpenTextPanelWithGraphicsBackup(u32 value);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Selects active entry1, backs up BG graphics and opens requested panel, returning1. Source: [eu/src/overlays/ov036/calls/OpenTextPanelWithGraphicsBackup.c:1-13](../src/overlays/ov036/calls/OpenTextPanelWithGraphicsBackup.c).
- Saves MAIN BG2/BG3 maps, characters, palette and window-mask state. Source: [eu/src/overlays/ov036/calls/BackupBgGraphics.c:1-65](../src/overlays/ov036/calls/BackupBgGraphics.c).

## UpdateTextPanelPromptCallback

Identity: `ov036:020c32e4`, ARM, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov036_020c32e4`.

EU entrypoint: [eu/libs/nitro/fs/calls/UpdateTextPanelPromptCallback.c](../libs/nitro/fs/calls/UpdateTextPanelPromptCallback.c).

```c
int UpdateTextPanelPromptCallback(void *p);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Invokes UpdatePanelPromptInput and returns1. Source: [eu/libs/nitro/fs/calls/UpdateTextPanelPromptCallback.c:1-3](../libs/nitro/fs/calls/UpdateTextPanelPromptCallback.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/library_nitro_fs/FS_UnloadOverlayImage_020c32c4.c:1-6](../../src/ov036/library_nitro_fs/FS_UnloadOverlayImage_020c32c4.c).
- Installs this function as the panel update callback. Source: [eu/src/overlays/ov036/calls/InitTextWindowControllerTask.c:1-28](../src/overlays/ov036/calls/InitTextWindowControllerTask.c).

Contract limits:

- Not a filesystem overlay unload despite inherited FS function name.

## ClosePanelTextWindows

Identity: `ov036:020c3368`, ARM, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov036_020c3368`.

EU entrypoint: [eu/src/overlays/ov036/calls/ClosePanelTextWindows.c](../src/overlays/ov036/calls/ClosePanelTextWindows.c).

```c
void * ClosePanelTextWindows();
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Thin adapter invokes CloseAllTextWindows. Source: [eu/src/overlays/ov036/calls/ClosePanelTextWindows.c:1-3](../src/overlays/ov036/calls/ClosePanelTextWindows.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/library_nitro_pxi/PXI_Init_020c3348.c:1-5](../../src/ov036/library_nitro_pxi/PXI_Init_020c3348.c).
- Target closes all three windows and clears history entries. Source: [eu/src/overlays/ov036/calls/CloseAllTextWindows.c:1-8](../src/overlays/ov036/calls/CloseAllTextWindows.c).

## AdvancePanelFinishedTextWindows

Identity: `ov036:020c3374`, ARM, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov036_020c3374`.

EU entrypoint: [eu/src/overlays/ov036/calls/AdvancePanelFinishedTextWindows.c](../src/overlays/ov036/calls/AdvancePanelFinishedTextWindows.c).

```c
void * AdvancePanelFinishedTextWindows();
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Thin adapter invokes AdvanceFinishedTextWindows. Source: [eu/src/overlays/ov036/calls/AdvancePanelFinishedTextWindows.c:1-3](../src/overlays/ov036/calls/AdvancePanelFinishedTextWindows.c).
- Shared C body selected by exact EU wrapper aliases. Source: [src/ov036/library_nitro_pxi/PXI_Init_020c3354.c:1-5](../../src/ov036/library_nitro_pxi/PXI_Init_020c3354.c).
- Target advances windows waiting at state7 and adjusts their name-record visibility. Source: [eu/src/overlays/ov036/calls/AdvanceFinishedTextWindows.c:1-6](../src/overlays/ov036/calls/AdvanceFinishedTextWindows.c).

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov036/calls/PanelSceneState_WaitControllerReady.c PanelSceneState_WaitControllerReady
python tools/verify_idx.py src/overlays/ov036/calls/UpdateEvent2DSceneObjects.c UpdateEvent2DSceneObjects
python tools/verify_idx.py src/overlays/ov036/calls/UpdateEvent2DActorSlot.c UpdateEvent2DActorSlot
python tools/verify_idx.py src/overlays/ov036/calls/GetActorSlotOffscreenY.c GetActorSlotOffscreenY
python tools/verify_idx.py src/overlays/ov036/calls/CreateEvent2DPanelTask.c CreateEvent2DPanelTask
python tools/verify_idx.py src/overlays/ov036/auto/CanEvent2DSceneAdvanceSession.c CanEvent2DSceneAdvanceSession
python tools/verify_idx.py src/overlays/ov036/calls/SlideEvent2DActorSlotsOffscreen.c SlideEvent2DActorSlotsOffscreen
python tools/verify_idx.py src/overlays/ov036/calls/StartActorSlotShake.c StartActorSlotShake
python tools/verify_idx.py src/overlays/ov036/calls/ReleaseEvent2DActorSlot.c ReleaseEvent2DActorSlot
python tools/verify_idx.py src/overlays/ov036/calls/ClearPanelWindowWaitState.c ClearPanelWindowWaitState
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_SetSlotSharedRecord.c PanelScriptCmd_SetSlotSharedRecord --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotX.c PanelScriptCmd_MoveActorSlotX --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotShake.c PanelScriptCmd_StartActorSlotShake --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_ToggleActorSlotFlip.c PanelScriptCmd_ToggleActorSlotFlip --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_StartActorFocusTransition.c PanelScriptCmd_StartActorFocusTransition --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_CloseAllTextWindows.c PanelScriptCmd_CloseAllTextWindows --thumb
python tools/verify_idx.py src/overlays/ov036/auto/PanelScriptResume_CloseTextWindowsDone.c PanelScriptResume_CloseTextWindowsDone --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_SetScreenLayerImage.c PanelScriptCmd_SetScreenLayerImage --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_SetActorSlotPriority.c PanelScriptCmd_SetActorSlotPriority --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_StartActorSlotAlphaFade.c PanelScriptCmd_StartActorSlotAlphaFade --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_ReleaseActorSlot.c PanelScriptCmd_ReleaseActorSlot --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_MoveActorSlotY.c PanelScriptCmd_MoveActorSlotY --thumb
python tools/verify_idx.py src/overlays/ov036/calls/FormatPanelWideText.c FormatPanelWideText --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerScroll.c PanelScriptCmd_StartScreenLayerScroll --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptResume_LoadEntityModel.c PanelScriptResume_LoadEntityModel --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_ReleaseModelSlot.c PanelScriptCmd_ReleaseModelSlot --thumb
python tools/verify_idx.py src/overlays/ov036/calls/PanelScriptCmd_StartScreenLayerZoom.c PanelScriptCmd_StartScreenLayerZoom --thumb
python tools/verify_idx.py src/overlays/ov036/auto/PanelScriptCmd_BeginWaitSoundState4Clear.c PanelScriptCmd_BeginWaitSoundState4Clear --thumb
python tools/verify_idx.py src/overlays/ov036/calls/IsPanelScriptSoundWaitComplete.c IsPanelScriptSoundWaitComplete --thumb
python tools/verify_idx.py src/overlays/ov036/calls/InitTextWindowTask.c InitTextWindowTask
python tools/verify_idx.py src/overlays/ov036/calls/DestroyTextWindowTask.c DestroyTextWindowTask
python tools/verify_idx.py src/overlays/ov036/calls/ReleaseTextWindowBackground.c ReleaseTextWindowBackground
python tools/verify_idx.py src/overlays/ov036/calls/LoadTextWindowFonts.c LoadTextWindowFonts
python tools/verify_idx.py src/overlays/ov036/calls/ReleaseTextWindowFonts.c ReleaseTextWindowFonts
python tools/verify_idx.py src/overlays/ov036/calls/ReleaseTextWindowGraphics.c ReleaseTextWindowGraphics
python tools/verify_idx.py src/overlays/ov036/calls/ReleaseTextWindowDisplayList.c ReleaseTextWindowDisplayList
python tools/verify_idx.py src/overlays/ov036/calls/UpdateTextWindowDisplayList.c UpdateTextWindowDisplayList
python tools/verify_idx.py src/overlays/ov036/calls/ReleaseTextWindowSpriteRecords.c ReleaseTextWindowSpriteRecords
python tools/verify_idx.py src/overlays/ov036/calls/UploadTextWindowBgCharacters.c UploadTextWindowBgCharacters
python tools/verify_idx.py src/overlays/ov036/calls/UploadTextWindowBgScreen.c UploadTextWindowBgScreen
python tools/verify_idx.py src/overlays/ov036/auto/TextWindowState_IdleNoOp.c TextWindowState_IdleNoOp
python tools/verify_idx.py src/overlays/ov036/auto/TextWindowState_WaitPageAdvanceNoOp.c TextWindowState_WaitPageAdvanceNoOp
python tools/verify_idx.py src/overlays/ov036/calls/TextWindowState_WaitPrimaryFadeOut.c TextWindowState_WaitPrimaryFadeOut
python tools/verify_idx.py src/overlays/ov036/calls/SetTextWindowFlag.c SetTextWindowFlag
python tools/verify_idx.py src/overlays/ov036/calls/ClearTextWindowFlag.c ClearTextWindowFlag
python tools/verify_idx.py src/overlays/ov036/calls/SetTextWindowState.c SetTextWindowState
python tools/verify_idx.py src/overlays/ov036/auto/GetTextWindowState.c GetTextWindowState
python tools/verify_idx.py src/overlays/ov036/calls/PlayTextWindowSound7WithCooldown.c PlayTextWindowSound7WithCooldown
python tools/verify_idx.py src/overlays/ov036/calls/CreateTextWindowTask.c CreateTextWindowTask
python tools/verify_idx.py src/overlays/ov036/calls/DestroyTextWindowTaskHandle.c DestroyTextWindowTaskHandle
python tools/verify_idx.py src/overlays/ov036/calls/InitTextWindowControllerTask.c InitTextWindowControllerTask
python tools/verify_idx.py src/overlays/ov036/auto/UpdateTextWindowControllerNoOp.c UpdateTextWindowControllerNoOp
python tools/verify_idx.py src/overlays/ov036/auto/IsTextWindowControllerReady.c IsTextWindowControllerReady
python tools/verify_idx.py src/overlays/ov036/calls/GetPanelTextWindowChoiceResult.c GetPanelTextWindowChoiceResult
python tools/verify_idx.py src/overlays/ov036/calls/OpenTextPanelWithGraphicsBackup.c OpenTextPanelWithGraphicsBackup
python tools/verify_idx.py libs/nitro/fs/calls/UpdateTextPanelPromptCallback.c UpdateTextPanelPromptCallback
python tools/verify_idx.py src/overlays/ov036/calls/ClosePanelTextWindows.c ClosePanelTextWindows
python tools/verify_idx.py src/overlays/ov036/calls/AdvancePanelFinishedTextWindows.c AdvancePanelFinishedTextWindows
bash tools/gate.sh
```

All entrypoints in this document pass their official function checks. The full
108-function block passes the fresh gate for all 108 linked modules. Affected
function bytes, resolved relocation targets/types and addends, and all module
hashes match the preserved baseline. Native signatures and algorithms are
unchanged; verified-library receipts remain current.
