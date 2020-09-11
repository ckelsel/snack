#include <stdio.h>
#include <curses.h>

void init_game()
{
    initscr();
}

void game_loop()
{
}

void game_score()
{
    printf("game over\n");
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
