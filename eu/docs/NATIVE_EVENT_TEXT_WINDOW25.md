# Event panel and text-window DATA contracts (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

## Owner and type limits

The event-panel manager, text-window task pointer, static text-window runtime and background-session task pointer are distinct owners. Layout names follow actual setters and consumers: fade-quad scale/translation locals are swapped in the inherited C, and the cursor word called portraitId is written as a measured-text size class 0..4. Tail anchor IDs select position/flip records, not character identities.

The c34cc/c3500 split is one twenty-word X table. Camera references at the same RAM address have been separately bound to resident ov046:gCameraManager; the physical ov036 tail can therefore retain its text-window identity. [Bank-qualified ownership](BANK_QUALIFIED_OWNER_BINDINGS.md) records the native loader proof.

The two copied 128/96 templates at c36b8/c36c0 are not included: QueueMessageWindowKind2/3 overwrite request.size with NULL before reading it. The resource-layer table at c33b0 is also not named here because its consumer role needs further proof.

## Inventory and evidence

### `ov036:020c3380` → `gEventFadeQuadBaseTranslation`

Previous label `data_ov036_020c3380`; size **12 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c3380.c`.

12 RO bytes: Q12 translation vector {0x80000,0x60000,0x3ffccd}.

DrawPanelFadeQuad copies this vector, optionally adds 0x333 to Z, and passes it to NNS_G3dGlbSetBaseTrans before drawing the quad.

Limits: The local variable is misleadingly called scale. The actual setter writes prmBaseTrans; name follows the consumer, not that variable.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c3380.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/DrawPanelFadeQuad.c` → `src/ov036/panel_state/DrawPanelFadeQuad_020bad3c.c`; line(s) 25, 96.

### `ov036:020c338c` → `gEventFadeQuadBaseScale`

Previous label `data_ov036_020c338c`; size **12 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c338c.c`.

12 RO bytes: Q12 scale vector {0x100000,0xc0000,0x1000}.

DrawPanelFadeQuad copies this vector and passes it to NNS_G3dGlbSetBaseScale, whose real body writes prmBaseScale.

Limits: The local variable is misleadingly called translation. Keep native fixed-point values and separate the translation table.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c338c.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/DrawPanelFadeQuad.c` → `src/ov036/panel_state/DrawPanelFadeQuad_020bad3c.c`; line(s) 26, 97.

### `ov036:020c3398` → `gEventFadeQuadCameraPosition`

Previous label `data_ov036_020c3398`; size **12 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c3398.c`.

12 RO bytes interpreted as VecFx32 {0,0,0x400000}, although defined as six halfwords.

DrawPanelFadeQuad copies the three-word vector and uses it as camPos in SetLookAt; that helper updates the G3D camera position and constructs the view matrix.

Limits: Preserve the existing six-halfword definition and bytes. This camera belongs to the fade-quad draw, not the persistent field-camera manager.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c3398.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/DrawPanelFadeQuad.c` → `src/ov036/panel_state/DrawPanelFadeQuad_020bad3c.c`; line(s) 27, 98.

### `ov036:020c33a4` → `gEventFadeQuadCameraUp`

Previous label `data_ov036_020c33a4`; size **12 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c33a4.c`.

12 RO bytes: Q12 up vector {0,0x1000,0}.

DrawPanelFadeQuad passes this vector as camUp to its SetLookAt helper, along with the separate camera position and zero target.

Limits: This is not a position or a global default for every camera backend.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c33a4.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/DrawPanelFadeQuad.c` → `src/ov036/panel_state/DrawPanelFadeQuad_020bad3c.c`; line(s) 28, 103.

### `ov036:020c33b8` → `gTextWindowTextBgIds`

Previous label `data_ov036_020c33b8`; size **8 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c33b8.c`.

8 RO bytes: two word-sized BG IDs {2,3}.

OpenQueuedTextWindow selects one by request.screen and stores it at window+0x2c. DrawTextWindow consumes that field as the BG argument to InitTextLayerAt and to choose the BG2/BG3 screen pointer.

Limits: Retain both entries and the native unchecked screen selection. The separate frame BG IDs are a distinct object with the same contents.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c33b8.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/OpenQueuedTextWindow.c` → `src/ov036/text_rendering/OpenQueuedTextWindow_020bf6c0.c`; line(s) 94, 129.

### `ov036:020c33c0` → `gTextWindowFrameBgIds`

