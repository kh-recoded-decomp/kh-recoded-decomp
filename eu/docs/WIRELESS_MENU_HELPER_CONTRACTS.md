# Wireless menu, board and helper contracts

This block describes 43 native EU overlay 015 ARM entrypoints: 34 menu/panel
functions and nine wireless-helper functions. The names are descriptive and
follow the actual owner, callback registration, API command or consumer. They
do not claim original source spelling. The validation section records the official byte-exact
checks after integration.

The source column identifies the accepted EU wrapper paths. Interpret shared
included bodies through their EU aliases. Inherited SDK template names, erased
callback prototypes and reference-region addresses do not establish the EU
contract. No structure layout or callback type changes are part of this block.

## Four distinct owners and asynchronous boundaries

| Owner | Demonstrated role |
|---|---|
| `data_ov015_0207e960` | Main wireless menu work, signed menu state and menu/widget/resource effects |
| `data_ov015_0207e964` | Separate connection-menu state object |
| `data_ov015_020812e0` | Board/panel work: modes, sequence, resources and buffered touch |
| `gWhState` and the SDK request/callback objects | Wireless-helper state and asynchronous WM operations |

The main-menu table has init/update/exit views at EU 0x0207e780/0x0207e784/
0x0207e788 with a 12-byte stride. The connection-menu table has the corresponding
views at 0x0207e804/0x0207e808/0x0207e80c. Each is one interleaved eight-state
table, rather than three independently bounded arrays. The state setters call
the old exit unless its signed state is -1, store the new byte, then invoke the
new init. They add no callback null or state-range validation.

Connection-menu state is distinct from the wireless helper's system state.
For example, helper state 3 is used while requests are pending. A test that
helper state differs from 3 does not prove idle or successful connection.
WM request return 2 is accepted as queued submission in these wrappers;
callback error halfword +2 is checked later. Submission and completion are
different results, and individual immediate failures have different state/reset
policies. Preserve those differences rather than routing every failure to one
new generic reset path.

## Main wireless menu and widgets

Menu +0xe0 masks 0x10 and 0x20 independently guard MAIN and SUB widget resources.
Releasing those groups destroys their nested widgets/buffers without freeing
the outer wireless menu. Main group resources begin at +0x5ac and widgets at
+0x644; SUB resources begin at +0x5f8 and widgets at +0x6ac0. The updater's
state/flag gates are distinct from those ownership bits.

