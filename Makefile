BOARD := node32s
UPLOAD_SPEED := 921600
TERM_SPEED := 115200
SPIFFS_IMAGE :=

# watch the CPU execute and enable game "debug" port
#LOCAL_CPPFLAGS := -DCPU_DEBUG -DDEBUG

include arduino-esp32.mk
