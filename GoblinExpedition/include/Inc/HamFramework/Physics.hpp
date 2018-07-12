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
# include "../Siv3DAddon/Box2D.hpp"

namespace ham
{
	class PhysicsBody;
	class PhysicsShape;
	class PhysicsWheelJoint;

	struct PhysicsMaterial
	{
		double density = 1.0;

		double restitution = 0.0;

		double friction = 0.2;

		constexpr PhysicsMaterial(s3d::nullopt_t) {}

		constexpr PhysicsMaterial(double _density = 1.0, double _restitution = 0.1, double _friction = 0.2)
			: density(_density)
			, restitution(_restitution)
			, friction(_friction) {}
	};

	struct PhysicsFilter
	{
		s3d::uint16 categoryBits = 0b0000'0000'0000'0001;

		s3d::uint16 maskBits = 0b1111'1111'1111'1111;

		s3d::int16 groupIndex = 0;

		constexpr PhysicsFilter(s3d::nullopt_t) {}

		constexpr PhysicsFilter(uint16 _categoryBits = 0b0000'0000'0000'0001, uint16 _maskBits = 0b1111'1111'1111'1111u, int16 _groupIndex = 0)
			: categoryBits(_categoryBits)
			, maskBits(_maskBits)
			, groupIndex(_groupIndex) {}
	};

	struct WheelJointState
	{
		bool enableMotor = false;

		double maxMotorTorque = 1.0;

		double frequencyHz = 2.0;

		double dampingRatio = 0.7;

		constexpr WheelJointState(bool _enableMotor = false, double _maxMotorTorque = 1.0, double _frequencyHz = 2.0, double _dampingRatio = 0.7)
			: enableMotor(_enableMotor)
			, maxMotorTorque(_maxMotorTorque)
			, frequencyHz(_frequencyHz)
			, dampingRatio(_dampingRatio) {}
	};

	enum class PhysicsBodyType
	{
		Static,

		Kinematic,

		Dynamic
	};

	enum class PhysicsShapeType
	{
		Line,

		LineString,

		Circle,

		Rect,

		Triangle,

		Quad,

		Polygon
	};

	class PhysicsWorld
	{
	private:

		class CPhysicsWorld;

		std::shared_ptr<CPhysicsWorld> pImpl;

	public:

		PhysicsWorld(const s3d::Vec2& gravity = s3d::Vec2(0.0, -9.8));

		std::weak_ptr<b2World> getWorldPtr() const;

		void enableSleep(bool enable);

		bool getSleepEnabled() const;

		void setGravity(const s3d::Vec2& gravity);

		s3d::Vec2 getGravity() const;

		void update(double timeStep = 1.0 / 60.0, int32 velocityIterations = 6, int32 positionIterations = 2) const;

		void shiftOrigin(const s3d::Vec2& newOrigin);

