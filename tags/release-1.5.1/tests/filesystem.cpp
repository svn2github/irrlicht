#include "irrlicht.h"
#include "testUtils.h"

using namespace irr;
using namespace core;
using namespace io;

bool filesystem(void)
{
	IrrlichtDevice * device = irr::createDevice(video::EDT_NULL, dimension2d<s32>(1, 1));
	assert(device);
	if(!device)
		return false;
	
	io::IFileSystem * fs = device->getFileSystem ();
	if ( !fs )
		return false;
	
	bool result = true;
	
	core::stringc workingDir = device->getFileSystem()->getWorkingDirectory();
	
	core::stringc empty;
	if ( fs->existFile(empty.c_str()) )
	{
		logTestString("Empty filename should not exist.\n");
		result = false;
	}
	
	stringc newWd = workingDir + "/media";
	bool changed = device->getFileSystem()->changeWorkingDirectoryTo(newWd.c_str());
	assert(changed);
	
	if ( fs->existFile(empty.c_str()) )
	{
		logTestString("Empty filename should not exist even in another workingdirectory.\n");
		result = false;
	}
	
	// The working directory must be restored for the other tests to work.
	changed = device->getFileSystem()->changeWorkingDirectoryTo(workingDir.c_str());
	assert(changed);
	
	// adding  a folder archive which just should not really change anything
	device->getFileSystem()->addFolderFileArchive( "./" );
	
	if ( fs->existFile(empty.c_str()) )
	{
		logTestString("Empty filename should not exist in folder file archive.\n");
		result = false;
	}
	
	return result;
}
