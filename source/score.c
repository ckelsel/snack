#include "score.h"
#include <stdio.h>

#define SCORE_FILE "high_score"

void write_score(int score)
{
    // 分数创新高
    int old_score = read_score();
    if (old_score >= score)
    {
        return;
    }

    FILE *fp = fopen(SCORE_FILE, "w");
    if (fp)
    {
        fwrite(&score, 1, sizeof(score), fp);
        fclose(fp);
    }
}

int read_score()
{
    int score = 0;

    FILE *fp = fopen(SCORE_FILE, "r");
    if (fp)
    {
        fread(&score, 1, sizeof(score), fp);
        fclose(fp);
    }
    return score;
}
