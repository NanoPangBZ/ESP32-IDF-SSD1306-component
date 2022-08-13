#ifndef _ssd1306_h
#define _ssd1306_h

#include "ssd1306_hal.h"

class Ssd1306{
public:
    Ssd1306(Ssd1306_hal_handle_t *hal_t);
    ~Ssd1306();
    void softInit();
    void refresh();
    void drawPoint(uint8_t x,uint8_t y,uint8_t bit);
    void displayChar(uint8_t x,uint8_t y,char chr,uint8_t size);
    void displayString(uint8_t x,uint8_t y,char *str,uint8_t size);
private:
    void setPosition(uint8_t page,uint8_t x);
    uint8_t* _getByteAddr(uint8_t page,uint8_t x);
    Ssd1306_hal_handle_t   _hal_t;
    bool                   _isSelfBuf;
};

#endif //_ssd1306_h
