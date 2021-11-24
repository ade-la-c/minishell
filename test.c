void	cmd_loop(t_data *data, t_cmd *cmd, int *i, int j)
{
	int	l;

	l = 0;
	while (data->progs[*i].av[l])
		l++;
	cmd[*i].arg = malloc(sizeof(char *) * (l + 1));
	if (!cmd[*i].arg)
		exit_error("malloc failed");
	cmd[*i].builtin = ft_strdup(data->progs[*i].av[0]);
	if (!(cmd[*i].builtin))
		exit_error("1 strdup failed");
	j = -1;
	while (data->progs[*i].av[++j])
	{
		cmd[*i].arg[j] = ft_strdup(data->progs[*i].av[j]);
		if (!cmd[*i].arg[j])
			exit_error("2 strdup failed");
	}
	cmd[*i].arg[j] = NULL;
	cmd[*i].fdin = data->progs[*i].fdin;
	cmd[*i].fdout = data->progs[*i].fdout;
	cmd[*i].pipe = 1;
	*i += 1;
}