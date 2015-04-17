#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    cocos2d::Size size;
private:
    
    /* 跟随测试 */
    void testFollow();
    cocos2d::Sprite* getSprite(int tag);
    //跟随定时器
    void updateDrawNode(float dt);
    void updateFollow(float dt);
    
    /* 在一定范围内（矩形），返回一个点 */
    /* 在一定范围内（大矩形和小矩形），返回一个点 */
    /* 在一定范围内（矩形），返回一个点 与传入点有一定距离 */
    cocos2d::Vec2 getRandomPositionByMinLen(cocos2d::Vec2 anchor,cocos2d::Vec2 posNow,float w,float h,float len);
};

#endif // __HELLOWORLD_SCENE_H__
