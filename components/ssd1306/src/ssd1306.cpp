#include "ssd1306.h"
#include "string.h"
#include "font_lib.h"

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
    memset(_hal_t.buf,0x00,1024);
    refresh();
    //OLED12864_Send_NumByte(OLED12864_InitCmd,28,OLED_CMD);
}

void Ssd1306::refresh(){
    setPosition(0,0);
    _hal_t.sendDat(_hal_t.buf,1024,_hal_t.ctx);
}

void Ssd1306::clear(){
    memset(_hal_t.buf,0x00,1024);
}

void Ssd1306::clearPage(uint8_t page,uint8_t x,uint8_t len){
    uint8_t *offsetAddr = _hal_t.buf + page *128 + x;
    memset(offsetAddr,0x00,len);
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

void Ssd1306::drawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2){
    float sx,sy;
    float k,k_1;   //斜率
    k = ((float)y2-y1) / ((float)x2-x1);
    k_1 = 1/k;
    sx = x1;
    sy = y1;
    for(;x1<=x2;x1++)
    {
        sy += k;
        drawPoint(x1,(int)sy,1);
    }
    for(;y1<=y2;y1++)
    {
        sx += k_1;
        drawPoint((int)sx,y1,1);
    }
}

void Ssd1306::displayChar(uint8_t x,uint8_t y,char chr,uint8_t size){
    unsigned char *offsetAddr = _hal_t.buf + ( (y/8) * 128 ) + x;
    uint8_t pageOffset = y%8;
    uint8_t pageUpOffset = 8 - pageOffset;
    switch (size)
    {
    case 1:
        for(uint8_t sx = 0; sx<6 ;sx++){
            *(offsetAddr) &=  ~(0xff << pageOffset);
            *(offsetAddr) |=  assic_0806[chr-0x20][sx] << pageOffset;
            offsetAddr += 128;
            *(offsetAddr) &=  ~(0xff >> pageUpOffset);
            *(offsetAddr) |=  assic_0806[chr-0x20][sx] >> pageUpOffset;
            offsetAddr -= 127;
        }
        break;
    case 2:
        for(uint8_t sx = 0; sx<8 ;sx++){
            *(offsetAddr) &=  ~(0xff << pageOffset);
            *(offsetAddr) |=  (assic_1608[chr-0x20][sx] << pageOffset);
            offsetAddr += 128;
            *(offsetAddr) &=  ~0xff ;
            *(offsetAddr) |=  assic_1608[chr-0x20][sx] >> pageUpOffset;
            *(offsetAddr) |=  assic_1608[chr-0x20][sx+8] << pageOffset;
            offsetAddr += 128;
            *(offsetAddr) &=  ~(0xff >> pageUpOffset);
            *(offsetAddr) |=  (assic_1608[chr-0x20][sx+8] >> pageUpOffset);
            offsetAddr -= 255;
        }
        break;
    default:
        break;
    }
}

void Ssd1306::displayString(uint8_t x,uint8_t y,char *str,uint8_t size){
    uint8_t sx = x;
    while(*str!='\0')
    {
        displayChar(sx,y,*str,size);
        switch(size)
        {
            case 1:
                sx+=6;
                break;
            case 2:
                sx+=8;
                break;
            default:
                break;
        }
        str++;
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
