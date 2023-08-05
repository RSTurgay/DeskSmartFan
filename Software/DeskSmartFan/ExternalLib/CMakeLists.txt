add_library(external_lib
        Inc/ssd1306.h
        Inc/fonts.h
        Src/ssd1306.c
        Src/fonts.c
        )

target_include_directories(external_lib PUBLIC
        Src
        Inc
        )

target_link_libraries(external_lib
        hardware_i2c
        pico_stdlib)