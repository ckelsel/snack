#include <stdio.h>
#include <curses.h>


#define MAP_WIDTH 40
#define MAP_HEIGHT 12

/**
 * @brief 绘制地图
 */
void draw_map()
{
    for (int i = 0; i < MAP_HEIGHT+1; i++)
    {
        // 绘制一行
        for (int j = 0; j < MAP_WIDTH +1; j++)
        {
            // 最后一行
            if (i == MAP_HEIGHT)
            {
                printw("-");
            }
            else
            {
                printw(" ");
            }

            if (j == MAP_WIDTH)
            {
                printw("|\n");
            }
        }
    }

    printw("Copyright (C) xie kunming\n");
    printw("2020-9-11\n");
}

void init_game()
{
    initscr();

    draw_map();
}

void game_loop()
{
    getch();
}

void game_score()
{
    endwin();
}

int main()
{
    /* 初始化游戏 */
    init_game();

    /* 游戏主循环 */
    game_loop();

    /* 游戏得分 */
    game_score();

    return 0;
}
