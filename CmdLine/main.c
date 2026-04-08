#include <stdio.h>
#include <string.h>
#include "cmd_line.h"


static int32_t cmd_help(uint8_t* argv);
static int32_t cmd_led(uint8_t* argv);


cmd_line_t cmd_table[] = {
    {(int8_t *)"help", cmd_help, (int8_t *)"Show help"},
    {(int8_t *)"led", cmd_led, (int8_t *)"Control LED"},
    {0, 0, 0}};

int32_t cmd_help(uint8_t *args)
{
    // printf("Available commands: help, led\n");
    printf("Available commands:\n");
    for (int i = 0; cmd_table[i].cmd != 0; i++)
    {
        printf("%s: %s\n", cmd_table[i].cmd, cmd_table[i].info);
    }
    return 0;
}

int32_t cmd_led(uint8_t *args)
{
    if (args)
        printf("LED command with arg:%s\n", args);
    else
        printf("LED command no arg\n");
    return 0;
}

int main(int argc, char const *argv[])
{
    uint8_t input[255];
    printf("CommandLineInterface (type 'exit' to quit)\n");
    while (1)
    {
        printf("> ");
        /* đọc input từ terminal */
        if (fgets((char *)input, sizeof(input), stdin) == NULL)
            continue;
        if (strcmp((char *)input, "exit\n") == 0)
            break;
        uint8_t ret = cmd_line_parser(cmd_table, input);
        /* handle result */
        if (ret == CMD_NOT_FOUND)
            printf("Command not found\n");
        else if (ret == CMD_TOO_LONG)
            printf("Command too long\n");
        else if (ret == CMD_TBL_NOT_FOUND)
            printf("Command table not found\n");
        else
            printf("Command executed successfully\n");
    }
    return 0;
}