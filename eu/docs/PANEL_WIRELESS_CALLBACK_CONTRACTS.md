# Panel lifecycle, widget and wireless callback contracts (ov013-015)

These 40 EU names follow owner constructors, native dispatch and actual
consumers. Existing prototypes, registered hooks and raw results are preserved.
Original identities distinguish overlays sharing native RAM addresses.

## Identity and source table

Sources are relative to `eu/`; evidence paths use repository root. Shared-source names must be resolved through the EU wrapper.

| EU identity/mode | Proposed name | EU source | Evidence source |
|---|---|---|---|
| ov013:020732a4 arm | `Ov013Panel_LeaveSaveStateNoop` | `src/overlays/ov013/auto/Ov013Panel_LeaveSaveStateNoop.c` | `eu/src/overlays/ov013/calls/ChangePanelMenuState.c` |
| ov013:020739a0 arm | `Ov013Panel_LeavePlayerCardTransitionNoop` | `src/overlays/ov013/auto/Ov013Panel_LeavePlayerCardTransitionNoop.c` | `eu/src/overlays/ov013/calls/ChangePanelMenuState.c` |
| ov013:02073a98 arm | `Ov013Panel_LeaveHeldScrollTowardStartNoop` | `src/overlays/ov013/auto/Ov013Panel_LeaveHeldScrollTowardStartNoop.c` | `eu/src/overlays/ov013/calls/ChangePanelMenuState.c` |
| ov013:02073b90 arm | `Ov013Panel_LeaveHeldScrollTowardEndNoop` | `src/overlays/ov013/auto/Ov013Panel_LeaveHeldScrollTowardEndNoop.c` | `eu/src/overlays/ov013/calls/ChangePanelMenuState.c` |
| ov013:02074238 arm | `Ov013Scroll_Phase0UpdateNoop` | `src/overlays/ov013/auto/Ov013Scroll_Phase0UpdateNoop.c` | `eu/src/overlays/ov013/calls/SetPanelPhase.c` |
| ov013:0207423c arm | `Ov013Scroll_LeavePhase0Noop` | `src/overlays/ov013/auto/Ov013Scroll_LeavePhase0Noop.c` | `eu/src/overlays/ov013/calls/SetPanelPhase.c` |
| ov013:02074348 arm | `Ov013Scroll_LeaveUpNoop` | `src/overlays/ov013/auto/Ov013Scroll_LeaveUpNoop.c` | `eu/src/overlays/ov013/calls/SetPanelPhase.c` |
| ov013:0207441c arm | `Ov013Scroll_LeaveDownNoop` | `src/overlays/ov013/auto/Ov013Scroll_LeaveDownNoop.c` | `eu/src/overlays/ov013/calls/SetPanelPhase.c` |
| ov013:02074498 arm | `Ov013MenuTouchEventNoop` | `src/overlays/ov013/auto/Ov013MenuTouchEventNoop.c` | `src/ov013/panel_state/InitPanelScene_0206c480.c` |
| ov013:02074718 arm | `Ov013SubWidget19ConfirmNoop` | `src/overlays/ov013/auto/Ov013SubWidget19ConfirmNoop.c` | `src/ov013/panel_state/InitPanelSubScreenGraphics_0206d078.c` |
| ov013:020749ec arm | `Ov013SubWidget26ConfirmNoop` | `src/overlays/ov013/auto/Ov013SubWidget26ConfirmNoop.c` | `src/ov013/panel_state/InitPanelSubScreenGraphics_0206d078.c` |
| ov013:020749f0 arm | `Ov013SubWidget27ConfirmNoop` | `src/overlays/ov013/auto/Ov013SubWidget27ConfirmNoop.c` | `src/ov013/panel_state/InitPanelSubScreenGraphics_0206d078.c` |
| ov014:0206d2e0 arm | `Ov014Panel_LeaveOpenStateNoop` | `src/overlays/ov014/auto/Ov014Panel_LeaveOpenStateNoop.c` | `src/ov014/panel_state/ChangePanelState_0206d1c0.c` |
| ov014:0206d2e4 arm | `Ov014Panel_EnterEditStateNoop` | `src/overlays/ov014/auto/Ov014Panel_EnterEditStateNoop.c` | `src/ov014/panel_state/ChangePanelState_0206d1c0.c` |
| ov014:0206e84c arm | `Ov014Panel_LeaveEditStateNoop` | `src/overlays/ov014/auto/Ov014Panel_LeaveEditStateNoop.c` | `src/ov014/panel_state/ChangePanelState_0206d1c0.c` |
| ov014:0206e8fc arm | `Ov014Panel_LeaveCloseStateNoop` | `src/overlays/ov014/auto/Ov014Panel_LeaveCloseStateNoop.c` | `src/ov014/panel_state/ChangePanelState_0206d1c0.c` |
| ov015:0206fa98 arm | `ApplyWirelessCardProgressBonus` | `src/overlays/ov015/calls/ApplyWirelessCardProgressBonus.c` | `src/ov002/unclassified_helpers/StampContextDateTime_02067564.c` |
| ov015:02070c54 arm | `WirelessMenu_LeaveState0Noop` | `src/overlays/ov015/auto/WirelessMenu_LeaveState0Noop.c` | `eu/src/overlays/ov015/calls/SetWirelessMenuState.c` |
| ov015:02070fa8 arm | `WirelessMenu_LeaveState1AndReleaseCursor` | `src/overlays/ov015/calls/WirelessMenu_LeaveState1AndReleaseCursor.c` | `eu/src/overlays/ov002/calls/ReleaseMenuCursorState.c` |
| ov015:02071060 arm | `WirelessMenu_LeaveOwnerProfileStateNoop` | `src/overlays/ov015/auto/WirelessMenu_LeaveOwnerProfileStateNoop.c` | `eu/src/overlays/ov015/calls/SetWirelessMenuState.c` |
| ov015:020716ec arm | `WirelessMenu_LeaveState3AndReleaseCursor` | `src/overlays/ov015/calls/WirelessMenu_LeaveState3AndReleaseCursor.c` | `eu/src/overlays/ov002/calls/ReleaseMenuCursorState.c` |
| ov015:02071ab0 arm | `WirelessMenu_LeaveHeaderStateNoop` | `src/overlays/ov015/auto/WirelessMenu_LeaveHeaderStateNoop.c` | `eu/src/overlays/ov015/calls/SetWirelessMenuState.c` |
| ov015:02072754 arm | `WirelessSubWidget4ConfirmNoop` | `src/overlays/ov015/auto/WirelessSubWidget4ConfirmNoop.c` | `eu/src/overlays/ov015/calls/SetupPanelGraphics.c` |
| ov015:02072860 arm | `WirelessCardSlot1_SelectAndSlideOutWithSound` | `src/overlays/ov015/calls/WirelessCardSlot1_SelectAndSlideOutWithSound.c` | `src/ov015/panel_state/InitPanelScreenGraphics_0206d59c.c` |
| ov015:02072878 arm | `WirelessCardSlot2_SelectAndSlideOutWithSound` | `src/overlays/ov015/calls/WirelessCardSlot2_SelectAndSlideOutWithSound.c` | `src/ov015/panel_state/InitPanelScreenGraphics_0206d59c.c` |
| ov015:02072890 arm | `WirelessCardSlot3_SelectAndSlideOutWithSound` | `src/overlays/ov015/calls/WirelessCardSlot3_SelectAndSlideOutWithSound.c` | `src/ov015/panel_state/InitPanelScreenGraphics_0206d59c.c` |
| ov015:02072cec arm | `SetWirelessReceivedCardCallback` | `src/overlays/ov015/calls/SetWirelessReceivedCardCallback.c` | `src/ov015/reviewed_helpers/InvokePanelCallback_02073598.c` |
| ov015:02072f98 arm | `WirelessConnection_LeaveState0Noop` | `src/overlays/ov015/auto/WirelessConnection_LeaveState0Noop.c` | `eu/src/overlays/ov015/calls/SetWirelessConnectionState.c` |
| ov015:02072f9c arm | `WirelessConnection_EnterState1Noop` | `src/overlays/ov015/auto/WirelessConnection_EnterState1Noop.c` | `eu/src/overlays/ov015/calls/SetWirelessConnectionState.c` |
| ov015:02072fa0 arm | `WirelessConnection_UpdateState1Noop` | `src/overlays/ov015/auto/WirelessConnection_UpdateState1Noop.c` | `eu/src/overlays/ov015/calls/SetWirelessConnectionState.c` |
| ov015:02072fa4 arm | `WirelessConnection_LeaveState1Noop` | `src/overlays/ov015/auto/WirelessConnection_LeaveState1Noop.c` | `eu/src/overlays/ov015/calls/SetWirelessConnectionState.c` |
| ov015:02073030 arm | `WirelessConnection_EnterState3Noop` | `src/overlays/ov015/auto/WirelessConnection_EnterState3Noop.c` | `eu/src/overlays/ov015/calls/SetWirelessConnectionState.c` |
| ov015:020730a4 arm | `WirelessConnection_LeaveState3Noop` | `src/overlays/ov015/auto/WirelessConnection_LeaveState3Noop.c` | `eu/src/overlays/ov015/calls/SetWirelessConnectionState.c` |
| ov015:020730a8 arm | `WirelessConnection_EnterState4Noop` | `src/overlays/ov015/auto/WirelessConnection_EnterState4Noop.c` | `eu/src/overlays/ov015/calls/SetWirelessConnectionState.c` |
| ov015:02073148 arm | `WirelessConnection_LeaveState4Noop` | `src/overlays/ov015/auto/WirelessConnection_LeaveState4Noop.c` | `eu/src/overlays/ov015/calls/SetWirelessConnectionState.c` |
| ov015:0207314c arm | `WirelessConnection_EnterState5Noop` | `src/overlays/ov015/auto/WirelessConnection_EnterState5Noop.c` | `eu/src/overlays/ov015/calls/SetWirelessConnectionState.c` |
| ov015:020731b8 arm | `WirelessConnection_LeaveState5Noop` | `src/overlays/ov015/auto/WirelessConnection_LeaveState5Noop.c` | `eu/src/overlays/ov015/calls/SetWirelessConnectionState.c` |
| ov015:0207321c arm | `WirelessConnection_LeaveState6Noop` | `src/overlays/ov015/auto/WirelessConnection_LeaveState6Noop.c` | `eu/src/overlays/ov015/calls/SetWirelessConnectionState.c` |
| ov015:02073280 arm | `WirelessConnection_LeaveState7Noop` | `src/overlays/ov015/auto/WirelessConnection_LeaveState7Noop.c` | `eu/src/overlays/ov015/calls/SetWirelessConnectionState.c` |
| ov015:02075338 arm | `WirelessMenu_State5DisplayEffectsNoop` | `src/overlays/ov015/auto/WirelessMenu_State5DisplayEffectsNoop.c` | `eu/src/overlays/ov015/calls/UpdateWirelessMenuDisplayEffects.c` |

