#include "Base.h"
#include <cassert>
#include <cmath>

class Program : public Base
{
public:
    Program(void);
    virtual ~Program(void);

private:	

protected:
	virtual void createScene(void);
	virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual void createFrameListener(void);
	Ogre::Real mMove;            // The movement constant
	Ogre::Vector3 mDirection;    // Value to move in the correct direction
 
};