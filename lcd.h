//lcd.h
#include"types.h"
void writeLCD(u8 byte);
void cmdLCD(u8 cmd);
void charLCD(u8 ascii);
void InitLCD(void);
void strLCD(s8 *s);
void u32LCD(u32 n);
void s32LCD(s32 n);
void f32LCD(f32 fnum,u8 ndp);
