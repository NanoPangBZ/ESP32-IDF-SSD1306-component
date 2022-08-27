## ESP32 SSD1306 C++ Component

v0.1 Currently, only 4wire-spi mode is supported.

### components/ssd1306

- /src

	Control logic of ssd1306 and display of basic characters and graphics.It's separate from hardware.

- /hal

	Hardware abstraction layer.Provide a unified interface for /src to operate the hardware under different MCUs and different ssd1306 modes.

## ESP32 SSD1306 C++组件

v0.1 当前仅支持4wire spi模式

### components/ssd1306

- /src

	ssd1306的控制逻辑与基本的字符与图形的显示，与具体硬件平台无关

- /hal

	硬件抽象层 向src提供统一的操作底层硬件的接口
