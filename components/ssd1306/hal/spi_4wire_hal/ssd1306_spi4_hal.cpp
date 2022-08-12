#include "ssd1306_spi4_hal.h"

#include "freertos\FreeRTOS.h"
#include "freertos\task.h"
#include "driver\gpio.h"
#include "driver\spi_master.h"
#include "stdlib.h"
#include "string.h"
#include "esp_timer.h"

Ssd1306::Ssd1306_fun_t spi4_fun_t = {
    .ctx = NULL,
    .init = Init,
    .sendCmd = sendCmd,
    .sendDat = sendDat,
    .buf = NULL,
};

static spi_device_handle_t  spi_handle;     //spi操作句柄

static void OLED12864_GPIO_Init(void)
{
    gpio_set_direction((gpio_num_t)OLED_DC,GPIO_MODE_OUTPUT);
    gpio_set_direction((gpio_num_t)OLED_RES,GPIO_MODE_OUTPUT);
    OLED12864_Reset_Bit(OLED_DC);
    OLED12864_Set_Bit(OLED_RES);
}

void IRAM_ATTR OLED12864_SPI_Start_CallBack(spi_transaction_t *para){
    if( (int)para->user == OLED_CMD){
        gpio_set_level((gpio_num_t)OLED_DC,0);
    }else{
        gpio_set_level((gpio_num_t)OLED_DC,1);
    }
}

static void OLED12864_SPI_Init(void)
{
    spi_bus_config_t buscfg;
    buscfg.miso_io_num = -1;
    buscfg.sclk_io_num = OLED_SCL;
    buscfg.quadwp_io_num = -1;
    buscfg.quadhd_io_num = -1;
    buscfg.max_transfer_sz = 4092;
    buscfg.mosi_io_num = OLED_MOSI;
    spi_device_interface_config_t device_interface;
    device_interface.clock_speed_hz = SPI_MASTER_FREQ_20M;
    device_interface.queue_size = 3;
    device_interface.mode = 3;
    device_interface.spics_io_num = OLED_CS;
    device_interface.pre_cb = OLED12864_SPI_Start_CallBack;

    spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
    spi_bus_add_device(SPI2_HOST,&device_interface,&spi_handle);

}

static void OLED12864_Set_Bit(int pin_Num){
    gpio_set_level((gpio_num_t)pin_Num,1);
}

static void OLED12864_Reset_Bit(int pin_Num){
    gpio_set_level((gpio_num_t)pin_Num,0);
}

static void OLED12864_Send_NumByte(const uint8_t*dat,uint16_t len,uint8_t cmd)
{
    static spi_transaction_t tran;
    tran.tx_buffer = dat;
    tran.length = len*8;
    tran.rxlength = tran.length;
    tran.flags = SPI_TRANS_MODE_OCT;
    if(cmd==OLED_CMD){
        tran.user = (void*)OLED_CMD;
    }else{
        tran.user = (void*)OLED_DATA;
    }
    spi_device_queue_trans(spi_handle,&tran, portMAX_DELAY );
}

static void OLED12864_delay_ms(uint16_t ms){`
    vTaskDelay(ms/portTICK_PERIOD_MS);
}

void Init(void*ctx){
    OLED12864_GPIO_Init();
    OLED12864_SPI_Init();
}

void sendCmd(uint8_t* cmd,uint8_t len,void* ctx){
    OLED12864_Send_NumByte(cmd,len,OLED_CMD);
}

void sendDat(uint8_t* dat,uint8_t len,void* ctx){
    OLED12864_Send_NumByte(dat,len,OLED_CMD);
}

