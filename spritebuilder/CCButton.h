#ifndef __CCBUTTON_H__
#define __CCBUTTON_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "base/CCMap.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

namespace spritebuilder {

class CCButton : public Control
{
public:
    static CCButton* create();
    static CCButton* create(Sprite* sprite);
    static CCButton* create(Node* label, Sprite* backgroundSprite);
    static CCButton* create(const std::string& title, const std::string& fontName, float fontSize);
    
    virtual void needsLayout(void);
    
    virtual void setEnabled(bool enabled);
    virtual void setSelected(bool enabled);
    virtual void setHighlighted(bool enabled);
    
    bool isPushed() const { return _isPushed; }
    
    /**
     * Returns the title used for a state.
     *
     * @param state The state that uses the title. Possible values are described in
     * "CCControlState".
     *
     * @return The title for the specified state.
     */
    virtual std::string getTitleForState(State state);
    
    /**
     * Sets the title string to use for the specified state.
     * If a property is not specified for a state, the default is to use
     * the ButtonStateNormal value.
     *
     * @param title The title string to use for the specified state.
     * @param state The state that uses the specified title. The values are described
     * in "CCControlState".
     */
    virtual void setTitleForState(const std::string& title, State state);
    
    /**
     * Returns the title color used for a state.
     *
     * @param state The state that uses the specified color. The values are described
     * in "CCControlState".
     *
     * @return The color of the title for the specified state.
     */
    
    virtual Color3B getTitleColorForState(State state) const;
    
    /**
     * Sets the color of the title to use for the specified state.
     *
     * @param color The color of the title to use for the specified state.
     * @param state The state that uses the specified color. The values are described
     * in "CCControlState".
     */
    virtual void setTitleColorForState(const Color3B& color, State state);
    
    /**
     * Returns the title label used for a state.
     *
     * @param state The state that uses the title label. Possible values are described
     * in "CCControlState".
     */
    virtual Node* getTitleLabelForState(State state);
    
    /**
     * Sets the title label to use for the specified state.
     * If a property is not specified for a state, the default is to use
     * the ButtonStateNormal value.
     *
     * @param label The title label to use for the specified state.
     * @param state The state that uses the specified title. The values are described
     * in "CCControlState".
     */
    virtual void setTitleLabelForState(Node* label, State state);
    
    virtual void setTitleTTFForState(const std::string& fntFile, State state);
    virtual const std::string& getTitleTTFForState(State state);
    
    virtual void setTitleTTFSizeForState(float size, State state);
    virtual float getTitleTTFSizeForState(State state);
    
    /**
     * Sets the font of the label, changes the label to a BMFont if neccessary.
     * @param fntFile The name of the font to change to
     * @param state The state that uses the specified fntFile. The values are described
     * in "CCControlState".
     */
    virtual void setTitleBMFontForState(const std::string& fntFile, State state);
    virtual const std::string& getTitleBMFontForState(State state);
    
    /**
     * Returns the background sprite used for a state.
     *
     * @param state The state that uses the background sprite. Possible values are
     * described in "CCControlState".
     */
    virtual Sprite* getBackgroundSpriteForState(State state);
    
    /**
     * Sets the background sprite to use for the specified button state.
     *
     * @param sprite The background sprite to use for the specified state.
     * @param state The state that uses the specified image. The values are described
     * in "CCControlState".
     */
    virtual void setBackgroundSpriteForState(Sprite* sprite, State state);
    
    /**
     * Sets the background spriteFrame to use for the specified button state.
     *
     * @param spriteFrame The background spriteFrame to use for the specified state.
     * @param state The state that uses the specified image. The values are described
     * in "CCControlState".
     */
    virtual void setBackgroundSpriteFrameForState(SpriteFrame * spriteFrame, State state);
    
    // Overrides
    virtual bool onTouchBegan(Touch *touch, Event *event) override;
    virtual void onTouchMoved(Touch *touch, Event *event) override;
    virtual void onTouchEnded(Touch *touch, Event *event) override;
    virtual void onTouchCancelled(Touch *touch, Event *event) override;
    
    virtual void setOpacity(GLubyte var) override;
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
	virtual void setColor(const Color3B&) override;
    virtual void updateDisplayedColor(const Color3B& parentColor) override;
    
    const std::string& getCurrentTitle() const { return _currentTitle; };
    std::string getCurrentTitle() { return _currentTitle; };
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    CCButton();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~CCButton();
    
    virtual bool init() override;
    virtual bool initWithLabelAndBackgroundSprite(Node* label, Sprite* backgroundSprite);
    virtual bool initWithBackgroundSprite(Sprite* sprite);
    virtual bool initWithTitleAndFontNameAndFontSize(const std::string& title, const std::string& fontName, float fontSize);
    
protected:
    bool _isPushed;
    bool _parentInited;
    
    Point   m_pOldPos;
    bool    m_bMoved;
    
    /** The current title that is displayed on the button. */
    std::string _currentTitle;
    
    /** The current color used to display the title. */
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(Color3B, _currentTitleColor, CurrentTitleColor);
    
    /** The current title label. */
    CC_SYNTHESIZE_RETAIN(Node*, _titleLabel, TitleLabel);
    
    /** The current background sprite. */
    CC_SYNTHESIZE_RETAIN(Sprite*, _backgroundSprite, BackgroundSprite);
    
    /** The prefered size of the button, if label is larger it will be expanded. */
    CC_PROPERTY_PASS_BY_REF(Size, _preferredSize, PreferredSize);
    
    /** Adjust the button zooming on touchdown. Default value is YES. */
    CC_PROPERTY(bool, _zoomOnTouchDown, ZoomOnTouchDown);
    /** Scale ratio button on touchdown. Default value 1.1f */
    CC_SYNTHESIZE(float, _scaleRatio, ScaleRatio);
    
    CC_PROPERTY_PASS_BY_REF(Vec2, _labelAnchorPoint, LabelAnchorPoint);
    
    std::unordered_map<int, std::string> _titleDispatchTable;
    std::unordered_map<int, Color3B> _titleColorDispatchTable;
    
    Map<int, Node*> _titleLabelDispatchTable;
    Map<int, Sprite*> _backgroundSpriteDispatchTable;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(CCButton);
    
public:
    std::function<void(Ref*)> onTouchUpInside;
    
};


}

#endif