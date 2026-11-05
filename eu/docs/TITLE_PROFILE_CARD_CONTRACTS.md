# Title, profile panel and player-card list contracts

This block describes 58 native EU ARM functions: eight in overlay 000, 25 in
overlay 002, 24 in overlay 013 and one companion in overlay 014. The names follow
matched bodies and their consumers. They are descriptive names, not claims of
original spelling. No overlay 015 work belongs to this block.

The source columns identify the accepted EU wrappers.
Each wrapper must be interpreted through its aliases when it includes a shared
body: root US filenames and template SDK prototypes are not proof of the EU
owner or signature. The naming block was integrated after
`16ba14a163baa01aff8a74d4a12a2589d0c05b2e`; the validation section records
the official checks and unchanged bytes.

## Owners and lifetimes

The title panel in ov000 is the object passed to its callbacks. Its session
holder `data_ov000_02063a08` points to a separate two-word record: word +4 is
the status read by `HandleSessionModeTransition`, while word +0 is copied to
the panel only on status 1. The old library placement of one getter does not
prove CARD API ownership or a CARD result enum. The two guarded title resources
released by this block are embedded resources, not the allocation of the
outer title panel.

Overlay 002 has two different owners. `InitProfilePanel` obtains task work,
clears 0x130 bytes and stores it in `data_ov002_0206c460` (also exposed as
`gOv002PanelState` by the typed header). This owner contains key repeat, fonts,
four text layers and a packed-message view. The separate pointer at
`data_ov002_0206c464` owns the larger menu context used by background animation
and `ReleaseContextResources`. Releasing the latter must not be substituted
for destroying the former task work.

| Ov002 panel offset | Meaning established by initializer/updater |
|---:|---|
| +0x10 | Flags: independent initialized and MAIN pending-upload masks |
| +0x11 | Flags: SUB pending-upload masks and other panel state |
| +0x12 | Borrowed input/key-repeat record initialized as 26 bytes |
| +0x30 | Font view supplied to text-layer constructors |
| +0x48 / +0x7c | MAIN text layers 0 / 1 |
| +0xb0 / +0xe4 | SUB text layers 2 / 3 |
| +0x118 | Packed-resource view used by message lookup |

The text layers own list/buffer resources guarded by initialized bits. Releasing
those resources leaves the outer panel work intact. Resetting a layer and
marking it pending for upload is distinct from destroying it. `UpdatePanelState`
uploads only initialized layers whose corresponding pending bit is set, then
clears the four pending bits.

Owner nickname/message buffers live in MAIN storage rather than either menu
allocation. `InitProfilePanel` fills and processes them once under its cache
flag, using `OS_GetOwnerInfo`, wide-string copies and banned-word processing.
The getters return borrowed UTF-16 addresses. Native declarations that call
these DATA symbols functions or cast their addresses to `int` must not become
host callback types or truncated host pointers.

Overlay 013 uses `data_ov013_02074ce0` for its player-card list context. Its
animator containers at +0x304/+0x350, object groups at +0x39c/+0x6818, list
fields and callback-state bytes are views into that owner. Overlay 014 uses
the separate `data_ov014_0206f9a0`; the one companion refresh below does not
share the ov013 owner. These partial views do not establish complete portable
layouts or allocation sizes.

## Title panel: eight identities

| Native identity | Name | EU source wrapper | Contract |
|---|---|---|---|
| ov000:0x02061b88 | `SetTitleBrightnessAndMaybeWaitVBlank` | `src/overlays/ov000/calls/SetTitleBrightnessAndMaybeWaitVBlank.c` | Inputs: brightness and wait flag. Applies the same value to MAIN and SUB brightness helpers; waits one VBlank only when the second input is nonzero. Logical operation is void. The legacy first call omits its explicit input; ROM shows incoming R0 reaches that setter. |
| ov000:0x02062318 | `UpdateTitleTimedPanelPhase` | `src/overlays/ov000/calls/UpdateTitleTimedPanelPhase.c` | With borrowed title work, increments the timer at +0x24. At 60 or more returns next phase 1..5 from phase +0x2c, after setting transition parameters; otherwise returns -1. Phase-0 key mask 0x9 or a touch rising edge forces timer 60 for the next call, not an immediate second dispatch. |
| ov000:0x0206276c | `ApplyTitleMenuFlagsAndStoreLanguage` | `src/overlays/ov000/calls/ApplyTitleMenuFlagsAndStoreLanguage.c` | With borrowed title panel, applies menu flags with TRUE, then writes GetLanguageIndex() into global packed field 0x1a02, width 3. No allocation or result. |
| ov000:0x02062908 | `ReleaseTitlePanelResources` | `src/overlays/ov000/calls/ReleaseTitlePanelResources.c` | Releases two guarded resources within the same title owner, via ReleaseObjectIfActive and ReleaseEmbeddedIfActive. Does not free that outer owner. The inherited NNS cell-animation/sequence signature does not describe the actual large game object. |
| ov000:0x02062a58 | `RecordTitleStartTickWrapper` | `src/overlays/ov000/calls/RecordTitleStartTickWrapper.c` | No logical input. Forwards the helper storing OS_GetTick() at main global data_0205fe00 +0x18. The wrapper's inherited pointer return is not an established owned pointer or logical result. |
| ov000:0x0206300c | `SetupTitleDisplayBanksAndLayersWrapper` | `src/overlays/ov000/calls/SetupTitleDisplayBanksAndLayersWrapper.c` | No logical input. Forwards setup of display VRAM banks, graphics modes, BG controls and SUB blend state. The inherited pointer return does not establish a returned resource. |
| ov000:0x02063770 | `GetTitleSessionStatus` | `src/overlays/ov000/calls/GetTitleSessionStatus.c` | Returns the signed word at +4 of the record pointed to by the title holder data_ov000_02063a08. Its consumer distinguishes 0/1/2; status 1 stores the companion value and marks session ready. No CARD API result enum is proved. |
| ov000:0x02063784 | `GetTitleSessionValue` | `libs/nitro/card/calls/GetTitleSessionValue.c` | Returns the first word of the same borrowed title-session record. HandleSessionModeTransition stores it only on status 1. The old nitro/card placement and card-result comment do not establish a card result code. |

