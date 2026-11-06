# EU wireless menu tables and state storage

These names distinguish wireless UI resource indices, board-selection inputs and SDK state storage. Physical extents are configured definitions, not newly inferred capacities. Preserve all existing values, padding, section placement, relocations and callback interfaces.

## Identity and source map

| EU identity | Name | Physical storage | Definition |
| --- | --- | --- | --- |
| ov015 `0x02079f58` | `gWirelessSelectionSourceWidgetIds` | 12 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_02079f58.c` |
| ov015 `0x02079f64` | `gWirelessSelectionPriorityWidgetIds` | 12 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_02079f64.c` |
| ov015 `0x02079f70` | `gWirelessSlideInWidgetIds` | 12 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_02079f70.c` |
| ov015 `0x02079f7c` | `gWirelessShareSelectionWidgetIds` | 12 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_02079f7c.c` |
| ov015 `0x02079fc8` | `gWirelessSharingMainBgConfig` | 20 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_02079fc8.c` |
| ov015 `0x02079fdc` | `gWirelessSharingSubBgConfig` | 20 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_02079fdc.c` |
| ov015 `0x02079ff0` | `gWirelessAlternateMainBgConfig` | 20 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_02079ff0.c` |
| ov015 `0x0207a034` | `gWirelessSharingMainObjConfig` | 24 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a034.c` |
| ov015 `0x0207a04c` | `gWirelessSharingSubObjConfig` | 24 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a04c.c` |
| ov015 `0x0207a064` | `gWirelessAlternateMainObjConfig` | 24 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a064.c` |
| ov015 `0x0207a07c` | `gWirelessEdgeBottomScreenIds` | 32 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a07c.c` |
| ov015 `0x0207a09c` | `gWirelessSubBodyScreenIds` | 32 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a09c.c` |
| ov015 `0x0207a0bc` | `gWirelessSubHeaderScreenIds` | 32 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a0bc.c` |
| ov015 `0x0207a0dc` | `gWirelessEdgeTopScreenIds` | 32 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a0dc.c` |
| ov015 `0x0207a0fc` | `gWirelessSubNextBgFrame` | 32 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a0fc.c` |
| ov015 `0x0207a11c` | `gWirelessCenterBodyScreenIds` | 32 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a11c.c` |
| ov015 `0x0207a13c` | `gWirelessEdgeNextBgFrame` | 32 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a13c.c` |
| ov015 `0x0207a15c` | `gWirelessCenterHeaderScreenIds` | 32 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a15c.c` |
| ov015 `0x0207a17c` | `gWirelessCenterNextBgFrame` | 32 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a17c.c` |
| ov015 `0x0207a1c8` | `gWirelessRandomProfileRankLimits` | 24 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a1c8.c` |
| ov015 `0x0207a1e0` | `gWirelessFixedRoundRangeWeights` | 8 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a1e0.c` |
| ov015 `0x0207a1e8` | `gWirelessTraceZeroOffsets` | 10 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a1e8.c` |
| ov015 `0x0207a1f2` | `gWirelessTraceLateralOffsets` | 10 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a1f2.c` |
| ov015 `0x0207a218` | `gWirelessPartnerRoundRangeWeights` | 20 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a218.c` |
| ov015 `0x0207a2b8` | `gWirelessResultTitleMessageIds` | 20 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a2b8.c` |
| ov015 `0x0207a2cc` | `gWirelessPartnerResultTitleMessageIds` | 20 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a2cc.c` |
| ov015 `0x0207a2f8` | `gWirelessBoardOverlayWidgetIds` | 24 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a2f8.c` |
| ov015 `0x0207a548` | `gWirelessSpecialSlotChanceByProgress` | 4 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a548.c` |
| ov015 `0x0207a54c` | `gWirelessSpecialGroupWeights` | 8 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a54c.c` |
| ov015 `0x0207a554` | `gWirelessPanelFixedRewardDescriptor` | 12 bytes (rodata) | `src/overlays/ov015/data/tables/data_ov015_0207a554.c` |
| ov015 `0x0207e960` | `gWirelessMenuWork` | 4 bytes (bss) | `src/overlays/ov015/data/bss/Bss_ov015_0207e960.c` |
| ov015 `0x0207e964` | `gWirelessCardExchangeGlobals` | 28 bytes (bss) | `src/overlays/ov015/data/bss/Bss_ov015_0207e960.c` |
| ov015 `0x0207e9e0` | `gWirelessWepKeyStorage` | 20 bytes (bss) | `src/overlays/ov015/data/bss/Bss_ov015_0207e9e0.c` |
| ov015 `0x0207e9f4` | `gWirelessConnectSsidStorage` | 44 bytes (bss) | `src/overlays/ov015/data/bss/Bss_ov015_0207e9e0.c` |
| ov015 `0x0207ea20` | `gWirelessParentParamStorage` | 64 bytes (bss) | `src/overlays/ov015/data/bss/Bss_ov015_0207e9e0.c` |
| ov015 `0x0207eac0` | `gWirelessMpSendBuffer` | 160 bytes (bss) | `src/overlays/ov015/data/bss/Bss_ov015_0207eac0.c` |
| ov015 `0x0207eb60` | `gWirelessParentBssDescriptorStorage` | 192 bytes (bss) | `src/overlays/ov015/data/bss/Bss_ov015_0207eb60.c` |
| ov015 `0x0207ec20` | `gWirelessMpReceiveBuffer` | 896 bytes (bss) | `src/overlays/ov015/data/bss/Bss_ov015_0207ec20.c` |
| ov015 `0x0207f3a0` | `gWirelessKeySharingStorage` | 2080 bytes (bss) | `src/overlays/ov015/data/bss/Bss_ov015_0207f3a0.c` |
| ov015 `0x0207fbc0` | `gWirelessDataSharingStorage` | 1088 bytes (bss) | `src/overlays/ov015/data/bss/Bss_ov015_0207fbc0.c` |

## Consumers and boundaries

### `gWirelessSelectionSourceWidgetIds`

Three widget IDs 1,2,3. The caller resolves position, shows the chosen widget and applies values before building its selection view.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/SetupWirelessSelectionSlotFromWidget.c`.

