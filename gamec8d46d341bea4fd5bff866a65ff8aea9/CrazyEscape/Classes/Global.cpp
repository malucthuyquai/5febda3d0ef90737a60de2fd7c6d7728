#include "Global.h"
#include "GameConfig.h"
#include "cocos2d.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //Android
#include "jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
void Global::submitScore() {
    cocos2d::JniMethodInfo minfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(minfo,  "mobi/smartad/beatmouse/BeatMouse","submitScore","(F)V")) {
        minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID, score);
    }
}
void Global::showLeaderBoard() {
    cocos2d::JniMethodInfo minfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(minfo,  "mobi/smartad/beatmouse/BeatMouse","showLeaderBoard","()V")) {
        minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
}
void Global::shareFacebook(std::string path) {
    cocos2d::JniMethodInfo minfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(minfo,  "mobi/smartad/beatmouse/BeatMouse","shareFacebook","(Ljava/lang/String;)V")) {
        jstring arg1 = minfo.env->NewStringUTF(path.c_str());
        minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID, arg1);
        minfo.env->DeleteLocalRef(minfo.classID);
        minfo.env->DeleteLocalRef(arg1);
    }
}
#endif  //Android
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) //IOS
void Global::submitScore() { CCLOG("submitscore"); }
void Global::showLeaderBoard() { CCLOG("showleaderboard"); }
void Global::shareFacebook(std::string path) { CCLOG("sharefacebook"); }
#endif //IOS

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ""abcdefghijklmnopqrstuvwxyz""0123456789";

static Global* _global;

Global* Global::sharedGlobal(){
    if (!_global) {
        _global = Global::create();
    }
    return _global;
}

bool Global::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCNode::init() )
    {
        return false;
    }
    admobIsShow = false;
    return true;
}

int Global::level;
float Global::score;
float Global::total;
bool Global::admobIsShow;
bool Global::admobIsLoaded;
int Global::admobHeight;
bool Global::isIpad;
std::string Global::flurryEventName;

cocos2d::Animate* Global::createAnimate(const char *plist, const char *frames, const char *name) {
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
    Animation *animation = Animation::create();
    animation->setDelayPerUnit(0.03f);
    std::string animationFramePrefix = name;
    std::string animationFrames = frames;
    char *strArr= new char[animationFrames.size()+1];
    strArr[animationFrames.size()]=0;
    memcpy(strArr,animationFrames.c_str(),animationFrames.size());
    const char* p;
    for (p = strtok(strArr, "," );  p;  p = strtok( NULL, "," )) {
        std::string frameName = animationFramePrefix + "_00000" + p + ".png";
        SpriteFrame* sprite =  SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName.c_str());
        animation->addSpriteFrame(sprite);
    }
    Animate *animationAction = Animate::create(animation);
    return animationAction;
}

void Global::postNotification(std::string notificationName) {
    notify->postNotification(notificationName.c_str());
}

int Global::getWidth() {
    return _W;
}

int Global::getHeight() {
    return _H;
}

std::string Global::encrypt(std::string str)
{
    std::string s = randomString(10);
    std::string tmp = s + str;
    tmp = base64_encode(reinterpret_cast<const unsigned char*>(tmp.c_str()), (int)tmp.length());
    return s + tmp;
}

std::string Global::decrypt(std::string str)
{
    if(str.length() <= 10) return str;
    std::string s = str.substr(10);
    s = base64_decode(s);
    return s.substr(10);
}

std::string randomString(unsigned int len) {
    std::string s = "";
    char *a=new char[base64_chars.size()+1];
    a[base64_chars.size()]=0;
    memcpy(a, base64_chars.c_str(), base64_chars.size());
    for (int i=0; i<len; i++) {
        s += a[arc4random() % base64_chars.size()];
    }
    return s;
}

static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            
            for(i = 0; (i <4) ; i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    if (i) {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];
        while((i++ < 3))
            ret += '=';
        
    }
    return ret;
}

std::string base64_decode(std::string const& encoded_string) {
    int in_len = (int)encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;
    while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);
            
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            
            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;
        for (j = 0; j <4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        
        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    return ret;
}