## State tables reconstructed from the ROM

All five logical state tables use three function pointers per record: enter, update, exit, stride 12 bytes. They cross physical DATA fragments. A fragment file name and its C declaration order do not identify the logical table base. The extracted EU bytes, symbol address/mode and dispatchers establish these records:

| Owner/table | Logical base | Records | State field / dispatcher |
|---|---|---|---|
| ov013 panel menu | 02074bbc | 12 | singleton mode; `ChangePanelMenuState` invokes old exit, writes mode, invokes new enter |
| ov013 scroll phases | 02074b34 | 3 | singleton +0xd258; `SetPanelPhase` uses the same exit/write/enter pattern |
| ov014 record edit panel | 0206f8f8 | 3 | singleton +0xcf8a; `ChangePanelState` |
| ov015 wireless menu | 0207e780 | 8 | singleton 0207e960 signed byte0; `SetWirelessMenuState` |
| ov015 wireless connection | 0207e804 | 8 | separate singleton 0207e964 signed byte0; `SetWirelessConnectionState` |

The old state -1 skips its exit call. These native setters do not bounds-check the new signed state. This documentation does not add state validation or merge the two wireless owners.

| Table / state | Enter | Update | Exit |
|---|---|---|---|
| ov013 panel menu state 5 | `ResetPanelSaveStep` | `PollPanelSaveStep` | `Ov013Panel_LeaveSaveStateNoop` |
| ov013 panel menu state 8 | `BeginOv013PlayerCardPageTransition` | `AdvancePanelCloseStep` | `Ov013Panel_LeavePlayerCardTransitionNoop` |
| ov013 panel menu state 9 | `ResetPanelListUpStep` | `UpdateOv013HeldScrollTowardStart` | `Ov013Panel_LeaveHeldScrollTowardStartNoop` |
| ov013 panel menu state 10 | `ResetPanelListDownStep` | `UpdateOv013HeldScrollTowardEnd` | `Ov013Panel_LeaveHeldScrollTowardEndNoop` |
| ov013 scroll phase 0 | `SetPanelScrollUpDirection` | `Ov013Scroll_Phase0UpdateNoop` | `Ov013Scroll_LeavePhase0Noop` |
| ov013 scroll phase 1 | `LoadPanelPaletteBase` | `ScrollPanelSlotsUp` | `Ov013Scroll_LeaveUpNoop` |
| ov013 scroll phase 2 | `SetPanelScrollDownDirection` | `ScrollPanelSlotsDown` | `Ov013Scroll_LeaveDownNoop` |
| ov014 record edit panel state 0 | `RefreshOv014SelectedEntryInfo` | `UpdatePanelOpenStep` | `Ov014Panel_LeaveOpenStateNoop` |
| ov014 record edit panel state 1 | `Ov014Panel_EnterEditStateNoop` | `UpdatePanelEditInput` | `Ov014Panel_LeaveEditStateNoop` |
| ov014 record edit panel state 2 | `ResetPanelCloseStep` | `UpdatePanelCloseStep` | `Ov014Panel_LeaveCloseStateNoop` |
| ov015 wireless menu state 0 | `ResetPanelExitFlags` | `UpdatePanelExitSequence` | `WirelessMenu_LeaveState0Noop` |
| ov015 wireless menu state 1 | `ResetPanelSelection` | `UpdatePanelMenuState_02070c80` | `WirelessMenu_LeaveState1AndReleaseCursor` |
| ov015 wireless menu state 2 | `InitWirelessMenuOwnerProfileView` | `UpdatePanelPendingAction` | `WirelessMenu_LeaveOwnerProfileStateNoop` |
| ov015 wireless menu state 3 | `StartPlayerCardSharing` | `UpdatePanelShareState` | `WirelessMenu_LeaveState3AndReleaseCursor` |
| ov015 wireless menu state 4 | `ClearOv002PanelModeDirtyFromWireless` | `DrawWirelessPanelHeaderAndEnterState1` | `WirelessMenu_LeaveHeaderStateNoop` |
| ov015 wireless connection state 0 | `InitPeerWirelessSession` | `EnterWirelessConnectionState3UnlessHelperState3` | `WirelessConnection_LeaveState0Noop` |
| ov015 wireless connection state 1 | `WirelessConnection_EnterState1Noop` | `WirelessConnection_UpdateState1Noop` | `WirelessConnection_LeaveState1Noop` |
| ov015 wireless connection state 3 | `WirelessConnection_EnterState3Noop` | `HandleMatchTransition` | `WirelessConnection_LeaveState3Noop` |
| ov015 wireless connection state 4 | `WirelessConnection_EnterState4Noop` | `UpdateWirelessParentState` | `WirelessConnection_LeaveState4Noop` |
| ov015 wireless connection state 5 | `WirelessConnection_EnterState5Noop` | `HandleConnectTransition` | `WirelessConnection_LeaveState5Noop` |
| ov015 wireless connection state 6 | `StartWirelessFinalizeDelay16` | `PollWirelessFinalizeDelay17` | `WirelessConnection_LeaveState6Noop` |
| ov015 wireless connection state 7 | `StartWirelessFinalizeDelay19` | `PollWirelessFinalizeDelay20` | `WirelessConnection_LeaveState7Noop` |

