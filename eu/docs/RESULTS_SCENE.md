# EU results-scene initialization

`InitResultsScene` (formerly `func_ov034_020ba400`) prepares the results scene and returns the
`UpdateResultsScreen` handler. Its implementation is in
`src/overlays/ov034/calls/InitResultsScene.c`.
The entry arguments supply the stage, world, area, score, shop section and
session kind. The task already owns the work allocation; the legacy symbol
`NNSi_FndGetCurrentRootHeap` used here retrieves that work pointer.

The initializer clears the work record, copies the entry arguments, loads
its dependent overlays and initializes the tile table and input repeat state.
It obtains the results parameter buffer, sets up the selected stage and
rewards, then builds the stage-specific shop entries. `bonusStage`, the shop
scan cursor and the immutable `firstStage` bound represent different values.
Keeping those names separate makes the scan and its bounds explicit.

## State ownership and target layout

The initializer owns these two real four-byte BSS objects:

| Address | C symbol | Meaning |
|---|---|---|
| `0x020c0fa0` | `data_ov034_020c0fa0` | `ResultsParams *`, the session parameter buffer |
| `0x020c0fa4` | `data_ov034_020c0fa4` | `ResultsWork *`, the current task work |

They replace the previous eight-byte raw reservation. They do not add another
allocation. The remaining 152 BSS bytes are defined by
`src/overlays/ov034/data/bss/Bss_ov034_020c0fa8.c`; the combined range is still
exactly `0x020c0fa0..0x020c1040`.

Important recovered work layout contracts are checked in the C source:

| Item | EU layout |
|---|---|
| `ResultsWork` size | `0x6d98` |
| Tile table | `+0x64d8`, size `0x1c` |
| Task and fade controls | `+0x64f4`, `+0x64f8`, `+0x64fc` |
| Input repeat record | `+0x6b94`, size `0x1a` |
| `ResultsParams` size | `0x90` |
| One icon cell | 12 bytes |

The tile setup copies four IDs and passes a descriptor with count 4 and
width/height 32 to `InitTileTableFrom`. Its reserved word is initialized to
zero. The destination table is the real subobject of `ResultsWork`.

## Reproducible code generation

The EU target uses ARM instructions with stock MWCC DSI 1.1, not Thumb.
The compiler map selects `dsi/1.1`; the ordinary project flags remain in use.
Two source directives describe the required code-generation constraints:

- `defer_codegen on` delays emission until the translation unit is known.
  MWCC can then use a common address base for the adjacent BSS objects while
  preserving their separate alias identities. This is the source equivalent
  of the compiler's documented `-ipa file` mode. `__option(defer_codegen)`
  checks that the selected compiler actually enables it.
- `opt_lifetimes off` preserves the distinct bonus-stage and scan-cursor
  lifetimes used by this EU routine.

Both directives are guarded by `__MWERKS__`. The pointer definitions are in
reverse declaration order because that is the emission order of this
compiler. Their offsets and combined size are verified, rather than forced
with linker aliases or extra storage.

The only residual unlinked objdiff rows are the absolute overlay IDs 27 and
24. The official verifier resolves them to the ROM values; the linked module
check must include those resolved words as well.

## Completion flag accesses

In the mode-zero branch, the ROM clears bit 3 of the session halfword at
`data_0206085c + 6`, stores it, reloads the halfword, then clears and stores
bit 4. The stores occur at function offsets `+0x244` and `+0x250`, with the
reload at `+0x248`.

The explicit volatile access for `bonus` preserves that observed two-step
memory update. Replacing it with an ordinary field assignment causes MWCC
to remove the first store and the reload, shortening the function by 12
bytes including the changed conditional sequence. Original source qualifiers
and asynchronous sharing have not been recovered; the cast records the
actual access sequence required by the EU reconstruction.

## Guidance for a later port

Treat the two pointers as logical scene state. Existing target helpers also
use paired views of this BSS range. A host port should centralize the state
and update those helper views consistently; independently declared C globals
are not guaranteed to remain adjacent on another toolchain.

The byte offsets, pointer sizes and bitfield allocation describe the DS ABI.
Keep the named fields and stage/shop logic when adapting the code, and replace
task work access, session buffers, overlay loading and graphics initialization
with the host implementations. Review the two-step flag update against the
port's own scheduling and state ownership before simplifying it.

## Validation

Run the existing checks from the EU directory:

```sh
python tools/verify_idx.py src/overlays/ov034/calls/InitResultsScene.c InitResultsScene
bash tools/gate.sh
```

The official unit check currently matches all 1972 bytes and 40 relocations,
including the eight-byte BSS layout. The fresh linked-module gate passes **108/108**. The built initializer equals
the ROM index across all 1972 linked bytes. An independent audit also verifies
the two pointer slots, both remaining arrays and the full 160-byte BSS range.
