#pragma once
#include <Siv3D.hpp>
#include <fstream>
#include <string>
#include <sstream>

/// <summary>
/// �����������N���X
/// </summary>
class TextInterFace
{
public:
	/// <summary>
	/// ��{�I�t�H�[�}�b�g�`��
	/// </summary>
	enum class FormatText
	{
		TXT,		//�e�L�X�g�t�@�C��
		CSV,		//CSV�t�@�C��
	};

	/// <summary>
	/// �ǂݍ��݃^�C�v
	/// </summary>
	enum class ReaderType
	{
		CSV,		//CSV�ǂݍ���
		TextLine,	//�ŏ�����Ō�܂ł��ЂƂ̕�����Ƃ��Ĉ���
		TextLen,	//1�s���Ƃɓǂݍ���
		TextChar,	//1�������Ƃɓǂݍ���
	};

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TextInterFace();


	/// <summary>
	/// �������o�͂��܂�
	/// </summary>
	/// <param name="color">
	/// �F
	/// </param>
	void draw(const Color& color = Palette::White);


	/// <summary>
	/// ��������]�����ďo�͂��܂�
	/// </summary>
	/// <param name="degree">
	/// ��]�x
	/// </param>
	/// <param name="color">
	/// �F
	/// </param>
	void draw(const double& degree , const Color& color = Palette::White);


	/// <summary>
	/// �������w��̈ʒu�ŏo�͂��܂�
	/// </summary>
	/// <param name="position">
	/// �o�͂�����W
	/// </param>
	/// <param name="color">
	/// �F
	/// </param>
	void draw(const Vec2& position , const Color& color = Palette::White);
	

	/// <summary>
	/// �����̕�����`�悵�܂�
	/// </summary>
	/// <param name="string_">
	/// �`�悵����������
	/// </param>
	/// <param name="position_">
	/// �`��ʒu
	/// </param>
	/// <param name="color">
	/// �`��F
	/// </param>
	/// <param name="degree">
	/// ��]�x
	/// </param>
	void draw(const String& string_, const Vec2& position_, const Color& color = Palette::White, const double& degree = 0.0);


	/// <summary>
	/// ������𐶐����܂�
	/// </summary>
	/// <param name="string">
	/// �w�肷�镶��
	/// </param>
	/// <param name="font_">
	/// �t�H���g
	/// </param>
	/// <returns>
	/// �C���X�^���X���������A�h���X�l
	/// </returns>
	static TextInterFace* Create(const std::string& string,const Font& font_);


	/// <summary>
	/// �e�L�X�g�t�@�C���܂���CSV�̓ǂݍ��ݗp��������쐬���܂�
	/// </summary>
	/// <param name="filepath_"></param>
	/// <param name="format"></param>
	/// <param name="font_"></param>
	/// <returns></returns>
	static TextInterFace* Create(const std::string& filepath_, const FormatText& format, const Font& font_);


	/// <summary>
	/// �e�L�X�g�t�@�C���܂���CSV�t�@�C���ǂݍ��݂��s���܂�
	/// </summary>
	/// <param name="readertype">
	/// �ǂݍ��ޕ��@
	/// </param>
	/// <returns>
	/// �ǂݍ��񂾃t�@�C���̕�����
	/// </returns>
	Array<String> ReadText(const ReaderType& readertype);


	/// <summary>
	/// ������z����i�[���܂�
	/// </summary>
	/// <param name="arrayString_">
	/// �i�[���Ă���������z��
	/// </param>
	void setArrayString(const Array<String>& arrayString_);


	/// <summary>
	/// �i�[����Ă��镶����z���Ԃ��܂�
	/// </summary>
	Array<String> getArrayString()const;


	/// <summary>
	/// ������ɕ�����z��̗v�f�������܂�
	/// </summary>
	/// <param name="arrayString_">
	/// ������z��
	/// </param>
	/// <param name="number">
	/// �������ԍ�
	/// </param>
	void StringAssignment(const Array<String>& arrayString_ ,const size_t& number);


	/// <summary>
	/// �t�H���g��ύX���܂�
	/// </summary>
	/// <param name="font_">
	/// �ݒ肷��t�H���g
	/// </param>
	void ChengeFont(const Font& font_);


private:
	/// <summary>
	/// �����𐶐����܂�
	/// </summary>
	/// <param name="string">
	/// �w�肷�镶��
	/// </param>
	/// <param name="font_">
	/// �t�H���g
	/// </param>
	TextInterFace(const std::string& string , const Font& font_);


