#pragma once
#include"Graphics.h"
#include"Vei2.h"
#include"RectI.h"
#include"SpriteCodex.h"
class MemeField
{
private:
	class Tile
	{
	public:
		enum class state {
			Flagged,
			Hidden,
			Revealed
		};
		bool meme=false;
		state currstate = state::Hidden;
		void spwanmeme();
		 bool hasmeme();
		void revealTile();
		void Drawtile(Graphics& gfx,const Vei2& screenpos);

	};
private:
	static int constexpr Hieght = 20;
	static int constexpr Width = 16;
	Tile mememap[Hieght*Width];
private:
	Tile& Tileat(Vei2& gridpos);
public:
	MemeField(int nmemes);
	void Drawmemefield(Graphics& gfx);




	
};

