int main(int ac, char **av, char **env)
{
    int count;
    t_pipx *pipx;
    int *fork_id;
    int **pipe_id;
    int outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    int infile = open(av[1], O_RDONLY);

    if (ac > 4)
    {
        count = 0;
        init_variables(&pipx, &fork_id, &pipe_id, ac);
        init_pipx(pipx, ac);

        while (count < ac - 3)
        {
            pipx[count].pm = check_args(count, av, env, &pipx[count]);

            if (pipe(pipe_id[count]) == -1)
                return (perror("pipe\n"), 1);

            fork_id[count] = fork();
            if (fork_id[count] == -1)
            {
                perror("Fork");
                exit(EXIT_FAILURE);
            }

            if (fork_id[count] == 0) // Child process
            {
                // if (count != 0) // Not the first command
                // {
                //     dup2(pipe_id[count - 1][0], STDIN_FILENO);
                //     close(pipe_id[count - 1][0]);
                //     close(pipe_id[count - 1][1]);
                // }
                // else // First command
                // {
                //     dup2(pipx[0].infile, STDIN_FILENO);
                //     close(pipx[0].infile);
                // }

                // if (count != ac - 4) // Not the last command
                // {
                //     dup2(pipe_id[count][1], STDOUT_FILENO);
				// 	close(pipe_id[count][0]);
                // 	close(pipe_id[count][1]);
                // }
                // else // Last command
                // {
                //     dup2(pipx[0].outfile, STDOUT_FILENO);
                //     close(pipx[0].outfile);
                // }
                close(pipe_id[count][0]);
                close(pipe_id[count][1]);

                if (execve(ft_strjoin_p(pipx[count].cmd[pipx[count].pos], pipx[count].pm[0]), pipx[count].pm, env) == -1)
                {
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            }
            else // Parent process
            {
                if (count != 0)
                {
                    close(pipe_id[count - 1][0]);
                    close(pipe_id[count - 1][1]);
                }
                close(pipe_id[count][1]);

                count++;
            }
        }

        while (wait(NULL) > 0)
            ;

        close(outfile);
        close(infile);
    }
    exit(EXIT_FAILURE);
}
