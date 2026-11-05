# Movie subtitles, scrolling text and board widgets (EU)

This document describes nineteen EU functions and the contracts needed to port their behavior. Names follow the function bodies, real callees and callers. Native identities include the overlay bank because different overlays can occupy the same address.

The layouts below are partial views of 32-bit DS storage. They establish the listed fields and operations, not complete allocation sizes or host structure layouts.

## Movie script commands

| Function | EU identity | Established contract |
| --- | --- | --- |
| `IsMovieSceneFlag8Set` | ov003 `02064744`, ARM | Returns whether scene halfword `+2` has mask `8`. The purpose of this flag remains unassigned. |
| `MovieScriptCmd_StartStream` | ov003 `02064764`, Thumb | Examines three 8-byte operands in order. An operand is resolved only when its type is `2`. Passes the first resolved pointer, or NULL, to `MovieScene_StartStream`; returns `1`. |
| `MovieScriptCmd_WaitForSubtitleFrame` | ov003 `020647b8`, Thumb | Reads an integer threshold, stores it through `ScriptCmd_SetElemField`, then applies the frame-wait rule below. |
| `MovieScriptPoll_SubtitleFrame` | ov003 `020647f0`, Thumb | Applies the same rule to its supplied threshold. It does not decode an operand or write the script element field. |
| `MovieScriptCmd_RequestStop` | ov003 `02064844`, Thumb | Sets scene byte `+0x8b9` and returns `0`. |
| `MovieScriptPoll_StopRequestClear` | ov003 `02064850`, Thumb | Returns `1` when that request byte is zero, otherwise `0`. This does not establish that every movie resource has been destroyed. |

The frame-wait rule is ordered:

1. If neither movie state word is `2`, return `1` immediately.
2. While either state is `2`, threshold `0` returns `0`.
3. Otherwise return whether the current presented-frame count is at least the threshold.

`MovieScene_IsAnyStateTwo` reads the current task's scene state at `+0x8b0` and `+0x8b4`; it has no logical input. `GetMoviePresentedFrameCount` returns the playback timer's presented-page counter at `+0x48`, or `-1` if that timer is absent. The inherited private `SubtitleStream` label does not establish a separate subtitle-timing owner; the VBlank framebuffer-swap writer establishes this counter's role. Negative thresholds and the missing-record sentinel therefore retain their ordinary signed-comparison behavior.

The command's `ScriptCmd_SetElemField` call is a real side effect: it writes the threshold at script object `+ currentIndex * 0x70 + 0x20`. The original assembly performs that call before the state check. Its incidental register result is not an input required by `MovieScene_IsAnyStateTwo`.

Starting a stream still resolves the second and third type-2 operands even though their returned pointers are discarded. Preserve those evaluations. The adapter does not copy or free operand storage; lifetime handling belongs to the stream-start path.

## Subtitle renderer

| Function | EU identity | Established contract |
| --- | --- | --- |
| `SetMovieSubtitleAlignmentMode` | ov003 `020649a0`, ARM | Stores the supplied alignment word at renderer `+0x64`. |
| `HandleMovieSubtitleControlCode` | ov003 `020649fc`, ARM | Handles the control values listed below and returns TRUE. |
| `DrawNextMovieSubtitleGlyph` | ov003 `02064ec4`, ARM | Consumes control/sentinel results until a code unit is available, draws one glyph in two passes and advances the horizontal pen. Returns FALSE at end of base text; it also retains a branch for a zero line-helper result, although the current line helper always returns `1`. |
| `DrawMovieSubtitleTextImmediate` | ov003 `02065028`, ARM | Installs a borrowed byte-string pointer, updates alignment and draws while the continuation predicate permits. Afterwards clears the base pointer, base cursor and active source, and marks upload pending. |

The immediate-draw routine's second argument is a text pointer. Its inherited `leadTime` parameter label is incorrect: the word is stored at `+0x68` and consumed as a character buffer. No timing conversion occurs in this function.

### Recovered renderer fields

