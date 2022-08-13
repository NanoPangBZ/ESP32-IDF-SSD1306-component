#include "ssd1306.h"

Ssd1306::Ssd1306(Ssd1306_hal_handle_t *hal_t){
    _hal_t = *hal_t;
    _isSelfBuf = false;
    if(!_hal_t.buf){
        _hal_t.buf = new unsigned char[1024];
        _isSelfBuf = true;
    }
    _hal_t.init(_hal_t.ctx);
    softInit();
}

Ssd1306::~Ssd1306(){
    if(_isSelfBuf){
        delete []_hal_t.buf;
    }
}

void Ssd1306::softInit(){
    static uint8_t initCmd[28] = {
    0xae,0x00,0x10,0x40,0x81,0xcf,
    0xa1,0xc8,0xa6,0xa8,0x3f,0xd3,
    0x00,0xd5,0x80,0xd9,0xf1,0xda,
    0x12,0xdb,0x40,0x20,0x00,0x8d,
    0x14,0xa4,0xa6,0xaf
    };
    _hal_t.sendCmd(initCmd,28,_hal_t.ctx);
    //OLED12864_Send_NumByte(OLED12864_InitCmd,28,OLED_CMD);
}

void Ssd1306::refresh(){
    setPosition(0,0);
    _hal_t.sendDat(_hal_t.buf,1024,_hal_t.ctx);
}

void Ssd1306::drawPoint(uint8_t x,uint8_t y,uint8_t bit){
    if( y > 63 || x > 127)
        return;
    uint8_t page = y/8;
    uint8_t offset = y%8;
    if(bit){
        _hal_t.buf[page*128+x] |= (0x01<<offset);
    }else{
        _hal_t.buf[page*128+x] &= ~(0x01<<offset);
    }
}

void Ssd1306::setPosition(uint8_t page,uint8_t x){
    static uint8_t dat[3];
    dat[0] = 0xb0 + page;           //页地址
    dat[1] = ((0xf0&x)>>4)|0x10;    //x坐标高四位设定
    dat[2] = 0x0f&x;                //x坐标低四位设定
    _hal_t.sendCmd(dat,3,_hal_t.ctx);
    //OLED12864_Send_NumByte(dat,3,OLED_CMD);
}

//ssd1306
