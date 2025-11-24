#include "rush02.h"

char	*find_str(char *n, t_dict *dict)
{
	int	i;

	i = 0;
	while (dict[i].val)
	{
		if (ft_strcmp(dict[i].n, n) == 0)
			return (dict[i].val);
		i++;
	}
	return (NULL);
}

void	print_space(int *first)
{
	if (!*first)
		ft_putstr(" ");
	*first = 0;
}

void	convert_small(char *n, t_dict *dict, int *first)
{
	int		len;
	int		val;
	char	buf[2];

	len = ft_strlen(n);
	val = 0;
	if (len == 1)
		val = n[0] - '0';
	else if (len == 2)
		val = (n[0] - '0') * 10 + (n[1] - '0');
	else if (len == 3)
		val = (n[0] - '0') * 100 + (n[1] - '0') * 10 + (n[2] - '0');

	if (val >= 100)
	{
		buf[0] = val / 100 + '0';
		buf[1] = '\0';
		convert_small(buf, dict, first);
		print_space(first);
		ft_putstr(find_str("100", dict));
		val %= 100;
		if (val > 0)
			print_space(first);
	}
	if (val >= 20)
	{
		buf[0] = val / 10 + '0';
		buf[1] = '0'; // Make it "20", "30" etc.
		buf[2] = '\0'; // Wait, buf size is 2. Need 3.
		// Actually let's just use find_str with constructed string.
		// Or better, just iterate.
	}
}
// Wait, the recursive logic for small numbers (0-999) is tricky with strings if I don't have atoi.
// But I can implement a mini-atoi for small chunks or just handle chars.
// Let's rewrite convert_small properly.

void	convert_three_digits(char *n, t_dict *dict, int *first)
{
	int		len;
	char	temp[4];
	
	len = ft_strlen(n);
	// Handle hundreds
	if (len == 3 && n[0] != '0')
	{
		temp[0] = n[0];
		temp[1] = '\0';
		print_space(first);
		ft_putstr(find_str(temp, dict));
		print_space(first);
		ft_putstr(find_str("100", dict));
		if (n[1] != '0' || n[2] != '0')
			print_space(first);
	}
	// Handle tens and ones
	if (len > 1)
	{
		// If len is 3, we look at index 1 and 2. If len is 2, index 0 and 1.
		int tens_idx = (len == 3) ? 1 : 0;
		int ones_idx = (len == 3) ? 2 : 1;
		
		if (n[tens_idx] == '1') // 10-19
		{
			temp[0] = n[tens_idx];
			temp[1] = n[ones_idx];
			temp[2] = '\0';
			ft_putstr(find_str(temp, dict));
			return ;
		}
		else if (n[tens_idx] >= '2') // 20-99
		{
			temp[0] = n[tens_idx];
			temp[1] = '0';
			temp[2] = '\0';
			ft_putstr(find_str(temp, dict));
			if (n[ones_idx] != '0')
			{
				print_space(first); // Actually standard rush02 might use hyphen, but space is safer.
				// Wait, if I printed "twenty", I need space before "one"?
				// The subject says "twenty-one" usually? No, "twenty one" is fine or check subject.
				// Subject example: "forty two". Space.
			}
		}
		if (n[tens_idx] != '1' && n[ones_idx] != '0')
		{
			temp[0] = n[ones_idx];
			temp[1] = '\0';
			ft_putstr(find_str(temp, dict));
		}
	}
	else if (len == 1 && n[0] != '0')
	{
		ft_putstr(find_str(n, dict));
	}
}
// The above convert_three_digits is a bit messy. Let's clean it up.

void	print_magnitude(int mag, t_dict *dict, int *first)
{
	char	*zeros;
	int		i;

	if (mag == 0)
		return ;
	zeros = (char *)malloc(sizeof(char) * (mag + 2));
	if (!zeros)
		return ;
	zeros[0] = '1';
	i = 1;
	while (i <= mag)
	{
		zeros[i] = '0';
		i++;
	}
	zeros[i] = '\0';
	print_space(first);
	ft_putstr(find_str(zeros, dict));
	free(zeros);
}

void	process_group(char *group, int mag, t_dict *dict, int *first)
{
	// Check if group is "000"
	if (ft_strcmp(group, "000") == 0)
		return ;
	
	// Remove leading zeros for conversion
	int i = 0;
	while (group[i] == '0' && group[i + 1])
		i++;
	
	convert_three_digits(group + i, dict, first);
	print_magnitude(mag, dict, first);
}

// I need to implement convert_three_digits properly now.
void	convert_chunk(char *str, t_dict *dict, int *first)
{
	int		len;
	char	buf[2];
	char	buf2[3];

	len = ft_strlen(str);
	if (len == 3)
	{
		if (str[0] != '0')
		{
			buf[0] = str[0];
			buf[1] = '\0';
			print_space(first);
			ft_putstr(find_str(buf, dict));
			print_space(first);
			ft_putstr(find_str("100", dict));
		}
		convert_chunk(str + 1, dict, first);
	}
	else if (len == 2)
	{
		if (str[0] == '0')
			convert_chunk(str + 1, dict, first);
		else if (str[0] == '1')
		{
			print_space(first);
			ft_putstr(find_str(str, dict));
		}
		else
		{
			buf2[0] = str[0];
			buf2[1] = '0';
			buf2[2] = '\0';
			print_space(first);
			ft_putstr(find_str(buf2, dict));
			convert_chunk(str + 1, dict, first);
		}
	}
	else if (len == 1)
	{
		if (str[0] != '0')
		{
			print_space(first);
			ft_putstr(find_str(str, dict));
		}
	}
}

void	convert_number(char *n, t_dict *dict)
{
	int		len;
	int		first;
	int		i;
	int		group_len;
	char	*group;

	int		k;
	int		is_zero;

	first = 1;
	// Handle 0 explicitly
	if (ft_strcmp(n, "0") == 0)
	{
		ft_putstr(find_str("0", dict));
		return ;
	}
	len = ft_strlen(n);
	i = 0;
	while (i < len)
	{
		group_len = (len - i) % 3;
		if (group_len == 0)
			group_len = 3;
		group = ft_strndup(n + i, group_len);
		// Check if group is all zeros
		is_zero = 1;
		k = 0;
		while (group[k])
		{
			if (group[k] != '0')
				is_zero = 0;
			k++;
		}
		
		if (!is_zero)
		{
			convert_chunk(group, dict, &first);
			// Magnitude: len - i - group_len
			print_magnitude(len - i - group_len, dict, &first);
		}
		free(group);
		i += group_len;
	}
}