## Profile panel, graphics and persistent record adapters

The last seven adapters in this group access save-global data through
`data_0205fe0c`. Packed record fields at save +0x276c and category flag sets at
+0x2788 are distinct regions. Their bit widths and category mapping are part of
the native data format. No equipment/ability meaning is assigned merely from
the use of records.

`ClearGlobalMenuRecordField` is a significant native ABI boundary. The 508-byte
ARM `ClearPackedField` body contains no calls, relocations or instructions that
write R0. The caller can therefore observe its unchanged input pointer in R0,
even though the reconstructed callee currently declares a void result. Its
optional output is a DS pointer word. A port should preserve the logical pointer
identity explicitly; treating it as BOOL, normalizing it to 1, or retaining a
32-bit host-pointer truncation would change the observed contract. Repairing
that source declaration is separate from this naming block.

| Native identity | Name | EU source wrapper | Contract |
|---|---|---|---|
| ov002:0x02061930 | `GetCachedOwnerNickname` | `src/overlays/ov002/calls/GetCachedOwnerNickname.c` | No input; returns the address of the cached owner nickname UTF-16 buffer in MAIN. InitProfilePanel copies OS owner data and performs banned-word processing once under its cached flag. Borrowed storage, not a function pointer or owned allocation. |
| ov002:0x0206193c | `GetCachedOwnerMessage` | `src/overlays/ov002/calls/GetCachedOwnerMessage.c` | No input; returns the cached owner message UTF-16 buffer in MAIN. Same cache/processing lifecycle as nickname. Native backing storage is 29 u16 units; the initializer's temporary message has 27. These observations do not establish 29 usable text characters. |
| ov002:0x02061dc8 | `DrawOv002MainPanelCenteredText` | `src/overlays/ov002/calls/DrawOv002MainPanelCenteredText.c` | Selector zero chooses MAIN text layer +0x48 and sets dirty mask 0x40 at panel +0x10; any other value chooses +0x7c and sets 0x80. Forwards the remaining seven drawing arguments to DrawCenteredTextLine. No new text ownership. |
| ov002:0x02062000 | `GetOv002PanelKeyRepeatState` | `src/overlays/ov002/calls/GetOv002PanelKeyRepeatState.c` | Returns a borrowed pointer to the repeat/input record at ov002 panel +0x12. The initializer sets up its 26-byte record and the updater merges button masks there. It is not a copied key mask or an independently allocated record. |
| ov002:0x02062014 | `SetOv002PanelModeDirtyFromLowBit` | `src/overlays/ov002/calls/SetOv002PanelModeDirtyFromLowBit.c` | Replaces panel +0x10 mask 0x2 with (value & 1) << 1. It uses the low bit, not nonzero-to-TRUE normalization: value 2 clears the mask and value 3 sets it. |
| ov002:0x0206203c | `ResetOv002MainPanelText` | `src/overlays/ov002/calls/ResetOv002MainPanelText.c` | Selector -1 resets both MAIN text layers, 0 resets +0x48 and 1 resets +0x7c via virtual slot 1 with mode 0. Sets corresponding pending-upload masks 0x40/0x80. Other selectors do nothing. |
| ov002:0x020620fc | `ResetOv002SubPanelText` | `src/overlays/ov002/calls/ResetOv002SubPanelText.c` | Same selector protocol for SUB text layers +0xb0/+0xe4, setting pending-upload masks 0x1/0x2 at panel +0x11. Other selectors do nothing. |
| ov002:0x020621c4 | `GetOv002PanelMessage` | `src/overlays/ov002/calls/GetOv002PanelMessage.c` | Passes the integer index to GetPackedFileEntry using the packed-resource view at ov002 panel +0x118. Returns a borrowed entry used as message text by UI consumers; the wrapper does not copy it or add its own bounds guarantee. |
| ov002:0x020621e4 | `ReleaseOv002SubPanelTextLayers` | `src/overlays/ov002/calls/ReleaseOv002SubPanelTextLayers.c` | Destroys initialized SUB text-layer list resources at +0xb0/+0xe4 according to panel +0x10 masks 0x10/0x20, then clears both initialized bits. Does not free the outer panel work. |
| ov002:0x02062254 | `InitOv002MainPanelGraphics` | `src/overlays/ov002/calls/InitOv002MainPanelGraphics.c` | No input. Configures MAIN BG/OBJ VRAM banks, display/BG controls and priorities, then initializes MAIN BG2/BG3 text layers using the font view at panel +0x30. |
| ov002:0x02062368 | `InitOv002SubPanelGraphics` | `src/overlays/ov002/calls/InitOv002SubPanelGraphics.c` | No input. Configures SUB BG/OBJ VRAM banks, display/BG controls and priorities, then calls the two SUB text-layer constructors using the font view at panel +0x30. |
| ov002:0x02062470 | `InitOv002MainBg3TextLayer` | `src/overlays/ov002/calls/InitOv002MainBg3TextLayer.c` | Borrowed font input. Releases existing initialized layer-0 resources, initializes MAIN BG3 text with the eight-u16 frame [1,0,31,15,1,15,0,3], then marks that layer initialized. The font is not transferred or freed here. |
| ov002:0x02062504 | `InitOv002MainBg2TextLayer` | `src/overlays/ov002/calls/InitOv002MainBg2TextLayer.c` | Borrowed font input. Releases existing initialized layer-1 resources, initializes MAIN BG2 text with frame [0,0,32,24,1,15,0,3], then marks its independent initialized bit. |
| ov002:0x020629a8 | `ResetOv002PanelGraphics` | `src/overlays/ov002/calls/ResetOv002PanelGraphics.c` | No input/result. Calls ResetMainPanelGraphics and then ResetSubPanelGraphics, in that order. |
| ov002:0x02062d94 | `ReleaseOv002ContextResourcesWrapper` | `src/overlays/ov002/calls/ReleaseOv002ContextResourcesWrapper.c` | No logical input. Delegates ReleaseContextResources, which releases children/resources and frees the ov002 menu context at data_ov002_0206c464. This differs from the task work at data_ov002_0206c460. An inherited pointer return does not grant ownership of a result. |
| ov002:0x02062dfc | `UpdateOv002ChildPanel` | `src/overlays/ov002/calls/UpdateOv002ChildPanel.c` | No input/result. Calls the currently bound ov014 UpdatePanelState_0206cf38; only return 1 triggers SwitchPanelMode(0) in the ov002 owner. It does not switch for other nonzero results. |
| ov002:0x02062ecc | `SwitchOv002PanelToMode0` | `src/overlays/ov002/calls/SwitchOv002PanelToMode0.c` | No input. Calls SwitchPanelMode(0): the callee clears the mode-dirty bit, exits the previous nonnegative mode, stores 0 and enters it. Logical effect is void despite the wrapper's inherited pointer-return view. |
| ov002:0x02064394 | `AnimateOv002MenuBackgroundWrapper` | `src/overlays/ov002/calls/AnimateOv002MenuBackgroundWrapper.c` | No logical input. Calls AnimateMenuBgFrames. A nonzero delay is decremented; at zero, eight-entry mapping tables choose frames for two groups of SUB BG1 rows, then delay becomes 2. No returned allocation. |
| ov002:0x020678cc | `MarkGlobalMenuRecordFlagBits` | `src/overlays/ov002/calls/MarkGlobalMenuRecordFlagBits.c` | Inputs: record ID and optional output word. Calls MarkRecordFlagBits(save +0x2788, ID), optionally stores its boolean result. The callee sets primary and secondary category bits unless the record is already flagged. |
| ov002:0x020678fc | `ApplySingleGlobalMenuRecord` | `src/overlays/ov002/calls/ApplySingleGlobalMenuRecord.c` | Inputs: one record ID and optional output word. Calls ApplyRecordsToPackedFields(save +0x276c, &ID, 1), optionally storing its boolean result. The callee handles category/slot conflicts; result is not proof that the requested record was applied. |
| ov002:0x0206793c | `ApplyGlobalMenuCategoryRecord` | `src/overlays/ov002/calls/ApplyGlobalMenuCategoryRecord.c` | Inputs: category, offset and optional output word. Calls ApplyCategoryRecord on save +0x276c and optionally stores its boolean result. The callee may map a category base or expand a record-list category; no equipment/item meaning is added here. |
| ov002:0x02067974 | `ClearGlobalMenuRecordField` | `src/overlays/ov002/calls/ClearGlobalMenuRecordField.c` | Inputs: field selector, matching index and optional output word. Calls ClearPackedField(save +0x276c, selector, match). ROM proves R0 is never written by that callee: the optional output receives the same native target pointer, not a success boolean. |
| ov002:0x020679ac | `ClearGlobalMenuSecondaryRecordFlag` | `src/overlays/ov002/calls/ClearGlobalMenuSecondaryRecordFlag.c` | Inputs: category and offset. Calls SetRecordFlagFromTable(save +0x2788, category, offset, FALSE, FALSE). Those last flags select clearing the secondary flag set; primary bits remain unchanged. |
| ov002:0x02069b8c | `GetMenuCategoryRecordFlagState` | `src/overlays/ov002/calls/GetMenuCategoryRecordFlagState.c` | Inputs: flag-set pointer, category, offset and primary-check selector. Calls LookupTableOffset first, even for category 0x12. That category then returns 0; all others return GetRecordFlagState, which can produce -1, 0 or 1. Preserve signed failure/sentinel behavior. |
| ov002:0x0206a9f8 | `IsMenuRecordAllowedByRandomFilter` | `src/overlays/ov002/calls/IsMenuRecordAllowedByRandomFilter.c` | Input: record ID. Returns 0 for membership in its 19-ID exclusion table, otherwise 1. Random record pickers use it as one filter. It is not a complete validity, availability or ownership test. |

