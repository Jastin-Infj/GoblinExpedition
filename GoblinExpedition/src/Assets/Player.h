#pragma once
#include "GameObject.h"

#define PLAYER_LIFE_INIT      2             //���C�t�l�@�������l
#define PLAYER_LIFE_MIN       1				//���C�t�l�@�Œ�l
#define PLAYER_LIFE_MAX       10			//���C�t�l�@����l
#define PLAYER_LIFE_DECREMENT 1				//���C�t�l�@�����l


#define MOUSE_SCALE_W         2				//�}�E�X���� �c
#define MOUSE_SCALE_H         2				//�}�E�X���� ��

class Player : public GameObject
{
public:
	typedef std::shared_ptr<Player> SP;		//�X�}�[�g�|�C���^
	typedef std::weak_ptr<Player>   WP;		//�E�B�[�N�|�C���^


	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();


	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player();


	/// <summary>
	/// �p�����[�^�̏����������܂�
	/// </summary>
	/// <param name="taskname">
	/// �I�u�W�F�N�g�^�X�N��(�O���[�v���E�^�X�N��)
	/// </param>
	/// <param name="position">
	/// �������W(X���W , Y���W)
	/// </param>
	/// <param name="scale">
	/// �傫��(X���W , Y���W)
	/// </param>
	/// <param name="life">
	/// ���C�t�l
	/// </param>
	/// <param name="order">
	/// �`��D�揇��(0.0f �` 1.0f)
	/// </param>
	/// <returns>
	/// �������ݒ�I�� true (false�Ȃ�)
	/// </returns>
	bool Init_Parameter(
		const TASKNAME& taskname, 
		const Vec2&     position, 
		const Point&    scale , 
		const int&      life,
		const float&    order
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
	/// �̗͂�Ԃ��܂�
	/// </summary>
	/// <returns>
	/// �̗�
	/// </returns>
	int getLife()const;


	/// <summary>
	/// �̗͂̐��ɂ���ă��C�tUI�̐��𐶐����܂�
	/// </summary>
	void LifeUICreate();


	/// <summary>
	/// �̗͒l��ύX�E�ݒ肵�܂�
	/// </summary>
	/// <param name="life">
	/// �̗͒l
	/// </param>
	void setLife(int life);


	/// <summary>
	/// ���C�t�l������ȏォ�𔻒肵�܂�
	/// </summary>
	/// <returns></returns>
	constexpr bool isLifeMax()const;


	/// <summary>
	/// �̗͂̍ŏ��l��Ԃ��܂�
	/// </summary>
	/// <returns>
	/// �ŏ����C�t�l
	/// </returns>
	const int  LifeMin();


	/// <summary>
	/// �̗͂̏���l��Ԃ��܂�
	/// </summary>
	/// <returns>
	/// ������C�t�l
	/// </returns>
	const int  LifeMax();


	/// <summary>
	/// �I�u�W�F�N�g�𐶐����܂�
	/// </summary>
	/// <param name="taskname">
	/// �I�u�W�F�N�g�^�X�N��(�O���[�v���E�^�X�N��)�̐ݒ肵�܂�
	/// </param>
	/// <param name="position">
	/// �������W��ݒ�E�ύX���܂�(X���W , Y���W)
	/// </param>
	/// <param name="scale">
	/// �傫����ݒ�E�ύX���܂�(X���W , Y���W)
	/// </param>
	/// <param name="life">
	/// ���C�t�l(1 - 10)
	/// </param>
	/// <param name="order">
	/// <para>�`��D�揇��(0.0f �` 1.0f)</para>
	/// <para>���傫���قǃ��C���[���O�ɍs���܂�</para>
	/// </param>
	/// <param name="flag">
	/// �^�X�N�V�X�e���ɓo�^ (���� true / ���Ȃ� false)
	/// </param>
	/// <returns>
	/// ���������I�u�W�F�N�g�̃V�F�A�|�C���^
	/// </returns>
	static TaskObject::SP Create(
		const TASKNAME& taskname, 
		const Vec2&     position, 
		const Point&    scale, 
		const int&		life,
		const float&    order= 1.0f, 
		bool            flag = true
		);


	/// <summary>
	/// �}�E�X�̓����蔻��𖈃t���[�����m���܂�
	/// </summary>
	void Mousehitupdate();


	/// <summary>
	/// �G�Ɠ����荶�N���b�N�������ꂽ���ǂ����𔻒肵�܂�
	/// </summary>
	/// <param name="target">
	/// �^�[�Q�b�g�̓G
	/// </param>
	/// <returns>
	/// ���N���b�N�������ꂽ true / false
	/// </returns>
	bool MouseHit_toEnemy(const Rect& target)const;


/*�O���N���X�Ń��\�b�h�g�p*/


	/// <summary>
	/// ���C�t�l�����̋L���܂���0���𔻒肵�܂�
	/// </summary>
	constexpr bool isLifeZero()const;


	/// <summary>
	/// ���C�t�����������܂�
	/// </summary>
	void LifeDecrement();


	/// <summary>
	/// Enemy�ɐڐG�������Ƃ̏���
	/// </summary>
	void Receive_Enemy();

private:
	int            life;					//�̗�
};