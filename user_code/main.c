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
	fd = open(afsk_dir, O_WRONLY, 0777);
	if (fd < 0) {
		perror("Could not open file");
		return -1;
	}

	printf("fd: %d\n");

	fd = ioctl(fd, IOCTL_SET, 20);
	if (fd == -1) {
		perror("IOCTL_SET failed");
	}

	printf("fd: %d\n", fd);

	close(fd);

	fd = open(afsk_dir, O_WRONLY, 0777);
	if (fd < 0) {
		perror("Could not open file");
		return -1;
	}

	printf("fd: %d\n", fd);

	fd = ioctl(fd, IOCTL_GET, &status);
	if (fd == -1) {
		perror("IOCTL_GET failed");
	}

	printf("fd: %d\n", fd);

	close(fd);

	return 0;
}