Previous label `data_ov036_020c33c0`; size **8 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c33c0.c`.

8 RO bytes: two word-sized BG IDs {2,3}.

OpenQueuedTextWindow stores the selected value at window+0x24. LoadTextWindowFrame uses that field to choose BG2/BG3 priority/offset updates and its frame upload adapters.

Limits: The local tileLimit label is false for this observed consumer. This table is not a tile-count or an allocation bound.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c33c0.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/OpenQueuedTextWindow.c` → `src/ov036/text_rendering/OpenQueuedTextWindow_020bf6c0.c`; line(s) 92, 126.

### `ov036:020c33c8` → `gTextWindowDisplayPlaneMasks`

Previous label `data_ov036_020c33c8`; size **8 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c33c8.c`.

8 RO bytes: two native display-plane masks {4,8}.

OpenQueuedTextWindow stores one at window+0x20. SetDisplayLayersVisible combines that mask with DISPCNT bits 8..12 when showing or hiding the window BG plane.

Limits: The local tileBase label is not the demonstrated meaning. Preserve mask values and native register sequencing.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c33c8.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/OpenQueuedTextWindow.c` → `src/ov036/text_rendering/OpenQueuedTextWindow_020bf6c0.c`; line(s) 91, 125.

### `ov036:020c33d0` → `gDialogTailDefaultYPositions`

Previous label `data_ov036_020c33d0`; size **8 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c33d0.c`.

8 RO bytes: two Q12 Y positions selected by the anchor row.

LayoutTextWindow and UpdateTextWindowTail use this table for dialog styles above 7. The selected anchor supplies row 0/1.

Limits: These are tail/marker positions, not the text-frame dimensions. Do not substitute them for the size-class-specific Y table.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c33d0.c`; line(s) 18.
- `eu/src/overlays/ov036/calls/LayoutTextWindow.c` → `src/ov036/text_rendering/LayoutTextWindow_020c03e0.c`; line(s) 99, 256.
- `eu/src/overlays/ov036/calls/UpdateTextWindowTail_020c12e8.c` → `src/ov036/text_rendering/UpdateTextWindowTail_020c12e8.c`; line(s) 69, 120.

### `ov036:020c33d8` → `gDialogTailDefaultXPositions`

Previous label `data_ov036_020c33d8`; size **16 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c33d0.c`.

16 RO bytes read as four Q12 words, each 0x80000; the native definition uses eight halfwords.

LayoutTextWindow and UpdateTextWindowTail select one word using anchor.column for dialog styles above 7.

Limits: Preserve the halfword declaration and duplicate positions. This does not merge the four columns into one value.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c33d0.c`; line(s) 14.
- `eu/src/overlays/ov036/calls/LayoutTextWindow.c` → `src/ov036/text_rendering/LayoutTextWindow_020c03e0.c`; line(s) 98, 255.
- `eu/src/overlays/ov036/calls/UpdateTextWindowTail_020c12e8.c` → `src/ov036/text_rendering/UpdateTextWindowTail_020c12e8.c`; line(s) 68, 119.

### `ov036:020c33e8` → `gDialogSpecialStyleFrameIds`

Previous label `data_ov036_020c33e8`; size **28 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c33d0.c`.

28 RO bytes: seven native frame-image IDs.

LoadTextWindowFrame selects index style-7 for explicit styles 7..12 and fixes the size class to 3, then loads the chosen image from the text-window image resource.

Limits: Only indices 0..5 are selected by this branch; keep the seventh native word without calling it padding or unused.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c33d0.c`; line(s) 9.
- `eu/src/overlays/ov036/calls/LoadTextWindowFrame.c` → `src/ov036/text_rendering/LoadTextWindowFrame_020bfb0c.c`; line(s) 58, 115.

### `ov036:020c3404` → `gDialogTailYBySizeClass`

Previous label `data_ov036_020c3404`; size **40 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c33d0.c`.

40 RO bytes: five pairs of Q12 Y positions.

LayoutTextWindow and UpdateTextWindowTail index [cursor+0x20][anchor.row]. LoadTextWindowFrame writes that cursor word as a size class 0..4 derived from measured text dimensions or the selected style.

Limits: The private portraitId label in the layout code is misleading for this word. Do not assign character/portrait identities to the five rows.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c33d0.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/LayoutTextWindow.c` → `src/ov036/text_rendering/LayoutTextWindow_020c03e0.c`; line(s) 97, 253.
- `eu/src/overlays/ov036/calls/UpdateTextWindowTail_020c12e8.c` → `src/ov036/text_rendering/UpdateTextWindowTail_020c12e8.c`; line(s) 67, 117.

