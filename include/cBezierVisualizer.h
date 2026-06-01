#include "../termGL/include/termGL.h"

#ifndef C_BEZIER_VISUALIZER
# define C_BEZIER_VISUALIZER

# define MOVE_INCREMENT	0.1f
# define STEP_INCREMENT 0.01f
# define MIN_STEP	0.01f

# define LINE_COLOR	GREEN
# define POINT_COLOR	WHITE
# define SEL_POINT_COLOR	RED

fVec3	nBezier(const uintVec3 *control_points, const unsigned int control_point_count, const float t);

typedef struct {
	int	should_quit;
	int	current_point;
	fVec3	*control_points;
	int	control_point_count;
	float	step;
}	Context;

void	inputHandler(char keycode, void *v_context);
#endif
