# EU early overlay data contracts

These names cover movie/scroll scripts, panel format strings, task-work references and field-object constants. Each identity retains its physical storage, native values and current interface. Global storage whose first word is a pointer may include an uncharacterized tail; that tail is preserved rather than assigned invented structure fields.

## Identity and source map

| EU identity | Name | Physical storage | Definition |
| --- | --- | --- | --- |
| ov000 `0x02063a08` | `gTitleSelectionGlobals` | 24 bytes (bss) | `src/overlays/ov000/data/bss/Bss_ov000_02063a04.c` |
| ov002 `0x0206c2c4` | `gProfilePanelTaskClass` | 20 bytes (data) | `src/ov002/data/Data_ov002_0206c2c4.c` |
| ov002 `0x0206c41c` | `gOv002ScreenFadeCompleteStorage` | 4 bytes (data) | `src/ov002/data/Data_ov002_0206c41c.c` |
| ov002 `0x0206c420` | `gOv002ScreenFadeTaskClass` | 20 bytes (data) | `src/ov002/data/Data_ov002_0206c41c.c` |
| ov002 `0x0206c460` | `gOv002ProfilePanelWork` | 4 bytes (bss) | `src/overlays/ov002/data/bss/Bss_ov002_0206c460.c` |
| ov002 `0x0206c464` | `gOv002MenuWork` | 4 bytes (bss) | `src/overlays/ov002/data/bss/Bss_ov002_0206c464.c` |
| ov002 `0x0206c468` | `gOv002ScreenFadeWork` | 4 bytes (bss) | `src/overlays/ov002/data/bss/Bss_ov002_0206c468.c` |
| ov002 `0x0206c470` | `gMenuContextCommandFlagStorage` | 16 bytes (bss) | `src/overlays/ov002/data/bss/Bss_ov002_0206c46c.c` |
| ov003 `0x020650e0` | `gMovieSceneTaskClass` | 20 bytes (data) | `src/ov003/data/Data_ov003_020650e0.c` |
| ov003 `0x020650f4` | `gMovieSceneTextPaletteStorage` | 64 bytes (data) | `src/ov003/data/Data_ov003_020650e0.c` |
| ov003 `0x02065134` | `gMovieSceneTimelineEvents` | 1824 bytes (data) | `src/ov003/data/Data_ov003_020650e0.c` |
| ov003 `0x020658c0` | `gMovieSceneWork` | 4 bytes (bss) | `src/overlays/ov003/data/bss/Bss_ov003_020658c0.c` |
| ov003 `0x020658c4` | `gMovieSubtitleLayoutGlobals` | 28 bytes (bss) | `src/overlays/ov003/data/bss/Bss_ov003_020658c0.c` |
| ov004 `0x02063ba8` | `gScrollTextAlignmentXOffsets` | 8 bytes (rodata) | `src/ov004/data/Rodata_ov004_02063ba8.c` |
| ov004 `0x02063bb0` | `gScrollTextObjectMarkers` | 48 bytes (rodata) | `src/ov004/data/Rodata_ov004_02063ba8.c` |
| ov004 `0x02063c30` | `gScrollTextInitialScript` | 656 bytes (rodata) | `src/ov004/data/Rodata_ov004_02063bf0.c` |
| ov004 `0x02063ec0` | `gScrollTextRollingScript` | 1600 bytes (rodata) | `src/ov004/data/Rodata_ov004_02063bf0.c` |
| ov004 `0x02064530` | `gScrollTextTaskClass` | 20 bytes (data) | `src/ov004/data/Data_ov004_02064530.c` |
| ov008 `0x020a1400` | `gChildSpawnerStageFrameCounts` | 14 bytes (data) | `src/ov008/data/Data_ov008_020a1400.c` |
| ov008 `0x020a140e` | `gSegmentedObjectJointSuffixes` | 26 bytes (data) | `src/ov008/data/Data_ov008_020a1400.c` |
| ov010 `0x020a1d40` | `gSpecialReleaseBurstPosition` | 12 bytes (rodata) | `src/ov010/data/Rodata_ov010_020a1d40.c` |
| ov010 `0x020a1d4c` | `gSpecialObjectSpriteLoadParameters` | 48 bytes (rodata) | `src/ov010/data/Rodata_ov010_020a1d40.c` |
| ov010 `0x020a1d7c` | `gAnimSequenceRotationAdjustment` | 16 bytes (rodata) | `src/ov010/data/Rodata_ov010_020a1d7c.c` |
| ov013 `0x02074c70` | `gOv013SummaryFormatSpaceConcat` | 16 bytes (data) | `src/ov013/data/Data_ov013_02074c70.c` |
| ov013 `0x02074c80` | `gOv013SummaryFormatSpaced` | 20 bytes (data) | `src/ov013/data/Data_ov013_02074c70.c` |
| ov013 `0x02074c94` | `gOv013SummaryFormatDe` | 24 bytes (data) | `src/ov013/data/Data_ov013_02074c70.c` |
| ov013 `0x02074cac` | `gOv013SummaryFormatDi` | 24 bytes (data) | `src/ov013/data/Data_ov013_02074cac.c` |
| ov013 `0x02074cc4` | `gOv013SummaryFormatConcat` | 28 bytes (data) | `src/ov013/data/Data_ov013_02074cac.c` |
| ov013 `0x02074ce0` | `gOv013PanelGlobals` | 32 bytes (bss) | `src/overlays/ov013/data/bss/Bss_ov013_02074ce0.c` |
| ov014 `0x0206f954` | `gRecordPanelFractionFormat` | 12 bytes (data) | `src/ov014/data/Data_ov014_0206f954.c` |
| ov014 `0x0206f9a0` | `gOv014PanelGlobals` | 32 bytes (bss) | `src/overlays/ov014/data/bss/Bss_ov014_0206f9a0.c` |
| ov016 `0x020a6e0c` | `gFloorSwitchCollisionHalfExtents` | 12 bytes (rodata) | `src/ov016/data/Rodata_ov016_020a6e0c.c` |
| ov016 `0x020a6e18` | `gFieldObjectLaunchUnitScale` | 12 bytes (rodata) | `src/ov016/data/Rodata_ov016_020a6e18.c` |
| ov016 `0x020a6e24` | `gFieldObjectLoweringStep` | 12 bytes (rodata) | `src/ov016/data/Rodata_ov016_020a6e24.c` |
| ov016 `0x020a6e30` | `gFieldObjectGroundProbeVector` | 12 bytes (rodata) | `src/ov016/data/Rodata_ov016_020a6e30.c` |
| ov016 `0x020a6e3c` | `gMovingFieldObjectCollisionHalfExtents` | 12 bytes (rodata) | `src/ov016/data/Rodata_ov016_020a6e3c.c` |
| ov016 `0x020a6e60` | `gOverlay016ScriptCommandHandlers` | 104 bytes (data) | `src/ov016/data/Data_ov016_020a6e60.c` |
| ov017 `0x020a5e18` | `gGridObjectGroundProbeVector` | 12 bytes (rodata) | `src/ov017/data/Rodata_ov017_020a5e18.c` |
| ov019 `0x020a367c` | `gLinkSettlingSweepDelta` | 12 bytes (rodata) | `src/ov019/data/Rodata_ov019_020a367c.c` |
| ov020 `0x020a3a50` | `gBlockGroundProbeVector` | 12 bytes (rodata) | `src/ov020/data/Rodata_ov020_020a3a50.c` |

