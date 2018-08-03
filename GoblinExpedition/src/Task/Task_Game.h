#pragma once
#include "../TaskSystem/TaskObject.h"

#define ENEMY_CREATE_TIME 130		//�G�������܂łɂ����鎞��
#define ENEMY_CREATE_SIZE 5			//���̐����łǂꂭ�炢�̓G�𐶐����邩
#define ENEMY_RANDOM_Y    352		//�����_���͈̔�

#define ENEMY_DESTROYINGCOUNT_INIT  0		//�G�̌��j���@�������l
#define ENEMY_DESTROYINGCOUNT_MIN   0		//�G�̌��j���@�ŏ��l
#define ENEYMY_DESTROYINGCOUNT_MAX  999		//�G�̌��j���@�ő�l

#define SCORE_INIT        0			//�X�R�A�̏������l
#define SCORE_MIN         0			//�X�R�A�̍ŏ��l
#define SCORE_MAX         99999     //�X�R�A�ő�l

#define MUSOUITEM_CREATECOUNT  1	//���o�A�C�e���𐶐�����^�C�~���O

class Game : public TaskObject
{
public:
	typedef std::shared_ptr<Game> SP;


	///<summary>
	///�R���X�g���N�^
	///</summary>
	Game();


	///<summary>
	///�f�X�g���N�^
	///</summary>
	virtual ~Game();

	
	///<summary>
	///<para>����������<para>
	///����:�O���[�v���E�^�X�N��
	///<summary>
	///<param name="taskname">�O���[�v���E�^�X�N��</param>
	bool Init(const std::pair<std::string, std::string>& taskname);


	///<summary>
	///�X�V����
	///</summary>
	void Update()override;


	///<summary>
	///�`�揈�� �g�p���Ȃ�
	///</summary>
	void Render()override {};


	///<summary>
	///<para>�������</para>
	///<para>��� ����/���s true:false</para>
	///</summary>
	bool Finalize()override;


	///<summary>
	///<para>�I�u�W�F�N�g�𐶐����܂�</para>
	///<para>����: �O���[�v���E�^�X�N�� , (�^�X�N�V�X�e���ɓo�^���邩)
	///<returns>�I�u�W�F�N�g�̃X�}�[�g�|�C���^��Ԃ��܂�</returns>
	///</summary>
	static TaskObject::SP Create(const std::pair<std::string, std::string>& taskname, bool flag = true);


	/// <summary>
	/// �G�������_���������܂�
	/// </summary>
	void Enemy_Create();


	/// <summary>
	/// ���o�A�C�e���𐶐����ėǂ����𔻒肵�܂�
	/// </summary>
	/// <returns>
	/// �����o���� true / �����o���Ȃ� false
	/// </returns>
	bool isMusouItemCreate()const;

//�O���Ŏg�p���郁�\�b�h

	/// <summary>
	/// �X�R�A�����Z�����܂�
	/// </summary>
	/// <param name="addtion">
	/// �X�R�A�ɉ��Z����l
	/// </param>
	void ScoreAddition(const int& addition);


	/// <summary>
	/// ���݂̃X�R�A��Ԃ��܂�
	/// </summary>
	/// <returns>
	/// ���݂̃X�R�A
	/// </returns>
	int  getScore()const;


	/// <summary>
	/// �G�̌��j���J�E���g�𑝉������܂�
	/// </summary>
	/// <param name="destroyingcount">
	/// �G�̌��j���|�C���g
	/// </param>
	void Enemy_DestroyingCount_Add(const int& destroyingcount);


	/// <summary>
	/// ���o�A�C�e���𐶐����܂�
	/// </summary>
	void MusouItem_Create();


private:
	float enemycreatetime;				//�G����������܂ł̎���
	int   score;						//�X�R�A
	int   enemy_destroyingcount;		//�G�̌��j��
};