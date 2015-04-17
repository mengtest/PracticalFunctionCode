#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //获取大小
    size = Director::getInstance()->getVisibleSize();
    
    //设置背景
    auto background = LayerColor::create(Color4B(255, 255, 235, 255));
    addChild(background);

    //显示某个功能
    testFollow();
    
    return true;
}

//跟随测试
void HelloWorld::testFollow()
{
    auto hero = Sprite::create("res/CloseNormal.png");
    hero->setPosition(size.width / 2,size.height / 2 - 50);
    this->addChild(hero);
    hero->setTag(120110);
    
    auto follow = Sprite::create("res/CloseNormal.png");
    follow->setPosition(size.width / 2,size.height / 2);
    this->addChild(follow);
    follow->setTag(120111);
    
    follow->runAction(RepeatForever::create(RotateBy::create(1, 360)));
    
    auto drawNode = DrawNode::create();
    this->addChild(drawNode);
    drawNode->setTag(110110);
    
    this->schedule(schedule_selector(HelloWorld::updateDrawNode), 1.0f / 60);
    
    this->schedule(schedule_selector(HelloWorld::updateFollow), 1.0f / 60);
    
    float r = 80;
    
    //触屏
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [hero](Touch* touch,Event* event)
    {
        
        Vec2 pos = touch->getLocation();
        
        if (hero->boundingBox().containsPoint(pos))
        {
            
            return true;
        }
        
        return false;
    };
    
    listener->onTouchMoved = [hero,follow,r](Touch* touch,Event* event)
    {
        Vec2 pos= touch->getLocation();
        hero->setPosition(pos);
        
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::updateFollow(float dt)
{
    Vec2 hero_pos = getSprite(120110)->getPosition();
    Vec2 follow_pos = getSprite(120111)->getPosition();
    
    int r = 50;
    
    Vec2 tmp_pos = hero_pos + Vec2(0,r);
    float distance = tmp_pos.getDistance(follow_pos);
    
    float x = 0;
    float y = 0;
    
    float x1 = 0;
    float y1 = 0;
    
    Vec2 offest = tmp_pos - follow_pos;
    float radian = atanf(offest.y / offest.x);
    
    int f = 1;
    if (offest.x > 0)
    {
        f = -1;
    }
    
    if (distance >= r)
    {
        x = r *  f * cosf(radian);
        y = r *  f * sinf(radian);
        
        x1 = x = -x / 25;
        y1 = y = -y / 25;
        
        x1 = x1 / 2;
        y1 = y1 / 2;
        
        getSprite(120111)->runAction(Sequence::create(MoveBy::create(0.05,Vec2(x * 2, y * 2)),MoveBy::create(0.5,Vec2(x /2, y /2)),MoveBy::create(1.2,Vec2(x1, y1)), NULL));
    }
    
}

Sprite* HelloWorld::getSprite(int tag)
{
    return (Sprite*)this->getChildByTag(tag);
}

void HelloWorld::updateDrawNode(float dt)
{
    DrawNode* drawNode = (DrawNode*)this->getChildByTag(110110);
    
    drawNode->clear();
    
    drawNode->drawDot(getSprite(120110)->getPosition() + Vec2(0,50), 80, Color4F(100, 100, 0, 0.5));
    
    drawNode->drawDot(getSprite(120110)->getPosition() + Vec2(0,50), 3, Color4F(255, 255, 34, 1));
}



