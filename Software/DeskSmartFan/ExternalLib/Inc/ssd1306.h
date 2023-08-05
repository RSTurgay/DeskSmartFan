/*
 * ssd1306.h
 *
 *  Created on: Dec 5, 2020
 *      Author: Turgay Hopal
 */

#ifndef INC_SSD1306_H_
#define INC_SSD1306_H_

#include "fonts.h"
#include "hardware/i2c.h"

#define SSD1306_I2C_ADDR        			0x3C

// COMMAND DEFINES

// Fundamental Command Table

#define _CMD_SET_CONTRAST_CONTROL 			0x81
#define _SET_CONTRAST_CONTROL_START			0x00
#define _SET_CONTRAST_CONTROL_END			0xFF

#define _CMD_ENTIRE_DISPLAY_ON				0xA4
#define _CMD_ENTIRE_DISPLAY_OFF				0xA5
#define _CMD_SET_DISPLAY_NORMAL				0xA6
#define _CMD_SET_DISPLAY_INVERSE			0xA7
#define _CMD_SET_DISPLAY_ON					0xAF
#define _CMD_SET_DISPLAY_OFF				0xAE

// Scrolling Command Table

// Continuous Horizontal Scroll Setup

#define _CMD_CONT_HORIZONTAL_SCROLL_RIGHT	0x26
#define _CMD_CONT_HORIZONTAL_SCROLL_LEFT	0x27
#define _H_FRAME_FREQUENCY_5_FRAMES			0x00
#define _H_FRAME_FREQUENCY_64_FRAMES		0x01
#define _H_FRAME_FREQUENCY_128_FRAMES		0x02
#define _H_FRAME_FREQUENCY_256_FRAMES		0x03
#define _H_FRAME_FREQUENCY_3_FRAMES			0x04
#define _H_FRAME_FREQUENCY_4_FRAMES			0x05
#define _H_FRAME_FREQUENCY_25_FRAMES		0x06
#define _H_FRAME_FREQUENCY_2_FRAMES			0x07

// Continuous Vertical and Horizontal Scroll Setup

#define _CMD_CONT_VERTICAL_SCROLL_RIGHT		0x29
#define _CMD_CONT_VERTICAL_SCROLL_LEFT		0x2A
#define _V_FRAME_FREQUENCY_5_FRAMES			0x00
#define _V_FRAME_FREQUENCY_64_FRAMES		0x01
#define _V_FRAME_FREQUENCY_128_FRAMES		0x02
#define _V_FRAME_FREQUENCY_256_FRAMES		0x03
#define _V_FRAME_FREQUENCY_3_FRAMES			0x04
#define _V_FRAME_FREQUENCY_4_FRAMES			0x05
#define _V_FRAME_FREQUENCY_25_FRAMES		0x06
#define _V_FRAME_FREQUENCY_2_FRAMES			0x07
#define _V_SCROLL_OFSET_START				0x01
#define _V_SCROLL_OFSET_END					0x3F

#define _CMD_SCROLL_DEACTIVE				0x2E

#define _CMD_SCROLL_ACTIVE					0x2F

// Set Vertical Scroll Area

#define _CMD_SET_VERTICAL_SCROLL_AREA		0xA3
#define _V_TOP_FIXED_AREA_ROWS_START		0x00
#define _V_TOP_FIXED_AREA_ROWS_END			0x3F
#define _V_SCROLL_AREA_ROWS_START			0x00
#define _V_SCROLL_AREA_ROWS_END				0x7F

// Addressing Setting Command Table

#define _CMD_PAGE_ADDR_MODE_LOW_COL_0		0x00
#define _CMD_PAGE_ADDR_MODE_LOW_COL_1		0x01
#define _CMD_PAGE_ADDR_MODE_LOW_COL_2		0x02
#define _CMD_PAGE_ADDR_MODE_LOW_COL_3		0x03
#define _CMD_PAGE_ADDR_MODE_LOW_COL_4		0x04
#define _CMD_PAGE_ADDR_MODE_LOW_COL_5		0x05
#define _CMD_PAGE_ADDR_MODE_LOW_COL_6		0x06
#define _CMD_PAGE_ADDR_MODE_LOW_COL_7		0x07
#define _CMD_PAGE_ADDR_MODE_LOW_COL_8		0x08
#define _CMD_PAGE_ADDR_MODE_LOW_COL_9		0x09
#define _CMD_PAGE_ADDR_MODE_LOW_COL_10		0x0A
#define _CMD_PAGE_ADDR_MODE_LOW_COL_11		0x0B
#define _CMD_PAGE_ADDR_MODE_LOW_COL_12		0x0C
#define _CMD_PAGE_ADDR_MODE_LOW_COL_13		0x0D
#define _CMD_PAGE_ADDR_MODE_LOW_COL_14		0x0E
#define _CMD_PAGE_ADDR_MODE_LOW_COL_15		0x0F

