# Three session state words

`ClearSessionStateWords` (EU overlay001, 0x02064dc8, Thumb) writes zero to
exactly three consecutive 32-bit words of the object pointed to by
`data_ov001_020a0480`: offsets **0x27a8, 0x27ac and 0x27b0**. The prior name
`ClearFieldCounters` and the shared US view named `FieldCounters` are historical
labels. No increment, elapsed-time or count contract has been established for
these words. The EU implementation uses a local partial view with neutral names.
The opaque prefixes are native DS offsets, not a recovered full session layout.

`RefreshSessionSelections` resets the same words after restoring selection
records. The item picker, slot menu and item screen test words from this range
against zero; other handlers compare a word to the literal state value 10.
These observations establish stored states, but do not identify what each
nonzero value means. Zero is not labeled ready, idle or completed. The three-word
reset does not prove a total element count for every consumer of nearby storage.

## Entrypoints and forwarding

| EU address | Current name | Observed behavior |
|---|---|---|
| ov001:02064dc8 | `ClearSessionStateWords` | Three stores of zero; no allocation or release. |
| ov001:02065f20 | `ScriptCmd_ClearSessionStateWords` | No local operand decoding; calls the reset, returns integer 1. Command-table word 178. |
| ov075:020ce818 | `ClearItemPickerSessionStateWordsThunk` | Thumb tail call through literal 0x02064dc9. |
| ov076:020ca628 | `ClearSlotMenuSessionStateWordsThunk` | Same target and unchanged argument registers. |
| ov077:020c765c | `ClearItemScreenSessionStateWordsThunk` | Same target and unchanged argument registers. |

The three eight-byte thunks are shared-source wrappers whose legacy file names
mention PXI. Their ROM literals and branch instructions target this game session
reset; they perform no FIFO initialization. Reward dispatchers call them for
specific item codes and discard the return register. Their inherited pointer
return declarations are unresolved decompiler artifacts: no returned pointer or
ownership transfer is established. A port should expose the proven reset side
effect without treating the residual register as a result. The script command's
explicit 1 is independent of that residual register; the full VM status protocol
is not inferred here.

## Evidence and reproduction

The native reset is in `src/overlays/ov001/calls/ClearSessionStateWords.c`.
The reference body is
`../src/ov001/field_manager/ClearFieldCounters_02064dc8.c`; the EU wrapper for
`RefreshSessionSelections` includes the shared implementation that writes the
same offsets. The script command table and the three reward dispatchers retain
their original ordering and calls. The ROM-derived index confirms the thunk
literal targets, including the Thumb bit; identical RAM addresses in other
overlays are not interchangeable symbols.

From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/ClearSessionStateWords.c ClearSessionStateWords --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_ClearSessionStateWords.c ScriptCmd_ClearSessionStateWords --thumb
python tools/verify_idx.py src/overlays/ov075/calls/ClearItemPickerSessionStateWordsThunk.c ClearItemPickerSessionStateWordsThunk --thumb
python tools/verify_idx.py src/overlays/ov076/calls/ClearSlotMenuSessionStateWordsThunk.c ClearSlotMenuSessionStateWordsThunk --thumb
python tools/verify_idx.py src/overlays/ov077/calls/ClearItemScreenSessionStateWordsThunk.c ClearItemScreenSessionStateWordsThunk --thumb
bash tools/gate.sh
```

Expected sizes are 32, 10, 8, 8 and 8 bytes. The cleanup also compares affected
production functions before and after, including relocation targets and addends,
and requires all 108 linked modules to remain byte-exact.
