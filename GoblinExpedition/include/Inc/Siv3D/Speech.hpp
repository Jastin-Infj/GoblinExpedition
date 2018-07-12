//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2015 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Format.hpp"
# include "Duration.hpp"

namespace s3d
{
	// https://msdn.microsoft.com/en-us/library/hh361638(v=office.14).aspx
	enum class Language
	{
		English = 0x409,

		Japanese = 0x411,

		Spanish = 0x40a,

		French = 0x40c,

		German = 0x407,

		ChinesePRC = 0x804,

		ChineseTaiwan = 0x404,

		Unspecified = 0x000,
	};

	namespace Speech
	{
		/// <summary>
		/// 指定した言語での読み上げが可能かを調べます。
		/// </summary>
		/// <param name="language">
		/// 言語
		/// </param>
		/// <remarks>
		/// Microsoft Speech Platform - Runtime Languages をインストールすると言語が使用可能になります。
		/// </remarks>
		/// <returns>
		/// 読み上げが可能な場合 true, それ以外の場合は false
		/// </returns>
		bool HasLanguage(Language language);

		/// <summary>
		/// デフォルトの読み上げ言語を設定します。
		/// </summary>
		/// <param name="language">
		/// 言語
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetDefaultLanguage(Language language);

		/// <summary>
		/// 現在のデフォルトの読み上げ言語を取得します。
		/// </summary>
		/// <returns>
		/// 現在のデフォルトの読み上げ言語
		/// </returns>
		Language GetDefaultLanguage();

		/// <summary>
		/// 文章の読み上げを再生します。
		/// </summary>
		/// <param name="text">
		/// 読み上げる文章
		/// </param>
		/// <param name="language">
		/// 言語
		/// </param>
		/// <param name="isXML">
		/// 文章が SAPI XML TTS 形式であるか
		/// </param>
		/// <returns>
		/// 再生の開始に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool Speak(const String& text, Language language = Language::Unspecified, bool isXML = true);

		/// <summary>
		/// 文章の読み上げが再生中であるかを取得します。
		/// </summary>
		/// <returns>
		/// 再生中の場合 true, それ以外の場合は false
		/// </returns>
		bool IsSpeaking();

		/// <summary>
		/// 文章の読み上げを一時停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void Pause();

		/// <summary>
		/// 一時停止した文章の読み上げを再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void Resume();

		/// <summary>
		/// 文章の読み上げの音量を設定します。
		/// </summary>
		/// <param name="volume">
		/// 設定する音量 [0.0, 1.0]
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetVolume(double volume);

		/// <summary>
		/// 文章の読み上げの音量を取得します。
		/// </summary>
		/// <returns>
		/// 文章の読み上げの音量 [0.0, 1.0]
		/// </returns>
		double GetVolume();

		/// <summary>
		/// 文章の読み上げの速度を設定します。
		/// </summary>
		/// <param name="volume">
		/// 設定する速度 [-10, 10]
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetSpeed(int32 speed);

		/// <summary>
		/// 文章の読み上げの速度を取得します。
		/// </summary>
		/// <returns>
		/// 文章の読み上げの速度 [-10, 10]
		/// </returns>
		int32 GetSpeed();
	}

	namespace detail
	{
		inline void FormatL(const FormatData&)
		{
			return;
		}

		template <class Type, class ... Args>
		inline void FormatL(FormatData& formatData, const Type& value, const Args& ... args)
		{
			std::wostringstream ws;

			ws.imbue(std::locale(""));

			ws << value;

			formatData.string.append(ws.str());

			FormatL(formatData, args...);
		}

		template <class ... Args>
		inline String FormatL(const Args& ... args)
		{
			static_assert(format_validation<Args...>::value, "type \"char*\" cannot be used in Format()");

			FormatData formatData;

			FormatL(formatData, args...);

			return std::move(formatData.string);
		}

		inline String FormatL(wchar ch)
		{
			return String(1, ch);
		}

		inline String FormatL(const wchar* const str)
		{
			return String(str);
		}

		inline String FormatL(const String& str)
		{
			return str;
		}

		inline String FormatL(String&& str)
		{
			return std::move(str);
		}
	}

	inline void Say(const String& text)
	{
		Speech::Speak(text);
	}

	template <class ... Args>
	inline void Say(const Args& ... args)
	{
		Say(detail::FormatL(args...));
	}
}
