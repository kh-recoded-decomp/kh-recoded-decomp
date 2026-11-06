# Field-panel, message-window and field-switch callbacks

These EU overlay 001 callbacks belong to three distinct owners: the field-scene manager, the message-window work block, and class 11 field objects. Their names describe the roles proved by the registration tables, invokers and state writers below.

| EU identity | Function | Current source |
| --- | --- | --- |
| `ov001:020708f0` | `FieldPanel_ShownStateNoop` | `eu/src/overlays/ov001/auto/FieldPanel_ShownStateNoop.c` |
| `ov001:0207a118` | `MessageWindow_WaitForInputNoop` | `eu/src/overlays/ov001/auto/MessageWindow_WaitForInputNoop.c` |
| `ov001:0207ad5c` | `MenuOverlay_ReadyStateNoop` | `eu/src/overlays/ov001/auto/MenuOverlay_ReadyStateNoop.c` |
| `ov001:02085f04` | `FieldSwitchObject_BeforeReleaseNoop` | `eu/src/overlays/ov001/auto/FieldSwitchObject_BeforeReleaseNoop.c` |

All four are two-byte Thumb functions containing `BX LR` (`70 47`). The invokers pass an owner pointer in R0 and discard the residual return. The current definitions remain empty `void(void)` functions imported through legacy `_fp_init` wrappers. Their distinct, nonnull registrations remain significant. The wrapper prototype alone does not establish a portable callback ABI; a typed port should describe each invoker consistently across translation units.

## Field panel shown state

`FieldPanel_ShownStateNoop` receives `gFieldSceneGlobals.manager`. The state word is manager +0x47c. `OpenFieldPanel` accepts state 0 and requests state 1; `UpdateMenuSlideIn` changes it to 2 when the opening tween finishes. The state-2 callback holds that state without additional work. `StartFieldSlideIn` accepts state 2 and requests state 3; `UpdateSceneSlideOut` returns it to 0 when its tween finishes.

The native table at 0x0209ecec contains the callback pointer 0x020708f1 at +8. `UpdateFieldHud` passes the manager at 0x02070ecc and invokes the selected handler at 0x02070ece. The instruction at 0x02070ed0 replaces R0, so the callback return has no logical status meaning. `UpdateMenuSlideIn` stores state 2 at 0x020708ac; `StartFieldSlideIn` compares state 2 at 0x020718a2 and stores state 3 at 0x02071962.

Source evidence:

- `src/ov001/field_manager/UpdateFieldHud_02070e98.c:105`: `handler(manager)`.
- `src/ov001/field_manager/OpenFieldPanel_020717e4.c:51`: requests state 1.
- `src/ov001/field_manager/UpdateMenuSlideIn_02070870.c:33`: enters state 2.
- `src/ov001/field_manager/StartFieldSlideIn_02071898.c:96`: requests state 3.
- `src/ov001/shared_engine/UpdateSceneSlideOut_020708f4.c:38`: returns to state 0.

“Shown” describes this field-panel state only. It does not establish global HUD visibility, input ownership, duration or a cleanup action.

## Message window waiting for input

`MessageWindow_WaitForInputNoop` receives `gMessageWindowWork +4`; its phase is argument +8, equivalent to global work +0xc. `DrawGridMenuCellsAndEnterState6` draws the grid and writes phase 6. Each frame, `RunActiveModeHandler` processes `HandleModeMenuInput`, rereads the phase, then invokes the selected callback.

In phase 6, pressed-key mask 0x1 closes through `UpdateMessageWindow_0207a68c` and `CloseModeWindow`. Direction masks move the choice; mask 0x80 also closes when work +0x68 is zero. Closing changes the phase to 0 or 7. The no-op itself neither polls keys nor advances the window. Explicit external close APIs can also end this phase.

The table at 0x0209ef24 contains 0x0207a119 at +0x18. The phase-6 writer is 0x02079f7a–0x02079f7c. The dispatcher calls input processing at 0x0207a4e4, reads the phase at 0x0207a4e8, passes work +4 at 0x0207a4f4, and invokes the callback at 0x0207a4f6. `MOVS R0,#0` at 0x0207a4f8 discards its return.

Source evidence:

- `src/ov001/leaf_research/RunActiveModeHandler_0207a4d0.c:29`: invokes the selected handler.
- `eu/src/overlays/ov001/calls/DrawGridMenuCellsAndEnterState6.c:8`: writes phase 6.
- `src/ov001/field_manager/HandleModeMenuInput_0207a370.c:21`: phase-6 input branch.
- `src/ov001/field_manager/UpdateMessageWindow_0207a68c.c:73`: phase-6 close branch.
- `src/ov001/field_manager/CloseModeWindow_0207a260.c:56`: enters phase 7; the alternate branch enters phase 0.

## Menu-overlay ready state

`MenuOverlay_ReadyStateNoop` receives `gSubscenePanelWork`. Its phase is panel +0x30. `UpdateDisplayFadeState` enters phase 6 when its setup or bypass path finishes; both brightness-convergence handlers also enter phase 6 when brightness reaches zero. The callback leaves this settled phase unchanged.

`RequestPanelModeChange` accepts phase 6 or 0, checks panel +0x38 independently, then calls `Panel_InitFromModeTables`, which requests phase 1 for the next overlay load. “Ready” describes the settled phase and does not promise that every independent request guard passes. Phase 6 can bypass a fade.

