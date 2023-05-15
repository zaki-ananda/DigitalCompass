#define __SFR_OFFSET 0x00
#include "avr/io.h"
#include "registerMap.h"

delay1s:
.equ Rloop, Rtemp1

  LDI Rloop, 80
  delay1s_loop:         ;1 second loop delay
    LDI Rcontrol, 61
    OUT TCNT0, Rcontrol ;initialize timer0 with count=0

    LDI Rcontrol, 0b00000101 
    OUT TCCR0B, Rcontrol

    CALL delay_waitTOV

    CLR Rcontrol
    OUT TCCR0B, Rcontrol ;stop timer0

    LDI Rcontrol, (1<<TOV0)
    OUT TIFR0, Rcontrol ;clear OCF0 flag

    DEC Rloop
    BREQ delay1s_exitloop
    JMP delay1s_loop
  delay1s_exitloop:
RET

delay1ms:               ;1 ms loop delay
  .equ Rloop, Rtemp1

  LDI Rloop, 80
  delay1ms_loop: 
    LDI Rcontrol, 61
    OUT TCNT0, Rcontrol ;initialize timer0 with count=0

    LDI Rcontrol, 0b0000010
    OUT TCCR0B, Rcontrol

    CALL delay_waitTOV

    CLR Rcontrol
    OUT TCCR0B, Rcontrol ;stop timer0

    LDI Rcontrol, (1<<TOV0)
    OUT TIFR0, Rcontrol ;clear OCF0 flag

    DEC Rloop
    BREQ delay1ms_exitloop
    JMP delay1ms_loop
  delay1ms_exitloop:
RET

delay100ms:             ;100ms loop delay
  .equ Rloop, Rtemp1

  LDI Rloop, 8
  delay100ms_loop: 
    LDI Rcontrol, 61
    OUT TCNT0, Rcontrol ;initialize timer0 with count=0

    LDI Rcontrol, 0b0000101
    OUT TCCR0B, Rcontrol

    CALL delay_waitTOV

    CLR Rcontrol
    OUT TCCR0B, Rcontrol ;stop timer0

    LDI Rcontrol, (1<<TOV0)
    OUT TIFR0, Rcontrol ;clear OCF0 flag

    DEC Rloop
    BREQ delay100ms_exitloop
    JMP delay100ms_loop
  delay100ms_exitloop:
RET

delay_waitTOV:
  IN Rstatus, TIFR0 ;get TIFR0 byte & check
  SBRS Rstatus, TOV0 ;if OCF0=1, skip next instruction
  RJMP delay_waitTOV ;else, loop back & check OCF0 flag
RET
