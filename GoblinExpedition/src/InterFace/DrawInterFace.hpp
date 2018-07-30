#pragma once
#include <Siv3D.hpp>
///<summary>
///�`��@�\��ǉ�����N���X
///</summary>
class DrawInterFace
{
public:
	///<summary>
	///<para>�R���X�g���N�^</para>
	///<para>��`�𐶐�����ɂ� setDrawBace() setDrawSrc()���Ăяo���Ă�������</para>
	///</summary>
	DrawInterFace() {}


	/// <summary>
	/// ��`�������R���X�g���N�^
	/// </summary>
	/// <param name="draw">
	/// (�`����Wxy,�`��T�C�Yxy)
	/// </param>
	/// <param name="src">
	/// (�摜�����W,�摜��1���T�C�Y)
	/// </param>
	explicit DrawInterFace(const s3d::RectF& draw, const s3d::Rect& src)
	{
		this->drawbace = draw;
		this->srcbace = src;
	}


	/// <summary>
	/// �`��@�\��ǉ����܂�(Src�Ȃ�)
	/// </summary>
	/// <param name="draw">
	/// (�`����Wxy,�`��T�C�Yxy)
	/// </param>
	static DrawInterFace* Addcomponent(const s3d::RectF& draw)
	{
		DrawInterFace* drawcreate = new DrawInterFace();
		drawcreate->setDrawBace(draw);
		return drawcreate;
	}


	/// <summary>
	/// �`��@�\��ǉ����܂�
	/// </summary>
	/// <param name="draw">
	/// (�`����Wxy,�`��T�C�Yxy)
	/// </param>
	/// <param name="src">
	/// (�摜�����W,�摜��1���T�C�Y)
	/// </param>
	static DrawInterFace* Addcomponent(const s3d::RectF& draw, const s3d::Rect& src)
	{
		return new DrawInterFace(draw, src);
	}

	/// <summary>
	/// �`�悷�邽�߂̋�`�𐶐����܂�
	/// </summary>
	/// <param name="draw">
	/// (�`����W x y , �`��T�C�Y x y )
	/// </param>
	void setDrawBace(const s3d::Rect& draw)
	{
		this->drawbace = draw;
	}


	/// <summary>
	/// �`�悷�邽�߂̋�`�𐶐����܂�
	/// </summary>
	/// <param name="x">
	/// �`����WX
	/// </param>
	/// <param name="y">
	/// �`����WY
	/// </param>
	/// <param name="w">
	/// �`��T�C�YX
	/// </param>
	/// <param name="h">
	/// �`��T�C�YY
	/// </param>
	void setDrawBace(double x, double y, int w, int h)
	{
		this->drawbace = { x,y,(double)w,(double)h };
	}


	/// <summary>
	/// �`�悷�邽�߂̋�`�𐶐����܂�
	/// </summary>
	/// <param name="draw_pos">
	/// �`����W
	/// </param>
	/// <param name="draw_size">
	/// �`��T�C�Y
	/// </param>
	void setDrawBace(const Vec2& draw_pos, const Point& draw_size)
	{
		this->drawbace = { draw_pos , draw_size };
	}


	/// <summary>
	/// �摜���̋�`�𐶐����܂�
	/// </summary>
	/// <param name="x">
	/// �`����WX
	/// </param>
	/// <param name="y">
	/// �`����WY
	/// </param>
	/// <param name="w">
	/// �`��T�C�YX
	/// </param>
	/// <param name="h">
	/// �`��T�C�YY
	/// </param>
	void setDrawSrc(int x, int y, int w, int h)
	{
		this->srcbace = { x,y,w,h };
	}


	/// <summary>
	/// �摜���̋�`�𐶐����܂�
	/// </summary>
	/// <param name="src">
	/// (�摜�����W x y,�摜��1���T�C�Y x y)
	/// </param>
	void setDrawSrc(const s3d::Rect& src)
	{
		this->srcbace = src;
	}


	/// <summary>
	/// �e�N�X�`����ݒ肵�܂�
	/// </summary>
	/// <param name="resourcemaneger_image">
	/// ResourceManager����擾����Texture
	/// </param>
	void setTexture(Texture resourcemaneger_image)
	{
		this->image = resourcemaneger_image;
	}


	///<summary>
	///�`���`��Ԃ��܂�
	///</summary>
	///<returns>
	/// �`���`
	///</returns>
	s3d::Rect getDrawBace()const
	{
		return this->drawbace;
	}


	///<summary>
	///�摜����`��Ԃ��܂�
	///</summary>
	///<returns>
	///�摜����`
	///</returns>
	s3d::Rect getSrcBace()const
	{
		return this->srcbace;
	}


