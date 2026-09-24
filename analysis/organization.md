# Code organization and verified progress

The project uses **system → overlay/module → subsection → function**. The
reviewed assignments are in `config/bk9e/organization.json`. Overlay IDs,
addresses, symbol identities, source paths and ROM layout are unchanged.
ARM9, ITCM, DTCM and ARM7 use the module level alongside the overlays.

Systems group related overlays using callers and shared structures. Each
subsection lists its original function symbols and the evidence for that
grouping. For example, `movie_playback` contains `ov003` and `ov022`;
`ov001` has actor animation, actor state and appearance, script commands,
object creation, and unclassified code.

Unlisted functions automatically belong to their module's **Unclassified code**
subsection. They are still in the denominator. Address proximity or a successful
byte match alone does not establish a semantic relationship. Review Ghidra
callers, callees and shared types before moving a function into a named group;
include related unmatched functions when the evidence supports their ownership.
The catalog records evidence and, where needed, uncertainty. Ghidra signatures
and types remain in the corresponding `analysis/*.json` and `analysis/types/`
knowledge files.

## Browse the hierarchy

These commands recompile registered functions and compare every byte against
the extracted ROM before showing progress:

```text
python tools/khrecoded.py progress
python tools/khrecoded.py progress --system movie_playback
python tools/khrecoded.py progress --module ov001
python tools/khrecoded.py progress --module ov001 --subsection actor_animation --functions
```

`PROGRESS.md` contains system, overlay and subsection percentages, with the
owning subsection beside every matched function. `build/progress.json` contains
all 10,359 identified functions, including unmatched functions, nested under
their single owner. The filtered command lists both matched and pending members.

## Accounting

Matching percentage is `verified C/C++ bytes / analysed code bytes`. It is
byte-weighted at every level, never an average of child percentages. The
denominator comes from the original delink code ranges and function sizes,
not from manually supplied catalog totals. Function spans must be disjoint
and contained in those ranges. Code gaps outside function spans are retained
as explicit ranges and bytes in the unclassified subsection.

Duplicate system/module ownership, duplicate subsection IDs, duplicate function
ownership, unknown symbols, overlapping functions and functions outside code
ranges fail validation. Every original module must appear once in the catalog.
All subsection totals add up to their module; module totals add up to their
system; system totals retain the original 1,768,220 analysed ARM9 bytes.

A nonempty subsection is complete only when all of its assigned code bytes
match. An empty subsection is not complete. This is completion of the current
reviewed scope: later evidence may move additional functions into that scope.
Understanding a gameplay role and matching its compiled bytes remain separate
measures. ARM7 has an unknown denominator and no function inventory; it is
displayed explicitly and excluded from the analysed ARM9 percentage.

ROM-free conservation tests run with `python tools/khrecoded.py check --profile ci`.
The full check additionally verifies the ROM identity, exact baseline rebuild
and fresh compilation of every registered match.
