#include "GameScene.h"
#include "MainScene.h"

USING_NS_CC;


#define WALL_COLOR Color4F(0.6f, 0.6f, 0.6f, 1)
#define WALL_HEIGHT 32
#define PADDLE_SIZE 40
#define BALL_SIZE SCALED_WIDTH(this->ball)
#define PADDLE_HEIGHT SCALED_HEIGHT(this->player1Paddle)

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
void Game::drawPaddles(float width, float height)
{
    this->player1Paddley = this->player2Paddley = height / 2;

    this->player1Paddle = Sprite::create("player1Paddle.png");
    this->player2Paddle = Sprite::create("player2Paddle.png");

    float scalePaddley = (height / 6) / HEIGHT(this->player1Paddle);
    this->player1Paddle->setScaleY(scalePaddley);
    this->player2Paddle->setScaleY(scalePaddley);

    this->addChild(this->player1Paddle);
    this->addChild(this->player2Paddle);
}
void Game::redrawPaddles(float width, float height)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float halfHeight = PADDLE_HEIGHT / 2;
    if (this->player1Paddley > height - WALL_HEIGHT - halfHeight)
    {
        this->player1Paddley = height - WALL_HEIGHT - halfHeight;
    }
    if (this->player2Paddley > height - WALL_HEIGHT - halfHeight)
    {
        this->player2Paddley = height - WALL_HEIGHT - halfHeight;
    }
    if (this->player1Paddley < WALL_HEIGHT + halfHeight)
    {
        this->player1Paddley = WALL_HEIGHT + halfHeight;
    }
    if (this->player2Paddley < WALL_HEIGHT + halfHeight)
    {
        this->player2Paddley = WALL_HEIGHT + halfHeight;
    }
    this->player1Paddle->setPosition(Vec2(origin.x + PADDLE_SIZE, origin.y + this->player1Paddley));
    this->player2Paddle->setPosition(Vec2(origin.x + width - PADDLE_SIZE, origin.y + this->player2Paddley));
}
void Game::drawWalls(float width, float height)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto top = DrawNode::create();
    Vec2 topVertices[] = 
    { 
        Vec2(origin.x + 0,      origin.y + height), 
        Vec2(origin.x + width,  origin.y + height), 
        Vec2(origin.x + width,  origin.y + height - WALL_HEIGHT), 
        Vec2(origin.x + 0,      origin.y + height - WALL_HEIGHT)
    };
    top->drawPolygon(topVertices, 4, WALL_COLOR, 0, WALL_COLOR);
    this->addChild(top);

    auto bottom = DrawNode::create();
    Vec2 bottomVertices[] = 
    { 
        Vec2(origin.x + 0,      origin.y + WALL_HEIGHT), 
        Vec2(origin.x + width,  origin.y + WALL_HEIGHT), 
        Vec2(origin.x + width,  origin.y + 0), 
        Vec2(origin.x + 0,      origin.y + 0)
    };
    bottom->drawPolygon(bottomVertices, 4, WALL_COLOR, 0, WALL_COLOR);
    this->addChild(bottom);
}
void Game::updateBall()
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float width = visibleSize.width;
    float height = visibleSize.height;

    float ball_top = this->yBallMove + (BALL_SIZE / 2);
    float ball_bottom = this->yBallMove - (BALL_SIZE / 2);
    float leftBall = this->xBallMove - (BALL_SIZE / 2);
    float rightBall = this->xBallMove + (BALL_SIZE / 2);

    if (ball_top >= height - WALL_HEIGHT ||
        ball_bottom <= WALL_HEIGHT)
    {
        int mag = this->dyBallMove > 0 ? 1 : -1;
        mag *= -1;

        this->dyBallMove = mag * (rand() % 10 + 95) / 100.0f * this->ballSpeed;
    }

    float left_of_left_paddle = PADDLE_SIZE - leftBall;
    bool in_line_lpaddle = abs(this->player1Paddley - yBallMove) < PADDLE_HEIGHT / 2 + BALL_SIZE / 2;
    if (left_of_left_paddle >= 0 && left_of_left_paddle < -this->dxBallMove && in_line_lpaddle)
    {
        this->dxBallMove = (rand() % 10 + 95) / 100.0f * this->ballSpeed;
    }

    float right_of_right_paddle = rightBall - (width - PADDLE_SIZE);
    bool in_line_rpaddle = abs(this->player2Paddley - yBallMove) < PADDLE_HEIGHT / 2 + BALL_SIZE / 2;
    if (right_of_right_paddle >= 0 && left_of_left_paddle < this->dxBallMove && in_line_rpaddle)
    {
        this->dxBallMove = -(rand() % 10 + 95) / 100.0f * this->ballSpeed;
    }

    if (rightBall < 0)
    {
        this->player2Score++;
        this->updateScore();
        this->resetBall();
    }
    else if (leftBall > width)
    {
        this->player1Score++;
        this->updateScore();
        this->resetBall();
    }

    this->xBallMove += this->dxBallMove;
    this->yBallMove += this->dyBallMove;
    this->ball->setPosition(Vec2(origin.x + this->xBallMove, origin.y + this->yBallMove));
}
void Game::resetBall()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float width = visibleSize.width;
    float height = visibleSize.height;

    this->xBallMove = width / 2;
    this->yBallMove = height / 2;

    int diff = UserDefault::getInstance()->getIntegerForKey("difficulty", 1);
    this->ballSpeed = diff * 1.5 + 2;

    this->dxBallMove = rand() % 2 ? this->ballSpeed : -this->ballSpeed;
    this->dyBallMove = (rand() % 2 ? this->ballSpeed : -this->ballSpeed);
}
void Game::updateScore()
{
    char tmp[32];
    sprintf(tmp, "Player 1 Score: %i", this->player1Score);
    this->label1->setString(std::string(tmp));

    auto b_str = std::string("Score: ");
    sprintf(tmp, "Player 2 Score: %i", this->player2Score);
    this->label2->setString(std::string(tmp));
}

