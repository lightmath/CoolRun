#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
public:

	short state;//0������1��Ծ��2����
	short direction;//0�ң�1��
	cocos2d::CCSprite *mainSprite;
	cocos2d::CCSprite *bg1;//������ͼ����

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	void setState(short var);
    
	void menuCallbackHandle1(CCObject *pSender);
	
	void menuCallbackHandle2(CCObject *pSender);

	void update(float dt);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
