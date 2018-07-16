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


	///<summary>
	///<para>�R���X�g���N�^</para>
	///<para>����: s3d::Rect(�`����Wxy,�`��T�C�Yxy),s3d::Rect(�摜�����W,�摜��1���T�C�Y)</para>
	///</summary>
	explicit DrawInterFace(s3d::Rect& draw, s3d::Rect& src)
	{
		this->drawbace = draw;
		this->srcbace = src;
	}


	///<summary>
	///<para>�`�悷�邽�߂̋�`�𐶐����܂�</para>
	///<para>s3d::Rect(�`����W , �`��T�C�Y)</para>
	///</summary>
	void setDrawBace(s3d::Rect& draw)
	{
		this->drawbace = draw;
	}


	///<summary>
	///<para>�`�悷�邽�߂̋�`�𐶐����܂�</para>
	///<para>����:�@�`����W x y, �`��T�C�Y x y</para>
	///</summary>
	void setDrawBace(int x, int y, int w, int h)
	{
		this->drawbace = { x,y,w,h };
	}


	///<summary>
	///<para>�`�悷�邽�߂̋�`�𐶐����܂�</para>
	///<para>����:�@Point(�`����W), Point(�`��T�C�Y)</para>
	///</summary>
	void setDrawBace(Point& pos , Point size)
	{
		this->drawbace = { pos , size };
	}


	///<summary>
	///<para>�摜���̋�`�𐶐����܂�</para>
	///<para>����: �摜�����Wxy , �摜���T�C�Y(1��) </para>
	///</summary>
	void setDrawSrc(int x, int y, int w, int h)
	{
		this->srcbace = { x,y,w,h };
	}


	///<summary>
	///<para>�摜���̋�`�𐶐����܂�</para>
	///<para>����: s3d::Rect(�摜�����W x y,�摜��1���T�C�Y x y)</para>
	///</summary>
	void setDrawSrc(s3d::Rect& src)
	{
		this->srcbace = src;
	}


	///<summary>
	///<para>�e�N�X�`����ݒ肵�܂�</para>
	///<para>ResourceManager����擾���܂�</para>
	///</summary>
	void setTexture(Texture image_)
	{
		this->image = image_;
	}


	///<summary>
	///<para>�`���`��Ԃ��܂�</para>
	///</summary>
	///<returns>�`���`</returns>
	s3d::Rect getDrawBace()const
	{
		return this->drawbace;
	}


	///<summary>
	///<para>�摜����`��Ԃ��܂�</para>
	///</summary>
	///<returns>�摜����`</returns>
	s3d::Rect getSrcBace()const
	{
		return this->srcbace;
	}


	///<summary>
	///<para>�`������܂�</para>
	///<para>�`��ʒu�E�T�C�Y , �摜���ʒu�E�T�C�Y</para>
	///</summary>
	void Draw(s3d::Rect& draw_, s3d::Rect& src_)
	{
		
	}


	///<summary>
	///<para>�`������܂�</para>
	///<para>�`��ʒu , �`��T�C�Y , �摜���ʒu�E�T�C�Y</para>
	///</summary>
	void Draw()
	{
		this->image.draw();
	}

	
private:
	s3d::Rect  drawbace;	//�`���`(����)
	s3d::Rect  srcbace;		//�摜����`�i�����j

	Texture image;		//�e�N�X�`��
};