### `ov036:020c342c` → `gDialogFrameRect0X`

Previous label `data_ov036_020c342c`; size **2 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c342c.c`.

2 RO bytes: first frame rectangle X halfword, value 10.

PlaceTextWindowFrame reads the native FrameRect array (x,y,width,height) from this address using the cursor size class.

Limits: The logical five-rectangle table is split 2+2+2+34 bytes; keep the first field separate in native storage.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c342c.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/PlaceTextWindowFrame.c` → `src/ov036/text_rendering/PlaceTextWindowFrame_020bfe18.c`; line(s) 77, 140, 141, 142, 143.

### `ov036:020c342e` → `gDialogFrameRect0Y`

Previous label `data_ov036_020c342e`; size **2 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c342e.c`.

2 RO bytes: first frame rectangle Y halfword, value 11.

The FrameRect view rooted at c342c reaches this word at +2 and assigns it to window.frame.y.

Limits: Do not infer a separate one-element array contract from the source allocation.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c342e.c`; line(s) 3.
- `eu/src/ov036/data/Rodata_ov036_020c342c.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/PlaceTextWindowFrame.c` → `src/ov036/text_rendering/PlaceTextWindowFrame_020bfe18.c`; line(s) 77, 140, 141, 142, 143.

### `ov036:020c3430` → `gDialogFrameRect0Width`

Previous label `data_ov036_020c3430`; size **2 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c3430.c`.

2 RO bytes: first frame rectangle width halfword, value 12.

The same FrameRect reader reaches this word at +4 and assigns it to window.frame.width.

Limits: Preserve halfword units and the separate height word at the beginning of the next native object.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c3430.c`; line(s) 9.
- `eu/src/ov036/data/Rodata_ov036_020c342c.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/PlaceTextWindowFrame.c` → `src/ov036/text_rendering/PlaceTextWindowFrame_020bfe18.c`; line(s) 77, 140, 141, 142, 143.

### `ov036:020c3432` → `gDialogFrameRectTableTail`

Previous label `data_ov036_020c3432`; size **34 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c3430.c`.

34 RO bytes: first rectangle height followed by four complete eight-byte rectangles.

PlaceTextWindowFrame reads all four fields at an eight-byte stride from the c342c base. The four native allocations together form 40 bytes, matching five size-class rectangles.

Limits: The allocation is not seventeen unrelated values. Preserve the split and existing table indexing; no bounds check is added.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c3430.c`; line(s) 3.
- `eu/src/ov036/data/Rodata_ov036_020c342c.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/PlaceTextWindowFrame.c` → `src/ov036/text_rendering/PlaceTextWindowFrame_020bfe18.c`; line(s) 77, 140, 141, 142, 143.

### `ov036:020c348c` → `gTextWindowTailResourceIdsByStyle`

Previous label `data_ov036_020c348c`; size **64 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c348c.c`.

64 RO bytes: sixteen word-sized record resource IDs selected by window style.

LayoutTextWindow uses the selected resource to initialize entries[4], sets its enabled state from the anchor, and applies the configured X/Y flip flags to its slot.

Limits: The IDs identify tail/marker record resources in this path; individual visual-style names are not established.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c348c.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/LayoutTextWindow.c` → `src/ov036/text_rendering/LayoutTextWindow_020c03e0.c`; line(s) 94, 203, 258.

### `ov036:020c34cc` → `gDialogTailXBySizeClassPrefix`

Previous label `data_ov036_020c34cc`; size **52 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c34cc.c`.

52 RO bytes: first thirteen words of a five-by-four Q12 X-position table.

LayoutTextWindow and UpdateTextWindowTail index the base as [sizeClass][anchor.column]. The seven-word continuation at c3500 completes twenty words, matching five size classes and four columns.

Limits: Keep the two native objects. This prefix ends after the first word of size-class row 3; do not treat it as thirteen complete layout records.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c34cc.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/LayoutTextWindow.c` → `src/ov036/text_rendering/LayoutTextWindow_020c03e0.c`; line(s) 96, 252.
- `eu/src/overlays/ov036/calls/UpdateTextWindowTail_020c12e8.c` → `src/ov036/text_rendering/UpdateTextWindowTail_020c12e8.c`; line(s) 66, 116.

### `ov036:020c3500` → `gDialogTailXBySizeClassTail`

