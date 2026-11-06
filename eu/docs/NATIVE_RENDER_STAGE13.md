# Render, IRQ, sound and stage resource DATA (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

## Native owner boundaries

Vertex-color tables, material scaling globals, the IRQ wait queue and sound alarm records have separate native owners. Stage resource loading is represented by a loaded flag and a separate five-word container/selection object. Submode work and backend camera blocks have different lifetimes. The interpreter context backup is a single global and is not restored on every early return. Names preserve those limits; no storage, code or ABI is changed.

## Inventory and evidence

### `dtcm:027e0058` → `gTexturedBoxXFaceColors`

Previous label `data_027e0058`; existing ELF size **16 bytes**. Source: `eu/src/dtcm/data/Data_dtcm_027e0058.c`.

16 initialized bytes: two rows of four u16 vertex colors for the positive/negative X-facing box faces.

DrawTexturedBox selects side from the camera-relative X coordinate and sends the selected four halfwords directly to reg_G3_COLOR while emitting that face.

Limits: The table is fixed color data, not a geometry allocation. Preserve both rows and u32 source representation.

Pinned references:

- `eu/src/calls/DrawTexturedBox.c`; reference line(s) 49, 98, 101, 104, 107.
- `eu/src/dtcm/data/Data_dtcm_027e0058.c`; reference line(s) 5.

### `dtcm:027e0068` → `gTexturedBoxYFaceColors`

Previous label `data_027e0068`; existing ELF size **16 bytes**. Source: `eu/src/dtcm/data/Data_dtcm_027e0068.c`.

16 initialized bytes: two rows of four u16 vertex colors for the positive/negative Y-facing box faces.

DrawTexturedBox selects the row from the camera-relative Y coordinate and writes its four colors while emitting the Y face.

Limits: Some wireless translation units carry unused declarations/macros for this address in their shared preamble. Those declarations do not prove a wireless data owner; the drawing body demonstrates the consumed layout.

Pinned references:

- `eu/src/calls/DrawTexturedBox.c`; reference line(s) 50, 117, 120, 123, 126.
- `eu/src/dtcm/data/Data_dtcm_027e0068.c`; reference line(s) 11.
- `eu/src/overlays/ov015/calls/RecordWirelessChannelMeasurement.c`; reference line(s) 435, 437.
- `eu/src/overlays/ov015/calls/SelectWirelessChannelFromBitmap.c` → `src/ov015/wireless_channel_selection/SelectWirelessChannelFromBitmap_02074b4c.c`; reference line(s) 435, 437.
- `eu/src/overlays/ov015/calls/WH_StateInEndChild.c`; reference line(s) 466, 468.
- `eu/src/overlays/ov015/calls/measure_next_allowed_wireless_channel.c` → `src/ov015/wireless/measure_next_allowed_wireless_channel_020749b8.c`; reference line(s) 466, 468.

### `dtcm:027e0078` → `gTexturedBoxZFaceColorStorage`

Previous label `data_027e0078`; existing ELF size **40 bytes**. Source: `eu/src/dtcm/data/Data_dtcm_027e0068.c`.

40 initialized bytes; the first sixteen are two rows of four u16 Z-face colors, and the remaining 24 bytes are not assigned a role.

DrawTexturedBox consumes the two Z-face rows. DrawTexturedGridQuads consumes the first four halfwords when useColors is true, otherwise it emits color 0x7fff.

Limits: Preserve all 40 bytes; do not shrink to the sixteen-byte box-face view or infer that all twenty halfwords are used by the visible drawers.

Pinned references:

- `eu/src/calls/DrawTexturedBox.c`; reference line(s) 51, 136, 139, 142, 145.
- `eu/src/dtcm/data/Data_dtcm_027e0068.c`; reference line(s) 5.
- `eu/src/overlays/ov001/calls/DrawTexturedGridQuads.c` → `src/ov001/shared_engine/DrawTexturedGridQuads_020866ac.c`; reference line(s) 30, 61, 66, 71, 76.

### `dtcm:027e01ec` → `gMaterialColorScaleEnabledStorage`

Previous label `data_027e01ec`; existing ELF size **4 bytes**. Source: `eu/src/data/dtcm/bss/Bss_dtcm_027e01ec.c`.

4-byte BSS object whose low u16 enables material color scaling; upper halfword opaque.

setMaterialColorScale sets the low halfword to 1. NNSi_G3dFuncSbcMAT uses nonzero to choose scaled material color. NNS_G3dDraw clears it after the draw completes.

