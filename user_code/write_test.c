#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#define afsk_dir "/dev/afsk"

#define IOCTL_MAGIC 0xCE
#define IOCTL_SET _IOW(IOCTL_MAGIC, 1, char *)
#define IOCTL_GET _IOR(IOCTL_MAGIC, 2, char *)

int main(void)
{
	int fd, status;
	char string[20] = "some lengthy string";

	fd = open(afsk_dir, O_WRONLY, 0777);
	if (fd < 0) {
		perror("Could not open file");
		return -1;
	}
	printf("open: %d\n");

	fd = write(fd, string, 20);
	if (fd == -1) {
		perror("write failed");
		return -1;
	}
	printf("wrote: %d\n", fd);

	close(fd);

	return 0;
}