| Offset | Established use |
| --- | --- |
| `+0x34` | Horizontal line-width limit. |
| `+0x38` | Vertical line limit used by line advancement. |
| `+0x3c`, `+0x40` | Left and top draw margins, read as halfwords. |
| `+0x44` | Upload-pending flag. |
| `+0x48` | Additional line spacing. |
| `+0x4c`, `+0x50` | Horizontal and vertical pen positions. |
| `+0x54` | Foreground color passed to the glyph draw handler. |
| `+0x58` | Base-string byte cursor. |
| `+0x5c` | Alternate-string byte cursor. |
| `+0x60` | Active source: `0` is the base string; `1`-`4` select alternate strings. |
| `+0x64` | Alignment mode. This is separate from active source. |
| `+0x68` | Borrowed base-string pointer. |
| `+0x6c`-`+0x78` | Four borrowed alternate-string pointers. |
| `+0x7c` | Extra horizontal glyph spacing. |

The input is a byte string with ASCII, supported two- and three-byte UTF-8 forms, and game control bytes. The decoder produces 16-bit code units. It does not implement a complete Unicode decoder: four-byte UTF-8, validation and recovery from malformed input are not established. A port must not reinterpret the input pointer as a UTF-16 string.

Ending an alternate string switches back to the base source and returns internal sentinel `1`. Ending the base string returns `0`. The draw routine skips sentinel `1` rather than rendering it.

### Control values

| Value | Operation |
| --- | --- |
| `1` | Calls `SubtitleText_BeginDraw`: resets active source and vertical pen, marks upload pending and calls the renderer's reset handler. |
| `3` | Advances the cursor selected on entry to the control handler once more. |
| `8`, `9`, `11`, `12` | Select alternate source `1`, `2`, `3`, `4` respectively and reset its cursor to zero. |
| `10` | Advances the subtitle line. |

The decoder advances past a control byte before invoking the handler. Preserve the extra advancement performed by control `3`. Unlisted control values have no action in this handler and still return TRUE. The valid active-source range is an existing precondition, not a newly added bounds check.

### Alignment, wrapping and draw order

The existing function named `updateMovieStreamLeadTime` computes horizontal alignment: mode `0` sets pen X to zero, mode `1` centers and clamps a negative initial X to zero, and mode `2` right-aligns without that clamp. Centered subsequent lines reuse a cached X when pen Y is nonzero. This shared cache matters if multiple renderers are interleaved.

The existing `advanceMovieStreamWindow` advances pen Y by line spacing plus font height, scrolls when the next line would exceed the vertical limit, and recalculates alignment. It performs no playback-time operation. `IsMovieStreamReady` is the text continuation predicate: it tests the current base byte in source mode `0`, returns TRUE in alternate modes `1`-`4`, and FALSE for other modes.

`DrawNextMovieSubtitleGlyph` preserves the following sequence:

1. Decode through sentinel `1`; for a nonzero code unit, capture the current pen Y before resolving the glyph.
2. Resolve the glyph, compute its advance and, if needed, advance the line.
3. Test for a newline in the base text pointer. This test does not switch to the active alternate pointer.
4. Draw color `2` at `(x + 1, y + 1)`, then the configured foreground at `(x, y)`, including margins.
5. Advance pen X and return TRUE.

The actual source captures pen Y before glyph resolution and before possible line advancement; keep that capture before any operation that can affect line position. In particular, do not replace it with a fresh post-wrap pen Y. Glyph advance uses the font width record's signed byte plus configured spacing. When the base text contains no newline, line spacing plus font height is added to the captured Y before drawing. The newline test and two draw calls are observable behavior.

The immediate loop is controlled by the continuation predicate; it ignores each glyph draw result. Replacing that with a loop that stops on FALSE can change behavior. The selected base/alternate buffers must remain valid throughout this loop. The routine consumes text and marks upload pending; that alone is not proof that a VRAM transfer has already completed.

The existing helper named `MobiClip_ResolveGlyphRecord` resolves font glyph indices, widths and image pointers through font APIs. It is not a video-codec operation. Its font/image data is borrowed by the draw call; these adapters do not own or free it. The old naming corrections in this section describe established behavior and are separate from the nineteen-function inventory.

## Scrolling-text display adapters

