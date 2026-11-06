# Wireless reward result and native interface

GrantRewardEntry and PickWeightedReward return exactly 0 or 1 on normal return.
This follows from the original EU instructions, independently of their callers'
zero comparisons. Return representation, functional inputs and original C formal
arity are separate evidence questions.

## Canonical result

At ov015:02078454 GrantRewardEntry initializes R5 to 0. Its only later
non-restoring write to that register is MOVNE R5,#1 at 02078524. Every normal path
reaches MOV R0,R5 at 02078548, after the optional final SetContextCommandFlag call.
Its epilogue preserves R0. The result is a canonical 32-bit Boolean rather than a
residual pointer or the raw return of its last callee.

| Native path | Predicate/result |
|---|---|
| Signed type 0, ID 0..127 | AddRecordItem receives the initialized temporary record; its zero/nonzero result becomes 0/1. |
| Signed type 0, other ID | AddRecordItem receives NULL for that record argument; its zero/nonzero result becomes 0/1. |
| Signed type 9, record already flagged | Result 0. |
| Signed type 9, record not flagged | The command's separate output word is normalized to 0/1. |
| Other signed type | Result 0. |

SetGlobalPackedBit's residual pointer and DispatchContextCommand's own return
are discarded by GrantRewardEntry. The latter's separate output word controls
the predicate. SetContextCommandFlag may leave 1 in R0, but the final MOV R0,R5
replaces it. Preserve these distinctions when recovering source return types.

PickWeightedReward calls GrantRewardEntry at 02078420. Its remaining instructions
only adjust SP and restore registers excluding R0; it forwards the same result.
A 32-bit int-based BOOL represents this native return. A pointer/status-word
interpretation does not describe the proved result.

## Inputs and deliberately transmitted peer word

UpdatePanelMinigame has two known direct selector calls:

| Call address | R0 | R1 | R2 | Return use |
|---|---|---|---|---|
| ov015:020771bc | board+0x6c | signed byte at board+0x54 | board+0x78, explicitly formed at 020771b8 | Zero sets mask 0x100. |
| ov015:020772e0 | board+0x78 | signed byte at board+0x52 | board+0x6c, explicitly formed at 020772dc | Zero sets mask 0x200. |

The selector overwrites incoming R2 with an aggregate LDM at relative +0x18
(02078324), without first reading it. Two functional input values are proved.
The callers nevertheless calculate the peer descriptor address immediately
before BL; this word is intentional call preparation, not an unrelated leftover.
Its semantic purpose and whether it was an unused original formal remain open.

Do not infer original formal arity from a dead incoming register, introduce a
third/variadic formal solely for code generation, or remove caller preparation
without validating the resulting native behavior and bytes.

## Native source views and the port boundary

The current selector definition is void/two-formal while its caller declares
BOOL/three-formal. Grant's anonymous union record, WirelessRewardEntry and the
caller's PanelDescriptor also have distinct C type views despite their common
native size. Those declarations are evidence to reconcile, not a finalized host
header. A return-only edit would leave the complete interface inconsistent.

A later source-interface cleanup must reconcile the actual record layouts and
caller/callee declarations together. The native result is now proved; formal
arity and source compatibility are not closed by this document. Table storage
contracts remain separate in [WIRELESS_TABLES_STATE_STORAGE.md](WIRELESS_TABLES_STATE_STORAGE.md).

Active sources are `src/overlays/ov015/calls/GrantRewardEntry.c`,
`src/overlays/ov015/calls/PickWeightedReward.c` and
`src/overlays/ov015/calls/UpdatePanelMinigame.c`. All are ARM: GrantRewardEntry
uses dsi/1.1; the selector and caller use dsi/1.3p1. No source, prototype, flags or
compiler selection is changed by this audit.

## Evidence scope

Original BK9P overlays 015 and 002 were located through the NDS overlay table/FAT
and decompressed; both complete results agree with the extracted modules.
Relevant main ARM9 callee windows were also compared to the original NDS.
The review traces every GrantRewardEntry return branch, the selector epilogue,
the known direct callers and 32 known DATA/header consumers. It does not exclude
additional indirect calls. All native sources and previously validated module
hashes remain unchanged.
