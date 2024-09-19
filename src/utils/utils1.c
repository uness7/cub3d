# include "../../inc/cub3d.h"

static char	*get_file_extension(const char *file_path)
{
	char	*dot = ft_strrchr(file_path, '.');

	if (!dot || dot == file_path)
		return "" ;
	return (dot + 1) ;
}

bool	check_file_format(const char *file_path, char *format)
{
	char	*file_ext;

	file_ext = get_file_extension(file_path);
	if (ft_strncmp(file_ext, format, ft_strlen(file_ext)) == 0) 
		return (true);
	return (false);
}
