#ifndef FONTS_H
#define FONTS_H 

#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	uint8_t FontWidth;    /*!< Font width in pixels */
	uint8_t FontHeight;   /*!< Font height in pixels */
	const uint16_t *data; /*!< Pointer to data font data array */
} FontDef;

typedef struct {
	uint16_t Length;      /*!< String length in units of pixels */
	uint16_t Height;      /*!< String height in units of pixels */
} FONTS_SIZE_t;

extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;

char* FONTS_GetStringSize(char* str, FONTS_SIZE_t* SizeStruct, FontDef *Font);

#endif /* FONTS_H */