For example, ov013 scroll+0x4 is the phase0 update no-op; phase0 exit is the next word at +0x8. The fragment named `gPanelScrollHandlers` starts at 02074b3c, while the logical table starts at 02074b34. Likewise wireless menu/connection fragments begin two words after their logical bases. Naming an init/update/exit from the fragment alone would shift every role.

All empty functions are ARM `BX LR`: they preserve the incoming R0 word. No return is interpreted as BOOL, completion, an owned object or a request to change callbacks. Exit results are overwritten by the setter state work; per-frame dispatchers continue using their owner fields. An enter callback can leave a residual register result propagated by the setter, which is not a new logical API. Keep nonnull registered addresses and distinct duplicate functions.

Two wireless menu exits (states 1 and 3) call `ReleaseMenuCursorState`, which frees and clears the global touch/cursor owner when nonnull. These are call wrappers, not PXI/FIFO initializers. Their legacy void* return is not evidence of an owned pointer.

## Widget and touch event callbacks

`ResolveEntryStoreWord(root,id,callback)` resolves the widget, then the real setter stores its confirm callback at widget+0xa8. The old alias `StoreWordAt0x98` is wrong. `MoveFocusByDpad` invokes the nonnull callback as `(focusedWidget)` for confirm key mask 1; its callback return is not treated as accepted/handled. The no-ops remain registered.