Previous label `data_ov036_020c3500`; size **28 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c3500.c`.

28 RO bytes: final seven words of the five-by-four Q12 tail X-position table.

This is reached by the c34cc base-array view for the remaining columns of size class 3 and all four columns of size class 4. Its contents continue the same Q12 column pattern.

Limits: The former foreign camera alias is corrected to resident ov046:gCameraManager. This RO table remains an independent ov036 object; equal RAM addresses do not establish shared storage or a common host type.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c3500.c`; line(s) 35.
- `eu/src/overlays/ov047/Ov047CameraState.h`; line(s) 11, 12.
- `eu/src/overlays/ov047/calls/Camera_SweepLookAt.c` → `src/ov047/camera/Camera_SweepLookAt_020c6594.c`; line(s) 152, 196.
- `eu/src/ov036/data/Rodata_ov036_020c34cc.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/LayoutTextWindow.c` → `src/ov036/text_rendering/LayoutTextWindow_020c03e0.c`; line(s) 96, 252.
- `eu/src/overlays/ov036/calls/UpdateTextWindowTail_020c12e8.c` → `src/ov036/text_rendering/UpdateTextWindowTail_020c12e8.c`; line(s) 66, 116.

### `ov036:020c351c` → `gDialogFrameIdsByStyleAndSize`

Previous label `data_ov036_020c351c`; size **140 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c3500.c`.

140 RO bytes: seven rows of five word-sized frame-image IDs.

LoadTextWindowFrame indexes by style and computed size class in its default style branch, then builds the packed resource key and loads the selected frame image.

Limits: Keep all seven rows and original caller assumptions; special styles 7..12 use the separate frame-ID table.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c3500.c`; line(s) 23.
- `eu/src/overlays/ov036/calls/LoadTextWindowFrame.c` → `src/ov036/text_rendering/LoadTextWindowFrame_020bfb0c.c`; line(s) 59, 146.

### `ov036:020c35a8` → `gTextWindowTailAnchorConfigs`

Previous label `data_ov036_020c35a8`; size **272 bytes**; source `eu/src/ov036/data/Rodata_ov036_020c3500.c`.

272 RO bytes: seventeen native records of four words {column,row,flipX,flipY}.

LayoutTextWindow and UpdateTextWindowTail use column/row for placement, convert flip fields to slot flags, and disable entries[4] for anchor 16. Banner placement also distinguishes anchors 0..7 from the lower group.

Limits: The private speaker label does not mean these are character identities. Preserve the neutral anchor interpretation and the zero record at index 16.

Direct/base-view references:

- `eu/src/ov036/data/Rodata_ov036_020c3500.c`; line(s) 3.
- `eu/src/overlays/ov036/calls/LayoutTextWindow.c` → `src/ov036/text_rendering/LayoutTextWindow_020c03e0.c`; line(s) 93, 185, 246.
- `eu/src/overlays/ov036/calls/UpdateTextWindowTail_020c12e8.c` → `src/ov036/text_rendering/UpdateTextWindowTail_020c12e8.c`; line(s) 65, 114, 169.

### `ov036:020c385c` → `gTextWindowJoinLineBreak`

Previous label `data_ov036_020c385c`; size **4 bytes**; source `eu/src/ov036/data/Data_ov036_020c385c.c`.

4 initialized DATA bytes: narrow newline, NUL terminator and two zero padding bytes.

ScriptCmd_ShowJoinedMessage and ScriptCmd_ShowNameList append this separator with strcat between names/messages, then convert the joined UTF-8 text to UCS2.

Limits: The separator itself is a narrow string, not a UTF16 halfword array. Keep its writable DATA section and four-byte native allocation.

Direct/base-view references:

- `eu/src/ov036/data/Data_ov036_020c385c.c`; line(s) 5.
- `eu/src/overlays/ov036/calls/ScriptCmd_ShowJoinedMessage.c` → `src/ov036/shared_engine/ScriptCmd_ShowJoinedMessage_020be1e0.c`; line(s) 18, 35.
- `eu/src/overlays/ov036/calls/ScriptCmd_ShowNameList.c` → `src/ov036/shared_engine/ScriptCmd_ShowNameList_020be3ac.c`; line(s) 31, 52.

### `ov036:020c38bc` → `gDialogPrimaryRecordPositions`

Previous label `data_ov036_020c38bc`; size **40 bytes**; source `eu/src/ov036/data/Data_ov036_020c38bc.c`.

40 initialized DATA bytes: five Q12 X/Y position pairs.