Owner profile text comes from the cached OS owner nickname/message getters in
ov002, which return borrowed UTF-16 pointers. Those native pointers are not
integers or newly owned text buffers. Text IDs, widget IDs and six page selector
values remain numeric wherever artwork or localized text has not proved a
business meaning. In particular, widget setup alone does not establish a
share-specific operation, so the name is InitWirelessMenuChoiceWidgets.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Evidence |
|---|---|---|---|---|---|
| ov015:0x0206c4f0 | ARM | `UpdateWirelessMenu` | `src/overlays/ov015/calls/UpdateWirelessMenu.c` | `int(void)`. Updates RTC date, optional opponent/connect state, dispatches current menu update callback, updates effects/widgets as gated by flags, returns exit/result byte1. Boundary: Do not trust current PanelStateCallbacks field names or partial array sizes. Retain exact gating: sub widgets skipped in state 5, bob skipped in0/1/7. | State table aliases resolve by EU addresses to init+0/update+4/exit+8, stride 12; main context is7e960. |
| ov015:0x0206c5dc | ARM | `UpdateWirelessMenuDisplayEffects` | `src/overlays/ov015/calls/UpdateWirelessMenuDisplayEffects.c` | `void(void)`. For state 5 calls empty75338; conditionally updates connection timer, background scrolling/animation and highlight palette. Boundary: No generalized render loop claim; this is the separately gated effect callback. | Concrete flag bits e2.4/e1.7/e1.3/e2.1 and actual callees. |
| ov015:0x0206c660 | ARM | `ReleaseWirelessMenuWidgetGroups` | `src/overlays/ov015/calls/ReleaseWirelessMenuWidgetGroups.c` | `void(void)`. Calls main then sub widget-resource release helpers. Boundary: Inherited int/num/denom signature is misleading; last callee is void and no meaningful result is consumed by documented ownership flow. | Original disassembly consists of two BL then return. |
| ov015:0x0206c670 | ARM | `ReleaseWirelessMenuMainWidgetGroup` | `src/overlays/ov015/calls/ReleaseWirelessMenuMainWidgetGroup.c` | `void(void)`. If e0 bit 4 set, clears it, frees resource group5ac and destroys widgets644. Boundary: Does not free outer wireless menu; repeated call with cleared mask does nothing. | SetupPanelGraphics names mainLoaded/subLoaded masks4/5; ov0277e1c sweeps and frees resource buffers+c/+10/+14. |
| ov015:0x0206c6bc | ARM | `ReleaseWirelessMenuSubWidgetGroup` | `src/overlays/ov015/calls/ReleaseWirelessMenuSubWidgetGroup.c` | `void(void)`. If e0 bit 5 set, clears it, frees resource group5f8 and destroys widgets6ac0. Boundary: Preserve per-group flags and ownership; do not conflate two roots. | Parallel main helper and SetupPanelGraphics subLoaded mask. |
| ov015:0x0206e658 | ARM | `SetupWirelessSelectionSlotFromWidget` | `src/overlays/ov015/calls/SetupWirelessSelectionSlotFromWidget.c` | `void(int slotIndex)`. Looks up widget id from slot table, resolves combinedXY position, shows it, clears active bits, applies alternate values, initializes selection slot at captured position. Boundary: No slot bounds guard; position is captured before widget mutation. | WirelessMenuContext.h/WidgetRecordOps.h typed real operations. |
| ov015:0x0206edc8 | ARM | `DrawWirelessOwnerProfileText` | `src/overlays/ov015/calls/DrawWirelessOwnerProfileText.c` | `void(void)`. Clears main text layers, draws context choice name, cached owner nickname/message, choice-index label positioned by measured height. Boundary: Nickname/message are UTF16 pointers despite old int locals; message copy newline/max-length effects retained. | GetCachedOwnerNickname/GetCachedOwnerMessage proven via OS owner data initialization in ov002. |
| ov015:0x0206eefc | ARM | `DrawWirelessPanelChoiceLabels` | `src/overlays/ov015/calls/DrawWirelessPanelChoiceLabels.c` | `void(void)`. Clears sub text layer0, chooses text25/26 from context flags0..2, centers labels3c/3d at two X centers. Boundary: Label business wording is not recovered; do not invent yes/no/connect/disconnect text. | Direct text ids, font measure and ActivatePanelSlotCD calls. |
| ov015:0x02070af8 | ARM | `SetWirelessMenuState` | `src/overlays/ov015/calls/SetWirelessMenuState.c` | `void(s8 nextState)`. If old signedstate!=-1, invokes old exit callback; stores next byte, invokes new init callback. Boundary: Callbacks are not NULL-checked. Inherited three independently declared DATA arrays are views into one8-state interleaved table, not true array bounds. | EU symbols init207e780/update207e784/exit207e788, stride 12. Original disassembly confirms callback columns and signed state. |
| ov015:0x02070fb4 | ARM | `InitWirelessMenuOwnerProfileView` | `src/overlays/ov015/calls/InitWirelessMenuOwnerProfileView.c` | `void(void)`. Initializes panel screen graphics, draws owner profile text, clears panelActive/exitRequest fields. Boundary: Do not call this state 1 from raw array offset; true init base precedes exit base by 8 bytes. | State 2 init slot per table address mapping; calls owner-profile text helper. |
| ov015:0x020716f8 | ARM | `InitWirelessMenuChoiceWidgets` | `src/overlays/ov015/calls/InitWirelessMenuChoiceWidgets.c` | `void(void)`. Shows and configures choice widgets 4/7/8, focuses widget 8, captures selection, draws labels, installs the selection-sound callback and resets widget 9 animation. Boundary: Widget identity remains numeric where artwork meaning unproven; preserve focus/value capture order. | Concrete widget API calls and later choice/UI handlers. |
| ov015:0x02071a78 | ARM | `ClearOv002PanelModeDirtyFromWireless` | `src/overlays/ov015/calls/ClearOv002PanelModeDirtyFromWireless.c` | `void(void)`. Calls ov002 panel mode-dirty setter with 0. Boundary: Legacy pointer return is incidental; logicalvoid wrapper. | ov00262014 assigns bit 1 from lowbit of input; no other effect. |
| ov015:0x02071a88 | ARM | `DrawWirelessPanelHeaderAndEnterState1` | `src/overlays/ov015/calls/DrawWirelessPanelHeaderAndEnterState1.c` | `void(void)`. Sets up panel graphics, draws centered label/info text, sets ov002 modeDirty from 1, transitions menu state 1. Boundary: State 1 actual enum role not renamed beyond table evidence. | Concrete setup/draw calls and state setter. |
| ov015:0x02071bec | ARM | `FinishWirelessBoardViewWhenIntroEnds` | `src/overlays/ov015/calls/FinishWirelessBoardViewWhenIntroEnds.c` | `void(void)`. Polls board-intro update; while nonzero returns. On completion releases workbuffer, clears4effect flags, initializes sub graphics, clears subtext0, transitions menu2. Boundary: Retain full wait behavior and redraw/reset order; completion is intro/minigame state machine, not wireless connection success. | RunPanelIntroSequence returnsFALSE after fade-out reaches step300; UpdateWirelessBoardIntro also ticks board. |
| ov015:0x02071e48 | ARM | `InitWirelessPanelConfirmWidgets` | `src/overlays/ov015/calls/InitWirelessPanelConfirmWidgets.c` | `void(void)`. Enables all sub display layers, draws label70, initializes cursor, clears active bits of widgets b/1e/1f/20/21/9/11, resets widget11 frame, plays sound2,3. Boundary: Do not interpret specific text70 or widget art as known business choice. | State 7 init from table mapping; direct MMIO and widget operations. |
| ov015:0x02072758 | ARM | `PositionWirelessPanelSelectionMarker` | `src/overlays/ov015/calls/PositionWirelessPanelSelectionMarker.c` | `void(WidgetPositionRecord *selected)`. Sets e0bit1, resolves supplied widget position, shifts X by-0x2c000, places widgetb, focuses9, plays2,1. Boundary: Keep fx32 shift and supplied widget identity; no arbitrary pointer cast claim. | Direct widget APIs; argument supplied by selection callback path. |
| ov015:0x02072830 | ARM | `SelectPreviousWirelessPanelSubpageWrapper` | `src/overlays/ov015/calls/SelectPreviousWirelessPanelSubpageWrapper.c` | `void(void)`. Calls existing StepPanelCursorBlink, whose actual body decrements signed choiceIndex+3, wraps by choice limit, redraws info and marker/focus. Boundary: Related target name should be corrected to SelectPreviousWirelessPanelSubpage; do not propagate false blink label. | SetupPanelGraphics installs this callback. Real StepPanelCursorBlink body has no timer/blink operation. |
| ov015:0x0207283c | ARM | `SelectNextWirelessPanelSubpageWrapper` | `src/overlays/ov015/calls/SelectNextWirelessPanelSubpageWrapper.c` | `void(void)`. Forwards to increment choiceIndex+3 with limit wrap and widget4 marker/focus refresh. Boundary: Old parameterless/pointer return is legacy; target logicalvoid. | SetupPanelGraphics callback and actual SelectNextPanelSubpage body. |
| ov015:0x02072848 | ARM | `SelectPreviousWirelessPanelPageWrapper` | `src/overlays/ov015/calls/SelectPreviousWirelessPanelPageWrapper.c` | `void(void)`. Forwards to decrement page/choiceType+2, wrap0..5, update widget10 and focus/marker. Boundary: Page role is concrete selector6values; no fabricated item categories. | SetupPanelGraphics callback and actual SelectPrevPanelPage body. |
| ov015:0x02072854 | ARM | `SelectNextWirelessPanelPageWrapper` | `src/overlays/ov015/calls/SelectNextWirelessPanelPageWrapper.c` | `void(void)`. Forwards to increment page/choiceType+2 modulo6, update widget10 and focus/marker. Boundary: Preserve signedbyte narrowing beforewrap and node update order. | SetupPanelGraphics callback and actual SelectNextPanelPage body. |

