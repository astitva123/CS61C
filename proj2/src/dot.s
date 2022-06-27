.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 (int*) is the pointer to the start of v0
#   a1 (int*) is the pointer to the start of v1
#   a2 (int)  is the length of the vectors
#   a3 (int)  is the stride of v0
#   a4 (int)  is the stride of v1
# Returns:
#   a0 (int)  is the dot product of v0 and v1
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 75.
# - If the stride of either vector is less than 1,
#   this function terminates the program with error code 76.
# =======================================================
dot:

    # Prologue
    addi t0, zero, 1
    blt a2, t0, loop_end

    # t0 will store result
    mv t0, zero
    mv t5, zero

loop_start:

    bge t5, a2, loop_end

    mul t1, t5, a3
    mul t2, t5, a4

    slli t3, t1, 2
    slli t4, t2, 2

    add t3, a0, t3
    add t4, a1, t4

    lw t3, 0(t3)
    lw t4, 0(t4)

    mul t3, t3, t4
    add t0, t0, t3

    addi t5, t5, 1

    j loop_start

loop_end:

    mv a0, t0

    # Epilogue

    
    ret
