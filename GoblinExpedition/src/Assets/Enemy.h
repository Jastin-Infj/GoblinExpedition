#pragma once
#include "GameObject.h"


#include "Player.h"

#define SCORE				100		//�|����Ă��Ƃ��̃X�R�A

#define MOVE_SPEED_X        3		//X�ړ���
#define MOVE_SPEED_Y        0       //Y�ړ���

#define OPAQUE_INIT         255		//�s�����x�@�����l
#define OPAQUE_MIN          0		//�s�����x�@�ŏ��l
#define OPAQUE_MAX			255		//�s�����x  �ő�l
#define OPAQUE_DECREASERATE 0.88	//1�t���[��������̕s�����x������

#define OBJECT_TYPESIZE     2       //�G�̃I�u�W�F�N�g�^�C�v��

class Enemy : public GameObject
{
public:
	typedef std::shared_ptr<Enemy> SP;		//�X�}�[�g�|�C���^
	typedef std::weak_ptr<Enemy>   WP;		//�E�B�[�N�|�C���^

	enum class ObjectType
	{
		Goburin = 0,		//�S�u����
	};


	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Enemy();


	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Enemy();


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
		const ObjectType& objecttype,
		const Vec2&       position,
		const Point&      scale,
		const float&      order
	);


	/// <summary>
	/// �X�V����
	/// </summary>
	void UpDate()override;


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
	/// Player�������`�ƐڐG������s���܂�
	/// </summary>
	/// <param name="target">
	/// �����蔻��������`
	/// </param>
	/// <returns>
	/// �ڐG true / �ڐG�Ȃ� false
	/// </returns>
	bool onHitbaceExit(const RectF& target)const;


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
	/// �S�u�����̋@�\�g���ݒ���s���܂�
	/// </summary>
	void Goburin_Parameter();


	/// <summary>
	/// ���]���邩���Ȃ����𔻒肵�܂�
	/// </summary>
	void LeftRightInversion();


	/// <summary>
	/// �}�b�v�O��������܂�
	/// </summary>
	bool OutsideMap();


	/// <summary>
	/// �s���������������܂�
	/// </summary>
	void Opaque_Decrement();


	/// <summary>
	/// �s�����x��0�ɂȂ��Ă��邩�𔻒�����܂�
	/// </summary>
	/// <returns>
	/// 0 true / 0�ȊO false
	/// </returns>
	bool isOpaque_Zero()const;


	/// <summary>
	/// �}�E�X�ƓG�̓����蔻��
	/// </summary>
	void Mouse_Hit();


/*�O���N���X�Ŏg�p���\�b�h*/
	
	/// <summary>
	/// �����蔻���`��Ԃ��܂�
	/// </summary>
	/// <returns>
	/// �����蔻���`
	/// </returns>
	RectF getHitBace()const;


	/// <summary>
	/// �X�R�A��Ԃ��܂�
	/// </summary>
	/// <returns>
	/// �X�R�A
	/// </returns>
    const int getScore();
private:
	ObjectType	objecttype;					//�I�u�W�F�N�g�^�C�v
	bool leftrightinversionflag;			//���E���]�t���O
	bool mouse_hitflag;						//�ڐG����
	uint32      opaque;						//�s�����x
};