## Consumers and limits

### `gTitleSelectionGlobals`

First word borrows current task work while the title selection wrapper loads and runs ov 039; exit unloads ov 039 and clears that pointer. Remaining 20 bytes are uncharacterized storage, not additional proved fields.

Evidence: `src/overlays/ov000/calls/EnterOv039Selection.c`, `src/overlays/ov000/calls/ExitOv039Selection.c`, `src/overlays/ov000/calls/GetTitleSessionStatus.c`.

### `gProfilePanelTaskClass`

Task descriptor: flags 0x00110008, InitProfilePanel, ShutdownPanelScene, work size 0x130, NULL final word. Do not infer other packed flag fields.

Evidence: `src/overlays/ov002/calls/InitProfilePanel.c`, `src/overlays/ov002/calls/ShutdownPanelScene.c`.

### `gOv002ScreenFadeCompleteStorage`

One u 32 initialized 1; callers interpret its first byte as the fade-complete flag. Start clears it and MarkScreenFadeComplete sets it. Preserve all 4 physical bytes.

Evidence: `src/overlays/ov002/calls/StartScreenFade.c`, `src/overlays/ov002/calls/MarkScreenFadeComplete.c`.

### `gOv002ScreenFadeTaskClass`

Task descriptor: flags 0x00100008, StartScreenFade, MarkScreenFadeComplete,12-byte work, NULL final word. PostPanelEvent wrappers create it with direction/screens/speed packed in 4 bytes.

Evidence: `src/overlays/ov002/calls/StartScreenFade.c`, `src/overlays/ov002/calls/MarkScreenFadeComplete.c`, `src/overlays/ov002/calls/PostPanelEventOn.c`, `src/overlays/ov002/calls/PostPanelEventOff.c`.

