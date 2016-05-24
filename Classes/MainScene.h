#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__ 
#include "cocos2d.h"
#define WIDTH(node_ptr) (SIZE(node_ptr).width)
#define HEIGHT(node_ptr) (SIZE(node_ptr).height)
#define SCALED_WIDTH(node_ptr) (WIDTH(node_ptr) * node_ptr->getScaleX())
#define SCALED_HEIGHT(node_ptr) (HEIGHT(node_ptr) * node_ptr->getScaleY())
#define SIZE(node_ptr) (node_ptr->getContentSize())

class Main : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void menuOptionsCallback(cocos2d::Ref* pSender);
	void menuGameCallback(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Main);
};

#endif // __MAIN_SCENE_H__
