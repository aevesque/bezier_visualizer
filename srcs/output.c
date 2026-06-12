#include "../include/cBezierVisualizer.h"

static void	outputHeader(const int fd, Context *context)
{
	dprintf(fd,
		"bezier curve created by bezierEV.\n"
		"%d control points\n"
		"%d curve points (%.4f fixed interpolation interval)\n"
		, context->control_point_count, context->curve_point_count, context->curve_resolution);
}

static void	outputControlPoint(const int fd, const int *scale, Context *context)
{
	dprintf(fd, "Control points:\n");
	for (int i = 0; i < context->control_point_count; ++i)
		dprintf(fd, "\t%.4f, %.4f\n", context->control_points[i].x * scale[0], context->control_points[i].y * -1 * scale[1]);
		//changing the space from (-1, -1 is top left) to (1, -1 is bottom right)
}

static void	outputCurve(const int fd, const int *scale, Context *context)
{
	iVec3	control_points[context->control_point_count];

	Image	temp = initImage(scale[0], scale[1]);

	for (int i = 0; i < context->control_point_count; ++i)
		control_points[i] = toAbsoluteUnbound(context->control_points[i], &temp);
	destroyImage(&temp);

	dprintf(fd, "\nCurve points:\n");

	for (float t = 0; t < 1; t += context->curve_resolution)
	{
		const fVec3	p = nBezier(control_points, context->control_point_count, t);
		dprintf(fd, "\t%.4f, %.4f\n", p.x, p.y * -1);
	}
}

void	generateOutput(Parsed *parsed, Context *context)
{
	int	fd = open(parsed->filename, O_CREAT | O_TRUNC | O_WRONLY , 00644);

	if (fd < 0)
		return (printf("error: could not create or open %s\n", parsed->filename), (void)0);
	outputHeader(fd, context);
	outputControlPoint(fd, parsed->scale, context);
	outputCurve(fd, parsed->scale, context);
	close(fd);
	printf("sucessfully created file '%s'.\n", parsed->filename);
}