### `gOv002ProfilePanelWork`

Borrowed current-task work pointer assigned by InitProfilePanel; shared text/panel callbacks use it. No separate heap ownership or pointer clearing is inferred from the shutdown callback.

Evidence: `src/overlays/ov002/calls/InitProfilePanel.c`, `src/overlays/ov002/calls/ShutdownPanelScene.c`, `src/overlays/ov002/calls/DrawPanelSlotABText.c`.

### `gOv002MenuWork`

Pointer to heap-allocated menu context created/cleared by InitMenuContext. It owns the menu graphics/containers read by labels, popups and animated background callbacks; naming does not prove a release sequence by itself.

Evidence: `src/overlays/ov002/calls/InitMenuContext.c`, `src/overlays/ov002/calls/DrawMenuLabels.c`, `src/overlays/ov002/calls/AnimateMenuBgFrames.c`.

### `gOv002ScreenFadeWork`

Borrowed current-task 12-byte FadeState with copied direction/screens/speed and FX12 brightness. Update applies brightness to selected engines and returns-2 on completion,0 while running. No automatic pointer clearing is established.

Evidence: `src/overlays/ov002/calls/StartScreenFade.c`, `src/overlays/ov002/calls/UpdateScreenFade.c`.

### `gMenuContextCommandFlagStorage`

First byte is the context-command flag: mutating high-bit commands set 1, getter returns it, reset clears it and setter truncates input to u 8. Remaining 15 physical bytes are not characterized.

Evidence: `src/overlays/ov002/calls/DispatchContextCommand.c`, `src/overlays/ov002/calls/GetContextCommandFlag.c`, `src/overlays/ov002/calls/ResetContextCommandFlag.c`, `src/overlays/ov002/calls/SetContextCommandFlag.c`.

### `gMovieSceneTaskClass`

Task descriptor: flags 0x000d 0008, MovieScene_Init, MovieScene_Shutdown, work size 0xa 20, NULL final word.

Evidence: `src/overlays/ov003/calls/MovieScene_Init.c`, `src/overlays/ov003/calls/MovieScene_Shutdown.c`.

### `gMovieSceneTextPaletteStorage`

Static palette storage. Initialization loads its first 0x20 bytes at palette offset 0x1a 0 on both engines after loading the text font. Only that 32-byte prefix is established as the active palette here; definition remains 64 bytes.

Evidence: `src/overlays/ov003/calls/MovieScene_Init.c`.

### `gMovieSceneTimelineEvents`

152 physical 12-byte records with triggerTime u 32, handlerIndex u16 and 6 payload bytes. The dispatcher consumes events whose time is due, advances only when the handler returnsTRUE and stops when a handler returnsFALSE. No extra bounds guard is introduced.

Evidence: `src/overlays/ov003/calls/MovieScene_ProcessTimeline.c`.

### `gMovieSceneWork`

Borrowed movie task work assigned from GetRunningTaskWork. Shutdown releases its buffer/object/font/script resources, unregisters script group 3 and clears this pointer.

Evidence: `src/overlays/ov003/calls/MovieScene_Init.c`, `src/overlays/ov003/calls/MovieScene_Shutdown.c`, `src/overlays/ov003/calls/MovieScene_BeginFade.c`.

### `gMovieSubtitleLayoutGlobals`

First word caches the nonnegative horizontal offset computed as(availableWidth-measuredSubtitleWidth)/2 for centered text. Later text portions reuse it. Remaining 24 physical bytes are uncharacterized; this is pixel layout, not timing.

Evidence: `src/overlays/ov003/calls/updateMovieStreamLeadTime.c`.

### `gScrollTextAlignmentXOffsets`

Four u16 X positions{10,22,10,0}, indexed by text alignment and passed to DrawTextAnchored for normal and overlay lines.

Evidence: `src/overlays/ov004/calls/DrawScrollTextLine.c`.

### `gScrollTextObjectMarkers`

Four 12-byte records pairing an object index with a four-u16 marker. The caller recognizes SQEX/DSN1/DSN2/HAND marker codes and shows the corresponding object at fixed position instead of ordinary text.

Evidence: `src/overlays/ov004/calls/DrawScrollTextLine.c`.

### `gScrollTextInitialScript`

Initial script selected by reset; reset also sets delay 41, line 0, frameCount 0 and clears rolling. Physical 164 u 32 words remain unchanged; full opcode semantics are outside this name.

Evidence: `src/overlays/ov004/calls/ResetScrollTextScript.c`.

### `gScrollTextRollingScript`

Rolling script selected when mode becomes 1 and rolling begins; line 0 and delay 100 are set before graphics/offset initialization. Physical 400 u 32 words remain unchanged.