| Owning root | Widget IDs | Callback behavior |
|---|---|---|
| ov013 sub-widget root | 0x13, 0x1a, 0x1b (19,26,27) | Registered empty confirm hooks |
| ov015 sub-widget root | 4 | Registered empty confirm hook |
| ov015 card-selection sub-root | 1,2,3 | Three distinct wrappers forward the widget to SelectWidgetAndSlideOut, then sound(2,1) |

The shared selector reads widget+0xc kind 1/2/3, stores selectedCard 0/1/2, clears the corresponding context flag, starts the upward tween and sounds(2,8). The wrapper adds a second sound call. The legacy wrapper declaration/call omitted the widget argument in C; native R0 forwarding and the real worker prove the input. No signature repair is silently mixed into this rename plan.

The ov013 menu-touch no-op is a separate interface: InitMenuCursorState stores it in the first word of a 0x2c-byte owner. UpdateMenuTouch calls `(event,&point,0)` for press 1, release 2, tap 4 or drag 8. Its incoming R0 is an event mask, not a widget or cursor pointer.

## Received-card callback and misleading SDK view

`SetWirelessReceivedCardCallback` is a wireless callback setter. Native instructions load singleton 0207e964 and store R0 at +0x90. StartPlayerCardSharing registers AddReceivedPlayerCard there. PrepareOpponentProfile passes its internal 0x70-byte profile at owner+8 to InvokePanelCallback, which calls the exact +0x90 function slot and discards the result. The pointer is borrowed during the call; no allocation or transfer is performed by the setter/dispatcher.

