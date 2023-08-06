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

const char USB_MOTD[BUF_SIZE] = "COMPSYS 301 Pathfinding Robot\n";

char USB_input[BUF_SIZE];
char USB_buffer[BUF_SIZE];

/**
 * @brief Get input from the terminal.
 *
 * @note - Turn echo `OFF`
 * @note - Use `CR` line endings
 *
 * @returns void The input string is made available in `USB_input`, and `flag_KB_string` is set.
 */
void USB_get_input(void);

/**
 * @brief Put a string to the terminal.
 *
 * @warning `string` must be C-string that has allocated space for at least 64 characters.
 *
 * @note The USB implementation restricts data packets to 64 characters, so this function truncates the length to 62 characters (where the 63rd character is a `'!'`).
 *
 * @param string The string to put to the terminal.
 */
void USB_put_string(char *string);

/**
 * @brief Put a character to the terminal.
 *
 * @param character The character to put to the terminal.
 */
void USB_put_char(char character);

#endif