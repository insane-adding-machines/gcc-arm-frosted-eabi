/*
 * Stub version of waitpid.
 */

#include <errno.h>
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *stat_loc, int options)
{
  return sys_waitpid(pid, stat_loc, options);
}

