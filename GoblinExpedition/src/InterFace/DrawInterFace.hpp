#pragma once
#include <Siv3D.hpp>
#include "ObjectType.h"
#include "../Assets/CharaBace.h"
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


	/// <summary>
	/// 矩形生成つきコンストラクタ
	/// </summary>
	/// <param name="draw">
	/// (描画座標xy,描画サイズxy)
	/// </param>
	/// <param name="src">
	/// (画像元座標,画像元1つ分サイズ)
	/// </param>
	explicit DrawInterFace(const s3d::Rect& draw, const s3d::Rect& src)
	{
		this->drawbace = draw;
		this->srcbace = src;
	}


	/// <summary>
	/// 描画するための矩形を生成します
	/// </summary>
	/// <param name="draw">
	/// (描画座標 x y , 描画サイズ x y )
	/// </param>
	void setDrawBace(const s3d::Rect& draw)
	{
		this->drawbace = draw;
	}


	/// <summary>
	/// 描画するための矩形を生成します
	/// </summary>
	/// <param name="x">
	/// 描画座標X
	/// </param>
	/// <param name="y">
	/// 描画座標Y
	/// </param>
	/// <param name="w">
	/// 描画サイズX
	/// </param>
	/// <param name="h">
	/// 描画サイズY
	/// </param>
	void setDrawBace(int x, int y, int w, int h)
	{
		this->drawbace = { x,y,w,h };
	}


	/// <summary>
	/// 描画するための矩形を生成します
	/// </summary>
	/// <param name="draw_pos">
	/// 描画座標
	/// </param>
	/// <param name="draw_size">
	/// 描画サイズ
	/// </param>
	void setDrawBace(const Point& draw_pos, const Point draw_size)
	{
		this->drawbace = { draw_pos , draw_size };
	}


	/// <summary>
	/// 画像元の矩形を生成します
	/// </summary>
	/// <param name="x">
	/// 描画座標X
	/// </param>
	/// <param name="y">
	/// 描画座標Y
	/// </param>
	/// <param name="w">
	/// 描画サイズX
	/// </param>
	/// <param name="h">
	/// 描画サイズY
	/// </param>
	void setDrawSrc(int x, int y, int w, int h)
	{
		this->srcbace = { x,y,w,h };
	}


	/// <summary>
	/// 画像元の矩形を生成します
	/// </summary>
	/// <param name="src">
	/// (画像元座標 x y,画像元1つ分サイズ x y)
	/// </param>
	void setDrawSrc(const s3d::Rect& src)
	{
		this->srcbace = src;
	}


	/// <summary>
	/// テクスチャを設定します
	/// </summary>
	/// <param name="resourcemaneger_image">
	/// ResourceManagerから取得したTexture
	/// </param>
	void setTexture(Texture resourcemaneger_image)
	{
		this->image = resourcemaneger_image;
	}


	///<summary>
	///描画矩形を返します
	///</summary>
	///<returns>
	/// 描画矩形
	///</returns>
	s3d::Rect getDrawBace()const
	{
		return this->drawbace;
	}


	///<summary>
	///画像元矩形を返します
	///</summary>
	///<returns>
	///画像元矩形
	///</returns>
	s3d::Rect getSrcBace()const
	{
		return this->srcbace;
	}


	/// <summary>
	/// テクスチャを貼り付けて描画をします
	/// </summary>
	/// <param name="draw_">
	/// (描画座標 x y , 描画サイズ x y)
	/// </param>
	/// <param name="src_">
	/// (画像元座標 x y , 画像元サイズ x y)
	/// </param>
	void TextureDraw(const s3d::Rect& draw_, const s3d::Rect& src_)
	{
		s3d::Rect(draw_)(this->image(src_)).draw();
	}


	/// <summary>
	/// テクスチャを貼り付けて描画をします
	/// </summary>
	/// <param name="drawpos">
	/// 描画座標
	/// </param>
	/// <param name="drawsize">
	/// 描画サイズ
	/// </param>
	/// <param name="src_">
	/// (画像元座標 x y , 画像元サイズ x y )
	/// </param>
	void TextureDraw(const Point& drawpos, const Point& drawsize, const s3d::Rect& src_)
	{
		s3d::Rect(drawpos, drawsize)(this->image(src_)).draw();
	}


	/// <summary>
	/// 矩形を指定の色に塗りつぶしして描画します
	/// </summary>
	/// <param name="drawpos">
	/// 描画座標
	/// </param>
	/// <param name="drawsize">
	/// 描画サイズ
	/// </param>
	/// <param name="color">
	/// 描画カラー
	/// </param>
	void PaletteColorDraw(const Point& drawpos, const Point& drawsize, const Color& color)
	{
		s3d::Rect(drawpos, drawsize).draw(color);
	}


	/// <summary>
	/// 矩形を指定の色に塗りつぶしして描画します
	/// </summary>
	/// <param name="draw_">
	/// 描画座標・描画矩形
	/// </param>
	/// <param name="color">
	/// 描画カラー
	/// </param>
	void PaletteColorDraw(const Rect& draw_ , const Color& color)
	{
		draw_.draw(color);
	}

private:
	s3d::Rect  drawbace;	//描画矩形(整数)
	s3d::Rect  srcbace;		//画像元矩形（整数）
	Texture image;			//テクスチャ
};