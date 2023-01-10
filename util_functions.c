#include "cub.h"

void ft_puterrmsg(char *msg)
{
	int i;

	i = 0;
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (dstsize > 0)
	{
		while (i + 1 < (dstsize) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < (n - 1)) && (s1[i] == s2[i]) && (s1[i] || s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	if (str[i] == '\0' && c == '\0')
		return (&str[i]);
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i--;
	}
	return (NULL);
}

t_parse	*create_struct(void)
{
	t_parse *stc;

	stc = malloc(sizeof(t_parse *));
	if (!stc)
		stc = NULL;
	return (stc);
}

char	*create_array(int size)
{
	char	*tab;

	tab = malloc((sizeof(char) * size));
	if (!tab)
		tab = NULL;
	return (tab);
}

char	**create_2d_array(int size)
{
	char **tab;

	tab = malloc((sizeof(char *) * size));
	if(!tab)
		tab = NULL;
	return (tab);
}

int	file_name_checker(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (file[i] == '.')
		{
			if (ft_strncmp(&file[i + 1], "cub", 4) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	open_file(char *file)
{
	int fd;

	fd = open(file, O_RDWR);
	if (fd < 0)
	{
		printf("Error\n");
		ft_puterrmsg(file);
		ft_puterrmsg(": ");
		perror("");
		return (-1);
	}
	return (fd);
}