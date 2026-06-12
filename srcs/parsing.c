#include "../include/cBezierVisualizer.h"

static void	printHelp(void)
{
	printf("\t-o <file>: set <file> as the output file\n"
		"\t-s <number>: set <number> as both x and y output scale\n"
		"\t-x <number>: set <number> as the x output scale\n"
		"\t-y <number>: set <number> as the y output scale\n"
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

static int	setUniformScale(int argc, char **argv, int *argv_i, Parsed *output)
{
	if (*argv_i + 1 >= argc)
		return (printf("%s: missing scale. Usage : %s -s <number>.\n", argv[0], argv[0]), 1);

	const int scale = atoi(argv[*argv_i + 1]);

	if (!scale)
		return (printf("%s: missing or invalid scale. Usage : %s -s <number>.\n", argv[0], argv[0]), 1);
	output->scale[0] = scale;
	output->scale[1] = scale;
	*argv_i = *argv_i + 1;
	return (0);
}

static int	setScale(int argc, char **argv, int *argv_i, int *output, char opt)
{
	if (*argv_i + 1 >= argc)
		return (printf("%s: missing scale. Usage : %s -%c <number>.\n", argv[0], argv[0], opt), 1);

	const int scale = atoi(argv[*argv_i + 1]);

	if (!scale)
		return (printf("%s: missing or invalid scale. Usage : %s -%c <number>.\n", argv[0], argv[0], opt), 1);
	*output = scale;
	*argv_i = *argv_i + 1;
	return (0);
}

static int	parseOptions(int argc, char **argv, int *argv_i, Parsed *output)
{
	switch (argv[*argv_i][1]) {
		case 'h': return (printHelp(), 1);
		case 'o': return (setOutputFilename(argc, argv, argv_i, output));
		case 's': return (setUniformScale(argc, argv, argv_i, output));
		case 'x': return (setScale(argc, argv, argv_i, &output->scale[0], 'x'));
		case 'y': return (setScale(argc, argv, argv_i, &output->scale[1], 'y'));
		default:
			  return (printf("%s: invalid option : %s.\n", argv[0], argv[*argv_i]), 1);
	}
	return (0);
}

int	parse(int argc, char **argv, Parsed *output)
{
	*output = (Parsed) {
		.filename = DEFAULT_FILENAME,
		.scale = DEFAULT_SCALE,
	};

	for (int i = 1; i < argc; ++i)
		if (argv[i][0] != '-' || parseOptions(argc, argv, &i, output))
			return (1);
	return (0);
}
