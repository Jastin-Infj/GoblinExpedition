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
# include <unordered_map>
# include "Handle.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "Mesh.hpp"
# include "TransformedMesh.hpp"
# include "TextureAsset.hpp"

namespace s3d
{
	/// <summary>
	/// マテリアル
	/// </summary>
	struct Material
	{
		ColorF ambient;

		ColorF diffuse;

		ColorF specular;

		ColorF transmittance;

		ColorF emission;

		float shininess;

		float ior;
		
		float dissolve;

		int32 illum;

		String name;

		String ambientTextureName;

		String diffuseTextureName;

		String specularTextureName;

		String normalTextureName;
	};

	/// <summary>
	/// モデルノード
	/// </summary>
	struct ModelNode
	{
		ModelNode() = default;

		ModelNode(const String& _name, const Mesh& _mesh, const Material& _material)
			: name(_name)
			, mesh(_mesh)
			, material(_material) {}

		String name;

		Mesh mesh;

		Material material;
	};

	enum class ModelDesc
	{
		UnmanageTextures,

		ManageTextures,

		Default = ManageTextures,
	};

	/// <summary>
	/// モデル
	/// </summary>
	class Model
	{
	protected:

		class Handle{};

		using ModelHandle = Siv3DHandle<Handle>;

		std::shared_ptr<ModelHandle> m_handle;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Model();

		/// <summary>
		/// 3D モデルファイルからモデルをロードします。
		/// </summary>
		/// <param name="path">
		/// 3D モデルファイルのパス
		/// </param>
		/// <remarks>
		/// Wavefront OBJ 形式のみサポートしています。
		/// </remarks>
		explicit Model(const FilePath& path, ModelDesc desc = ModelDesc::Default);

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~Model();

		/// <summary>
		/// モデルをリリースします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void release();

		explicit operator bool() const { return !isEmpty(); }

		HandleIDType id() const;

		bool isEmpty() const;

		bool operator == (const Model& model) const;

		bool operator != (const Model& model) const;

		/// <summary>
		/// モデルノードの一覧を取得します。
		/// </summary>
		/// <returns>
		/// モデルノードの一覧
		/// </returns>
		const Array<ModelNode>& nodes() const;

		const Model& draw(const ColorF& color = Palette::White) const
		{
			for (const auto& node : nodes())
			{
				if (node.material.diffuseTextureName.isEmpty)
				{
					node.mesh.draw(color);
				}
				else
				{
					node.mesh.draw(TextureAsset(node.material.diffuseTextureName), color);
				}
			}

			return *this;
		}

		const Model& draw(const Mat4x4& matrix, const ColorF& color = Palette::White) const
		{
			for (const auto& node : nodes())
			{
				if (node.material.diffuseTextureName.isEmpty)
				{
					node.mesh.draw(matrix, color);
				}
				else
				{
					node.mesh.draw(matrix, TextureAsset(node.material.diffuseTextureName), color);
				}
			}

			return *this;
		}

		const Model& drawForward(const ColorF& color = Palette::White) const
		{
			for (const auto& node : nodes())
			{
				if (node.material.diffuseTextureName.isEmpty)
				{
					node.mesh.drawForward(color);
				}
				else
				{
					node.mesh.drawForward(TextureAsset(node.material.diffuseTextureName), color);
				}
			}

			return *this;
		}

		const Model& drawForward(const Mat4x4& matrix, const ColorF& color = Palette::White) const
		{
			for (const auto& node : nodes())
			{
				if (node.material.diffuseTextureName.isEmpty)
				{
					node.mesh.drawForward(matrix, color);
				}
				else
				{
					node.mesh.drawForward(matrix, TextureAsset(node.material.diffuseTextureName), color);
				}
			}

			return *this;
		}

		const Model& drawShadow() const
		{
			for (const auto& node : nodes())
			{
				node.mesh.drawShadow();
			}

			return *this;
		}

		const Model& drawShadow(const Mat4x4& matrix) const
		{
			for (const auto& node : nodes())
			{
				TransformedMesh(matrix, node.mesh).drawShadow();
			}

			return *this;
		}
	};
}