Limits: The flag is reset after a complete model draw, not after each material. Preserve the four-byte object and existing u16 views.

Pinned references:

- `eu/src/calls/NNS_G3dDraw.c`; reference line(s) 14, 38.
- `eu/src/calls/NNSi_G3dFuncSbcMAT.c` → `src/itcm/library_nitro_nns/NNSi_G3dFuncSbcMAT_01ffe3d8.c`; reference line(s) 181, 393.
- `eu/src/calls/setMaterialColorScale.c` → `src/itcm/graphics/setMaterialColorScale_01fff67c.c`; reference line(s) 10, 14.
- `eu/src/data/dtcm/bss/Bss_dtcm_027e01ec.c`; reference line(s) 5.

### `dtcm:027e01f0` → `gMaterialColorScaleStorage`

Previous label `data_027e01f0`; existing ELF size **8 bytes**. Source: `eu/src/data/dtcm/bss/Bss_dtcm_027e01ec.c`.

8-byte BSS object: u16 red/green/blue scale values at 0/2/4, with final two bytes opaque.

setMaterialColorScale extracts each five-bit packed-color component and stores component+1. NNSi_G3dFuncSbcMAT passes this prefix to ScaleMaterialColor when scaling is enabled.

Limits: The values are 1..32 after the setter, not raw 0..31 components or a packed color word. Do not shrink the object to six bytes or claim its tail is another channel.

Pinned references:

- `eu/src/calls/NNSi_G3dFuncSbcMAT.c` → `src/itcm/library_nitro_nns/NNSi_G3dFuncSbcMAT_01ffe3d8.c`; reference line(s) 182, 397.
- `eu/src/calls/setMaterialColorScale.c` → `src/itcm/graphics/setMaterialColorScale_01fff67c.c`; reference line(s) 9, 15, 16, 17.
- `eu/src/data/dtcm/bss/Bss_dtcm_027e01ec.c`; reference line(s) 4.

### `dtcm:027e00a0` → `gIrqWaitThreadQueue`

Previous label `data_027e00a0`; existing ELF size **8 bytes**. Source: `eu/src/data/dtcm/bss/Bss_dtcm_027e00a0.c`.

8-byte DTCM BSS thread-queue head/tail storage.

OS_InitIrqTable clears both words. OS_WaitIrq passes this address to OS_SleepThread while its requested IRQ flags remain absent. The native OS_IrqHandler_ThreadSwitch walks queued threads, marks them runnable and clears both head/tail words.

Limits: This is the wait queue, separate from the IRQ check flags at DTCM+0x3ff8. The existing ARM scheduling path remains native assembly; no concurrency model is replaced.

Pinned references:

- `eu/libs/nitro/os/calls/OS_InitIrqTable.c` → `src/arm9/library_nitro_os/OS_InitIrqTable_02001d78.c`; reference line(s) 1, 4, 5.
- `eu/libs/nitro/os/calls/OS_WaitIrq.c` → `src/arm9/library_nitro_os/OS_WaitIrq_02001bf8.c`; reference line(s) 11, 34.
- `eu/src/asm_stubs/calls/OS_IrqHandler_ThreadSwitch.c` → `src/itcm/asm/OS_IrqHandler_ThreadSwitch_01ff81b0.c`; reference line(s) 2, 9, 24.
- `eu/src/data/dtcm/bss/Bss_dtcm_027e00a0.c`; reference line(s) 3.

### `main:02057c34` → `gSoundInitialized`

Previous label `data_02057c34`; existing ELF size **4 bytes**. Source: `eu/src/data/bss/Bss_main_02057c34.c`.

4-byte BSS initialization guard.

SND_Init returns immediately when nonzero; otherwise stores TRUE before initializing the sound command mutex, command queues and alarm handlers.

Limits: The flag is set before the subsequent initializers run. It is not a proof that every initialization step completed, and no rollback state is added.

Pinned references:

- `eu/libs/nitro/snd/calls/SND_Init.c` → `src/arm9/library_nitro_snd/func_0200ed90.c`; reference line(s) 46, 48.
- `eu/src/data/bss/Bss_main_02057c34.c`; reference line(s) 8.

### `main:02059720` → `gSoundAlarmHandlers`

Previous label `data_02059720`; existing ELF size **96 bytes**. Source: `eu/src/data/bss/Bss_main_02059708.c`.

96-byte BSS array of eight twelve-byte records: callback word 0, argument word 4, byte generation ID 8, three padding bytes.

