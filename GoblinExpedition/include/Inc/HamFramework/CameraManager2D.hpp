//-----------------------------------------------
//
//	This file is part of the HamFramework for Siv3D.
//
//	Copyright (C) 2014-2016 Hamukun
//	Copyright (C) 2014-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "../Siv3D.hpp"

namespace ham
{
	class BasicCamera2D
	{
	protected:

		s3d::Vec2 m_pos = s3d::Window::BaseSize() * 0.5;

		double m_scale = 1.0;

	public:

		BasicCamera2D() = default;

		BasicCamera2D(const s3d::Vec2& pos, double scale)
			: m_pos(pos)
			, m_scale(scale)
		{

		}

		virtual ~BasicCamera2D() {}

		void setPos(const s3d::Vec2& pos)
		{
			m_pos = pos;
		}

		const s3d::Vec2& getPos() const
		{
			return m_pos;
		}

		void setScale(double scale)
		{
			m_scale = scale;
		}

		double getScale() const
		{
			return m_scale;
		}

		s3d::RectF getCameraArea() const
		{
			return s3d::RectF(m_pos - s3d::Window::BaseSize() * 0.5 / m_scale, s3d::Window::BaseSize() / m_scale);
		}

		s3d::Mat3x2 getMat3x2() const
		{
			return s3d::Mat3x2::Scale(m_scale).translate(s3d::Window::BaseSize() * 0.5 - m_scale * m_pos);
		}

		s3d::Transformer2D createTransformer() const
		{
			return s3d::Transformer2D(getMat3x2(), true);
		}
	};

	class Camera2D : public BasicCamera2D
	{
	private:

		void controlWithKeyboard(double speed, double scaleRatio)
		{

			if (m_keyConfig[0].pressed)
			{
				m_targetPos.y -= (speed / m_targetScale);
			}

			if (m_keyConfig[1].pressed)
			{
				m_targetPos.x -= (speed / m_targetScale);
			}

			if (m_keyConfig[2].pressed)
			{
				m_targetPos.y += (speed / m_targetScale);
			}

			if (m_keyConfig[3].pressed)
			{
				m_targetPos.x += (speed / m_targetScale);
			}

			if (m_keyConfig[4].pressed)
			{
				m_targetScale *= scaleRatio;
			}

			if (m_keyConfig[5].pressed)
			{
				m_targetScale /= scaleRatio;
			}
		}

		void controlWithMouse(bool useMouseControl, double speed, double scaleRatio, double mouseSpeedRatio)
		{
			if (!useMouseControl)
			{
				m_grabPos = s3d::none;

				return;
			}

			s3d::Mouse::PushTransform(s3d::Mouse::GetTransform().inverse());
			{
				if (s3d::Input::MouseR.clicked)
				{
					m_grabPos = s3d::Mouse::Pos();
				}
				else if (m_grabPos)
				{
					const s3d::Point delta = s3d::Mouse::Pos() - m_grabPos.value();

					m_targetPos += mouseSpeedRatio * speed * delta / m_targetScale;

					if (s3d::Input::MouseR.released)
					{
						m_grabPos = s3d::none;
					}
				}
			}
			s3d::Mouse::PopTransform();

			if (s3d::Mouse::Wheel() < 0)
			{
				m_targetScale *= scaleRatio;
			}

			if (s3d::Mouse::Wheel() > 0)
			{
				m_targetScale /= scaleRatio;
			}
		}

	protected:

		s3d::Vec2 m_targetPos = BasicCamera2D::m_pos;

		double m_targetScale = BasicCamera2D::m_scale;

		std::array<s3d::Key, 6> m_keyConfig =
		{
			s3d::Input::KeyW, s3d::Input::KeyA, s3d::Input::KeyS, s3d::Input::KeyD,
			s3d::Input::KeyUp, s3d::Input::KeyDown
		};

		s3d::Optional<s3d::Point> m_grabPos;

	public:

		Camera2D() = default;

		Camera2D(const s3d::Vec2& pos, double scale)
			: BasicCamera2D(pos, scale)
			, m_targetPos(pos)
			, m_targetScale(scale)
		{

		}

		virtual ~Camera2D() 
		{

		}

		void update(double speed = 10.0, double scaleRatio = 1.1, double mouseSpeedRatio = 0.01, double lerpRatio = 0.2, bool useKeyControl = true, bool useMouseControl = true)
		{
			if (useKeyControl)
			{
				controlWithKeyboard(speed, scaleRatio);
			}

			if (useMouseControl)
			{
				controlWithMouse(useMouseControl, speed, scaleRatio, mouseSpeedRatio);
			}

			//À•W‚É‚æ‚Á‚ÄˆÊ’u‚ð•Ï‰»‚³‚¹‚é
			m_pos = s3d::Math::Lerp(m_pos, m_targetPos, lerpRatio);

			m_scale = s3d::Math::Lerp(m_scale, m_targetScale, lerpRatio);
		}

