/*
* Frosted version of sendto
*/


#include "syscall_table.h"
#include <sys/socket.h>
#include <errno.h>
extern int sys_sendto(int sd, const void *buf, unsigned int len, int flags, struct sockaddr_env *se);


ssize_t	sendto(int sd, const void *buf, size_t len, int flags, const struct sockaddr *sa, socklen_t socklen)
{
    struct sockaddr_env se;
    int ret;
    se.se_addr = sa;
    se.se_len = socklen;
    ret = sys_sendto(sd, buf, len, flags, &se);
    if (ret < 0) {
        errno = 0 - ret;
        ret = -1;
    }
    return ret;
}

ssize_t	send(int sd, const void *buf, size_t len, int flags)
{
    return sendto(sd, buf, len, flags, NULL, 0);
}
