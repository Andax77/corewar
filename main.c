#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
	int		ret = 0;
	char	c = 0;
	int		fd = open(argv[1], O_RDONLY);
	while ((ret = read(fd, &c, 4)))
	{
		printf("%d - ret = %d\n", c, ret);
	}
	printf("%d\n", c);
	close(fd);
	return 0;
}
