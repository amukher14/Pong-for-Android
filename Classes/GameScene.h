#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class Game : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
     
    void update(float dt);
    void updateBall();

    // implement the "static create()" method manually
    CREATE_FUNC(Game);

private:
    void drawWalls(float width, float height);
    void drawPaddles(float width, float height);
    void redrawPaddles(float width, float height);
    void updateScore();
    void resetBall();

    cocos2d::Sprite *ball;
    float xBallMove;
    float yBallMove;
    float dxBallMove;
    float dyBallMove;
    float ballSpeed;

    cocos2d::Rect p1UP;
    cocos2d::Rect p1DOWN;
    cocos2d::Rect p2UP;
    cocos2d::Rect p2DOWN;
	
	cocos2d::Sprite *player1Paddle;
    cocos2d::Sprite *player2Paddle;
    int player1Paddley;
    int player2Paddley;

    cocos2d::Label *label1;
    cocos2d::Label *label2;
	int player1Score = 0;
    int player2Score = 0;
};

#endif // __GAME_SCENE_H__
