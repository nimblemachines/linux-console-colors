/*
 * Quick-and-dirty hack to get current Linux console colors and print them out.
 */

#include <sys/ioctl.h>
#include <stdio.h>          /* printf */
#include <stdint.h>         /* uint8_t */
#include <linux/kd.h>       /* GIO_CMAP */

int main(int argc, char **argv)
{
    uint8_t palette[48];
    uint8_t *p;
    uint8_t red, green, blue;
    int i;

    ioctl(0, GIO_CMAP, palette);

    p = palette;
    for (i = 0; i < 16; i++)
    {
        red = *p++;
        green = *p++;
        blue = *p++;
        printf("%02x%02x%02x ", red, green, blue);
    }
    printf("\n");
}
