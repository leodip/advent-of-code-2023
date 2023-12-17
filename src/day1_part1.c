#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/day1_part1.h"

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

    while ((characters = getline(&line, &line_size, fp)) != -1)
    {
        calibration_number = get_calibration_number(line);
        line[strlen(line) - 1] = 0; // remove newline
        printf("Line: %s - calibration number %d;\n", line, calibration_number);
        total += calibration_number;
    }

    printf("\nTotal: %d\n\n", total);

    fclose(fp);
    free(line);

    printf("Bye.\n");
    return 0;
}

int get_calibration_number(char *line)
{
    int i = 0;
    int numbers[2] = {-1, -1};

    size_t string_length = strlen(line);

    for(int i = 0; i < string_length; i++)
    {
        if (isdigit(line[i]))
        {
            if (numbers[0] == -1)
            {
                numbers[0] = line[i] - '0';
            }
            else
            {
                numbers[1] = line[i] - '0';
            }
        }
    }

    if (numbers[0] == -1)
    {
        numbers[0] = 0;
    }

    if (numbers[1] == -1)
    {
        numbers[1] = numbers[0];
    }

    char calibration_number_str[2];
    sprintf(calibration_number_str, "%d%d", numbers[0], numbers[1]);
    return atoi(calibration_number_str);
}
