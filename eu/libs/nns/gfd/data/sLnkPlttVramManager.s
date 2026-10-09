    .section .bss
    .balign 4

    .global sLnkPlttVramManager
    .type sLnkPlttVramManager, %object
sLnkPlttVramManager:
    .space 0x14
    .size sLnkPlttVramManager, . - sLnkPlttVramManager

    .global sLnkPlttVramManagerListHead
    .equ sLnkPlttVramManagerListHead, 0x0205a900

    .global sLnkPlttVramBlockPoolList
    .equ sLnkPlttVramBlockPoolList, 0x0205a904
