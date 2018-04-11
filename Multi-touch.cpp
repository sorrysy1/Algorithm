#include "Multi-touch.h"

bool Multi-touch::init()
{

  m_listener = EventListenerTouchAllAtOnce::create();
	m_listener->onTouchesBegan = CC_CALLBACK_2(TKWorldMapLayer::onTouchesBegan, this);
	m_listener->onTouchesMoved = CC_CALLBACK_2(TKWorldMapLayer::onTouchesMoved, this);
	m_listener->onTouchesEnded = CC_CALLBACK_2(TKWorldMapLayer::onTouchesEnded, this);
	m_listener->onTouchesCancelled = CC_CALLBACK_2(TKWorldMapLayer::onTouchesCancelled, this);
	m_listener->setEnabled(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
  
  this->setContentSize(Size);
  
  return;
}

void Multi-touch::onTouchesBegan(const std::vector<cocos2d::Touch *>& touches, cocos2d::Event *event)
{
	for (auto i : touches)
	{
		i->retain();
		m_touches.pushBack(i);
	}

	if (m_touches.size() == 1)
	{
		auto touch = m_touches.begin();
		oneTouchBegan(*touch);
	}

	if (m_touches.size() >= 2)
	{
		m_isScale = true;
		return;
	}

	//for (ssize_t i = 0; i<MIN(2 - c, touches.size()); ++i) {
	//	m_touches.pushBack(touches[i]);
	//}
	//if (m_touches.size() == 2) 
	//{
	//	m_worldMap->setTouchEnabled(false);
	//}
}
void Multi-touch::onTouchesMoved(const std::vector<cocos2d::Touch *>& touches, cocos2d::Event *event)
{
	if (m_touches.size() == 1)
	{
		auto touch = m_touches.begin();
		oneTouchMoved(*touch);
	}

	if (m_touches.size() < 2)
		return;
	cocos2d::Vec2 lp1 = m_touches.at(0)->getPreviousLocationInView();
	cocos2d::Vec2 lp2 = m_touches.at(1)->getPreviousLocationInView();
	float ldis = lp1.getDistanceSq(lp2);

	cocos2d::Vec2 cp1 = m_touches.at(0)->getLocationInView();
	cocos2d::Vec2 cp2 = m_touches.at(1)->getLocationInView();
	float cdis = cp1.getDistanceSq(cp2);

	if (abs(ldis - cdis) > FLT_EPSILON) 
	{
		m_isScale = true;


		float scale = m_worldMap->getScale() * sqrtf(cdis / ldis);
		if (scale > 1.5f)
		{
			scale = 1.5f;
		}
		else if (scale < 0.52f)
		{
			scale = 0.52f;
		}
		float bef_scale = m_worldMap->getScale() ;

		float change = bef_scale - scale;

		m_worldMap->setScale(scale);

		Vec2 cur_pos = m_worldMap->getPosition();
		Vec2 mid_pos = Vec2(640, 360);
		Vec2 p = mid_pos - cur_pos;
		float num = 1;
		if (change > 0)
		{
			float n = bef_scale - 0.52f;
			num = change / n;
		}
		else
		{
			num = change ;
		}
		p = cur_pos + p * num;
		moveImg(m_worldMap, p);
	}
}

void Multi-touch::onTouchesEnded(const std::vector<cocos2d::Touch *>& touches, cocos2d::Event *event)
{
	if (m_touches.size() == 1)
	{
		auto touch = m_touches.begin();
		oneTouchEnded(*touch);
	}

	onTouchesCancelled(touches, event);

}

void Multi-touch::onTouchesCancelled(const std::vector<cocos2d::Touch *>& touches, cocos2d::Event *event)
{
	m_isScale = false;

	for (auto i : touches)
	{
		for (int j = m_touches.size() - 1; j >= 0; j--)
		{
			if (i == m_touches.at(j))
			{
				i->release();
				m_touches.erase(m_touches.begin() + j);
			}
		}
	}
}


bool Multi-touch::oneTouchBegan(Touch* touch)
{
	auto worldPoint = touch->getLocation();
	return true;
}

void Multi-touch::oneTouchMoved(Touch *touch)
{
	auto worldPoint = touch->getLocation();
}

void Multi-touch::oneTouchEnded(Touch *touch)
{
	auto worldPoint = touch->getLocation();
}

void Multi-touch::oneTouchCancelled(Touch *touch)
{
	oneTouchEnded(touch);
}
