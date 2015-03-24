//
//  MainLayer.cpp
//  TweeJumpCocos2dx
//
//  Created by Carlos Pinan on 13/10/13.
//
//

#include "MainLayer.h"

using namespace cocos2d;

MainLayer::MainLayer()
{
    RANDOM_SEED();
    
    Sprite* background = Sprite::create("images/background.png");
    addChild(background);
    background->setPosition(Point(_W * 0.5f, _H * 0.5f));
    initClouds();
}

void MainLayer::initClouds()
{
    currentCloudTag = kCloudsStartTag;
    while(currentCloudTag < kCloudsStartTag + K_NUM_CLOUDS)
    {
        initCloud();
        currentCloudTag++;
    }
    resetClouds();
}

void MainLayer::initCloud()
{
    Rect rect;
    const char *name = "images/cloud1.png";
    switch((int) CCRANDOM_0_1() * 3)
    {
        case 0:
            rect = Rect(336, 16, 256, 108);
            name = "images/cloud1.png";
            break;
            
        case 1:
            rect = Rect(336, 128, 257, 110);
            name = "images/cloud1.png";
            break;
            
        case 2:
            rect = Rect(336, 240, 252, 119);
            name = "images/cloud1.png";
            break;
    }
    
    Sprite* cloud = Sprite::create(name);
    addChild(cloud, 3, currentCloudTag);
    cloud->setOpacity(128);
    
}

void MainLayer::resetClouds()
{
    currentCloudTag = kCloudsStartTag;
    while(currentCloudTag < kCloudsStartTag + K_NUM_CLOUDS)
    {
        resetCloud();
        
        Sprite* cloud = dynamic_cast<Sprite*>(getChildByTag(currentCloudTag));
        Point position = cloud->getPosition();
        position.y -= SCREEN_HEIGHT;
        cloud->setPosition(position);
        
        currentCloudTag++;
    }
}

void MainLayer::resetCloud()
{
    Sprite* cloud = dynamic_cast<Sprite*>(getChildByTag(currentCloudTag));
    
    float distance = CCRANDOM_0_1() * 20 + 5;
    float scale = 5.0f / distance;
    cloud->setScale(scale);
    
    if(CCRANDOM_0_1() * 2 == 1)
        cloud->setScaleX(-cloud->getScaleX());
    
    Size size = cloud->getContentSize();
    float scaled_width = size.width * scale;
    float x = CCRANDOM_0_1() * (SCREEN_WIDTH + (int) scaled_width) - scaled_width * 0.5f;
    float y = CCRANDOM_0_1() * (SCREEN_HEIGHT - (int) scaled_width) + scaled_width * 0.5f + SCREEN_HEIGHT;
    
    cloud->setPosition(Point(x, y));
    
    
}

void MainLayer::update(float dt)
{
    for(int cloudTag = kCloudsStartTag; cloudTag < kCloudsStartTag + K_NUM_CLOUDS; cloudTag++)
    {
        Sprite* cloud = dynamic_cast<Sprite*>(getChildByTag(cloudTag));
        Size size = cloud->getContentSize();
        Point position = cloud->getPosition();
        
        position.x += 0.5f * cloud->getScaleY();
        if(position.x > SCREEN_WIDTH + size.width * 0.5f)
            position.x = -size.width * 0.5f;
        cloud->setPosition(position);

    }
    
}



