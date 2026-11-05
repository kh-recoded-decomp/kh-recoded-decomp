# Menu phases, suboverlay descriptors and text contracts

This document records 20 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

Menu phase is the native word at work +0xc9c4, used as an unchecked phase-callback-table index. It differs from the primary/secondary suboverlay indices and the top-level session state. The menu-work getter returns a borrowed owner pointer; its primary widget root occupies the prefix and the secondary root begins at +0x647c.

## Brightness and input

The two brightness tweens are configured from current MAIN/SUB values to the target shifted by 12, then started using the caller's duration. They allocate no stream buffers. Existing tween-clock units are retained; the duration is not asserted to be frames. Fade pollers wait only for MAIN tween finished bit 2 at tween +0x18 (menu +0xc9e8). They continue updating both suboverlays while waiting.

Fade-in completion enables menu input or buttons according to the specific path and enters phase 3. The submenu fade-in path changes buttons but not the separate inputEnabled word. `SetMenuInputEnabled` forwards its incoming value in live R0 to `SetMenuButtonsEnabled` before storing that value at +0xca10, despite the incomplete no-argument call in its current C view. Fade-out polling enters phase 8; cleanup occurs later rather than inside the poller.

## Descriptor tables and ownership

Primary work is stored at +0xc998 and secondary work at +0xc99c. Two separate BSS indices select eight-byte `{overlayId, descriptorPointer}` records; they are table indices, not overlay IDs. The primary table at 020be94c has 19 records, and the secondary table at 020be8ec has 12. Primary indices 1, 2 and 3 select overlay075 Matrix, overlay076 Slot and overlay077 Items respectively; index 0 selects overlay074 without assigning a human-facing role here.

| Descriptor offset | Primary | Secondary |
| --- | --- | --- |
| 0x00 | init(work), result consumed as ready | init(work), result consumed as ready |
| 0x04 | destroy(work) | destroy(work) |
| 0x08 | update(work) | update(work) |
| 0x0c | Secondary table index | Work byte size |
| 0x10 | Work byte size | Later interface fields, not specified here |

Allocation uses the corresponding byte-size field and clears the work before initialization. Initializers can be polled until their consumed result is nonzero. Updates run after readiness. Actual menu lifecycle consumers discard update/destroy return words; an empty callback may leave work in R0, which is not a computed success value. Destruction callbacks run before the caller frees work and unloads the overlay. Resetting the saved indices to -1 performs no destruction or unloading.

The pointer views four bytes into these pair tables overlap their storage. Older string labels for the first words are really integer overlay IDs 73/74. Do not emit duplicate C arrays for overlapping table views. Native descriptor layouts differ after the first three callbacks; a single shared struct would misread primary +0x0c as a size.

## Text selection and drawing

The font selector installs font10 at menu +0xca90, tests measured width strictly less than the limit, and installs font10s at +0xcaa8 when it does not fit. Equality selects the smaller font. The returned BOOL describes fit in the first font, not whether the fallback now fits. It changes the canvas font rather than text color.

