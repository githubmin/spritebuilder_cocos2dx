#include "CCButton.h"

namespace spritebuilder {

enum
{
    kZoomActionTag = 0xCCCB0001,
};

CCButton::CCButton()
: _isPushed(false)
, _parentInited(false)
, _currentTitleColor(Color3B::WHITE)
, _titleLabel(nullptr)
, _backgroundSprite(nullptr)
, _zoomOnTouchDown(false)
, m_bMoved(false)
, m_pOldPos(Point())
, m_moveThreshold(kMoveThreshold)
, onTouchUpInside(nullptr)
{
    
}

CCButton::~CCButton()
{
    CC_SAFE_RELEASE(_titleLabel);
    CC_SAFE_RELEASE(_backgroundSprite);
}

//initialisers

bool CCButton::init()
{
    return this->initWithLabelAndBackgroundSprite(Label::createWithSystemFont("", "Helvetica", 12), Sprite::create());
}

bool CCButton::initWithLabelAndBackgroundSprite(Node* node, Sprite* backgroundSprite)
{
    if (Control::init())
    {
        CCASSERT(node != nullptr, "node must not be nil.");
        LabelProtocol* label = dynamic_cast<LabelProtocol*>(node);
        CCASSERT(backgroundSprite != nullptr, "Background sprite must not be nil.");
        CCASSERT(label != nullptr, "label must not be nil.");
        
        _parentInited = true;
        
        _isPushed = false;
        
        // Zooming button by default
        _zoomOnTouchDown = true;
        _scaleRatio = 1.1f;
        
        // Set the default anchor point
        ignoreAnchorPointForPosition(false);
        setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        
        // Set the nodes
        setTitleLabel(node);
        setBackgroundSprite(backgroundSprite);
        
        // Set the default color and opacity
        setColor(Color3B::WHITE);
        setOpacity(255.0f);
        setOpacityModifyRGB(true);
        
        // Initialize the dispatch table
        
        setTitleForState(label->getString(), Control::State::NORMAL);
        setTitleColorForState(node->getColor(), Control::State::NORMAL);
        setTitleLabelForState(node, Control::State::NORMAL);
        setBackgroundSpriteForState(backgroundSprite, Control::State::NORMAL);
        
        setLabelAnchorPoint(Vec2::ANCHOR_MIDDLE);
        
        // Layout update
        needsLayout();
        
        return true;
    }
    //couldn't init the Control
    else
    {
        return false;
    }
}

CCButton* CCButton::create(Node* label, Sprite* backgroundSprite)
{
    CCButton *pRet = new CCButton();
    pRet->initWithLabelAndBackgroundSprite(label, backgroundSprite);
    pRet->autorelease();
    return pRet;
}

bool CCButton::initWithTitleAndFontNameAndFontSize(const std::string& title, const std::string& fontName, float fontSize)
{
    return initWithLabelAndBackgroundSprite(Label::createWithSystemFont(title, fontName, fontSize), Sprite::create());
}

CCButton* CCButton::create(const std::string& title, const std::string& fontName, float fontSize)
{
    CCButton *pRet = new CCButton();
    pRet->initWithTitleAndFontNameAndFontSize(title, fontName, fontSize);
    pRet->autorelease();
    return pRet;
}

bool CCButton::initWithBackgroundSprite(Sprite* sprite)
{
    Label *label = Label::createWithSystemFont("", "Arial", 30);//
    return initWithLabelAndBackgroundSprite(label, sprite);
}

CCButton* CCButton::create(Sprite* sprite)
{
    CCButton *pRet = new CCButton();
    pRet->initWithBackgroundSprite(sprite);
    pRet->autorelease();
    return pRet;
}

void CCButton::setEnabled(bool enabled)
{
    Control::setEnabled(enabled);
    needsLayout();
}

void CCButton::setSelected(bool enabled)
{
    Control::setSelected(enabled);
    needsLayout();
}

void CCButton::setHighlighted(bool enabled)
{
    if (enabled == true)
    {
        _state = Control::State::HIGH_LIGHTED;
    }
    else
    {
        _state = Control::State::NORMAL;
    }
    
    Control::setHighlighted(enabled);
    
    Action *action = getActionByTag(kZoomActionTag);
    if (action)
    {
        stopAction(action);
    }
    needsLayout();
    if( _zoomOnTouchDown )
    {
        float scaleValue = (isHighlighted() && isEnabled() && !isSelected()) ? _scaleRatio : 1.0f;
        Action *zoomAction = ScaleTo::create(0.05f, scaleValue);
        zoomAction->setTag(kZoomActionTag);
        runAction(zoomAction);
    }
}

void CCButton::setZoomOnTouchDown(bool zoomOnTouchDown)
{
    _zoomOnTouchDown = zoomOnTouchDown;
}

bool CCButton::getZoomOnTouchDown()
{
    return _zoomOnTouchDown;
}

void CCButton::setPreferredSize(const Size& size)
{
    _preferredSize = size;
    needsLayout();
}

const Size& CCButton::getPreferredSize() const
{
    return _preferredSize;
}

const Vec2& CCButton::getLabelAnchorPoint() const
{
    return this->_labelAnchorPoint;
}

void CCButton::setLabelAnchorPoint(const Vec2& labelAnchorPoint)
{
    this->_labelAnchorPoint = labelAnchorPoint;
    if (_titleLabel != nullptr)
    {
        this->_titleLabel->setAnchorPoint(labelAnchorPoint);
    }
}

std::string CCButton::getTitleForState(State state)
{
    auto iter = _titleDispatchTable.find((int)state);
    if (iter != _titleDispatchTable.end())
    {
        return iter->second;
    }
    
    iter = _titleDispatchTable.find((int)Control::State::NORMAL);
    
    return iter != _titleDispatchTable.end() ? iter->second : "";
}

void CCButton::setTitleForState(const std::string& title, State state)
{
    _titleDispatchTable.erase((int)state);
    
    if (!title.empty())
    {
        _titleDispatchTable[(int)state] = title;
    }
    
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}


Color3B CCButton::getTitleColorForState(State state) const
{
    Color3B returnColor = Color3B::WHITE;
    
    auto iter = _titleColorDispatchTable.find((int)state);
    if (iter != _titleColorDispatchTable.end())
    {
        returnColor = iter->second;
    }
    else
    {
        iter = _titleColorDispatchTable.find((int)Control::State::NORMAL);
        if (iter != _titleColorDispatchTable.end())
        {
            returnColor = iter->second;
        }
    }
    
    return returnColor;
}

void CCButton::setTitleColorForState(const Color3B& color, State state)
{
    _titleColorDispatchTable.erase((int)state);
    _titleColorDispatchTable[(int)state] = color;
    
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

Node* CCButton::getTitleLabelForState(State state)
{
    Node* titleLabel = _titleLabelDispatchTable.at((int)state);
    if (titleLabel)
    {
        return titleLabel;
    }
    return _titleLabelDispatchTable.at((int)Control::State::NORMAL);
}

void CCButton::setTitleLabelForState(Node* titleLabel, State state)
{
    Node* previousLabel = _titleLabelDispatchTable.at((int)state);
    if (previousLabel)
    {
        removeChild(previousLabel, true);
        _titleLabelDispatchTable.erase((int)state);
    }
    
    _titleLabelDispatchTable.insert((int)state, titleLabel);
    titleLabel->setVisible(false);
    titleLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    addChild(titleLabel, 1);
    
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

void CCButton::setTitleTTFForState(const std::string& fontName, State state)
{
    this->setTitleLabelForState(Label::createWithSystemFont(getTitleForState(state), fontName, 12), state);
}

const std::string& CCButton::getTitleTTFForState(State state)
{
    LabelProtocol* label = dynamic_cast<LabelProtocol*>(this->getTitleLabelForState(state));
    Label* labelTTF = dynamic_cast<Label*>(label);
    if(labelTTF != 0)
    {
        return labelTTF->getSystemFontName();
    }
    
    static std::string ret("");
    return ret;
}

void CCButton::setTitleTTFSizeForState(float size, State state)
{
    LabelProtocol* label = dynamic_cast<LabelProtocol*>(this->getTitleLabelForState(state));
    if(label)
    {
        Label* labelTTF = dynamic_cast<Label*>(label);
        if(labelTTF != 0)
        {
            return labelTTF->setSystemFontSize(size);
        }
    }
}

float CCButton::getTitleTTFSizeForState(State state)
{
    LabelProtocol* label = dynamic_cast<LabelProtocol*>(this->getTitleLabelForState(state));
    Label* labelTTF = dynamic_cast<Label*>(label);
    if(labelTTF != 0)
    {
        return labelTTF->getSystemFontSize();
    }
    else
    {
        return 0;
    }
}

void CCButton::setTitleBMFontForState(const std::string& fntFile, State state)
{
    std::string title = this->getTitleForState(state);
    this->setTitleLabelForState(Label::createWithBMFont(fntFile, title), state);
}

const std::string& CCButton::getTitleBMFontForState(State state)
{
    LabelProtocol* label = dynamic_cast<LabelProtocol*>(this->getTitleLabelForState(state));
    auto labelBMFont = dynamic_cast<Label*>(label);
    if(labelBMFont != 0)
    {
        return labelBMFont->getBMFontFilePath();
    }
    
    static std::string ret("");
    return ret;
}


Sprite* CCButton::getBackgroundSpriteForState(State state)
{
    auto backgroundSprite = _backgroundSpriteDispatchTable.at((int)state);
    if (backgroundSprite)
    {
        return backgroundSprite;
    }
    return _backgroundSpriteDispatchTable.at((int)Control::State::NORMAL);
}


void CCButton::setBackgroundSpriteForState(Sprite* sprite, State state)
{
    auto previousBackgroundSprite = _backgroundSpriteDispatchTable.at((int)state);
    if (previousBackgroundSprite)
    {
        removeChild(previousBackgroundSprite, true);
        _backgroundSpriteDispatchTable.erase((int)state);
    }
    
    _backgroundSpriteDispatchTable.insert((int)state, sprite);
    sprite->setVisible(false);
    sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    addChild(sprite);
    
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

void CCButton::setBackgroundSpriteFrameForState(SpriteFrame * spriteFrame, State state)
{
    Sprite * sprite = Sprite::createWithSpriteFrame(spriteFrame);
    this->setBackgroundSpriteForState(sprite, state);
}


void CCButton::needsLayout()
{
    if (!_parentInited) {
        return;
    }
    // Hide the background and the label
    if (_titleLabel != nullptr) {
        _titleLabel->setVisible(false);
    }
    if (_backgroundSprite) {
        _backgroundSprite->setVisible(false);
    }
    // Update anchor of all labels
    this->setLabelAnchorPoint(this->_labelAnchorPoint);
    
    // Update the label to match with the current state
    _currentTitle = getTitleForState(_state);
    
    _currentTitleColor = getTitleColorForState(_state);
    
    this->setTitleLabel(getTitleLabelForState(_state));
    
    LabelProtocol* label = dynamic_cast<LabelProtocol*>(_titleLabel);
    if (label && !_currentTitle.empty())
    {
        label->setString(_currentTitle);
    }
    
    if (_titleLabel)
    {
        _titleLabel->setColor(_currentTitleColor);
    }
    if (_titleLabel != nullptr)
    {
        _titleLabel->setPosition(Vec2 (getContentSize().width / 2, getContentSize().height / 2));
    }
    
    // Update the background sprite
    this->setBackgroundSprite(this->getBackgroundSpriteForState(_state));
    if (_backgroundSprite != nullptr)
    {
        _backgroundSprite->setPosition(Vec2 (getContentSize().width / 2, getContentSize().height / 2));
    }
    
    // Get the title label size
    Size titleLabelSize;
    if (_titleLabel != nullptr)
    {
        titleLabelSize = _titleLabel->getBoundingBox().size;
    }
    
    // Set the content size
    Rect rectTitle;
    if (_titleLabel != nullptr)
    {
        rectTitle = _titleLabel->getBoundingBox();
    }
    Rect rectBackground;
    if (_backgroundSprite != nullptr)
    {
        rectBackground = _backgroundSprite->getBoundingBox();
    }
    
    Rect maxRect = ControlUtils::RectUnion(rectTitle, rectBackground);
    maxRect = ControlUtils::RectUnion(Rect(0, 0, _preferredSize.width, _preferredSize.height), maxRect);
    setContentSize(Size(maxRect.size.width, maxRect.size.height));
    
    if (_titleLabel != nullptr)
    {
        _titleLabel->setPosition(Vec2(getContentSize().width/2, getContentSize().height/2));
        // Make visible the background and the label
        _titleLabel->setVisible(true);
    }
    
    if (_backgroundSprite != nullptr)
    {
        _backgroundSprite->setPosition(Vec2(getContentSize().width/2, getContentSize().height/2));
        _backgroundSprite->setVisible(true);
    }
}

bool CCButton::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    if (!isTouchInside(pTouch) || !isEnabled() || !isVisible() || !hasVisibleParents() )
    {
        return false;
    }
    
    for (Node *c = this->_parent; c != nullptr; c = c->getParent())
    {
        if (c->isVisible() == false)
        {
            return false;
        }
    }
    
    _isPushed = true;
    this->setHighlighted(true);
    sendActionsForControlEvents(Control::EventType::TOUCH_DOWN);
    
    //TODO: parent is null
    m_pOldPos = getParent()->convertToWorldSpace(this->getPosition());
    m_bMoved = false;
    
    return true;
}

void CCButton::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    if (!isEnabled() || !isPushed() || isSelected())
    {
        if (isHighlighted())
        {
            setHighlighted(false);
        }
        return;
    }
    
    //TODO: parent is null
    Point p = getParent()->convertToWorldSpace(getPosition());
    if(fabsf(p.x - m_pOldPos.x) > m_moveThreshold ||
       fabsf(p.y - m_pOldPos.y) > m_moveThreshold) {
        m_bMoved = true;
    }
    
    bool isTouchMoveInside = isTouchInside(pTouch);
    if (isTouchMoveInside && !isHighlighted())
    {
        setHighlighted(true);
        sendActionsForControlEvents(Control::EventType::DRAG_ENTER);
    }
    else if (isTouchMoveInside && isHighlighted())
    {
        sendActionsForControlEvents(Control::EventType::DRAG_INSIDE);
    }
    else if (!isTouchMoveInside && isHighlighted())
    {
        setHighlighted(false);
        
        sendActionsForControlEvents(Control::EventType::DRAG_EXIT);
    }
    else if (!isTouchMoveInside && !isHighlighted())
    {
        sendActionsForControlEvents(Control::EventType::DRAG_OUTSIDE);
    }
}
void CCButton::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    _isPushed = false;
    setHighlighted(false);
    
    if (m_bMoved) {
        //send CCControlEventValueChanged for replace
        sendActionsForControlEvents(Control::EventType::VALUE_CHANGED);
        m_bMoved = false;
        return;
    }
    m_bMoved = false;
    
    if (isTouchInside(pTouch))
    {
        if (onTouchUpInside) {
            onTouchUpInside(this);
        }else {
            sendActionsForControlEvents(Control::EventType::TOUCH_UP_INSIDE);
        }
    }
    else
    {
        sendActionsForControlEvents(Control::EventType::TOUCH_UP_OUTSIDE);
    }
}

void CCButton::setOpacity(GLubyte opacity)
{
    Control::setOpacity(opacity);
    
    for (auto iter = _backgroundSpriteDispatchTable.begin(); iter != _backgroundSpriteDispatchTable.end(); ++iter)
    {
        iter->second->setOpacity(opacity);
    }
    
    for (auto iter = _titleLabelDispatchTable.begin(); iter != _titleLabelDispatchTable.end(); ++iter)
    {
        iter->second->setOpacity(opacity);
    }
}

void CCButton::updateDisplayedOpacity(GLubyte parentOpacity)
{
    Control::updateDisplayedOpacity(parentOpacity);
    
    for (auto iter = _backgroundSpriteDispatchTable.begin(); iter != _backgroundSpriteDispatchTable.end(); ++iter)
    {
        iter->second->updateDisplayedOpacity(parentOpacity);
    }
    
    for (auto iter = _titleLabelDispatchTable.begin(); iter != _titleLabelDispatchTable.end(); ++iter)
    {
        iter->second->updateDisplayedOpacity(parentOpacity);
    }
}

void CCButton::setColor(const Color3B & color)
{
	Control::setColor(color);
	
    for (auto iter = _backgroundSpriteDispatchTable.begin(); iter != _backgroundSpriteDispatchTable.end(); ++iter)
    {
        iter->second->setColor(color);
    }
    
    for (auto iter = _titleLabelDispatchTable.begin(); iter != _titleLabelDispatchTable.end(); ++iter)
    {
        iter->second->setColor(color);
    }
}

void CCButton::updateDisplayedColor(const Color3B& parentColor)
{
    Control::updateDisplayedColor(parentColor);
    
    for (auto iter = _backgroundSpriteDispatchTable.begin(); iter != _backgroundSpriteDispatchTable.end(); ++iter)
    {
        iter->second->updateDisplayedColor(parentColor);
    }
    
    for (auto iter = _titleLabelDispatchTable.begin(); iter != _titleLabelDispatchTable.end(); ++iter)
    {
        iter->second->updateDisplayedColor(parentColor);
    }
}

void CCButton::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
    _isPushed = false;
    setHighlighted(false);
    sendActionsForControlEvents(Control::EventType::TOUCH_CANCEL);
}

CCButton* CCButton::create()
{
    CCButton *pCCButton = new CCButton();
    if (pCCButton && pCCButton->init())
    {
        pCCButton->autorelease();
        return pCCButton;
    }
    CC_SAFE_DELETE(pCCButton);
    return nullptr;
}

}

