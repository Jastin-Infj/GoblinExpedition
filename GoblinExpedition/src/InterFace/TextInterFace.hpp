#pragma once
#include <Siv3D.hpp>
#include <fstream>
#include <string>
#include <sstream>

/// <summary>
/// 文字を扱うクラス
/// </summary>
class TextInterFace
{
public:
	/// <summary>
	/// 基本的フォーマット形式
	/// </summary>
	enum class FormatText
	{
		TXT,		//テキストファイル
		CSV,		//CSVファイル
	};

	/// <summary>
	/// 読み込みタイプ
	/// </summary>
	enum class ReaderType
	{
		CSV,		//CSV読み込み
		TextLine,	//最初から最後までをひとつの文字列として扱う
		TextLen,	//1行ごとに読み込み
		TextChar,	//1文字ごとに読み込み
	};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TextInterFace();


	/// <summary>
	/// 文字を出力します
	/// </summary>
	/// <param name="color">
	/// 色
	/// </param>
	void draw(const Color& color = Palette::White);


	/// <summary>
	/// 文字を回転させて出力します
	/// </summary>
	/// <param name="degree">
	/// 回転度
	/// </param>
	/// <param name="color">
	/// 色
	/// </param>
	void draw(const double& degree , const Color& color = Palette::White);


	/// <summary>
	/// 文字を指定の位置で出力します
	/// </summary>
	/// <param name="position">
	/// 出力する座標
	/// </param>
	/// <param name="color">
	/// 色
	/// </param>
	void draw(const Vec2& position , const Color& color = Palette::White);
	

	/// <summary>
	/// 引数の文字を描画します
	/// </summary>
	/// <param name="string_">
	/// 描画したい文字列
	/// </param>
	/// <param name="position_">
	/// 描画位置
	/// </param>
	/// <param name="color">
	/// 描画色
	/// </param>
	/// <param name="degree">
	/// 回転度
	/// </param>
	void draw(const String& string_, const Vec2& position_, const Color& color = Palette::White, const double& degree = 0.0);


	/// <summary>
	/// 文字列を生成します
	/// </summary>
	/// <param name="string">
	/// 指定する文字
	/// </param>
	/// <param name="font_">
	/// フォント
	/// </param>
	/// <returns>
	/// インスタンス生成したアドレス値
	/// </returns>
	static TextInterFace* Create(const std::string& string,const Font& font_);


	/// <summary>
	/// テキストファイルまたはCSVの読み込み用文字列を作成します
	/// </summary>
	/// <param name="filepath_"></param>
	/// <param name="format"></param>
	/// <param name="font_"></param>
	/// <returns></returns>
	static TextInterFace* Create(const std::string& filepath_, const FormatText& format, const Font& font_);


	/// <summary>
	/// テキストファイルまたはCSVファイル読み込みを行います
	/// </summary>
	/// <param name="readertype">
	/// 読み込む方法
	/// </param>
	/// <returns>
	/// 読み込んだファイルの文字列
	/// </returns>
	Array<String> ReadText(const ReaderType& readertype);


	/// <summary>
	/// 文字列配列を格納します
	/// </summary>
	/// <param name="arrayString_">
	/// 格納しておく文字列配列
	/// </param>
	void setArrayString(const Array<String>& arrayString_);


	/// <summary>
	/// 格納されている文字列配列を返します
	/// </summary>
	Array<String> getArrayString()const;


	/// <summary>
	/// 文字列に文字列配列の要素を代入します
	/// </summary>
	/// <param name="arrayString_">
	/// 文字列配列
	/// </param>
	/// <param name="number">
	/// 代入する番号
	/// </param>
	void StringAssignment(const Array<String>& arrayString_ ,const size_t& number);


	/// <summary>
	/// フォントを変更します
	/// </summary>
	/// <param name="font_">
	/// 設定するフォント
	/// </param>
	void ChengeFont(const Font& font_);


private:
	/// <summary>
	/// 文字を生成します
	/// </summary>
	/// <param name="string">
	/// 指定する文字
	/// </param>
	/// <param name="font_">
	/// フォント
	/// </param>
	TextInterFace(const std::string& string , const Font& font_);


	/// <summary>
	/// テキストファイルまたはCSVの読み込み用文字列を作成します
	/// </summary>
	/// <param name="filepath_">
	/// ファイルパス
	/// </param>
	/// <param name="format">
	/// ファイル形式
	/// </param>
	/// <param name="font_">
	/// フォント
	/// </param>
	TextInterFace(const std::string& filepath_, const FormatText& format, const Font& font_);


	/// <summary>
	/// テキストを全て読み込みます
	/// </summary>
	/// <param name="fin">
	/// 読み込む形式
	/// </param>
	/// <returns>
	/// 読み込みをした文字列Vector
	/// </returns>
	Array<String> ReadLine();


	/// <summary>
	/// テキストを1行ごとに読み込みます
	/// </summary>
	/// <param name="fin">
	/// 読み込む形式
	/// </param>
	/// <returns>
	/// 読み込みをした文字Vector
	/// </returns>
	Array<String> ReadLen();