The four page/subpage wrappers have no logical inputs or returned allocation.
One inherited target, StepPanelCursorBlink, actually decrements a choice index
with wrapping/redraw and contains no blink-timer update. The wrapper names here
describe that operation without propagating the old label. Similar inherited
pointer returns from void setup/release functions do not establish owned
resource results.

## Connection-menu state

These functions operate on the separate +7e964 state object or delegate to the
helper. Finalization can issue further asynchronous work; it does not prove that
the state object has been freed or that disconnection has completed.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Evidence |
|---|---|---|---|---|---|
| ov015:0x02072cb4 | ARM | `ReturnWirelessConnectionToState2IfInRange3To7` | `src/overlays/ov015/calls/ReturnWirelessConnectionToState2IfInRange3To7.c` | `void(void)`. If signedstate byte is3..7 inclusive, calls connection-state setter2. Boundary: Other states including-1 unchanged. No full reset/finalization guarantee. | Exact unsigned-wrapped range test reduces to these5states. |
| ov015:0x02072ee4 | ARM | `SetWirelessConnectionState` | `src/overlays/ov015/calls/SetWirelessConnectionState.c` | `void(s8 nextState)`. Invokes old exit callback unless oldstate-1, writes nextbyte, invokes new init callback. Boundary: Separate7e964 state object from menu7e960. Partial DATA array sizes do not bound full interleaved8state table. | EU symbols init207e804/update207e808/exit207e80c, stride 12. Original disassembly parallels menu setter. |
| ov015:0x02072f7c | ARM | `EnterWirelessConnectionState3UnlessHelperState3` | `src/overlays/ov015/calls/EnterWirelessConnectionState3UnlessHelperState3.c` | `void(void)`. Checks helper system state; while3 returns, otherwise changes connection state 3. Boundary: Do not call all non3states idle or successful; can include errors. | GetPanelTransitionMode real helper state getter; asynchronous WEP/MP helpers write helperstate3 before requests. |
| ov015:0x02072fa8 | ARM | `FinalizeWirelessConnectionWrapper` | `src/overlays/ov015/calls/FinalizeWirelessConnectionWrapper.c` | `void(void)`. Calls WH_Finalize. Boundary: Do not assert outer state object destruction or synchronous completion. Legacy pointer result needs actual caller contract if exposed. | Connection state table installs at one exit column; real WH_Finalize handles end-child/scan/keysharing/reset paths. |