The existing C lives under `eu/libs/nns/snd/calls/` and labels the field NNSSndArc.loadBlockSize. Its comment claiming NNS_SndArcSetLoadBlockSize is false for this owner. The plan includes a precise comment correction while retaining the existing offset-compatible body and bytes. Full type/prototype repair is deferred to a separate change; a porter must reconstruct this as wireless connection state and a function-pointer slot, not copy the legacy sound-archive type.

## Progress and display-effect operations

ApplyWirelessCardProgressBonus evaluates query8+1 and the selected card matching-slot count before testing query5. When that guard is clear, command 0x80000009 writes the sum through StampContextDateTime, which upper-clamps progress to 100, stores the 7-bit progress field and samples/writes RTC fields. Do not move the guard before matching-slot work or infer gameplay meaning for the guard flag.

WirelessMenu_State5DisplayEffectsNoop is called only by the display-effects updater when menu state==5. It performs no drawing, state change or completion signal. The updater still runs its independent timer/background/highlight branches.

## Per-function behavior and limits

### `Ov013Panel_LeaveSaveStateNoop`

Empty exit callback for panel menu state index 5, proven by native ROM table base 0x2074bbc with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `Ov013Panel_LeavePlayerCardTransitionNoop`

Empty exit callback for panel menu state index 8, proven by native ROM table base 0x2074bbc with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `Ov013Panel_LeaveHeldScrollTowardStartNoop`

Empty exit callback for panel menu state index 9, proven by native ROM table base 0x2074bbc with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `Ov013Panel_LeaveHeldScrollTowardEndNoop`

Empty exit callback for panel menu state index 10, proven by native ROM table base 0x2074bbc with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `Ov013Scroll_Phase0UpdateNoop`

Empty update callback for scroll phase index 0, proven by native ROM table base 0x2074b34 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `Ov013Scroll_LeavePhase0Noop`

Empty exit callback for scroll phase index 0, proven by native ROM table base 0x2074b34 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `Ov013Scroll_LeaveUpNoop`

Empty exit callback for scroll phase index 1, proven by native ROM table base 0x2074b34 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `Ov013Scroll_LeaveDownNoop`

Empty exit callback for scroll phase index 2, proven by native ROM table base 0x2074b34 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `Ov013MenuTouchEventNoop`

Panel init passes this empty function to InitMenuCursorState. The helper stores it in the first word of the 0x2c-byte menu-touch owner; UpdateMenuTouch invokes callback(event,&point,0) for event masks 1/2/4/8.

No touch work or return semantics. Actual incoming R0 is event code, not a cursor pointer; use the real touch dispatcher if later recovering its prototype.

### `Ov013SubWidget19ConfirmNoop`

Initializer calls ResolveEntryStoreWord(root,widgetId,callback), which resolves the exact sub-root widget and stores callback at widget+a8h. MoveFocusByDpad invokes that nonnull confirm slot with the focused widget when keys&1. This callback itself is empty.

Do not replace registration with NULL or assign an accepted/handled return. Legacy alias StoreWordAt0x98 is false: real setter writes+a8h. Widget ID is the demonstrated identity, not a gameplay label.

### `Ov013SubWidget26ConfirmNoop`

Initializer calls ResolveEntryStoreWord(root,widgetId,callback), which resolves the exact sub-root widget and stores callback at widget+a8h. MoveFocusByDpad invokes that nonnull confirm slot with the focused widget when keys&1. This callback itself is empty.

Do not replace registration with NULL or assign an accepted/handled return. Legacy alias StoreWordAt0x98 is false: real setter writes+a8h. Widget ID is the demonstrated identity, not a gameplay label.

### `Ov013SubWidget27ConfirmNoop`

Initializer calls ResolveEntryStoreWord(root,widgetId,callback), which resolves the exact sub-root widget and stores callback at widget+a8h. MoveFocusByDpad invokes that nonnull confirm slot with the focused widget when keys&1. This callback itself is empty.

Do not replace registration with NULL or assign an accepted/handled return. Legacy alias StoreWordAt0x98 is false: real setter writes+a8h. Widget ID is the demonstrated identity, not a gameplay label.

### `Ov014Panel_LeaveOpenStateNoop`

Empty exit callback for record edit panel state index 0, proven by native ROM table base 0x206f8f8 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `Ov014Panel_EnterEditStateNoop`

