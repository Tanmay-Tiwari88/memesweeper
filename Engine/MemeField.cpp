#include "MemeField.h"
#include<assert.h>
#include<random>
#include"RectI.h"

void MemeField::Tile::spwanmeme()
{
	meme = true;
}

bool MemeField::Tile::hasmeme()
{
	return meme;
}

void MemeField::Tile::revealTile()
{
	currstate = state::Revealed;
}

void MemeField::Tile::Drawtile(Graphics & gfx, const Vei2 & screenpos)
{
	switch (currstate)
	{
	case MemeField::Tile::state::Flagged:
		SpriteCodex::DrawTileButton(screenpos, gfx);
		SpriteCodex::DrawTileFlag(screenpos, gfx);
		break;
	case MemeField::Tile::state::Hidden:
		SpriteCodex::DrawTileButton(screenpos, gfx);
		break;
	case MemeField::Tile::state::Revealed:
		if (hasmeme())
			SpriteCodex::DrawTileBomb(screenpos, gfx);
		else
			SpriteCodex::DrawTile0(screenpos, gfx);
		break;

	}
}

MemeField::Tile& MemeField::Tileat(Vei2 & gridpos)
{
	return mememap[gridpos.y*Width+gridpos.x];
}

MemeField::MemeField(int nmemes)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> x(0, Hieght);
	std::uniform_int_distribution<int> y(0, Width);
	for (int i = 0; i < nmemes; i++)
	{
		Vei2 memepos;
		
		do {
			 memepos = { x(rng),y(rng) };
		} while (Tileat(memepos).hasmeme());
			Tileat(memepos).spwanmeme();
			
	}
}

void MemeField::Drawmemefield(Graphics& gfx)
{
	RectI r = RectI(Vei2{ 0,0 }, SpriteCodex::tileSize*Width, SpriteCodex::tileSize*Hieght);
	gfx.DrawRect(r,Colors::Cyan);
	for (int i = 0; i < Width; i++)
	{
		for (int j = 0; j < Hieght; j++)
		{
			Vei2 screenpos(i*SpriteCodex::tileSize,j*SpriteCodex::tileSize);
			//mememap[j*Width + i].revealTile();
			mememap[j*Width + i].Drawtile(gfx, screenpos);
		}
	}
}
