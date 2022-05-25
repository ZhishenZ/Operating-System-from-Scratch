.section .text
.global start


start:
    mrs x0, mpidr_el1//Move to ARM register from system coprocessor register.
                     //read the system register. The register is the Multiprocessor Affinity Register
    // MPIDR_EL n The processor and cluster IDs, in multi-core or cluster systems.
    // 0x is the destination register 

    // The lower 2 bits of mpidr_el1 holds the information abou the CPU, 
    // mask off the other bits using and instructions:
    and x0,x0,#3
    // 3 is equal to 0b11 and this will mask the low two bits of the 0x
    // and the store the result of 0x and #3 in the 0x register

    // if the value is 0, this is exactly the CPU we are looking for, 
    // otherwise we will put it into sleep. 
    cmp x0,#0
    beq kernel_entry// beq is connected to cmp 

end:
    b end //infinite loop, b means "jump to"

kernel_entry:
    mov sp, #0x80000// move the stack pointer to 80 000, our code will be loaded to this address
                  // Stack grows downwards. When we push a value into stack, the stack pointer will point to 8 bytes below 80000  
                  //
                  //|--------------------------------|
                  //|                                |
                  //|                                |
                  //|            BOOT CODE           |
                  //|                                |
                  //|--------------------------------|      0x80000
                  //|                                |<=sp (0x7fff8)
                  //|                                |
                  //|              STACK             |
                  //|                                |
                  //|                                |
                  //|--------------------------------|      0x00000
    bl KMain// then we branch to kernel main. 
    b end//    AFTER WE RETURN from the main function, we will branch to the end

    // at the end of the file must have a new line
    