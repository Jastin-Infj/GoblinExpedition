#pragma once
#include "../TaskSystem/TaskObject.h"
#include "../InterFace/ShapeMouseCursor.hpp"

class HowPlay : public TaskObject
{
public:
	typedef std::shared_ptr<HowPlay> SP;		//�X�}�[�g�|�C���^
	typedef std::weak_ptr<HowPlay>   WP;		//�E�B�[�N�|�C���^


											/// <summary>
											/// �R���X�g���N�^
											/// </summary>
	HowPlay();


	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~HowPlay();


	/// <summary>
	/// ���U���g������
	/// </summary>
	/// <param name="taskname_">
	/// �^�X�N��(�O���[�v���E�^�X�N��)
	/// </param>
	/// <returns>
	/// �������I�� true 
	/// </returns>
	bool Init(const std::pair<std::string, std::string>& taskname_);


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
	/// ������� true 
	/// </returns>
	bool Finalize()override;


	/// <summary>
	/// ���U���g��ʂ𐶐����܂�
	/// </summary>
	/// <param name="taskname">
	/// �^�X�N��(�O���[�v���E�^�X�N��)
	/// </param>
	/// <param name="flag">
	/// �^�X�N�V�X�e���ɓo�^�����邩 ���� true /  ���Ȃ� false
	/// </param>
	/// <returns>
	/// �����o���� true / �����o���Ȃ� false
	/// </returns>
	static TaskObject::SP Create(const std::pair<std::string, std::string>& taskname, bool flag = true);


	/// <summary>
	/// �}�E�X�ƑΏۂ̐}�`�Ƃ̓����蔻����s���܂�
	/// </summary>
	void MouseHitleftClicked_update();
private:
	ShapeMouseCursor* shapemouse;		//�}�`����}�E�X�J�[�\��
};