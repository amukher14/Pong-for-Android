#include "MainScene.h"
#include "OptionScene.h"
USING_NS_CC;

Scene* OptionList::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OptionList::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OptionList::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    } 
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Options", "fonts/Marker Felt.ttf", 36);
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    this->difficulty_item = MenuItemFont::create("Difficulty", CC_CALLBACK_1(OptionList::menuDifficultyCallback, this));
    auto back_item = MenuItemFont::create("Back", CC_CALLBACK_1(OptionList::menuBackCallback, this));
    auto menu = Menu::create(difficulty_item, back_item, nullptr);
    menu->alignItemsVerticallyWithPadding(20.0f);
    this->addChild(menu, 0);
    
    this->changeDifficulty();
    return true;
}

void OptionList::changeDifficulty()
{
    int diff = UserDefault::getInstance()->getIntegerForKey("difficulty", 1);

    std::string diff_text = "";
    switch (diff)
    {
        case 1:
            diff_text = "Difficulty: Easy";
            break;
        case 2:
            diff_text = "Difficulty: Medium";
            break;
        case 3:
            diff_text = "Difficulty: Hard";
            break;
    }

    this->difficulty_item->setString(diff_text);
}

void OptionList::menuDifficultyCallback(Ref *pSender)
{
    int diff = UserDefault::getInstance()->getIntegerForKey("difficulty", 1);
    diff++;
    if (diff == 4)
    {
        diff = 1;
    }
    UserDefault::getInstance()->setIntegerForKey("difficulty", diff);

    this->changeDifficulty();
}

void OptionList::menuBackCallback(Ref *pSender)
{
    auto newScene = Main::createScene();
    Director::getInstance()->replaceScene(newScene);
}

void OptionList::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}