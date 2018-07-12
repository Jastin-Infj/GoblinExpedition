//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

namespace s3d
{
	enum class LogDescription
	{
		Error,		// Less
		Fail,		// Less
		Warning,	// Less
		Script,		// Less
		App,		// Normal
		Info,		// Normal
		Debug,		// More
		NumberOfDesc,
	};

	void OutputLog(LogDescription desc, const String& str);

	void OutputLog(LogDescription desc, const Image& image, const String& str);

	template <class ... Args>
	inline void OutputLog(const LogDescription desc, const Args& ... args)
	{
		OutputLog(desc, Format(args...));
	}

	template <class ... Args>
	inline void OutputLog(const LogDescription desc, const Image& image, const Args& ... args)
	{
		OutputLog(desc, image, Format(args...));
	}

	void OutputLogOnce(LogDescription desc, int32 id, const String& str);

	void OutputLogOnce(LogDescription desc, int32 id, const Image& image, const String& str);

	template <class ... Args>
	inline void OutputLogOnce(LogDescription desc, const int32 id, const Args& ... args)
	{
		OutputLogOnce(desc, id, Format(args...));
	}

	template <class ... Args>
	inline void OutputLogOnce(LogDescription desc, const int32 id, const Image& image, const Args& ... args)
	{
		OutputLogOnce(desc, id, image, Format(args...));
	}
}