Empty enter callback for record edit panel state index 1, proven by native ROM table base 0x206f8f8 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `Ov014Panel_LeaveEditStateNoop`

Empty exit callback for record edit panel state index 1, proven by native ROM table base 0x206f8f8 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `Ov014Panel_LeaveCloseStateNoop`

Empty exit callback for record edit panel state index 2, proven by native ROM table base 0x206f8f8 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `ApplyWirelessCardProgressBonus`

Computes current 7-bit progress(query8)+1+CountMatchingSlotIds(selectedCard). If query5 is clear, command80000009 passes this value to StampContextDateTime, which upper-clamps to 100 and writes progress plus RTC fields. Invoked by sharing and result entry.

Computation and slot-matching resource work precede query5 guard; do not reorder. No gameplay name for guardbit, ranking class or lower clamp is inferred; native calls/order remain.

### `WirelessMenu_LeaveState0Noop`

Empty exit callback for wireless menu state index 0, proven by native ROM table base 0x207e780 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessMenu_LeaveState1AndReleaseCursor`

Menu table exit callback for state 1. ARM call wrapper delegates to ReleaseMenuCursorState, which conditionally frees the global 0x2c-byte touch/cursor owner and clears its pointer.

No PXI initialization. Do not infer owned-pointer return from legacy void* declaration or propagated R0. Two exit addresses remain distinct; no null/lifetime changes.

### `WirelessMenu_LeaveOwnerProfileStateNoop`

Empty exit callback for wireless menu state index 2, proven by native ROM table base 0x207e780 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessMenu_LeaveState3AndReleaseCursor`

Menu table exit callback for state 3. ARM call wrapper delegates to ReleaseMenuCursorState, which conditionally frees the global 0x2c-byte touch/cursor owner and clears its pointer.

No PXI initialization. Do not infer owned-pointer return from legacy void* declaration or propagated R0. Two exit addresses remain distinct; no null/lifetime changes.

### `WirelessMenu_LeaveHeaderStateNoop`

Empty exit callback for wireless menu state index 4, proven by native ROM table base 0x207e780 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessSubWidget4ConfirmNoop`

Initializer calls ResolveEntryStoreWord(root,widgetId,callback), which resolves the exact sub-root widget and stores callback at widget+a8h. MoveFocusByDpad invokes that nonnull confirm slot with the focused widget when keys&1. This callback itself is empty.

Do not replace registration with NULL or assign an accepted/handled return. Legacy alias StoreWordAt0x98 is false: real setter writes+a8h. Widget ID is the demonstrated identity, not a gameplay label.

### `WirelessCardSlot1_SelectAndSlideOutWithSound`

Registered confirm callback for sub-widget 1. Native R0 widget reaches SelectWidgetAndSlideOut, whose kind 1/2/3 branch sets selectedCard 0/1/2, clears the corresponding flag, tweens the widget upward and sounds(2,8); wrapper then sounds(2,1).

Three identical bodies remain distinct registered identities. Legacy zero-argument declaration omits the real widget input; no source signature repair here. Keep both sound calls and order.

### `WirelessCardSlot2_SelectAndSlideOutWithSound`

Registered confirm callback for sub-widget 2. Native R0 widget reaches SelectWidgetAndSlideOut, whose kind 1/2/3 branch sets selectedCard 0/1/2, clears the corresponding flag, tweens the widget upward and sounds(2,8); wrapper then sounds(2,1).

Three identical bodies remain distinct registered identities. Legacy zero-argument declaration omits the real widget input; no source signature repair here. Keep both sound calls and order.

### `WirelessCardSlot3_SelectAndSlideOutWithSound`

Registered confirm callback for sub-widget 3. Native R0 widget reaches SelectWidgetAndSlideOut, whose kind 1/2/3 branch sets selectedCard 0/1/2, clears the corresponding flag, tweens the widget upward and sounds(2,8); wrapper then sounds(2,1).

Three identical bodies remain distinct registered identities. Legacy zero-argument declaration omits the real widget input; no source signature repair here. Keep both sound calls and order.

### `SetWirelessReceivedCardCallback`

Stores raw callback word at wireless-connection singleton 0207e964+90h. StartPlayerCardSharing passes AddReceivedPlayerCard; InvokePanelCallback reads/calls this exact slot with the prepared 0x70-byte profile from PrepareOpponentProfile. Native code is STR R0,[R1,#90h].

The setter now uses the canonical external 28-byte BSS prefix and the native connection-work offset directly. The former sound-archive private types and redundant shared-BSS definition have been removed; the active source is under ov015/calls. Its 20 native bytes and one relocation are unchanged. The remaining 24 bytes in the global prefix stay opaque. Callback dispatch discards its result; no BOOL or owned profile transfer is added.

### `WirelessConnection_LeaveState0Noop`

Empty exit callback for wireless connection state index 0, proven by native ROM table base 0x207e804 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessConnection_EnterState1Noop`

