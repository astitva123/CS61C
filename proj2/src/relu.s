.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
# 	a0 (int*) is the pointer to the array
#	a1 (int)  is the # of elements in the array
# Returns:
#	None
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 78.
# ==============================================================================
relu:
    # Prologue
    
    addi t0, t0, 1
    blt a1, t0, loop_end
    
    mv t0, a0
    mv t1, zero

loop_start:

    slli t2, t1, 2
    add t0, t0, t2
    add t2, 0(t0), zero
    bge t2, zero, loop_continue
    sw zero, 0(t0)

loop_continue:  

    addi t1, t1, 1
    blt t1, a1, loop_start

loop_end:


    # Epilogue

    
	ret