LayoutTextWindow uses the pair selected by the measured-text size class for entries[0] in ordinary dialog styles. Special styles instead use an explicit fixed position.

Limits: These are positions for dialog record slot 0, not the frame rectangle or portrait positions; the local portraitId name is not adopted. The exact graphic/icon role of that record is not assigned.

Direct/base-view references:

- `eu/src/ov036/data/Data_ov036_020c38bc.c`; line(s) 5.
- `eu/src/overlays/ov036/calls/LayoutTextWindow.c` → `src/ov036/text_rendering/LayoutTextWindow_020c03e0.c`; line(s) 95, 242.

### `ov036:020c3940` → `gEvent2DPanelManager`

Previous label `data_ov036_020c3940`; size **12 bytes**; source `eu/src/overlays/ov036/data/bss/Bss_ov036_020c3940.c`.

12 BSS bytes: native Event2DPanelManager {buffer,work,extra}.

InitEvent2DPanel stores GetRunningTaskWork in manager.work, initializes its two script buffers, allocates scene slots/actors/layers and returns RunPanelStateMachine. Draw/update/script adapters access that same work at manager+4.

Limits: The manager object and its allocated 0x10fc-byte task work are separate owners. Roles of manager.buffer/extra are not expanded from unused-looking declarations.

Direct/base-view references:

- `eu/src/overlays/ov036/Event2DPanel.h`; line(s) 53.
- `eu/src/overlays/ov036/calls/AdvancePanelScriptSkipAndRestoreScene.c`; line(s) 48, 62.
- `eu/src/overlays/ov036/calls/AdvanceSlotTransition.c` → `src/ov036/panel_state/AdvanceSlotTransition_020bb8e0.c`; line(s) 35, 41, 45.
- `eu/src/overlays/ov036/calls/AttachPendingSceneModel.c` → `src/ov036/unclassified_helpers/AttachPendingSceneModel_020bd130.c`; line(s) 23, 32, 33.
- `eu/src/overlays/ov036/calls/ClearPanelSceneTransition.c`; line(s) 13, 17.
- `eu/src/overlays/ov036/calls/DrawPanelFadeQuad.c` → `src/ov036/panel_state/DrawPanelFadeQuad_020bad3c.c`; line(s) 24, 101.
- `eu/src/overlays/ov036/calls/DrawPanelSceneFrame.c` → `src/ov036/panel_state/DrawPanelSceneFrame_020bb130.c`; line(s) 41, 50, 61.
- `eu/src/overlays/ov036/calls/EnterPanelModeThree.c` → `src/ov036/panel_state/EnterPanelModeThree_020bc51c.c`; line(s) 21, 30, 45.
- `eu/src/overlays/ov036/calls/FindOrAcquireModelSlot.c` → `src/ov036/panel_state/FindOrAcquireModelSlot_020bc138.c`; line(s) 19, 25.
- `eu/src/overlays/ov036/calls/FindOrAcquireOwnerSlot.c` → `src/ov036/panel_state/FindOrAcquireOwnerSlot_020bb7c0.c`; line(s) 27, 32.
- `eu/src/overlays/ov036/calls/FinishPanelSceneSetup.c` → `src/ov036/panel_state/FinishPanelSceneSetup_020baa38.c`; line(s) 44, 57.
- `eu/src/overlays/ov036/calls/FinishPanelSceneTransition.c`; line(s) 13, 18, 20.
- `eu/src/overlays/ov036/calls/GetActorSlotPosition.c` → `src/ov036/unclassified_helpers/GetActorSlotPosition_020bd0dc.c`; line(s) 27, 32.
- `eu/src/overlays/ov036/calls/GetPanelCursorOverride.c` → `src/ov036/panel_state/GetPanelCursorOverride_020bda08.c`; line(s) 24, 28.
- `eu/src/overlays/ov036/calls/GetPanelFlag40.c` → `src/ov036/panel_state/GetPanelFlag40_020bd8a8.c`; line(s) 18, 21.
- `eu/src/overlays/ov036/calls/GetSceneWorkValue10d8.c` → `src/ov036/unclassified_helpers/GetSceneWorkValue10d8_020bd49c.c`; line(s) 13, 16.
- `eu/src/overlays/ov036/calls/HasPanelScriptSkipTarget.c` → `src/ov036/unclassified_helpers/HasSceneActiveMenu_020bc648.c`; line(s) 13, 16.
- `eu/src/overlays/ov036/calls/InitEvent2DPanel.c`; line(s) 43, 44, 45, 46, 47, 48, 49, 50, 53, 55, 57, 59, 60, 61, 63, 64, 65, 76.
- `eu/src/overlays/ov036/calls/InitPanelDisplay.c` → `src/ov036/panel_state/InitPanelDisplay_020bc1b0.c`; line(s) 12, 47, 48, 56, 57.
- `eu/src/overlays/ov036/calls/InitializePanelArchive.c`; line(s) 15, 30.
- `eu/src/overlays/ov036/calls/IsSceneFlag10Clear.c` → `src/ov036/unclassified_helpers/IsSceneFlag10Clear_020bc5c0.c`; line(s) 13, 16.
- `eu/src/overlays/ov036/calls/IsSceneReady.c` → `src/ov036/unclassified_helpers/IsSceneReady_020bc3a8.c`; line(s) 13, 16.
- `eu/src/overlays/ov036/calls/IsScreenLayerLoaded.c` → `src/ov036/panel_state/IsScreenLayerLoaded_020bd540.c`; line(s) 19, 23.
- `eu/src/overlays/ov036/calls/LoadSceneModelSlot.c` → `src/ov036/unclassified_helpers/LoadSceneModelSlot_020bd1a0.c`; line(s) 38, 47.
- `eu/src/overlays/ov036/calls/LoadScreenLayerImage.c` → `src/ov036/panel_state/LoadScreenLayerImage_020bb99c.c`; line(s) 34, 49.
- `eu/src/overlays/ov036/calls/LoadTextureInChunks.c` → `src/ov036/panel_state/LoadTextureInChunks_020bc8b4.c`; line(s) 13, 26.
- `eu/src/overlays/ov036/calls/MoveActorSlotX.c` → `src/ov036/unclassified_helpers/MoveActorSlotX_020bcbb4.c`; line(s) 33, 38.
- `eu/src/overlays/ov036/calls/MoveActorSlotY.c` → `src/ov036/unclassified_helpers/MoveActorSlotY_020bcd08.c`; line(s) 33, 39.
- `eu/src/overlays/ov036/calls/MoveSceneModelSlot.c` → `src/ov036/unclassified_helpers/MoveSceneModelSlot_020bd2c8.c`; line(s) 27, 33.
- `eu/src/overlays/ov036/calls/OpenPanelMessageArchive.c`; line(s) 15, 29.
- `eu/src/overlays/ov036/calls/RecordPanelInputEvent.c` → `src/ov036/panel_state/RecordPanelInputEvent_020bc458.c`; line(s) 23, 27, 28, 29, 30, 31.
- `eu/src/overlays/ov036/calls/ReleaseModelSlot.c` → `src/ov036/panel_state/ReleaseModelSlot_020bd414.c`; line(s) 25, 32.
- `eu/src/overlays/ov036/calls/RequestPanelScriptSkipAndSnapshotPositions.c` → `src/ov036/panel_state/SnapshotActorSlotPositions_020bc5e0.c`; line(s) 32, 38, 47.
- `eu/src/overlays/ov036/calls/ResetScreenLayer.c` → `src/ov036/panel_state/ResetScreenLayer_020bd500.c`; line(s) 21, 26.
- `eu/src/overlays/ov036/calls/ResetSlotScene.c` → `src/ov036/panel_state/ResetSlotScene_020bb428.c`; line(s) 41, 47.
- `eu/src/overlays/ov036/calls/RunPanelScriptFrame.c` → `src/ov036/panel_state/RunPanelScriptFrame_020ba970.c`; line(s) 16, 22, 30.
- `eu/src/overlays/ov036/calls/RunPanelStateMachine.c` → `src/ov036/panel_state/RunPanelStateMachine_020ba620.c`; line(s) 16, 27, 28, 30, 32, 34.
- `eu/src/overlays/ov036/calls/RunPanelSubScriptFrame.c` → `src/ov036/panel_state/RunPanelSubScriptFrame_020ba9d0.c`; line(s) 16, 22, 30.
- `eu/src/overlays/ov036/calls/SetActorSlotPriority.c` → `src/ov036/unclassified_helpers/SetActorSlotPriority_020bcf70.c`; line(s) 24, 29.
- `eu/src/overlays/ov036/calls/SetPanelCursorOverride.c` → `src/ov036/panel_state/SetPanelCursorOverride_020bd9a4.c`; line(s) 24, 28.
- `eu/src/overlays/ov036/calls/SetPanelScriptBgmRequest.c` → `src/ov036/unclassified_helpers/SetSceneCursor_020bd980.c`; line(s) 14, 17, 18.
- `eu/src/overlays/ov036/calls/SetSceneFlag4000.c` → `src/ov036/unclassified_helpers/SetSceneFlag4000_020bc3f8.c`; line(s) 13, 16.
- `eu/src/overlays/ov036/calls/SetSceneModelBlendIndex.c` → `src/ov036/unclassified_helpers/SetSceneModelBlendIndex_020bd36c.c`; line(s) 30, 36.
- `eu/src/overlays/ov036/calls/SetScreenLayerImage.c` → `src/ov036/panel_state/SetScreenLayerImage_020bd4b4.c`; line(s) 23, 28.
- `eu/src/overlays/ov036/calls/SetSlotSharedRecord.c` → `src/ov036/panel_state/SetSlotSharedRecord_020bca70.c`; line(s) 30, 40.
- `eu/src/overlays/ov036/calls/ShutdownPanelScene_020bab74.c`; line(s) 41, 58, 95.
- `eu/src/overlays/ov036/calls/ShutdownSceneWork_020ba6c4.c`; line(s) 14, 30, 31, 33.
- `eu/src/overlays/ov036/calls/SlideActorSlotsOffscreen.c` → `src/ov036/unclassified_helpers/SlideActorSlotsOffscreen_020bc81c.c`; line(s) 25, 30.
- `eu/src/overlays/ov036/calls/StartActorFocusTransition.c` → `src/ov036/unclassified_helpers/StartActorFocusTransition_020bcec8.c`; line(s) 30, 35.
- `eu/src/overlays/ov036/calls/StartActorSlotAlphaFade.c` → `src/ov036/unclassified_helpers/StartActorSlotAlphaFade_020bcfcc.c`; line(s) 28, 33.
- `eu/src/overlays/ov036/calls/StartBgMosaicTransition.c`; line(s) 26, 30.
- `eu/src/overlays/ov036/calls/StartPanelSceneLoad.c`; line(s) 13, 19.
- `eu/src/overlays/ov036/calls/StartScreenBrightnessFade.c` → `src/ov036/panel_state/StartScreenBrightnessFade_020bd5dc.c`; line(s) 31, 40.
- `eu/src/overlays/ov036/calls/StartScreenBrightnessFade_020bd6dc.c` → `src/ov036/panel_state/StartScreenBrightnessFade_020bd6bc.c`; line(s) 13, 18.
- `eu/src/overlays/ov036/calls/StartScreenLayerScroll.c` → `src/ov036/panel_state/StartScreenLayerScroll_020bd570.c`; line(s) 31, 36.
- `eu/src/overlays/ov036/calls/StartScreenLayerZoom.c`; line(s) 30, 35.
- `eu/src/overlays/ov036/calls/StepActorSlotAlphaFade.c`; line(s) 28, 37.
- `eu/src/overlays/ov036/calls/StepActorSlotMove.c`; line(s) 29, 38.
- `eu/src/overlays/ov036/calls/StepBgMosaicTransition.c`; line(s) 30, 40.
- `eu/src/overlays/ov036/calls/StepSceneModelMove.c` → `src/ov036/unclassified_helpers/StepSceneModelMove_020bb080.c`; line(s) 25, 34.
- `eu/src/overlays/ov036/calls/StepScreenBrightnessFade.c` → `src/ov036/panel_state/StepScreenBrightnessFade_020bbc64.c`; line(s) 29, 35.
- `eu/src/overlays/ov036/calls/SwapActorSlotResource.c` → `src/ov036/unclassified_helpers/SwapActorSlotResource_020bc978.c`; line(s) 36, 53, 54.
- `eu/src/overlays/ov036/calls/ToggleActorSlotFlip.c` → `src/ov036/unclassified_helpers/ToggleActorSlotFlip_020bce20.c`; line(s) 19, 24.
- `eu/src/overlays/ov036/calls/ToggleSceneBlendAndClearColor.c` → `src/ov036/panel_state/ToggleSceneBlendAndClearColor_020bd8c8.c`; line(s) 22, 29, 38.
- `eu/src/overlays/ov036/calls/UpdateLayerShake.c`; line(s) 28, 64.
- `eu/src/overlays/ov036/calls/UpdatePendingSlotScene.c` → `src/ov036/panel_state/UpdatePendingSlotScene_020bafa8.c`; line(s) 16, 21.
- `eu/src/overlays/ov036/calls/UpdateScreenLayer.c`; line(s) 31, 42, 58.
- `eu/src/overlays/ov036/calls/UpdateSpriteShake.c`; line(s) 30, 47.
- `eu/src/overlays/ov036/calls/PanelSceneState_WaitControllerReady.c`; line(s) 13, 21.
- `eu/src/overlays/ov036/calls/UpdateEvent2DSceneObjects.c`; line(s) 57, 72.
- `eu/src/overlays/ov036/calls/UpdateEvent2DActorSlot.c`; line(s) 4, 12.
- `eu/src/overlays/ov036/calls/Event2DSceneOnLeaveClearFlag2.c`; line(s) 4, 7.
- `eu/src/overlays/ov036/calls/StartActorSlotShake.c`; line(s) 4, 11.
- `eu/src/overlays/ov036/calls/ReleaseEvent2DActorSlot.c`; line(s) 4, 15.
- `eu/src/overlays/ov036/calls/ClearPanelWindowWaitState.c`; line(s) 4, 8.
- `eu/src/overlays/ov036/data/bss/Bss_ov036_020c3940.c`; line(s) 3.

