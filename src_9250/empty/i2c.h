#define __SFR_OFFSET 0x00
#include "avr/io.h"
#include "registerMap.h"

I2C_init:
  LDI Rcontrol, 0
  STS TWSR, Rcontrol ;prescaler = 0
  LDI Rcontrol, 12 ;division factor = 12
  STS TWBR, Rcontrol ;SCK freq = 400kHz
  LDI Rcontrol, (1<<TWEN)
  STS TWCR, Rcontrol ;enable TWI
RET

I2C_start:
  LDI Rcontrol, (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
  STS TWCR, Rcontrol ;transmit START condition
  RCALL I2C_waitInt
RET

I2C_waitInt:
  LDS Rstatus, TWCR
  SBRS Rstatus, TWINT ;TWI interrupt = 1?
  JMP I2C_waitInt ;if no, wait for end of transmission
RET

I2C_write:
  STS TWDR, RdataOut 
  LDI Rcontrol, (1<<TWINT)|(1<<TWEN)
  STS TWCR, Rcontrol
  CALL I2C_waitInt
RET

I2C_read_NACK:
  LDI Rcontrol, (1<<TWINT)|(1<<TWEN)
  STS TWCR, Rcontrol
  CALL I2C_waitInt
  LDS RdataIn, TWDR
RET

I2C_stop:
  LDI Rcontrol, (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)
  STS TWCR, Rcontrol ;transmit STOP condition
RET