	/// <summary>
	/// �e�N�X�`����\��t���ĕ`������܂�
	/// </summary>
	/// <param name="draw_">
	/// (�`����W x y , �`��T�C�Y x y)
	/// </param>
	/// <param name="src_">
	/// (�摜�����W x y , �摜���T�C�Y x y)
	/// </param>
	/// <param name="mirror">
	/// ���E���]�t���O �@���] true / ���]���Ȃ� false
	/// </param>
	void TextureDraw(const s3d::RectF& draw_, const s3d::Rect& src_,bool mirror = false)
	{
		if (mirror)
		{
			s3d::RectF(draw_)(this->image(src_).mirror()).draw();
		}
		else
		{
			s3d::RectF(draw_)(this->image(src_)).draw();
		}
	}


	/// <summary>
	/// �e�N�X�`����\��t���ĕ`������܂�(���ߏ����Ή�)
	/// </summary>
	/// <param name="draw_">
	/// (�`����W x y , �`��T�C�Y x y)
	/// </param>
	/// <param name="src_">
	/// (�摜�����W x y , �摜���T�C�Y x y)
	/// </param>
	/// <param name="alfa">
	/// �A���t�@�l
	/// </param>
	/// <param name="mirror">
	/// ���E���]�t���O �@���] true / ���]���Ȃ� false
	/// </param>
	void TextureDraw(const s3d::RectF& draw_, const s3d::Rect& src_,const Color& alfa , bool mirror = false)
	{
		if (mirror)
		{
			s3d::RectF(draw_)(this->image(src_).mirror()).draw(alfa);
		}
		else
		{
			s3d::RectF(draw_)(this->image(src_)).draw(alfa);
		}
	}


	/// <summary>
	/// �e�N�X�`����\��t���ĕ`������܂�
	/// </summary>
	/// <param name="drawpos">
	/// �`����W
	/// </param>
	/// <param name="drawsize">
	/// �`��T�C�Y
	/// </param>
	/// <param name="src_">
	/// (�摜�����W x y , �摜���T�C�Y x y )
	/// </param>
	/// <param name="mirror">
	/// ���E���]�t���O �@���] true / ���]���Ȃ� false
	/// </param>
	void TextureDraw(const Point& drawpos, const Point& drawsize, const s3d::Rect& src_ , bool mirror = false)
	{
		if (mirror)
		{
			s3d::Rect(drawpos, drawsize)(this->image(src_).mirror()).draw();
		}
		else
		{
			s3d::Rect(drawpos, drawsize)(this->image(src_)).draw();
		}
	}


	/// <summary>
	/// ���X�ɓ��߂����Ȃ���`������܂�
	/// </summary>
	/// <param name="drawpos">
	/// �`����W
	/// </param>
	/// <param name="drawsize">
	/// �`��T�C�Y
	/// </param>
	/// <param name="src_">
	/// (�摜�����W x y , �摜���T�C�Y x y )
	/// </param>
	/// <param name="alfa">
	/// �A���t�@�l(rbg�J���[ , �s�����x)
	/// </param>
	/// <param name="mirror">
	/// ���E���]�t���O �@���] true / ���]���Ȃ� false
	/// </param>
	void TextureDraw(const Point& drawpos, const Point& drawsize, const s3d::Rect& src_,Color& alfa , bool mirror = false)
	{
		if (alfa.a <= 0)
		{
			alfa.a = 0;
		}
		alfa.a--;
		if (mirror)
		{
			s3d::Rect(drawpos, drawsize)(this->image(src_).mirror()).draw(alfa);
		}
		else
		{
			s3d::Rect(drawpos, drawsize)(this->image(src_)).draw(alfa);
		}
	}


	/// <summary>
	/// ��`���w��̐F�ɓh��Ԃ����ĕ`�悵�܂�
	/// </summary>
	/// <param name="drawpos">
	/// �`����W
	/// </param>
	/// <param name="drawsize">
	/// �`��T�C�Y
	/// </param>
	/// <param name="color">
	/// �`��J���[
	/// </param>
	void PaletteColorDraw(const Point& drawpos, const Point& drawsize, const Color& color)
	{
		s3d::Rect(drawpos, drawsize).draw(color);
	}


	/// <summary>
	/// ��`���w��̐F�ɓh��Ԃ����ĕ`�悵�܂�
	/// </summary>
	/// <param name="draw_">
	/// �`����W�E�`���`
	/// </param>
	/// <param name="color">
	/// �`��J���[
	/// </param>
	void PaletteColorDraw(const Rect& draw_ , const Color& color)
	{
		draw_.draw(color);
	}
private:
	s3d::RectF drawbace;	//�`���`(����)
	s3d::Rect  srcbace;		//�摜����`�i�����j
	Texture image;			//�e�N�X�`��
};