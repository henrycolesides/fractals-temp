
// Square wave:
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "FPToolkit.c"

void builder(char source[], char dest[], char map[][10], int depth, const int max);
void square_wave(char string[]);
int main()
{
    char map[10][10] = {{0}};
    strcpy(map[0], "A");
    strcpy(map[1], "f+f+B");
    strcpy(map[2], "B");
    strcpy(map[3], "f-f-A");
    
    char source[1000] = {0};
    source[0] = 'A';

    char dest[1000] = {0};

    float swidth = 800;
    float sheight = 800;
    G_init_graphics(swidth, sheight);
    G_rgb(0, 0, 0);
    G_clear();

    builder(source, dest, map, 0, 10);
    G_wait_key();
}

void builder(char source[], char dest[], char map[][10], int depth, const int max)
{
    int dest_pos = 0;
    bool mapped = false;
    for(int i = 0; i < strlen(source); ++i)
    {
        mapped = false;
        char current[1] = {source[i]};
        for(int j = 0; j < 10; ++j)
        {
            if(strcmp(current, map[j]) == 0)
            {
                mapped = true;
                int new_len = strlen(map[j + 1]);
                for(int k = 0; k < new_len; ++k)
                {
                    dest[dest_pos] = map[j + 1][k];
                    ++dest_pos;
                }
            }
        }
        if(mapped == false)
        {
            dest[dest_pos] = source[i];
            ++dest_pos;
        }
    }
    
    printf("Source: %s\nDest: %s\n", source, dest);
    if(depth >= max)
    {
        square_wave(dest);
        return;
    }
    
    char new_dest[1000] = {'\0'};
    builder(dest, new_dest, map, depth + 1, max);
}

void square_wave(char string[])
{
    G_rgb(1.0, 1.0, 1.0);
    float p[2] = {10.0, 400.0};
    float p2[2];
    float angle = 3.14159 / 2.0;
    float distance = 40;
    float min[2] = {p[0], p[1]};
    float max[2] = {p[1], p[0]};

    for(int i = 0; i < strlen(string); ++i)
    {
        switch(string[i])
        {
            case 'f':
                p2[0] = p[0] + (cos(angle) * distance);
                p2[1] = p[1] + (sin(angle) * distance);

                if(p2[0] > max[0]) max[0] = p2[0];
                if(p2[1] > max[1]) max[1] = p2[1];

                if(p2[0] < min[0]) min[0] = p2[0];
                if(p2[1] < min[1]) min[1] = p2[1];

                break;
            case '+':
                angle -= 3.14159 / 2.0;
                break;
            case '-':
                angle += 3.14159 / 2.0;
                break;
            default:
                break;
        }
        p[0] = p2[0];
        p[1] = p2[1];
    }

    for(int i = 0; i < strlen(string); ++i)
    {
        switch(string[i])
        {
            case 'f':
                p2[0] = p[0] + (cos(angle) * distance);
                p2[1] = p[1] + (sin(angle) * distance);
                break;
            case '+':
                angle -= 3.14159 / 2.0;
                break;
            case '-':
                angle += 3.14159 / 2.0;
                break;
            default:
                break;
        }
        G_line(p[0], p[1], p2[0], p2[1]);
        p[0] = p2[0];
        p[1] = p2[1];
        G_wait_key();
}
                break;
            case '+':
                angle -= 3.14159 / 2.0;
                break;
            case '-':
                angle += 3.14159 / 2.0;
                break;
            default:
                break;
        }
        G_line(p[0], p[1], p2[0], p2[1]);
        p[0] = p2[0];
        p[1] = p2[1];
        G_wait_key();
    }
}
