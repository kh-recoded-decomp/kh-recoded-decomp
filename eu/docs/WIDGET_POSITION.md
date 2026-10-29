# Widget position setter

`func_ov027_020b91e8` is reconstructed in
`src/nonmatching/SetWidgetPositionComponents.c`. It remains outside the linked
build and matching-C coverage. Its four arguments are the indexed-record array,
a widget, a two-coordinate input and a mode.

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

## Arithmetic and overlap observations

Coordinate addition and subtraction wrap at 32 bits. The draft expresses that
through unsigned arithmetic before conversion to signed `s32`, avoiding signed
arithmetic overflow in the calculation. A port must retain signed 32-bit
coordinate storage and the target's two's-complement interpretation; changing
these operations to saturating arithmetic changes behavior.

The executable tests include input pointing at the widget's complete `position`
or `offset` pair. They also stress the original machine code with input starting
at `0x38` or `0x40`, shifted by one coordinate. In absolute XY mode the ROM reads
both subtraction inputs before storing either offset component; the draft keeps
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
  pairs, on each of the original and compiled candidate images. Inputs include
  signed endpoints and random full-width words. Whole data-buffer comparisons
  check unchanged bytes as well as results; observed record writes check order.
- Six invalid modes on both images, with no widget/input/record mutations.
- Original getter execution confirming the different Y output conventions,
  followed by setter checks confirming both modes consume `input.y`.
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

The current draft compiles with CodeWarrior `dsi/1.1` to 408 bytes, the original
size, with the same five relocation offsets and targets. Twenty-four ordinary
instruction bytes still differ in the absolute single-axis cases. The first
difference reported by the ordinary verifier is `0x95`; the remaining issue is
arithmetic/store scheduling and register allocation. The propagation pragma
preserves this closer instruction layout and has no effect on the documented
operation. These remain mismatches, and passing the behavior tests does not
award matching-C credit.
