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
# include <cassert>

namespace s3d
{
	/// <summary>
	/// ストップウォッチを開始・再開します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void Stopwatch::start()
	{
		if (!m_pausing)
		{
			return;
		}

		m_startTimeMillisec = Time::GetMillisec();

		m_isActive = true;

		m_pausing = false;
	}

	/// <summary>
	/// ストップウォッチの経過時間を[ミリ秒]で返します。
	/// </summary>
	/// <returns>
	/// ストップウォッチの経過時間[ミリ秒]
	/// </returns>
	inline int32 Stopwatch::ms() const
	{
		if (!m_isActive)
		{
			return 0;
		}

		if (m_pausing)
		{
			return m_accumulationMillisec;
		}

		return (m_accumulationMillisec + (Time::GetMillisec() - m_startTimeMillisec));
	}

	/// <summary>
	/// ストップウォッチを一時停止します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void Stopwatch::pause()
	{
		m_accumulationMillisec = ms();

		m_pausing = true;
	}

	/// <summary>
	/// ストップウォッチが一時停止中である場合、再開します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void Stopwatch::resume()
	{
		if (!isPaused())
		{
			return;
		}

		start();
	}

	/// <summary>
	/// ストップウォッチを停止し、経過時間を 0 にリセットします。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void Stopwatch::reset() noexcept
	{
		m_accumulationMillisec = 0;

		m_isActive = false;

		m_pausing = true;
	}

	/// <summary>
	/// 経過時間を 0 にリセットして、ストップウォッチを開始します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void Stopwatch::restart()
	{
		reset();

		start();
	}

	/// <summary>
	/// ストップウォッチの経過時間を変更します。
	/// </summary>
	/// <param name="time">
	/// 新しく設定する経過時間
	/// </param>
	/// <returns>
	/// なし
	/// </returns>
	inline void Stopwatch::set(const MillisecondsF& time)
	{
		m_isActive |= (time.count() != 0);

		m_accumulationMillisec = static_cast<uint32>(time.count());

		m_startTimeMillisec = Time::GetMillisec();
	}

	/// <summary>
	/// ストップウォッチを開始・再開します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void Stopwatch64::start()
	{
		if (!m_pausing)
		{
			return;
		}

		m_startTimeMillisec = Time::GetMillisec64();

		m_isActive = true;

		m_pausing = false;
	}

	/// <summary>
	/// ストップウォッチの経過時間を[ミリ秒]で返します。
	/// </summary>
	/// <returns>
	/// ストップウォッチの経過時間[ミリ秒]
	/// </returns>
	inline int64 Stopwatch64::ms() const
	{
		if (!m_isActive)
		{
			return 0;
		}

		if (m_pausing)
		{
			return m_accumulationMillisec;
		}

		return (m_accumulationMillisec + (Time::GetMillisec64() - m_startTimeMillisec));
	}

	/// <summary>
	/// ストップウォッチを一時停止します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void Stopwatch64::pause()
	{
		m_accumulationMillisec = ms();

		m_pausing = true;
	}

	/// <summary>
	/// ストップウォッチが一時停止中である場合、再開します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void Stopwatch64::resume()
	{
		if (!isPaused())
		{
			return;
		}

		start();
	}

	/// <summary>
	/// ストップウォッチを停止し、経過時間を 0 にリセットします。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void Stopwatch64::reset() noexcept
	{
		m_accumulationMillisec = 0;

		m_isActive = false;

		m_pausing = true;
	}

	/// <summary>
	/// 経過時間を 0 にリセットして、ストップウォッチを開始します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void Stopwatch64::restart()
	{
		reset();

		start();
	}

	/// <summary>
	/// ストップウォッチの経過時間を変更します。
	/// </summary>
	/// <param name="time">
	/// 新しく設定する経過時間
	/// </param>
	/// <returns>
	/// なし
	/// </returns>
	inline void Stopwatch64::set(const MillisecondsF& time)
	{
		m_isActive |= (time.count() != 0);

		m_accumulationMillisec = static_cast<uint64>(time.count());

		m_startTimeMillisec = Time::GetMillisec64();
	}

	/// <summary>
	/// ストップウォッチを開始・再開します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void StopwatchMicrosec::start()
	{
		if (!m_pausing)
		{
			return;
		}

		m_isActive = true;

		m_pausing = false;

		m_startTimeMicrosec = Time::GetMicrosec();
	}

	/// <summary>
	/// ストップウォッチの経過時間を[マイクロ秒]で返します。
	/// </summary>
	/// <returns>
	/// ストップウォッチの経過時間[マイクロ秒]
	/// </returns>
	inline int64 StopwatchMicrosec::us() const
	{
		const int64 t = Time::GetMicrosec();

		if (!m_isActive)
		{
			return 0;
		}

		if (m_pausing)
		{
			return m_accumulationMicrosec;
		}

		return m_accumulationMicrosec + (t - m_startTimeMicrosec);
	}

	/// <summary>
	/// ストップウォッチを一時停止します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void StopwatchMicrosec::pause()
	{
		m_accumulationMicrosec = us();

		m_pausing = true;
	}

	/// <summary>
	/// ストップウォッチが一時停止中である場合、再開します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void StopwatchMicrosec::resume()
	{
		if (!isPaused())
		{
			return;
		}

		start();
	}

	/// <summary>
	/// ストップウォッチを停止し、経過時間を 0 にリセットします。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void StopwatchMicrosec::reset() noexcept
	{
		m_accumulationMicrosec = 0;

		m_isActive = false;

		m_pausing = true;
	}

	/// <summary>
	/// 経過時間を 0 にリセットして、ストップウォッチを開始します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	inline void StopwatchMicrosec::restart()
	{
		reset();

		start();
	}

	/// <summary>
	/// ストップウォッチの経過時間を変更します。
	/// </summary>
	/// <param name="time">
	/// 新しく設定する経過時間
	/// </param>
	/// <returns>
	/// なし
	/// </returns>
	inline void StopwatchMicrosec::set(const MicrosecondsF& time)
	{
		m_isActive |= (time.count() != 0);

		m_accumulationMicrosec = static_cast<int64>(time.count());

		m_startTimeMicrosec = Time::GetMicrosec();
	}
}
