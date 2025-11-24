#include "rush02.h"

int	get_file_size(char *filename)
{
	int		fd;
	int		size;
	char	buf[1];

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	size = 0;
	while (read(fd, buf, 1))
		size++;
	close(fd);
	return (size);
}

char	*read_file(char *filename)
{
	int		fd;
	int		size;
	char	*content;

	size = get_file_size(filename);
	if (size == -1)
		return (NULL);
	content = (char *)malloc(sizeof(char) * (size + 1));
	if (!content)
		return (NULL);
	fd = open(filename, O_RDONLY);
	read(fd, content, size);
	content[size] = '\0';
	close(fd);
	return (content);
}

char	*get_val(char *str, int *i)
{
	int		j;
	char	*val;

	while (str[*i] == ' ')
		(*i)++;
	if (str[*i] == ':')
		(*i)++;
	while (str[*i] == ' ')
		(*i)++;
	j = *i;
	while (str[j] && str[j] != '\n')
		j++;
	val = (char *)malloc(sizeof(char) * (j - *i + 1));
	if (!val)
		return (NULL);
	j = 0;
	while (str[*i] && str[*i] != '\n' && str[*i] != '\r')
	{
		val[j] = str[*i];
		j++;
		(*i)++;
	}
	val[j] = '\0';
	if (str[*i] == '\r')
		(*i)++;
	return (val);
}

char	*get_key(char *str, int *i)
{
	int		j;
	char	*key;

	j = *i;
	while (str[j] >= '0' && str[j] <= '9')
		j++;
	key = (char *)malloc(sizeof(char) * (j - *i + 1));
	if (!key)
		return (NULL);
	j = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		key[j] = str[*i];
		j++;
		(*i)++;
	}
	key[j] = '\0';
	return (key);
}

void	swap_dict(t_dict *a, t_dict *b)
{
	t_dict	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	cmp_keys(char *s1, char *s2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 != len2)
		return (len1 - len2);
	return (ft_strcmp(s1, s2));
}

void	sort_dict(t_dict *dict)
{
	int	i;
	int	j;

	i = 0;
	while (dict[i].val)
	{
		j = i + 1;
		while (dict[j].val)
		{
			if (cmp_keys(dict[i].n, dict[j].n) > 0)
				swap_dict(&dict[i], &dict[j]);
			j++;
		}
		i++;
	}
}

t_dict	*parse_dict(char *filename)
{
	char	*content;
	t_dict	*dict;
	int		i;
	int		j;
	int		lines;

	content = read_file(filename);
	if (!content)
		return (NULL);
	lines = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
			lines++;
		i++;
	}
	dict = (t_dict *)malloc(sizeof(t_dict) * (lines + 2)); // +2 for safety/sentinel
	if (!dict)
		return (NULL);
	i = 0;
	j = 0;
	while (content[i])
	{
		while (content[i] == '\n')
			i++;
		if (!content[i])
			break ;
		dict[j].n = get_key(content, &i);
		dict[j].val = get_val(content, &i);
		j++;
	}
	dict[j].val = NULL;
	free(content);
	sort_dict(dict);
	return (dict);
}

void	free_dict(t_dict *dict)
{
	int	i;

	i = 0;
	while (dict[i].val)
	{
		free(dict[i].n);
		free(dict[i].val);
		i++;
	}
	free(dict);
}
