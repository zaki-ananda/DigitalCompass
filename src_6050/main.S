#define __SFR_OFFSET 0x00
#include "avr/io.h"
#include "i2c.h"
#include "usart.h"
#include "oled.h"
#include "delay.h"

.global main
main:

init:
  CALL USART_init
  CALL I2C_init
  CALL OLED_init
  CALL OLED_displayOn
  
  LDI RMPU_RA, 0x75
  CALL MPU_read
  MOV RdataOut, RMPU_data
  CALL USART_printByte
  CALL USART_newline

loop:
  CALL delay1s  

  LDI RMPU_RA, 0x43
  LDI ROLED_page, 0
  LDI ROLED_col, 0
  CALL showMPUReading

  LDI RMPU_RA, 0x44
  LDI ROLED_page, 0
  LDI ROLED_col, 12
  CALL showMPUReading

  CALL USART_newline

  LDI RMPU_RA, 0x45
  LDI ROLED_page, 1
  LDI ROLED_col, 0
  CALL showMPUReading

  LDI RMPU_RA, 0x46
  LDI ROLED_page, 1
  LDI ROLED_col, 12
  CALL showMPUReading

  CALL USART_newline

  LDI RMPU_RA, 0x47
  LDI ROLED_page, 2
  LDI ROLED_col, 0
  CALL showMPUReading

  LDI RMPU_RA, 0x48
  LDI ROLED_page, 2
  LDI ROLED_col, 12
  CALL showMPUReading

  CALL USART_newline

JMP loop

showMPUReading:
  CALL MPU_read
  
  MOV RdataOut, RMPU_data
  CALL USART_printByte

  MOV ROLED_buffer, RMPU_data
  CALL OLED_writeByte
RET

MPU_read:
  CALL I2C_start
  
  LDI RdataOut, MPU_Addr_W
  CALL I2C_write
  
  MOV RdataOut, RMPU_RA
  CALL I2C_write
  
  CALL I2C_start
  
  LDI RdataOut, MPU_Addr_R
  CALL I2C_write
  
  CALL I2C_read_NACK
  CALL I2C_stop
  MOV RMPU_data, RdataIn
RET
