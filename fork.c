#include "minishell.h"

// int main(void)
// {
// 	pid_t pid;
// 	int status;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("failed");
// 		exit(1);
// 	}
// 	if (pid == 0)
// 	{
//         // printf("child is running away  — my PID is %d\n", getpid());
// 		// kill(getpid(), SIGKILL);
// 		return (42);
// 	}

// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 	{
//         printf("child came back: %d\n", WEXITSTATUS(status));
// 	}
// 	else
// 	{
// 		printf("child got killed? and the status is %d\n", WEXITSTATUS(status));
// 	}
//     return (0);
// }


int main(void)
{

	char *input;
	input = readline("minishell$ ");
	char **args = ft_split(input, ' ');

    pid_t   pid;
    int     status;
    // char    *argv[] = {"/bin/ls", "-la", NULL};
    char    *envp[] = {NULL}; // empty env for now

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (1);
    }
    if (pid == 0)
    {
		if (strcmp(args[0], "ls") == 0 || strcmp(args[0], "/bin/ls") == 0)
		{
			// Child: replace ourselves with /bin/ls
			execve("/bin/ls", args, envp);
			// execve only returns if it FAILED
			perror("execve");
			return (127);
		}
    }
    // Parent: wait for ls to finish
    waitpid(pid, &status, 0);
    printf("ls exited with: %d\n", WEXITSTATUS(status));
	free (input);
    return (0);
}
