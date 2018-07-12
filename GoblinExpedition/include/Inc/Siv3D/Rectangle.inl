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
	template <class SizeType, class ElementType>
	inline SizeType Rectangle<SizeType, ElementType>::_get_tl() const
	{
		return pos;
	}

	template< class SizeType, class ElementType>
	inline SizeType Rectangle<SizeType, ElementType>::_get_tr() const
	{
		return{ x + w - 1, y };
	}

	template <class SizeType, class ElementType>
	inline SizeType Rectangle<SizeType, ElementType>::_get_bl() const
	{
		return{ x, y + h - 1 };
	}

	template <class SizeType, class ElementType>
	inline SizeType Rectangle<SizeType, ElementType>::_get_br() const
	{
		return{ x + w - 1, y + h - 1 };
	}

	template <class SizeType, class ElementType>
	inline SizeType Rectangle<SizeType, ElementType>::_get_center() const
	{
		return{ x + w / 2, y + h / 2 };
	}

	template <class SizeType, class ElementType>
	inline Line Rectangle<SizeType, ElementType>::_get_top() const
	{
		return{ tl, tr };
	}

	template <class SizeType, class ElementType>
	inline Line Rectangle<SizeType, ElementType>::_get_right() const
	{
		return{ tr, br };
	}

	template <class SizeType, class ElementType>
	inline Line Rectangle<SizeType, ElementType>::_get_bottom() const
	{
		return{ br, bl };
	}

	template <class SizeType, class ElementType>
	inline Line Rectangle<SizeType, ElementType>::_get_left() const
	{
		return{ bl, tl };
	}
}
