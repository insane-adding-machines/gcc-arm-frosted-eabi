/*
 * Frosted version of lseek.
 */

#include "syscall_table.h"
#include <errno.h>
extern int sys_seek(int fd, int offset, int  whence);

int lseek (int fd, int offset, int whence)
{
    return sys_seek(fd, offset, whence);
}
