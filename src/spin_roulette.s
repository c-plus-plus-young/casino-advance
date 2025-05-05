    .section .text
    .align 2
    .global spin_roulette
    .type spin_roulette, %function

// int spin_roulette(int dividend, int divisor);
spin_roulette:
    PUSH    {lr}

    // r0 = dividend
    // r1 = divisor

mod_loop:
    CMP     r0, r1          // while (dividend >= divisor)
    BLT     done            // end if dividend < divisor
    SUB     r0, r0, r1      // dividend -= divisor
    B       mod_loop

done:
    POP     {lr}
    BX      lr              // return remainder
