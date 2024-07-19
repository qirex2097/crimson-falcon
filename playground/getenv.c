#include <libc.h>

// getenv関数を使って環境変数PATHから指定されたファイル名を探す
// :区切りで分割して、各ディレクトリにファイルがあるかどうかをaccess関数で確認
// ファイルが見つかればそのファイルのフルパスを返す
// 見つからなければNULLを返す

char	*serch_path(const char *filename)
{
	char	*path;
	char	*path_copy;

	path = getenv("PATH");
	path_copy = strdup(path);
    char *path_token = strtok(path_copy, ":");
	char *full_path = malloc(strlen(path_token) + strlen(filename) + 2); //+2 for '/' and '\0'
	
    if (!full_path)
	{
		free(path_copy);
		return (NULL);
	}
	while (path_token)
	{
		strcpy(full_path, path_token);
		strcat(full_path, "/");
		strcat(full_path, filename);
		if (access(full_path, F_OK) == 0) //F_OK : file exists
		{
			free(path_copy);
			return (full_path);
		}
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

int	main(void)
{
	char	*path;

	path = serch_path("pwd");
	printf("%s\n", path);
	free(path);
	return (0);
}