## Board/panel work and buffered touch

Board mode +8 and pending mode +0x0c are separate words. The sequence-playing
byte +0x5f controls one specific sound sequence, without proving its theme or
loop duration. Releasing widget/resource groups leaves this outer allocation
and global pointer intact.

Touch edges use buffered sample count at +0x38 and the previous sample's
negative-coordinate sentinel. A just-pressed edge is not an offscreen test or
release event. The A/B/touch aggregate preserves masks 1/2 and this touch-down
predicate without assigning confirm/cancel meaning to every consumer.

Descriptor formatting produces UTF-16. The initial copy's bound does not prove
a bound for the appended formatted portion. Generic table/descriptor records
are not renamed as particular game-item categories without their formats.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Evidence |
|---|---|---|---|---|---|
| ov015:0x02075320 | ARM | `UpdateWirelessBoardIntro` | `src/overlays/ov015/calls/UpdateWirelessBoardIntro.c` | `BOOL(void)`. Calls RunPanelIntroSequence, ticks UpdatePanelBoard unconditionally, returns original intro result. Boundary: Do not skip boardtick on completion/fade frames. | RunPanelIntroSequence step/fade/input/minigame state machine read; caller71bec waits while resultnonzero. |
| ov015:0x0207634c | ARM | `ReleaseWirelessPanelResources` | `src/overlays/ov015/calls/ReleaseWirelessPanelResources.c` | `void(void)`. Destroys widget root160, frees packed resource65e0, destroys3owned object lists65ec/65f0/65f4. Boundary: Retains outer panel allocation and globalpointer; no general freeall claim. | Paired SetupPanelBoard resources and helper bodies. |
| ov015:0x02077904 | ARM | `StartWirelessPanelSequenceIfStopped` | `src/overlays/ov015/calls/StartWirelessPanelSequenceIfStopped.c` | `void(void)`. If sequencePlaying byte5f clear, plays2,c and sets1; otherwise no-op. Boundary: No assumption about sound meaning or loop duration. | StopPanelSequence checks samebyte, stops(player2,seqArcNo c,fade0) and clearsflag. |
| ov015:0x02077978 | ARM | `SetWirelessPanelModeAndStopSequence` | `src/overlays/ov015/calls/SetWirelessPanelModeAndStopSequence.c` | `void(u32 mode)`. Stores mode+8, stops matchingsequence, clears workflags+18 mask 10000. Boundary: Does not write pendingMode+c. | Ov015PanelWork.h identifies mode+8; real StopPanelSequence body. |
| ov015:0x020779a4 | ARM | `SetWirelessPanelModeAndPendingMode` | `src/overlays/ov015/calls/SetWirelessPanelModeAndPendingMode.c` | `void(u32 mode, u32 pendingMode)`. Calls mode setter/stop then stores pendingMode+c. Boundary: Full call side effects preserved. | Ov015PanelWork.h fields mode 8/pendingModec. |
| ov015:0x02078554 | ARM | `FormatWirelessPanelDescriptorText` | `src/overlays/ov015/calls/FormatWirelessPanelDescriptorText.c` | `u16 *(u16 *out, const PanelDescriptor *desc)`. Kind 0 copies recordA text with bound63, optionally appends format37/count; other kind delegates tableB fieldcopy; returns outputpointer. Boundary: Output UTF16, format destination starts at length*2. Do not infer game-item category or bound totalappend from first copy bound. | Real descriptor kind/id/count accesses, record-slot acquire/release and packed message lookup. |
| ov015:0x02078918 | ARM | `IsWirelessPanelAOrBOrNewTouchPressed` | `src/overlays/ov015/calls/IsWirelessPanelAOrBOrNewTouchPressed.c` | `BOOL(void)`. Returns normalizedOR of input mask 1, mask 2, and just-pressed touch predicate. Boundary: No cancel/confirm semantics inferred from which button handler consumes it. | IsGlobalBit0Set and IsButtonBPressed both read same input word with masks1/2; UpdateWirelessPanelTouch establishes touch edge. |
| ov015:0x02078f18 | ARM | `ConfigureWirelessPanelSubBg2Control` | `src/overlays/ov015/calls/ConfigureWirelessPanelSubBg2Control.c` | `u32(void)`. Replaces subBG2CNT at 0400100c with(old&0x43)\|0x94 and returns written value. Boundary: Preserves priority/mosaic-selectedbits only; do not replace with guessed standardBG preset. | Exact original body/MMIO address. |
| ov015:0x020790c0 | ARM | `IsWirelessPanelTouchJustPressed` | `src/overlays/ov015/calls/IsWirelessPanelTouchJustPressed.c` | `BOOL(void)`. True when current sampleCount>0 and previousTouch has negativeX orY. Boundary: This is touch-down edge, not touch-release or spatial offscreen test. Existing IsCursorOffscreen name hides previousTouch sentinel logic. | UpdateWirelessPanelTouch saves last previous sample when oldcount>0, otherwise(-1,-1), then writes new sample count. |
| ov015:0x020790e8 | ARM | `HasWirelessPanelTouchSamples` | `src/overlays/ov015/calls/HasWirelessPanelTouchSamples.c` | `BOOL(void)`. Returns signed16 touchSampleCount+38 >0. Boundary: No predicate for hardware touch alone; exact buffered count. | Ov015PanelWork.h and UpdateWirelessPanelTouch writer. |