	/// <summary>
	/// �e�L�X�g�t�@�C���܂���CSV�̓ǂݍ��ݗp��������쐬���܂�
	/// </summary>
	/// <param name="filepath_">
	/// �t�@�C���p�X
	/// </param>
	/// <param name="format">
	/// �t�@�C���`��
	/// </param>
	/// <param name="font_">
	/// �t�H���g
	/// </param>
	TextInterFace(const std::string& filepath_, const FormatText& format, const Font& font_);


	/// <summary>
	/// �e�L�X�g��S�ēǂݍ��݂܂�
	/// </summary>
	/// <param name="fin">
	/// �ǂݍ��ތ`��
	/// </param>
	/// <returns>
	/// �ǂݍ��݂�����������Vector
	/// </returns>
	Array<String> ReadLine();


	/// <summary>
	/// �e�L�X�g��1�s���Ƃɓǂݍ��݂܂�
	/// </summary>
	/// <param name="fin">
	/// �ǂݍ��ތ`��
	/// </param>
	/// <returns>
	/// �ǂݍ��݂���������Vector
	/// </returns>
	Array<String> ReadLen();


	/// <summary>
	/// �e�L�X�g��1�������ǂݍ��݂܂�
	/// </summary>
	/// <returns>
	/// �ǂݍ��݂���������Vector
	/// </returns>
	Array<String> ReadChar();


