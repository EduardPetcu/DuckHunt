#include "lab_m1/Tema1/Tema1.h"
#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include "lab_m1/Tema1/Defines.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
using namespace m1;
// TODO: DE REPARAT fisierul de stats!
void Tema1::updateStats() {
    FILE* stats_file, * stats_file_write;
    string filename = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema1", "stats.txt");
    string filename_write = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema1", "stats");

    stats_file = fopen(filename.c_str(), "r");
    stats_file_write = fopen(filename_write.c_str(), "w");
    char buffer[1000];
    int score_printed = 0;
    float time_float = 0.0f;
    fscanf(stats_file, "%s = %d\n", buffer, &score_printed);
    if (score > score_printed) {
        fputs("highscore = ", stats_file_write);
        fprintf(stats_file_write, "%d\n", score);
    }
    else {
        fputs("highscore = ", stats_file_write);
        fprintf(stats_file_write, "%d\n", score_printed);
    }
    fscanf(stats_file, "%s = %d\n", buffer, &score_printed);
    fputs("ducks_killed_last_round = ", stats_file_write);
    fprintf(stats_file_write, "%d\n", duck_counter);
    
    fscanf(stats_file, "%s = %d\n", buffer, &score_printed);
    fputs("total_ducks_killed = ", stats_file_write);
    fprintf(stats_file_write, "%d\n", score_printed + duck_counter);

    fscanf(stats_file, "%s = %f\n", buffer, &time_float);
    fputs("time_spent_last_round = ", stats_file_write);
    fprintf(stats_file_write, "%.1f\n", timeSpent);

    fscanf(stats_file, "%s = %f\n", buffer, &time_float);
    fputs("total_time_spent = ", stats_file_write);
    fprintf(stats_file_write, "%.1f\n", time_float + timeSpent);

    fclose(stats_file);
    fclose(stats_file_write);
    std::remove(filename.c_str());
    std::rename(filename_write.c_str(), filename.c_str());
}

void Tema1::initStats() {
    FILE* stats_file;
    string filename = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema1", "stats.txt");
    stats_file = fopen(filename.c_str(), "r");
    fseek(stats_file, 12, SEEK_SET);
    fscanf(stats_file, "%d", &highscore);
    fclose(stats_file);
}