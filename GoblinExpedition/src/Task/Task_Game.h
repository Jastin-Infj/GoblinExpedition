#pragma once
#include "../TaskSystem/TaskObject.h"

#define ENEMY_CREATE_TIME 30		//�G�������܂łɂ����鎞��
#define ENEMY_CREATE_SIZE 5			//���̐����łǂꂭ�炢�̓G�𐶐����邩
#define ENEMY_RANDOM_Y    352		//�����_���͈̔�

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
	void UpDate()override;


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
private:
	float enemycreatetime;		//�G����������܂ł̎���
};