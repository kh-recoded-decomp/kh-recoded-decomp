# Packed resources and wide-text wrappers

`PackedResource.h` describes the recovered file header, loaded view and entry
accessor used by overlay 27. The entry accessor is generic: it computes an
address and performs no text decoding. The two formatting wrappers impose a
16-bit text interpretation only when they select an entry as a format string.

## Evidence and names

| Previous symbol | Current name | Established behavior |
|---|---|---|
| `func_ov027_020ba2c8` (`0x020ba2c8`) | `GetPackedFileEntry` | Checks the view's count, follows per-record byte strides and returns the selected payload after its four-byte record prefix. |
| `func_ov027_020ba300` (`0x020ba300`) | `FormatPackedWideText` | Builds the recovered DS argument stream, calls the V wrapper and returns the supplied destination. |
| `func_ov027_020ba33c` (`0x020ba33c`) | `VFormatPackedWideText` | Uses an entry as `Text_VSNPrintfWide`'s format, passes the argument stream and returns the destination. |
| `func_ov001_02076a54` (`0x02076a54`) | `DrawPackedFieldMenuEntry` | Copies the menu's frame tile template to the selected cell and draws its packed entry through the existing field text helper. |

`LoadPackedFileView` is the existing loader that establishes the layout. The
loader, accessor and formatting wrappers now share one definition. Three
native consumers use that same view instead of a separate three-word
placeholder or message-set structure: `ShowTitleNotice`, `DrawFieldSlotCell`
and `InitFieldCommandMenu`.

## Header and loaded view

| File offset | Type | Established use |
|---|---|---|
| `0x00` | `u32` | Payload byte offset relative to the loaded file base. |
| `0x04` | `u32` | Entry count. |

These eight bytes are the established header prefix. No magic, version,
encoding tag or total file length is recovered by this block.

| View offset | Type | Established use |
|---|---|---|
| `0x00` | `void *` | Owning loaded-buffer address. The loader reads a typed header from it. |
| `0x04` | `u32` | Cached count copied from the file header. |
| `0x08` | `u8 *` | Cached payload address: file base plus the header's payload offset. |

The DS view is 12 bytes. Keeping the owner as `void *` is deliberate: its
actual release helper writes through a `void **` owner slot. A typed header
pointer is used when interpreting the file, avoiding an incompatible cast
between pointer-to-pointer types during release.

The loader clears the view, chooses the existing backend according to its
`fromTail` selector and passes the existing value 14 to that backend. The
resource argument is the current 32-bit DS file-ID/path-address word. The loader
then copies count and payload address into the view. It neither validates the
header's offset/count against a total length nor frees a previous owner before
replacing the view. The cached fields do not follow later header edits.

## Entry traversal

The first word of each record is interpreted as a signed 32-bit byte stride to
the next record. Since the selected payload begins four bytes after that word,
the stored stride must account for its prefix as well as its payload. Access
starts at `view->payload` and adds one stored stride for each preceding entry;
this is not a fixed-size table or an offset array. Querying entry N is linear
in N, and entries can have different sizes.

The exact bounds test is `(u32)index >= view->count`; traversal uses the signed
index. A matching or larger unsigned index returns null. Valid callers provide
a sane count and nonnegative index in range. Do not treat this unsigned test
as a complete malformed-file or negative-index validator for arbitrary counts.
There is no check for null view, record length, header alignment, backward or
zero strides, file bounds or a payload terminator. A host parser should handle
these constraints deliberately when reading the DS file format; this block
adds no new checks to the matching path.

The returned address is borrowed from the loaded buffer. It carries no size,
encoding or independent ownership. Releasing that buffer invalidates its entry
addresses; replacing a view alone does not release the previous buffer. The formatting wrappers require a valid selected entry that
contains a terminated 16-bit format string. They do not check the accessor's
null result before passing it to the formatter.

## Wide-format capacity and results

Capacity counts **16-bit code units**, including room for termination. It does
not count bytes or host `wchar_t` elements. Both wrappers return the original
destination pointer; neither reports a formatted length, truncation or success.

The underlying formatter's sink consumes one capacity unit per halfword write.
Its logical cursor still advances for attempted output after storage fills.
At the end it writes a terminator at the current cursor when space remains,
or at destination element `capacity - 1` when full and capacity is nonzero.
With zero capacity it suppresses destination writes, while still interpreting
the format and its arguments. Its attempted code-unit count is discarded by
both wrappers. Callers must provide a destination whose allocation matches
the passed capacity; the wrappers add no destination-null check.

