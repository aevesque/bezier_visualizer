#include "../include/cBezierVisualizer.h"

void	renderFrame(Context *context, TermGL termGL)
{
	uintVec3	control_points[context->control_point_count];

	for (int i = 0; i < context->control_point_count; ++i)
	{
		control_points[i] = toAbsolute(context->control_points[i], DISPLAY(termGL));
		setPixelZBuffered(control_points[i].x, control_points[i].y, ALWAYS_ON_TOP, (i == context->current_point ? SEL_POINT_COLOR : POINT_COLOR), DISPLAY(termGL));
	}

	for (float t = 0; t < 1; t += context->step)
	{
		const fVec3	p = nBezier(control_points, context->control_point_count, t);
		setPixel(p.x, p.y, LINE_COLOR, DISPLAY(termGL));
	}
}

int main(void)
{
	TermGL	termGL = termGLInit(50, 50);
	Context context = {
		.control_points = calloc(sizeof(fVec3), 2),
		.control_point_count = 2,
		.step = 0.01f,
	};

	setFramerate(10, termGL);
	registerInputHandler(inputHandler, &context, termGL);

	while (!context.should_quit)
	{
		renderFrame(&context, termGL);
		renderDisplay(termGL);
	}

	free(context.control_points);
	termGLDestroy(termGL);
}
