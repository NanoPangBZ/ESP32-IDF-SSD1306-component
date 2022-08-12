#ifndef _ssd1306_h
#define _ssd1306_h

#include "spi_4wire_hal/ssd1306_spi4_hal.h"

class Ssd1306{
public:
    typedef struct{
        void *ctx;
        void (*init)(void*);
        void (*deinit)(void*);
        void (*sendCmd)(unsigned char*cmd,unsigned char len,void*);
        void (*sendDat)(unsigned char*dat,unsigned char len,void*);
        unsigned char *buf;
    }Ssd1306_fun_t;
    Ssd1306(Ssd1306_fun_t *fun_t);
    ~Ssd1306();
protected:
    Ssd1306_fun_t   _fun_t;
    bool            _isSelfBuf;
};

#endif //_ssd1306_h
