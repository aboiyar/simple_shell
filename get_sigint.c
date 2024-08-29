#include "holberton.h"

/**
 * get_sigint - Handles the Crtl + C call in prompt
 * @sig: Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