## Player-card pages and held list scrolling

The player-card interpretation has a direct consumer. `DrawPlayerCardDetails`
uses the compressed cursor index in `DispatchContextCommand(0, index, 0, &card)`,
then renders name, message, date, rank, level and avatar fields from the returned
card. Every tenth displayed entry follows a caption path instead of reading a
card. Thus the page-mode routines select display behavior; their old comments
about advancing a day do not match the body.

Counts, cursor and row-height inputs in this list are signed bytes. Preserve
negative sentinels and signed division when compressing the cursor. The held
scroll callbacks perform one step per invocation with a two-tick delay; they do
not block until a whole scroll completes. The two selection words at +0x10 and
+0x14 are named A/B by storage identity, without inventing a higher-level enum.

`GXS_LoadBG0Scr` receives `(source, byteOffset, byteCount)`. Its implementation
copies into `G2S_GetBG0ScrPtr()+byteOffset`, using DMA or CPU copy. The old local
argument name `dest` in some callers is misleading. Screen payloads begin after
their 12-byte headers; record-derived offsets, sizes and digit-tile locations
must retain those byte units. Similarly, a DISPCNT layer-mask replacement is a
full replacement of mask 0x1f00, preserving bits outside it.

| Native identity | Name | EU source wrapper | Contract |
|---|---|---|---|
| ov013:0x0206c760 | `ReleaseOv013PanelResources` | `src/overlays/ov013/calls/ReleaseOv013PanelResources.c` | No input/result. Releases record slot 9, inactive slots, conditional sound, cursor state, animator containers and two object groups, then frees the ov013 context. The global pointer is not cleared by this body. |
| ov013:0x0206c9d4 | `DispatchOv013PendingPanelActions` | `src/overlays/ov013/calls/DispatchOv013PendingPanelActions.c` | No input/result. Dispatches page animation, palette pulse and queued SUB BG0 clear from context flags +0x98/+0x99. If +0x98 mask 0x2 is set, draws cursor+1 and item count, then clears that mask. Other helpers consume their own pending flags. |
| ov013:0x0206ca70 | `DispatchOv013ScrollEnterCallback` | `src/overlays/ov013/calls/DispatchOv013ScrollEnterCallback.c` | No input/result. Uses the signed byte at context +0xd258 as an index into 12-byte scroll-state callback entries and calls the first pointer. No local bounds or null check. |
| ov013:0x0206caa4 | `ConfigureOv013PlayerCardPageMode` | `src/overlays/ov013/calls/ConfigureOv013PlayerCardPageMode.c` | No logical input. Uses signed list cursor, or shared-setting bytes +0x10/+0x11 when the panel is not busy, to choose ordinary versus every-tenth-entry page/display behavior. Initializes graphics and selects masks/phases according to pending flags. Does not increment a day or cursor counter. |
| ov013:0x0206cfd8 | `SetOv013MainLayerMask1e` | `src/overlays/ov013/calls/SetOv013MainLayerMask1e.c` | No logical inputs. Replaces MAIN DISPCNT mask 0x1f00 with 0x1e00, preserves other bits and returns the resulting register word. This enables BG1/BG2/BG3/OBJ and disables BG0; it is not only a single-bit clear. |
| ov013:0x0206cff0 | `ResetOv013PlayerCardPageDisplay` | `src/overlays/ov013/calls/ResetOv013PlayerCardPageDisplay.c` | No input/result. Writes MAIN layer mask 0x0d00, sets context +0x99 mask 0x40, updates group visibility with mode 0, clears pending flags, stores -1 at +0x2e8 and selects panel phase 0. |
| ov013:0x0206fbbc | `PositionOv013CursorWidget` | `src/overlays/ov013/calls/PositionOv013CursorWidget.c` | No input/result. Focuses widget 20+row-in-view, resolves its position, then places cursor widget 0 at x=8 in fx32 and y=context +0xa8 plus list row-pixels*4096. These are positions, not tint values. |
| ov013:0x02070a18 | `ComputeOv013ScrollLimits` | `src/overlays/ov013/calls/ComputeOv013ScrollLimits.c` | No input/result. Computes signed rowHeight*(itemCount-visibleCount); writes the negative to context +0x2e0 and the positive maximum scroll-pixels value to +0x2f8. Inputs retain their signed-byte interpretation. |
| ov013:0x02070a50 | `UploadOv013SubBg0ScreenEntry1` | `src/overlays/ov013/calls/UploadOv013SubBg0ScreenEntry1.c` | No input/result. Looks up screen entry 1 and its active record in container +0x350. Uploads bytes after the 12-byte screen header to SUB BG0 with byte offset=(signed record +4)<<6 and size=screen header +8. SDK input is the source, not a destination pointer. |
| ov013:0x02070aa0 | `QueueOv013SubBg0ClearAndHideWidgets` | `src/overlays/ov013/calls/QueueOv013SubBg0ClearAndHideWidgets.c` | No input/result. Sets context +0x98 mask 0x4 and hides widgets 9 and 10. DispatchOv013PendingPanelActions consumes that queued flag through ClearOv013SubBg0PanelArea. |
| ov013:0x02070b1c | `ClearOv013SubBg0PanelArea` | `src/overlays/ov013/calls/ClearOv013SubBg0PanelArea.c` | No input/result. Clears width*height*2 bytes of SUB BG0 screen memory at base+((signed active-record +4)<<6), using active record 1 from container +0x350; then clears context +0x98 mask 0x4. |
| ov013:0x02070b78 | `DrawOv013ListPositionCounter` | `src/overlays/ov013/calls/DrawOv013ListPositionCounter.c` | Inputs: current position and total. Uploads base screen entry 3, then decimal digits from entry 2 into two fixed column pairs on SUB BG0. The dispatcher supplies cursor+1 and itemCount. Loops render zero once; no negative-value formatting policy is added. |
| ov013:0x02070cb4 | `GetOv013PlayerCardIndexFromCursor` | `src/overlays/ov013/calls/GetOv013PlayerCardIndexFromCursor.c` | No input. Returns signed cursor - (cursor+1)/10. DrawPlayerCardDetails uses it as the card index for non-tenth entries; every tenth entry follows the separate caption path. Preserve signed division and negative sentinels. |
| ov013:0x02070e40 | `ApplyOv013SubitemValuesToWidgets` | `src/overlays/ov013/calls/ApplyOv013SubitemValuesToWidgets.c` | Input: alternate-selection flag. Applies selected subitem values/sequences to widgets 20..25 and 6, reloading the global context between calls. No transfer of widget or container ownership. |
| ov013:0x02071444 | `RefreshOv013PlayerCardPage` | `src/overlays/ov013/calls/RefreshOv013PlayerCardPage.c` | No logical inputs/result. Calls page-mode configuration and then DrawPlayerCardDetails. Legacy numer/denom parameters and int return do not reflect the real no-input, void callees. |
| ov013:0x02071a90 | `SetOv002PanelStateFlag4FromOv013` | `src/overlays/ov013/calls/SetOv002PanelStateFlag4FromOv013.c` | No input. Delegates the ov002 SetPanelStateFlag4 setter, ORing mask 0x4 into that other owner's byte +0x11. Native result is the resulting byte value widened to a word, not the pointer suggested by the inherited wrapper declaration. |
| ov013:0x0207390c | `BeginOv013PlayerCardPageTransition` | `src/overlays/ov013/calls/BeginOv013PlayerCardPageTransition.c` | No input/result. Clears step +0x2bc, sets MAIN brightness -16, posts panel event (1,0x6000), chooses page mode and draws card details. Does not advance a day or cursor counter. |
| ov013:0x020739bc | `UpdateOv013HeldScrollTowardStart` | `src/overlays/ov013/calls/UpdateOv013HeldScrollTowardStart.c` | No input/result. One held-scroll update toward the start: at zero delay adds row height to scroll offset, clamps to 0 and returns to state 1 at the boundary; otherwise updates widgets/caption/markers, plays sound (2,0) and sets delay 2. Touch release returns to state 1. |
| ov013:0x02073ab4 | `UpdateOv013HeldScrollTowardEnd` | `src/overlays/ov013/calls/UpdateOv013HeldScrollTowardEnd.c` | No input/result. Counterpart toward the end: subtracts row height and clamps at the negative limit +0x2e0, with the same visual update, delay and touch-release policy. Direction assumes the positive row height established by the list UI. |
| ov013:0x02074420 | `SetOv013WidgetSelectionAWithSound` | `src/overlays/ov013/calls/SetOv013WidgetSelectionAWithSound.c` | Input: borrowed widget/context pointer. Copies its word +0x0c into ov013 selection word +0x10 and plays sound (2,0) only when the value changes. A identifies this storage slot, not an invented selection enum. |
| ov013:0x0207445c | `SetOv013WidgetSelectionBWithSound` | `src/overlays/ov013/calls/SetOv013WidgetSelectionBWithSound.c` | Input: borrowed widget/context pointer. Copies its word +0x0c into the second selection word +0x14 and plays sound (2,0) only on change. The higher-level meaning of this second slot remains unassigned. |
| ov013:0x02074598 | `EnterOv013PanelMenuState9` | `src/overlays/ov013/calls/EnterOv013PanelMenuState9.c` | No input/result. Calls ChangePanelMenuState(9). The numeric state is retained without inventing a gameplay meaning. |
| ov013:0x020745a8 | `EnterOv013PanelMenuState10` | `src/overlays/ov013/calls/EnterOv013PanelMenuState10.c` | No input/result. Calls ChangePanelMenuState(10), where 10 is decimal state 10. No role is inferred from that number alone. |
| ov013:0x020746f4 | `SetOv013ResultMode2AndPlaySound` | `src/overlays/ov013/calls/SetOv013ResultMode2AndPlaySound.c` | No input/result. Stores 2 in ov013 result-mode byte +3 and plays sound (2,1). This does not establish a complete result-mode enum. |
| ov014:0x0206d234 | `RefreshOv014SelectedEntryInfo` | `src/overlays/ov014/calls/RefreshOv014SelectedEntryInfo.c` | No input/result. Calls ov014 DrawSelectedEntryInfo(0), then clears byte +0xcf8c of its own context. The cleared byte's wider meaning remains unassigned. |

