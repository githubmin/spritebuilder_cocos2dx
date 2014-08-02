//
//  CCButtonLoader.cpp
//  cocos2d_libs
//
//  Created by LiuHuanMing on 8/1/14.
//
//

#include "CCButtonLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

namespace spritebuilder {
    
#define PROPERTY_ZOOMONTOUCHDOWN "zoomOnTouchDown"
#define PROPERTY_TITLE_NORMAL "title|1"
#define PROPERTY_TITLE_HIGHLIGHTED "title|2"
#define PROPERTY_TITLE_DISABLED "title|3"
#define PROPERTY_TITLECOLOR_NORMAL "titleColor|1"
#define PROPERTY_TITLECOLOR_HIGHLIGHTED "titleColor|2"
#define PROPERTY_TITLECOLOR_DISABLED "titleColor|3"
#define PROPERTY_TITLETTF_NORMAL "titleTTF|1"
#define PROPERTY_TITLETTF_HIGHLIGHTED "titleTTF|2"
#define PROPERTY_TITLETTF_DISABLED "titleTTF|3"
#define PROPERTY_TITLETTFSIZE_NORMAL "titleTTFSize|1"
#define PROPERTY_TITLETTFSIZE_HIGHLIGHTED "titleTTFSize|2"
#define PROPERTY_TITLETTFSIZE_DISABLED "titleTTFSize|3"
#define PROPERTY_LABELANCHORPOINT "labelAnchorPoint"
#define PROPERTY_PREFEREDSIZE "preferredSize" // TODO Should be "preferredSize". This is a typo in cocos2d-iphone, cocos2d-x and CocosBuilder!
#define PROPERTY_TITLE_FONTNAME "fontName"
#define PROPERTY_TITLE_FONTSIZE "fontSize"
#define PROPERTY_HORIZONTAL_PADDING "horizontalPadding"
#define PROPERTY_VERTICAL_PADDING "verticalPadding"
    
#define PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL "backgroundSpriteFrame|Normal"
#define PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED "backgroundSpriteFrame|Highlighted"
#define PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED "backgroundSpriteFrame|Disabled"
#define PROPERTY_BACKGROUNDSPRITEFRAME_SELECTED "backgroundSpriteFrame|Selected"
    
#define PROPERTY_LABELCOLOR_NORMAL    "labelColor|Normal"
#define PROPERTY_LABELCOLOR_HIGHLIGHTED     "labelColor|Highlighted"
#define PROPERTY_LABELCOLOR_DISABLED     "labelColor|Disabled"
    
#define PROPERTY_LABELCOLOR     "labelColor"
#define PROPERTY_OUTLINE_COLOR     "outlineColor"
#define PROPERTY_FONT_COLOR     "fontColor"
#define PROPERTY_OUTLINE_WIDTH     "outlineWidth"
#define PROPERTY_SHADOW_COLOR     "shadowColor"
    
#define PROPERTY_SHADOW_BLUR_RADIUS     "shadowBlurRadius"
    
#define PROPERTY_SHADOW_OFFSET     "shadowOffset"
#define PROPERTY_TITLE     "title"
    
#define PROPERTY_MAXSIZE "maxSize"
    
CCButton * CCButtonLoader::createNode(cocos2d::Node * pParent, CCBReader * ccbReader) {
    auto pRet = CCButton::create();
    return pRet;
}

void CCButtonLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_ZOOMONTOUCHDOWN) == 0) {
        ((CCButton *)pNode)->setZoomOnTouchDown(pCheck);
    } else {
        ControlLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, ccbReader);
    }
}

void CCButtonLoader::onHandlePropTypeString(Node * pNode, Node * pParent, const char * pPropertyName, const char * pString, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLE_NORMAL) == 0) {
        ((CCButton *)pNode)->setTitleForState(pString, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_HIGHLIGHTED) == 0) {
        ((CCButton *)pNode)->setTitleForState(pString, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_DISABLED) == 0) {
        ((CCButton *)pNode)->setTitleForState(pString, Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE) == 0) {
        ((CCButton *)pNode)->setTitleForState(pString, Control::State::NORMAL);
        ((CCButton *)pNode)->setTitleForState(pString, Control::State::HIGH_LIGHTED);
        ((CCButton *)pNode)->setTitleForState(pString, Control::State::DISABLED);
    } else {
        ControlLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, ccbReader);
    }
}