Evidence: `src/overlays/ov004/calls/StartScrollTextRoll.c`.

### `gScrollTextTaskClass`

Task descriptor with InitScrollTextWork, ReleaseScrollTextWork, work size 0x30354, flags 0x00110008 and NULL final word.

Evidence: `src/overlays/ov004/calls/InitScrollTextWork.c`, `src/overlays/ov004/calls/ReleaseScrollTextWork.c`.

### `gChildSpawnerStageFrameCounts`

Seven signed 16-bit frame lengths{1,9,47,1,9,37,1} indexed by stage. Length 1 loops; other lengths advance the saved stage when animation completes. Units become FX12 by shifting 12.

Evidence: `src/overlays/ov008/calls/UpdateChildSpawnerStage.c`.

### `gSegmentedObjectJointSuffixes`

Packed signed-byte suffixes indexed by segment to format metal%02d joint names before FindModelResource. Physical 13 u16 words are read as 26 bytes; do not index as 13 u16 entries.

Evidence: `src/overlays/ov008/calls/FieldObject_RespawnSegmented.c`.

### `gSpecialReleaseBurstPosition`

FX12 vector{0,0xae 1,0x151f} copied to the burst request position before submitting it to the configured effect group. No named body part or world-space interpretation is inferred.

Evidence: `src/overlays/ov010/calls/Entity_UpdateSpecialRelease.c`.

### `gSpecialObjectSpriteLoadParameters`

Six two-word param/count pairs copied locally. The caller combines archive entries 2*i and 2*i+1 with these values and stores six returned sprite IDs.

Evidence: `src/overlays/ov010/calls/LoadObjectSprites.c`.

### `gAnimSequenceRotationAdjustment`

FX12 quaternion{0,0xb 50,0xb 50,0} multiplied after the normalized model-result quaternion before rebuilding the matrix. Preserve approximation and multiplication order; no exact angle is inferred.

Evidence: `src/overlays/ov010/calls/AnimSequence_GetCurrentPosition.c`, `src/overlays/ov010/calls/AnimSequence_Update_020a1b70.c`.

### `gOv013SummaryFormatSpaceConcat`

UTF16 format%s %s%s. DrawContextEntrySummary selects it for language index 3; the other consumers may choose their own argument order. Preserve physical padding and UTF16 interpretation.

Evidence: `src/overlays/ov013/calls/DrawContextEntrySummary.c`, `src/overlays/ov013/calls/DrawPanelResultCaption.c`, `src/overlays/ov013/calls/RefreshProgressCaption.c`.

### `gOv013SummaryFormatSpaced`

UTF16 format%s %s %s, with one extra zero u16 in storage. DrawContextEntrySummary selects it for indices 1/2 and reverses argument roles between those cases.

Evidence: `src/overlays/ov013/calls/DrawContextEntrySummary.c`, `src/overlays/ov013/calls/DrawPanelResultCaption.c`, `src/overlays/ov013/calls/RefreshProgressCaption.c`.

### `gOv013SummaryFormatDe`

UTF16 format%s %s de %s. DrawContextEntrySummary selects it for language index 5. The literal word and parameter order are retained.

Evidence: `src/overlays/ov013/calls/DrawContextEntrySummary.c`, `src/overlays/ov013/calls/DrawPanelResultCaption.c`, `src/overlays/ov013/calls/RefreshProgressCaption.c`.

### `gOv013SummaryFormatDi`

UTF16 format%s %s di %s. DrawContextEntrySummary selects it for language index 4. The literal word and parameter order are retained.

Evidence: `src/overlays/ov013/calls/DrawContextEntrySummary.c`, `src/overlays/ov013/calls/DrawPanelResultCaption.c`, `src/overlays/ov013/calls/RefreshProgressCaption.c`.

### `gOv013SummaryFormatConcat`

UTF16 format%s%s%s used by the default/language 0 summary path. The physical 14-u16 definition includes additional zero padding beyond its terminator.

Evidence: `src/overlays/ov013/calls/DrawContextEntrySummary.c`, `src/overlays/ov013/calls/DrawPanelResultCaption.c`, `src/overlays/ov013/calls/RefreshProgressCaption.c`.

### `gOv013PanelGlobals`

First word points to the heap-owned ov 013 panel context. Initialization allocates/clears it and the release path frees it. Remaining 28 bytes of global storage have no independent role proved; do not shrink the definition or infer pointer clearing.

Evidence: `src/overlays/ov013/calls/InitPanelScene_0206c480.c`, `src/overlays/ov013/calls/ReleaseOv013PanelResources.c`, `src/overlays/ov013/calls/InitRecordResultScreen.c`.

