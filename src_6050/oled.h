#define __SFR_OFFSET 0x00
#include "avr/io.h"
#include "registerMap.h"

OLED_init:
  CALL I2C_start

  LDI RdataOut, OLED_Addr_W
  CALL I2C_write
  
  LDI RdataOut, 0x00
  CALL I2C_write

  LDI RdataOut, 0xAE
  CALL I2C_write

  LDI RdataOut, 0xD5
  CALL I2C_write
  LDI RdataOut, 0x80
  CALL I2C_write

  LDI RdataOut, 0xA8
  CALL I2C_write
  LDI RdataOut, 31
  CALL I2C_write

  LDI RdataOut, 0xD3
  CALL I2C_write
  LDI RdataOut, 0x00
  CALL I2C_write

  LDI RdataOut, 0x40
  CALL I2C_write

  LDI RdataOut, 0x8D
  CALL I2C_write
  LDI RdataOut, 0x14
  CALL I2C_write

  LDI RdataOut, 0x20
  CALL I2C_write
  LDI RdataOut, 0x00
  CALL I2C_write

  LDI RdataOut, 0xA1
  CALL I2C_write
  LDI RdataOut, 0xC8
  CALL I2C_write

  LDI RdataOut, 0xDA
  CALL I2C_write
  LDI RdataOut, 0x02
  CALL I2C_write

  LDI RdataOut, 0x81
  CALL I2C_write
  LDI RdataOut, 0x80
  CALL I2C_write

  LDI RdataOut, 0xD9
  CALL I2C_write
  LDI RdataOut, 0x22
  CALL I2C_write

  LDI RdataOut, 0xDB
  CALL I2C_write
  LDI RdataOut, 0x20
  CALL I2C_write

  LDI RdataOut, 0xA4
  CALL I2C_write
  
  LDI RdataOut, 0xA6
  CALL I2C_write

  LDI RdataOut, 0x2E
  CALL I2C_write
  
  CALL I2C_stop

  CALL USART_null
RET

OLED_clearscreen:
	.equ ROLED_4bit, Rtemp5
  
  LDI Rtemp3, 30
  OLED_clearscreen_loopPage:
		CALL I2C_start;Sending write init command
		LDI RdataOut, OLED_Addr_W
		CALL I2C_write

		LDI RdataOut, 0x00      ;Send command
		CALL I2C_write

		LDI Rtemp1, 0xB0        ;Def page position
		ADD Rtemp1, ROLED_page  ;Add offset, if any
		MOV RdataOut, Rtemp1    ;Command: Send page position

		CALL I2C_write

		LDI RdataOut, 0x21      ;Command: Send col boundary
		CALL I2C_write

		MOV RdataOut, 0
		CALL I2C_write

		LDI RdataOut, 127
		CALL I2C_write
		CALL I2C_stop

		CALL delay1ms

		CALL I2C_start; Sending write data
		LDI RdataOut, OLED_Addr_W; Send OLED SLA+W
		CALL I2C_write

		LDI RdataOut, 0x40; Send GDDRAM data
		CALL I2C_write

		LDI Rtemp1, 126

		OLED_clearscreen_loopCol:
		  LDI RdataOut, 0
		  CALL I2C_write
		  DEC Rtemp1
		BRNE OLED_clearscreen_loopCol
		CALL I2C_stop
	
		DEC Rtemp3
	BRNE OLED_clearscreen_loopPage
  CALL USART_null
RET

OLED_displayOn:
  CALL I2C_start
    LDI RdataOut, OLED_Addr_W
    CALL I2C_write
    
    LDI RdataOut, 0x00
    CALL I2C_write

    LDI RdataOut, 0xAF
    CALL I2C_write
  CALL I2C_stop

  CALL USART_null
RET

OLED_displayOff:
  CALL I2C_start
    LDI RdataOut, OLED_Addr_W
    CALL I2C_write
    
    LDI RdataOut, 0x00
    CALL I2C_write

    LDI RdataOut, 0xAE
    CALL I2C_write
  CALL I2C_stop

  CALL USART_null
RET

OLED_writeByte:
  .equ ROLED_4bit, Rtemp5
  
  CALL I2C_start;Sending write init command
    LDI RdataOut, OLED_Addr_W
    CALL I2C_write

    LDI RdataOut, 0x00      ;Send command
    CALL I2C_write

    LDI Rtemp1, 0xB0        ;Def page position
    ADD Rtemp1, ROLED_page  ;Add offset, if any
    MOV RdataOut, Rtemp1    ;Command: Send page position

    CALL I2C_write

    LDI RdataOut, 0x21      ;Command: Send col boundary
    CALL I2C_write

    MOV RdataOut, ROLED_col
    CALL I2C_write

    LDI RdataOut, 127
    CALL I2C_write
  CALL I2C_stop

  CALL delay1ms
  
  CALL I2C_start; Sending write data
    LDI RdataOut, OLED_Addr_W; Send OLED SLA+W
    CALL I2C_write
  
    LDI RdataOut, 0x40; Send GDDRAM data
    CALL I2C_write
    
    OLED_writePageColumn_High:
      LDI R30, lo8(OLED_char)
      LDI R31, hi8(OLED_char)


      MOV ROLED_4bit, ROLED_buffer
      ANDI ROLED_4bit, 0xF0
      SWAP ROLED_4bit
      LDI Rtemp6, 6
      MUL ROLED_4bit, Rtemp6
      ADD R30, R0
      CLR R0
      ADC R31, R0
    CALL OLED_writeChar

    OLED_writePageColumn_Low:
      LDI R30, lo8(OLED_char)
      LDI R31, hi8(OLED_char)
      CLR R0

      MOV ROLED_4bit, ROLED_buffer
      ANDI ROLED_4bit, 0x0F
      LDI Rtemp6, 6
      MUL ROLED_4bit, Rtemp6
      ADD R30, R0
      CLR R0
      ADC R31, R0
    CALL OLED_writeChar

  CALL I2C_stop

  CALL USART_null
RET

OLED_writeChar:
  LDI Rtemp1, 6
  OLED_writeChar_loop:
    LPM RdataOut, Z+
    CALL I2C_write
    DEC Rtemp1
  BRNE OLED_writeChar_loop
RET

OLED_char:
  .byte 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E // 0
  .byte 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 // 1
  .byte 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 // 2
  .byte 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 // 3
  .byte 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 // 4
  .byte 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 // 5
  .byte 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 // 6
  .byte 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 // 7
  .byte 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 // 8
  .byte 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E // 9
  .byte 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C // A
  .byte 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 // B
  .byte 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 // C
  .byte 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C // D
  .byte 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 // E
  .byte 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 // F
;END OF OLED_char
