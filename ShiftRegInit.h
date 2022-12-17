#ifndef _SHIFT_REG_INIT_H_
#define _SHIFT_REG_INIT_H_

extern void write_reg(void);//sends values to solenoids/74HC595 Shift Regs
extern void ShiftReg_SSD(void);//sends values to SSDs/74HC595 Shift Regs

extern int p1_button_write_reg(void);//receives values from player 1 buttons / 74HC165 Shift Regs
	
extern int p2_button_write_reg(void);//receives values from player 2 buttons / 74HC165 Shift Regs

#endif