## Wireless requests and completion callbacks

The parent WEP generator is at helper offset +0x34 and the child generator at
+0x1c, established by their setup/request paths. A misleading local
childKeyGenerator label in the parent path must not merge their roles. The
parent completion's existing successor label WH_StartScanStep actually calls
WMi_StartParentEx; its behavior supplies the parent identity here.

The port-13 sharing wrapper calls WM_StartDataSharing with its existing global
information and native arguments `(info,13,0xffff,2,1)`. It interprets the immediate
zero status as success, unlike the queued-return-2 request wrappers. This path
sets helper state 6 and records failure without additionally forcing state 9.

The project SDK enum identifies request 9 as END_PARENT and 0x0b as END_SCAN.
The callbacks retained under misleading UI-related names still belong to those
wireless request chains. No key-buffer, callback or sharing-info ownership is
transferred by these wrappers; the required asynchronous lifetime remains part
of the existing helper/SDK protocol.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Evidence |
|---|---|---|---|---|---|
| ov015:0x02073894 | ARM | `WH_RequestParentWepKey` | `src/overlays/ov015/calls/WH_RequestParentWepKey.c` | `BOOL(void)`. Sets helperstate3, uses generator+34 with keybuffer/parentinfo, requests WM_SetWEPKey; returnsTRUE only queued2, otherwise storeserror and setsstate9. Boundary: Inherited local childKeyGenerator label is wrong. No NULL guard; caller checks generator. | WH_StateOutSetParentParam identifies+34 as parentKeyGenerator; child generator is+1c in SetChildWepKey. |
| ov015:0x020738f8 | ARM | `WH_OnParentWepKeySet` | `src/overlays/ov015/calls/WH_OnParentWepKeySet.c` | `void(WMCallback *callback)`. On callback error storescode and entersstate9; on success requests startparent, state 9 if request fails. Boundary: Related StartScanStep label is wrong; imported helper return ABI must be preserved. | WH_StateOutSetParentParam→parentkey request installs this; WH_StartScanStep actually calls WMi_StartParentEx(callback,1). |
| ov015:0x02073c48 | ARM | `WH_StartPort13DataSharing` | `src/overlays/ov015/calls/WH_StartPort13DataSharing.c` | `BOOL(void)`. Enters helperstate6, calls data-sharing wrapper with globalinfo/port13; successraw0→TRUE, failure records error→FALSE. Boundary: The native caller tests the SDK status result; legacy void declarations do not establish that ABI. Keep original error-state behavior (does not force9 here). | Main func02012284 calls WM_StartDataSharing(info,port,ffff,2,1). WirelessMPHelper.h defines actual SDK call. |
| ov015:0x02073cbc | ARM | `WH_RequestEndMP` | `src/overlays/ov015/calls/WH_RequestEndMP.c` | `BOOL(void)`. Enters helperstate3, requests WM_EndMP(OnEndMP), acceptsqueued2 asTRUE else storeserror and returnsFALSE. Boundary: Submission success not completion; no forcedstate9 on immediate failure. | Actual SDK WM_EndMP call and callback installed. |
| ov015:0x02073cec | ARM | `WH_OnEndMP` | `src/overlays/ov015/calls/WH_OnEndMP.c` | `void(WMCallback *callback)`. Callback error records error and resets; success requests endparent, resets if submissionfails. Boundary: Reset fallback occurs on botherror/nextrequestfailure; no full disconnect alias. | Callback installed by WH_RequestEndMP; successor73d1c sends command9. |
| ov015:0x02073d1c | ARM | `WH_RequestEndParent` | `src/overlays/ov015/calls/WH_RequestEndParent.c` | `BOOL(void)`. Submits WM command9 with HandlePanelPromptSelection callback; queued2→TRUE else storeserror/FALSE. Boundary: Existing callback HandlePanelPromptSelection is wireless endparent callback, not UI prompt; related correction recorded separately. | include/nitro/wm.h enum identifies9 as WM_APIID_END_PARENT; RunTransitionSlot9 checks parentstate7 then submits9. |
| ov015:0x0207414c | ARM | `WH_RequestEndScan` | `src/overlays/ov015/calls/WH_RequestEndScan.c` | `BOOL(void)`. Submits WM command0xb with OnWirelessScanEnded callback; queued2→TRUE else storeserror/FALSE. Boundary: Submission/completion distinct; original callback handles subsequent auto-connect. | WM enum identifies0xb as END_SCAN; RunTransitionSlotB checks scanstate5 and submits0xb. |
| ov015:0x02074250 | ARM | `WH_OnChildWepKeySet` | `src/overlays/ov015/calls/WH_OnChildWepKeySet.c` | `void(WMCallback *callback)`. On callback error storescode/enters9; otherwise startswirelesschild, enters9 if requestfails. Boundary: Distinct from parent callback738f8; do not mergebecause similar error skeleton. | SetChildWepKey generator+1c installs thiscallback; StartWirelessChild real successor. |
| ov015:0x02074ce0 | ARM | `WH_TerminateOnCallbackError8` | `src/overlays/ov015/calls/WH_TerminateOnCallbackError8.c` | `void(WMCallback *callback)`. If callback16biterror+2 equals8, sets helperstate9 then calls OS_Terminate; otherwise no-op. Boundary: Error8 descriptive SDK label not claimed; no action on other codes. | Exactbody/callback error prefix convention used throughout wireless helpers. |