### `gRecordPanelFractionFormat`

UTF16 format%d/%d used by the selected-entry information drawing path. Retain both argument order and the 12-byte physical storage.

Evidence: `src/overlays/ov014/calls/DrawSelectedEntryInfo.c`.

### `gOv014PanelGlobals`

First word points to the heap context allocated/cleared by InitRecordPanel, used by category, entry, profile and graphics callbacks. Remaining 28 bytes of global storage are uncharacterized; no separate field layout or release guarantee is asserted.

Evidence: `src/overlays/ov014/calls/InitRecordPanel.c`, `src/overlays/ov014/calls/QueryPanelEntry.c`, `src/overlays/ov014/calls/DrawSelectedEntryInfo.c`.

### `gFloorSwitchCollisionHalfExtents`

FX12 box half-extents{0xb 9a,0xb 9a,0xb 9a} copied for the floor-switch collision query.

Evidence: `src/overlays/ov016/calls/UpdateFloorSwitch.c`.

### `gFieldObjectLaunchUnitScale`

FX12 unit scale{0x1000,0x1000,0x1000} copied as the base scale for the launched-object animation before per-frame adjustment.

Evidence: `src/overlays/ov016/calls/AnimateLaunchedFieldObject.c`.

### `gFieldObjectLoweringStep`

FX12 vector{0,-0x600,0}; its Y component lowers position toward the stored height before collision bounds/actor placement are updated.

Evidence: `src/overlays/ov016/calls/LowerFieldObjectStep.c`.

### `gFieldObjectGroundProbeVector`

FX12 vector{0,-0x64000,0} copied for the downward model-segment ground query. Keep vector magnitude and independent query parameters unchanged.

Evidence: `src/overlays/ov016/calls/SnapFieldObjectToGround.c`.

### `gMovingFieldObjectCollisionHalfExtents`

FX12 box half-extents{0xc 00,0xc 00,0xc 00} used after raising the center Y by 0xc 00; bounds are swept by the current velocity.

Evidence: `src/overlays/ov016/calls/MoveFieldObjectWithCollision.c`.

### `gOverlay016ScriptCommandHandlers`

13 run/resume pointer pairs used by the overlay 016 entry in gScriptHandlerBindingsSlot8. Preserve NULL slots and exact opcode order; do not infer command names for absent entries.

Evidence: `src/overlays/ov016/calls/ScriptCmd_LoadOverlayKind9.c`, `src/overlays/ov016/calls/ScriptCmd_SpawnFieldObjectTree.c`.

### `gGridObjectGroundProbeVector`

FX12 vector{0,-0x64000,0} passed as query.direction from the object's position with separate query.length 0x1800; the hit updates drop offset.

Evidence: `src/overlays/ov017/calls/UpdateGridObjectDropOffsetFromRay.c`.

### `gLinkSettlingSweepDelta`

FX12 vector{0,-0x1e 000,0} copied to the collision shape sweep delta; swept bounds and collision query use that downward displacement.

Evidence: `src/overlays/ov019/calls/SettleLinkHeight.c`.

### `gBlockGroundProbeVector`

FX12 vector{0,-0x64000,0} passed as query.direction from the block position with separate query.length 0x1800; keep its magnitude and query scalar separate.

Evidence: `src/overlays/ov020/calls/ProbeBlockGroundOffset.c`.

## Porting boundaries

Task descriptors contain packed scheduling flags and constructor/destructor pointers; their names identify the proved lifecycle pair, not every packed bit. Borrowed task work must remain distinct from heap-allocated contexts and from the globals that point to them. A cleanup that frees a context without clearing its global does not establish a NULL guarantee.

Text format declarations are UTF16 arrays even where legacy formatter prototypes use char pointers. Their parameter order and physical zero padding are preserved. Frame lengths and collision vectors are FX12 where observed by their consumers; the direction vector and an independent ray length must not be normalized or combined without separate semantic analysis.

The movie helper historically named updateMovieStreamLeadTime actually computes horizontal text layout from measured subtitle width. This document identifies its cached data as layout state without changing that helper or claiming a timing contract. The movie palette storage has a 32-byte loaded prefix in a 64-byte definition; the remainder stays preserved.

The overlay016 command table has 13 run/resume pairs. Its registration is established by `src/overlays/ov001/data/tables/gScriptHandlerBindingsSlot8.c`, which binds the table to overlay ID16; do not infer VM opcode meanings from table address or fill NULL entries.


## Byte-exact validation

44 DATA identities retain their source paths, native sizes and storage.
247/248 affected official function checks pass; the remaining
1 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 283 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