### `gWirelessSelectionPriorityWidgetIds`

Three widget IDs 1,2,3. The caller sets the chosen widget record priority to 252 after building its selection view.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/SetupWirelessSelectionSlot.c`.

### `gWirelessSlideInWidgetIds`

Three widget IDs 1,2,3 selecting the widget moved from Y=0x12c000 toward its stored position.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/SlideInPanelWidget.c`.

### `gWirelessShareSelectionWidgetIds`

Three widget IDs 1,2,3. A context-flag-selected slot identifies the widget whose move must finish before selection and slide-out.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/UpdatePanelShareState.c`.

### `gWirelessSharingMainBgConfig`

Main background template for the wxc/wla resource, copied before container initialization.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/InitPanelScreenGraphics.c`.

### `gWirelessSharingSubBgConfig`

Sub background template for the wxc/wle resource, copied before container initialization.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/InitPanelScreenGraphics.c`.

### `gWirelessAlternateMainBgConfig`

Background template for the alternate main-screen initialization path.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/InitPanelMainScreen.c`.

### `gWirelessSharingMainObjConfig`

Main object template; resource keys are replaced in a local copy and 25 widget descriptors are loaded.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/InitPanelScreenGraphics.c`.

### `gWirelessSharingSubObjConfig`

Sub object template; resource keys are replaced in a local copy and 13 widget descriptors are loaded.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/InitPanelScreenGraphics.c`.

### `gWirelessAlternateMainObjConfig`