## Evidence and limits for a port

The behavior in the tables is read from the 58 wrappers and their actual EU
included bodies. The following initializer/consumer paths provide the main
cross-checks beyond those bodies:

- `src/overlays/ov000/calls/HandleSessionModeTransition.c` proves the two-word
  title-session consumer and distinguishes status from its companion value.
- `src/calls/SetBrightnessAndSyncMain.c`,
  `src/calls/SetSecondaryBrightness.c` and the title wrapper's ARM instructions
  prove the brightness input reaches both setters, despite one incomplete
  declaration. Both setters may queue a write outside VBlank; the optional
  subsequent wait does not itself prove that a queued write has been flushed.
- `src/overlays/ov002/calls/InitProfilePanel.c`,
  `src/overlays/ov002/calls/UpdatePanelState.c` and
  `src/overlays/ov002/Ov002PanelState.h` establish the owner, repeat record,
  text-layer initialized/pending masks and cached OS owner strings.
  `src/data/bss/Bss_main_02060878.c` supplies the native backing-array sizes.
- `src/overlays/ov002/calls/ReleaseContextResources.c` and
  `src/overlays/ov002/calls/AnimateMenuBgFrames.c` establish the distinct menu
  context, child cleanup and screen-row animation.
- `src/overlays/ov002/calls/MarkRecordFlagBits.c`,
  `src/overlays/ov002/calls/ApplyRecordsToPackedFields.c`,
  `src/overlays/ov002/calls/ApplyCategoryRecord.c`,
  `src/overlays/ov002/calls/ClearPackedField.c`,
  `src/overlays/ov002/calls/SetRecordFlagFromTable.c`,
  `src/overlays/ov002/calls/SetRecordFlagBit.c` and
  `src/overlays/ov002/calls/GetRecordFlagState.c` establish which save region is
  mutated, the secondary/primary distinction and signed -1/0/1 query results.