		PhysicsBody createEmpty(const s3d::Vec2& center, PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createLine(const s3d::Vec2& center, const s3d::Vec2& begin, const s3d::Vec2& end, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createLine(const s3d::Vec2& center, const s3d::Line& line, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createLineString(const s3d::Vec2& center, const s3d::Array<s3d::Vec2>& points, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createLineString(const s3d::Vec2& center, const s3d::LineString& lineString, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createLineStringClosed(const s3d::Vec2& center, const s3d::Array<s3d::Vec2>& points, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createLineStringClosed(const s3d::Vec2& center, const s3d::LineString& lineString, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createCircle(const s3d::Vec2& center, double r, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createCircle(const s3d::Vec2& center, double r, const s3d::Vec2& offset, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createCircle(const s3d::Vec2& center, const s3d::Circle& circle, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createRect(const s3d::Vec2& center, double size, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createRect(const s3d::Vec2& center, const s3d::Vec2& size, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createRect(const s3d::Vec2& center, const s3d::Vec2& size, const s3d::Vec2& offset, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createRect(const s3d::Vec2& center, const s3d::RectF& rect, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createTriangle(const s3d::Vec2& center, double sides, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createTriangle(const s3d::Vec2& center, double sides, double angle, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createTriangle(const s3d::Vec2& center, double sides, double angle, const s3d::Vec2& offset, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createTriangle(const s3d::Vec2& center, const s3d::Vec2& p0, const s3d::Vec2& p1, const s3d::Vec2& p2, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createTriangle(const s3d::Vec2& center, const s3d::Triangle& triangle, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createQuad(const s3d::Vec2& center, const s3d::Vec2& p0, const s3d::Vec2& p1, const s3d::Vec2& p2, const s3d::Vec2& p3, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createQuad(const s3d::Vec2& center, const s3d::Quad& quad, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createPolygon(const s3d::Vec2& center, const s3d::Array<s3d::Vec2>& points, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsBody createPolygon(const s3d::Vec2& center, const s3d::Polygon& polygon, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter(), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic) const;

		PhysicsWheelJoint createWheelJoint(const PhysicsBody& bodyA, const PhysicsBody& bodyB, const s3d::Vec2& anchor, const s3d::Vec2& axis, const WheelJointState& wheelJointState = WheelJointState());
	};

	class PhysicsWorld::CPhysicsWorld
	{
	private:

		std::shared_ptr<b2World> m_world;

	public:

		CPhysicsWorld(const s3d::Vec2& gravity);

		std::weak_ptr<b2World> getWorldPtr() const;
	};

	class PhysicsBody
	{
	private:

		class CPhysicsBody;

		std::shared_ptr<CPhysicsBody> pImpl;

		friend class PhysicsWheelJoint;

	public:

		PhysicsBody();

		PhysicsBody(const PhysicsWorld& world, const s3d::Vec2& center = s3d::Vec2(0, 0), PhysicsBodyType bodyType = PhysicsBodyType::Dynamic);

		bool initialized() const;

		PhysicsBody& addLine(const s3d::Vec2& begin, const s3d::Vec2& end, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addLine(const s3d::Line& line, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addLineString(const s3d::Array<s3d::Vec2>& points, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addLineString(const s3d::LineString& lineString, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addLineStringClosed(const s3d::Array<s3d::Vec2>& points, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addLineStringClosed(const s3d::LineString& lineString, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addCircle(double r, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addCircle(double r, const s3d::Vec2& offset, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addCircle(const s3d::Circle& circle, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addRect(double size, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addRect(const s3d::Vec2& size, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addRect(const s3d::Vec2& size, const s3d::Vec2& offset, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addRect(const s3d::RectF& rect, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addTriangle(double sides, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addTriangle(double sides, double angle, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addTriangle(double sides, double angle, const s3d::Vec2& offset, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addTriangle(const s3d::Vec2& p0, const s3d::Vec2& p1, const s3d::Vec2& p2, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addTriangle(const s3d::Triangle& triangle, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addQuad(const s3d::Vec2& p0, const s3d::Vec2& p1, const s3d::Vec2& p2, const s3d::Vec2& p3, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addQuad(const s3d::Quad& quad, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addPolygon(const s3d::Array<s3d::Vec2>& points, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		PhysicsBody& addPolygon(const s3d::Polygon& polygon, const PhysicsMaterial& material = PhysicsMaterial(), const PhysicsFilter& filter = PhysicsFilter());

		void setSleepingAllowed(bool allowed);

		bool isSleepingAllowed() const;

		void setAwake(bool awake);

		bool isAwake() const;

		void setPos(double x, double y);

		void setPos(const s3d::Vec2& pos);

		void moveBy(double x, double y);

		void moveBy(const s3d::Vec2& v);

		void setAngle(double angle);

		void rotateBy(double angle);

		void setTransform(double x, double y, double angle);

		void setTransform(const s3d::Vec2& pos, double angle);

		void applyForce(const s3d::Vec2& force);

		void applyForce(const s3d::Vec2& force, const s3d::Vec2& offset);

		void applyForceAt(const s3d::Vec2& force, const s3d::Vec2& pos);

		void applyLinearImpulse(const s3d::Vec2& force);

		void applyLinearImpulse(const s3d::Vec2& force, const s3d::Vec2& offset);

		void applyLinearImpulseAt(const s3d::Vec2& force, const s3d::Vec2& offset);

		void applyTorque(double torque);

		void applyAngularImpulse(double torque);

		s3d::Vec2 getPos() const;

		double getAngle() const;

		std::pair<s3d::Vec2, double> getTransform() const;

		void setVelocity(const s3d::Vec2& v);

		s3d::Vec2 getVelocity() const;

		void setAngularVelocity(double omega);

		double getAngularVelocity() const;

		void setDamping(double damping);

		double getDamping() const;

		void setAngularDamping(double damping);

		double getAngularDamping() const;

		void setGravityScale(double scale);

		double getGravityScale() const;

		double getMass() const;

		double getInertia() const;

		void setBodyType(PhysicsBodyType bodyType);

		PhysicsBodyType getBodyType() const;

		void setFixedRotation(bool fixedRotation);

		bool isFixedRotation() const;

		void draw(const s3d::Color& color = s3d::Palette::White) const;

		PhysicsShape& shape(size_t index);

		const PhysicsShape& shape(size_t index) const;

		template <class PShape, std::enable_if_t<std::is_base_of<PhysicsShape, PShape>::value>* = nullptr>
		std::shared_ptr<PShape> shapeAs(const size_t index) const;

		size_t num_shapes() const;
	};

	class PhysicsBody::CPhysicsBody
	{
	private:

		s3d::Array<std::shared_ptr<PhysicsShape>> m_shapes;

		b2Body* m_body = nullptr;

	public:

		CPhysicsBody(const PhysicsWorld& world, const s3d::Vec2& center, PhysicsBodyType bodyType);

		~CPhysicsBody();

		void addLine(const s3d::Line& line, const PhysicsMaterial& material, const PhysicsFilter& filter);

		void addLineString(const s3d::Array<s3d::Vec2>& points, bool closed, const PhysicsMaterial& material, const PhysicsFilter& filter);

		void addCircle(const s3d::Circle& circle, const PhysicsMaterial& material, const PhysicsFilter& filter);

		void addRect(const s3d::RectF& rect, const PhysicsMaterial& material, const PhysicsFilter& filter);

		void addTriangle(const s3d::Triangle& triangle, const PhysicsMaterial& material, const PhysicsFilter& filter);

		void addQuad(const s3d::Quad& quad, const PhysicsMaterial& material, const PhysicsFilter& filter);

		void addPolygon(const s3d::Polygon& polygon, const PhysicsMaterial& material, const PhysicsFilter& filter);

		b2Body* getBody();

		const b2Body* getBody() const;

		s3d::Array<std::shared_ptr<PhysicsShape>>& getShapes();
	};

	struct Fixture
	{
		s3d::Array<b2Fixture*> fixtures;
	};

	class PhysicsShape
	{
	protected:

		Fixture m_fixtures;

	public:

		virtual ~PhysicsShape() {}

		virtual PhysicsShapeType getShapeType() const = 0;

		virtual void draw(const s3d::Color& color) const = 0;

		void setDensity(double density);

		double getDensity() const;

		void setFriction(double friction);

		double getFriction() const;

		void setRestitution(double restitution);

		double getRestitution() const;

		void setFilter(const PhysicsFilter& filter);

		PhysicsFilter getFilter() const;
	};

	class PhysicsWheelJoint
	{
	private:

		class CPhysicsWheelJoint;

		std::shared_ptr<CPhysicsWheelJoint> pImpl;

	public:

		PhysicsWheelJoint();

		PhysicsWheelJoint(const PhysicsWorld& world, const PhysicsBody& bodyA, const PhysicsBody& bodyB, const s3d::Vec2& anchor, const s3d::Vec2& axis, const WheelJointState& wheelJointState);

		void setMotorSpeed(double speed);

		double getMotorSpeed() const;

		void enableMotor(bool enable);

		void setMotor(bool enable, double speed = 0.0);
	};

	class PhysicsWheelJoint::CPhysicsWheelJoint
	{
	private:

		b2WheelJoint* m_wheelJoint = nullptr;

		b2World* m_world = nullptr;

	public:

		CPhysicsWheelJoint(const PhysicsWorld& world, const PhysicsBody& bodyA, const PhysicsBody& bodyB, const s3d::Vec2& anchor, const s3d::Vec2& axis, const WheelJointState& wheelJointState);

		~CPhysicsWheelJoint();

		b2WheelJoint* getWheelJoint();

		const b2WheelJoint* getWheelJoint() const;
	};

	namespace detail
	{
		inline constexpr s3d::Vec2 ToVec2(const b2Vec2& b2Vec2)
		{
			return{ b2Vec2.x, b2Vec2.y };
		}

		inline b2Vec2 ToB2Vec2(const s3d::Vec2& vec2)
		{
			return{ static_cast<float32>(vec2.x), static_cast<float32>(vec2.y) };
		}

		inline b2FixtureDef MakeFixtureDef(b2Shape* shape, const PhysicsMaterial& material, const PhysicsFilter& filter)
		{
			b2FixtureDef fixtureDef;
			fixtureDef.shape = shape;
			fixtureDef.density = static_cast<float32>(material.density);
			fixtureDef.friction = static_cast<float32>(material.friction);
			fixtureDef.restitution = static_cast<float32>(material.restitution);
			fixtureDef.filter.categoryBits = filter.categoryBits;
			fixtureDef.filter.maskBits = filter.maskBits;
			fixtureDef.filter.groupIndex = filter.groupIndex;
			return fixtureDef;
		}
	}

	class B2Line : public PhysicsShape
	{
	private:

		b2EdgeShape m_shape;

	public:

		B2Line(b2Body* body, const s3d::Line& line, const PhysicsMaterial& material, const PhysicsFilter& filter)
		{
			m_shape.Set(detail::ToB2Vec2(line.begin), detail::ToB2Vec2(line.end));

			const b2FixtureDef fixtureDef = detail::MakeFixtureDef(&m_shape, material, filter);

			m_fixtures.fixtures.push_back(body->CreateFixture(&fixtureDef));
		}

		PhysicsShapeType getShapeType() const override
		{
			return PhysicsShapeType::Line;
		}

		void draw(const s3d::Color& color = s3d::Palette::White) const override
		{
			getLine().draw(3.0 / s3d::Graphics2D::GetMaxScaling(), color);
		}

		s3d::Line getLine() const
		{
			const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
			const s3d::Vec2 begin(m_shape.m_vertex1.x * transform.q.c - m_shape.m_vertex1.y * transform.q.s + transform.p.x, m_shape.m_vertex1.x * transform.q.s + m_shape.m_vertex1.y * transform.q.c + transform.p.y);
			const s3d::Vec2 end(m_shape.m_vertex2.x * transform.q.c - m_shape.m_vertex2.y * transform.q.s + transform.p.x, m_shape.m_vertex2.x * transform.q.s + m_shape.m_vertex2.y * transform.q.c + transform.p.y);
			return{ begin, end };
		}
	};

	class B2LineString : public PhysicsShape
	{
	private:

		b2ChainShape m_shape;

		mutable s3d::LineString m_lineString;

		bool m_closed;

	public:

		B2LineString(b2Body* body, const s3d::Array<s3d::Vec2>& _points, bool closed, const PhysicsMaterial& material, const PhysicsFilter& filter)
		{
			s3d::Array<b2Vec2> points(_points.size());

			for (size_t i = 0; i < _points.size(); ++i)
			{
				points[i].Set(static_cast<float32>(_points[i].x), static_cast<float32>(_points[i].y));
			}

			m_closed = closed;

			m_lineString.assign(_points.begin(), _points.end());

			if (closed)
			{
				m_shape.CreateLoop(points.data(), static_cast<int32>(points.size()));
			}
			else
			{
				m_shape.CreateChain(points.data(), static_cast<int32>(points.size()));
			}

			const b2FixtureDef fixtureDef = detail::MakeFixtureDef(&m_shape, material, filter);

			m_fixtures.fixtures.push_back(body->CreateFixture(&fixtureDef));
		}

		PhysicsShapeType getShapeType() const override
		{
			return PhysicsShapeType::LineString;
		}

		void draw(const s3d::Color& color = s3d::Palette::White) const override
		{
			getLineString().draw(3.0 / s3d::Graphics2D::GetMaxScaling(), color, m_closed);
		}

		const s3d::LineString& getLineString() const
		{
			const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();

			for (int32 i = 0; i < m_shape.m_count - m_closed; ++i)
			{
				const b2Vec2& pos = m_shape.m_vertices[i];
				m_lineString.point(i).set(pos.x * transform.q.c - pos.y*transform.q.s + transform.p.x, pos.x*transform.q.s + pos.y*transform.q.c + transform.p.y);
			}

			return m_lineString;
		}
	};

	class B2Circle : public PhysicsShape
	{
	private:

		b2CircleShape m_shape;

	public:

		B2Circle(b2Body* body, const s3d::Circle& circle, const PhysicsMaterial& material, const PhysicsFilter& filter)
		{
			m_shape.m_radius = static_cast<float32>(circle.r);

			m_shape.m_p.Set(static_cast<float32>(circle.x), static_cast<float32>(circle.y));

			const b2FixtureDef fixtureDef = detail::MakeFixtureDef(&m_shape, material, filter);

			m_fixtures.fixtures.push_back(body->CreateFixture(&fixtureDef));
		}

		PhysicsShapeType getShapeType() const override
		{
			return PhysicsShapeType::Circle;
		}

		void draw(const s3d::Color& color = s3d::Palette::White) const override
		{
			getCircle().draw(color);
		}

		s3d::Circle getCircle() const
		{
			const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
			const b2Vec2& pos = m_shape.m_p;
			return s3d::Circle(pos.x * transform.q.c - pos.y*transform.q.s + transform.p.x, pos.x*transform.q.s + pos.y*transform.q.c + transform.p.y, m_shape.m_radius);
		}
	};

	class B2Rect : public PhysicsShape
	{
	private:

		b2PolygonShape m_shape;

	public:

		B2Rect(b2Body* body, const s3d::RectF& rect, const PhysicsMaterial& material, const PhysicsFilter& filter)
		{
			m_shape.SetAsBox(static_cast<float32>(rect.w * 0.5f), static_cast<float32>(rect.h * 0.5f), detail::ToB2Vec2(rect.center), 0.0f);

			const b2FixtureDef fixtureDef = detail::MakeFixtureDef(&m_shape, material, filter);

			m_fixtures.fixtures.push_back(body->CreateFixture(&fixtureDef));
		}

		PhysicsShapeType getShapeType() const override
		{
			return PhysicsShapeType::Rect;
		}

		void draw(const s3d::Color& color = s3d::Palette::White) const override
		{
			getQuad().draw(color);
		}

		s3d::Quad getQuad() const
		{
			const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
			const b2Vec2& pos0 = m_shape.m_vertices[0];
			const b2Vec2& pos1 = m_shape.m_vertices[1];
			const b2Vec2& pos2 = m_shape.m_vertices[2];
			const b2Vec2& pos3 = m_shape.m_vertices[3];
			return s3d::Quad
			(
				pos0.x * transform.q.c - pos0.y*transform.q.s + transform.p.x, pos0.x*transform.q.s + pos0.y*transform.q.c + transform.p.y,
				pos1.x * transform.q.c - pos1.y*transform.q.s + transform.p.x, pos1.x*transform.q.s + pos1.y*transform.q.c + transform.p.y,
				pos2.x * transform.q.c - pos2.y*transform.q.s + transform.p.x, pos2.x*transform.q.s + pos2.y*transform.q.c + transform.p.y,
				pos3.x * transform.q.c - pos3.y*transform.q.s + transform.p.x, pos3.x*transform.q.s + pos3.y*transform.q.c + transform.p.y
			);
		}
	};

	class B2Triangle : public PhysicsShape
	{
	private:

		b2PolygonShape m_shape;

	public:

		B2Triangle(b2Body* body, const s3d::Triangle& triangle, const PhysicsMaterial& material, const PhysicsFilter& filter)
		{
			const b2Vec2 points[3] = { detail::ToB2Vec2(triangle.p0), detail::ToB2Vec2(triangle.p1), detail::ToB2Vec2(triangle.p2) };

			m_shape.Set(points, 3);

			const b2FixtureDef fixtureDef = detail::MakeFixtureDef(&m_shape, material, filter);

			m_fixtures.fixtures.push_back(body->CreateFixture(&fixtureDef));
		}

		PhysicsShapeType getShapeType() const override
		{
			return PhysicsShapeType::Triangle;
		}

		void draw(const s3d::Color& color = s3d::Palette::White) const override
		{
			getTriangle().draw(color);
		}

		s3d::Triangle getTriangle() const
		{
			const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
			const b2Vec2& pos0 = m_shape.m_vertices[0];
			const b2Vec2& pos1 = m_shape.m_vertices[1];
			const b2Vec2& pos2 = m_shape.m_vertices[2];
			return s3d::Triangle
			(
				pos0.x * transform.q.c - pos0.y*transform.q.s + transform.p.x, pos0.x*transform.q.s + pos0.y*transform.q.c + transform.p.y,
				pos1.x * transform.q.c - pos1.y*transform.q.s + transform.p.x, pos1.x*transform.q.s + pos1.y*transform.q.c + transform.p.y,
				pos2.x * transform.q.c - pos2.y*transform.q.s + transform.p.x, pos2.x*transform.q.s + pos2.y*transform.q.c + transform.p.y
			);
		}
	};

	class B2Quad : public PhysicsShape
	{
	private:

		b2PolygonShape m_shape;

	public:

		B2Quad(b2Body* body, const s3d::Quad& quad, const PhysicsMaterial& material, const PhysicsFilter& filter)
		{
			const b2Vec2 points[4] = { detail::ToB2Vec2(quad.p[0]), detail::ToB2Vec2(quad.p[1]), detail::ToB2Vec2(quad.p[2]), detail::ToB2Vec2(quad.p[3]) };

			m_shape.Set(points, 4);

			const b2FixtureDef fixtureDef = detail::MakeFixtureDef(&m_shape, material, filter);

			m_fixtures.fixtures.push_back(body->CreateFixture(&fixtureDef));
		}

		PhysicsShapeType getShapeType() const override
		{
			return PhysicsShapeType::Quad;
		}

		void draw(const s3d::Color& color = s3d::Palette::White) const override
		{
			getQuad().draw(color);
		}

		s3d::Quad getQuad() const
		{
			const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
			const b2Vec2& pos0 = m_shape.m_vertices[0];
			const b2Vec2& pos1 = m_shape.m_vertices[1];
			const b2Vec2& pos2 = m_shape.m_vertices[2];
			const b2Vec2& pos3 = m_shape.m_vertices[3];
			return s3d::Quad
			(
				pos0.x * transform.q.c - pos0.y*transform.q.s + transform.p.x, pos0.x*transform.q.s + pos0.y*transform.q.c + transform.p.y,
				pos1.x * transform.q.c - pos1.y*transform.q.s + transform.p.x, pos1.x*transform.q.s + pos1.y*transform.q.c + transform.p.y,
				pos2.x * transform.q.c - pos2.y*transform.q.s + transform.p.x, pos2.x*transform.q.s + pos2.y*transform.q.c + transform.p.y,
				pos3.x * transform.q.c - pos3.y*transform.q.s + transform.p.x, pos3.x*transform.q.s + pos3.y*transform.q.c + transform.p.y
			);
		}
	};

	class B2Polygon : public PhysicsShape
	{
	private:

		s3d::Polygon m_basePolygon;

	public:

		B2Polygon(b2Body* body, const s3d::Polygon& polygon, const PhysicsMaterial& material, const PhysicsFilter& filter)
			: m_basePolygon(polygon)
		{
			b2PolygonShape m_shape;

			for (const auto& triangle : polygon.triangles())
			{
				const b2Vec2 points[3] = { detail::ToB2Vec2(triangle.p0), detail::ToB2Vec2(triangle.p1), detail::ToB2Vec2(triangle.p2) };

				m_shape.Set(points, 3);

				const b2FixtureDef fixtureDef = detail::MakeFixtureDef(&m_shape, material, filter);

				m_fixtures.fixtures.push_back(body->CreateFixture(&fixtureDef));
			}
		}

		PhysicsShapeType getShapeType() const override
		{
			return PhysicsShapeType::Polygon;
		}

		void draw(const s3d::Color& color = s3d::Palette::White) const override
		{
			const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();

			m_basePolygon.drawTransformed(transform.q.s, transform.q.c, s3d::Vec2(transform.p.x, transform.p.y), color);
		}

		s3d::Polygon getPolygon() const
		{
			const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();

			return m_basePolygon.cloneTransformed(transform.q.s, transform.q.c, s3d::Vec2(transform.p.x, transform.p.y));
		}
	};

	//-----------------------------------------------
	//
	//	PhysicsWorld
	//

	inline PhysicsWorld::PhysicsWorld(const s3d::Vec2& gravity)
		: pImpl(std::make_shared<CPhysicsWorld>(gravity)) {}

	inline std::weak_ptr<b2World> PhysicsWorld::getWorldPtr() const
	{
		return pImpl->getWorldPtr();
	}

	inline void PhysicsWorld::enableSleep(const bool enable)
	{
		pImpl->getWorldPtr().lock()->SetAllowSleeping(enable);
	}

	inline bool PhysicsWorld::getSleepEnabled() const
	{
		return pImpl->getWorldPtr().lock()->GetAllowSleeping();
	}

	inline void PhysicsWorld::setGravity(const s3d::Vec2& gravity)
	{
		pImpl->getWorldPtr().lock()->SetGravity(detail::ToB2Vec2(gravity));
	}

	inline s3d::Vec2 PhysicsWorld::getGravity() const
	{
		return detail::ToVec2(pImpl->getWorldPtr().lock()->GetGravity());
	}

	inline void PhysicsWorld::update(const double timeStep, const int32 velocityIterations, const int32 positionIterations) const
	{
		pImpl->getWorldPtr().lock()->Step(static_cast<float32>(timeStep), velocityIterations, positionIterations);
	}

	inline void PhysicsWorld::shiftOrigin(const s3d::Vec2& newOrigin)
	{
		pImpl->getWorldPtr().lock()->ShiftOrigin(detail::ToB2Vec2(newOrigin));
	}

	inline PhysicsBody PhysicsWorld::createEmpty(const s3d::Vec2& center, PhysicsBodyType bodyType) const
	{
		return PhysicsBody(*this, center, bodyType);
	}

	inline PhysicsBody PhysicsWorld::createLine(const s3d::Vec2& center, const s3d::Vec2& begin, const s3d::Vec2& end, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		return createLine(center, s3d::Line(begin, end), material, filter, bodyType);
	}

	inline PhysicsBody PhysicsWorld::createLine(const s3d::Vec2& center, const s3d::Line& line, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		PhysicsBody body(*this, center, bodyType);

		body.addLine(line, material, filter);

		return body;
	}

	inline PhysicsBody PhysicsWorld::createLineString(const s3d::Vec2& center, const s3d::Array<s3d::Vec2>& points, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		PhysicsBody body(*this, center, bodyType);

		body.addLineString(points, material, filter);

		return body;
	}

	inline PhysicsBody PhysicsWorld::createLineString(const s3d::Vec2& center, const s3d::LineString& lineString, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		PhysicsBody body(*this, center, bodyType);

		body.addLineString(lineString, material, filter);

		return body;
	}

	inline PhysicsBody PhysicsWorld::createLineStringClosed(const s3d::Vec2& center, const s3d::Array<s3d::Vec2>& points, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		PhysicsBody body(*this, center, bodyType);

		body.addLineStringClosed(points, material, filter);

		return body;
	}

	inline PhysicsBody PhysicsWorld::createLineStringClosed(const s3d::Vec2& center, const s3d::LineString& lineString, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		PhysicsBody body(*this, center, bodyType);

		body.addLineStringClosed(lineString, material, filter);

		return body;
	}

	inline PhysicsBody PhysicsWorld::createCircle(const s3d::Vec2& center, double r, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		return createCircle(center, s3d::Circle(r), material, filter, bodyType);
	}

	inline PhysicsBody PhysicsWorld::createCircle(const s3d::Vec2& center, double r, const s3d::Vec2& offset, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		return createCircle(center, s3d::Circle(offset, r), material, filter, bodyType);
	}

	inline PhysicsBody PhysicsWorld::createCircle(const s3d::Vec2& center, const s3d::Circle& circle, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		PhysicsBody body(*this, center, bodyType);

		body.addCircle(circle, material, filter);

		return body;
	}

	inline PhysicsBody PhysicsWorld::createRect(const s3d::Vec2& center, double size, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		return createRect(center, s3d::RectF(size).setCenter(0, 0), material, filter, bodyType);
	}

	inline PhysicsBody PhysicsWorld::createRect(const s3d::Vec2& center, const s3d::Vec2& size, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		return createRect(center, s3d::RectF(size).setCenter(0, 0), material, filter, bodyType);
	}

	inline PhysicsBody PhysicsWorld::createRect(const s3d::Vec2& center, const s3d::Vec2& size, const s3d::Vec2& offset, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		return createRect(center, s3d::RectF(size).setCenter(offset), material, filter, bodyType);
	}

	inline PhysicsBody PhysicsWorld::createRect(const s3d::Vec2& center, const s3d::RectF& rect, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		PhysicsBody body(*this, center, bodyType);

		body.addRect(rect, material, filter);

		return body;
	}

	inline PhysicsBody PhysicsWorld::createTriangle(const s3d::Vec2& center, double sides, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		return createTriangle(center, s3d::Triangle(sides), material, filter, bodyType);
	}

	inline PhysicsBody PhysicsWorld::createTriangle(const s3d::Vec2& center, double sides, double angle, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		return createTriangle(center, s3d::Triangle(sides, angle), material, filter, bodyType);
	}

	inline PhysicsBody PhysicsWorld::createTriangle(const s3d::Vec2& center, double sides, double angle, const s3d::Vec2& offset, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		return createTriangle(center, s3d::Triangle(offset, sides, angle), material, filter, bodyType);
	}

	inline PhysicsBody PhysicsWorld::createTriangle(const s3d::Vec2& center, const s3d::Vec2& p0, const s3d::Vec2& p1, const s3d::Vec2& p2, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		return createTriangle(center, s3d::Triangle(p0, p1, p2), material, filter, bodyType);
	}

	inline PhysicsBody PhysicsWorld::createTriangle(const s3d::Vec2& center, const s3d::Triangle& triangle, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		PhysicsBody body(*this, center, bodyType);

		body.addTriangle(triangle, material, filter);

		return body;
	}

	inline PhysicsBody PhysicsWorld::createQuad(const s3d::Vec2& center, const s3d::Vec2& p0, const s3d::Vec2& p1, const s3d::Vec2& p2, const s3d::Vec2& p3, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		return createQuad(center, s3d::Quad(p0, p1, p2, p3), material, filter, bodyType);
	}

	inline PhysicsBody PhysicsWorld::createQuad(const s3d::Vec2& center, const s3d::Quad& quad, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		PhysicsBody body(*this, center, bodyType);

		body.addQuad(quad, material, filter);

		return body;
	}

	inline PhysicsBody PhysicsWorld::createPolygon(const s3d::Vec2& center, const s3d::Array<s3d::Vec2>& points, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		return createPolygon(center, s3d::Polygon(points), material, filter, bodyType);
	}

	inline PhysicsBody PhysicsWorld::createPolygon(const s3d::Vec2& center, const s3d::Polygon& polygon, const PhysicsMaterial& material, const PhysicsFilter& filter, PhysicsBodyType bodyType) const
	{
		PhysicsBody body(*this, center, bodyType);

		body.addPolygon(polygon, material, filter);

		return body;
	}

	inline PhysicsWheelJoint PhysicsWorld::createWheelJoint(const PhysicsBody& bodyA, const PhysicsBody& bodyB, const s3d::Vec2& anchor, const s3d::Vec2& axis, const WheelJointState& wheelJointState)
	{
		return PhysicsWheelJoint(*this, bodyA, bodyB, anchor, axis, wheelJointState);
	}

	//-----------------------------------------------
	//
	//	CPhysicsWorld
	//

	inline PhysicsWorld::CPhysicsWorld::CPhysicsWorld(const s3d::Vec2& gravity)
		: m_world(std::make_shared<b2World>(detail::ToB2Vec2(gravity)))
	{

	}

	inline std::weak_ptr<b2World> PhysicsWorld::CPhysicsWorld::getWorldPtr() const
	{
		return m_world;
	}

	//-----------------------------------------------
	//
	//	PhysicsBody
	//

	inline PhysicsBody::PhysicsBody()
	{

	}

	inline PhysicsBody::PhysicsBody(const PhysicsWorld& world, const s3d::Vec2& center, const PhysicsBodyType bodyType)
		: pImpl(std::make_shared<CPhysicsBody>(world, center, bodyType))
	{

	}

	inline bool PhysicsBody::initialized() const
	{
		return !!pImpl;
	}

	inline PhysicsBody& PhysicsBody::addLine(const s3d::Vec2& begin, const s3d::Vec2& end, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addLine(s3d::Line(begin, end), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addLine(const s3d::Line& line, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->addLine(line, material, filter);

		return *this;
	}

	inline PhysicsBody& PhysicsBody::addLineString(const s3d::Array<s3d::Vec2>& points, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->addLineString(points, false, material, filter);

		return *this;
	}

	inline PhysicsBody& PhysicsBody::addLineString(const s3d::LineString& lineString, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addLineString(lineString.getArray(), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addLineStringClosed(const s3d::Array<s3d::Vec2>& points, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->addLineString(points, true, material, filter);

		return *this;
	}

	inline PhysicsBody& PhysicsBody::addLineStringClosed(const s3d::LineString& lineString, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addLineStringClosed(lineString.getArray(), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addCircle(const double r, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addCircle(s3d::Circle(r), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addCircle(const double r, const s3d::Vec2& offset, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addCircle(s3d::Circle(offset, r), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addCircle(const s3d::Circle& circle, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->addCircle(circle, material, filter);

		return *this;
	}

	inline PhysicsBody& PhysicsBody::addRect(const double size, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addRect(s3d::RectF(size).setCenter(0, 0), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addRect(const s3d::Vec2& size, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addRect(s3d::RectF(size).setCenter(0, 0), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addRect(const s3d::Vec2& size, const s3d::Vec2& offset, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addRect(s3d::RectF(size).setCenter(offset), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addRect(const s3d::RectF& rect, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->addRect(rect, material, filter);

		return *this;
	}

	inline PhysicsBody& PhysicsBody::addTriangle(double sides, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addTriangle(s3d::Triangle(sides), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addTriangle(double sides, double angle, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addTriangle(s3d::Triangle(sides, angle), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addTriangle(double sides, double angle, const s3d::Vec2& offset, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addTriangle(s3d::Triangle(offset, sides, angle), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addTriangle(const s3d::Vec2& p0, const s3d::Vec2& p1, const s3d::Vec2& p2, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addTriangle(s3d::Triangle(p0, p1, p2), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addTriangle(const s3d::Triangle& triangle, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->addTriangle(triangle, material, filter);

		return *this;
	}

	inline PhysicsBody& PhysicsBody::addQuad(const s3d::Vec2& p0, const s3d::Vec2& p1, const s3d::Vec2& p2, const s3d::Vec2& p3, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addQuad(s3d::Quad(p0, p1, p2, p3), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addQuad(const s3d::Quad& quad, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->addQuad(quad, material, filter);

		return *this;
	}

	inline PhysicsBody& PhysicsBody::addPolygon(const s3d::Array<s3d::Vec2>& points, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		return addPolygon(s3d::Polygon(points), material, filter);
	}

	inline PhysicsBody& PhysicsBody::addPolygon(const s3d::Polygon& polygon, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->addPolygon(polygon, material, filter);

		return *this;
	}

	inline void PhysicsBody::setSleepingAllowed(const bool allowed)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getBody()->SetSleepingAllowed(allowed);
	}

	inline bool PhysicsBody::isSleepingAllowed() const
	{
		if (!pImpl)
		{
			return true;
		}

		return pImpl->getBody()->IsSleepingAllowed();
	}

	inline void PhysicsBody::setAwake(const bool awake)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getBody()->SetAwake(awake);
	}

	inline bool PhysicsBody::isAwake() const
	{
		if (!pImpl)
		{
			return true;
		}

		return pImpl->getBody()->IsAwake();
	}

	inline void PhysicsBody::setPos(const double x, const double y)
	{
		setPos(s3d::Vec2(x, y));
	}

	inline void PhysicsBody::setPos(const s3d::Vec2& pos)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getBody()->SetTransform(detail::ToB2Vec2(pos), pImpl->getBody()->GetAngle());
	}

	inline void PhysicsBody::moveBy(const double x, const double y)
	{
		moveBy(s3d::Vec2(x, y));
	}

	inline void PhysicsBody::moveBy(const s3d::Vec2& v)
	{
		setPos(getPos() + v);
	}

	inline void PhysicsBody::setAngle(const double angle)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getBody()->SetTransform(pImpl->getBody()->GetPosition(), static_cast<float32>(angle));
	}

	inline void PhysicsBody::rotateBy(const double angle)
	{
		setAngle(getAngle() + angle);
	}

	inline void PhysicsBody::setTransform(const double x, const double y, const double angle)
	{
		return setTransform(s3d::Vec2(x, y), angle);
	}

	inline void PhysicsBody::setTransform(const s3d::Vec2& pos, const double angle)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getBody()->SetTransform(detail::ToB2Vec2(pos), static_cast<float32>(angle));
	}

	inline void PhysicsBody::applyForce(const s3d::Vec2& force)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getBody()->ApplyForceToCenter(detail::ToB2Vec2(force), true);
	}

	inline void PhysicsBody::applyForce(const s3d::Vec2& force, const s3d::Vec2& offset)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getBody()->ApplyForce(detail::ToB2Vec2(force), pImpl->getBody()->GetWorldCenter() + detail::ToB2Vec2(offset), true);
	}

	inline void PhysicsBody::applyForceAt(const s3d::Vec2& force, const s3d::Vec2& pos)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getBody()->ApplyForce(detail::ToB2Vec2(force), detail::ToB2Vec2(pos), true);
	}

	inline void PhysicsBody::applyLinearImpulse(const s3d::Vec2& force)
	{
		if (!pImpl)
		{
			return;
		}

		PhysicsBody::pImpl->getBody()->ApplyLinearImpulseToCenter(detail::ToB2Vec2(force), true);
	}

	inline void PhysicsBody::applyLinearImpulse(const s3d::Vec2& force, const s3d::Vec2& offset)
	{
		if (!pImpl)
		{
			return;
		}

		PhysicsBody::pImpl->getBody()->ApplyLinearImpulse(detail::ToB2Vec2(force), pImpl->getBody()->GetWorldCenter() + detail::ToB2Vec2(offset), true);
	}

	inline void PhysicsBody::applyLinearImpulseAt(const s3d::Vec2& force, const s3d::Vec2& pos)
	{
		if (!pImpl)
		{
			return;
		}

		PhysicsBody::pImpl->getBody()->ApplyLinearImpulse(detail::ToB2Vec2(force), detail::ToB2Vec2(pos), true);
	}

	inline void PhysicsBody::applyTorque(const double torque)
	{
		if (!pImpl)
		{
			return;
		}

		PhysicsBody::pImpl->getBody()->ApplyTorque(static_cast<float32>(torque), true);
	}

	inline void PhysicsBody::applyAngularImpulse(const double torque)
	{
		if (!pImpl)
		{
			return;
		}

		PhysicsBody::pImpl->getBody()->ApplyAngularImpulse(static_cast<float32>(torque), true);
	}

	inline s3d::Vec2 PhysicsBody::getPos() const
	{
		if (!pImpl)
		{
			return s3d::Vec2(0, 0);
		}

		return detail::ToVec2(pImpl->getBody()->GetPosition());
	}

	inline double PhysicsBody::getAngle() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getBody()->GetAngle();
	}

	inline std::pair<s3d::Vec2, double> PhysicsBody::getTransform() const
	{
		if (!pImpl)
		{
			return{ s3d::Vec2(0,0), 0.0 };
		}

		return{ detail::ToVec2(pImpl->getBody()->GetPosition()), pImpl->getBody()->GetAngle() };
	}

	inline void PhysicsBody::setVelocity(const s3d::Vec2& v)
	{
		if (!pImpl)
		{
			return;
		}

		return pImpl->getBody()->SetLinearVelocity(detail::ToB2Vec2(v));
	}

	inline s3d::Vec2 PhysicsBody::getVelocity() const
	{
		if (!pImpl)
		{
			return s3d::Vec2(0, 0);
		}

		return detail::ToVec2(pImpl->getBody()->GetLinearVelocity());
	}

	inline void PhysicsBody::setAngularVelocity(const double omega)
	{
		if (!pImpl)
		{
			return;
		}

		return pImpl->getBody()->SetAngularVelocity(static_cast<float32>(omega));
	}

	inline void PhysicsBody::setDamping(const double damping)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getBody()->SetLinearDamping(static_cast<float32>(damping));
	}

	inline double PhysicsBody::getAngularVelocity() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getBody()->GetAngularVelocity();
	}

	inline double PhysicsBody::getDamping() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getBody()->GetLinearDamping();
	}

	inline void PhysicsBody::setAngularDamping(const double damping)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getBody()->SetAngularDamping(static_cast<float32>(damping));
	}

	inline double PhysicsBody::getAngularDamping() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getBody()->GetAngularDamping();
	}

	inline void PhysicsBody::setGravityScale(const double scale)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getBody()->SetGravityScale(static_cast<float32>(scale));
	}

	inline double PhysicsBody::getGravityScale() const
	{
		if (!pImpl)
		{
			return 1.0;
		}

		return pImpl->getBody()->GetGravityScale();
	}

	inline double PhysicsBody::getMass() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getBody()->GetMass();
	}

	inline double PhysicsBody::getInertia() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getBody()->GetInertia();
	}

	inline void PhysicsBody::setBodyType(const PhysicsBodyType bodyType)
	{
		if (!pImpl)
		{
			return;
		}

		return pImpl->getBody()->SetType(static_cast<b2BodyType>(bodyType));
	}

	inline PhysicsBodyType PhysicsBody::getBodyType() const
	{
		if (!pImpl)
		{
			return PhysicsBodyType::Static;
		}

		return static_cast<PhysicsBodyType>(pImpl->getBody()->GetType());
	}

	inline void PhysicsBody::setFixedRotation(const bool fixedRotation)
	{
		if (!pImpl)
		{
			return;
		}

		return pImpl->getBody()->SetFixedRotation(fixedRotation);
	}

	inline bool PhysicsBody::isFixedRotation() const
	{
		if (!pImpl)
		{
			return false;
		}

		return pImpl->getBody()->IsFixedRotation();
	}

	inline void PhysicsBody::draw(const s3d::Color& color) const
	{
		if (!pImpl)
		{
			return;
		}

		for (const auto& shape : pImpl->getShapes())
		{
			shape->draw(color);
		}
	}

	inline PhysicsShape& PhysicsBody::shape(const size_t index)
	{
		if (!pImpl)
		{
			throw std::out_of_range("PhysicsBody::shape() PhysicsBody is empty.");
		}

		return *pImpl->getShapes()[index];
	}

	inline const PhysicsShape& PhysicsBody::shape(const size_t index) const
	{
		if (!pImpl)
		{
			throw std::out_of_range("PhysicsBody::shape() PhysicsBody is empty.");
		}

		return *pImpl->getShapes()[index];
	}

	template <class PShape, std::enable_if_t<std::is_base_of<PhysicsShape, PShape>::value>*>
	inline std::shared_ptr<PShape> PhysicsBody::shapeAs(const size_t index) const
	{
		if (!pImpl)
		{
			throw std::out_of_range("PhysicsBody::shapeAs() PhysicsBody is empty.");
		}

		return std::dynamic_pointer_cast<PShape>(pImpl->getShapes()[index]);
	}

	inline size_t PhysicsBody::num_shapes() const
	{
		if (!pImpl)
		{
			return 0;
		}

		return pImpl->getShapes().size();
	}

	//-----------------------------------------------
	//
	//	CPhysicsBody
	//

	inline PhysicsBody::CPhysicsBody::CPhysicsBody(const PhysicsWorld& world, const s3d::Vec2& center, const PhysicsBodyType bodyType)
	{
		b2BodyDef bodyDef;
		bodyDef.type = static_cast<b2BodyType>(bodyType);
		bodyDef.position = detail::ToB2Vec2(center);

		m_body = world.getWorldPtr().lock()->CreateBody(&bodyDef);
	}

	inline PhysicsBody::CPhysicsBody::~CPhysicsBody()
	{
		m_body->GetWorld()->DestroyBody(m_body);
	}

	inline void PhysicsBody::CPhysicsBody::addLine(const s3d::Line& line, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		m_shapes.push_back(std::make_shared<B2Line>(m_body, line, material, filter));
	}

	inline void PhysicsBody::CPhysicsBody::addLineString(const s3d::Array<s3d::Vec2>& points, bool closed, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		m_shapes.push_back(std::make_shared<B2LineString>(m_body, points, closed, material, filter));
	}

	inline void PhysicsBody::CPhysicsBody::addCircle(const s3d::Circle& circle, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		m_shapes.push_back(std::make_shared<B2Circle>(m_body, circle, material, filter));
	}

	inline void PhysicsBody::CPhysicsBody::addRect(const s3d::RectF& rect, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		m_shapes.push_back(std::make_shared<B2Rect>(m_body, rect, material, filter));
	}

	inline void PhysicsBody::CPhysicsBody::addTriangle(const s3d::Triangle& triangle, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		m_shapes.push_back(std::make_shared<B2Triangle>(m_body, triangle, material, filter));
	}

	inline void PhysicsBody::CPhysicsBody::addQuad(const s3d::Quad& quad, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		m_shapes.push_back(std::make_shared<B2Quad>(m_body, quad, material, filter));
	}

	inline void PhysicsBody::CPhysicsBody::addPolygon(const s3d::Polygon& polygon, const PhysicsMaterial& material, const PhysicsFilter& filter)
	{
		m_shapes.push_back(std::make_shared<B2Polygon>(m_body, polygon, material, filter));
	}

	inline b2Body* PhysicsBody::CPhysicsBody::getBody()
	{
		return m_body;
	}

	inline const b2Body* PhysicsBody::CPhysicsBody::getBody() const
	{
		return m_body;
	}

	inline s3d::Array<std::shared_ptr<PhysicsShape>>& PhysicsBody::CPhysicsBody::getShapes()
	{
		return m_shapes;
	}

	//-----------------------------------------------
	//
	//	PhysicsShape
	//

	inline void PhysicsShape::setDensity(const double density)
	{
		for (auto& fixture : m_fixtures.fixtures)
		{
			fixture->SetDensity(static_cast<float32>(density));
		}
	}

	inline double PhysicsShape::getDensity() const
	{
		return m_fixtures.fixtures[0]->GetDensity();
	}

	inline void PhysicsShape::setFriction(const double friction)
	{
		for (auto& fixture : m_fixtures.fixtures)
		{
			fixture->SetFriction(static_cast<float32>(friction));
		}
	}

	inline double PhysicsShape::getFriction() const
	{
		return m_fixtures.fixtures[0]->GetFriction();
	}

	inline void PhysicsShape::setRestitution(const double restitution)
	{
		for (auto& fixture : m_fixtures.fixtures)
		{
			fixture->SetRestitution(static_cast<float32>(restitution));
		}
	}

	inline double PhysicsShape::getRestitution() const
	{
		return m_fixtures.fixtures[0]->GetRestitution();
	}

	inline void PhysicsShape::setFilter(const PhysicsFilter& filter)
	{
		b2Filter filterData;
		filterData.categoryBits = filter.categoryBits;
		filterData.maskBits = filter.maskBits;
		filterData.groupIndex = filter.groupIndex;

		for (auto& fixture : m_fixtures.fixtures)
		{
			fixture->SetFilterData(filterData);
		}
	}

	inline PhysicsFilter PhysicsShape::getFilter() const
	{
		const auto& filterData = m_fixtures.fixtures[0]->GetFilterData();
		PhysicsFilter filter;
		filter.categoryBits = filterData.categoryBits;
		filter.maskBits = filterData.maskBits;
		filter.groupIndex = filterData.groupIndex;
		return filter;
	}

	//-----------------------------------------------
	//
	//	PhysicsWheelJoint
	//

	inline PhysicsWheelJoint::PhysicsWheelJoint()
	{

	}

	inline PhysicsWheelJoint::PhysicsWheelJoint(const PhysicsWorld& world, const PhysicsBody& bodyA, const PhysicsBody& bodyB, const s3d::Vec2& anchor, const s3d::Vec2& axis, const WheelJointState& wheelJointState)
		: pImpl(std::make_shared<CPhysicsWheelJoint>(world, bodyA, bodyB, anchor, axis, wheelJointState))
	{

	}

	inline void PhysicsWheelJoint::setMotorSpeed(const double speed)
	{
		if (!pImpl)
		{
			return;
		}

		if (auto wheelJoint = pImpl->getWheelJoint())
		{
			wheelJoint->SetMotorSpeed(static_cast<float32>(speed));
		}
	}

	inline double PhysicsWheelJoint::getMotorSpeed() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		if (auto wheelJoint = pImpl->getWheelJoint())
		{
			return wheelJoint->GetMotorSpeed();
		}
		else
		{
			return 0.0;
		}
	}

	inline void PhysicsWheelJoint::enableMotor(const bool enable)
	{
		if (!pImpl)
		{
			return;
		}

		if (auto wheelJoint = pImpl->getWheelJoint())
		{
			wheelJoint->EnableMotor(enable);
		}
	}

	inline void PhysicsWheelJoint::setMotor(const bool enable, const double speed)
	{
		if (!pImpl)
		{
			return;
		}

		if (auto wheelJoint = pImpl->getWheelJoint())
		{
			wheelJoint->EnableMotor(enable);

			wheelJoint->SetMotorSpeed(static_cast<float32>(speed));
		}
	}

	//-----------------------------------------------
	//
	//	CPhysicsWheelJoint
	//

	inline PhysicsWheelJoint::CPhysicsWheelJoint::CPhysicsWheelJoint(const PhysicsWorld& world, const PhysicsBody& bodyA, const PhysicsBody& bodyB, const s3d::Vec2& anchor, const s3d::Vec2& axis, const WheelJointState& wheelJointState)
	{
		if (!bodyA.initialized() || !bodyB.initialized())
		{
			return;
		}

		b2WheelJointDef wheelJointDef;
		wheelJointDef.Initialize(bodyA.pImpl->getBody(), bodyB.pImpl->getBody(), detail::ToB2Vec2(anchor), detail::ToB2Vec2(axis));
		wheelJointDef.enableMotor = wheelJointState.enableMotor;
		wheelJointDef.maxMotorTorque = static_cast<float32>(wheelJointState.maxMotorTorque);
		wheelJointDef.frequencyHz = static_cast<float32>(wheelJointState.frequencyHz);
		wheelJointDef.dampingRatio = static_cast<float32>(wheelJointState.dampingRatio);
		m_wheelJoint = static_cast<b2WheelJoint*>(world.getWorldPtr().lock()->CreateJoint(&wheelJointDef));

		m_world = world.getWorldPtr().lock().get();
	}

	inline PhysicsWheelJoint::CPhysicsWheelJoint::~CPhysicsWheelJoint()
	{
		if (!m_world || !m_wheelJoint)
		{
			return;
		}

		m_world->DestroyJoint(m_wheelJoint);
	}

	inline b2WheelJoint* PhysicsWheelJoint::CPhysicsWheelJoint::getWheelJoint()
	{
		return m_wheelJoint;
	}

	inline const b2WheelJoint* PhysicsWheelJoint::CPhysicsWheelJoint::getWheelJoint() const
	{
		return m_wheelJoint;
	}
}
