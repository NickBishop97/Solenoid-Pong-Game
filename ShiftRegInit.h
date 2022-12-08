#ifndef _SHIFT_REG_INIT_H_
#define _SHIFT_REG_INIT_H_

extern void write_reg(void);//sends values to solenoids
extern void ShiftReg_SSD(void);//sends values to SSDs

extern int p1_button_write_reg(void);
	
extern int p2_button_write_reg(void);

#endif
