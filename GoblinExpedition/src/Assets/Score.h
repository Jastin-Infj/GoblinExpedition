#pragma once

#include "GameObject.h"

#define SCORE_INIT 0		//�����X�R�A�l
#define SCORE_MIN  0		//�X�R�A�Œ�l
#define SCORE_MAX  99999	//�X�R�A����l


/// <summary>
/// �X�R�A�N���X
/// </summary>
class Score : public GameObject
{
public:
	typedef std::shared_ptr<Score> SP;		//�V�F�A�|�C���^
	typedef std::weak_ptr<Score>   WP;		//�E�B�[�N�|�C���^

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Score();


	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Score();


	/// <summary>
	/// �X�R�A���������ݒ肵�܂�
	/// </summary>
	/// <param name="taskname_">
	/// �I�u�W�F�N�g��(�O���[�v���E�^�X�N��)
	/// </param>
	/// <param name="position_">
	/// �������W�l(X���W , Y���W)
	/// </param>
	/// <param name="scale_">
	/// �傫��(X , Y)
	/// </param>
	/// <param name="digit_">
	/// �����̌���
	/// </param>
	/// <param name="order_">
	/// �`��D�揇��
	/// </param>
	/// <returns>
	/// �������ݒ�I�� true
	/// </returns>
	bool Score_Parameter(
		const TASKNAME&   taskname_,
		const Vec2&       position_,
		const Point&      scale_,
		const int&        digit_,
		const float&      order_
		);


	/// <summary>
	/// �X�R�A�𐶐����܂�
	/// </summary>
	/// <param name="taskname_">
	/// �I�u�W�F�N�g��(�O���[�v���E�^�X�N��)
	/// </param>
	/// <param name="position_">
	/// �������W�l(X���W , Y���W)
	/// </param>
	/// <param name="scale_">
	/// �傫��(X , Y)
	/// </param>
	/// <param name="digit_">
	/// ���蓖�Ă錅��
	/// </param>
	/// <param name="order_">
	/// �`��D�揇��
	/// </param>
	/// <param name="flag">
	/// �^�X�N�V�X�e���ɓo�^�����邩 true / false
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	TaskObject::SP Create(
		const TASKNAME&   taskname_, 
		const Vec2&       position_, 
		const Point&      scale_, 
		const int&        digit_,
		const float&      order_ = 1.0f, 
		bool              flag = true
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
	/// ��� true 
	/// </returns>
	bool Finalize()override;


	/// <summary>
	/// �X�R�A�v�Z�����܂�
	/// </summary>
	void Score_UpDate();


	/// <summary>
	/// ���݂̃X�R�A��Ԃ��܂�
	/// </summary>
	/// <returns>
	/// ���݂̃X�R�A
	/// </returns>
	int getScore()const;


	/// <summary>
	/// �w��̌����̐�����Ԃ��܂�
	/// </summary>
	/// <param name="digit_">
	/// ���ׂ錅��
	/// </param>
	/// <returns>
	/// �Ή����������̐���
	/// </returns>
	std::string Digit();


	/// <summary>
	/// �e�����̉摜����`��ݒ肵�܂�
	/// </summary>
	/// <param name="value">
	/// �w�肳�ꂽ�����̐��l
	/// </param>
	void setvalueSrc(const std::string& value);
private:
	int score;			//�X�R�A
	int selectdigit;	//�Ή������錅��
};