/*
 * ssd1306.c
 *
 *  Created on: Dec 5, 2020
 *      Author: Turgay Hopal
 */
#include "../Inc/ssd1306.h"

struct SSD1306_GPIO ssd1306;

struct SSD1306_InitTypedef initSSD1306;

static uint8_t SSD1306_ScreenBuffer[1024];

void SSD1306_SetI2C(i2c_inst_t *I2C) {
	ssd1306.I2C = I2C;
}

void SSD1306_Init(uint8_t width, uint8_t height) {

	initSSD1306.Width = width;
	initSSD1306.Height = height;
	initSSD1306.CurrentX = 0;
	initSSD1306.CurrentY = 0;

	SSD1306_InitAddr initAddr;
	initAddr.AddrMode = _SET_MEM_ADDR_MODE_PAGE_ADDR;
	initAddr.ColEndAddr = _SET_COL_START_ADDR_START;
	initAddr.ColStartAddr = _SET_COL_END_ADDR_END;
	initAddr.GDDRAMStartAddr = _CMD_SET_GDDRAM_PAGE_START_PAGE_0;
	initAddr.LowColStartAddr = _CMD_PAGE_ADDR_MODE_LOW_COL_0;
	initAddr.HighColStartAddr = _CMD_PAGE_ADDR_MODE_HIGH_COL_0;
	initAddr.PageStartAddr = _SET_PAGE_ADDR_START_PAGE_0;
	initAddr.PageEndAddr = _SET_PAGE_ADDR_END_PAGE_7;

	SSD1306_InitHardware initHardware;
	initHardware.DisplayStartLine = _CMD_SET_DISPLAY_START_LINE_START;
	initHardware.ComPinsConfValue = _SET_COM_PINS_ALTERNATIVE_REMAP_DIS;
	initHardware.DisplayOffsetValue = _SET_DISPLAY_OFFSET_START;
	initHardware.MultiplexRatioValue = _SET_MULTIPLEX_RATIO_END;
	initHardware.ScanDirectionMode = _CMD_COM_OUTPUT_SCAN_DIR_REMAPPED;
	initHardware.SegmentRemap = _CMD_SET_SEGMENT_REMAP_ADDR_127;

	SSD1306_InitTiming initTiming;
	initTiming.DisplayDevideRatio = _SET_DISPLAY_DEVIDE_RATO_RST;
	initTiming.DisplayOscillatorFreq = _SET_DISPLAY_DEVIDE_OSC_FREQ_RST;
	initTiming.PreChargePeriodPhase1 = _SET_PRE_CHARGE_PHASE_1_RST;
	initTiming.PreChargePeriodPhase2 = _SET_PRE_CHARGE_PHASE_2_RST;
	initTiming.VComhDeselectLevel = _SET_VCOMH_DESELET_LEVEL_0_77_VCC;

	SSD1306_InitChargePump initChargePump;
	initChargePump.ChargePumpStatus = _SET_CHARGE_PUMP_ENABLE;

	SSD1306_SetDisplayOff();
	SSD1306_SetDisplayModeNormal();
	SSD1306_SetEntireDisplayOn();
	SSD1306_SetContrast(0xFF);
	SSD1306_SetAddrSetting(initAddr);
	SSD1306_SetHardwareSetting(initHardware);
	SSD1306_SetTimingSetting(initTiming);
	SSD1306_SetChargePumpSetting(initChargePump);
	SSD1306_SetDisplayOn();

	SSD1306_FillColor(BLACK);

	SSD1306_UpdateScreen();

}

void SSD1306_FillColor(SSD1306_Color color) {
	uint32_t i;

	for (i = 0; i < ((initSSD1306.Width * initSSD1306.Height) / 8); i++) {
		SSD1306_ScreenBuffer[i] = (color == BLACK) ? 0x00 : 0xFF;
	}
}

void SSD1306_UpdateScreen(void) {
	uint8_t i;
	uint8_t temp_buffer[initSSD1306.Width + 1];

	for (i = 0; i < 8; i++) {
		writeCommand(0xB0 + i);
		writeCommand(0x00);
		writeCommand(0x10);

		temp_buffer[0] = 0x40;

		for(uint8_t j = 0; j <= initSSD1306.Width; j++) {
			temp_buffer[j + 1] = SSD1306_ScreenBuffer[(initSSD1306.Width * i) + j];
		}
		i2c_write_blocking(ssd1306.I2C, SSD1306_I2C_ADDR, temp_buffer, sizeof(temp_buffer), false);
	}
}

void writeCommand(uint8_t command) {
	uint8_t send_data[] = {0x00, command};
  	i2c_write_blocking(ssd1306.I2C, SSD1306_I2C_ADDR, send_data, 2, false); 
}

