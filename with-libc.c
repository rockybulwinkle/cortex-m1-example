#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "uart.h"


// LIBC SYSCALLS
/////////////////////

extern int _end;

void *_sbrk(int incr) {
  static unsigned char *heap = NULL;
  unsigned char *prev_heap;

  if (heap == NULL) {
    heap = (unsigned char *)&_end;
  }
  prev_heap = heap;

  heap += incr;

  return prev_heap;
}

int _close(int file) {
    (void)(file); //quiet gcc!
  return -1;
}

int _fstat(int file, struct stat *st) {
    (void)(file); //quiet gcc!
  st->st_mode = S_IFCHR;

  return 0;
}

int _isatty(int file) {
    (void)(file); //quiet gcc!
  return 1;
}

int _lseek(int file, int ptr, int dir) {
    (void)(file); //quiet gcc!
    (void)(ptr); //quiet gcc!
    (void)(dir); //quiet gcc!
  return 0;
}

void _exit(int status) {
    (void)(status); //quiet gcc!
  __asm("BKPT #0");
}

void _kill(int pid, int sig) {
    (void)(pid); //quiet gcc!
    (void)(sig); //quiet gcc!
  return;
}

int _getpid(void) {
  return -1;
}

int _write (int file, char * ptr, int len) {
  int written = 0;

  if ((file != 1) && (file != 2) && (file != 3)) {
    return -1;
  }

  for (; len != 0; --len) {
    //if (usart_serial_putchar(&stdio_uart_module, (uint8_t)*ptr++)) {
    //if (_putchar((uint8_t)*ptr++)) {
    putchar_uart0((uint8_t)*ptr++);
    ++written;
  }
  return written;
}

int _read (int file, char * ptr, int len) {
  int read = 0;

  if (file != 0) {
    return -1;
  }

  for (; len > 0; --len) {
    //usart_serial_getchar(&stdio_uart_module, (uint8_t *)ptr++);
    *ptr++=0;
    //read++;
  }
  return read;
}

