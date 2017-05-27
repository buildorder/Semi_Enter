#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termio.h>
#include <string.h>

int main()
{
	int fd, end;
	struct termios port;
	char buf[50];

	fd = open("/dev/ttyACM0", O_RDONLY);
	if ( fd < 0 )
	{
		perror("Port isn't open");
		return -1;
	}

	memset(&port, 0, sizeof(struct termios));
	port.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
	port.c_iflag = IGNPAR;
	port.c_oflag = 0;
	port.c_lflag = ICANON;

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&port);

	while(1)
	{
		end = read(fd, buf, 50);
		buf[end] = 0;
		printf("%s", buf);
	}

	return 0;
}
