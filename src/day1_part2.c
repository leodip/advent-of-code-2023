#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/day1_part2.h"

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
    char first_digit = -1;
    char second_digit = -1;
    
    char *words[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *digits[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    
    int indexes_first_occurrence_words[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int indexes_first_occurrence_digits[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int indexes_last_occurrence_words[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int indexes_last_occurrence_digits[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    
    int i = 0;
    for (i = 0; i < 9; i++)
    {
        indexes_first_occurrence_words[i] = find_first_occurrence_of_substring(line, words[i]);
        indexes_first_occurrence_digits[i] = find_first_occurrence_of_substring(line, digits[i]);
        indexes_last_occurrence_words[i] = find_last_occurrence_of_substring(line, words[i]);
        indexes_last_occurrence_digits[i] = find_last_occurrence_of_substring(line, digits[i]);
    }

    int min_index = -1;    
    int max_index = -1;

    for (i = 0; i < 9; i++)
    {
        if (indexes_first_occurrence_words[i] != -1 && (min_index == -1 || indexes_first_occurrence_words[i] < min_index))
        {
            min_index = indexes_first_occurrence_words[i];
            first_digit = digits[i][0];
        }

        if (indexes_first_occurrence_digits[i] != -1 && (min_index == -1 || indexes_first_occurrence_digits[i] < min_index))
        {
            min_index = indexes_first_occurrence_digits[i];
            first_digit = digits[i][0];
        }

        if (indexes_last_occurrence_words[i] != -1 && (max_index == -1 || indexes_last_occurrence_words[i] > max_index))
        {
            max_index = indexes_last_occurrence_words[i];
            second_digit = digits[i][0];
        }

        if (indexes_last_occurrence_digits[i] != -1 && (max_index == -1 || indexes_last_occurrence_digits[i] > max_index))
        {
            max_index = indexes_last_occurrence_digits[i];
            second_digit = digits[i][0];
        }
    }
    
    char calibration_number_str[2];
    sprintf(calibration_number_str, "%c%c", first_digit, second_digit);
    return atoi(calibration_number_str);
}

int find_first_occurrence_of_substring(char *line, char *substring)
{
    char *p = strstr(line, substring);
    if (p)
    {
        int index = p - line;
        return index;
    }

    return -1;
}

int find_last_occurrence_of_substring(char *line, char *substring)
{
    char *ptr = line;
    char *last_ptr = NULL;

    while ((ptr = strstr(ptr, substring)) != NULL)
    {
        last_ptr = ptr;
        ptr++;
    }

    if (last_ptr)
    {
        int index = last_ptr - line;
        return index;
    }

    return -1;
}