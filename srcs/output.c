#include "../include/cBezierVisualizer.h"

static void	outputControlPoint(const int fd, Context *context)
{
	dprintf(fd, "Control points:\n");
	for (int i = 0; i < context->control_point_count; ++i)
		dprintf(fd, "\t%.4f, %.4f\n", context->control_points[i].x, context->control_points[i].y * -1);
		//changing the space from (-1, -1 is top left) to (1, -1 is bottom right)
}

static void	outputCurve(const int fd, Context *context)
{
	iVec3	control_points[context->control_point_count];

	Image	temp = initImage(100, 100);

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

void	generateOutput(const char *filename, Context *context)
{
	int	fd = open(filename, O_CREAT | O_WRONLY, 00644);

	if (fd < 0)
		return (printf("error: could not create or open %s\n", filename), (void)0);
	outputControlPoint(fd, context);
	outputCurve(fd, context);
	close(fd);
}
