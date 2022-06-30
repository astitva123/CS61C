.globl read_matrix

.data
file_path: .asciiz "../inputs/test_read_matrix/test_input.bin"

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
# - If malloc returns an error,
#   this function terminates the program with error code 88.
# - If you receive an fopen error or eof, 
#   this function terminates the program with error code 90.
# - If you receive an fread error or eof,
#   this function terminates the program with error code 91.
# - If you receive an fclose error or eof,
#   this function terminates the program with error code 92.
# ==============================================================================
read_matrix:

    # Prologue

    addi sp, sp, -28
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    sw s5, 20(sp)
    sw ra, 24(sp)

    la a0, file_path

    mv s0, a0
    mv s1, a1
    mv s2, a2

    # opening file

    mv a1, s0
    li a2, 3

    jal ra fopen

    li t0, -1
    bne a0, t0, no_fopen_error
    li a1, 90
    jal exit2

no_fopen_error:

    # s4 stores file reference
    mv s4, a0

    # reading # rows 

    mv a1, s4
    mv a2, s1
    li a3, 4 
    jal fread

    # reading # cols

    mv a1, s4
    mv a2, s2
    li a3, 4
    jal fread

    # s3 will store pointer to result matrix

    lw t0, 0(s1)
    lw t1, 0(s2)
    mul s3, t0, t1
    slli s3, s3, 2

    mv a0, s3
    jal malloc

    mv s3, a0

    # loop variable
    mv s5, zero

read_loop:

    lw t0, 0(s1)
    lw t1, 0(s2)
    mul t0, t0, t1
    bge s5, t0, read_loop_end

    slli t0, s5, 2
    add t0, s3, t0

    mv a1, s4
    mv a2, t0
    li a3, 4
    jal fread

    addi s5, s5, 1
    j read_loop

read_loop_end:

    mv a0, s3

    # Epilogue

    addi sp, sp, 28
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    lw s5, 20(sp)
    sw ra, 24(sp)

    ret
