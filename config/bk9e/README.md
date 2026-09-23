# BK9E `dsd` analysis metadata

Generated from the verified `BK9E` revision 0 ROM with `dsd` 0.12.1. These
plain-text files describe ARM9 main, ITCM, DTCM, and all 105 ARM9 overlays:
symbol candidates, sections, relocations, and delink boundaries. They are
analysis metadata, not reconstructed source code or game binary content.

`dsd init` warned about several calls into the middle of inferred functions
and six unresolved cross-overlay relocations. The generated boundaries are
useful starting hypotheses; they are not proof of complete function discovery
or a source build. ARM7 is extracted locally, but `dsd` did not generate an
ARM7 function configuration in this run.

Do not rerun `dsd init` over reviewed edits without preserving the existing
metadata. The normal `setup` command creates this folder only if absent.

