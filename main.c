#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

int main()
{
    bool exit = false;
    do
    {
        system("clear");
        printf("Welcome to the file manager. Select an option:\n\n");
        printf("Current directory: ");
        fflush(stdout);
        system("pwd");
        system("ls -A | cat");
        printf("\n(1) Change directory\n");
        printf("(2) Create file\n");
        printf("(3) Create new directory\n");
        printf("(4) Delete a file\n");
        printf("(5) Delete a directory\n");
        printf("(6) Create a symbolic link\n");
        printf("(7) Change permissions\n");
        printf("(0) Exit program\n");
        printf("Option: ");
        int option;
        scanf("%i", &option);
        while (getchar() != '\n');
        char *new_item = NULL;
        ssize_t new_item_len;
        size_t new_item_size = 0;
        char *cmd;
        int result;
        switch (option)
        {
        case 0:
            exit = true;
            printf("Exiting...\n");
            break;
        case 1:
            printf("Change to directory: ");
            new_item_len = getline(&new_item, &new_item_size, stdin);
            new_item[new_item_len-1] = 0;
            new_item_len--;
            result = chdir(new_item);
            if (result)
            {
                printf("Error: %i \n", result);
            }
            else
            {
                printf("Successfully changed to directory '%s'\n", new_item);
            }
            free(new_item);
            break;
        case 2:
            printf("New file: ");
            new_item_len = getline(&new_item, &new_item_size, stdin);
            new_item[new_item_len-1] = 0;
            new_item_len--;
            cmd = malloc(9 + new_item_len);
            strcpy(cmd, "touch \"");
            strcat(cmd, new_item);
            strcat(cmd, "\"");
            result = system(cmd);
            if (result)
            {
                printf("Error: %i \n", result);
            }
            else
            {
                printf("File '%s' successfully created\n", new_item);
            }
            free(cmd);
            free(new_item);
            break;
        case 3:
            printf("New directory: ");
            new_item_len = getline(&new_item, &new_item_size, stdin);
            new_item[new_item_len-1] = 0;
            new_item_len--;
            cmd = malloc(9 + new_item_len);
            strcpy(cmd, "mkdir \"");
            strcat(cmd, new_item);
            strcat(cmd, "\"");
            result = system(cmd);
            if (result)
            {
                printf("Error: %i \n", result);
            }
            else
            {
                printf("Directory '%s' successfully created\n", new_item);
            }
            free(cmd);
            free(new_item);
            break;
        case 4:
            printf("File to delete: ");
            new_item_len = getline(&new_item, &new_item_size, stdin);
            new_item[new_item_len-1] = 0;
            new_item_len--;
            cmd = malloc(9 + new_item_len);
            strcpy(cmd, "rm -f \"");
            strcat(cmd, new_item);
            strcat(cmd, "\"");
            result = system(cmd);
            if (result)
            {
                printf("Error: %i \n", result);
            }
            else
            {
                printf("File '%s' successfully deleted\n", new_item);
            }
            free(cmd);
            free(new_item);
            break;
        case 5:
            printf("Directory to delete: ");
            new_item_len = getline(&new_item, &new_item_size, stdin);
            new_item[new_item_len-1] = 0;
            new_item_len--;
            cmd = malloc(10 + new_item_len);
            strcpy(cmd, "rm -rf \"");
            strcat(cmd, new_item);
            strcat(cmd, "\"");
            result = system(cmd);
            if (result)
            {
                printf("Error: %i \n", result);
            }
            else
            {
                printf("Directory '%s' and its contents successfully deleted\n", new_item);
            }
            free(cmd);
            free(new_item);

            break;
        case 6:
            printf("Item to link to: ");
            new_item_len = getline(&new_item, &new_item_size, stdin);
            new_item[new_item_len-1] = 0;
            new_item_len--;
            printf("Link location: ");
            char* new_link = NULL;
            size_t new_link_size = 0;
            ssize_t new_link_len = getline(&new_link, &new_link_size, stdin);
            new_link[new_link_len-1] = 0;
            new_link_len--;
            cmd = malloc(25 + new_item_len + new_link_len);
            strcpy(cmd, "ln -s \"`realpath \"");
            strcat(cmd, new_item);
            strcat(cmd, "\"`\" \"");
            strcat(cmd, new_link);
            strcat(cmd, "\"");
            result = system(cmd);
            if (result)
            {
                printf("Error: %i \n", result);
            }
            else
            {
                printf("Link '%s' successfully created\n", new_link);
            }
            free(cmd);
            free(new_item);
            free(new_link);
            break;
        case 7:
            printf("Item to change perms for: ");
            new_item_len = getline(&new_item, &new_item_size, stdin);
            new_item[new_item_len-1] = 0;
            new_item_len--;
            printf("Permissions: ");
            char* new_perms = NULL;
            size_t new_perms_size = 0;
            ssize_t new_perms_len = getline(&new_perms, &new_perms_size, stdin);
            new_perms[new_perms_len-1] = 0;
            new_perms_len--;
            cmd = malloc(12 + new_item_len + new_perms_len);
            strcpy(cmd, "chmod \"");
            strcat(cmd, new_perms);
            strcat(cmd, "\" \"");
            strcat(cmd, new_item);
            strcat(cmd, "\"");
            result = system(cmd);
            if (result)
            {
                printf("Error: %i \n", result);
            }
            else
            {
                printf("Permissions for file %s changed.\n", new_item);
            }
            free(cmd);
            free(new_item);
            free(new_perms);
            break;
        default:
            printf("Unknown option, please try again.\n");
            break;
        }
        if (!exit)
        {
            printf("Press enter to continue");
            getchar();
        }
    } while (!exit);
}