#ifndef ZTEST_IOCTL_H
#define ZTEST_IOCTL_H
#include <linux/ioctl.h>

#define ZTESTIO 'z'

#define ZTEST_GET_INFO  _IO(ZTESTIO, 0x00)

#endif