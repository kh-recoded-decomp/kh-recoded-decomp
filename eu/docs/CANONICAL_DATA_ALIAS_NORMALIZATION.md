# Canonical DATA aliases and active-context storage

Three duplicate numeric configuration labels already had canonical C/ELF
owners at the same module/address. Their configuration aliases are removed;
no variable was added, resized or moved.

| Native identity | Existing C/ELF owner | Bytes |
|---|---|---:|
| main:02056ae0 | gTextTagColors | 8 |
| ov021:020b5620 | gActiveFieldButtonEntryIndex | 4 |
| ov021:020b56dc | gScriptHandlerTable | 128 |

Each owner exports one allocation. Twelve EU wrappers contain the token
`data_ov021_020b5620` only on the left of a macro binding a shared-region
symbol to `gEffectResourceContainersLoaded` at another EU address. Those
macro left sides and bindings remain unchanged. Equal spelling in a shared
source does not establish an owning-bank reference to EU 020b5620.

## Active definitions

- [Text tag colors](../src/data/bss/Bss_main_02056ae0.c).
- [Field-button entry index](../src/overlays/ov021/data/bss/Bss_ov021_020b5620.c).
- [Script handler table](../src/overlays/ov021/data/bss/Bss_ov021_020b56d0.c).

## Active field-context storage and view

The remaining former numeric definition at ov021:020b56c4 is now
`gActiveFieldContextStorage`. It owns the same three-u32, 12-byte BSS range
[0x020b56c4, 0x020b56d0). The existing `gActiveFieldContext` identity remains a
typed view of that same native address. Symbol discovery retains its existing
`LINKER_SYMBOL_SCAN` facade; the facade is excluded from the native C build
and creates no second allocation. Only the old backing name is changed. No
new storage or alias is introduced.

[RunScriptThread](../src/overlays/ov021/calls/RunScriptThread.c) uses the backing
words and its typed event/link/player context view through distinct external
identifiers. An attempted coalescing of those identifiers changed compiler
alias knowledge and lost an external reference: the function shrank from
348 bytes with 13 relocation records to 340 bytes with 12. Official byte
verification rejected that candidate with the same compiler profile and
unchanged verifier.

The accepted spelling preserves the original storage/view distinction and
RunScriptThread's 348 bytes/13 relocations. The two names resolve to the same
native address. They do not represent two independent objects or permission
to allocate two contexts in a host port. A portable interface should model
one backing region and its views explicitly, then validate any alias/type
cleanup as its own change.

The [physical definition](../src/overlays/ov021/data/bss/Bss_ov021_020b56c0.c)
retains the three-word array and its neighboring `gActiveSubModeState` without
layout changes. EU shared-source macro left sides/includes, types and selected
compiler profiles are preserved. This is the final storage naming contract;
there is no pending fourth coalescing operation.

## Validation

The earlier three canonical-configuration removals passed 14 official
function checks and 21 complete-object comparisons, including their BSS
owners, with all 108 module hashes unchanged.

The final backing-storage naming and [ten interior alias normalizations](INTERIOR_DATA_ALIAS_NORMALIZATION.md)
pass all 87 affected official function checks. All 94 complete production
objects retain allocated section bytes/alignment, symbol offsets/sizes, and
relocation target values/types/addends. A fresh linked gate passes 108/108
native modules with every hash unchanged. The rejected coalescing control
remains part of the evidence and is not treated as an accepted cleanup.

The [retained-label ledger](EU_PENDING_DATA_LABELS.md) records 835 original
naming assignments, this one backing-storage name, three earlier canonical
closures, ten retired interior aliases and the 92 remaining numeric identities.
Metadata aliases are not extra allocations.