void SSD1306_SetContrast(uint8_t value) {
	uint8_t contrast;
	contrast = _SET_CONTRAST_CONTROL_START + value;
	if (contrast > _SET_CONTRAST_CONTROL_END) {
		contrast = _SET_CONTRAST_CONTROL_END;
	}
	writeCommand(_CMD_SET_CONTRAST_CONTROL);
	writeCommand(contrast);
}

void SSD1306_SetEntireDisplayOn(void) {
	writeCommand(_CMD_ENTIRE_DISPLAY_ON);
}

void SSD1306_SetEntireDisplayOff(void) {
	writeCommand(_CMD_ENTIRE_DISPLAY_OFF);
}

void SSD1306_SetDisplayModeNormal(void) {
	writeCommand(_CMD_SET_DISPLAY_NORMAL);
}
void SSD1306_SetDisplayModeInverse(void) {
	writeCommand(_CMD_SET_DISPLAY_INVERSE);
}
void SSD1306_SetDisplayOn(void) {
	writeCommand(_CMD_SET_DISPLAY_ON);
}

void SSD1306_SetDisplayOff(void) {
	writeCommand(_CMD_SET_DISPLAY_OFF);
}

void SSD1306_SetActiveScroll(void) {
	writeCommand(_CMD_SCROLL_ACTIVE);
}

void SSD1306_SetDeactiveScroll(void) {
	writeCommand(_CMD_SCROLL_DEACTIVE);
}

void SSD1306_SetDisplayHorizontalScroll(
		SSD1306_HorizonalScrollSetup horizontalScroolSetup) {

	writeCommand(horizontalScroolSetup.ScrollDirection);
	writeCommand(0x00);
	writeCommand(horizontalScroolSetup.StartPageAddr);
	writeCommand(horizontalScroolSetup.FrameFrequency);
	writeCommand(horizontalScroolSetup.EndPageAddr);
	writeCommand(0x00);
	writeCommand(0xFF);
}

void SSD1306_SetDisplayVerticalScrool(
		SSD1306_VerticalScrollSetup verticalScrollSetup) {

	writeCommand(verticalScrollSetup.ScrollDirection);
	writeCommand(0x00);
	writeCommand(verticalScrollSetup.StartPageAddr);
	writeCommand(verticalScrollSetup.FrameFrequency);
	writeCommand(verticalScrollSetup.EndPageAddr);
	writeCommand(verticalScrollSetup.VerticalScrollOffset);
}

void SSD1306_SetDisplayVerticalScrollArea(
		SSD1306_VerticalScrollArea verticalScrollArea) {

	writeCommand(_CMD_SET_VERTICAL_SCROLL_AREA);
	writeCommand(verticalScrollArea.TopFixedAreaRows);
	writeCommand(verticalScrollArea.ScrollAreaRows);
}

void SSD1306_SetAddrSetting(SSD1306_InitAddr initAddr) {

	if (initAddr.AddrMode == _SET_MEM_ADDR_MODE_PAGE_ADDR) {

		writeCommand(_CMD_SET_MEM_ADDR_MODE);
		writeCommand(initAddr.AddrMode);

		writeCommand(initAddr.LowColStartAddr);

		writeCommand(initAddr.HighColStartAddr);

		writeCommand(initAddr.GDDRAMStartAddr);

	} else {

		writeCommand(_CMD_SET_MEM_ADDR_MODE);
		writeCommand(initAddr.AddrMode);

		writeCommand(_CMD_SET_COL_ADDR);
		writeCommand(initAddr.ColStartAddr);
		writeCommand(initAddr.ColEndAddr);

		writeCommand(_CMD_SET_PAGE_ADDR);
		writeCommand(initAddr.PageStartAddr);
		writeCommand(initAddr.PageEndAddr);
	}
}
void SSD1306_SetHardwareSetting(SSD1306_InitHardware initHardware) {

	writeCommand(initHardware.DisplayStartLine);
	writeCommand(initHardware.SegmentRemap);

	writeCommand(_CMD_SET_MULTIPLEX_RATIO);
	writeCommand(initHardware.MultiplexRatioValue);

	writeCommand(initHardware.ScanDirectionMode);

	writeCommand(_CMD_SET_DISPLAY_OFFSET);
	writeCommand(initHardware.DisplayOffsetValue);

	writeCommand(_CMD_SET_COM_PINS_HARDWARE_CONF);
	writeCommand(initHardware.ComPinsConfValue);

}
void SSD1306_SetTimingSetting(SSD1306_InitTiming initTiming) {

	writeCommand(_CMD_DISPLAY_CLK_DIV_RATIO_OSC_FRE);
	writeCommand(
			initTiming.DisplayDevideRatio | initTiming.DisplayOscillatorFreq);

	writeCommand(_CMD_SET_PRE_CHARGE_PERIOD);
	writeCommand(initTiming.PreChargePeriodPhase1 | initTiming.PreChargePeriodPhase2);

	writeCommand(_CMD_SET_VCOMH_DESELET_LEVEL);
	writeCommand(initTiming.VComhDeselectLevel);
}

