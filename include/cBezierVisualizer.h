#include "../termGL/include/termGL.h"

#include <fcntl.h>

#ifndef C_BEZIER_VISUALIZER
# define C_BEZIER_VISUALIZER

# define DEFAULT_FILENAME	"output"
typedef struct {
	char *filename;
}	Parsed;

int	parse(int argc, char **argv, Parsed *output);

# define STARTING_MOVE_RESOLUTION 0.01f
# define MIN_MOVE_RESOLUTION 0.0001f
# define MAX_MOVE_RESOLUTION 1.0f

# define STARTING_CURVE_RESOLUTION (1.0f / 100)
# define MIN_CURVE_RESOLUTION (1.0f / 1000)

# define LINE_COLOR	GREEN
# define POINT_COLOR	WHITE
# define SEL_POINT_COLOR	RED

fVec3	nBezier(const iVec3 *control_points, const unsigned int control_point_count, const float t);

typedef struct {
	int	should_quit;
	int	current_point;
	fVec3	*control_points;
	int	control_point_count;
	unsigned int	curve_point_count;
	float	curve_resolution;
	float	move_resolution;
}	Context;

void	inputHandler(char keycode, void *v_context);

void	displayGeneralInfo(Context *context, TermGL termGL);
void	displayPointInfo(Context *context, TermGL termGL);

void	generateOutput(const char *filename, Context *context);
#endif