void Game::update(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float width = visibleSize.width;
    float height = visibleSize.height;

    this->redrawPaddles(width, height);

    this->updateBall();
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float width = visibleSize.width;
    float height = visibleSize.height;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "Close1.png",
                                           "Close2.png",
                                           CC_CALLBACK_1(Game::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    this->drawWalls(width, height);
    this->drawPaddles(width, height);
    this->redrawPaddles(width, height);
    this->ball = Sprite::create("ball.png");
    float ball_scale = (width / 32) / (WIDTH(this->ball));
    this->ball->setScaleX(ball_scale);
    this->ball->setScaleY(ball_scale);
    this->addChild(this->ball);
    this->resetBall();
    this->updateBall();
    auto middleLine = Sprite::create("middleLine.png");
    middleLine->setPosition(Vec2(origin.x + width / 2, origin.y + height / 2));
    middleLine->setScaleY(height / middleLine->getContentSize().height);
    this->addChild(middleLine);
    this->label1 = Label::createWithTTF("A", "fonts/Marker Felt.ttf", 24);
    this->label1->setPosition(Vec2(width / 2 - 100,
        origin.y + height - WALL_HEIGHT - this->label1->getContentSize().height));
    this->addChild(this->label1, 1);
    this->label2 = Label::createWithTTF("B", "fonts/Marker Felt.ttf", 24);
    this->label2->setPosition(Vec2(width / 2 + 100,
        origin.y + height - WALL_HEIGHT - this->label2->getContentSize().height));
    this->addChild(this->label2, 1);
    this->updateScore();
    this->p1UP = Rect(origin.x,                    origin.y + height / 2,  origin.x + 150,     origin.y + height);
    this->p1DOWN = Rect(origin.x,                  origin.y,               origin.x + 150,     origin.y + height / 2);
    this->p2UP = Rect(origin.x + width - 150,      origin.y + height / 2,  origin.x + width,   origin.y + height);
    this->p2DOWN = Rect(origin.x + width - 150,    origin.y,               origin.x + width,   origin.y + height / 2);
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true); 
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        auto game = static_cast<Game*>(event->getCurrentTarget());
        Point location = game->convertToNodeSpace(touch->getLocation());
        float height = Director::getInstance()->getVisibleSize().height;

        if (game->p1UP.containsPoint(location))
        {
            game->player1Paddley += height / 15;
        }
        else if (game->p1DOWN.containsPoint(location))
        {
            game->player1Paddley -= height / 15;
        }
        else if (game->p2UP.containsPoint(location))
        {
            game->player2Paddley += height / 15;
        }
        else if (game->p2DOWN.containsPoint(location))
        {
            game->player2Paddley -= height / 15;
        }

        return false;
    };
    listener1->onTouchMoved = [](Touch* touch, Event* event){
    };
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    this->schedule(schedule_selector(Game::update));
    return true;
}
void Game::menuCloseCallback(Ref* pSender)
{
    auto newScene = Main::createScene();
    Director::getInstance()->replaceScene(newScene);
}