#define _CMD_PAGE_ADDR_MODE_HIGH_COL_0		0x10
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_1		0x11
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_2		0x12
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_3		0x13
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_4		0x14
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_5		0x15
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_6		0x16
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_7		0x17
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_8		0x18
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_9		0x19
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_10		0x1A
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_11		0x1B
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_12		0x1C
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_13		0x1D
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_14		0x1E
#define _CMD_PAGE_ADDR_MODE_HIGH_COL_15		0x1F

#define _CMD_SET_MEM_ADDR_MODE				0x20
#define _SET_MEM_ADDR_MODE_HEROZONAL		0x00
#define _SET_MEM_ADDR_MODE_VERTICAL			0x01
#define _SET_MEM_ADDR_MODE_PAGE_ADDR		0x02

#define _CMD_SET_COL_ADDR					0x21
#define _SET_COL_START_ADDR_START			0x00
#define _SET_COL_START_ADDR_END				0x7F
#define _SET_COL_END_ADDR_START				0x00
#define _SET_COL_END_ADDR_END				0x7F

#define _CMD_SET_PAGE_ADDR					0x22
#define _SET_PAGE_ADDR_START_PAGE_0			0x00
#define _SET_PAGE_ADDR_START_PAGE_1			0x01
#define _SET_PAGE_ADDR_START_PAGE_2			0x02
#define _SET_PAGE_ADDR_START_PAGE_3			0x03
#define _SET_PAGE_ADDR_START_PAGE_4			0x04
#define _SET_PAGE_ADDR_START_PAGE_5			0x05
#define _SET_PAGE_ADDR_START_PAGE_6			0x06
#define _SET_PAGE_ADDR_START_PAGE_7			0x07
#define _SET_PAGE_ADDR_END_PAGE_0			0x00
#define _SET_PAGE_ADDR_END_PAGE_1			0x01
#define _SET_PAGE_ADDR_END_PAGE_2			0x02
#define _SET_PAGE_ADDR_END_PAGE_3			0x03
#define _SET_PAGE_ADDR_END_PAGE_4			0x04
#define _SET_PAGE_ADDR_END_PAGE_5			0x05
#define _SET_PAGE_ADDR_END_PAGE_6			0x06
#define _SET_PAGE_ADDR_END_PAGE_7			0x07

#define _CMD_SET_GDDRAM_PAGE_START_PAGE_0	0xB0
#define _CMD_SET_GDDRAM_PAGE_START_PAGE_1	0xB1
#define _CMD_SET_GDDRAM_PAGE_START_PAGE_2	0xB2
#define _CMD_SET_GDDRAM_PAGE_START_PAGE_3	0xB3
#define _CMD_SET_GDDRAM_PAGE_START_PAGE_4	0xB4
#define _CMD_SET_GDDRAM_PAGE_START_PAGE_5	0xB5
#define _CMD_SET_GDDRAM_PAGE_START_PAGE_6	0xB6
#define _CMD_SET_GDDRAM_PAGE_START_PAGE_7	0xB7

// Hardware Configuration (Panel resolution & layout related) Command Table

#define _CMD_SET_DISPLAY_START_LINE_START	0x40
#define _CMD_SET_DISPLAY_START_LINE_END		0x7F
#define _CMD_SET_SEGMENT_REMAP_ADDR_0		0xA0
#define _CMD_SET_SEGMENT_REMAP_ADDR_127		0xA1

#define _CMD_SET_MULTIPLEX_RATIO			0xA8
#define _SET_MULTIPLEX_RATIP_START			0x10
#define _SET_MULTIPLEX_RATIO_END			0x3F

#define _CMD_COM_OUTPUT_SCAN_DIR_NORMAL		0xC0
#define _CMD_COM_OUTPUT_SCAN_DIR_REMAPPED	0xC8

#define _CMD_SET_DISPLAY_OFFSET				0xD3
#define _SET_DISPLAY_OFFSET_START			0x00
#define _SET_DISPLAY_OFFSET_END				0x3F

#define _CMD_SET_COM_PINS_HARDWARE_CONF		0xDA
#define _SET_COM_PINS_SEQUENTIAL_REMAP_DIS	0x02
#define _SET_COM_PINS_SEQUENTIAL_REMAP_EN	0x22
#define _SET_COM_PINS_ALTERNATIVE_REMAP_DIS	0x12
#define _SET_COM_PINS_ALTERNATIVE_REMAP_EN	0x32

// Timing & Driving Scheme Setting Command Table

#define _CMD_DISPLAY_CLK_DIV_RATIO_OSC_FRE	0xD5
#define _SET_DISPLAY_DEVIDE_RATO_RST		0x00
#define _SET_DISPLAY_DEVIDE_OSC_FREQ_RST	0xF0

#define _CMD_SET_PRE_CHARGE_PERIOD			0xD9
#define _SET_PRE_CHARGE_PHASE_1_RST			0x02
#define _SET_PRE_CHARGE_PHASE_2_RST			0x20

