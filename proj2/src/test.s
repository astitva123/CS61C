.globl test_file

.import "utils.s"

.data
file_path: .asciiz "./test.txt"

.text
test_file:

    la a1, file_path
    mv a2, zero

    jal fopen

    addi t0, zero, -1
    bne a0, t0, no_fopen_error

    li a1, 90
    jal exit2

no_fopen_error: 

    li a1, 0
    jal exit2


