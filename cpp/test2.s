.section sec1
    .global iPhone
    .extern samsung, Thirteen
    .word iPhone, Thirteen, Pro
    .skip 4
    .word 42
    .skip 0x2

.section sec2
    .equ iPhone, 0xD
    .equ a, 0
    .equ b, 2
    .equ c, 0x2
    iret
Pro:
    call *[r1 + Pro]
    jmp *[r1 + 13]
    jeq *[r2]
    jne *r2
    jgt *iPhone
    jmp *0x2233
    jmp %samsung
    jmp 0x3322
    jmp c
    push r1 
    pop r0
    shl r5, r2
    shr r5, r2
.section sec3
    ldr r0, iPhone
    str r0, Pro
    str r0, $Pro
    str r0, 0x1122
    str r0, $0x1122
    str r0, $42
    str r0, %Pro
    str r0, r3
    str r0, [r3]
    str r0, [r3 + 42]
    str r0, [r3 + Pro]
    ret
.end