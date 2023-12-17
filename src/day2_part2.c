#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>
#include "../include/day2_part2.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s input_file\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];
    printf("Reading from file: %s\n\n", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s\n", filename);
        exit(1);
    }

    ssize_t characters;
    char *line = NULL;
    size_t line_size = 0;

    int calibration_number = 0;
    int total = 0;

    int game = 0;
    while ((characters = getline(&line, &line_size, fp)) != -1)
    {   
        game++;        
        
        printf("%s", line);     

        max_colors max_colors = get_max_colors(line);

        printf("max_red: %d, max_green: %d, max_blue: %d\n", max_colors.max_red, max_colors.max_green, max_colors.max_blue);
        int power = max_colors.max_red * max_colors.max_green * max_colors.max_blue;
        printf("power: %d\n\n", power);

        total += power;
    }

    printf("Total: %d\n", total);

    fclose(fp);
    free(line);

    printf("Bye.\n");
    return 0;
}

max_colors get_max_colors(char *line)
{
    regex_t regex;
    int ret_value;
    
    size_t max_groups = 2;
    regmatch_t group_array[max_groups];

    max_colors max_colors;
    max_colors.max_red = 0;
    max_colors.max_green = 0;
    max_colors.max_blue = 0;

    char *cubes_revealed_str = strstr(line, ": ");
    cubes_revealed_str += 2; // Skip past the ": "

    ret_value = regcomp(&regex, "([^;]+)", REG_EXTENDED);

    char *cursor = cubes_revealed_str;
    while (!regexec(&regex, cursor, max_groups, group_array, 0)) {
        int start = group_array[1].rm_so;
        int end = group_array[1].rm_eo;
        char match[strlen(cursor) + 1];
        strcpy(match, cursor);        
        match[group_array[1].rm_eo] = '\0';
        cursor += group_array[1].rm_eo;
        
        int cube_count_red = get_cube_count(match, "red");
        int cube_count_green = get_cube_count(match, "green");
        int cube_count_blue = get_cube_count(match, "blue");

        if(cube_count_red > max_colors.max_red) {
            max_colors.max_red = cube_count_red;
        }

        if(cube_count_green > max_colors.max_green) {
            max_colors.max_green = cube_count_green;
        }

        if(cube_count_blue > max_colors.max_blue) {
            max_colors.max_blue = cube_count_blue;
        }
    }

    regfree(&regex);
    return max_colors;
}

int get_cube_count(char *line, char *color)
{
    regex_t regex;
    int ret_value;

    size_t max_groups = 2;
    regmatch_t group_array[max_groups];

    char pattern [50];
    sprintf(pattern, "([[:digit:]]+)[[:space:]]%s", color);    

    ret_value = regcomp(&regex, pattern, REG_EXTENDED);
    ret_value = regexec(&regex, line, max_groups, group_array, 0);

    if(ret_value == REG_NOMATCH) {
        return 0;
    }
    char source_copy[strlen(line) + 1];
    strcpy(source_copy, line);
    source_copy[group_array[1].rm_eo] = 0;
    char *id_str = &source_copy[group_array[1].rm_so];

    regfree(&regex);
    return atoi(id_str);
}