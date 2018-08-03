#pragma once

#include <Siv3D.hpp>

//�ǉ��@�\
#include "../TaskSystem/TaskSystem.h"			//TaskSystem���g�p�o����悤�ɂ���
#include "../TaskSystem/TaskObject.h"			//TaskSystem�ɓo�^�ł���N���X���g�p�o����悤�ɂ��܂�

#include "../InterFace/Collider.hpp"			//�����蔻��
#include "../InterFace/DrawInterFace.hpp"		//�`��@�\
#include "../InterFace/MoveInterFace.hpp"		//�ړ��@�\

using TASKNAME = std::pair<std::string, std::string>;

/// <summary>
/// �I�u�W�F�N�g�𐶐�����N���X
/// </summary>
class GameObject : public TaskObject
{
public:
	typedef std::shared_ptr<GameObject> SP;		//�V�F�A�|�C���^
	typedef std::weak_ptr<GameObject> WP;		//�E�B�[�N�|�C���^


	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameObject();


	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameObject();


	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update()override {};


	/// <summary>
	/// �`������܂�
	/// </summary>
	virtual void Render()override {};


	/// <summary>
	/// �������
	/// </summary>
	/// <returns>
	/// ������� true / ����o���Ȃ� false
	/// </returns>
	virtual bool Finalize() { return true; }


	/// <summary>
	/// �����l�̃x�N�g�������W�ړ����s���܂�
	/// </summary>
	/// <param name="offset">
	/// �ړ���������W�l
	/// </param>
	void OffsetPosition(const Vec2& offset);

protected:
	Vec2  position;					//���݂̍��W
	Point scale;					//�I�u�W�F�N�g�̑傫��
	float          order;			//�`��D�揇��
	Collider*      collider;		//�����蔻��
	DrawInterFace* draw;			//�`��@�\
	MoveInterFace* move;			//�ړ��@�\
};


