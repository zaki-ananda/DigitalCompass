#define __SFR_OFFSET 0x00
#include "avr/io.h"

.equ Rstatus, 2
.equ Rtemp, 3
.equ RdataIn, 4
.equ Rcontrol, 16
.equ RdataOut, 17
.equ Rtemp1, 18
.equ Rtemp3, 19
.equ RMPU_RA, 20
.equ RMPU_data, 21
.equ ROLED_page, 22
.equ ROLED_buffer, 23
.equ ROLED_col, 24
.equ Rtemp5, 25
.equ Rtemp6, 26
.equ Rtemp4, 27

.equ MPU_Addr_W, 0b11010000
.equ MPU_Addr_R, 0b11010001
.equ OLED_Addr_W,0b01111000
.equ OLED_Addr_R,0b01111001
