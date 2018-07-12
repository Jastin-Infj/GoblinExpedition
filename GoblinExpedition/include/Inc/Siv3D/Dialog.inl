//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	namespace Dialog
	{
		/// <summary>
		/// ファイルオープンダイアログを使って画像ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <remarks>
		/// BMP, PNG, JPEG, GIF 形式の画像ファイルのみ表示されます。
		/// </remarks>
		/// <returns>
		/// 選択された画像ファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenBasicImage(const String& title, const FilePath& initialPath)
		{
			return GetOpen({
				ExtensionFilter::BasicImage,
				ExtensionFilter::BMP,
				ExtensionFilter::PNG,
				ExtensionFilter::JPEG,
				ExtensionFilter::GIF
			},
			title,
			initialPath
			);
		}

		/// <summary>
		/// ファイルオープンダイアログを使って画像ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択された画像ファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenImage(const String& title, const FilePath& initialPath)
		{
			return GetOpen({
				ExtensionFilter::AllImage,
				ExtensionFilter::BMP,
				ExtensionFilter::PNG,
				ExtensionFilter::JPEG,
				ExtensionFilter::GIF,
				ExtensionFilter::TGA,
				ExtensionFilter::DDS,
				ExtensionFilter::WebP,
				ExtensionFilter::JPEG2000,
				ExtensionFilter::TIFF,
				ExtensionFilter::PPM,
			},
			title,
			initialPath
			);
		}

		/// <summary>
		/// ファイルオープンダイアログを使ってオーディオファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択されたオーディオファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenSound(const String& title, const FilePath& initialPath)
		{
			return GetOpen({
				ExtensionFilter::AllSound,
				ExtensionFilter::WAVE,
				ExtensionFilter::MP3,
				ExtensionFilter::OggVorbis,
				ExtensionFilter::AAC,
				ExtensionFilter::WMA,
			},
			title,
			initialPath
			);
		}

		/// <summary>
		/// ファイルオープンダイアログを使って MIDI ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択された MIDI ファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenMidi(const String& title, const FilePath& initialPath)
		{
			return GetOpen({
				ExtensionFilter::MIDI
			},
			title,
			initialPath
			);
		}

		/// <summary>
		/// ファイルオープンダイアログを使ってテキストファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択されたテキストファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenText(const String& title, const FilePath& initialPath)
		{
			return GetOpen({
				ExtensionFilter::Text
			},
			title,
			initialPath
			);
		}

		/// <summary>
		/// ファイルオープンダイアログを使って動画ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択された動画ファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenVideo(const String& title, const FilePath& initialPath)
		{
			return GetOpen({
				ExtensionFilter::AllVideo,
				ExtensionFilter::AVI,
				ExtensionFilter::MP4,
				ExtensionFilter::WMV,
				ExtensionFilter::MOV
			},
			title,
			initialPath
			);
		}

		/// <summary>
		/// ファイルオープンダイアログを使ってファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択されたファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenAll(const String& title, const FilePath& initialPath)
		{
			return GetOpen({
				ExtensionFilter::All
			},
			title,
			initialPath
			);
		}

		/// <summary>
		/// ファイル保存ダイアログを使って画像ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <remarks>
		/// BMP, PNG, JPEG, GIF 形式の画像ファイルのみ表示されます。
		/// </remarks>
		/// <returns>
		/// 選択されたオーディオファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetSaveBasicImage(const String& title, const FilePath& initialPath)
		{
			return GetSave({
				ExtensionFilter::PNG,
				ExtensionFilter::BMP,
				ExtensionFilter::JPEG,
				ExtensionFilter::GIF,
				ExtensionFilter::BasicImage
			},
			title,
			initialPath
			);
		}

		/// <summary>
		/// ファイル保存ダイアログを使って画像ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択された画像ファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetSaveImage(const String& title, const FilePath& initialPath)
		{
			return GetSave({
				ExtensionFilter::PNG,
				ExtensionFilter::BMP,
				ExtensionFilter::JPEG,
				ExtensionFilter::GIF,
				ExtensionFilter::TGA,
				ExtensionFilter::DDS,
				ExtensionFilter::WebP,
				ExtensionFilter::JPEG2000,
				ExtensionFilter::TIFF,
				ExtensionFilter::PPM,
				ExtensionFilter::AllImage
			},
			title,
			initialPath
			);
		}

		/// <summary>
		/// ファイル保存ダイアログを使ってオーディオファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択されたオーディオファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetSaveSound(const String& title, const FilePath& initialPath)
		{
			return GetSave({
				ExtensionFilter::WAVE,
				ExtensionFilter::OggVorbis,
				ExtensionFilter::MP3,
				ExtensionFilter::AAC,
				ExtensionFilter::WMA,
				ExtensionFilter::AllSound
			},
			title,
			initialPath
			);
		}

		/// <summary>
		/// ファイル保存ダイアログを使ってテキストファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択されたテキストファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetSaveText(const String& title, const FilePath& initialPath)
		{
			return GetSave({
				ExtensionFilter::Text
			},
			title,
			initialPath
			);
		}

		/// <summary>
		/// ファイル保存ダイアログを使って動画ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択された動画のパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetSaveVideo(const String& title, const FilePath& initialPath)
		{
			return GetSave({
				ExtensionFilter::AVI
			},
			title,
			initialPath
			);
		}

		/// <summary>
		/// ファイル保存ダイアログを使ってファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択されたファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetSaveAll(const String& title, const FilePath& initialPath)
		{
			return GetSave({
				ExtensionFilter::All
			},
			title,
			initialPath
			);
		}
	}
}
