#ifndef _ssd1306_h
#define _ssd1306_h

class ssd1306;

typedef struct{
    void *ctx;
    void (*init)(void*);
    void (*deinit)(void*);
    void (*sendCmd)(unsigned char*cmd,unsigned char len,void*);
    void (*sendDat)(unsigned char*dat,unsigned char len,void*);
    unsigned char *buf[1024];
}ssd1306_op_t;

using oled12864 = ssd1306;

class ssd1306{
public:
    ssd1306(ssd1306_op_t *op_t);
    ~ssd1306();
    void init();
    void deinit();
    void drawPoint(unsigned char x,unsigned char y,unsigned char bit);
    void drawLine(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);
    void drawRect(unsigned char x,unsigned char y,unsigned char w,unsigned char h);
    int showString(const char *str,unsigned char x,unsigned char y);
    //bool setPosition(unsigned char page,unsigned char x);
    //bool refresh();
    //bool drawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
    //bool drawPoint(uint8_t x,uint8_t y,uint8_t bit);
protected:
    ssd1306_op_t    _op_t;
};

#endif //_ssd1306_h
