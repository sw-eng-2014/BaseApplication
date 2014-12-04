#include "Program.h"
//-------------------------------------------------------------------------------------
Program::Program(void)
{
}
//-------------------------------------------------------------------------------------
Program::~Program(void)
{
}
//--------------------------------------------------------------------------------------
void Program::createScene(void)
{
		//Create penguin
		Ogre::Entity* entPenguin = mSceneMgr->createEntity("Penguin", "instrument_stick.mesh");
		entPenguin -> setCastShadows(true);
		Ogre::SceneNode* nodPenguin = mSceneMgr->getRootSceneNode()->createChildSceneNode("PenguinNode", Ogre::Vector3( 0, 20, 0 ));
		nodPenguin->scale( .1, .1, .1); 
		//nodPenguin->attachObject(entPenguin);
		Ogre::SceneNode* child = nodPenguin->createChildSceneNode("MoveNode");
		child->attachObject(entPenguin);
		child->translate(-150,0,0);
}
//-------------------------------------------------------------------------------------
//Creation of frame listner
 void Program::createFrameListener(void){
	mMove = 250;
 }
 //-------------------------------------------------------------------------------------
//Key pressed event
bool Program::keyPressed(const OIS::KeyEvent &arg){
	bool ret = Base::keyPressed(arg);

    return ret;
}

//-------------------------------------------------------------------------------------
//Key released event
bool Program::keyReleased(const OIS::KeyEvent &arg){
	bool ret = Base::keyReleased(arg);
	
	return ret;
}

bool Program::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	//Static variables 
	static bool mMouseDown = false;     // If a mouse button is depressed
	static Ogre::Real mRotate = 0.13;   // The rotate constant
	static Ogre::Real mMove = 250;      // The movement constant
	bool currMouse = mMouse->getMouseState().buttonDown(OIS::MB_Left);
	bool ret = Base::frameRenderingQueued(evt);

	Ogre::Vector3 transVector = Ogre::Vector3::ZERO;
	Ogre::Vector3 transVector2 = Ogre::Vector3::ZERO;
		if (mKeyboard->isKeyDown(OIS::KC_W)) // Forward
		{
			transVector.z -= mMove;
		}
		if (mKeyboard->isKeyDown(OIS::KC_S)) // Backward
		{
			transVector.z += mMove;
		}
		if (mKeyboard->isKeyDown(OIS::KC_A)) // Left - yaw or strafe
		{
			if(mKeyboard->isKeyDown( OIS::KC_LSHIFT ))
			{
				// Yaw left
				mSceneMgr->getSceneNode("PenguinNode")->roll(Ogre::Degree(mRotate * 5));
			} else {
				transVector.x -= mMove; // Strafe left
			}
		}
		if (mKeyboard->isKeyDown(OIS::KC_D)) // Right - yaw or strafe
		{
			if(mKeyboard->isKeyDown( OIS::KC_LSHIFT ))
			{
				// Yaw right
				mSceneMgr->getSceneNode("PenguinNode")->yaw(Ogre::Degree(-mRotate * 5));
			} else {
				transVector.x += mMove; // Strafe right
			}
		}
		if (mKeyboard->isKeyDown(OIS::KC_Z)) // Up
		{
			transVector.y += mMove;
		}
		if (mKeyboard->isKeyDown(OIS::KC_X)) // Down
		{
			transVector.y -= mMove;
		}
		if (mKeyboard->isKeyDown(OIS::KC_1)) // Change speed
		{
			mMove = 125;
			mRotate = 0.07;
		}
		if (mKeyboard->isKeyDown(OIS::KC_2)) // Change speed
		{
			mMove = 250;
			mRotate = 0.13;
		}
		if (mKeyboard->isKeyDown(OIS::KC_2)) // Change speed
		{
			mMove = 250;
			mRotate = 0.13;
		}
		if (mKeyboard->isKeyDown(OIS::KC_L)) // Forward
		{
			transVector2.x -= mMove;
		}
		if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
		{
			transVector2.x += mMove;
		}
		// Translate the results to the scenenode
		mSceneMgr->getSceneNode("MoveNode")->translate(transVector2 * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
		mSceneMgr->getSceneNode("PenguinNode")->translate(transVector * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	return ret;
}

//Ogre startup sequence 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int Program(int argc, char *argv[])
#endif
    {
        // Create application object
        Program app;
 
        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }
 
        return 0;
    }
 
#ifdef __cplusplus
}
#endif