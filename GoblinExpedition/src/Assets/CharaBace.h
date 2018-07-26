#pragma once
#include <Siv3D.hpp>

//�ǉ��������@�\�͂����ɋL�q����
#include "../TaskSystem/TaskObject.h"
#include "../InterFace/DrawInterFace.hpp"
#include "../InterFace/MoveInterFace.hpp"
#include "../InterFace/Collider.hpp"


///<summary>
///�I�u�W�F�N�g�^�C�v��ݒ肷��t�@�C���ł�
///</summary>
enum class ObjectType
{
	Back,		//�w�i
	UI,			//UI
	Player,		//�v���C��
	Mouse,		//�}�E�X
	Enemy,		//�G
	Item,		//�A�C�e��
};


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
	/// <param name="hitbace">
	/// �����蔻���`
	/// </param>
	/// <param name="draw">
	/// �`��@�\
	/// </param>
	/// <param name="move">
	/// �ړ��@�\
	/// </param>
	/// <returns>
	/// �������o���� / true (false�Ȃ�)
	/// </returns>
	bool ParameterInit
	(
		const std::pair<std::string, std::string>& taskname, 
		ObjectType                                 objecttype, 
		const Point&							   pos, 
		const Point&							   scale,
		float									   order,
		bool									   hitbace,
		bool									   draw,
		bool									   move
	);


	/// <summary>
	/// �I�u�W�F�N�g�𐶐����܂�
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
	/// <param name="hitbace">
	/// �����蔻��@�\�@�ǉ� / �ǉ��Ȃ�(false)
	/// </param>
	/// <param name="drawinterface">
	/// �`��@�\�@�ǉ� / �ǉ��Ȃ�(false)
	/// </param>
	/// <param name="moveinterface">
	/// �ړ��@�\�@�ǉ� / �ǉ��Ȃ�(false)
	/// </param>
	/// <param name="flag">
	/// �V�X�e���ɓo�^���� (true)/���Ȃ�(false)
	/// </param>
	/// <returns>
	/// ���������I�u�W�F�N�g�̃X�}�[�g�|�C���^
	/// </returns>
	static CharaBace::SP Create
	(
		const std::pair<std::string, std::string>& taskname, 
		ObjectType								   objecttype, 
		const Point&							   pos, 
		const Point&							   scale,
		float									   order, 
		bool								       hitbace = false,
		bool                                       drawinterface = false,
		bool									   moveinterface = false,
		bool									   flag = true
	);


	/// <summary>
	/// ���W�̐ݒ�E�ύX�����܂�
	/// </summary>
	/// <param name="pos">
	/// �ݒ肷����W
	/// </param>
	void setPosition(const Point& pos);


	/// <summary>
	/// ���݂̍��W��Ԃ��܂�
	/// </summary>
	/// <returns>
	/// ���݂̍��W
	/// </returns>
	Point getPosition()const;


	/// <summary>
	/// �I�u�W�F�N�g�^�C�v��Ԃ��܂�
	/// </summary>
	/// <returns>
	/// �I�u�W�F�N�g�^�C�v
	/// </returns>
	ObjectType getObjectType()const;

//=================================================================================================

	struct EnemyFunction
	{
		/// <summary>
		/// Player�������`�ƐڐG������s���܂�
		/// </summary>
		/// <param name="me">
		/// �����蔻�肷�鎩�g
		/// </param>
		/// <param name="target">
		/// �����蔻������鑊��
		/// </param>
		/// <returns>
		/// �ڐG true / �ڐG�Ȃ� false
		/// </returns>
		bool onHitbaceExit(const CharaBace::SP& me , const CharaBace::SP& target)const;


		/// <summary>
		/// ���E���]�t���O��Ԃ��܂�
		/// </summary>
		/// <returns>
		/// ���E���]�t���O��Ԃ�
		/// </returns>
		bool getleftrightinversionflag()const;


		/// <summary>
		/// ���E���]�t���O�����ւ��܂�
		/// </summary>
		void changeleftrightinversionflag();


		/// <summary>
		/// ���E���]�t���O��ݒ肵�܂�
		/// </summary>
		/// <param name="flag">
		/// true ���] / false ���]�Ȃ�
		/// </param>
		void setleftrightinversionflag(bool flag);
	private:
		//���E���]�t���O
		bool leftrightinversionflag;
	};


	struct PlayerFunction
	{
	public:
		///<summary>
		///���C�t�l��Ԃ��܂�
		///<summary>
		///<returns>
		///
		///
	private:
		int life;
	};
//==================================================================================================
private:
	ObjectType     objecttype;		//�����Ă���Ώ�
	Point          position;		//���݈ʒu
	Point          scale;			//�傫��
	Collider*      collider;		//�����蔻��@�\
	DrawInterFace* draw;			//�`��@�\
	MoveInterFace* move;			//�ړ��@�\

	EnemyFunction* enemyfunction;	//�G�̋@�\

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


	///<summary>
	///�e�N�X�`����ResourceManager����擾���đΏۂ̃I�u�W�F�N�g�^�C�v�ɂ���ăe�N�X�`����Ԃ��܂�
	///</summary>
	void setResoruceManagerTexture()const;


	/// <summary>
	/// �I�u�W�F�N�g�^�C�v�ɂ���ĕ`����@��ω������܂�
	/// </summary>
	void ObjecytypeDraw();


	/// <summary>
	/// �I�u�W�F�N�g�^�C�v�ɂ���ē����蔻���`��ݒ肵�܂�
	/// </summary>
	void setObjectTypeCollider();


	/// <summary>
	/// �I�u�W�F�N�g�^�C�v�ɂ���Ĉړ��ʂ�ݒ肵�܂�
	/// </summary>
	void setObjectTypeMoveSpeed();


	/// <summary>
	/// �I�u�W�F�N�g�^�C�v�ɂ���Ĉړ����@��ݒ肵�܂�
	/// </summary>
	void ObjectTypeMove();
};