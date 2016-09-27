/*
 * Quick-and-dirty hack to set Linux console colors to something other than
 * the disgusting barf that comes "out of the box".
 */

#include <sys/ioctl.h>
#include <errno.h>
#include <stdio.h>          /* fprintf */
#include <stdlib.h>         /* strtol */
#include <stdint.h>         /* uint8_t */
#include <linux/kd.h>       /* PIO_CMAP */

static void usage()
{
    fprintf(stderr, "Usage: set-console-colors <rgbhex0> .. <rgbhex15>\n");
    exit(1);
}

int main(int argc, char **argv)
{
    long int rgb;
    uint8_t palette[48];
    uint8_t *p;
    int i;

    if (argc != 17)
        usage();

    p = palette;
    for (i = 0; i < 16; i++)
    {
        errno = 0;
        rgb = strtol(*++argv, NULL, 16);
        if (errno)
            usage();

        *p++ = (rgb >> 16) & 0xff;  /* red */
        *p++ = (rgb >>  8) & 0xff;  /* green */
        *p++ = (rgb      ) & 0xff;  /* blue */
    }
    ioctl(0, PIO_CMAP, palette);
}
