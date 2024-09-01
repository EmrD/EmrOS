; boot.asm

SECTION .multiboot
    dd 0x1BADB002            ; magic number
    dd 0x00                  ; flags
    dd -(0x1BADB002 + 0x00)  ; checksum

SECTION .text
    extern main               ; C kodundaki main fonksiyonuna çağrı yapmak için

    global _start             ; Başlangıç etiketi (kernel'in başlangıç noktası)
_start:
    call main                 ; main fonksiyonuna çağrı yapar

hlt_loop:                     ; sonsuz döngü
    hlt
    jmp hlt_loop
