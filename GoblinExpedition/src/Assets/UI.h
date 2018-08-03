#pragma once
#include "GameObject.h"

//�ǉ��@�\
#include "../InterFace/DrawInterFace.hpp"


class UI : public GameObject
{
public:
	typedef std::shared_ptr<UI> SP;		//�X�}�[�g�|�C���^
	typedef std::weak_ptr<UI>	WP;		//�E�B�[�N�|�C���^


	/// <summary>
	/// �I�u�W�F�N�g�^�C�v
	/// </summary>
	enum class ObjectType
	{
		Background = 0,	//�w�i�֌W
		PlayerLife = 1,	//Player�̃��C�t
		ScoreUI    = 2, //�X�R�AUI
		MusouItem  = 3, //���o�A�C�e��
		ResultRogo = 4,	//���U���g���S
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UI();


	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~UI();


	/// <summary>
	/// �p�����[�^�̏����������܂�
	/// </summary>
	/// <param name="taskname">
	/// �I�u�W�F�N�g�^�X�N��(�O���[�v���E�^�X�N��)
	/// </param>
	/// <param name="objecttype">
	/// �I�u�W�F�N�g�^�C�v
	/// </param>
	/// <param name="position">
	/// �������W(X���W , Y���W)
	/// </param>
	/// <param name="scale">
	/// �傫��(X���W , Y���W)
	/// </param>
	/// <param name="order">
	/// �`��D�揇��(0.0f �` 1.0f)
	/// </param>
	/// <returns>
	/// �������ݒ�I�� true (false�Ȃ�)
	/// </returns>
	bool Init_Parameter(
		const TASKNAME&   taskname,
		const ObjectType& objecttype  , 
		const Vec2&       position, 
		const Point&      scale, 
		const float&      order
		);


	/// <summary>
	/// �X�V����
	/// </summary>
	void Update()override;


	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render()override;


	/// <summary>
	/// �������
	/// </summary>
	/// <returns>
	/// ��� true (false�Ȃ�)
	/// </returns>
	bool Finalize()override;

	
	/// <summary>
	/// �I�u�W�F�N�g�𐶐����܂�
	/// </summary>
	/// <param name="taskname">
	/// �I�u�W�F�N�g�^�X�N��(�O���[�v���E�^�X�N��)
	/// </param>
	/// <param name="objecttype">
	/// �I�u�W�F�N�g�^�C�v
	/// </param>
	/// <param name="position">
	/// �������W(x���W , y���W)
	/// </param>
	/// <param name="scale">
	/// �傫��(�� , �c)
	/// </param>
	/// <param name="order">
	/// �`��D�揇��(0.0f ~ 1.0f)
	/// </param>
	/// <param name="flag">
	/// �^�X�N�V�X�e���ɓo�^�@����  true / ���Ȃ� false
	/// </param>
	/// <returns>
	/// ���������X�}�[�g�|�C���^
	/// </returns>
	static TaskObject::SP Create(
		const TASKNAME&   taskname, 
		const ObjectType& objecttype, 
		const Vec2&       position, 
		const Point&      scale, 
		const float&      order = 1.0f, 
		const bool        flag = true
		);


	/// <summary>
	/// �w�i�̐ݒ���s���܂�
	/// </summary>
	void BackGround_Parameter();


	/// <summary>
	/// Player�̃��C�tUI�̐ݒ���s���܂�
	/// </summary>
	void Player_Life_Parameter();


	/// <summary>
	/// �X�R�AUI�̐ݒ���s���܂�
	/// </summary>
	void ScoreUI_Parameter();


	/// <summary>
	/// ���o�A�C�e���̐ݒ���s���܂�
	/// </summary>
	void MusouItem_Parameter();


	/// <summary>
	/// ���o�A�C�e�����g�p���܂�
	/// </summary>
	void MusouItem_Use();


	/// <summary>
	/// �G��S�ł����܂�
	/// </summary>
	void EnemiesKill();


	/// <summary>
	/// ���U���g���S�̐ݒ���s���܂�
	/// </summary>
	void ResultRogo_Parameter();

//�O���N���X�Ŏg�p���郁�\�b�h
	

	/// <summary>
	/// �E�B���h�E���ɂ��邩�𔻒肵�܂�
	/// </summary>
	/// <param name="position">
	/// ���W( x , y )
	/// </param>
	/// <param name="scale">
	/// �傫��(�c , ��)
	/// </param>
	/// <returns>
	/// �E�B���h�E�� true / �E�B���h�E�O false
	/// </returns>
	bool isInWindow(const Vec2& position, const Point& scale);


	/// <summary>
	/// �E�B���h�E���ɂ��邩�𔻒肵�܂�
	/// </summary>
	/// <param name="drawbase">
	/// �`���`
	/// </param>
	/// <returns>
	/// �E�B���h�E�� true / �E�B���h�E�O false
	/// </returns>
	bool isInWindow(const RectF& drawbase);


	/// <summary>
	/// UI�Ƃ̓����蔻����s���܂�
	/// </summary>
	/// <param name="drawbase">
	/// ���肷���`
	/// </param>
	/// <returns>
	/// �ڐG true / �ڐG���Ă��Ȃ� false
	/// </returns>
	bool Hit(const RectF& drawbase);


	/// <summary>
	/// �}�E�X�̔��肵����̏���
	/// </summary>
	void Receive_Player();


	/// <summary>
	/// �}�E�X�����N���b�N���ꂽ���𔻒肵�܂�
	/// </summary>
	/// <returns>
	/// �����ꂽ : true ������Ă��Ȃ� false 
	/// </returns>
	bool MouseLclicked();


private:
	ObjectType objecttype;		//�I�u�W�F�N�g�^�C�v
	bool       killcheck;		//����ł��邩�H
};


///// <summary>
///// ���o�A�C�e���̓����蔻���`��Ԃ��܂�
///// </summary>
///// <returns>
///// ���o�A�C�e�������蔻���`
///// </returns>
//RectF getDrawBase_MusuoItem()const;