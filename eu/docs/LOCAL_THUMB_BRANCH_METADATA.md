# Local Thumb BL transfers and linker relocations

The native CFG records a Thumb BL edge even when its destination is a local label inside the same function. The compiler can resolve this PC-relative transfer without an ELF relocation. Treating it as an external reference made two byte-identical C functions fail the standalone relocation check.

The existing ROM/config index builder now classifies such a transfer as ordinary instruction bytes only after validating its full original target. The rule requires a Thumb source, Thumb BL kind, one explicit destination bank equal to the source bank, a Thumb label strictly inside the function and no function entrypoint at that address. Recursive calls, other functions, different or ambiguous banks, interworking BLX and address loads remain relocations. The native CFG records are retained unchanged.

The exact native impact is bounded:

| Function | Native start / size | Previously external offsets | Local target |
|---|---|---|---|
| ApplyHitToEnemyGroup | ov001:0209591c / 2352 bytes | 212 | ov001:0209623a |
| EnterActorState | ov052, 2792 bytes | 58, 200, 258, 308, 358, 632, 688 | ov052:020cde20 |

Apply's BL has bytes `00 f0 23 fc` and reaches its own local return path. Its displacement exceeds a short Thumb B's range. All eight instruction words agree with both the original ROM and existing complete C objects. No label is promoted to a function, and no new helper or parameter is introduced.

Only the explicit existing native-refresh command updates the two historical index entries. Their unmasked ROM bytes, mode, size, bank and every other field remain exact. The remaining 71 and 66 relocation records respectively retain their offsets and targets. Other index entries keep the existing conservative merge policy.

The official verifier is unchanged. Removing these eight external-relocation masks makes all four bytes of each transfer part of ordinary exact comparison. Strict replays reject 32 individual byte mutations; source controls at their actual compilation paths reproduce the old inventory discrepancy without granting a baseline exception.

## Reproduction

Run from `eu/`:

```sh
python tools/test_rebuild_index.py
python tools/rebuild_index.py --write --refresh-native-relocs ApplyHitToEnemyGroup EnterActorState
python tools/verify_idx.py src/overlays/ov001/calls/ApplyHitToEnemyGroup.c ApplyHitToEnemyGroup --thumb
python tools/verify_idx.py src/overlays/ov052/calls/EnterActorState.c EnterActorState --thumb
bash tools/gate.sh
```

All 48 generator tests pass, including rejection/retention cases for incorrect opcodes and targets, recursion, other functions, boundaries, ambiguous banks, loads and BLX. All 30 affected and regression function checks pass. All 33 complete objects retain allocated bytes/alignment, symbol layouts and relocation records after the permitted identifier renames. A fresh gate preserves every hash across 108 native modules.

- [Existing builder](../tools/rebuild_index.py) and [regression tests](../tools/test_rebuild_index.py).
- [ApplyHitToEnemyGroup](../src/overlays/ov001/calls/ApplyHitToEnemyGroup.c).
- [EnterActorState](../src/overlays/ov052/calls/EnterActorState.c).
- [Earlier native-metadata policy](NATIVE_RELOCATION_METADATA.md).

This corrects the index's distinction between local control flow and linker imports. C bodies, compiler flags, native instructions and the official comparison policy are unchanged.
