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
	/// ���`�̕`��t�H�[�}�b�g�N���X
	/// </summary>
	enum class InitFormat
	{
		Normal,			//�摜�T�C�Y�݂̂̕`�������
		AddCollider,	//�����蔻����̐ݒ�
	};


	/// <summary>
	/// �I�u�W�F�N�g�^�C�v
	/// </summary>
	enum class ObjectType
	{
		Background,		//�w�i�֌W
		PlayerLife,		//Player�̃��C�t
		ScoreUI   ,		//�X�R�AUI
		MusouItem ,		//���o�A�C�e��
		ResultRogo,		//���U���g���S
		TitleRogo ,		//�^�C�g�����S
		ESCAPERogo,		//�G�X�P�[�v
		HowPlayUI ,		//�V�ѕ�UI
		toTitle   ,		//�^�C�g���֖߂�
		toGame    ,		//�Q�[���X�^�[�g
		TitleStart,		//�^�C�g���̃X�^�[�g
		TitleExit ,		//�^�C�g���ł̏I��
		Leftclickfont,	//���N���b�N�t�H���g
		Attackfont,		//�U���t�H���g
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
	/// <param name="initformat">
	/// �������ݒ���@
	/// </param>
	/// <param name="src">
	/// �摜����`
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
		const InitFormat& initformat,
		const Rect&       src,
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
	/// <param name="initformat">
	/// �������ݒ���@
	/// </param>
	/// <param name="src">
	/// �摜����`
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
		const InitFormat& initformat,
		const Rect&       src,
		const float&      order = 1.0f, 
		const bool        flag = true
		);

private:

	/// <summary>
	/// ���o�A�C�e�����g�p���܂�
	/// </summary>
	void MusouItem_Use();


	/// <summary>
	/// �Q�[�����I�������܂�
	/// </summary>
	void Escape_Use();


	/// <summary>
	/// �G��S�ł����܂�
	/// </summary>
	void EnemiesKill();


	/// <summary>
	/// �}�E�X�ō��N���b�N�������ꂽ��̏������s���܂�
	/// </summary>
	void TitleStartUI_LeftClicked();

	
	/// <summary>
	/// �}�E�X�ō��N���b�N�������ꂽ��̏������s���܂�
	/// </summary>
	void ToGameUI_LeftClicked();


	/// <summary>
	/// �}�E�X�ō��N���b�N�������ꂽ��̏������s���܂�
	/// </summary>
	void TitleExitUI_LeftClicked();
	

	/// <summary>
	/// �}�E�X�ō��N���b�N�������ꂽ��̏������s���܂�
	/// </summary>
	/// <param name="src_"></param>
	/// <returns></returns>
	void TotitleUI_LeftClicked();


	/// <summary>
	/// �����ݒ�Őݒ肷�鐗�`�@�摜�T�C�Y���̕`�������
	/// </summary>
	/// <param name="src_">
	/// �摜����`
	/// </param>
	void Normal(const Rect& src_);


	/// <summary>
	/// �����ݒ�Őݒ肷�鐗�`�@�����蔻��̐ݒ�Ɖ摜�T�C�Y���̓����蔻���`������܂�
	/// </summary>
	/// <param name="src_">
	/// �摜����`
	/// </param>
	void AddCollider(const Rect& src_);

//�O���N���X�Ŏg�p���郁�\�b�h
	
public:
	/// <summary>
	/// �E�B���h�E���ɂ��邩�𔻒肵�܂�
	/// </summary>
	/// <param name="position">
	/// ���W( x , y )
	/// </param>
	/// <returns>
	/// �E�B���h�E�� true / �E�B���h�E�O false
	/// </returns>
	bool isInWindow(const Vec2& position);


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


	/// <summary>
	/// ���g�����I�u�W�F�N�g�^�C�v��Ԃ��܂�
	/// </summary>
	/// <returns>
	/// �I�u�W�F�N�g�^�C�v
	/// </returns>
	ObjectType getObjecttype()const;


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