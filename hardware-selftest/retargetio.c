#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rsl1000.h"

int fileno(FILE *);
int _close(int file);
int _fstat(int file, struct stat *st);
int _isatty(int file);
int _lseek(int file, int ptr, int dir);
int _read(int file, char *ptr, int len);
int _write(int file, const char *ptr, int len);

extern char _end;                 /**< Defined by the linker */


int _close(int file)
{
  (void) file;
  return 0;
}

void _exit(int status)
{
  (void) status;
  while (1) {
  }                 /* Hang here forever... */
}

int _fstat(int file, struct stat *st)
{
  (void) file;
  st->st_mode = S_IFCHR;
  return 0;
}

int _getpid(void)
{
  return 1;
}


int _isatty(int file)
{
  (void) file;
  return 1;
}


int _kill(int pid, int sig)
{
  (void)pid;
  (void)sig;
  return -1;
}


int _lseek(int file, int ptr, int dir)
{
  (void) file;
  (void) ptr;
  (void) dir;
  return 0;
}


int _read(int file, char *ptr, int len)
{
  int c, rxCount = 0;

  (void) file;

  RSL1000_UART->Receive(ptr, len);
  while(RSL1000_UART->GetRxCount() <= len);

  return rxCount;
}

int _write(int file, const char *ptr, int len)
{
  int txCount;

  (void) file;

  while(RSL1000_UART->GetStatus().tx_busy);
  RSL1000_UART->Send(ptr, len);

  return len;
}
