add_executable(desk_smart_fan
        Src/main.c
        Inc/main.h)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(desk_smart_fan
        pico_binary_info
        hardware_i2c
        pico_stdlib
        external_lib)

# enable usb output, disable uart output
pico_enable_stdio_usb(desk_smart_fan 1)
pico_enable_stdio_uart(desk_smart_fan 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(desk_smart_fan)