This is a custom formatter, not a recovered promise of standard `printf`
compatibility. Among the established differences relevant to a port:

- `%s` consumes a pointer to 16-bit units.
- `%f` uses the fixed-point formatting helper, rather than fetching a C
  variadic `double` by assumption.
- `%p` uses the native 32-bit pointer convention and eight-digit precision.
- The implemented `%n` paths calculate a byte count from the 16-bit cursor,
  rather than simply storing the number of wide code units.

Other supported modifiers and edge cases belong to `Text_VSNPrintfWide` and
its helpers; do not replace that call with a host `vswprintf` solely because
the names resemble one another.

## Native variadic ABI and host port

`PackedWideFormatArgs` is explicitly a DS argument-word pointer (`char *`), not
a portable C `va_list`. The variadic wrapper has four fixed parameters. Its
matched implementation obtains the following stack argument words from the
address of its final fixed parameter, using the existing four-byte alignment.
The V wrapper passes that stream by value. `Text_VSNPrintfWide` consumes argument
slots rounded to four bytes, including pointer and multiword values.

A host port needs its own `va_start`/`va_list` or an explicit typed argument
representation, and a formatter that reads those host values correctly. Do not
cast a 64-bit host `va_list` or pointer to the native DS word stream. Keep
16-bit text/code-unit capacities separate from the host's `wchar_t` size and
retain the custom format semantics that callers use.

The resource view is also a DS layout, not a serialized host-pointer format.
Read file metadata/record words using the file's byte layout and use native
host owner/payload pointers in the host view. Establish buffer lifetime and
bounds from the asset/loader contract instead of treating a cached pointer as
a separate allocation.

## Field-menu client and release

`DrawPackedFieldMenuEntry` retains the observed DS menu accesses: frame-template
pointer at `+0xe4`, indexed cell pointer at `+0x74 + index * 4`, cell pixel buffer
at cell `+0x24`, and text context at menu `+0x34`. It copies `0x200` bytes, selects
the packed entry with that same index and calls the existing text helper with
coordinates `(0, 4)`, color 4 and width-limit value `0x38`, using `GetFieldFont1`.
It does not validate the index or the resulting entry before delegating.
These offsets do not establish a complete menu/cell allocation type for a host.

`ShowTitleNotice` releases `messages.file` using `FreePointerIfSet`.
`InitFieldCommandMenu` now also passes `&view.file`/`&slotView.file` explicitly,
with the helper's actual `void **` declaration. The old call passed the
three-word view's address and happened to address the same first word.
Release frees and clears only the owner word: cached count and payload remain
unchanged and must not be used as live entries afterward. The accessor and
formatting wrappers do not transfer buffer ownership.

Shared US wrappers still contain older argument/return views through EU
aliases. Native consumers converted in this block share the real resource
layout and prototypes; recover the remaining caller views before treating the
entire DS API as a host interface.

## Reproduction

From `eu/`:

```sh
python tools/rebuild_index.py --write --refresh-reloc-names
python tools/verify_idx.py src/overlays/ov027/calls/GetPackedFileEntry.c GetPackedFileEntry
python tools/verify_idx.py src/overlays/ov027/calls/FormatPackedWideText.c FormatPackedWideText
python tools/verify_idx.py src/overlays/ov027/calls/VFormatPackedWideText.c VFormatPackedWideText
python tools/verify_idx.py src/overlays/ov027/calls/LoadPackedFileView.c LoadPackedFileView --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DrawPackedFieldMenuEntry.c DrawPackedFieldMenuEntry --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InitFieldCommandMenu.c InitFieldCommandMenu --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DrawFieldSlotCell.c DrawFieldSlotCell --thumb
python tools/verify_idx.py src/overlays/ov000/calls/ShowTitleNotice.c ShowTitleNotice
python tools/verify_idx.py src/calls/Text_VSNPrintfWide.c Text_VSNPrintfWide --thumb
bash tools/gate.sh
```

The four renamed functions retain 56, 60, 44 and 72 bytes; the loader retains
54 bytes. The full verification also covers the formatter/sink, representative
native clients, every renamed caller and all 108 freshly linked modules.
Naming and recovered types add no C or DATA reconstruction credit.
