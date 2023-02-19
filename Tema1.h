#pragma once

#include "components/simple_scene.h"
#include "components/text_renderer.h"

#define MAX_DUCKS 6
#define NUMBER_OF_BUTTONS 3
#define NUMBER_OF_STATS   5
namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();
        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        
        void InitVariables();
        bool CheckAllDucks();
        void CreateMeshes();
        void RenderBackground();
        void RandomDuckEffect(int i);
        void CheckBonusEffects(int i);
        void NewColorLevel();
        void RenderInfo();
        void ResetVariables();
        void CheckKillingSpree(float time);
        bool RescaleDiamond(float time);
        void CheckMargins(float time);
        void CheckUpperMargin(float time);
        void SlowTimeEffect();
        void NewDucks();
        void BossFightHealthBar();
        void AngleAdjustment(int duckNumber);
        void RenderFreezeTime(float timeRemaining);
        void DuckMovement(float timeRemaining, int duckNumber);
        void DuckAnimation(float deltaTimeSeconds);
        void WingAnimation(float deltaTimeSeconds);
        void RandomMovement(float deltaTimeSeconds);
        void FlyAway(float deltaTimeSeconds);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void initStats();
        void initTimeVariables();
        void initSpeedVariables();
        void updateStats();
        void renderStats();
        void startingWindow();
        void statsWindow();
        void checkButtonType();
     protected:
        gfxc::TextRenderer* textRenderer;
        GLenum polygonMode = GL_FILL;
        const glm::vec3 kTextColor = NormalizedRGB(166, 172, 205);
        const glm::vec3 kBackgroundColor = NormalizedRGB(41, 45, 62);

        float cx, cy;
        bool flyAway = false, freezeTime = false, BIG_DUCK;
        bool deadDuck[MAX_DUCKS] = {false};
        glm::mat3 modelMatrix;
        glm::vec3 color[MAX_DUCKS], colorLevel, colorBackground, colorButton[NUMBER_OF_BUTTONS], colorBackButton;
        int marginX, marginY;
        float translateX, translateY;
        float scaleX, scaleY, bonusX, bonusY;
        float angleTurn[MAX_DUCKS];
        const float MOUSE_SPEED = 0.85f;
        float posXCursor, posYCursor;
        float diamondLength1, diamondLength2;
        float rotationWings;
        bool changeWingDirection;
        float posHeadX[MAX_DUCKS], posHeadY[MAX_DUCKS];
        float triangleSide, circleRadius, grassHeight, dirtHeight, barLength, barHeight, wireframeLength;
        float timeDuck, slowTime, lastBounce, changeDirection, flashTime, timeSpent, timeOnScreen;
        float duckSpeed, wingSpeed, reducedSpeed, wingTurnTime;
        int posXBossBar, posYBossBar, scalingFactor; // (scalingFactor is for boss health bar)
        float edgeBodyX, edgeBodyY, edgeWingX, edgeWingY, bossBarScaling;
        int numberOfLifes, Ammo, nrOfDucks, maxAmmo, randomAngle;
        int duck_counter;
        int score, highscore, killingSpree, scoreMultiplier, ducksOnScreen, bigDuckHP, ducksOnScreenCopy;
        bool isStarting, isStats;
        std::string buttonName[NUMBER_OF_BUTTONS];
        std::string textStatsToRender[NUMBER_OF_STATS];
    };
}   // namespace m1