SND_AlarmInit clears each callback/argument/ID. SNDi_SetAlarmHandler stores callback+argument and increments/returns the byte ID. SNDi_IncAlarmId increments that byte. SNDi_CallAlarmHandler extracts alarm index and ID from the message, invokes callback(arg) only when generation matches and callback is non-NULL.

Limits: Keep the padding bytes. The invoker does not enforce alarmIndex < 8 in the visible C; no bounds checks or callback return contract is introduced.

Pinned references:

- `eu/libs/nitro/snd/calls/SND_AlarmInit.c` → `src/arm9/library_nitro_snd/SND_AlarmInit_0200f4d0.c`; reference line(s) 14, 21, 22, 23.
- `eu/libs/nitro/snd/calls/SNDi_CallAlarmHandler.c` → `src/arm9/library_nitro_snd/func_0200f558.c`; reference line(s) 48, 49.
- `eu/libs/nitro/snd/calls/SNDi_IncAlarmId.c` → `src/arm9/library_nitro_snd/func_0200f508.c`; reference line(s) 1, 4.
- `eu/libs/nitro/snd/calls/SNDi_SetAlarmHandler.c` → `src/arm9/library_nitro_snd/func_0200f528.c`; reference line(s) 48, 49.
- `eu/src/data/bss/Bss_main_02059708.c`; reference line(s) 3.

### `ov021:020b5624` → `gCharacterSoundCueArchive`

Previous label `data_ov021_020b5624`; existing ELF size **4 bytes**. Source: `eu/src/overlays/ov021/data/bss/Bss_ov021_020b5624.c`.

4-byte BSS archive/container result word.

OpenCharacterSoundCueArchive stores Msg_OpenContainerAndReadHeader for ba/ch/se.p2 with mode 0x11. LoadCharacterSoundCueTable uses the word to form resource IDs. FreeCueTable_020a7ccc passes it to ZeroHalfThenFree when nonzero and then clears it.

Limits: The native loader still uses inherited PathGraph/PathPoint typedef labels; actual archive/file and sound-cue consumers establish the role. Do not copy those path labels into a port interface.

Pinned references:

- `eu/src/overlays/ov021/calls/FreeCueTable_020a7ccc.c` → `src/ov021/shared_engine/FreeCueTable_020a7cac.c`; reference line(s) 2, 5, 6, 8.
- `eu/src/overlays/ov021/calls/LoadCharacterSoundCueTable.c` → `src/ov021/object_state/LoadPathGraph_020a7cc8.c`; reference line(s) 72, 84.
- `eu/src/overlays/ov021/calls/OpenCharacterSoundCueArchive.c`; reference line(s) 3, 8.
- `eu/src/overlays/ov021/data/bss/Bss_ov021_020b5624.c`; reference line(s) 3.

### `ov021:020b5640` → `gEffectResourceContainersLoaded`

Previous label `data_ov021_020b5640`; existing ELF size **4 bytes**. Source: `eu/src/overlays/ov021/data/bss/Bss_ov021_020b5640.c`.

4-byte BSS loaded flag preceding the separate resource-container storage.

LoadMsgContainers opens three names from gEffectResourceSets and sets TRUE. FreeSharedBuffers releases the three published containers only when this flag is nonzero, then clears it.

Limits: Other native views are anchored at this address and access the neighboring container/selection words. This four-byte flag is not the entire logical resource set.

Pinned references:

- `eu/src/overlays/ov021/calls/ClearPendingWord.c` → `src/ov021/unclassified_helpers/ClearPendingWord_020a95b4.c`; reference line(s) 8, 12, 13.
- `eu/src/overlays/ov021/calls/FreeSharedBuffers.c`; reference line(s) 8, 18, 23.
- `eu/src/overlays/ov021/calls/GetTimedEntryKey.c` → `src/ov021/shared_engine/GetTimedEntryKey_020a96dc.c`; reference line(s) 9, 13, 15.
- `eu/src/overlays/ov021/calls/LoadMsgContainers.c`; reference line(s) 13, 27.
- `eu/src/overlays/ov021/calls/MakePaletteUploadParams130.c` → `src/ov021/shared_engine/MakePaletteUploadParams130_020a9744.c`; reference line(s) 8, 11.
- `eu/src/overlays/ov021/calls/MakePaletteUploadParams145.c` → `src/ov021/shared_engine/MakePaletteUploadParams145_020a976c.c`; reference line(s) 8, 11.
- `eu/src/overlays/ov021/calls/MakePaletteUploadParams160.c` → `src/ov021/shared_engine/MakePaletteUploadParams160_020a9664.c`; reference line(s) 8, 11.
- `eu/src/overlays/ov021/calls/MakePaletteUploadParams20.c` → `src/ov021/shared_engine/MakePaletteUploadParams20_020a95ec.c`; reference line(s) 8, 11.
- `eu/src/overlays/ov021/calls/MakePaletteUploadParams210.c` → `src/ov021/shared_engine/MakePaletteUploadParams210_020a963c.c`; reference line(s) 8, 11.
- `eu/src/overlays/ov021/calls/MakePaletteUploadParams230.c` → `src/ov021/shared_engine/MakePaletteUploadParams230_020a9614.c`; reference line(s) 8, 11.
- `eu/src/overlays/ov021/calls/MakePaletteUploadParams40.c` → `src/ov021/shared_engine/MakePaletteUploadParams40_020a968c.c`; reference line(s) 8, 11.
- `eu/src/overlays/ov021/calls/MakePaletteUploadParams60.c` → `src/ov021/shared_engine/MakePaletteUploadParams60_020a96b4.c`; reference line(s) 8, 11.
- `eu/src/overlays/ov021/calls/MakeVramUploadParams.c` → `src/ov021/shared_engine/MakeVramUploadParams_020a95c8.c`; reference line(s) 8, 11.
- `eu/src/overlays/ov021/calls/SetPendingFromTable.c` → `src/ov021/unclassified_helpers/SetPendingFromTable_020a9598.c`; reference line(s) 9, 14, 15, 16.
- `eu/src/overlays/ov021/data/bss/Bss_ov021_020b5640.c`; reference line(s) 4.

### `ov021:020b5644` → `gEffectResourceContainerStorage`

Previous label `data_ov021_020b5644`; existing ELF size **20 bytes**. Source: `eu/src/overlays/ov021/data/bss/Bss_ov021_020b5640.c`.

20-byte BSS symbol: three container words at 0/4/8, selected/pending container word at0xc, selection index at0x10.

LoadMsgContainers writes the three entries through a combined view anchored four bytes before this object. SetPendingFromTable copies containers[index] into pending only when pending is zero and stores index. ClearPendingWord clears pending. MakeVramUploadParams and related helpers use pending to form packed resource identifiers.

Limits: FreeSharedBuffers clears the separate loaded flag but leaves these words unchanged. Do not call the pending word a VRAM address merely because one old partial typedef does; the demonstrated operation forms resource IDs.

Pinned references:

- `eu/src/overlays/ov021/calls/FreeSharedBuffers.c`; reference line(s) 9, 12.
- `eu/src/overlays/ov021/calls/LoadMsgContainers.c`; reference line(s) 14, 17.
- `eu/src/overlays/ov021/calls/SetPendingFromTable.c` → `src/ov021/unclassified_helpers/SetPendingFromTable_020a9598.c`; reference line(s) 10, 15.
- `eu/src/overlays/ov021/data/bss/Bss_ov021_020b5640.c`; reference line(s) 3.

### `ov021:020b56c0` → `gActiveSubModeState`

Previous label `data_ov021_020b56c0`; existing ELF size **4 bytes**. Source: `eu/src/overlays/ov021/data/bss/Bss_ov021_020b56c0.c`.

4-byte BSS pointer to current submode TaskObject work; pointee prefix contains mode, block, update callback and heap reference.

StartSubMode publishes GetRunningTaskWork, clears its sixteen-byte prefix, sets heap/mode, allocates and clears a mode-sized block, loads the selected overlay and stores the initializer-returned update callback. Dispatchers route by the stored mode. ReleaseActiveSubModeOverlay runs the selected release, unloads its overlay, stores mode=-1, calls the native free API with work words 1/3 and clears work word 1.

Limits: Release does not set this global pointer to NULL. Keep the native free API argument views unchanged; do not infer parameter ordering from inherited names. This pointer is distinct from the backend camera work allocation.

Pinned references:

- `eu/src/overlays/ov021/calls/CopySubModeState.c` → `src/ov021/sub_mode/CopySubModeState_020af634.c`; reference line(s) 7, 14.
- `eu/src/overlays/ov021/calls/DispatchModeUpdate.c` → `src/ov021/sub_mode/DispatchModeUpdate_020af4ac.c`; reference line(s) 16, 22.
- `eu/src/overlays/ov021/calls/ForwardSubModeEnd.c` → `src/ov021/sub_mode/ForwardSubModeEnd_020af7e4.c`; reference line(s) 3, 8.
- `eu/src/overlays/ov021/calls/ForwardSubModeEvent.c` → `src/ov021/sub_mode/ForwardSubModeEvent_020af664.c`; reference line(s) 7, 14.
- `eu/src/overlays/ov021/calls/ForwardSubModePairA.c` → `src/ov021/sub_mode/ForwardSubModePairA_020af544.c`; reference line(s) 7, 15.
- `eu/src/overlays/ov021/calls/ForwardSubModePairB.c` → `src/ov021/sub_mode/ForwardSubModePairB_020af57c.c`; reference line(s) 7, 15.
- `eu/src/overlays/ov021/calls/ForwardSubModeStart.c` → `src/ov021/sub_mode/ForwardSubModeStart_020af7b8.c`; reference line(s) 3, 8.
- `eu/src/overlays/ov021/calls/ForwardSubModeValue.c` → `src/ov021/sub_mode/ForwardSubModeValue_020af694.c`; reference line(s) 7, 14.
- `eu/src/overlays/ov021/calls/GetActiveCameraCullingOrigin.c`; reference line(s) 7, 16.
- `eu/src/overlays/ov021/calls/GetActiveCameraViewPlaneNormals.c`; reference line(s) 3, 11.
- `eu/src/overlays/ov021/calls/GetActiveSubMode.c`; reference line(s) 1, 4.
- `eu/src/overlays/ov021/calls/GetActiveSubModeCameraWork.c`; reference line(s) 7, 16.
- `eu/src/overlays/ov021/calls/HasDefaultSubModeCameraChangePending.c`; reference line(s) 3, 9.
- `eu/src/overlays/ov021/calls/IsPointWithinActiveCameraView.c`; reference line(s) 3, 11.
- `eu/src/overlays/ov021/calls/IsShapeWithinActiveCameraView.c` → `src/ov021/reviewed_helpers/func_ov021_020af738.c`; reference line(s) 3, 11.
- `eu/src/overlays/ov021/calls/NotifySubModeEvent.c` → `src/ov021/sub_mode/NotifySubModeEvent_020af6c4.c`; reference line(s) 7, 15.
- `eu/src/overlays/ov021/calls/QuerySubModeStatus.c` → `src/ov021/sub_mode/QuerySubModeStatus_020af3f4.c`; reference line(s) 7, 15.
- `eu/src/overlays/ov021/calls/ReleaseActiveSubModeOverlay.c`; reference line(s) 3, 13, 26, 27, 29, 30.
- `eu/src/overlays/ov021/calls/RunSubModeUpdate.c` → `src/ov021/sub_mode/RunSubModeUpdate_020af364.c`; reference line(s) 12, 16, 18.
- `eu/src/overlays/ov021/calls/SetSubModeFrozen.c` → `src/ov021/sub_mode/SetSubModeFrozen_020af434.c`; reference line(s) 7, 15.
- `eu/src/overlays/ov021/calls/StartSubMode.c` → `src/ov021/sub_mode/StartSubMode_020af260.c`; reference line(s) 12, 47, 49, 50, 51, 53, 54, 56, 61, 64, 67, 70.
- `eu/src/overlays/ov021/calls/UpdateActiveSubModeCamera.c`; reference line(s) 3, 10.
- `eu/src/overlays/ov021/calls/UpdateSubModeResult.c` → `src/ov021/sub_mode/UpdateSubModeResult_020af46c.c`; reference line(s) 7, 16.
- `eu/src/overlays/ov021/data/bss/Bss_ov021_020b56c0.c`; reference line(s) 9.

### `ov021:020b56d0` → `gStageScriptContextBackup`

Previous label `data_ov021_020b56d0`; existing ELF size **12 bytes**. Source: `eu/src/overlays/ov021/data/bss/Bss_ov021_020b56d0.c`.

12-byte BSS backup of three active context pointers: event record, link and actor/player.

RunScriptThread copies the current active context into this backup, clears/rebuilds the active context according to thread owner, then restores it from the backup on its normal final return.

Limits: The backup is one shared global, not a stack. Early returns in RunScriptThread occur before the final restore; do not promise exception safety, reentrancy or unconditional restoration.

Pinned references:

- `eu/src/overlays/ov021/calls/RunScriptThread.c`; reference line(s) 44, 64, 134.
- `eu/src/overlays/ov021/data/bss/Bss_ov021_020b56d0.c`; reference line(s) 4.


## Byte-exact validation

98 DATA identities retain their source paths, native sizes and storage.
280/282 affected official function checks pass; the remaining
2 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 348 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