| Function | EU identity | Logical interface and effect |
| --- | --- | --- |
| `SetScrollMainBlendBrightness` | ov004 `02061694`, ARM | `void(int planes, int brightness)`: delegates to `G2x_SetBlendBrightness_` at MAIN blend control `0x04000050`. |
| `SetScrollSubBlendBrightness` | ov004 `020616b4`, ARM | Same operation for SUB blend control `0x04001050`. |
| `ClearScrollMainBlendControl` | ov004 `0206223c`, ARM | `void(void)`: writes halfword zero to MAIN blend control only. |
| `ClearScrollSubBlendControl` | ov004 `02062250`, ARM | Same write for SUB blend control only. |
| `UpdateScrollTextScreensWrapper` | ov004 `020622e4`, ARM | `void(void)`: tail-delegates to `UpdateScrollTextScreens`. |

The brightness helper chooses a brighten/darken control mode from the sign and writes the absolute coefficient at register base `+4`. It does not allocate or return a buffer. Clearing blend control does not clear all blend registers or the stored coefficient.

`UpdateScrollTextScreens` runs the crossfade path when screen 0 is in state `3` or `4`; otherwise it updates brightness for both screens. These wrappers add no ownership or synchronization guarantee.

## Text layer and board widget adapters

| Function | EU identity | Established contract |
| --- | --- | --- |
| `InitOv023TextLayer26` | ov023 `020b5944`, Thumb | Copies eight halfwords of frame data, obtains tile-table entry `26` (`0x1a`) and field font 3, initializes the text layer at work `+0x0c` with layer argument `6`, marks the corresponding table row dirty and stores work `+8 = 1`. |
| `BlitBoardWidgetAndFinishPendingTeardown` | ov024 `020b65c4`, Thumb | Blits the supplied widget through the tile table at context `+8`; afterwards, if teardown is pending, releases and clears six resource slots and clears the pending flag. |
| `ClearBoardWidgetTileArea` | ov024 `020b65e8`, Thumb | Clears the clipped tile area for the supplied widget through that same context table. |
| `RerollBoardSlotsWrapper` | ov024 `020b72fc`, Thumb | Tail-delegates to `RerollBoardSlots` with the incoming board pointer. |

For the widget operations, the supplied value is a widget pointer, despite inherited integer parameter declarations. The blit helper looks up its table row, copies a screen rectangle and marks that row dirty. The clear helper clips the rectangle, zeroes affected halfword rows and marks the row dirty. Neither operation is an immediate-display guarantee, and the supplied widget is not freed by these adapters.

Deferred teardown happens after the blit attempt, including when the lower-level row lookup prevents a copy. `ReleaseOverlayResourceSlots` frees each non-NULL pointer among six slots and clears it. It does not establish that the widget or outer context has been destroyed.

The ov023 text initializer borrows the selected font and layer screen base. `InitTextLayerAtFromEnd` selects allocation from the heap end and uses a non-NULL screen base to choose map filling. Internal text-layer storage must follow that subsystem's cleanup contract. This adapter establishes only its used fields at work `+8` and `+0x0c`; it does not establish a complete enclosing dialog layout. Only the work pointer has a proved logical input role; unused saved native argument slots do not justify public fields or parameters.

Rerolling mutates the supplied board only when `needsReset` is nonzero. It clears that flag, rebuilds slot values, randoms, bonuses and links, and chooses initial picks. The existing target also passes the global board pointer to some filling/bonus helpers. A port must reconcile that dependency before assuming arbitrary independent board instances. Preserve RNG evaluation order and the in-place compaction sequence.

## Native ABI and evidence boundaries

Several matching sources use erased declarations such as `void *f()` or generated four-word argument lists. The native veneers do not make those logical interfaces real:

- Alignment is one store from R1 to `[R0 + 0x64]`, followed by return. R0 remains the renderer address; that residual register alone does not establish a fluent host setter API.
- The blend clear helpers return with their MMIO address still in R0. Their useful operation is the halfword write; no memory ownership is returned.
- The scroll update wrapper is an ARM literal-loaded tail branch. The board reroll wrapper is a Thumb literal-loaded tail branch; its real callee consumes the preserved incoming board pointer and has a void interface.
- The wait command's real element-field write is retained even though the subsequent predicate has no input.

