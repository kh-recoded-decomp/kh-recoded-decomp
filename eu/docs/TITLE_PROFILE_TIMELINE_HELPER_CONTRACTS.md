# Title, profile-mode, packed progress and timeline helpers (ov000-004)

These 14 EU names follow state tables, native dispatch and paired consumers.
Two background-config hooks retain numeric names because no reader or invoker
of their copied pointer words has been established. Existing prototypes and
registered callbacks are preserved.

## Identity table

EU source paths are relative to `eu/`; evidence paths are relative to repository root. The plan records pre-change source/object hashes and original ROM bytes.

| EU identity / mode | Proposed name | EU source | Evidence |
|---|---|---|---|
| ov000:02063038 arm | `UpdateTitleFormatNoticeKeepState` | `src/overlays/ov000/auto/UpdateTitleFormatNoticeKeepState.c` | `eu/src/overlays/ov000/calls/UpdateTitlePanel.c` |
| ov000:02063040 arm | `LeaveTitleFormatNoticeNoop` | `src/overlays/ov000/auto/LeaveTitleFormatNoticeNoop.c` | `eu/src/overlays/ov000/calls/SwitchPanelState.c` |
| ov002:02062dd8 arm | `Ov002Panel_UpdateMode1Noop` | `src/overlays/ov002/auto/Ov002Panel_UpdateMode1Noop.c` | `src/ov002/panel_state/SwitchPanelMode_02062cb8.c` |
| ov002:02062ddc arm | `Ov002Panel_LeaveMode1Noop` | `src/overlays/ov002/auto/Ov002Panel_LeaveMode1Noop.c` | `src/ov002/panel_state/SwitchPanelMode_02062cb8.c` |
| ov002:02062ec8 arm | `Ov002Panel_EnterMode5Noop` | `src/overlays/ov002/auto/Ov002Panel_EnterMode5Noop.c` | `src/ov002/panel_state/SwitchPanelMode_02062cb8.c` |
| ov002:02062edc arm | `Ov002Panel_LeaveMode5Noop` | `src/overlays/ov002/auto/Ov002Panel_LeaveMode5Noop.c` | `src/ov002/panel_state/SwitchPanelMode_02062cb8.c` |
| ov002:02062f80 arm | `Ov002Panel_UpdateMode4Noop` | `src/overlays/ov002/auto/Ov002Panel_UpdateMode4Noop.c` | `src/ov002/panel_state/SwitchPanelMode_02062cb8.c` |
| ov002:02062f84 arm | `Ov002Panel_LeaveMode4Noop` | `src/overlays/ov002/auto/Ov002Panel_LeaveMode4Noop.c` | `src/ov002/panel_state/SwitchPanelMode_02062cb8.c` |
| ov002:02067524 arm | `GetRecordPanelProgress` | `src/overlays/ov002/auto/GetRecordPanelProgress.c` | `src/ov013/panel_state/RecordPanelClear_02070f50.c` |
| ov002:02067538 arm | `SetContextIndexedGlobalFlag` | `src/overlays/ov002/auto/SetContextIndexedGlobalFlag.c` | `src/ov002/unclassified_helpers/DispatchContextCommand_02066c78.c` |
| ov002:020679fc arm | `ReadGlobalPackedFlag` | `src/overlays/ov002/auto/ReadGlobalPackedFlag.c` | `src/ov002/unclassified_helpers/WriteGlobalPackedFlag_020679dc.c` |
| ov003:020642fc arm | `MovieEvent_HoldCurrentEvent` | `src/overlays/ov003/auto/MovieEvent_HoldCurrentEvent.c` | `src/ov003/video_playback/MovieScene_ProcessTimeline_0206436c.c` |
| ov003:02064974 arm | `DestroyMovieSceneObjectListForwarder` | `src/overlays/ov003/calls/DestroyMovieSceneObjectListForwarder.c` | `eu/src/overlays/ov003/calls/MovieScene_Shutdown.c` |
| ov004:0206252c arm | `ScrollText_Mode3FrameNoop` | `src/overlays/ov004/auto/ScrollText_Mode3FrameNoop.c` | `src/ov004/scroll_text/RunScrollTextFrame_020629d0.c` |

## Distinct table protocols

| Owner | Native table | Layout and proven dispatch |
|---|---|---|
| Title panel (ov000) | 02063884, 15 states | 12-byte enter/update/exit records. UpdateTitlePanel reads update; SwitchPanelState invokes old exit and new enter. |
| Profile panel (ov002) | 0206c2ec, 7 modes | 16-byte enter/update/exit/draw records. SwitchPanelMode uses enter/exit; UpdatePanelState selects update at base+4. |
| Movie timeline (ov003) | 020650c4, 7 entries | Handler(scene,time,event) -> BOOL, selected by the current event. FALSE prevents eventIndex increment. |
| Scroll text (ov004) | 02064520, 4 handlers | Frame hook indexed by work.mode. Mode3 uses the empty hook and the frame driver returns 0. |

The title and profile-panel tables cross physical DATA fragments. Names such as gPanelInitialStateHandler or gPanelModeExitCallback describe slices, not the logical record base/role. ROM reconstruction in


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov000/auto/UpdateTitleFormatNoticeKeepState.c UpdateTitleFormatNoticeKeepState
python tools/verify_idx.py src/overlays/ov000/auto/LeaveTitleFormatNoticeNoop.c LeaveTitleFormatNoticeNoop
python tools/verify_idx.py src/overlays/ov002/auto/Ov002Panel_UpdateMode1Noop.c Ov002Panel_UpdateMode1Noop
python tools/verify_idx.py src/overlays/ov002/auto/Ov002Panel_LeaveMode1Noop.c Ov002Panel_LeaveMode1Noop
python tools/verify_idx.py src/overlays/ov002/auto/Ov002Panel_EnterMode5Noop.c Ov002Panel_EnterMode5Noop
python tools/verify_idx.py src/overlays/ov002/auto/Ov002Panel_LeaveMode5Noop.c Ov002Panel_LeaveMode5Noop
python tools/verify_idx.py src/overlays/ov002/auto/Ov002Panel_UpdateMode4Noop.c Ov002Panel_UpdateMode4Noop
python tools/verify_idx.py src/overlays/ov002/auto/Ov002Panel_LeaveMode4Noop.c Ov002Panel_LeaveMode4Noop
python tools/verify_idx.py src/overlays/ov002/auto/GetRecordPanelProgress.c GetRecordPanelProgress
python tools/verify_idx.py src/overlays/ov002/auto/SetContextIndexedGlobalFlag.c SetContextIndexedGlobalFlag
python tools/verify_idx.py src/overlays/ov002/auto/ReadGlobalPackedFlag.c ReadGlobalPackedFlag
python tools/verify_idx.py src/overlays/ov003/auto/MovieEvent_HoldCurrentEvent.c MovieEvent_HoldCurrentEvent
python tools/verify_idx.py src/overlays/ov003/calls/DestroyMovieSceneObjectListForwarder.c DestroyMovieSceneObjectListForwarder
python tools/verify_idx.py src/overlays/ov004/auto/ScrollText_Mode3FrameNoop.c ScrollText_Mode3FrameNoop
bash tools/gate.sh
```
