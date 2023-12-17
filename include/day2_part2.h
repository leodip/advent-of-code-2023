typedef struct {
    int max_red;
    int max_green;
    int max_blue;
} max_colors;

max_colors get_max_colors(char *line);
int get_cube_count(char *line, char *color);