Object template for the alternate main-screen initialization path; resource keys are replaced in a local copy.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/InitPanelMainScreen.c`.

### `gWirelessEdgeBottomScreenIds`

Eight IDs 10..17 read as base[0]; four full-width rows are copied to main BG1 rows 20..23.

Base means the legacy FrameTable view at 0207a07c. Its indexed access crosses separate 32-byte physical definitions. Preserve all nine identities/order; both regions in edge/center helpers use main GX, despite old main/sub local labels.

Evidence: `src/overlays/ov015/calls/AnimateBg1EdgeBandTiles.c`.

### `gWirelessSubBodyScreenIds`

Eight IDs 10..17 selecting the ten-row body region copied to sub BG1.

Base means the legacy FrameTable view at 0207a07c. Its indexed access crosses separate 32-byte physical definitions. Preserve all nine identities/order; both regions in edge/center helpers use main GX, despite old main/sub local labels.

Evidence: `src/overlays/ov015/calls/AnimateSubBg1Screen.c`.

### `gWirelessSubHeaderScreenIds`

Eight IDs 20..27 selecting the two-row header region copied to sub BG1.

Base means the legacy FrameTable view at 0207a07c. Its indexed access crosses separate 32-byte physical definitions. Preserve all nine identities/order; both regions in edge/center helpers use main GX, despite old main/sub local labels.

Evidence: `src/overlays/ov015/calls/AnimateSubBg1Screen.c`.

### `gWirelessEdgeTopScreenIds`

Eight IDs 20..27 read as base[3]; four full-width rows are copied to main BG1 rows 0..3.

Base means the legacy FrameTable view at 0207a07c. Its indexed access crosses separate 32-byte physical definitions. Preserve all nine identities/order; both regions in edge/center helpers use main GX, despite old main/sub local labels.

Evidence: `src/overlays/ov015/calls/AnimateBg1EdgeBandTiles.c`.

### `gWirelessSubNextBgFrame`

Eight next-frame values 1,2,3,4,5,6,7,0 cycling the sub-screen animation.

Base means the legacy FrameTable view at 0207a07c. Its indexed access crosses separate 32-byte physical definitions. Preserve all nine identities/order; both regions in edge/center helpers use main GX, despite old main/sub local labels.

Evidence: `src/overlays/ov015/calls/AnimateSubBg1Screen.c`.

### `gWirelessCenterBodyScreenIds`

Eight IDs 10..17 read as base[5]; ten 12-tile rows are copied to main BG1 rows 6..15.

Base means the legacy FrameTable view at 0207a07c. Its indexed access crosses separate 32-byte physical definitions. Preserve all nine identities/order; both regions in edge/center helpers use main GX, despite old main/sub local labels.

Evidence: `src/overlays/ov015/calls/AnimateBg1CenterTiles.c`.

### `gWirelessEdgeNextBgFrame`

Eight next-frame values 1,2,3,4,5,6,7,0 read as base[6] for the edge animation.

Base means the legacy FrameTable view at 0207a07c. Its indexed access crosses separate 32-byte physical definitions. Preserve all nine identities/order; both regions in edge/center helpers use main GX, despite old main/sub local labels.

Evidence: `src/overlays/ov015/calls/AnimateBg1EdgeBandTiles.c`.

### `gWirelessCenterHeaderScreenIds`

Eight IDs 20..27 read as base[7]; two seven-tile rows are copied to main BG1 offsets 0x1a and 0x5a.

Base means the legacy FrameTable view at 0207a07c. Its indexed access crosses separate 32-byte physical definitions. Preserve all nine identities/order; both regions in edge/center helpers use main GX, despite old main/sub local labels.

Evidence: `src/overlays/ov015/calls/AnimateBg1CenterTiles.c`.

### `gWirelessCenterNextBgFrame`

Eight next-frame values 1,2,3,4,5,6,7,0 read as base[8] for the center animation.

Base means the legacy FrameTable view at 0207a07c. Its indexed access crosses separate 32-byte physical definitions. Preserve all nine identities/order; both regions in edge/center helpers use main GX, despite old main/sub local labels.

Evidence: `src/overlays/ov015/calls/AnimateBg1CenterTiles.c`.

### `gWirelessRandomProfileRankLimits`

Six random-range upper bounds 3,5,8,11,14,17 selected by generated classId 0..5 when choosing rank.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/GenerateRandomProfile.c`.

### `gWirelessFixedRoundRangeWeights`

Four packed signed-byte value/weight pairs {6,40},{7,30},{8,20},{9,10}; selected value becomes rangeIndex when isFixed is nonzero.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/GeneratePanelRound.c`.

### `gWirelessTraceZeroOffsets`

Five zero s16 offsets swapped between X and Y according to the dominant trace axis.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/ClearTilesAlongLine.c`.

### `gWirelessTraceLateralOffsets`

Five s16 offsets 0,1,-1,2,-2 widen the trace over at most five passes; swapped between X and Y by dominant axis.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/ClearTilesAlongLine.c`.

### `gWirelessPartnerRoundRangeWeights`

Ten packed signed-byte value/weight pairs. The considered prefix has partner[0x6b]+1 entries capped at 10; selected value becomes rangeIndex.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/GeneratePanelRound.c`.

### `gWirelessResultTitleMessageIds`

Five message IDs 0,0,7,5,6 indexed by titleIndex to build the player result header.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/SetupResultPanel.c`.

### `gWirelessPartnerResultTitleMessageIds`

Five message IDs 0,0,7,0,0 indexed by titleIndex for the partner body text when resultKind is 6.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/SetupResultPanel.c`.

### `gWirelessBoardOverlayWidgetIds`