The table at 0x0209ef6c contains 0x0207ad5d at +0x18. `UpdatePanelScene` reads phase +0x30 at 0x0207b014 and invokes the selected callback with the panel at 0x0207b020; the subsequent path overwrites R0 before reading it. State-6 writes occur at 0x0207acac, 0x0207acd4, 0x0207acf8, 0x0207ad22 and 0x0207ad4e. The mode-request initializer writes phase 1 at 0x0207b27a.

Source evidence:

- `eu/src/overlays/ov001/calls/UpdatePanelScene.c:51`: invokes the phase callback.
- `src/ov001/field_manager/UpdateDisplayFadeState_0207ac90.c:30`: enters phase 6.
- `src/ov001/field_manager/StepSubScreenFadeIn_0207ad04.c:19`: enters phase 6 at brightness zero.
- `src/ov001/leaf_research/StepSubScreenFadeIn_0207ad30.c:19`: the opposite convergence direction.
- `src/ov001/leaf_research/RequestPanelModeChange_0207b27c.c:38`: accepts phase 0 or 6.
- `eu/src/overlays/ov001/calls/Panel_InitFromModeTables.c:28`: requests phase 1.

## Field-switch hook before release

`FieldSwitchObject_BeforeReleaseNoop` belongs to a class 11 field-object instance, allocated with a 0x78-byte object size. `ActivateFieldSwitchObject` calls `SetupPanelHandlers` for session state 4. Setup installs this callback at object +0x68.

The class constructor registers `ReleaseTaskWithCallback` at class +0x10. `ReleaseObjectUse` invokes that method as `(object, 0)`. The method calls instance +0x68 with the object, then releases attached models and owner resources. The no-op is a notification before those resource releases.

Native setup loads 0x02085f05 from 0x02085f5c and stores it at object +0x68 at 0x02085f4c. The constructor stores 0x02082301 at class +0x10 at 0x0208265e. `ReleaseTaskWithCallback` reads instance +0x68 at 0x02082306 and invokes it at 0x0208230c. At 0x0208230e it replaces R0 with the class/work pointer from object +8, discarding the callback return.

Source evidence:

- `src/ov001/field_objects/ActivateFieldSwitchObject_02082070.c:140`: selects session state 4.
- `src/ov001/reviewed_helpers/SetupPanelHandlers_02085f18.c:25`: installs the callback.
- `src/ov001/unclassified_helpers/CreateFieldObjectClassType11_020825e0.c:57`: installs the class release method.
- `src/ov001/field_objects/ReleaseObjectUse_0207f648.c:29`: invokes that method.
- `src/ov001/unclassified_helpers/ReleaseTaskWithCallback_020822d8.c:18`: invokes the instance hook before releasing resources.
- `src/ov001/reviewed_helpers/ClosePanelWithSound_020825bc.c:16`: invokes the separate callback at object +0x6c.

The private `SetupPanelHandlers` field labels `update` and `draw` are misleading: +0x68 is read before release, while `ClosePanelWithSound` invokes +0x6c. Neither label proves a per-frame update or draw role. No callback allocation ownership or returned pointer is established.

## Retained menu-overlay phase 0

`MenuOverlay_Phase0Noop` (formerly `func_ov001_0207abd8`) at `ov001:0207abd8` has its operational slot name in `eu/src/overlays/ov001/auto/MenuOverlay_Phase0Noop.c`. It occupies nonnull table slot 0 and receives `gSubscenePanelWork` through `UpdatePanelScene`, with an ignored return. `RequestPanelModeChange` accepts phase 0 or 6 but checks +0x38 separately. `InitFieldPanelScene` zero-fills 0x114 bytes, then synchronously sets phase 2 before returning.

No persistent same-owner transition into phase 0 after initialization is established. A descriptive lifecycle name needs a writer of panel +0x30 = 0 whose result reaches the dispatcher, or a same-owner descriptor contract identifying that phase. The zero fill and acceptance comparison alone do not establish an inactive or disabled state. [The operational contract](FIELD_OPERATIONAL_CALLBACKS_COMMANDS.md) names the registered slot without claiming that missing transition.

## Native provenance

The original `eu/recoded.nds` header identifies BK9P. Overlay-table entry 1 selects FAT range 0x48e00..0x7b5e0. Decompression yields 258208 bytes at 0x020613e0, byte-identical to `eu/dsd_extract/arm9_overlays/ov001.bin`, SHA-256 `25e21d3cbdd78107bff05dc971a145936f2087114c4cfb5b89aedc93636f6015`.

Read the ARM9 overlay-table offset at ROM header +0x50 and the FAT offset at +0x48 to reproduce the extraction. Decode functions using their configured ARM/Thumb extents; literal-pool words remain data. The instruction and pointer evidence above comes from the original module.

## Name history

| Previous symbol | Current symbol |
| --- | --- |
| `func_ov001_020708f0` | `FieldPanel_ShownStateNoop` |
| `func_ov001_0207a118` | `MessageWindow_WaitForInputNoop` |
| `func_ov001_0207ad5c` | `MenuOverlay_ReadyStateNoop` |
| `func_ov001_02085f04` | `FieldSwitchObject_BeforeReleaseNoop` |

## Validation

The official gate passed. All 14 individual byte-exact checks passed, all 21 complete objects retained their allocated sections, symbol layouts and relocation targets/types/addends, and all 108 module hashes remained unchanged. These counts cover the combined integration block containing these callbacks, the two stage-expression names and three existing DATA aliases.
