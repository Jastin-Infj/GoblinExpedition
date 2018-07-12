// <author>Mikhail Semenov</author>
// <date>2015-03-14</date>
// <summary>Implementation of the steps functions</summary>

//
//	modified for Siv3D
//

//
// Licenced with the Code Project Open Licence (CPOL)
// http://www.codeproject.com/info/cpol10.aspx
//

# pragma once
#include <type_traits>

namespace loop
{
	template <class T, class N, class S>
	class steps_class
	{
	public:

		class steps_iterator : public std::iterator<std::forward_iterator_tag, T>
		{
			N m_step_counter;
			T m_counter;
			S m_step;

		public:

			steps_iterator()
				: m_step_counter(N()) {}
			
			constexpr steps_iterator(N steps_count, T start, S step)
				: m_step_counter(steps_count)
				, m_counter(start)
				, m_step(step) {}

			steps_iterator& operator++()
			{
				--m_step_counter;
				m_counter += m_step;
				return *this;
			}

			steps_iterator operator++(int)
			{
				steps_iterator  it = *this;
				--m_step_counter;
				m_counter += m_step;
				return it;
			}

			const T& operator*() const
			{
				return m_counter;
			}

			const T* operator->() const
			{
				return &m_counter;
			}

			bool operator== (const steps_iterator& r) const
			{
				return m_step_counter == r.m_step_counter;
			}

			bool operator!= (const steps_iterator& r) const
			{
				return !(m_step_counter == r.m_step_counter);
			}
		};

		typedef steps_iterator iterator;

	private:
		iterator m_end_iterator;
		iterator m_start_iterator;

	public:

		constexpr steps_class(T start, N step_count, S step)
			: m_start_iterator(step_count, start, step) {}

		iterator begin() const
		{
			return m_start_iterator;
		}

		iterator end() const { return m_end_iterator; }
	};

	template <class T, class N, class S = int>
	inline constexpr auto step(T a, N n, S s = 1)
	{
		static_assert(std::is_integral<N>::value, "step: the second parameter should be of integral type");
		return steps_class<decltype(a + s), N, S>(a, n, s);
	}

	template <class N>
	inline constexpr auto step(N n)
	{
		static_assert(std::is_integral<N>::value, "step: parameter should be of integral type");
		return steps_class<N, N, int>(N(0), n, 1);
	}

	template <class N>
	inline constexpr auto step_backward(N n)
	{
		static_assert(std::is_integral<N>::value, "step_backward: parameter should be of integral type");
		return steps_class<N, N, int>(n + int(-1), n, int(-1));
	}

	template <class T, class U>
	class CommonType
	{
		typedef typename std::remove_reference<T>::type T1;
		typedef typename std::remove_reference<U>::type U1;

	public:
		typedef decltype(T1() + U1()) type;
	};

	template <class T>
	class CommonType<T, T>
	{
		typedef typename std::remove_reference<T>::type T1;

	public:
		typedef T1 type;
	};

	template <class T, class U, class S = int,
	class StartType = typename CommonType<T, U>::type,
	class CounterType = typename CommonType<std::size_t, StartType>::type>
		inline steps_class<StartType, CounterType, S> step_to(T a, U b, S s = 1)
	{
		static_assert(std::is_integral<StartType>::value, "step_to requires integral parameters");
		CounterType  n = 0;

		if (s == 0 || b != a && (b < a) != (s < 0))
		{
			n = 0;
		}
		else
		{
			S abs_s = s > 0 ? s : -s;
			CounterType diff = b > a ? (long long) b - (long long) a : (long long) a - (long long) b;

			if (abs_s == 1)
				n = diff;
			else
				n = diff / abs_s;

			n++;
		}
		return steps_class<StartType, CounterType, S>(a, n, s);
	}

	template <class T, class U, class S = int,
	class StartType = typename CommonType<T, U>::type,
	class CounterType = typename CommonType<std::size_t, StartType>::type>
		inline steps_class<StartType, CounterType, S> step_until(T a, U b, S s = 1)
	{
		static_assert(std::is_integral<StartType>::value, "step_until requires integral parameters");
		CounterType  n;

		if (b == a || s == 0 || (b < a) != (s < 0))
		{
			n = 0;
		}
		else
		{
			S abs_s = s > 0 ? s : -s;
			CounterType diff = b > a ? (long long) b - (long long) a : (long long) a - (long long) b;


			if (abs_s == 1)
				n = diff;
			else
				n = diff / abs_s;

			CounterType finish = a + n*s;
			if (finish != b)
			{
				n++;
			}
		}
		return steps_class<StartType, CounterType, S>(a, n, s);
	}
}
