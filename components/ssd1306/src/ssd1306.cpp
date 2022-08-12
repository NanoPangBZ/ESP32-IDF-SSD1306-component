#include "ssd1306.h"

Ssd1306::Ssd1306(Ssd1306_fun_t *fun_t){
    _fun_t = *fun_t;
    _isSelfBuf = false;
    if(!_fun_t.buf){
        _fun_t.buf = new unsigned char[1024];
        _isSelfBuf = true;
    }
}

Ssd1306::~Ssd1306(){
    if(_isSelfBuf){
        delete []_fun_t.buf;
    }
}

//ssd1306
