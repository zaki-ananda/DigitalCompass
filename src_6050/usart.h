#define __SFR_OFFSET 0x00
#include "avr/io.h"
#include "registerMap.h"

USART_init:
  CLR Rcontrol
  STS UCSR0A, Rcontrol ;clear UCSR0A register
  STS UBRR0H, Rcontrol ;clear UBRR0H register
  LDI Rcontrol, 51 ;& store in UBRR0L 51 value
  STS UBRR0L, Rcontrol ;to set baud rate 19200
  LDI Rcontrol, 1<<RXEN0 | 1<<TXEN0 ;enable RXB & TXB
  STS UCSR0B, Rcontrol
  LDI Rcontrol, 1<<UCSZ00 | 1<<UCSZ01;asynch, no parity, 1 stop, 8 bits
  STS UCSR0C, Rcontrol
RET

USART_printByte:
  .equ R_4bit, Rtemp1
  .equ R_toASCII, Rtemp3
  
  MOV R_4bit, RdataOut ; print RdataOut to serial monitor
  RCALL ASCII_MSD ; print right digit
  RCALL USART_wait ; check if ready to print
  STS UDR0, R_4bit ; store to data register

  MOV R_4bit, RdataOut
  RCALL ASCII_LSD ; print left digit
  RCALL USART_wait ; check if ready to print
  STS UDR0, R_4bit ; store to data register
RET

USART_newline:
  LDI Rtemp1, 13
  RCALL USART_wait
  STS UDR0, Rtemp1 ;carriage return
  
  LDI Rtemp1, 10
  RCALL USART_wait
  STS UDR0, Rtemp1 ;carriage return
RET

USART_qMark:
  LDI Rtemp1, 63
  RCALL USART_wait
  STS UDR0, Rtemp1 ;carriage return
RET

USART_null:
  LDI Rtemp1, 0
  RCALL USART_wait
  STS UDR0, Rtemp1 ;null (nochar)

  LDI Rtemp1, 0
  RCALL USART_wait
  STS UDR0, Rtemp1 ;null (nochar)
RET

USART_wait:
  LDS Rstatus, UCSR0A
  SBRS Rstatus, UDRE0 ;test data buffer if data can be sent
  RJMP USART_wait
RET

ASCII_MSD:
  ANDI R_4bit, 0xF0
  SWAP R_4bit
  CPI R_4bit, 10
  BRPL ASCII_MSD_AF
  SUBI R_4bit, -48
  ASCII_MSD_Finish:
RET

ASCII_MSD_AF:
  SUBI R_4bit, -55
RJMP ASCII_MSD_Finish

ASCII_LSD:
  ANDI R_4bit, 0x0F
  CPI R_4bit, 10
  BRPL ASCII_LSD_AF
  SUBI R_4bit, -48
  ASCII_LSD_Finish:
RET

ASCII_LSD_AF:
  SUBI R_4bit, -55
RJMP ASCII_LSD_Finish
