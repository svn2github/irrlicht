// Copyright (C) 2002-2007 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_GUI_FONT_H_INCLUDED__
#define __C_GUI_FONT_H_INCLUDED__

#include "IGUIFontBitmap.h"
#include "irrString.h"
#include "irrMap.h"
#include "IXMLReader.h"
#include "IReadFile.h"
#include "irrArray.h"

namespace irr
{

namespace video
{
	class IVideoDriver;
	class IImage;
}

namespace gui
{

	class IGUIEnvironment;

class CGUIFont : public IGUIFontBitmap
{
public:

	//! constructor
	CGUIFont(IGUIEnvironment* env, const c8* filename);

	//! destructor
	virtual ~CGUIFont();

	//! loads a font from a texture file
	bool load(const c8* filename);

	//! loads a font from a texture file
	bool load(io::IReadFile* file);

	//! loads a font from an XML file
	bool load(io::IXMLReader* xml);

	//! draws an text and clips it to the specified rectangle if wanted
	virtual void draw(const wchar_t* text, const core::rect<s32>& position, video::SColor color, bool hcenter=false, bool vcenter=false, const core::rect<s32>* clip=0);

	//! returns the dimension of a text
	virtual core::dimension2d<s32> getDimension(const wchar_t* text);

	//! Calculates the index of the character in the text which is on a specific position.
	virtual s32 getCharacterFromPos(const wchar_t* text, s32 pixel_x);

	//! Returns the type of this font
	virtual EGUI_FONT_TYPE getType() const { return EGFT_BITMAP; }

	//! set an Pixel Offset on Drawing ( scale position on width )
	virtual void setKerningWidth (s32 kerning);
	virtual void setKerningHeight (s32 kerning);

	//! set an Pixel Offset on Drawing ( scale position on width )
	virtual s32 getKerningWidth(const wchar_t* thisLetter=0, const wchar_t* previousLetter=0);
	virtual s32 getKerningHeight();

	//! gets the sprite bank
	virtual IGUISpriteBank* getSpriteBank();

	//! returns the sprite number from a given character
	virtual u32 getSpriteNoFromChar(const wchar_t *c);

private:

	struct SFontArea
	{
		SFontArea() : underhang(0), overhang(0), width(0), spriteno(0) {}
		s32				underhang;
		s32				overhang;
		s32				width;
		u32				spriteno;
	};

	//! load & prepare font from ITexture
	bool loadTexture(video::IImage * image, const c8* name);

	void readPositions16bit(video::IImage* texture, s32& lowerRightPositions);
	void readPositions32bit(video::IImage* texture, s32& lowerRightPositions);

	s32 getAreaFromCharacter (const wchar_t c);
	void setMaxHeight();

	core::array<SFontArea>		Areas;
	core::map<wchar_t, s32>		CharacterMap;
	video::IVideoDriver*		Driver;
	IGUISpriteBank*			SpriteBank;
	IGUIEnvironment*		Environment;
	u32				WrongCharacter;
	s32				MaxHeight;
	s32				GlobalKerningWidth, GlobalKerningHeight;
};

} // end namespace gui
} // end namespace irr

#endif