Six widget IDs 10,11,12,13,14,19 whose visibility follows board position and mask checks.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/UpdatePanelBoard.c`.

### `gWirelessSpecialSlotChanceByProgress`

First three bytes are chances 8,20,40 selected using progress thresholds 49/79 before adding a special group to eligible slots.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields. The final padding bytes are not additional live entries.

Evidence: `src/overlays/ov015/calls/GeneratePanelRound.c`.

### `gWirelessSpecialGroupWeights`

First six bytes are three signed-byte value/weight pairs selecting groups 0x3a,0x3b,0x3c; copied weight for 0x3b becomes zero when queried level >=99.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields. The final padding bytes are not additional live entries.

Evidence: `src/overlays/ov015/calls/GeneratePanelRound.c`.

### `gWirelessPanelFixedRewardDescriptor`

Six-u16 descriptor {0,284,0,0,100,0} passed as the source descriptor to GrantRewardEntry for one reward step.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields. Literal 284 is not assigned an asset/item name.

Evidence: `src/overlays/ov015/calls/UpdatePanelMinigame.c`.

### `gWirelessMenuWork`

Pointer to the heap-owned 0xdec4-byte wireless menu context. Initialization allocates/clears it and creates graphics; cleanup releases widget groups and frees it without clearing the pointer.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/InitPanelState_0206c480.c`, `src/overlays/ov015/calls/ShutdownPanelState_0206c4d4.c`, `src/overlays/ov015/calls/SetupWirelessSelectionSlot.c`.

### `gWirelessCardExchangeGlobals`

First word points to the heap-owned card-exchange context, which owns one send and four receive buffers, each 0x80 bytes aligned 32. Cleanup frees buffers/context without clearing the global.

Only the first-word pointer is characterized; the remaining 24 bytes have no independent field role proved. Do not shrink this definition to one pointer.

Evidence: `src/overlays/ov015/calls/InitShareBuffers.c`, `src/overlays/ov015/calls/FreePanelBuffers.c`, `src/overlays/ov015/calls/BeginPeerCardExchange.c`.

### `gWirelessWepKeyStorage`

Static storage passed to the key generator and WM_SetWEPKey in child/parent key setup. Its configured definition is 20 bytes; the SDK cache-maintenance span is separately 80 bytes.

WM_SetWEPKey performs DC_StoreRange for 80 bytes when WEP mode is nonzero, crossing e9f4 and the first 16 bytes of ea20. No 20-byte SDK key capacity is claimed; preserve physical layout without fusion/retyping.

Evidence: `src/overlays/ov015/calls/SetChildWepKey.c`, `src/overlays/ov015/calls/WH_RequestParentWepKey.c`.

### `gWirelessConnectSsidStorage`

Static storage cleared for 24 bytes and passed as ssid to WM_StartConnectEx, whose local SDK implementation copies 24 bytes into the request.

Physical storage is 44 bytes, but only a 24-byte SSID payload is established. The remaining 20 bytes have no independent role proved; the address also lies inside the WEP cache-flush span.

Evidence: `src/overlays/ov015/calls/WH_Initialize.c`, `src/overlays/ov015/calls/StartWirelessChild.c`.

### `gWirelessParentParamStorage`

Parent-parameter storage. Initialization clears userGameInfo pointer/length; parent setup uses the block, and SetWirelessSessionParam writes its word at +8.

Do not infer every private parent-parameter field. The first 16 bytes are also inside the 80-byte cache-flush span beginning at the WEP storage.

Evidence: `src/overlays/ov015/calls/WH_Initialize.c`, `src/overlays/ov015/calls/WH_ParentConnect.c`, `src/overlays/ov015/calls/SetWirelessSessionParam.c`.

### `gWirelessMpSendBuffer`

Static sendBuf passed to WM_StartMP by parent/child setup, together with the separate runtime sendBufferSize.

Physical capacity and runtime API size are separate facts. No new bounds check, allocation, alignment change or ownership transfer is proposed.

Evidence: `src/overlays/ov015/calls/StartWirelessMP.c`, `src/overlays/ov015/calls/WH_StateInStartChildMP.c`.

### `gWirelessParentBssDescriptorStorage`

Static parent BSS descriptor storage cleared for 192 bytes, passed as pInfo to WM_StartConnectEx and to the child key generator.

This descriptor is distinct from the 24-byte child SSID payload. WM_StartConnectEx uses descriptor.length for its cache span, not this definition size as an unconditional bound.

Evidence: `src/overlays/ov015/calls/WH_Initialize.c`, `src/overlays/ov015/calls/StartWirelessChild.c`, `src/overlays/ov015/calls/SetChildWepKey.c`.