#define _CMD_SET_VCOMH_DESELET_LEVEL		0xDB
#define _SET_VCOMH_DESELET_LEVEL_0_65_VCC	0x00
#define _SET_VCOMH_DESELET_LEVEL_0_77_VCC	0x20
#define _SET_VCOMH_DESELET_LEVEL_0_83_VCC	0x30

#define _CMD_CHARGE_PUMP_SETTING			0x8D
#define _SET_CHARGE_PUMP_ENABLE				0x14
#define _SET_CHARGE_PUMP_DISABLE			0x10

struct SSD1306_InitTypedef{
	uint8_t Height;
	uint8_t Width;
	uint8_t CurrentX;
	uint8_t CurrentY;
};

typedef struct {
	uint8_t AddrMode;		 	// Addressing Mode Select
	uint8_t ColStartAddr;    	// Vertical or Horizontal Addressing Mode
	uint8_t ColEndAddr;      	// Vertical or Horizontal Addressing Mode
	uint8_t LowColStartAddr; 	// Page Addressing Mode
	uint8_t HighColStartAddr;	// Page Addressing Mode
	uint8_t PageStartAddr;	 	// Page Addressing Mode
	uint8_t PageEndAddr;	 	// Page Addressing Mode
	uint8_t GDDRAMStartAddr; 	// Page Addressing Mode
}SSD1306_InitAddr;

typedef struct {
	uint8_t DisplayStartLine;
	uint8_t SegmentRemap;
	uint8_t MultiplexRatioValue;
	uint8_t ScanDirectionMode;
	uint8_t DisplayOffsetValue;
	uint8_t ComPinsConfValue;
}SSD1306_InitHardware;

typedef struct {
	uint8_t DisplayDevideRatio;
	uint8_t DisplayOscillatorFreq;
	uint8_t PreChargePeriodPhase1;
	uint8_t PreChargePeriodPhase2;
	uint8_t VComhDeselectLevel;
}SSD1306_InitTiming;

typedef struct {
	uint8_t ChargePumpStatus;
}SSD1306_InitChargePump;

typedef struct {
	uint8_t ScrollDirection;
	uint8_t StartPageAddr;
	uint8_t FrameFrequency;
	uint8_t EndPageAddr;
}SSD1306_HorizonalScrollSetup;

typedef struct {
	uint8_t ScrollDirection;
	uint8_t StartPageAddr;
	uint8_t FrameFrequency;
	uint8_t EndPageAddr;
	uint8_t VerticalScrollOffset;
}SSD1306_VerticalScrollSetup;

typedef struct {
	uint8_t TopFixedAreaRows;
	uint8_t ScrollAreaRows;
}SSD1306_VerticalScrollArea;

typedef enum {
	BLACK = 0x00,
	WHITE = 0x01
}SSD1306_Color;

struct SSD1306_GPIO {
	i2c_inst_t *I2C;
};

void SSD1306_SetI2C(i2c_inst_t *I2C);
void SSD1306_Init(uint8_t width, uint8_t height);
void SSD1306_FillColor(SSD1306_Color color);
void SSD1306_UpdateScreen(void);
void SSD1306_SetScrollRight(uint8_t startRow, uint8_t stopRow);
void SSD1306_SetScrollLeft(uint8_t startRow, uint8_t stopRow);
void SSD1306_StopScroll(void);

void SSD1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_Color color);
char SSD1306_WriteChar(char ch, FontDef Font, SSD1306_Color color);
char SSD1306_WriteString(char *str, FontDef Font, SSD1306_Color color);
void SSD1306_SetCursor(uint8_t x, uint8_t y);
void SSD1306_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, SSD1306_Color color);

// Private Functions

void writeCommand(uint8_t command);

// Command Functions

void SSD1306_SetContrast(uint8_t value);
void SSD1306_SetEntireDisplayOn(void);
void SSD1306_SetEntireDisplayOff(void);
void SSD1306_SetDisplayModeNormal(void);
void SSD1306_SetDisplayModeInverse(void);
void SSD1306_SetDisplayOn(void);
void SSD1306_SetDisplayOff(void);
void SSD1306_SetActiveScroll(void);
void SSD1306_SetDeactiveScroll(void);
void SSD1306_SetDisplayHorizontalScroll(SSD1306_HorizonalScrollSetup horizontalScroolSetup);
void SSD1306_SetDisplayVerticalScrool(SSD1306_VerticalScrollSetup verticalScrollSetup);
void SSD1306_SetDisplayVerticalScrollArea(SSD1306_VerticalScrollArea verticalScrollArea);
void SSD1306_SetAddrSetting(SSD1306_InitAddr initAddr);
void SSD1306_SetHardwareSetting(SSD1306_InitHardware initHardware);
void SSD1306_SetTimingSetting(SSD1306_InitTiming initTiming);
void SSD1306_SetChargePumpSetting(SSD1306_InitChargePump initChargePump);

#endif /* INC_SSD1306_H_ */
