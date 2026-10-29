# Widget positioning

`func_ov027_020b91e8` (`SetWidgetPosition`) is matched C in
`src/overlays/ov027/calls/func_ov027_020b91e8.c`, included in the linked EU build.
Its four arguments are the indexed-record array, a widget, a two-coordinate
input and a mode. The superseded nonmatching draft has been removed.

## Data and behavior

The recovered widget prefix in `src/overlays/ov027/WidgetPosition.h` contains:

| Offset | Field | Meaning used by this function |
|---|---|---|
| `0x14` | `recordIds[2]` | Two destination record indices; `-1` skips a slot. |
| `0x34` | `position` | Base position returned by `GetWidgetPosition`. |
| `0x3c` | `offset` | Displacement relative to that base. |

The prefix ends at `0x44`; it is not the size of the complete widget allocation.
The setter leaves the base position unchanged. After updating the selected
offset components, it sends the resulting base-plus-offset position to both
destination records, in slot order. Duplicate indices are written twice.
`IndexedRecord_SetPair` independently ignores any negative index; the setter's
own sentinel comparison is specifically against `-1`.

| Mode | Input | Offset components replaced |
|---|---|---|
| `COMBINED_XY` (`0`) | Absolute `input.x`, `input.y` | Both, with input minus base. |
| `COMBINED_X` (`1`) | Absolute `input.x` | X only. |
| `COMBINED_Y` (`2`) | Absolute `input.y` | Y only. |
| `OFFSET_XY` (`3`) | Relative `input.x`, `input.y` | Both directly. |
| `OFFSET_X` (`4`) | Relative `input.x` | X only. |
| `OFFSET_Y` (`5`) | Relative `input.y` | Y only. |
| Other values | Unused | No widget or destination-record writes. |

The getter `ResolveWidgetPositionComponents` has a specific asymmetry:
`OFFSET_Y` returns the Y offset in `out.x`, while `COMBINED_Y` returns absolute
Y in `out.y`. Do not copy the `OFFSET_Y` convention into this setter: the setter
reads both Y modes from `input.y`.

`GetWidgetPosition` simply returns `&widget->position`; its context argument is
unused. The EU definition now uses this typed two-argument interface, replacing
the old four-word decompiler placeholder, and still matches all eight ROM bytes.
Both getter declarations live in `WidgetPosition.h`.

The getter clears its eight-byte output before reading the widget. With output
pointing at the complete base or offset field, that field is therefore cleared
before the coordinates are resolved. This is distinct from the setter's alias
behavior. Invalid getter modes still clear the output and return its address.

## Arithmetic and overlap observations

The widget must refer to mutable storage. The matching source takes a const
read view and obtains a mutable target view before changing the offset; the
qualifier does not make this a read-only operation. A port can expose an ordinary
mutable-widget setter without retaining this compiler aliasing pattern.

Coordinate addition and subtraction wrap at 32 bits. The implementation expresses that
through unsigned arithmetic before conversion to signed `s32`, avoiding signed
arithmetic overflow in the calculation. A port must retain signed 32-bit
coordinate storage and the target's two's-complement interpretation; changing
these operations to saturating arithmetic changes behavior.

The executable tests include input pointing at the widget's complete `position`
or `offset` pair. They also stress the original machine code with input starting
at `0x38` or `0x40`, shifted by one coordinate. In absolute XY mode the ROM reads
both subtraction inputs before storing either offset component; the implementation keeps
explicit snapshots to describe that observed sequence.

These shifted pointers are machine-code stress cases, not a recovered public C
API contract. They need not designate complete `WidgetPoint` objects under the
C object/effective-type rules, and their use by real callers has not been
established. Compiler execution agreeing on these cases does not prove their
language-level validity on another host. A port should first audit its callers
and choose explicit byte-buffer handling if partial object overlap is required.

The two `MI_CpuCopy8` calls retain the original copy routine. The stress tests
also replay its actual ARM instructions with shifted overlaps; this does not
establish a general overlap guarantee or a `memmove` contract for that SDK API.

`python tools/test_widget_position.py -v`, run from `eu/`, checks:

- 2,376 combinations of coordinates, six valid modes and destination-index
  pairs, on each of the original and compiled matching C images. Inputs include
  signed endpoints and random full-width words. Whole data-buffer comparisons
  check unchanged bytes as well as results; observed record writes check order.
- Six invalid modes on both images, with no widget/input/record mutations.
- Original getter execution confirming the different Y output conventions,
  followed by setter checks confirming both modes consume `input.y`.
- 864 getter cases per image: 32 coordinate pairs, six valid and three invalid
  modes, and output separate from the widget or pointing at its complete base
  or offset point. Original, matching CodeWarrior C, GCC and Clang images are
  checked for wrapped results, returned output pointers and all unchanged bytes.
- Twenty-four input/widget alias cases on both images, comparing complete
  data buffers and destination-write order.
- The same valid-mode arithmetic model and overlap stress cases on GCC 12.2.1
  (Arm GNU 12.2.Rel1) and Clang 22.1.3 builds. These are separate behavior checks,
  with 392-byte and 364-byte outputs respectively, not matching builds. These
  optional checks skip when their compiler is unavailable.

All four callees (`GetWidgetPosition`, `MI_CpuFill8`, `MI_CpuCopy8` and
`IndexedRecord_SetPair`) execute their original instructions. There are no
mocked engine calls or instruction substitutions. Candidate ELF branch
relocations are resolved for execution; this does not modify production
objects, the ROM or the ordinary verifier.

The free compilers emit inline switch tables. The test's small ELF linker resolves
their local text-section addresses as well as external ARM branch relocations;
it rejects local destinations outside the function. This links the candidate
for execution without changing the production verifier or matching policy.

## Matching status

The setter compiles with CodeWarrior `dsi/1.3p1` to exactly 408 bytes and five
relocations. The const read view and mutable target preserve the original
single-axis instruction scheduling. Explicit unsigned coordinate arithmetic and
named modes retain the complete match; the earlier 24-byte gap is closed.
`GetWidgetPosition` matches eight bytes, and `ResolveWidgetPositionComponents`
matches 200 bytes with three relocations. The getter also uses unsigned
arithmetic for wrapping additions.

```sh
python tools/verify_idx.py src/overlays/ov027/calls/func_ov027_020b91e8.c func_ov027_020b91e8
python tools/verify_idx.py src/overlays/ov027/calls/GetWidgetPosition.c GetWidgetPosition
python tools/verify_idx.py src/overlays/ov027/calls/ResolveWidgetPositionComponents.c ResolveWidgetPositionComponents
python tools/test_widget_position.py -v
```
