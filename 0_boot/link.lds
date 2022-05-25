ENTRY(start) /*start was defined in boot.s, so the linkerscript can find it*/
SECTIONS
{
    . = 0x80000;/*set the curent location to 80000 and then load the .text section in this address*/

    .text  :  {
        *(.text) /*meaning that the .text sections in the object file
                  **  boot.o and main.o are added in text segment of the output file.
                  **  When we link the object file, the boot.o file should be linked first
                  **  Otherwise boot section could end up in the middle of the ouput file.
                  */
    }

    .rodata  :  {
        *(.rodata)
    }

    . = ALIGN(16);   /*data segment align to 16 byte boundary, and ALIGN HAS TO END WITH A ";“ */
    
    .data  :  {
        *(.data)
    }

    /*The ‘bss’ contains all the uninitalized data. (better save place)*/
    .bss : {
        *(.bss)
    }
}