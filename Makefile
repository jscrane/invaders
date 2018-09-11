BOARD := node32s
UPLOAD_SPEED := 921600
TERM_SPEED := 115200

# watch the CPU execute and enable game "debug" port
#LOCAL_CPPFLAGS := -DCPU_DEBUG -DDEBUGGING

include arduino-esp32.mk
