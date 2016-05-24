#include "MainScene.h"
#include "OptionScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* Main::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Main::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Main::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float height = visibleSize.height;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Main::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto closeMenu = Menu::create(closeItem, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu, 1);

    // Create menu items
    auto gameOptionInMenu = MenuItemImage::create(
                                           "play.png",
                                           "play2.png",
                                           CC_CALLBACK_1(Main::menuGameCallback, this));
    auto optionInMenu = MenuItemImage::create(
                                           "options.png",
                                           "options2.png",
                                           CC_CALLBACK_1(Main::menuOptionsCallback, this));
    float button_scale = (height / 5) / gameOptionInMenu->getContentSize().height;
    gameOptionInMenu->setScaleX(button_scale);
    gameOptionInMenu->setScaleY(button_scale);
    optionInMenu->setScaleX(button_scale);
    optionInMenu->setScaleY(button_scale);
	Vector<MenuItem*> menuItems;
	menuItems.pushBack(optionInMenu);
	menuItems.pushBack(gameOptionInMenu);
	auto menu = Menu::createWithArray(menuItems); 
    menu->alignItemsVerticallyWithPadding(20.0f);
    this->addChild(menu, 0);

    auto title = Sprite::create("title.png");
    float title_scale = (height / 7) / (HEIGHT(title));
    title->setScaleX(title_scale);
    title->setScaleY(title_scale);

    title->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - SCALED_HEIGHT(title) * 0.6));
    this->addChild(title);

    auto author = Label::createWithTTF("by Arjun Mukherjee", "fonts/Marker Felt.ttf", 36);
    author->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - SCALED_HEIGHT(title) * 1.3));
    this->addChild(author);

    return true;
}

void Main::menuGameCallback(Ref* pSender)
{
    auto newScene = Game::createScene();
    Director::getInstance()->replaceScene(newScene);
}
void Main::menuOptionsCallback(Ref* pSender)
{
    auto newScene = OptionList::createScene();
    Director::getInstance()->replaceScene(newScene);
}
void Main::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
