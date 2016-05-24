#ifndef __OPTION_SCENE_H__
#define __OPTION_SCENE_H__ 

#include "cocos2d.h"

class OptionList : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuBackCallback(cocos2d::Ref *pSender);
	
    void menuDifficultyCallback(cocos2d::Ref *pSender);
    void changeDifficulty();

    // implement the "static node()" method manually
    CREATE_FUNC(OptionList);

private:
    cocos2d::MenuItemFont *difficulty_item;
};

#endif // __OPTIONLIST_SCENE_H__