### `ov036:020c394c` → `gTextWindowTaskWork`

Previous label `data_ov036_020c394c`; size **4 bytes**; source `eu/src/overlays/ov036/data/bss/Bss_ov036_020c394c.c`.

4 BSS bytes: pointer saved from GetRunningTaskWork by the text-window task constructor.

The constructor at EU ov036:020be858 saves this pointer, clears the separate static text-window resource work, initializes its windows/key repeat/background and returns UpdateTextWindows.

Limits: This task-work pointer is distinct from the gTextWindowResourceTable pointer to static runtime storage. No ownership transfer of the task work is inferred.

Direct/base-view references:

- `eu/src/overlays/ov036/calls/InitTextWindowTask.c`; line(s) 7, 19.
- `eu/src/overlays/ov036/data/bss/Bss_ov036_020c394c.c`; line(s) 4.

### `ov036:020ca204` → `gTextWindowBgTaskWorkPointerStorage`

Previous label `data_ov036_020ca204`; size **28 bytes**; source `eu/src/overlays/ov036/data/bss/Bss_ov036_020ca204.c`.

28 BSS bytes whose first word is the borrowed background-session task-work pointer; the remaining 24 bytes are retained opaque.

The constructor at EU ov036:020c2d68 stores GetRunningTaskWork here, configures BG controls/callbacks and saves the child text-window task handle at work+4. BackupBgGraphics and UploadAndFreeBgGraphics use this pointer to snapshot/restore BG2/BG3 maps, characters and palette. The destructor destroys the child and clears the pointer.

