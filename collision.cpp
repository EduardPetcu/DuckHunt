#include "lab_m1/Tema1/Tema1.h"
#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include "lab_m1/Tema1/Defines.h"

using namespace std;
using namespace m1;

// COLLISION: DUCK - WALL
void Tema1::CheckUpperMargin(float timeD) {

    // MARGINE SUS
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (posHeadY[i] + circleRadius > marginY) {
            angleTurn[i] = 2 * PI - angleTurn[i];
            lastBounce = timeD;
        }
    }
}
void Tema1::CheckMargins(float timeD) {

    if (timeD - lastBounce < EPS)
        return;
    if (!flyAway) {
        CheckUpperMargin(timeD);
    }
    // MARGINE DREAPTA
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (posHeadX[i] + circleRadius > marginX) {
            angleTurn[i] = PI - angleTurn[i];
            lastBounce = timeD;
        }
    }
    // MARGINE STANGA
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (posHeadX[i] < 0) {
            angleTurn[i] = PI - angleTurn[i];
            lastBounce = timeD;
        }
    }
    // MARGINE JOS
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (posHeadY[i] - circleRadius < 0) {
            angleTurn[i] = 2 * PI - angleTurn[i];
            lastBounce = timeD;
        }
    }
}

// COLLISION: DUCK - CURSOR
void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    for (int i = 0; i < NUMBER_OF_BUTTONS; ++i) {
        if (colorButton[i] == GREEN)
            checkButtonType();
    }
    if (Ammo <= 0)
        return;
    Ammo--;
    for (int i = 0; i < ducksOnScreen; ++i) {
        if ((posXCursor > posHeadX[i] - circleRadius && posXCursor < posHeadX[i] + circleRadius &&
            posYCursor > posHeadY[i] - circleRadius && posYCursor < posHeadY[i] + circleRadius)) {
            colorBackground = CRIMSON;
            flashTime = FLASH_TIME_LIMIT;
            if (BIG_DUCK) {
                bigDuckHP = bigDuckHP - BOSS_HEADSHOT_DAMAGE;
            }
            else {
                if (!deadDuck[i]) {
                    score = score + 50;
                    duck_counter++;
                }
                deadDuck[i] = true;
            }
            return;
        }
        // this works, trust me!
        if (((posXCursor >= posHeadX[i] - triangleSide / 2 - (2 * triangleSide) * cos(angleTurn[i]) && posXCursor <= posHeadX[i]) ||
            (posXCursor <= posHeadX[i] + triangleSide / 2 - (2 * triangleSide) * cos(angleTurn[i]) && posXCursor >= posHeadX[i])) &&
            ((posYCursor >= posHeadY[i] - triangleSide / 2 - (2 * triangleSide) * sin(angleTurn[i]) && posYCursor <= posHeadY[i]) ||
                (posYCursor <= posHeadY[i] + triangleSide / 2 - (2 * triangleSide) * sin(angleTurn[i]) && posYCursor >= posHeadY[i]))) {
            colorBackground = CRIMSON;
            flashTime = FLASH_TIME_LIMIT;
            if (BIG_DUCK) {
                bigDuckHP = bigDuckHP - BOSS_BODYSHOT_DAMAGE;
            }
            else {
                if (!deadDuck[i]) {
                    score = score + 50;
                    duck_counter++;
                }
                deadDuck[i] = true;
            }
            return;
        }
    }
}