Shadow drawing uses the logically supplied layer, coordinates, color, text flags, text and maxWidth despite misleading z/color/style/flags parameter labels. It draws the offset shadow and then foreground, restoring the layer's default font from its first word rather than the font that happened to be on entry. Centered multiline drawing measures each UTF16 line, centers it around X, advances by glyph height and follows the returned next-line pointer. It neither allocates text nor chooses a wrapping width.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov039:020bab00` | ARM | `RuntimeState_SetMode` | `SetMenuPhase` | [eu/src/overlays/ov039/calls/SetMenuPhase.c](../src/overlays/ov039/calls/SetMenuPhase.c) |
| `ov039:020bab18` | ARM | `GetStateC9C4` | `GetMenuPhase` | [eu/src/overlays/ov039/calls/GetMenuPhase.c](../src/overlays/ov039/calls/GetMenuPhase.c) |
| `ov039:020bacdc` | ARM | `InitStreamBufferPair` | `StartMenuBrightnessTweens` | [eu/src/overlays/ov039/calls/StartMenuBrightnessTweens.c](../src/overlays/ov039/calls/StartMenuBrightnessTweens.c) |
| `ov039:020bb2d0` | ARM | `func_ov039_020bb2d0` | `WaitMenuFadeInThenEnableInput` | [eu/src/overlays/ov039/calls/WaitMenuFadeInThenEnableInput.c](../src/overlays/ov039/calls/WaitMenuFadeInThenEnableInput.c) |
| `ov039:020bb4c8` | ARM | `func_ov039_020bb4c8` | `WaitSubMenuFadeInThenEnableButtons` | [eu/src/overlays/ov039/calls/WaitSubMenuFadeInThenEnableButtons.c](../src/overlays/ov039/calls/WaitSubMenuFadeInThenEnableButtons.c) |
| `ov039:020bb518` | ARM | `func_ov039_020bb518` | `WaitMenuFadeOutThenEnterShutdown` | [eu/src/overlays/ov039/calls/WaitMenuFadeOutThenEnterShutdown.c](../src/overlays/ov039/calls/WaitMenuFadeOutThenEnterShutdown.c) |
| `ov039:020bb708` | ARM | `func_ov039_020bb708` | `DispatchMenuPhaseUpdate` | [eu/src/overlays/ov039/calls/DispatchMenuPhaseUpdate.c](../src/overlays/ov039/calls/DispatchMenuPhaseUpdate.c) |
| `ov039:020bc038` | ARM | `func_ov039_020bc038` | `SetMenuInputEnabled` | [eu/src/overlays/ov039/calls/SetMenuInputEnabled.c](../src/overlays/ov039/calls/SetMenuInputEnabled.c) |
| `ov039:020bc1dc` | ARM | `func_ov039_020bc1dc` | `GetMenuWork` | [eu/src/overlays/ov039/calls/GetMenuWork.c](../src/overlays/ov039/calls/GetMenuWork.c) |
| `ov039:020bcd24` | ARM | `SetTextColorIfFits` | `SelectMenuFontForWidth` | [eu/src/overlays/ov039/calls/SelectMenuFontForWidth.c](../src/overlays/ov039/calls/SelectMenuFontForWidth.c) |
| `ov039:020bcdd8` | ARM | `func_ov039_020bcdd8` | `ResetMenuSubOverlayIndices` | [eu/src/overlays/ov039/calls/ResetMenuSubOverlayIndices.c](../src/overlays/ov039/calls/ResetMenuSubOverlayIndices.c) |
| `ov039:020bcf10` | ARM | `func_ov039_020bcf10` | `InvokePrimaryMenuSubOverlayDestroy` | [eu/src/overlays/ov039/calls/InvokePrimaryMenuSubOverlayDestroy.c](../src/overlays/ov039/calls/InvokePrimaryMenuSubOverlayDestroy.c) |
| `ov039:020bcf40` | ARM | `func_ov039_020bcf40` | `UpdatePrimaryMenuSubOverlay` | [eu/src/overlays/ov039/calls/UpdatePrimaryMenuSubOverlay.c](../src/overlays/ov039/calls/UpdatePrimaryMenuSubOverlay.c) |
| `ov039:020bd074` | ARM | `func_ov039_020bd074` | `UpdateSecondaryMenuSubOverlay` | [eu/src/overlays/ov039/calls/UpdateSecondaryMenuSubOverlay.c](../src/overlays/ov039/calls/UpdateSecondaryMenuSubOverlay.c) |
| `ov039:020bd644` | ARM | `func_ov039_020bd644` | `GetPrimaryMenuSubOverlayIndex` | [eu/src/overlays/ov039/calls/GetPrimaryMenuSubOverlayIndex.c](../src/overlays/ov039/calls/GetPrimaryMenuSubOverlayIndex.c) |
| `ov039:020bd654` | ARM | `func_ov039_020bd654` | `GetPrimaryMenuSecondaryOverlayIndex` | [eu/src/overlays/ov039/calls/GetPrimaryMenuSecondaryOverlayIndex.c](../src/overlays/ov039/calls/GetPrimaryMenuSecondaryOverlayIndex.c) |
| `ov039:020bd674` | ARM | `func_ov039_020bd674` | `GetPrimaryMenuSubOverlayWorkSize` | [eu/src/overlays/ov039/calls/GetPrimaryMenuSubOverlayWorkSize.c](../src/overlays/ov039/calls/GetPrimaryMenuSubOverlayWorkSize.c) |
| `ov039:020bd694` | ARM | `func_ov039_020bd694` | `GetSecondaryMenuSubOverlayWorkSize` | [eu/src/overlays/ov039/calls/GetSecondaryMenuSubOverlayWorkSize.c](../src/overlays/ov039/calls/GetSecondaryMenuSubOverlayWorkSize.c) |
| `ov039:020be548` | THUMB | `func_ov039_020be548` | `DrawMenuTextWithShadow` | [eu/src/overlays/ov039/calls/DrawMenuTextWithShadow.c](../src/overlays/ov039/calls/DrawMenuTextWithShadow.c) |
| `ov039:020be594` | THUMB | `func_ov039_020be594` | `DrawCenteredMenuTextLines` | [eu/src/overlays/ov039/calls/DrawCenteredMenuTextLines.c](../src/overlays/ov039/calls/DrawCenteredMenuTextLines.c) |

