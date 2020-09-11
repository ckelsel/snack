#include <stdio.h>
#include <curses.h>


#define MAP_WIDTH 40
#define MAP_HEIGHT 12

struct position {
    /* x坐标 */
    int x;

    /* y坐标 */
    int y;

    /* 字符,蛇头部#、身子* */
    char ch;
};

/* 贪吃蛇 */
struct position g_snack[MAP_WIDTH * MAP_HEIGHT];

/* 蛇的实际长度 */
int g_snack_length = 0;

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

/**
 * @brief 初始化贪吃蛇
 */
void init_snack()
{
    g_snack[0].x = 0;
    g_snack[0].y = 0;
    g_snack[0].ch ='*';

    g_snack[1].x = 0;
    g_snack[1].y = 1;
    g_snack[1].ch ='*';

    g_snack[2].x = 0;
    g_snack[2].y = 2;
    g_snack[2].ch ='*';

    g_snack[3].x = 0;
    g_snack[3].y = 3;
    g_snack[3].ch ='#';

    g_snack_length = 4;
}

/**
 * @brief 绘制贪吃蛇
 */
void draw_snack()
{
    for (int i = 0; i < g_snack_length; i++)
    {
        mvaddch(g_snack[i].x, g_snack[i].y, g_snack[i].ch);
    }
}

void init_game()
{
    initscr();

    /* 获取方向键 */
    keypad(stdscr, TRUE);

    /* 不回显 */
    noecho();

    draw_map();

    init_snack();

    draw_snack();
}

void game_loop()
{
    while (1)
    {
        int tail_x = g_snack[0].x;
        int tail_y = g_snack[0].y;

        // (x,y)
        // (0,0),(0,1),(0,2),(0,3)
        // (0,1),(0,2),(0,3)(0,3)
        // (0,1),(0,2),(0,3)(0,4)
        /* 移动蛇的身子，不包括头结点 */
        for (int i = 0; i < g_snack_length - 1; i++)
        {
            g_snack[i].x = g_snack[i+1].x;
            g_snack[i].y = g_snack[i+1].y;
        }

        int key = getch();
        switch (key)
        {
            /* 上 */
            case KEY_UP:
                g_snack[g_snack_length-1].x -= 1;
                break;

            /* 下 */
            case KEY_DOWN:
                g_snack[g_snack_length-1].x += 1;
                break;

            /* 左 */
            case KEY_LEFT:
                g_snack[g_snack_length-1].y -= 1;
                break;

            /* 右 */
            case KEY_RIGHT:
                g_snack[g_snack_length-1].y += 1;
                break;

            /* 退出 */
            case 'q':
                return;
                break;

            default:
                break;
        }

        // 清除蛇的尾巴
        mvaddch(tail_x, tail_y, ' ');

        draw_snack();
    }
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
