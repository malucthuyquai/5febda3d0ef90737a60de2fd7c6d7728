#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "cocos2d.h"

class Global : public cocos2d::Node
{
public:
    virtual bool init();
    
    static Global *sharedGlobal();
    static std::string encrypt(std::string str);
    static std::string decrypt(std::string str);
    
    static int level;
    static float score;
    static float total;
    static bool admobIsShow;
    static bool admobIsLoaded;
    static int admobHeight;
    static bool isIpad;
    
    static std::string flurryEventName;
    void postNotification(std::string notificationName);
    
    void submitScore();
    void showLeaderBoard();
    void shareFacebook(std::string path);
    int getWidth();
    int getHeight();
    
    cocos2d::__Array *textureArray;
    cocos2d::Animate* createAnimate(const char*plist, const char*frames, const char *name);
    
    CREATE_FUNC(Global);
};

std::string randomString(unsigned int len);
std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);



#endif /* defined(__EggSeed__Global__) */
