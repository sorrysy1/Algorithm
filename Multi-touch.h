

class Multi-touch
{
public:
protected:
	bool init();
private:
	void onTouchesBegan(const std::vector<cocos2d::Touch *>& touches, cocos2d::Event *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch *>& touches, cocos2d::Event *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch *>& touches, cocos2d::Event *event);
	void onTouchesCancelled(const std::vector<cocos2d::Touch *>& touches, cocos2d::Event *event);

	bool oneTouchBegan(Touch* touch);
	void oneTouchMoved(Touch *touch);
	void oneTouchEnded(Touch *touch);
	void oneTouchCancelled(Touch *touch);
  
private:
  	cocos2d::EventListenerTouchAllAtOnce *m_listener;
	  cocos2d::Vector<cocos2d::Touch *> m_touches;
};
