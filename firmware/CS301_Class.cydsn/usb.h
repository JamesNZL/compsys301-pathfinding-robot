#ifndef UART_H_
#define UART_H_

#define USE_USB

#define BUF_SIZE	64 // USBUART fixed buffer size
#define CHAR_NULL	'0'
#define CHAR_BACKSP 0x08
#define CHAR_DEL	0x7F
#define CHAR_ENTER	0x0D
#define LOW_DIGIT	'0'

extern uint8 flag_KB_string = 0;

char displaystring[BUF_SIZE] = "CS301 2016\n";
char line[BUF_SIZE], entry[BUF_SIZE];
uint8 usbBuffer[BUF_SIZE];

void handle_usb();
void usb_put_string(char *s);
void usb_put_char(char c);

#endif