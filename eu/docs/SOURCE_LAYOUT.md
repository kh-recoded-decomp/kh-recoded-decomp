# Finding EU code and understanding the source tree

Start with the system index in [README.md](README.md). The current source tree
preserves native module identities and the shared US/EU implementation bodies.
This page explains which paths are authoritative and how to follow a function
without knowing its address.

## Current layout

Paths in this table are relative to the repository root.

| Location | Purpose |
|---|---|
| `src/arm9/`, `src/ovNNN/` | Shared/reference-region implementation bodies. EU wrappers select the correct names through aliases before including these files. Read the wrapper and its included body together. |
| `eu/src/calls/`, `eu/src/auto/` | EU main/ITCM function entrypoints and wrappers. The module, ARM/Thumb mode and native extent come from configuration. DTCM currently contains DATA/BSS rather than function symbols. |
| `eu/src/overlays/ovNNN/{calls,auto}/` | EU function entrypoints for native FS overlay ID NNN. A function's descriptive filename is the main lookup key. |
| `eu/src/ovNNN/data/`, `eu/src/overlays/ovNNN/data/` | Reconstructed overlay storage. Both layouts are active in the current project; use the module's delink ranges to find the owning source. |
| `eu/src/data/`, `eu/src/dtcm/` | Main/autoload DATA sources; configuration establishes their native placement. |
| `eu/libs/` | Historical SDK/middleware source grouping. Consult the function's evidence and progress category to determine its actual role. |
| `eu/src/collision/`, other shared native headers | Recovered game layouts and contracts used by the EU sources. Their DS pointer widths and ABI checks remain intentional. |
| `eu/nitro/`, `eu/nnsys/` | Native SDK type declarations used by the EU compiler. |
| `eu/config/arm9/` | Main module symbols, delink ranges, relocations and build configuration. `itcm/`, `dtcm/` and `overlays/ovNNN/` retain native module identities. |
| `eu/portable/` | Separately checked portable library counterparts. Their behavior tests and progress accounting are distinct from matched native C. |
| `eu/docs/` | Ownership, layouts, interfaces, evidence and remaining uncertainties, grouped by the index rather than by address. |
| `eu/analysis/legacy_data/` | Proven superseded DATA copies, preserved with their active replacements and archival evidence. These files are outside the compiled source tree. |
| `eu/build/`, `eu/dsd_extract/` | Generated reports/objects and extracted reference modules. An existing object can outlive its source's active build entry. |

`calls` and `auto` are historical matching-workflow categories. An `auto`
directory can contain completed, named C; its presence says nothing about
whether the code is understood or portable. Similarly, an address in a DATA
filename often identifies an aggregate file containing several objects.

## Follow the active implementation

1. Find the descriptive symbol in `eu/config/arm9/**/symbols.txt`. Record its
   module and address; for functions, also record mode and native extent.
   DATA labels with `kind:data(any)` need their extent established from the
   actual declaration/object and owning range. An interior alias does not
   define a separate allocation. Overlay bank plus address identifies the
   object; another overlay can reuse exactly the same RAM address.
2. Find the source owning that native range in the same module's `delinks.txt`.
   For DATA, check the complete symbol extent against the claimed section.
   A similarly named file elsewhere is not sufficient ownership evidence.
3. Open the EU source. If it includes a repository-root `src/...` body, apply
   its aliases when reading that body. A shared filename can retain a US
   address suffix while the wrapper supplies a different EU identity.
4. Read the appropriate contract from the system index, its actual callers and its
   constructors/writers. Partial native views and erased prototypes require
   their documented ABI interpretation before a host port can use them.

For example, [ApplySubBgScroll.c](../src/overlays/ov025/calls/ApplySubBgScroll.c)
includes the shared implementation after binding the EU globals and symbol.
[SetWirelessReceivedCardCallback.c](../libs/nns/snd/calls/SetWirelessReceivedCardCallback.c)
is game connection work despite its inherited sound-library directory and
private type spelling; its [wireless contract](PANEL_WIRELESS_CALLBACK_CONTRACTS.md)
establishes the owner. Directory placement alone does not certify library
semantics.

## Organization decision and the Days reference

[khdays-decomp's layout](https://github.com/Yokimitsuro/khdays-decomp/blob/93535afd7ca082f3d856bbf1cadae65be16d44ba/docs/layout.md)
groups overlays by their demonstrated role and keeps their `ovNNN` IDs. It is
a useful model for browsing systems and collecting proven shared types.
The reference was reviewed at commit
`93535afd7ca082f3d856bbf1cadae65be16d44ba`.

For this shared Re:coded repository, the compiled EU paths currently stay
stable. The system index supplies the functional grouping, while native
overlay IDs, shared-body includes and per-file compiler selections keep their
existing bindings. A wholesale directory move would need to update those
bindings and both regions' callers; it would not establish additional type or
ownership evidence. The proven inactive ov014 copy has instead been separated
into [the legacy archive](../analysis/legacy_data/README.md), with its active
typed table identified explicitly.

Days types and names are useful references when the actual Re:coded body,
callers, storage and ABI agree. Identical short getters, similar addresses or
matching private type names alone do not prove a shared gameplay role.

## Validating a future source move

Preserve the original source and compiled object first. Update the owning
delink path, include references and per-file compiler/flag selections together.
Compile controls from their actual configured paths: a backup path can select
different compiler settings and is not an equivalent control automatically.

Check affected functions and DATA layouts, relocation targets/types/addends,
and every complete linked module with the existing tools. Keep library source
and documentation receipts current through their official verifiers. The
known [standalone relocation baseline](DATA_NATIVE_RELOCATION_BASELINE.md)
remains explicit alongside the full 108-module gate.