	/// <summary>
	/// CSV�t�@�C���̓ǂݍ���
	/// </summary>
	/// <returns>
	/// �ǂݍ��݂���������Vector
	/// </returns>
	Array<String> ReadCsv();


private:
	Vec2			position;			//�ʒu
	std::string		filepath;			//�t�@�C���p�X
	FormatText		formattext;			//�t�@�C���`��
	String			text;				//�e�L�X�g
	Font*			font;				//�t�H���g
	Array<String>   strings;			//�����z��
};
/*�t�@�C���ǂݍ��ݗp�e�L�X�g�𐶐����܂�*/
inline TextInterFace::TextInterFace(const std::string& filepath_, const FormatText& format, const Font& font_)
{
	this->filepath = filepath_;
	this->formattext = format;
	this->position = {};
	this->font = new Font(font_);
}
/*������𐶐����܂�*/
inline TextInterFace::TextInterFace(const std::string& string,const Font& font_)
{
	this->text.narrow() = string;
	this->position = {};
	this->font = new Font(font_);
}
/*������𐶐����܂�*/
inline TextInterFace* TextInterFace::Create(const std::string& string,const Font& font_)
{
	return new TextInterFace(string,font_);
}
/*�e�L�X�g�t�@�C���܂���CSV�̓ǂݍ��ݗp��������쐬���܂�*/
inline TextInterFace* TextInterFace::Create(const std::string& filepath_, const FormatText& format, const Font& font_)
{
	return new TextInterFace(filepath_, format, font_);
}
/*�f�X�g���N�^*/
inline TextInterFace::~TextInterFace()
{
	if (this->font)
	{
		delete this->font;
		this->font = nullptr;
	}
}
/*������ɕ�����z��̗v�f�������܂�*/
inline void TextInterFace::StringAssignment(const Array<String>& arrayString_, const size_t& number)
{
	if (number >= arrayString_.size())
	{
		return;
	}
	this->text = arrayString_[number];
}
/*�t�H���g��ݒ�E�ύX���܂�*/
inline void TextInterFace::ChengeFont(const Font& font_)
{
	if (this->font)
	{
		delete this->font;
	}
	this->font = new Font(font_);
}
/*�����̕�����`�悵�܂�*/
inline void TextInterFace::draw(const String& string_, const Vec2& position_, const Color& color, const double& degree)
{
	const Font& f = *this->font;
	//�s��̌v�Z
	Graphics2D::SetTransform(
		Mat3x2::Scale(this->font->size(), this->font->height)*
		Mat3x2::Rotate(degree)*
		Mat3x2::Translate(position_)
	);
	f(string_).draw(position_, color);
}
/*�������o�͂��܂�*/
inline void TextInterFace::draw(const Color& color)
{
	const Font& f = *this->font;
	f(this->text).draw(this->position,color);
}
/*�w��̈ʒu�ɕ������o�͂��܂�*/
inline void TextInterFace::draw(const Vec2& position_ , const Color& color)
{
	const Font& f = *this->font;
	f(this->text).draw(position_,color);
}
/*��������]�����ďo�͂����܂�*/
inline void TextInterFace::draw(const double& degree,const Color& color)
{
	const Font& f = *this->font;

	//�s��̌v�Z
	Graphics2D::SetTransform(
		Mat3x2::Scale(this->font->size() ,this->font->height)*
		Mat3x2::Rotate(degree)*
		Mat3x2::Translate(this->position)
	);
	f(this->text).draw(this->position,color);
}
/*�e�L�X�g�t�@�C���܂���CSV�t�@�C���ǂݍ��݂��s���܂�*/
inline Array<String> TextInterFace::ReadText(const ReaderType& readertype)
{
	Array<String>(TextInterFace::*readerfunction[])() = 
	{
		&TextInterFace::ReadCsv,
		&TextInterFace::ReadLine,
		&TextInterFace::ReadLen,
		&TextInterFace::ReadChar
	};
	return (this->*readerfunction[((int)readertype)])();
}
/*�e�L�X�g��S�ēǂݍ��݂܂�*/
inline Array<String> TextInterFace::ReadLine()
{
	//��������i�[����Vector
	Array<String> readtext;
	//�ǂݍ��݂������������ꎞ�I�Ɏg�p���镶����
	String line;
	//�ǂݍ��݂ɕK�v�ȃ��[�_�[
	TextReader textreader;

	//�e�L�X�g�t�@�C���̃t�H�[�}�b�g�̂ݓK�p
	if (this->formattext == FormatText::TXT && textreader.open(Widen(this->filepath)))
	{
		line = textreader.readAll();
		readtext.push_back(line);
		textreader.close();
	}
	return readtext;
}
/*�e�L�X�g��1�s���Ƃɓǂݍ��݂܂�*/
inline Array<String> TextInterFace::ReadLen()
{
	//��������i�[����Vector
	Array<String> readtext;
	//�ǂݍ��݂������������ꎞ�I�Ɏg�p���镶����
	String line;
	//�ǂݍ��݂ɕK�v�ȃ��[�_�[
	TextReader textreader;

	if (this->formattext == FormatText::TXT && textreader.open(Widen(this->filepath)))
	{
		while (textreader.readLine(line))
		{
			readtext.push_back(line);
		}
		textreader.close();
	}
	return readtext;
}
/*�e�L�X�g��1�������ǂݍ��݂܂�*/
inline Array<String> TextInterFace::ReadChar()
{
	//��������i�[����Vector
	Array<String> readtext;
	//�ǂݍ��݂������������ꎞ�I�Ɏg�p���镶����
	String line;
	//�ǂݍ��݂ɕK�v�ȃ��[�_�[
	TextReader textreader;

	if (this->formattext == FormatText::TXT && textreader.open(Widen(this->filepath)))
	{
		while (textreader.readLine(line))
		{
			readtext.push_back(line);
		}
		textreader.close();
	}
	return readtext;
}
/*CSV�t�@�C����ǂݍ��݂܂�*/
inline Array<String> TextInterFace::ReadCsv()
{
	//��������i�[����Vector
	Array<String> readtext;
	//�ǂݍ��݂������������ꎞ�I�Ɏg�p���镶����
	String        line;
	//�ǂݍ��݂ɕK�v�ȃ��[�_�[
	CSVReader     csvreader;

	if (this->formattext == FormatText::CSV && csvreader.open(Widen(this->filepath)))
	{
		for (size_t row = 0; row < csvreader.rows; ++row)
		{
			for (size_t column = 0; column < csvreader.columns(row); ++column)
			{
				readtext.push_back(csvreader.get<String>(row, column));
			}
		}
	}
	return readtext;
}
/*��������i�[���܂�*/
inline void TextInterFace::setArrayString(const Array<String>& arrayString_)
{
	this->strings = arrayString_;
}
/*�i�[���Ă����������Ԃ��܂�*/
inline Array<String> TextInterFace::getArrayString()const
{
	return this->strings;
}