## Evidence and port boundaries

Every row carries a specific writer, callback or command-consumer check in
addition to its body. The listed bodies and EU aliases preserve the implementation evidence;
the two menu callback-column mappings and raw status/return distinctions were
also checked against native instructions during review. SDK command identities
come from the repository's own WM declarations and request bodies, rather than
from the misleading local helper names.

Partial local context views and independently declared DATA columns do not prove
complete allocations or capacities. Preserve signed-byte states, callback
order, source/data lifetime, UTF-16 pointer returns, widget position capture
before mutation, raw MMIO result words and exact error fallbacks. No wrapper
adds a general allocation-success, valid-state or live-handle guarantee.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`. All 43 entrypoints retain ARM mode:

```sh
python tools/verify_idx.py src/overlays/ov015/calls/UpdateWirelessMenu.c UpdateWirelessMenu
python tools/verify_idx.py src/overlays/ov015/calls/UpdateWirelessMenuDisplayEffects.c UpdateWirelessMenuDisplayEffects
python tools/verify_idx.py src/overlays/ov015/calls/ReleaseWirelessMenuWidgetGroups.c ReleaseWirelessMenuWidgetGroups
python tools/verify_idx.py src/overlays/ov015/calls/ReleaseWirelessMenuMainWidgetGroup.c ReleaseWirelessMenuMainWidgetGroup
python tools/verify_idx.py src/overlays/ov015/calls/ReleaseWirelessMenuSubWidgetGroup.c ReleaseWirelessMenuSubWidgetGroup
python tools/verify_idx.py src/overlays/ov015/calls/SetupWirelessSelectionSlotFromWidget.c SetupWirelessSelectionSlotFromWidget
python tools/verify_idx.py src/overlays/ov015/calls/DrawWirelessOwnerProfileText.c DrawWirelessOwnerProfileText
python tools/verify_idx.py src/overlays/ov015/calls/DrawWirelessPanelChoiceLabels.c DrawWirelessPanelChoiceLabels
python tools/verify_idx.py src/overlays/ov015/calls/SetWirelessMenuState.c SetWirelessMenuState
python tools/verify_idx.py src/overlays/ov015/calls/InitWirelessMenuOwnerProfileView.c InitWirelessMenuOwnerProfileView
python tools/verify_idx.py src/overlays/ov015/calls/InitWirelessMenuChoiceWidgets.c InitWirelessMenuChoiceWidgets
python tools/verify_idx.py src/overlays/ov015/calls/ClearOv002PanelModeDirtyFromWireless.c ClearOv002PanelModeDirtyFromWireless
python tools/verify_idx.py src/overlays/ov015/calls/DrawWirelessPanelHeaderAndEnterState1.c DrawWirelessPanelHeaderAndEnterState1
python tools/verify_idx.py src/overlays/ov015/calls/FinishWirelessBoardViewWhenIntroEnds.c FinishWirelessBoardViewWhenIntroEnds
python tools/verify_idx.py src/overlays/ov015/calls/InitWirelessPanelConfirmWidgets.c InitWirelessPanelConfirmWidgets
python tools/verify_idx.py src/overlays/ov015/calls/PositionWirelessPanelSelectionMarker.c PositionWirelessPanelSelectionMarker
python tools/verify_idx.py src/overlays/ov015/calls/SelectPreviousWirelessPanelSubpageWrapper.c SelectPreviousWirelessPanelSubpageWrapper
python tools/verify_idx.py src/overlays/ov015/calls/SelectNextWirelessPanelSubpageWrapper.c SelectNextWirelessPanelSubpageWrapper
python tools/verify_idx.py src/overlays/ov015/calls/SelectPreviousWirelessPanelPageWrapper.c SelectPreviousWirelessPanelPageWrapper
python tools/verify_idx.py src/overlays/ov015/calls/SelectNextWirelessPanelPageWrapper.c SelectNextWirelessPanelPageWrapper
python tools/verify_idx.py src/overlays/ov015/calls/ReturnWirelessConnectionToState2IfInRange3To7.c ReturnWirelessConnectionToState2IfInRange3To7
python tools/verify_idx.py src/overlays/ov015/calls/SetWirelessConnectionState.c SetWirelessConnectionState
python tools/verify_idx.py src/overlays/ov015/calls/EnterWirelessConnectionState3UnlessHelperState3.c EnterWirelessConnectionState3UnlessHelperState3
python tools/verify_idx.py src/overlays/ov015/calls/FinalizeWirelessConnectionWrapper.c FinalizeWirelessConnectionWrapper
python tools/verify_idx.py src/overlays/ov015/calls/UpdateWirelessBoardIntro.c UpdateWirelessBoardIntro
python tools/verify_idx.py src/overlays/ov015/calls/ReleaseWirelessPanelResources.c ReleaseWirelessPanelResources
python tools/verify_idx.py src/overlays/ov015/calls/StartWirelessPanelSequenceIfStopped.c StartWirelessPanelSequenceIfStopped
python tools/verify_idx.py src/overlays/ov015/calls/SetWirelessPanelModeAndStopSequence.c SetWirelessPanelModeAndStopSequence
python tools/verify_idx.py src/overlays/ov015/calls/SetWirelessPanelModeAndPendingMode.c SetWirelessPanelModeAndPendingMode
python tools/verify_idx.py src/overlays/ov015/calls/FormatWirelessPanelDescriptorText.c FormatWirelessPanelDescriptorText
python tools/verify_idx.py src/overlays/ov015/calls/IsWirelessPanelAOrBOrNewTouchPressed.c IsWirelessPanelAOrBOrNewTouchPressed
python tools/verify_idx.py src/overlays/ov015/calls/ConfigureWirelessPanelSubBg2Control.c ConfigureWirelessPanelSubBg2Control
python tools/verify_idx.py src/overlays/ov015/calls/IsWirelessPanelTouchJustPressed.c IsWirelessPanelTouchJustPressed
python tools/verify_idx.py src/overlays/ov015/calls/HasWirelessPanelTouchSamples.c HasWirelessPanelTouchSamples
python tools/verify_idx.py src/overlays/ov015/calls/WH_RequestParentWepKey.c WH_RequestParentWepKey
python tools/verify_idx.py src/overlays/ov015/calls/WH_OnParentWepKeySet.c WH_OnParentWepKeySet
python tools/verify_idx.py src/overlays/ov015/calls/WH_StartPort13DataSharing.c WH_StartPort13DataSharing
python tools/verify_idx.py src/overlays/ov015/calls/WH_RequestEndMP.c WH_RequestEndMP
python tools/verify_idx.py src/overlays/ov015/calls/WH_OnEndMP.c WH_OnEndMP
python tools/verify_idx.py src/overlays/ov015/calls/WH_RequestEndParent.c WH_RequestEndParent
python tools/verify_idx.py src/overlays/ov015/calls/WH_RequestEndScan.c WH_RequestEndScan
python tools/verify_idx.py src/overlays/ov015/calls/WH_OnChildWepKeySet.c WH_OnChildWepKeySet
python tools/verify_idx.py src/overlays/ov015/calls/WH_TerminateOnCallbackError8.c WH_TerminateOnCallbackError8
bash tools/gate.sh
```

All 43 official function checks pass. The fresh gate passes all 108 linked
modules; affected function bytes, resolved relocation targets/types and addends,
and all module hashes match the preserved baseline. Library receipts remain
current. No C/DATA reconstruction credit is added.
