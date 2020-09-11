#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define MAP_WIDTH 40
#define MAP_HEIGHT 12

/* 游戏得分 */
int g_score = 0;

struct position {
    /* x坐标 */
    int x;

    /* y坐标 */
    int y;

    /* 字符,蛇头部#、身子* */
    char ch;
};

/* 食物 */
struct position g_food;

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
    printw("Arrow Up,Down,Left,Right\n");
    printw("Press q to exit\n");
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

void init_food()
{
    g_food.x = rand() % MAP_HEIGHT;
    g_food.y = rand() % MAP_WIDTH;
    g_food.ch = '@';
}

void draw_food()
{
    mvaddch(g_food.x, g_food.y, g_food.ch);
}

void init_game()
{
    /* 随机数初始化 */
    srand((unsigned)time(NULL));

    initscr();

    /* 让getch不会阻塞 */
    nodelay(stdscr, TRUE);

    /* 获取方向键 */
    keypad(stdscr, TRUE);

    /* 不回显 */
    noecho();

    draw_map();

    init_snack();

    draw_snack();

    init_food();

    draw_food();
}

/**
 * @brief 贪吃蛇是否吃到自己
 *
 * @return -1吃到自己，0没有
 */
int eat_self()
{
    //4 a[3] a[2] a[1] a[0]
    for (int i = 0; i < g_snack_length - 1; i++)
    {
        if (g_snack[g_snack_length-1].x == g_snack[i].x
            && g_snack[g_snack_length-1].y == g_snack[i].y)
        {
            return -1;
        }
    }

    return 0;
}

void eat_food(int tail_x, int tail_y)
{
    // (0,1),(0,2),(0,3)  (0,4)
    // (0,2),(0,3),(0,4)
    // (0,2),(0,3),(0,4),(x,x)
    // (x,x),(0,2),(0,3),(0,4)
    // (0,1),(0,2),(0,3),(0,4)
    if (g_snack[g_snack_length-1].x == g_food.x
        && g_snack[g_snack_length-1].y == g_food.y)
    {
        g_snack_length += 1;

        for (int i = g_snack_length-1; i>0; i--)
        {
            g_snack[i].x = g_snack[i-1].x;
            g_snack[i].y = g_snack[i-1].y;
            g_snack[i].ch = g_snack[i-1].ch;
        }

        g_snack[0].x = tail_x;
        g_snack[0].y = tail_y;
        g_snack[0].ch = '*';

        draw_snack();


        /* 重新投喂食物 */
        init_food();
        draw_food();


        g_score += 10;
    }
}

/**
 * @brief 撞墙gg
 *
 * @return gg if return -1
 */
int hit_wall()
{
    if (g_snack[g_snack_length-1].x < 0
        || g_snack[g_snack_length-1].y < 0
        || g_snack[g_snack_length-1].x >= MAP_HEIGHT
        || g_snack[g_snack_length-1].y > MAP_WIDTH)
    {
        return -1;
    }

    return 0;
}

void game_loop()
{
    int last_key = KEY_RIGHT;

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
        if (key < 0)
        {
            key = last_key;
        }

        switch (key)
        {
            /* 上 */
            case KEY_UP:
                g_snack[g_snack_length-1].x -= 1;
                last_key = KEY_UP;
                break;

            /* 下 */
            case KEY_DOWN:
                g_snack[g_snack_length-1].x += 1;
                last_key = KEY_DOWN;
                break;

            /* 左 */
            case KEY_LEFT:
                g_snack[g_snack_length-1].y -= 1;
                last_key = KEY_LEFT;
                break;

            /* 右 */
            case KEY_RIGHT:
                g_snack[g_snack_length-1].y += 1;
                last_key = KEY_RIGHT;
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

        /* 吃食物 */
        eat_food(tail_x, tail_y);

        /* 吃到自己 */
        if (eat_self() < 0)
        {
            return;
        }

        /* 撞墙 */
        if (hit_wall() < 0)
        {
            return;
        }

        // 延时
        // 0 100ms
        // 10 90ms
        // 20 80ms
        usleep(100*1000 - g_score * 1000);
    }
}

void game_score()
{
    clear();
    printw("-----------------------------\n");
    printw(" Score: %d\n", g_score);
    printw("-----------------------------\n");
    printw("Press any key to exit\n");

    nodelay(stdscr, FALSE);
    getch();
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