Limits: This ELF allocation is 28 bytes even though its first-word view is a pointer. The graphics snapshot buffers belong to the pointed-to task work, not these trailing 24 bytes; do not shrink or reinterpret them in the rename block.

Direct/base-view references:

- `eu/src/overlays/ov036/calls/BackupBgGraphics.c`; line(s) 13, 42.
- `eu/src/overlays/ov036/calls/DestroyPxiChannelState.c` → `src/ov036/library_nitro_pxi/DestroyPxiChannelState_020c2dbc.c`; line(s) 8, 14, 16, 17.
- `eu/src/overlays/ov036/calls/UploadAndFreeBgGraphics.c` → `src/ov036/text_rendering/UploadAndFreeBgGraphics_020c31c8.c`; line(s) 14, 27.
- `eu/src/overlays/ov036/calls/InitTextWindowControllerTask.c`; line(s) 9, 19, 26.
- `eu/src/overlays/ov036/data/bss/Bss_ov036_020ca204.c`; line(s) 3.

## Additional consumer proof

- `eu/libs/nns/g3d/auto/NNS_G3dGlbSetBaseScale.c`.
- `eu/libs/nns/g3d/auto/NNS_G3dGlbSetBaseTrans.c`.
- `eu/src/overlays/ov036/calls/SetDisplayLayersVisible.c`.
- `eu/src/overlays/ov036/calls/DrawTextWindow.c`.
- `eu/src/overlays/ov036/calls/LoadTextWindowFrame.c`.
- `eu/src/overlays/ov036/Event2DPanel.h`.


## Byte-exact validation

75 DATA identities retain their source paths, native sizes and storage.
141/144 affected official function checks pass; the remaining
3 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 199 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