Empty enter callback for wireless connection state index 1, proven by native ROM table base 0x207e804 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessConnection_UpdateState1Noop`

Empty update callback for wireless connection state index 1, proven by native ROM table base 0x207e804 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessConnection_LeaveState1Noop`

Empty exit callback for wireless connection state index 1, proven by native ROM table base 0x207e804 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessConnection_EnterState3Noop`

Empty enter callback for wireless connection state index 3, proven by native ROM table base 0x207e804 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessConnection_LeaveState3Noop`

Empty exit callback for wireless connection state index 3, proven by native ROM table base 0x207e804 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessConnection_EnterState4Noop`

Empty enter callback for wireless connection state index 4, proven by native ROM table base 0x207e804 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessConnection_LeaveState4Noop`

Empty exit callback for wireless connection state index 4, proven by native ROM table base 0x207e804 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessConnection_EnterState5Noop`

Empty enter callback for wireless connection state index 5, proven by native ROM table base 0x207e804 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessConnection_LeaveState5Noop`

Empty exit callback for wireless connection state index 5, proven by native ROM table base 0x207e804 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessConnection_LeaveState6Noop`

Empty exit callback for wireless connection state index 6, proven by native ROM table base 0x207e804 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessConnection_LeaveState7Noop`

Empty exit callback for wireless connection state index 7, proven by native ROM table base 0x207e804 with 12-byte enter/update/exit records and its real dispatcher. Logical tables cross physical DATA fragments; source filename offsets do not define their base.

Preserve nonnull registration and distinct identity. ARM BX LR preserves incoming R0, whose value depends on the dispatcher; no object-pointer, BOOL, completion or additional cleanup result is promised. Numeric states carry no inferred gameplay meaning.

### `WirelessMenu_State5DisplayEffectsNoop`

Display-effects updater invokes this empty hook only when wireless menu state==5, before its independent connection timer/background/highlight branches.

No drawing or animation occurs here. Preserve the call/identity and avoid inferring board completion or flag changes from this hook.

## Reproducing the evidence