void CCButtonLoader::onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLETTF_NORMAL) == 0) {
        ((CCButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_HIGHLIGHTED) == 0) {
        ((CCButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_DISABLED) == 0) {
        ((CCButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::DISABLED);
        
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_FONTNAME) == 0) {
        ((CCButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::NORMAL);
        ((CCButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::HIGH_LIGHTED);
        ((CCButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::DISABLED);
    } else {
        ControlLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, ccbReader);
    }
}

void CCButtonLoader::onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_NORMAL) == 0) {
        ((CCButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_HIGHLIGHTED) == 0) {
        ((CCButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_DISABLED) == 0) {
        ((CCButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_FONTSIZE) == 0) {
        ((CCButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::NORMAL);
        ((CCButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::HIGH_LIGHTED);
        ((CCButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_HORIZONTAL_PADDING) == 0) {
//        ((CCButton *)pNode)->setHorizonPadding(pFloatScale);
    } else if(strcmp(pPropertyName, PROPERTY_VERTICAL_PADDING) == 0) {
//        ((CCButton *)pNode)->setVerticalPadding(pFloatScale);
    } else if(strcmp(pPropertyName, PROPERTY_OUTLINE_WIDTH) == 0) {
        _outlineWidth = pFloatScale;
    }  else if(strcmp(pPropertyName, PROPERTY_SHADOW_BLUR_RADIUS) == 0) {
        _shadowBlurRadius = pFloatScale;
    } else {
        ControlLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, ccbReader);
    }
}

void CCButtonLoader::onHandlePropTypePosition(cocos2d::Node * pNode,cocos2d:: Node * pParent, const char* pPropertyName, cocos2d::Point pPosition, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_SHADOW_OFFSET) == 0) {
        _shadowOffset = pPosition;
    } else {
        ControlLoader::onHandlePropTypePosition(pNode, pParent, pPropertyName, pPosition, ccbReader);
    }
}
void CCButtonLoader::onHandlePropTypePoint(Node * pNode, Node * pParent, const char * pPropertyName, Point pPoint, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_LABELANCHORPOINT) == 0) {
        ((CCButton *)pNode)->setLabelAnchorPoint(pPoint);
    } else {
        ControlLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, ccbReader);
    }
}

void CCButtonLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size pSize, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_PREFEREDSIZE) == 0) {
        ((CCButton *)pNode)->setPreferredSize(pSize);
    } else if(strcmp(pPropertyName, PROPERTY_MAXSIZE) == 0) {
//        ((CCButton *)pNode)->setMaxSize(pSize);
    } else {
        ControlLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, ccbReader);
    }
}

void CCButtonLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL) == 0) {
        if(pSpriteFrame != NULL) {
            ((CCButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::NORMAL);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED) == 0) {
        if(pSpriteFrame != NULL) {
            ((CCButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::HIGH_LIGHTED);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED) == 0) {
        if(pSpriteFrame != NULL) {
            ((CCButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::DISABLED);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_SELECTED) == 0) {
        if(pSpriteFrame != NULL) {
            ((CCButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::SELECTED);
        }
    } else {
        ControlLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pSpriteFrame, ccbReader);
    }
}

void CCButtonLoader::onHandlePropTypeColor4(Node * pNode, Node * pParent, const char * pPropertyName, Color4F pColor4F, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_NORMAL) == 0) {
        ((CCButton *)pNode)->setTitleColorForState(COLOR4F_TO_COLOR3B(pColor4F), Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_HIGHLIGHTED) == 0) {
        ((CCButton *)pNode)->setTitleColorForState(COLOR4F_TO_COLOR3B(pColor4F), Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_DISABLED) == 0) {
        ((CCButton *)pNode)->setTitleColorForState(COLOR4F_TO_COLOR3B(pColor4F), Control::State::DISABLED);
        
    } else if(strcmp(pPropertyName, PROPERTY_LABELCOLOR_NORMAL) == 0) {
        ((CCButton *)pNode)-> setTitleColorForState(COLOR4F_TO_COLOR3B(pColor4F), Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_LABELCOLOR_HIGHLIGHTED) == 0) {
        ((CCButton *)pNode)-> setTitleColorForState(COLOR4F_TO_COLOR3B(pColor4F), Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_LABELCOLOR_DISABLED) == 0) {
        ((CCButton *)pNode)-> setTitleColorForState(COLOR4F_TO_COLOR3B(pColor4F), Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_LABELCOLOR) == 0) {
        ((CCButton *)pNode)->getTitleLabel()->setColor(COLOR4F_TO_COLOR3B(pColor4F));
    } else if(strcmp(pPropertyName, PROPERTY_OUTLINE_COLOR) == 0) {
        _outlineColor = pColor4F;
    } else if(strcmp(pPropertyName, PROPERTY_FONT_COLOR) == 0) {
        ((CCButton *)pNode)->setTitleColorForState(Color3B(pColor4F.r, pColor4F.g, pColor4F.b), Control::State::NORMAL);
        ((CCButton *)pNode)->setTitleColorForState(Color3B(pColor4F.r, pColor4F.g, pColor4F.b), Control::State::HIGH_LIGHTED);
        ((CCButton *)pNode)->setTitleColorForState(Color3B(pColor4F.r, pColor4F.g, pColor4F.b), Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_SHADOW_COLOR) == 0) {
        _shadowColor = pColor4F;
    } else {
        ControlLoader::onHandlePropTypeColor4(pNode, pParent, pPropertyName, pColor4F, ccbReader);
    }
}
    
void CCButtonLoader::onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * ccbReader)
{
    if (strcmp(pPropertyName, "horizontalAlignment") == 0) {
        
    } else if (strcmp(pPropertyName, "verticalAlignment") == 0) {
        
    } else {
        ControlLoader::onHandlePropTypeIntegerLabeled(pNode, pParent, pPropertyName, pIntegerLabeled, ccbReader);
    };
}
    
}

