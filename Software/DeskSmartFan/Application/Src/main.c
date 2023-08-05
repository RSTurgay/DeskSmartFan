
#include "../Inc/main.h"

int main()
{
    stdio_init_all();

    i2c_init(i2c1, 100 * 1000);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);

    printf("\nSSD1306 Demo Started\n");

    SSD1306_SetI2C(i2c1);
    SSD1306_Init(128, 64);
    SSD1306_FillColor(BLACK);
    SSD1306_UpdateScreen();

    uint16_t counter = 0;

    while (true)
    {
        SSD1306_SetCursor(0, 0);
        SSD1306_WriteChar((uint16_t)(((counter % 100000) / 10000) + 48), Font_16x26, WHITE);
        SSD1306_WriteChar((uint16_t)(((counter % 10000) / 1000) + 48), Font_16x26, WHITE);
        SSD1306_WriteChar((uint16_t)(((counter % 1000) / 100) + 48), Font_16x26, WHITE);
        SSD1306_WriteChar((uint16_t)(((counter % 100) / 10) + 48), Font_16x26, WHITE);
        SSD1306_WriteChar((uint16_t)((counter % 10) + 48), Font_16x26, WHITE);

        SSD1306_UpdateScreen();
        counter++;
        printf("%d \r\n",counter);
    }

    return 0;
}