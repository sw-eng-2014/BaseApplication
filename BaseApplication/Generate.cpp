#include "Generate.h"
 
//-------------------------------------------------------------------------------------
Generate::Generate(void)
{
}
//-------------------------------------------------------------------------------------
Generate::~Generate(void)
{
}
//--------------------------------------------------------------------------------------
void Generate::createScene(void)
{
	// Create the SceneManager, in this case a generic one
		mSceneMgr = mRoot->createSceneManager("DefaultSceneManager");
		//Set settings
		mSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

		//Create penguin
		Ogre::Entity* entPenguin = mSceneMgr->createEntity("Penguin", "penguin.mesh");
		entPenguin -> setCastShadows(true);
		Ogre::SceneNode* nodPenguin = mSceneMgr->getRootSceneNode()->createChildSceneNode("PenguinNode", Ogre::Vector3( 0, 20, 0 ));
		nodPenguin->scale( 1, 1, 1); 
		nodPenguin->attachObject(entPenguin);
  
		//Create floor 
		Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
 
		Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
 
		Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
 
		entGround->setMaterialName("Examples/Rockwall");
		entGround->setCastShadows(false);

		// Add block 1 
		Ogre::Entity* entBlock1 = mSceneMgr->createEntity("Block1", "cube.mesh");
		entBlock1 -> setCastShadows(true);
		Ogre::SceneNode* nodBlock1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("Bock1Node", Ogre::Vector3( 100, 0, 100 ));
		nodBlock1->scale( .1, .5, .1); 
		nodBlock1->attachObject(entBlock1);

		// Add block 2
		Ogre::Entity* entBlock2 = mSceneMgr->createEntity("Block2", "cube.mesh");
		entBlock2 -> setCastShadows(true);
		Ogre::SceneNode* nodBlock2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("Bock2Node", Ogre::Vector3( -100, 0, -100 ));
		nodBlock2->scale( 1, 1, 1); 
		nodBlock2->attachObject(entBlock2);

		// Create a light
		Ogre::Light* light = mSceneMgr->createLight("BaseLight");
		light ->setType(Ogre::Light::LT_POINT);
		light->setPosition(100,100,100);
}

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
    int Generate(int argc, char *argv[])
#endif
    {
        // Create application object
        Generate app;
 
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