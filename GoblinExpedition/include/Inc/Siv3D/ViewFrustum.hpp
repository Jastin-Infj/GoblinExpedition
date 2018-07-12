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
# include <DirectXCollision.h>
# include "Fwd.hpp"
# include "DirectXMathUtility.hpp"
# include "Quaternion.hpp"

namespace s3d
{
	struct ViewFrustum : DirectX::BoundingFrustum
	{
		using DirectX::BoundingFrustum::BoundingFrustum;

		std::array<Vec3, 8> getCorners() const;

		template <class Primitive>
		bool intersects(const Primitive& primitive) const
		{
			return Geometry3D::Intersect(*this, primitive);
		}

		template <class Primitive>
		bool contains(const Primitive& primitive) const
		{
			return Geometry3D::Contains(*this, primitive);
		}
	};
}
