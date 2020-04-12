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
		int memes = 0;
		state currstate = state::Hidden;
		void spwanmeme();
		 bool hasmeme();
		void revealTile();
		void flagtile();
		void Drawtile(Graphics& gfx,const Vei2& screenpos);
		void setmemes(int n);

	};
private:
	static constexpr int  Hieght = 20;
	static constexpr int  Width = 20;
	Tile mememap[Hieght*Width];
private:
	int calcadjmemes( Vei2& pos );
	Tile& Tileat(Vei2& gridpos);
public:
	MemeField(int nmemes);
	void Drawmemefield(Graphics& gfx);
	bool revealonclick( Vei2&  pos);
	void  flagonclick(Vei2&  pos);
	void revealeallmemes();





	
};

