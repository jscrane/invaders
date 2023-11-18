t ?= esp32

ifeq ($t, tivac)
BOARD := EK-LM4F120XL
CPPFLAGS = -DDEBUGGING -DHARDWARE_H=\"hw/stellarpad-example.h\"
LIBRARIES = UTFT SD SpiRAM
endif

ifeq ($t, esp8266)
BOARD := d1_mini
BAUD := 921600
SPIFFS_IMAGE :=
EESZ := 4M
TERMINAL_SPEED := 115200
F_CPU := 80

CPPFLAGS = -DUSER_SETUP_LOADED -DILI9341_DRIVER \
	-DTFT_WIDTH=240 -DTFT_HEIGHT=320 \
	-DTFT_CS=PIN_D6 -DTFT_DC=PIN_D8 \
	-DTFT_RST=-1 -DSPI_FREQUENCY=40000000 -DLOAD_GLCD \
	-DHARDWARE_H=\"hw/esp8bit.h\"
LIBRARIES = TFT_eSPI SpiRAM LittleFS
endif

ifeq ($t, esp32)
UPLOADSPEED := 921600
SPIFFS_IMAGE :=
LIBRARIES = FS SPIFFS

ifeq ($b, lilygo)
BOARD := ttgo-t7-v14-mini32
TERMINAL_SPEED := 115200
SERIAL_PORT := /dev/ttyACM0
CPPFLAGS := -DHARDWARE_H=\"hw/ttgo-t7-v14-mini32.h\"
LIBRARIES += FabGL WiFi

else
BOARD := node32s
CPPFLAGS := -DUSER_SETUP_LOADED -DILI9341_DRIVER -DTFT_CS=5 -DTFT_DC=2 \
	-DTFT_RST=-1 -DTFT_WIDTH=240 -DTFT_HEIGHT=320 \
	-DSPI_FREQUENCY=40000000 -DLOAD_GLCD \
	-DHARDWARE_H=\"hw/node32s-example.h\"
LIBRARIES += TFT_eSPI
endif
endif

include $t.mk