- `src/overlays/ov013/calls/DrawPlayerCardDetails.c` and
  `src/overlays/ov013/Ov013PanelState.h` establish player-card consumption,
  signed list values and page/cursor relationships. The pending-action producer
  and dispatcher establish that mask 0x4 queues the SUB BG0 clear.
- `libs/nitro/gx/calls/GXS_LoadBG0Scr.c` establishes source-to-VRAM copying;
  `src/overlays/ov014/calls/UpdatePanelState_0206cf38.c` is the current child
  updater bound by the ov002 wrapper. The numeric child mode is not inferred
  solely from that binding.

None of the wrappers adds general range checks, proves a full resource lifetime
or transfers a borrowed font, message, profile or widget pointer to the caller.
The random exclusion predicate is only one filter; the record apply helpers can
return TRUE without applying the requested entry. Pending flags, initialized
flags and result enums are separate concepts even when their numeric masks
coincide in different owners.

Several historical wrappers expose pointer returns or unused arguments for
callees whose demonstrated operation is void. Preserve the compiled native
boundary until a separately validated type repair, while avoiding fabricated
logical inputs or owned-pointer contracts in a port. The retained numeric state
names, opaque title-session value and second selection word mark the extent of
the evidence rather than a complete recovered gameplay enum.

## Reproducible byte-exact validation

