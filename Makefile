PROCESSOR_FAMILY := lm4f
BOARD := lplm4f120h5qr
CPPFLAGS = -DDEBUGGING -DHARDWARE_H=\"hw/lm4f-utft.h\"
LIBRARIES = UTFT
include energia10.mk

#CPPFLAGS = -DUSER_SETUP_LOADED -DILI9341_DRIVER \
#	-DTFT_WIDTH=240 -DTFT_HEIGHT=320 \
#	-DTFT_CS=PIN_D6 -DTFT_DC=PIN_D8 \
#	-DTFT_RST=-1 -DSPI_FREQUENCY=40000000 -DLOAD_GLCD
#LIBRARIES = TFT_eSPI
#
#include arduino-esp.mk
