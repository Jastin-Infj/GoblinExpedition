#pragma once
#include <Siv3D.hpp>

//�ǉ��������@�\�͂����ɋL�q����
#include "../TaskSystem/TaskObject.h"
#include "../InterFace/DrawInterFace.hpp"
#include "../InterFace/ObjectType.h"

///<summary>
///�I�u�W�F�N�g�N���X
///</summary>
class CharaBace : public TaskObject
{
public:
	typedef std::shared_ptr<CharaBace> SP;


	///<summary>
	///�R���X�g���N�^
	///</summary>
	CharaBace();


	///<summary>
	///�f�X�g���N�^
	///</summary>
	virtual ~CharaBace();


	/// <summary>
	/// �p�����[�^�̏������ݒ�
	/// </summary>
	/// <param name="taskname">
	/// �O���[�v���E�^�X�N��
	/// </param>
	/// <param name="objecttype">
	/// �����I�u�W�F�N�g�^�C�v
	/// </param>
	/// <param name="pos">
	/// �������W
	/// </param>
	/// <param name="scale">
	/// �`��̑傫��
	/// </param>
	/// <param name="order">
	/// �`��̗D�揇��
	/// </param>
	/// <returns>
	/// �������o���� / true (false�Ȃ�)
	/// </returns>
	bool ParameterInit(const std::pair<std::string, std::string>& taskname, ObjectType objecttype, Point& pos, Point& scale,float order);


	/// <summary>
	/// �I�u�W�F�N�g�𐶐����܂�
	/// </summary>
	/// <param name="taskname">
	/// �O���[�v���E�^�X�N��
	/// </param>
	/// <param name="objectType">
	/// �����I�u�W�F�N�g�^�C�v
	/// </param>
	/// <param name="pos">
	/// �������W
	/// </param>
	/// <param name="scale">
	/// �`��̑傫��
	/// </param>
	/// <param name="order">
	/// �`��̗D�揇��
	/// </param>
	/// <param name="flag">
	/// �V�X�e���ɓo�^���� (true)/���Ȃ�(false)
	/// </param>
	/// <returns>
	/// ���������I�u�W�F�N�g�̃X�}�[�g�|�C���^
	/// </returns>
	static CharaBace::SP Create(const std::pair<std::string, std::string>& taskname, ObjectType objectType, Point pos, Point scale, float order, bool flag = true);


private:
	DrawInterFace* draw;		//�`��@�\
	ObjectType     objecttype;	//�����Ă���Ώ�
	Point          position;	//���݈ʒu
	Point          scale;		//�傫��

	///<summary>
	///�I�u�W�F�N�g�̍X�V����
	///</summary>
	void UpDate()override;


	///<summary>
	///�`�揈��
	///</summary>
	void Render()override;


	///<summary>
	///�������
	///</summary>
	bool Finalize()override;


	///<summary>
	///�e�N�X�`����ResourceManager����擾���đΏۂ̃I�u�W�F�N�g�^�C�v�ɂ���ăe�N�X�`����Ԃ��܂�
	///</summary>
	///<returns>�e�N�X�`���̃A�h���X�l</returns>
	Texture getResoruceManagerTexture()const;


	/// <summary>
	/// �^�[�Q�b�g�������̃^�C�v���𔻒肵�܂�
	/// </summary>
	/// <param name="objecttype">
	/// �I�u�W�F�N�g�̃^�C�v
	/// </param>
	/// <param name="checkObjectType">
	/// ���肷��I�u�W�F�N�g�̃^�C�v
	/// </param>
	/// <returns>
	/// �^�C�v�̈�v���Ă���/���Ă��Ȃ� true : false
	/// </returns>
	constexpr bool ObjectTypeCheck(const ObjectType& objecttype , const ObjectType& checkObjectType )const;


//=================================================================================================
};