	/// <summary>
	/// テキストを1文字ずつ読み込みます
	/// </summary>
	/// <returns>
	/// 読み込みをした文字Vector
	/// </returns>
	Array<String> ReadChar();


	/// <summary>
	/// CSVファイルの読み込み
	/// </summary>
	/// <returns>
	/// 読み込みをした文字Vector
	/// </returns>
	Array<String> ReadCsv();


private:
	Vec2			position;			//位置
	std::string		filepath;			//ファイルパス
	FormatText		formattext;			//ファイル形式
	String			text;				//テキスト
	Font*			font;				//フォント
	Array<String>   strings;			//文字配列
};
/*ファイル読み込み用テキストを生成します*/
inline TextInterFace::TextInterFace(const std::string& filepath_, const FormatText& format, const Font& font_)
{
	this->filepath = filepath_;
	this->formattext = format;
	this->position = {};
	this->font = new Font(font_);
}
/*文字列を生成します*/
inline TextInterFace::TextInterFace(const std::string& string,const Font& font_)
{
	this->text.narrow() = string;
	this->position = {};
	this->font = new Font(font_);
}
/*文字列を生成します*/
inline TextInterFace* TextInterFace::Create(const std::string& string,const Font& font_)
{
	return new TextInterFace(string,font_);
}
/*テキストファイルまたはCSVの読み込み用文字列を作成します*/
inline TextInterFace* TextInterFace::Create(const std::string& filepath_, const FormatText& format, const Font& font_)
{
	return new TextInterFace(filepath_, format, font_);
}
/*デストラクタ*/
inline TextInterFace::~TextInterFace()
{
	if (this->font)
	{
		delete this->font;
		this->font = nullptr;
	}
}
/*文字列に文字列配列の要素を代入します*/
inline void TextInterFace::StringAssignment(const Array<String>& arrayString_, const size_t& number)
{
	if (number >= arrayString_.size())
	{
		return;
	}
	this->text = arrayString_[number];
}
/*フォントを設定・変更します*/
inline void TextInterFace::ChengeFont(const Font& font_)
{
	if (this->font)
	{
		delete this->font;
	}
	this->font = new Font(font_);
}
/*引数の文字を描画します*/
inline void TextInterFace::draw(const String& string_, const Vec2& position_, const Color& color, const double& degree)
{
	const Font& f = *this->font;
	//行列の計算
	Graphics2D::SetTransform(
		Mat3x2::Scale(this->font->size(), this->font->height)*
		Mat3x2::Rotate(degree)*
		Mat3x2::Translate(position_)
	);
	f(string_).draw(position_, color);
}
/*文字を出力します*/
inline void TextInterFace::draw(const Color& color)
{
	const Font& f = *this->font;
	f(this->text).draw(this->position,color);
}
/*指定の位置に文字を出力します*/
inline void TextInterFace::draw(const Vec2& position_ , const Color& color)
{
	const Font& f = *this->font;
	f(this->text).draw(position_,color);
}
/*文字を回転させて出力をします*/
inline void TextInterFace::draw(const double& degree,const Color& color)
{
	const Font& f = *this->font;

	//行列の計算
	Graphics2D::SetTransform(
		Mat3x2::Scale(this->font->size() ,this->font->height)*
		Mat3x2::Rotate(degree)*
		Mat3x2::Translate(this->position)
	);
	f(this->text).draw(this->position,color);
}
/*テキストファイルまたはCSVファイル読み込みを行います*/
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
/*テキストを全て読み込みます*/
inline Array<String> TextInterFace::ReadLine()
{
	//文字列を格納するVector
	Array<String> readtext;
	//読み込みをした文字を一時的に使用する文字列
	String line;
	//読み込みに必要なリーダー
	TextReader textreader;

	//テキストファイルのフォーマットのみ適用
	if (this->formattext == FormatText::TXT && textreader.open(Widen(this->filepath)))
	{
		line = textreader.readAll();
		readtext.push_back(line);
		textreader.close();
	}
	return readtext;
}
/*テキストを1行ごとに読み込みます*/
inline Array<String> TextInterFace::ReadLen()
{
	//文字列を格納するVector
	Array<String> readtext;
	//読み込みをした文字を一時的に使用する文字列
	String line;
	//読み込みに必要なリーダー
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
/*テキストを1文字ずつ読み込みます*/
inline Array<String> TextInterFace::ReadChar()
{
	//文字列を格納するVector
	Array<String> readtext;
	//読み込みをした文字を一時的に使用する文字列
	String line;
	//読み込みに必要なリーダー
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
/*CSVファイルを読み込みます*/
inline Array<String> TextInterFace::ReadCsv()
{
	//文字列を格納するVector
	Array<String> readtext;
	//読み込みをした文字を一時的に使用する文字列
	String        line;
	//読み込みに必要なリーダー
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
/*文字列を格納します*/
inline void TextInterFace::setArrayString(const Array<String>& arrayString_)
{
	this->strings = arrayString_;
}
/*格納していた文字列を返します*/
inline Array<String> TextInterFace::getArrayString()const
{
	return this->strings;
}