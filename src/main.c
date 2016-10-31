#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "ztest_ioctl.h"

#define DEVICE_FILE "/dev/ztest"

static void usage() {
    fprintf(stdout, "'p': get current task_struct info\n");
}

int main(int argc, char *argv[]) {
    int fd = 0;
    int opt = 0;
    char *short_opts = "p";
    /* opterr = 0; */

    if (argc == 1) {
        fprintf(stderr, "Need command line\n");
        usage();
        exit(EXIT_FAILURE);
    }
    fd = open(DEVICE_FILE, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while ((opt=getopt(argc, argv, short_opts)) != -1) {
        switch (opt) {
        case 'p':
            fprintf(stdout, "ioctl ZTEST_GET_INFO\n");
            if (ioctl(fd, ZTEST_GET_INFO, (unsigned long)0) == -1) {
                perror("ioctl ZTEST_GET_INFO");
            }
            break;
        default:
            usage();
        }
    }

    close(fd);
    return EXIT_SUCCESS;
}