#include "../include/cBezierVisualizer.h"

static void	printHelp(void)
{
	printf("\t-o <file>: set <file> as the output file\n"
		"\t-h: display this help\n");
}

static int	setOutputFilename(int argc, char **argv, int *argv_i, Parsed *output)
{
	if (*argv_i + 1 >= argc)
		return (printf("%s: missing filename. Usage : %s -o <filename>.\n", argv[0], argv[0]), 1);
	output->filename = argv[*argv_i + 1];
	*argv_i = *argv_i + 1;
	return (0);
}

static int	parseOptions(int argc, char **argv, int *argv_i, Parsed *output)
{
	switch (argv[*argv_i][1]) {
		case 'h': return (printHelp(), 1);
		case 'o': return (setOutputFilename(argc, argv, argv_i, output));
		default:
			  return (printf("%s: invalid option : %s.\n", argv[0], argv[*argv_i]), 1);
	}
	return (0);
}

int	parse(int argc, char **argv, Parsed *output)
{
	*output = (Parsed) {
		.filename = DEFAULT_FILENAME,
	};

	for (int i = 1; i < argc; ++i)
		if (argv[i][0] != '-' || parseOptions(argc, argv, &i, output))
			return (1);
	return (0);
}