## SetMenuPhase

Identity: `ov039:020bab00`, ARM, native extent 24 bytes (including any configured pool). Previous symbol: `RuntimeState_SetMode`.

EU entrypoint: [eu/src/overlays/ov039/calls/SetMenuPhase.c](../src/overlays/ov039/calls/SetMenuPhase.c).

```c
void SetMenuPhase(int value);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Stores the supplied phase to menu+c9c4. Source: [src/ov039/event_state/func_ov039_020baae0.c:1-8](../../src/ov039/event_state/func_ov039_020baae0.c).
- The dispatcher indexes its phase callback table with this field. Source: [src/ov039/reviewed_helpers/func_ov039_020bb6e8.c:1-9](../../src/ov039/reviewed_helpers/func_ov039_020bb6e8.c).

Contract limits:

- Changes menu phase, not the top-level scene ID or suboverlay index.

## GetMenuPhase

Identity: `ov039:020bab18`, ARM, native extent 24 bytes (including any configured pool). Previous symbol: `GetStateC9C4`.

EU entrypoint: [eu/src/overlays/ov039/calls/GetMenuPhase.c](../src/overlays/ov039/calls/GetMenuPhase.c).

```c
int GetMenuPhase(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns menu+c9c4. Source: [src/ov039/event_state/GetStateC9C4.c:1-6](../../src/ov039/event_state/GetStateC9C4.c).
- The phase dispatcher consumes this value as a callback-table index. Source: [src/ov039/reviewed_helpers/func_ov039_020bb6e8.c:1-9](../../src/ov039/reviewed_helpers/func_ov039_020bb6e8.c).

Contract limits:

- No bounds validation.

## StartMenuBrightnessTweens

Identity: `ov039:020bacdc`, ARM, native extent 120 bytes (including any configured pool). Previous symbol: `InitStreamBufferPair`.

EU entrypoint: [eu/src/overlays/ov039/calls/StartMenuBrightnessTweens.c](../src/overlays/ov039/calls/StartMenuBrightnessTweens.c).

```c
void StartMenuBrightnessTweens(int blockCount, u32 flag);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Configures and starts the two brightness tweens from current main/sub values to targetBrightness<<12 using the supplied duration. Source: [src/ov039/reviewed_helpers/InitStreamBufferPair_020bacbc.c:1-16](../../src/ov039/reviewed_helpers/InitStreamBufferPair_020bacbc.c).
- EU aliases the actual callees to ConfigureTween and StartTween helpers. Source: [eu/src/overlays/ov039/calls/StartMenuBrightnessTweens.c:1-5](../src/overlays/ov039/calls/StartMenuBrightnessTweens.c).
- Samples these tweens and commits the brightness values. Source: [eu/src/overlays/ov039/calls/UpdateBrightnessAndTasks.c:1-9](../src/overlays/ov039/calls/UpdateBrightnessAndTasks.c).

Contract limits:

- No stream buffer allocation occurs.
- The duration uses the existing tween clock contract; do not label it frames without verifying units.

## WaitMenuFadeInThenEnableInput

Identity: `ov039:020bb2d0`, ARM, native extent 88 bytes (including any configured pool). Previous symbol: `func_ov039_020bb2d0`.

EU entrypoint: [eu/src/overlays/ov039/calls/WaitMenuFadeInThenEnableInput.c](../src/overlays/ov039/calls/WaitMenuFadeInThenEnableInput.c).

```c
void WaitMenuFadeInThenEnableInput(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Updates primary/secondary overlays; when main brightness tween finished bit is set, clears pending-secondary flag, enables menu input and enters phase3. Source: [eu/src/overlays/ov039/calls/WaitMenuFadeInThenEnableInput.c:1-21](../src/overlays/ov039/calls/WaitMenuFadeInThenEnableInput.c).
- Tween finished is bit2 at tween+0x18. Source: [src/arm9/runtime_data_utilities/SampleTweenValue_0205258c.c:1-55](../../src/arm9/runtime_data_utilities/SampleTweenValue_0205258c.c).
- Main brightness tween starts at+c9d0, so its finished flag resides at+c9e8. Source: [src/ov039/reviewed_helpers/InitStreamBufferPair_020bacbc.c:1-16](../../src/ov039/reviewed_helpers/InitStreamBufferPair_020bacbc.c).

Contract limits:

- Waits only for the main brightness tween flag.

## WaitSubMenuFadeInThenEnableButtons

Identity: `ov039:020bb4c8`, ARM, native extent 80 bytes (including any configured pool). Previous symbol: `func_ov039_020bb4c8`.

EU entrypoint: [eu/src/overlays/ov039/calls/WaitSubMenuFadeInThenEnableButtons.c](../src/overlays/ov039/calls/WaitSubMenuFadeInThenEnableButtons.c).

```c
void WaitSubMenuFadeInThenEnableButtons(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Updates both overlay handlers, then enables menu buttons and enters phase3 once the main brightness tween is finished. Source: [eu/src/overlays/ov039/calls/WaitSubMenuFadeInThenEnableButtons.c:1-20](../src/overlays/ov039/calls/WaitSubMenuFadeInThenEnableButtons.c).

Contract limits:

- Does not assign the separate inputEnabled word.

## WaitMenuFadeOutThenEnterShutdown

Identity: `ov039:020bb518`, ARM, native extent 72 bytes (including any configured pool). Previous symbol: `func_ov039_020bb518`.

EU entrypoint: [eu/src/overlays/ov039/calls/WaitMenuFadeOutThenEnterShutdown.c](../src/overlays/ov039/calls/WaitMenuFadeOutThenEnterShutdown.c).

```c
void WaitMenuFadeOutThenEnterShutdown(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Updates both overlays; enters phase8 when the main brightness tween has finished. Source: [eu/src/overlays/ov039/calls/WaitMenuFadeOutThenEnterShutdown.c:1-18](../src/overlays/ov039/calls/WaitMenuFadeOutThenEnterShutdown.c).
- The shutdown path destroys/free overlay work and chooses exit/reload state. Source: [eu/src/overlays/ov039/calls/ShutdownHandlersAndExit.c:1-84](../src/overlays/ov039/calls/ShutdownHandlersAndExit.c).

Contract limits:

- Does not destroy resources within this polling helper.

## DispatchMenuPhaseUpdate

Identity: `ov039:020bb708`, ARM, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov039_020bb708`.

EU entrypoint: [eu/src/overlays/ov039/calls/DispatchMenuPhaseUpdate.c](../src/overlays/ov039/calls/DispatchMenuPhaseUpdate.c).

```c
void DispatchMenuPhaseUpdate(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Reads menu phase, indexes the phase callback table and calls the nonnull function. Source: [src/ov039/reviewed_helpers/func_ov039_020bb6e8.c:1-9](../../src/ov039/reviewed_helpers/func_ov039_020bb6e8.c).
- The phase setter writes the same+c9c4 word read by GetStateC9C4. Source: [src/ov039/event_state/func_ov039_020baae0.c:1-8](../../src/ov039/event_state/func_ov039_020baae0.c).

Contract limits:

- No bounds check or default handler is supplied.

## SetMenuInputEnabled

Identity: `ov039:020bc038`, ARM, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov039_020bc038`.

EU entrypoint: [eu/src/overlays/ov039/calls/SetMenuInputEnabled.c](../src/overlays/ov039/calls/SetMenuInputEnabled.c).

```c
void SetMenuInputEnabled(u32 value);
```

The incoming value is forwarded to SetMenuButtonsEnabled in R0 despite the incomplete C call view, then stored at menu +0xca10. The rename preserves that native ABI.

Demonstrated behavior and evidence:

- Forwards the incoming value to SetMenuButtonsEnabled through live R0, then stores it at menu+ca10. Source: [eu/src/overlays/ov039/calls/SetMenuInputEnabled.c:1-9](../src/overlays/ov039/calls/SetMenuInputEnabled.c).
- Native menu prefix identifies+ca10 as inputEnabled. Source: [eu/src/overlays/ov039/Ov039MenuState.h:1-53](../src/overlays/ov039/Ov039MenuState.h).

Contract limits:

- Current C declaration omits the argument in its SetMenuButtonsEnabled call; any portable signature repair must preserve the actual value passed.
- Menu button gating and global inputEnabled remain separate fields.

## GetMenuWork

Identity: `ov039:020bc1dc`, ARM, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov039_020bc1dc`.

EU entrypoint: [eu/src/overlays/ov039/calls/GetMenuWork.c](../src/overlays/ov039/calls/GetMenuWork.c).

```c
int GetMenuWork(void);
```

The native int represents a borrowed menu-work pointer; its lifetime is the menu owner's lifetime.

Demonstrated behavior and evidence:

- Returns the exact global menu work pointer. Source: [eu/src/overlays/ov039/calls/GetMenuWork.c:1-5](../src/overlays/ov039/calls/GetMenuWork.c).
- The native menu header binds this global to Ov039MenuState. Source: [eu/src/overlays/ov039/Ov039MenuState.h:1-53](../src/overlays/ov039/Ov039MenuState.h).

Contract limits:

- Borrowed owner; the primary widget root occupies its prefix while the secondary root begins+0x647c.

## SelectMenuFontForWidth

Identity: `ov039:020bcd24`, ARM, native extent 100 bytes (including any configured pool). Previous symbol: `SetTextColorIfFits`.

EU entrypoint: [eu/src/overlays/ov039/calls/SelectMenuFontForWidth.c](../src/overlays/ov039/calls/SelectMenuFontForWidth.c).

```c
BOOL SelectMenuFontForWidth(int *object, int limit, int text);
```

The BOOL reports strict width<limit for the first font. Fallback installation does not establish that the text fits the fallback or that any text is truncated.

Demonstrated behavior and evidence:

- Selects font10 at menu+ca90, tests line width<limit and selects font10s at+caa8 if the text does not fit. Source: [src/ov039/widget_layers/SetTextColorIfFits_020bcd04.c:1-18](../../src/ov039/widget_layers/SetTextColorIfFits_020bcd04.c).
- Native header identifies font10 and font10s storage at these offsets. Source: [eu/src/overlays/ov039/Ov039MenuState.h:1-53](../src/overlays/ov039/Ov039MenuState.h).
- The actual width helper measures text through the canvas font. Source: [eu/src/calls/GetTextLayerLineWidth.c:1-15](../src/calls/GetTextLayerLineWidth.c).

Contract limits:

- Comparison is strict; width==limit selects the smaller font.
- Returns fit status for the first font. It does not change text color.

## ResetMenuSubOverlayIndices

Identity: `ov039:020bcdd8`, ARM, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov039_020bcdd8`.

EU entrypoint: [eu/src/overlays/ov039/calls/ResetMenuSubOverlayIndices.c](../src/overlays/ov039/calls/ResetMenuSubOverlayIndices.c).

```c
void ResetMenuSubOverlayIndices(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Stores -1 to primary and secondary active indices. Source: [eu/src/overlays/ov039/calls/ResetMenuSubOverlayIndices.c:1-6](../src/overlays/ov039/calls/ResetMenuSubOverlayIndices.c).
- Primary load stores index in element0. Source: [src/ov039/overlay_handling/LoadPrimarySubOverlay_020bce34.c:1-19](../../src/ov039/overlay_handling/LoadPrimarySubOverlay_020bce34.c).
- Secondary load stores index in element1. Source: [src/ov039/overlay_handling/LoadSecondarySubOverlay_020bcf50.c:1-19](../../src/ov039/overlay_handling/LoadSecondarySubOverlay_020bcf50.c).

Contract limits:

- Does not unload overlays or destroy work; only resets selection bookkeeping.

## InvokePrimaryMenuSubOverlayDestroy

Identity: `ov039:020bcf10`, ARM, native extent 48 bytes (including any configured pool). Previous symbol: `func_ov039_020bcf10`.

EU entrypoint: [eu/src/overlays/ov039/calls/InvokePrimaryMenuSubOverlayDestroy.c](../src/overlays/ov039/calls/InvokePrimaryMenuSubOverlayDestroy.c).

```c
void InvokePrimaryMenuSubOverlayDestroy(int arg0);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- If primary index!=-1, invokes descriptor callback+4 with caller work. Source: [eu/src/overlays/ov039/calls/InvokePrimaryMenuSubOverlayDestroy.c:1-11](../src/overlays/ov039/calls/InvokePrimaryMenuSubOverlayDestroy.c).
- Calls this callback before freeing primaryWork and unloading its overlay. Source: [eu/src/overlays/ov039/calls/ShutdownHandlersAndExit.c:1-84](../src/overlays/ov039/calls/ShutdownHandlersAndExit.c).

Contract limits:

- Callback is responsible for its own internals; outer work free/unload occurs separately.

## UpdatePrimaryMenuSubOverlay

Identity: `ov039:020bcf40`, ARM, native extent 48 bytes (including any configured pool). Previous symbol: `func_ov039_020bcf40`.

EU entrypoint: [eu/src/overlays/ov039/calls/UpdatePrimaryMenuSubOverlay.c](../src/overlays/ov039/calls/UpdatePrimaryMenuSubOverlay.c).

```c
void UpdatePrimaryMenuSubOverlay(int arg0);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- If primary index!=-1, invokes descriptor callback+8 with caller work. Source: [eu/src/overlays/ov039/calls/UpdatePrimaryMenuSubOverlay.c:1-11](../src/overlays/ov039/calls/UpdatePrimaryMenuSubOverlay.c).
- After init callback reports ready, frame updates use this callback. Source: [eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c:1-84](../src/overlays/ov039/calls/UpdateSubOverlayHandlers.c).

Contract limits:

- No null callback check is added.

## UpdateSecondaryMenuSubOverlay

Identity: `ov039:020bd074`, ARM, native extent 48 bytes (including any configured pool). Previous symbol: `func_ov039_020bd074`.

EU entrypoint: [eu/src/overlays/ov039/calls/UpdateSecondaryMenuSubOverlay.c](../src/overlays/ov039/calls/UpdateSecondaryMenuSubOverlay.c).

```c
void UpdateSecondaryMenuSubOverlay(int arg0);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- If secondary index!=-1, invokes secondary descriptor callback+8 with caller work. Source: [eu/src/overlays/ov039/calls/UpdateSecondaryMenuSubOverlay.c:1-11](../src/overlays/ov039/calls/UpdateSecondaryMenuSubOverlay.c).
- Frame update calls this after the secondary init callback reports ready. Source: [eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c:1-84](../src/overlays/ov039/calls/UpdateSubOverlayHandlers.c).

Contract limits:

- Descriptor layout differs from the primary layout after these first three function pointers.

## GetPrimaryMenuSubOverlayIndex

Identity: `ov039:020bd644`, ARM, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov039_020bd644`.

EU entrypoint: [eu/src/overlays/ov039/calls/GetPrimaryMenuSubOverlayIndex.c](../src/overlays/ov039/calls/GetPrimaryMenuSubOverlayIndex.c).

```c
int GetPrimaryMenuSubOverlayIndex(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns element0 of the active menu suboverlay index pair. Source: [eu/src/overlays/ov039/calls/GetPrimaryMenuSubOverlayIndex.c:1-5](../src/overlays/ov039/calls/GetPrimaryMenuSubOverlayIndex.c).
- The primary loader stores its selected table index here. Source: [src/ov039/overlay_handling/LoadPrimarySubOverlay_020bce34.c:1-19](../../src/ov039/overlay_handling/LoadPrimarySubOverlay_020bce34.c).

Contract limits:

- Index is a table position, not an overlay ID.

## GetPrimaryMenuSecondaryOverlayIndex

Identity: `ov039:020bd654`, ARM, native extent 32 bytes (including any configured pool). Previous symbol: `func_ov039_020bd654`.

EU entrypoint: [eu/src/overlays/ov039/calls/GetPrimaryMenuSecondaryOverlayIndex.c](../src/overlays/ov039/calls/GetPrimaryMenuSecondaryOverlayIndex.c).

```c
int GetPrimaryMenuSecondaryOverlayIndex(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns current primary descriptor+0x0c. Source: [src/ov039/reviewed_helpers/func_ov039_020bd634.c:1-6](../../src/ov039/reviewed_helpers/func_ov039_020bd634.c).
- Passes this value as index to LoadSecondarySubOverlay. Source: [eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c:1-84](../src/overlays/ov039/calls/UpdateSubOverlayHandlers.c).

Contract limits:

- This is not a work size in primary descriptors.

## GetPrimaryMenuSubOverlayWorkSize

Identity: `ov039:020bd674`, ARM, native extent 32 bytes (including any configured pool). Previous symbol: `func_ov039_020bd674`.

EU entrypoint: [eu/src/overlays/ov039/calls/GetPrimaryMenuSubOverlayWorkSize.c](../src/overlays/ov039/calls/GetPrimaryMenuSubOverlayWorkSize.c).

```c
int GetPrimaryMenuSubOverlayWorkSize(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns current primary descriptor+0x10. Source: [src/ov039/reviewed_helpers/func_ov039_020bd654.c:1-6](../../src/ov039/reviewed_helpers/func_ov039_020bd654.c).
- Allocates and clears primaryWork using the returned byte count. Source: [eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c:1-84](../src/overlays/ov039/calls/UpdateSubOverlayHandlers.c).

Contract limits:

- No active-index validity check exists in this getter.

## GetSecondaryMenuSubOverlayWorkSize

Identity: `ov039:020bd694`, ARM, native extent 32 bytes (including any configured pool). Previous symbol: `func_ov039_020bd694`.

EU entrypoint: [eu/src/overlays/ov039/calls/GetSecondaryMenuSubOverlayWorkSize.c](../src/overlays/ov039/calls/GetSecondaryMenuSubOverlayWorkSize.c).

```c
int GetSecondaryMenuSubOverlayWorkSize(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns current secondary descriptor+0x0c. Source: [src/ov039/reviewed_helpers/func_ov039_020bd674.c:1-6](../../src/ov039/reviewed_helpers/func_ov039_020bd674.c).
- Allocates and clears secondaryWork using the returned byte count. Source: [eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c:1-84](../src/overlays/ov039/calls/UpdateSubOverlayHandlers.c).

Contract limits:

- Secondary descriptor+c differs from primary descriptor+c, which is the secondary index.

## DrawMenuTextWithShadow

Identity: `ov039:020be548`, THUMB, native extent 76 bytes (including any configured pool). Previous symbol: `func_ov039_020be548`.

EU entrypoint: [eu/src/overlays/ov039/calls/DrawMenuTextWithShadow.c](../src/overlays/ov039/calls/DrawMenuTextWithShadow.c).

```c
void DrawMenuTextWithShadow(int *obj, int x, int y, int z, u32 color, u32 style, u32 flags);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Selects the menu font for width; draws at x+1,y+1,color+1 and then x,y,color; restores the default font saved in the layer first word. Source: [eu/src/overlays/ov039/calls/DrawMenuTextWithShadow.c:1-15](../src/overlays/ov039/calls/DrawMenuTextWithShadow.c).
- The selector changes canvas font+0x14, not color. Source: [src/ov039/widget_layers/SetTextColorIfFits_020bcd04.c:1-18](../../src/ov039/widget_layers/SetTextColorIfFits_020bcd04.c).
- Logical call inputs are layer,x,y,color,textFlags,text. Source: [src/arm9/font/DrawTextAnchored_020015a0.c:1-35](../../src/arm9/font/DrawTextAnchored_020015a0.c).
- The reset writes the font field at+0x14. Source: [src/arm9/library_nns_g2d/Obj_SetField14_02001490.c:1-1](../../src/arm9/library_nns_g2d/Obj_SetField14_02001490.c).

Contract limits:

- Current z/color/style/flags parameter labels are misleading: actual logical inputs include color,textFlags,text,maxWidth.
- Restores the layer default font from+0, not necessarily the previous canvas font.

## DrawCenteredMenuTextLines

Identity: `ov039:020be594`, THUMB, native extent 68 bytes (including any configured pool). Previous symbol: `func_ov039_020be594`.

EU entrypoint: [eu/src/overlays/ov039/calls/DrawCenteredMenuTextLines.c](../src/overlays/ov039/calls/DrawCenteredMenuTextLines.c).

```c
void DrawCenteredMenuTextLines(int obj, int x, int y, int z, int startIndex);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Measures each line, draws it centered around X, advances Y by the font glyph height and repeats using the returned next-line pointer. Source: [eu/src/overlays/ov039/calls/DrawCenteredMenuTextLines.c:1-16](../src/overlays/ov039/calls/DrawCenteredMenuTextLines.c).
- Width helper takes a UTF16 text pointer and optional next-line pointer. Source: [eu/src/calls/GetTextLayerLineWidth.c:1-15](../src/calls/GetTextLayerLineWidth.c).
- Calls the font-aware draw-string primitive with direction derived from font metadata. Source: [src/arm9/font/DrawDirectional_02001804.c:1-31](../../src/arm9/font/DrawDirectional_02001804.c).

Contract limits:

- The old index argument is a text pointer, and the old z argument is color.
- No text allocation or wrapping-width choice occurs here.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov039/calls/SetMenuPhase.c SetMenuPhase
python tools/verify_idx.py src/overlays/ov039/calls/GetMenuPhase.c GetMenuPhase
python tools/verify_idx.py src/overlays/ov039/calls/StartMenuBrightnessTweens.c StartMenuBrightnessTweens
python tools/verify_idx.py src/overlays/ov039/calls/WaitMenuFadeInThenEnableInput.c WaitMenuFadeInThenEnableInput
python tools/verify_idx.py src/overlays/ov039/calls/WaitSubMenuFadeInThenEnableButtons.c WaitSubMenuFadeInThenEnableButtons
python tools/verify_idx.py src/overlays/ov039/calls/WaitMenuFadeOutThenEnterShutdown.c WaitMenuFadeOutThenEnterShutdown
python tools/verify_idx.py src/overlays/ov039/calls/DispatchMenuPhaseUpdate.c DispatchMenuPhaseUpdate
python tools/verify_idx.py src/overlays/ov039/calls/SetMenuInputEnabled.c SetMenuInputEnabled
python tools/verify_idx.py src/overlays/ov039/calls/GetMenuWork.c GetMenuWork
python tools/verify_idx.py src/overlays/ov039/calls/SelectMenuFontForWidth.c SelectMenuFontForWidth
python tools/verify_idx.py src/overlays/ov039/calls/ResetMenuSubOverlayIndices.c ResetMenuSubOverlayIndices
python tools/verify_idx.py src/overlays/ov039/calls/InvokePrimaryMenuSubOverlayDestroy.c InvokePrimaryMenuSubOverlayDestroy
python tools/verify_idx.py src/overlays/ov039/calls/UpdatePrimaryMenuSubOverlay.c UpdatePrimaryMenuSubOverlay
python tools/verify_idx.py src/overlays/ov039/calls/UpdateSecondaryMenuSubOverlay.c UpdateSecondaryMenuSubOverlay
python tools/verify_idx.py src/overlays/ov039/calls/GetPrimaryMenuSubOverlayIndex.c GetPrimaryMenuSubOverlayIndex
python tools/verify_idx.py src/overlays/ov039/calls/GetPrimaryMenuSecondaryOverlayIndex.c GetPrimaryMenuSecondaryOverlayIndex
python tools/verify_idx.py src/overlays/ov039/calls/GetPrimaryMenuSubOverlayWorkSize.c GetPrimaryMenuSubOverlayWorkSize
python tools/verify_idx.py src/overlays/ov039/calls/GetSecondaryMenuSubOverlayWorkSize.c GetSecondaryMenuSubOverlayWorkSize
python tools/verify_idx.py src/overlays/ov039/calls/DrawMenuTextWithShadow.c DrawMenuTextWithShadow --thumb
python tools/verify_idx.py src/overlays/ov039/calls/DrawCenteredMenuTextLines.c DrawCenteredMenuTextLines --thumb
bash tools/gate.sh
```

All entrypoints in this document pass their official function checks. The full
108-function block passes the fresh gate for all 108 linked modules. Affected
function bytes, resolved relocation targets/types and addends, and all module
hashes match the preserved baseline. Native signatures and algorithms are
unchanged; verified-library receipts remain current.