		void draw(const s3d::Color& color = s3d::Palette::White) const
		{
			if (!m_grabPos)
			{
				return;
			}

			const double radius = 12.0;
			const s3d::Point delta = s3d::Mouse::Pos() - m_grabPos.value();
			const double length = delta.length();

			s3d::Circle(m_grabPos.value(), radius).drawFrame(2.0, 2.0, color);

			if (length >= radius * 2)
			{				
				const s3d::Vec2 direction = delta / length;
				const s3d::Vec2 normalDirection{ direction.y, -direction.x };
				const s3d::Vec2 leftOffset = normalDirection * 10;

				const s3d::Vec2 p0 = delta;
				const s3d::Vec2 p1 = s3d::Vec2(direction).setLength(radius * 1.2) - leftOffset;
				const s3d::Vec2 p2 = s3d::Vec2(direction).setLength(radius * 1.8);
				const s3d::Vec2 p3 = s3d::Vec2(direction).setLength(radius * 1.2) + leftOffset;

				s3d::Quad(p1, p2, p3, p0).moveBy(m_grabPos.value()).draw(color);
			}
		}

		void setKeyConfig(const std::array<s3d::Key, 6>& keys)
		{
			m_keyConfig = keys;
		}
		void setTargetPos(const Vec2& targetPos)
		{
			m_targetPos = targetPos;
		}

		void setTargetScale(const double targetScale)
		{
			m_targetScale = targetScale;
		}
	};

	class CameraBox2D : public Camera2D
	{
	private:

		void controlWithKeyboard(double speed, double scaleRatio)
		{
			if (m_keyConfig[0].pressed)
			{
				m_targetPos.y += (speed / m_targetScale);
			}

			if (m_keyConfig[1].pressed)
			{
				m_targetPos.x -= (speed / m_targetScale);
			}

			if (m_keyConfig[2].pressed)
			{
				m_targetPos.y -= (speed / m_targetScale);
			}

			if (m_keyConfig[3].pressed)
			{
				m_targetPos.x += (speed / m_targetScale);
			}

			if (m_keyConfig[4].pressed)
			{
				m_targetScale *= scaleRatio;
			}

			if (m_keyConfig[5].pressed)
			{
				m_targetScale /= scaleRatio;
			}
		}

		void controlWithMouse(bool useMouseControl, double speed, double scaleRatio, double mouseSpeedRatio)
		{
			if (!useMouseControl)
			{
				m_grabPos = s3d::none;

				return;
			}

			s3d::Mouse::PushTransform(s3d::Mouse::GetTransform().inverse());
			{
				if (s3d::Input::MouseR.clicked)
				{
					m_grabPos = s3d::Mouse::Pos();
				}
				else if (m_grabPos)
				{
					const s3d::Point delta = s3d::Mouse::Pos() - m_grabPos.value();

					m_targetPos += mouseSpeedRatio * speed * s3d::Point(delta.x, -delta.y) / m_targetScale;

					if (s3d::Input::MouseR.released)
					{
						m_grabPos = s3d::none;
					}
				}
			}
			s3d::Mouse::PopTransform();

			if (s3d::Mouse::Wheel() < 0)
			{
				m_targetScale *= scaleRatio;
			}

			if (s3d::Mouse::Wheel() > 0)
			{
				m_targetScale /= scaleRatio;
			}
		}

	public:

		using Camera2D::Camera2D;

		virtual ~CameraBox2D() {}

		void update(double speed = 10.0, double scaleRatio = 1.1, double mouseSpeedRatio = 0.01, double lerpRatio = 0.2, bool useKeyControl = true, bool useMouseControl = true)
		{
			if (useKeyControl)
			{
				controlWithKeyboard(speed, scaleRatio);
			}

			if (useMouseControl)
			{
				controlWithMouse(useMouseControl, speed, scaleRatio, mouseSpeedRatio);
			}

			m_pos = s3d::Math::Lerp(m_pos, m_targetPos, lerpRatio);

			m_scale = s3d::Math::Lerp(m_scale, m_targetScale, lerpRatio);
		}

		s3d::Mat3x2 getMat3x2() const
		{
			return s3d::Mat3x2::Scale(m_scale, -m_scale).translate(s3d::Window::BaseSize() * 0.5 - s3d::Vec2(m_scale, -m_scale) * m_pos);
		}

		s3d::Transformer2D createTransformer() const
		{
			return s3d::Transformer2D(getMat3x2(), true);
		}
	};
}