```powershell
Get-Content eu/src/overlays/ov013/calls/ChangePanelMenuState.c
Get-Content eu/src/overlays/ov013/calls/SetPanelPhase.c
Get-Content eu/src/overlays/ov014/calls/ChangePanelState.c
Get-Content eu/src/overlays/ov015/calls/SetWirelessMenuState.c
Get-Content eu/src/overlays/ov015/calls/SetWirelessConnectionState.c
Get-Content src/ov015/reviewed_helpers/InvokePanelCallback_02073598.c
Get-Content src/ov027/resource_container/MoveFocusByDpad_020b88c0.c
```


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov013/auto/Ov013Panel_LeaveSaveStateNoop.c Ov013Panel_LeaveSaveStateNoop
python tools/verify_idx.py src/overlays/ov013/auto/Ov013Panel_LeavePlayerCardTransitionNoop.c Ov013Panel_LeavePlayerCardTransitionNoop
python tools/verify_idx.py src/overlays/ov013/auto/Ov013Panel_LeaveHeldScrollTowardStartNoop.c Ov013Panel_LeaveHeldScrollTowardStartNoop
python tools/verify_idx.py src/overlays/ov013/auto/Ov013Panel_LeaveHeldScrollTowardEndNoop.c Ov013Panel_LeaveHeldScrollTowardEndNoop
python tools/verify_idx.py src/overlays/ov013/auto/Ov013Scroll_Phase0UpdateNoop.c Ov013Scroll_Phase0UpdateNoop
python tools/verify_idx.py src/overlays/ov013/auto/Ov013Scroll_LeavePhase0Noop.c Ov013Scroll_LeavePhase0Noop
python tools/verify_idx.py src/overlays/ov013/auto/Ov013Scroll_LeaveUpNoop.c Ov013Scroll_LeaveUpNoop
python tools/verify_idx.py src/overlays/ov013/auto/Ov013Scroll_LeaveDownNoop.c Ov013Scroll_LeaveDownNoop
python tools/verify_idx.py src/overlays/ov013/auto/Ov013MenuTouchEventNoop.c Ov013MenuTouchEventNoop
python tools/verify_idx.py src/overlays/ov013/auto/Ov013SubWidget19ConfirmNoop.c Ov013SubWidget19ConfirmNoop
python tools/verify_idx.py src/overlays/ov013/auto/Ov013SubWidget26ConfirmNoop.c Ov013SubWidget26ConfirmNoop
python tools/verify_idx.py src/overlays/ov013/auto/Ov013SubWidget27ConfirmNoop.c Ov013SubWidget27ConfirmNoop
python tools/verify_idx.py src/overlays/ov014/auto/Ov014Panel_LeaveOpenStateNoop.c Ov014Panel_LeaveOpenStateNoop
python tools/verify_idx.py src/overlays/ov014/auto/Ov014Panel_EnterEditStateNoop.c Ov014Panel_EnterEditStateNoop
python tools/verify_idx.py src/overlays/ov014/auto/Ov014Panel_LeaveEditStateNoop.c Ov014Panel_LeaveEditStateNoop
python tools/verify_idx.py src/overlays/ov014/auto/Ov014Panel_LeaveCloseStateNoop.c Ov014Panel_LeaveCloseStateNoop
python tools/verify_idx.py src/overlays/ov015/calls/ApplyWirelessCardProgressBonus.c ApplyWirelessCardProgressBonus
python tools/verify_idx.py src/overlays/ov015/auto/WirelessMenu_LeaveState0Noop.c WirelessMenu_LeaveState0Noop
python tools/verify_idx.py src/overlays/ov015/calls/WirelessMenu_LeaveState1AndReleaseCursor.c WirelessMenu_LeaveState1AndReleaseCursor
python tools/verify_idx.py src/overlays/ov015/auto/WirelessMenu_LeaveOwnerProfileStateNoop.c WirelessMenu_LeaveOwnerProfileStateNoop
python tools/verify_idx.py src/overlays/ov015/calls/WirelessMenu_LeaveState3AndReleaseCursor.c WirelessMenu_LeaveState3AndReleaseCursor
python tools/verify_idx.py src/overlays/ov015/auto/WirelessMenu_LeaveHeaderStateNoop.c WirelessMenu_LeaveHeaderStateNoop
python tools/verify_idx.py src/overlays/ov015/auto/WirelessSubWidget4ConfirmNoop.c WirelessSubWidget4ConfirmNoop
python tools/verify_idx.py src/overlays/ov015/calls/WirelessCardSlot1_SelectAndSlideOutWithSound.c WirelessCardSlot1_SelectAndSlideOutWithSound
python tools/verify_idx.py src/overlays/ov015/calls/WirelessCardSlot2_SelectAndSlideOutWithSound.c WirelessCardSlot2_SelectAndSlideOutWithSound
python tools/verify_idx.py src/overlays/ov015/calls/WirelessCardSlot3_SelectAndSlideOutWithSound.c WirelessCardSlot3_SelectAndSlideOutWithSound
python tools/verify_idx.py src/overlays/ov015/calls/SetWirelessReceivedCardCallback.c SetWirelessReceivedCardCallback
python tools/verify_idx.py src/overlays/ov015/auto/WirelessConnection_LeaveState0Noop.c WirelessConnection_LeaveState0Noop
python tools/verify_idx.py src/overlays/ov015/auto/WirelessConnection_EnterState1Noop.c WirelessConnection_EnterState1Noop
python tools/verify_idx.py src/overlays/ov015/auto/WirelessConnection_UpdateState1Noop.c WirelessConnection_UpdateState1Noop
python tools/verify_idx.py src/overlays/ov015/auto/WirelessConnection_LeaveState1Noop.c WirelessConnection_LeaveState1Noop
python tools/verify_idx.py src/overlays/ov015/auto/WirelessConnection_EnterState3Noop.c WirelessConnection_EnterState3Noop
python tools/verify_idx.py src/overlays/ov015/auto/WirelessConnection_LeaveState3Noop.c WirelessConnection_LeaveState3Noop
python tools/verify_idx.py src/overlays/ov015/auto/WirelessConnection_EnterState4Noop.c WirelessConnection_EnterState4Noop
python tools/verify_idx.py src/overlays/ov015/auto/WirelessConnection_LeaveState4Noop.c WirelessConnection_LeaveState4Noop
python tools/verify_idx.py src/overlays/ov015/auto/WirelessConnection_EnterState5Noop.c WirelessConnection_EnterState5Noop
python tools/verify_idx.py src/overlays/ov015/auto/WirelessConnection_LeaveState5Noop.c WirelessConnection_LeaveState5Noop
python tools/verify_idx.py src/overlays/ov015/auto/WirelessConnection_LeaveState6Noop.c WirelessConnection_LeaveState6Noop
python tools/verify_idx.py src/overlays/ov015/auto/WirelessConnection_LeaveState7Noop.c WirelessConnection_LeaveState7Noop
python tools/verify_idx.py src/overlays/ov015/auto/WirelessMenu_State5DisplayEffectsNoop.c WirelessMenu_State5DisplayEffectsNoop
bash tools/gate.sh
```