Run from `eu/`. These 58 entrypoints retain their native ARM mode:

```sh
python tools/verify_idx.py src/overlays/ov000/calls/SetTitleBrightnessAndMaybeWaitVBlank.c SetTitleBrightnessAndMaybeWaitVBlank
python tools/verify_idx.py src/overlays/ov000/calls/UpdateTitleTimedPanelPhase.c UpdateTitleTimedPanelPhase
python tools/verify_idx.py src/overlays/ov000/calls/ApplyTitleMenuFlagsAndStoreLanguage.c ApplyTitleMenuFlagsAndStoreLanguage
python tools/verify_idx.py src/overlays/ov000/calls/ReleaseTitlePanelResources.c ReleaseTitlePanelResources
python tools/verify_idx.py src/overlays/ov000/calls/RecordTitleStartTickWrapper.c RecordTitleStartTickWrapper
python tools/verify_idx.py src/overlays/ov000/calls/SetupTitleDisplayBanksAndLayersWrapper.c SetupTitleDisplayBanksAndLayersWrapper
python tools/verify_idx.py src/overlays/ov000/calls/GetTitleSessionStatus.c GetTitleSessionStatus
python tools/verify_idx.py libs/nitro/card/calls/GetTitleSessionValue.c GetTitleSessionValue
python tools/verify_idx.py src/overlays/ov002/calls/GetCachedOwnerNickname.c GetCachedOwnerNickname
python tools/verify_idx.py src/overlays/ov002/calls/GetCachedOwnerMessage.c GetCachedOwnerMessage
python tools/verify_idx.py src/overlays/ov002/calls/DrawOv002MainPanelCenteredText.c DrawOv002MainPanelCenteredText
python tools/verify_idx.py src/overlays/ov002/calls/GetOv002PanelKeyRepeatState.c GetOv002PanelKeyRepeatState
python tools/verify_idx.py src/overlays/ov002/calls/SetOv002PanelModeDirtyFromLowBit.c SetOv002PanelModeDirtyFromLowBit
python tools/verify_idx.py src/overlays/ov002/calls/ResetOv002MainPanelText.c ResetOv002MainPanelText
python tools/verify_idx.py src/overlays/ov002/calls/ResetOv002SubPanelText.c ResetOv002SubPanelText
python tools/verify_idx.py src/overlays/ov002/calls/GetOv002PanelMessage.c GetOv002PanelMessage
python tools/verify_idx.py src/overlays/ov002/calls/ReleaseOv002SubPanelTextLayers.c ReleaseOv002SubPanelTextLayers
python tools/verify_idx.py src/overlays/ov002/calls/InitOv002MainPanelGraphics.c InitOv002MainPanelGraphics
python tools/verify_idx.py src/overlays/ov002/calls/InitOv002SubPanelGraphics.c InitOv002SubPanelGraphics
python tools/verify_idx.py src/overlays/ov002/calls/InitOv002MainBg3TextLayer.c InitOv002MainBg3TextLayer
python tools/verify_idx.py src/overlays/ov002/calls/InitOv002MainBg2TextLayer.c InitOv002MainBg2TextLayer
python tools/verify_idx.py src/overlays/ov002/calls/ResetOv002PanelGraphics.c ResetOv002PanelGraphics
python tools/verify_idx.py src/overlays/ov002/calls/ReleaseOv002ContextResourcesWrapper.c ReleaseOv002ContextResourcesWrapper
python tools/verify_idx.py src/overlays/ov002/calls/UpdateOv002ChildPanel.c UpdateOv002ChildPanel
python tools/verify_idx.py src/overlays/ov002/calls/SwitchOv002PanelToMode0.c SwitchOv002PanelToMode0
python tools/verify_idx.py src/overlays/ov002/calls/AnimateOv002MenuBackgroundWrapper.c AnimateOv002MenuBackgroundWrapper
python tools/verify_idx.py src/overlays/ov002/calls/MarkGlobalMenuRecordFlagBits.c MarkGlobalMenuRecordFlagBits
python tools/verify_idx.py src/overlays/ov002/calls/ApplySingleGlobalMenuRecord.c ApplySingleGlobalMenuRecord
python tools/verify_idx.py src/overlays/ov002/calls/ApplyGlobalMenuCategoryRecord.c ApplyGlobalMenuCategoryRecord
python tools/verify_idx.py src/overlays/ov002/calls/ClearGlobalMenuRecordField.c ClearGlobalMenuRecordField
python tools/verify_idx.py src/overlays/ov002/calls/ClearGlobalMenuSecondaryRecordFlag.c ClearGlobalMenuSecondaryRecordFlag
python tools/verify_idx.py src/overlays/ov002/calls/GetMenuCategoryRecordFlagState.c GetMenuCategoryRecordFlagState
python tools/verify_idx.py src/overlays/ov002/calls/IsMenuRecordAllowedByRandomFilter.c IsMenuRecordAllowedByRandomFilter
python tools/verify_idx.py src/overlays/ov013/calls/ReleaseOv013PanelResources.c ReleaseOv013PanelResources
python tools/verify_idx.py src/overlays/ov013/calls/DispatchOv013PendingPanelActions.c DispatchOv013PendingPanelActions
python tools/verify_idx.py src/overlays/ov013/calls/DispatchOv013ScrollEnterCallback.c DispatchOv013ScrollEnterCallback
python tools/verify_idx.py src/overlays/ov013/calls/ConfigureOv013PlayerCardPageMode.c ConfigureOv013PlayerCardPageMode
python tools/verify_idx.py src/overlays/ov013/calls/SetOv013MainLayerMask1e.c SetOv013MainLayerMask1e
python tools/verify_idx.py src/overlays/ov013/calls/ResetOv013PlayerCardPageDisplay.c ResetOv013PlayerCardPageDisplay
python tools/verify_idx.py src/overlays/ov013/calls/PositionOv013CursorWidget.c PositionOv013CursorWidget
python tools/verify_idx.py src/overlays/ov013/calls/ComputeOv013ScrollLimits.c ComputeOv013ScrollLimits
python tools/verify_idx.py src/overlays/ov013/calls/UploadOv013SubBg0ScreenEntry1.c UploadOv013SubBg0ScreenEntry1
python tools/verify_idx.py src/overlays/ov013/calls/QueueOv013SubBg0ClearAndHideWidgets.c QueueOv013SubBg0ClearAndHideWidgets
python tools/verify_idx.py src/overlays/ov013/calls/ClearOv013SubBg0PanelArea.c ClearOv013SubBg0PanelArea
python tools/verify_idx.py src/overlays/ov013/calls/DrawOv013ListPositionCounter.c DrawOv013ListPositionCounter
python tools/verify_idx.py src/overlays/ov013/calls/GetOv013PlayerCardIndexFromCursor.c GetOv013PlayerCardIndexFromCursor
python tools/verify_idx.py src/overlays/ov013/calls/ApplyOv013SubitemValuesToWidgets.c ApplyOv013SubitemValuesToWidgets
python tools/verify_idx.py src/overlays/ov013/calls/RefreshOv013PlayerCardPage.c RefreshOv013PlayerCardPage
python tools/verify_idx.py src/overlays/ov013/calls/SetOv002PanelStateFlag4FromOv013.c SetOv002PanelStateFlag4FromOv013
python tools/verify_idx.py src/overlays/ov013/calls/BeginOv013PlayerCardPageTransition.c BeginOv013PlayerCardPageTransition
python tools/verify_idx.py src/overlays/ov013/calls/UpdateOv013HeldScrollTowardStart.c UpdateOv013HeldScrollTowardStart
python tools/verify_idx.py src/overlays/ov013/calls/UpdateOv013HeldScrollTowardEnd.c UpdateOv013HeldScrollTowardEnd
python tools/verify_idx.py src/overlays/ov013/calls/SetOv013WidgetSelectionAWithSound.c SetOv013WidgetSelectionAWithSound
python tools/verify_idx.py src/overlays/ov013/calls/SetOv013WidgetSelectionBWithSound.c SetOv013WidgetSelectionBWithSound
python tools/verify_idx.py src/overlays/ov013/calls/EnterOv013PanelMenuState9.c EnterOv013PanelMenuState9
python tools/verify_idx.py src/overlays/ov013/calls/EnterOv013PanelMenuState10.c EnterOv013PanelMenuState10
python tools/verify_idx.py src/overlays/ov013/calls/SetOv013ResultMode2AndPlaySound.c SetOv013ResultMode2AndPlaySound
python tools/verify_idx.py src/overlays/ov014/calls/RefreshOv014SelectedEntryInfo.c RefreshOv014SelectedEntryInfo
bash tools/gate.sh
```

All 58 official function checks pass. The fresh gate passes all 108 linked
modules. Affected function bytes, resolved relocation targets/types and addends,
and all module hashes match the preserved pre-rename baseline. Corrected comments
and a position variable remove unsupported CARD/day/tint meanings without
changing the native code or reconstruction credit.