### `gWirelessMpReceiveBuffer`

Static recvBuf passed to WM_StartMP by parent/child setup, together with the separate runtime recvBufferSize.

Physical capacity and runtime API size are separate facts. No new bounds check, allocation, alignment change or ownership transfer is proposed.

Evidence: `src/overlays/ov015/calls/StartWirelessMP.c`, `src/overlays/ov015/calls/WH_StateInStartChildMP.c`.

### `gWirelessKeySharingStorage`

Static state storage passed to WM_StartKeySharing on port 13 and to paired key-sharing end paths.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/StartWirelessKeySharing.c`, `src/overlays/ov015/calls/EndWirelessKeySharing.c`, `src/overlays/ov015/calls/WH_StartPort13DataSharing.c`.

### `gWirelessDataSharingStorage`

Static state storage passed to WM_StartDataSharing after MP completion and used by reset/finalize paths; it is distinct from key-sharing storage.

Preserve existing values, types, padding, ordering and relocations. No gameplay role is inferred for unnamed numeric fields.

Evidence: `src/overlays/ov015/calls/WH_StateOutStartChildMP.c`, `src/overlays/ov015/calls/WH_StateOutStartParentMP.c`, `src/overlays/ov015/calls/WH_Reset.c`, `src/overlays/ov015/calls/WH_Finalize.c`.

## Native storage relationships

The nine 32-byte frame tables from `0207a07c` through `0207a17c` remain separate physical definitions. Edge helpers use the base view at indices 0/3/6; center helpers use 5/7/8. Both copy regions with main-engine `GX_LoadBG1Scr`. The independent sub-screen helper references the tables at `0207a09c`, `0207a0bc` and `0207a0fc` directly. A missing direct symbol reference does not make the indexed tables unused.

The WEP storage at `0207e9e0` occupies 20 bytes, followed by 44-byte storage at `0207e9f4` and 64-byte parent parameters at `0207ea20`. The local `WM_SetWEPKey` implementation performs an 80-byte `DC_StoreRange` for nonzero WEP mode (`nitro/wm.h`: `WM_SIZE_WEPKEY`). That cache-maintenance span crosses the physical symbol boundaries. This does not establish separate 80-byte key allocation or authorize changing the contiguous native layout.

The local `WM_StartConnectEx` implementation copies a 24-byte SSID payload. MP send/receive calls take runtime sizes separately from their static definitions. Key-sharing and data-sharing state use different addresses and must not be confused with MP payload buffers.

## Ownership

The wireless menu owns a 0xdec4-byte heap context; its destructor frees it without clearing the stored pointer. The card-exchange context owns one send buffer and four receive buffers, each 0x80 bytes aligned to 32 bytes; release also leaves the global pointer uncleared. Other storage listed here has static lifetime. Naming does not add ownership transfers, NULL guarantees or bounds checks.

## Logical data-sharing storage span

`gWirelessDataSharingStorage` identifies the physical definition beginning at EU `0207fbc0`. That definition occupies 1088 bytes, while the native SDK routine uses a logical 2080-byte (`0x820`) data-sharing state beginning at the same address. Its initialization clears the whole range through `020803e0`. The range includes the existing physical fragments at `02080000`, `02080202`, `0208020e` and `02080303`; they are not independent SDK allocations.

Native evidence is `WM_StartDataSharing` relative +0x50/+0x52, which forms `0x82 << 4`, +0x58, which passes it in R2, and +0x5c, the call to `MIi_CpuClearFast`. The local implementation in `src/calls/WM_StartDataSharing.c` imports `src/arm9/library_nitro_wm/WM_StartDataSharing_02011cc0.c`, whose four 512-byte data sets and 32-byte index/control tail describe the same span.

For a port, keep this logical SDK state separate from the physical symbol fragments used to reproduce the original layout. Preserve native offsets and existing aliases until a separately verified representation unifies them. The later BSS beginning `020803e0` is outside the proved initialization span; no owner is inferred for it here.


## Byte-exact validation

40 DATA identities retain their source paths, native sizes and storage.
All 105 affected official function checks pass. A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 142 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```

## Reward result and declaration boundary

[WIRELESS_REWARD_INTERFACE.md](WIRELESS_REWARD_INTERFACE.md) proves the native
0/1 result and records the intentionally transmitted but unread peer-descriptor
word. The existing record and caller/callee declaration views still need a
coherent interface cleanup; these DATA identities do not supply a portable C
prototype or justify an invented parameter.
