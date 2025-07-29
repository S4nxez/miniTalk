#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

enum
{
	READY,
	BUSY
}

void	Signal(int, void *, bool);
void	Kill(pid_t, int );
#endif