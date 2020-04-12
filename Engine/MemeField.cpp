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

void MemeField::Tile::flagtile()
{
	currstate = state::Flagged;
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
		{
			switch (memes)
			{
			case 0:
				SpriteCodex::DrawTile0(screenpos, gfx);
				break;
			case 1:
				SpriteCodex::DrawTile1(screenpos, gfx);
				break;
			case 2:
				SpriteCodex::DrawTile2(screenpos, gfx);
				break;
			case 3:
				SpriteCodex::DrawTile3(screenpos, gfx);
				break;
			case 4:
				SpriteCodex::DrawTile4(screenpos, gfx);
				break;
			case 5:
				SpriteCodex::DrawTile5(screenpos, gfx);
				break;
			case 6:
				SpriteCodex::DrawTile6(screenpos, gfx);
				break;
			case 7:
				SpriteCodex::DrawTile7(screenpos, gfx);
				break;

			}
		}
		break;

	}
}

void MemeField::Tile::setmemes(int n)
{
	memes = n;
}

int MemeField::calcadjmemes( Vei2&  pos)
{
	int memes = 0;
	if (pos.x < 0 || pos.x>=Hieght || pos.y < 0 || pos.y>=Width)
		return -1;
	for (int x = pos.x - 1; x <= pos.x + 1; x++)
	{
		if (x >= 0 && x < Hieght)
		{
			for (int y = pos.y - 1; y <= pos.y + 1; y++)
			{
				if (y >= 0 && y <Width)
				{

					Vei2 currpos = { x,y };
					if (currpos.x == pos.x && currpos.y == pos.y)
					{
					}
					else
					{
						if (Tileat(currpos).hasmeme())
							memes++;
						else
						{
							revealonclick(currpos);
						}
					}
				}
			}
		}

	}
	return memes;
}

MemeField::Tile& MemeField::Tileat(Vei2 & gridpos)
{
	return mememap[(gridpos.y*Width)+gridpos.x];
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
			Tileat(Vei2(i,j)).Drawtile(gfx, screenpos);
		}
	}
}

bool MemeField::revealonclick( Vei2 &  pos)
{
	if (Tileat(pos).currstate != Tile::state::Flagged && Tileat(pos).currstate != Tile::state::Revealed)
	{
		Tileat(pos).revealTile();
		if (Tileat(pos).hasmeme())
			return true;
		int memes = calcadjmemes(pos);
		Tileat(pos).setmemes(memes);
		return false;
	}
	return false;

}

void MemeField::flagonclick(Vei2 & pos)
{
	if (Tileat(pos).currstate != Tile::state::Flagged && Tileat(pos).currstate != Tile::state::Revealed)
	Tileat(pos).flagtile();
}

void MemeField::revealeallmemes()
{
	for (int i = 0; i < Width; i++)
	{
		for (int j = 0; j < Hieght; j++)
		{
			Vei2 screenpos(i*SpriteCodex::tileSize, j*SpriteCodex::tileSize);
			//mememap[j*Width + i].revealTile();
			Tileat(Vei2(i, j)).revealTile();
		}
	}
}