void SSD1306_SetChargePumpSetting(SSD1306_InitChargePump initChargePump) {

	writeCommand(_CMD_CHARGE_PUMP_SETTING);
	writeCommand(initChargePump.ChargePumpStatus);
}

void SSD1306_SetScrollRight(uint8_t startRow, uint8_t endRow) {

	if (startRow < 0x00) {
		startRow = 0x00;
	} else if (startRow > 0x07) {
		startRow = 0x07;
	}

	if (endRow < 0x00) {
		endRow = 0x00;
	} else if (endRow > 0x07) {
		endRow = 0x07;
	}

	SSD1306_HorizonalScrollSetup initHorizonalScroll;

	initHorizonalScroll.ScrollDirection = _CMD_CONT_HORIZONTAL_SCROLL_RIGHT;
	initHorizonalScroll.StartPageAddr = startRow;
	initHorizonalScroll.EndPageAddr = endRow;
	initHorizonalScroll.FrameFrequency = _H_FRAME_FREQUENCY_2_FRAMES;

	SSD1306_SetDisplayHorizontalScroll(initHorizonalScroll);

	SSD1306_SetActiveScroll();

}
void SSD1306_SetScrollLeft(uint8_t startRow, uint8_t endRow) {

	if (startRow < 0x00) {
		startRow = 0x00;
	} else if (startRow > 0x07) {
		startRow = 0x07;
	}

	if (endRow < 0x00) {
		endRow = 0x00;
	} else if (endRow > 0x07) {
		endRow = 0x07;
	}

	SSD1306_HorizonalScrollSetup initHorizontalScroll;

	initHorizontalScroll.ScrollDirection = _CMD_CONT_HORIZONTAL_SCROLL_LEFT;
	initHorizontalScroll.StartPageAddr = startRow;
	initHorizontalScroll.EndPageAddr = endRow;
	initHorizontalScroll.FrameFrequency = _H_FRAME_FREQUENCY_2_FRAMES;

	SSD1306_SetDisplayHorizontalScroll(initHorizontalScroll);

	SSD1306_SetActiveScroll();
}

void SSD1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_Color color) {
	if (x >= initSSD1306.Width || y >= initSSD1306.Height) {
		return;
	}

	if (color == WHITE) {
		SSD1306_ScreenBuffer[x + (y / 8) * initSSD1306.Width] |= 1 << (y % 8);
	} else {
		SSD1306_ScreenBuffer[x + (y / 8) * initSSD1306.Width] &=
				~(1 << (y % 8));
	}
}

char SSD1306_WriteChar(char ch, FontDef Font, SSD1306_Color color) {
	uint32_t i, b, j;

	if (initSSD1306.Width <= (initSSD1306.CurrentX + Font.FontWidth)
			|| initSSD1306.Height <= (initSSD1306.CurrentY + Font.FontHeight)) {
		return 0;
	}

	for (i = 0; i < Font.FontHeight; i++) {
		b = Font.data[(ch - 32) * Font.FontHeight + i];
		for (j = 0; j < Font.FontWidth; j++) {
			if ((b << j) & 0x8000) {
				SSD1306_DrawPixel(initSSD1306.CurrentX + j, (initSSD1306.CurrentY + i), (SSD1306_Color) color);
			} else {
				SSD1306_DrawPixel(initSSD1306.CurrentX + j, (initSSD1306.CurrentY + i), (SSD1306_Color) !color);
			}
		}
	}

	initSSD1306.CurrentX += Font.FontWidth;
	return ch;
}

char SSD1306_WriteString(char *str, FontDef Font, SSD1306_Color color) {
	while (*str) {
		if (SSD1306_WriteChar(*str, Font, color) != *str) {
			return *str;
		}
		str++;
	}
	return *str;
}

void SSD1306_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, SSD1306_Color color)
{

    int16_t byteWidth = (w + 7) / 8;
    uint8_t byte = 0;

    for(int16_t j=0; j<h; j++, y++)
    {
        for(int16_t i=0; i<w; i++)
        {
            if(i & 7)
            {
               byte <<= 1;
            }
            else
            {
               byte = (*(const unsigned char *)(&bitmap[j * byteWidth + i / 8]));
            }
            if(byte & 0x80) SSD1306_DrawPixel(x+i, y, color);
        }
    }
}


void SSD1306_SetCursor(uint8_t x, uint8_t y) {
	initSSD1306.CurrentX = x;
	initSSD1306.CurrentY = y;
}
