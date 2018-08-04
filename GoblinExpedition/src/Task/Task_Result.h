#pragma once
#include "../TaskSystem/TaskObject.h"

class Result : public TaskObject
{
public:
	typedef std::shared_ptr<Result> SP;		//�X�}�[�g�|�C���^
	typedef std::weak_ptr<Result>   WP;		//�E�B�[�N�|�C���^


	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Result();


	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Result();


	/// <summary>
	/// ���U���g������
	/// </summary>
	/// <param name="taskname_">
	/// �^�X�N��(�O���[�v���E�^�X�N��)
	/// </param>
	/// <param name="score_">
	/// �X�R�A
	/// </param>
	/// <param name="destroyingcount_">
	/// �G�̌��j��
	/// </param>
	/// <returns>
	/// �������I�� true 
	/// </returns>
	bool Init(const std::pair<std::string, std::string>& taskname_ , const int& score_ , const int& destroyingcount_);


	/// <summary>
	/// �X�V����
	/// </summary>
	void Update()override;


	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render()override {};


	/// <summary>
	/// �������
	/// </summary>
	/// <returns>
	/// ������� true 
	/// </returns>
	bool Finalize()override;


	/// <summary>
	/// ���U���g��ʂ𐶐����܂�
	/// </summary>
	/// <param name="taskname">
	/// �^�X�N��(�O���[�v���E�^�X�N��)
	/// </param>
	/// <param name="score_">
	/// �X�R�A
	/// </param>
	/// <param name="destroyingcount_">
	/// �G�̌��j��
	/// </param>
	/// <param name="flag">
	/// �^�X�N�V�X�e���ɓo�^�����邩 ���� true /  ���Ȃ� false
	/// </param>
	/// <returns>
	/// �����o���� true / �����o���Ȃ� false
	/// </returns>
	static TaskObject::SP Create(const std::pair<std::string, std::string>& taskname,const int& score_ , const int& destroyingcount_, bool flag = true);


	/// <summary>
	/// �Q�[���f�[�^�𑗂�܂�
	/// </summary>
	/// <param name="score_">
	/// �X�R�A
	/// </param>
	/// <param name="destroyingcount_">
	/// �G�̌��j��
	/// </param>
	void set_gameData(const int& score_ , const int& destroyingcount_);
private:
	int score;					//�X�R�A
	int destroyingcount;		//���j��
};