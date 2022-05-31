// .gloabl to make this function avaliable to other files. 
.global delay 
.global out_word
.global in_word
// the delay function delays a period of time. 
delay:
    subs x0, x0, #1
    bne delay 
    // if it is non zero, we go back and continue doing the substraction until x0 is 0. 
    // the “bne” instruction only performs a jump if the zero (Z) flag is not set, i.e. when the result of the last math instruction (with an “s” appended) was not zero. 
    // The “beq” instruction is the opposite of that – it only performs a jump if the result was zero.

    ret // if it is zero, we simply return 



out_word:// store a word to the memory
    str w1, [x0] // we store the value in w1 to the memory location pointer by x0 
    ret          // because we want to store 4 byte data, we use 32 bit register w1 instead of using 64-bit register x1.  

in_word: // we load into 32-bit register w0 from the memory location addressed by x0
    ldr w0, [x0]// I think this line of code can be deleted? 
    ret // the return value is stored in x0, so when we return from the funciton, 
        // the data is saved in w0 as return value. 
