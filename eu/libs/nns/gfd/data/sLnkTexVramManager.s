    .section .bss
    .balign 4

    .global sLnkTexVramManager
    .type sLnkTexVramManager, %object
sLnkTexVramManager:
    .space 0x1c
    .size sLnkTexVramManager, . - sLnkTexVramManager

    .global sLnkTexUsedList
    .equ sLnkTexUsedList, 0x0205a8e4

    .global sLnkTexCompressedUsedList
    .equ sLnkTexCompressedUsedList, 0x0205a8e8

    .global sLnkTexBlockPool
    .equ sLnkTexBlockPool, 0x0205a8ec
