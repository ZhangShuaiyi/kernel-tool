#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include "ztest_ioctl.h"

#define DEV_NAME  "ztest"

static int ztest_open(struct inode *inodep, struct file *filep) {
    pr_debug("ztest device open\n");
    return 0;
}

static int ztest_close(struct inode *inodep, struct file *filep) {
    pr_debug("ztest device close\n");
    return 0;
}

static long ztest_ioctl(struct file *filep, unsigned int cmd, unsigned long arg) {
    switch (cmd) {
    case ZTEST_GET_INFO:
        pr_info("current task_struct %s [%d] start_code:0x%lx end_code:0x%lx\n",
                current->comm, current->pid, current->mm->start_code, current->mm->end_code);
        break;
    default:
        return -EINVAL;
    }
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = ztest_open,
    .release = ztest_close,
    .unlocked_ioctl = ztest_ioctl,
};

static struct miscdevice ztest_miscdevice = {
    .minor = MISC_DYNAMIC_MINOR,
    .fops = &fops,
};

static int __init ztest_init(void) {
    pr_debug("ztest module init\n");
    ztest_miscdevice.name = DEV_NAME;
    misc_register(&ztest_miscdevice);
    return 0;
}

static void __exit ztest_exit(void) {
    pr_debug("ztest module exit\n");
    misc_deregister(&ztest_miscdevice);
}

module_init(ztest_init);
module_exit(ztest_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZhangShuaiyi zhang_syi@163.com");
MODULE_DESCRIPTION("Linux module to get kernel info");
MODULE_VERSION("0.1");
