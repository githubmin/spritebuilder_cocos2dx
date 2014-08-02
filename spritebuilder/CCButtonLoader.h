//
//  CCButtonLoader.h
//  cocos2d_libs
//
//  Created by LiuHuanMing on 8/1/14.
//
//

#ifndef __cocos2d_libs__CCButtonLoader__
#define __cocos2d_libs__CCButtonLoader__

#include "CCControlLoader.h"
#include "extensions//GUI/CCControlExtension/CCControlButton.h"
#include "spritebuilder/CCButton.h"

namespace spritebuilder {

class CCButtonLoader : public ControlLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~CCButtonLoader() {};
    /**
     * @js NA
     * @lua NA
     */
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCButtonLoader, loader);
    
protected:
    
    virtual CCButton * createNode(cocos2d::Node * pParent, CCBReader * ccbReader);
    
    virtual void onHandlePropTypeCheck(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader);
    virtual void onHandlePropTypeString(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, const char * pString, CCBReader * ccbReader);
    virtual void onHandlePropTypeFontTTF(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * ccbReader);
    virtual void onHandlePropTypeFloatScale(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader);
    virtual void onHandlePropTypePoint(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Point pPoint, CCBReader * ccbReader);
    virtual void onHandlePropTypeSize(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Size pSize, CCBReader * ccbReader);
    virtual void onHandlePropTypeSpriteFrame(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::SpriteFrame * pSpriteFrame, CCBReader * ccbReader);
    virtual void onHandlePropTypeColor4(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Color4F pColor4F, CCBReader * ccbReader);
    virtual void onHandlePropTypePosition(cocos2d::Node * pNode,cocos2d:: Node * pParent, const char* pPropertyName, cocos2d::Point pPosition, CCBReader * ccbReader);
    virtual void onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * ccbReader);
    
protected:
    float   _outlineWidth;
    float   _shadowBlurRadius;
    cocos2d::Point _shadowOffset;
    cocos2d::Color4F _outlineColor;
    cocos2d::Color4F _shadowColor;
};

}

#endif /* defined(__cocos2d_libs__CCButtonLoader__) */
