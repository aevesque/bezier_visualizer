#include "../include/cBezierVisualizer.h"

void	renderFrame(Context *context, TermGL termGL)
{
	iVec3	control_points[context->control_point_count];

	for (int i = 0; i < context->control_point_count; ++i)
	{
		control_points[i] = toAbsoluteUnbound(context->control_points[i], DISPLAY(termGL));
		if (control_points[i].x >= 0 && control_points[i].x < (int)getDisplayWidth(termGL) && control_points[i].y >= 0 && control_points[i].y < (int)getDisplayHeight(termGL))
			setPixelZBuffered(control_points[i].x, control_points[i].y, ALWAYS_ON_TOP, (i == context->current_point ? SEL_POINT_COLOR : POINT_COLOR), DISPLAY(termGL));
	}

	for (float t = 0; t < 1; t += context->curve_resolution)
	{
		const fVec3	p = nBezier(control_points, context->control_point_count, t);
		if ((int)p.x >= 0 && p.x < getDisplayWidth(termGL) && (int)p.y >= 0 && p.y < getDisplayHeight(termGL))
			setPixelZBuffered(p.x, p.y, ZBUF_MAX, LINE_COLOR, DISPLAY(termGL));
	}

	displayGeneralInfo(context, termGL);
	displayPointInfo(context, termGL);
}

void	outputControlPoint(Context *context)
{
	printf("Control points :\n");
	for (int i = 0; i < context->control_point_count; ++i)
		printf("\t%.4f, %.4f\n", context->control_points[i].x * -1, context->control_points[i].y * -1);
		//multiplying by * -1 changes the space from -1 - 1 (-1, -1 is top left) to 1 - -1 (-1, -1 is bottom right)
}

int main(void)
{
	TermGL	termGL = termGLInit(100, 100);
	Context context = {
		.control_points = calloc(2, sizeof(fVec3)),
		.control_point_count = 2,
		.curve_resolution = STARTING_CURVE_RESOLUTION,
		.curve_point_count = 1 / STARTING_CURVE_RESOLUTION,
		.move_resolution = STARTING_MOVE_RESOLUTION,
	};

	setFramerate(10, termGL);
	registerInputHandler(inputHandler, &context, termGL);

	while (!context.should_quit)
	{
		renderFrame(&context, termGL);
		renderDisplay(termGL);
	}

	outputControlPoint(&context);

	free(context.control_points);
	termGLDestroy(termGL);
	return (0);
}
