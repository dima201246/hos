#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <wait.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	pid_t	chpid	= fork();

	if (chpid == 0) {
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp(STDIN_FILENO, getpid());
		chdir("./");
		setpgid(getpid(), getpid());		// Создаём группу процессов

		if (execv("./hos_alpha", argv) < 0)
		{
			std::cout << "Ooooops... You crack it!" << std::endl;
		}

		return 0;
	}
	else
	{
		waitpid(chpid, NULL, WUNTRACED);
	}

	return 0;
}