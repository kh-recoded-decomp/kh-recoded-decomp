# Font resource and width fallback contracts

The three EU BK9P helpers are Thumb and use the default compiler configuration
from `tools/project.py`. Their defining sources now expose the recovered font
resource and fallback interfaces. Native source/ROM evidence establishes the
contracts below; the final section records the existing verifier commands.

The current names are `LoadUtf16FontResource`, `DrawTextAnchoredWithFontFallback` and `DrawTaggedTextWithFontFallback`.

```c
BOOL LoadUtf16FontResource(FontResource *resource, const char *path);
void DrawTextAnchoredWithFontFallback(TextLayerFontView *layer,
    s32 x, s32 y, s32 color, u32 drawFlags, const u16 *text,
    NNSG2dFont *fallbackFont, s32 maxWidth);
void DrawTaggedTextWithFontFallback(TextLayerFontView *layer,
    s32 x, s32 y, s32 color, s32 alternateColor, const u16 *text,
    NNSG2dFont *fallbackFont, s32 maxWidth);
```

These interfaces are declared in `src/text/FontResources.h`. The resource view
checks its native 12-byte size and file-buffer offset +8; the partial layer view
checks the active canvas-font offset +0x14. The layer view is not a complete
allocation size. Existing shared callers still contain legacy word declarations
and must be normalized consistently when building a host port.

A native FontResource occupies twelve bytes: an eight-byte NNSG2dFont at offset zero and the owned file allocation at +8. The loader stores the allocated NFTR file in that last word, unpacks/relocates it and installs the UTF16 character splitter in the font prefix. Its return is always 1 if control returns; it does not report a failed load or a missing FINF block. It does not release a previous allocation before overwriting the pointer.

The old shared spelling had four formal inputs. ROM instructions arrange only
resource and path; incoming R2/R3 remain untouched before the file-loader call.
`Archive_LoadFile` discards its third argument and the lower loader does not use
its fourth. The defining EU helper now states the two logical inputs without
inventing heap or encoding parameters, retaining the exact 26-byte result. Other
shared loader callers still need their own interface recovery.

Text layers borrow the font. Their word at +0 is the default font, whereas the active text-canvas font is at +0x14 (canvas starts at +0x10). The function named Obj_SetField14 is specifically an active canvas-font setter. A typed host caller can borrow `&resource.font`; it must keep the owned file buffer alive while that font is used. The native release helper frees fileBuffer at +8 and leaves the pointer fields unchanged.

Both drawing wrappers first measure lines using the active canvas font at entry. If the largest measured width is strictly greater than maxWidth, they temporarily select fallbackFont. Equality retains the entry canvas font. The comparison is signed; a negative threshold selects fallback even for width zero. The wrapper draws once and always restores the layer.defaultFont value cached at entry to canvas.pFont afterward. It does **not** save and restore an arbitrary canvas-font override.

The fallback is a choice of another font, not glyph fallback, scaling, truncation or ellipsis. The wrappers do not test whether the chosen fallback fits. Anchored drawing can still remeasure that chosen font for positioning; that is separate from selecting the fallback.

| Function | Fifth input | Drawing behavior |
| --- | --- | --- |
| Anchored variant | drawFlags | Passes origin/alignment flags into the NNS anchored renderer. |
| Tagged variant | alternateColor | Writes the primary and alternate tag colors, then invokes the tagged renderer. It is not an alignment flag mask. |

GetLineWidth measures glyph charWidth plus canvas hSpace, subtracts the final hSpace and clamps the result to zero. A missing glyph uses the font's alterCharIndex. A line-feed provides a continuation pointer, so the wrappers scan subsequent LF-separated lines. NUL or control 0x1f ends that measurement scan. The tagged renderer can subsequently process 0x1f as a centered next-line control and continue drawing following text, so this fallback decision is not a complete tagged-text bounding-box calculation.

The tagged renderer stores its two colors in shared global state and does not restore that pair after drawing. Its tag handler selects color 1/2, the high byte of primary color for tag 4, and the centered next-line behavior for 0x1f. Preserve those controls and the original font-restoration rule when replacing the SDK renderer.

## Verification

From `eu/`:

```sh
python tools/verify_idx.py src/calls/LoadUtf16FontResource.c LoadUtf16FontResource --thumb
python tools/verify_idx.py src/calls/DrawTextAnchoredWithFontFallback.c DrawTextAnchoredWithFontFallback --thumb
python tools/verify_idx.py src/calls/DrawTaggedTextWithFontFallback.c DrawTaggedTextWithFontFallback --thumb
bash tools/gate.sh
```

Expected sizes are 26, 90 and 90 bytes. Integration preserves baseline objects
and compares affected production texts, resolved relocation targets/types and
addends, then requires unchanged hashes for all 108 linked modules. The typed
resource/view and logical arguments are justified by the loader, native callers,
line-width helper, canvas setter and drawing bodies, not by byte equality alone.