For reproduction, the EU symbol/configuration identity is authoritative. Relevant native source families are `eu/src/overlays/ov003`, `eu/src/overlays/ov004`, `eu/src/overlays/ov023`, `eu/src/overlays/ov024` and the actual tile-table helpers in `eu/src/overlays/ov027`. Font resolution and text-layer initialization are shared MAIN routines. Root-tree include filenames can retain US addresses and misleading SDK categories; neither proves the EU bank, logical signature or ownership.

A host port should represent pointers and callbacks with host types, translate MMIO effects through its display interface, and preserve the control/cursor, rounding and draw-order behavior described above. Native matching declarations remain a separate compatibility boundary.

## Verification

From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov003/calls/IsMovieSceneFlag8Set.c IsMovieSceneFlag8Set
python tools/verify_idx.py src/overlays/ov003/calls/MovieScriptCmd_StartStream.c MovieScriptCmd_StartStream --thumb
python tools/verify_idx.py src/overlays/ov003/calls/MovieScriptCmd_WaitForSubtitleFrame.c MovieScriptCmd_WaitForSubtitleFrame --thumb
python tools/verify_idx.py src/overlays/ov003/calls/MovieScriptPoll_SubtitleFrame.c MovieScriptPoll_SubtitleFrame --thumb
python tools/verify_idx.py src/overlays/ov003/calls/MovieScriptCmd_RequestStop.c MovieScriptCmd_RequestStop --thumb
python tools/verify_idx.py src/overlays/ov003/calls/MovieScriptPoll_StopRequestClear.c MovieScriptPoll_StopRequestClear --thumb
python tools/verify_idx.py src/overlays/ov003/auto/SetMovieSubtitleAlignmentMode.c SetMovieSubtitleAlignmentMode
python tools/verify_idx.py src/overlays/ov003/calls/HandleMovieSubtitleControlCode.c HandleMovieSubtitleControlCode
python tools/verify_idx.py src/overlays/ov003/calls/DrawNextMovieSubtitleGlyph.c DrawNextMovieSubtitleGlyph
python tools/verify_idx.py src/overlays/ov003/calls/DrawMovieSubtitleTextImmediate.c DrawMovieSubtitleTextImmediate
python tools/verify_idx.py src/overlays/ov004/calls/SetScrollMainBlendBrightness.c SetScrollMainBlendBrightness
python tools/verify_idx.py src/overlays/ov004/calls/SetScrollSubBlendBrightness.c SetScrollSubBlendBrightness
python tools/verify_idx.py src/overlays/ov004/auto/ClearScrollMainBlendControl.c ClearScrollMainBlendControl
python tools/verify_idx.py src/overlays/ov004/auto/ClearScrollSubBlendControl.c ClearScrollSubBlendControl
python tools/verify_idx.py src/overlays/ov004/calls/UpdateScrollTextScreensWrapper.c UpdateScrollTextScreensWrapper
python tools/verify_idx.py src/overlays/ov023/calls/InitOv023TextLayer26.c InitOv023TextLayer26 --thumb
python tools/verify_idx.py src/overlays/ov024/calls/BlitBoardWidgetAndFinishPendingTeardown.c BlitBoardWidgetAndFinishPendingTeardown --thumb
python tools/verify_idx.py src/overlays/ov024/calls/ClearBoardWidgetTileArea.c ClearBoardWidgetTileArea --thumb
python tools/verify_idx.py src/overlays/ov024/calls/RerollBoardSlotsWrapper.c RerollBoardSlotsWrapper --thumb
bash tools/gate.sh
```

Integration preserves baseline objects and compares affected production texts,
resolved relocation targets/types and addends. All 108 linked module hashes
must remain identical. The text encoding, cursor, glyph draw order, borrowed
buffer and deferred-resource contracts above are established separately from
the byte comparison.

The fuller [movie contracts](MOVIE_CAPTION_DECODER_CONTRACTS.md) distinguish
the timer's presented/decode/consumed counters and reader/decoder/caption owners.
Overlay003's two state words and stop-request byte remain distinct from the
overlay022 scene's playback phase and pending-caption-transfer byte.
