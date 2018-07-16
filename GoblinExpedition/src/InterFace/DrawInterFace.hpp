#pragma once
#include <Siv3D.hpp>

///<summary>
///描画機能を追加するクラス
///</summary>
class DrawInterFace
{
public:
	///<summary>
	///<para>コンストラクタ</para>
	///<para>矩形を生成するには setDrawBace() setDrawSrc()を呼び出してください</para>
	///</summary>
	DrawInterFace() {}


	///<summary>
	///<para>コンストラクタ</para>
	///<para>引数: s3d::Rect(描画座標xy,描画サイズxy),s3d::Rect(画像元座標,画像元1つ分サイズ)</para>
	///</summary>
	explicit DrawInterFace(const s3d::Rect& draw, const s3d::Rect& src)
	{
		this->drawbace = draw;
		this->srcbace = src;
	}


	///<summary>
	///<para>描画するための矩形を生成します</para>
	///<para>s3d::Rect(描画座標 , 描画サイズ)</para>
	///</summary>
	void setDrawBace(const s3d::Rect& draw)
	{
		this->drawbace = draw;
	}


	///<summary>
	///<para>描画するための矩形を生成します</para>
	///<para>引数:　描画座標 x y, 描画サイズ x y</para>
	///</summary>
	void setDrawBace(int x, int y, int w, int h)
	{
		this->drawbace = { x,y,w,h };
	}


	///<summary>
	///<para>描画するための矩形を生成します</para>
	///<para>引数:　Point(描画座標), Point(描画サイズ)</para>
	///</summary>
	void setDrawBace(const Point& pos ,const Point size)
	{
		this->drawbace = { pos , size };
	}


	///<summary>
	///<para>画像元の矩形を生成します</para>
	///<para>引数: 画像元座標xy , 画像元サイズ(1つ分) </para>
	///</summary>
	void setDrawSrc(int x, int y, int w, int h)
	{
		this->srcbace = { x,y,w,h };
	}


	///<summary>
	///<para>画像元の矩形を生成します</para>
	///<para>引数: s3d::Rect(画像元座標 x y,画像元1つ分サイズ x y)</para>
	///</summary>
	void setDrawSrc(const s3d::Rect& src)
	{
		this->srcbace = src;
	}


	///<summary>
	///<para>テクスチャを設定します</para>
	///<para>ResourceManagerから取得します</para>
	///</summary>
	void setTexture(Texture image_)
	{
		this->image = image_;
	}


	///<summary>
	///<para>描画矩形を返します</para>
	///</summary>
	///<returns>描画矩形</returns>
	s3d::Rect getDrawBace()const
	{
		return this->drawbace;
	}


	///<summary>
	///<para>画像元矩形を返します</para>
	///</summary>
	///<returns>画像元矩形</returns>
	s3d::Rect getSrcBace()const
	{
		return this->srcbace;
	}


	///<summary>
	///<para>描画をします</para>
	///<para>描画位置・サイズ , 画像元位置・サイズ</para>
	///</summary>
	void Draw(const s3d::Rect& draw_, const s3d::Rect& src_)
	{
		s3d::Rect(draw_)(this->image(src_)).draw();
	}


	///<summary>
	///<para>描画をします</para>
	///<para>描画位置 , 描画サイズ , 画像元位置・サイズ</para>
	///</summary>
	void Draw(const Point& pos ,const Point& size ,const s3d::Rect& src_)
	{
		s3d::Rect(pos, size)(this->image(src_)).draw();
	}

	
private:
	s3d::Rect  drawbace;	//描画矩形(整数)
	s3d::Rect  srcbace;		//画像元矩形（整数）

	Texture image;		//テクスチャ
};