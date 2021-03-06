#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	bg1 = CCSprite::create("scene/scene_1.png");
	//bg1->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	bg1->setAnchorPoint(ccp(0,0));
	bg1->setPosition(ccp(0,0));
	this->addChild(bg1,0,0);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 2);

	CCMenuItemFont *item1 = CCMenuItemFont::create("LEFT", this, menu_selector(HelloWorld::menuCallbackHandle1));
	CCMenuItemFont *item2 = CCMenuItemFont::create("RIGHT", this, menu_selector(HelloWorld::menuCallbackHandle2));
	CCMenu* menu2 = CCMenu::create( item1, item2, NULL);
	menu2->alignItemsHorizontallyWithPadding(50);

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	addChild(menu2,2);
	menu2->setPosition(ccp(s.width/2, 20));

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("COOL RUN", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    mainSprite = CCSprite::create("role/role3.png");
	direction = 2;

    // position the sprite on the center of the screen
    mainSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-110));

	// add the sprite as a child to this layer
    this->addChild(mainSprite, 1);
	CCLOG ("%s \n", "come in action");
	setRoleState(0);
	CCLOG ("%s \n", "come out action");
	this->scheduleUpdate();
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::setRoleState(short dir)
{
	if(direction == dir)
	{
		return;
	}
	direction = dir;

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCLOG ("%s \n", "1 start addSpriteFramesWithFile");
	cache->addSpriteFramesWithFile("role/Role3_Auto_Run.plist", "role/Role3_Auto_Run.png");
		
	CCLOG ("%s \n", "2 addSpriteFramesWithFile");
	CCArray* animFrames = CCArray::createWithCapacity(14);
	char str[100] = {0};
	for(int i = 0; i < 14; i++)
	{
		sprintf(str, "Role3_Auto_Run%04d", i);
		CCSpriteFrame *frame = cache->spriteFrameByName(str);
			
		CCLOG ("%s \n", str);
		animFrames->addObject(frame);
	}

	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.05f);
	mainSprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	CCLOG ("%s \n", "runaction");
}

void HelloWorld::menuCallbackHandle1(CCObject *pSender)
{
	mainSprite->setFlipX(true);
	direction = 1;
}

void HelloWorld::menuCallbackHandle2(CCObject *pSender)
{
	mainSprite->setFlipX(false);
	direction = 0;
}


void HelloWorld::update(float dt)
{
	//�ж��Ƿ�Խ��
	CCLOG ("VisibleOrigin: %f \n", (CCDirector::sharedDirector()->getVisibleSize()).width);
	CCPoint point1 = mainSprite->convertToWorldSpace(mainSprite->getPosition());
	if(point1.x<0)
	{
		mainSprite->setFlipX(false);
		direction = 0;
	}
	else if(point1.x>2*(CCDirector::sharedDirector()->getVisibleSize()).width)
	{
		mainSprite->setFlipX(true);
		direction = 1;
	}

	if(direction == 0)
	{
		mainSprite->setPosition(ccp(mainSprite->getPositionX()+2, mainSprite->getPositionY()));
	}
	else if(direction == 1)
	{
		mainSprite->setPosition(ccp(mainSprite->getPositionX()-2, mainSprite->getPositionY()));
	}


}