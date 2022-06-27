.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# =================================================================
argmax:

    # Prologue

    addi t0, zero, 1
    blt a1, t0, loop_end    

loop_start:

    mv t0, zero     
    mv t1, zero    

loop_continue:

    beq t0, a1, loop_end   

    slli t2, t0, 2         
    add t2, a0, t2      

    lw t2, 0(t2)         
    lw t3, 0(t1)           

    bge t3, t2, no_update 

    mv t1, t0

no_update:

    addi t0, t0, 1
    j loop_continue

loop_end:

    mv a0, t1
    

    # Epilogue


    ret
