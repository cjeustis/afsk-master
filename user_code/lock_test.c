#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#define afsk_dir "/dev/afsk"

#define IOCTL_MAGIC 0xCE
#define IOCTL_SET _IOW(IOCTL_MAGIC, 1, char *)
#define IOCTL_GET _IOR(IOCTL_MAGIC, 2, char *)

int main(void)
{
	int fd;
	int status;
	pid_t pid;

	pid = fork();

	if (pid == -1) {
		perror("Fork failed\n");
		return -1;
	}

	if (pid == 0) {
		/* Open the device */
		fd = open(afsk_dir, O_WRONLY, 0777);
		if (fd < 0) {
			perror("Could not open file");
			return -1;
		}
		printf("fd(%d): %d\n", pid, fd);

		/* Write to the device */
		fd = write(fd, "This is a test string", 22);
		printf("fd(%d): %d\n", pid, fd);
		// if (fd < 0) {
			usleep(100000);
			/* Write to the device */
			// fd = write(fd, "This is a test string", 22);
		// }
		// printf("fd(%d): %d\n", pid, fd);
		close(fd);

		/* Open the device */
		fd = open(afsk_dir, O_WRONLY, 0777);
		if (fd < 0) {
			perror("Could not open file");
			return -1;
		}
		printf("fd(%d): %d\n", pid, fd);

		/* Get delim size */
		fd = ioctl(fd, IOCTL_GET, &status);
		if (fd == -1) {
			perror("IOCTL_GET failed");
		}
		printf("fd(%d): %d\n", pid, fd);

		close(fd);

		return 0;
	} else {
		/* Open the device */
		fd = open(afsk_dir, O_WRONLY, 0777);
		if (fd < 0) {
			perror("Could not open file");
			return -1;
		}
		printf("fd(%d): %d\n", pid, fd);

		/* Change delim size */
		fd = ioctl(fd, IOCTL_SET, 40);
		if (fd == -1) {
			perror("IOCTL_SET failed");
		}
		printf("fd(%d): %d\n", pid, fd);
		close(fd);

		/* Open the device */
		fd = open(afsk_dir, O_WRONLY, 0777);
		if (fd < 0) {
			perror("Could not open file");
			return -1;
		}
		printf("fd(%d): %d\n", pid, fd);

		/* Get delim size */
		fd = ioctl(fd, IOCTL_GET, &status);
		if (fd == -1) {
			perror("IOCTL_GET failed");
		}
		printf("fd(%d): %d\n", pid, fd);

		close(fd);

		return 0;
	}

	return 0;
}
