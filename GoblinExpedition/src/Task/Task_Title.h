#pragma once
#include "../TaskSystem/TaskObject.h"
#include "../InterFace/ShapeMouseCursor.hpp"
class Title : public TaskObject
{
public:
	typedef std::shared_ptr<Title> SP;		//�V�F�A�|�C���^
	typedef std::weak_ptr<Title>   WP;		//�E�B�[�N�|�C���^


	///<summary>
	///�R���X�g���N�^
	///</summary>
	Title();


	///<summary>
	///�f�X�g���N�^
	///</summary>
	virtual ~Title();

	
	///<summary>
	///<para>����������</para>
	///����:�O���[�v���E�^�X�N��
	///</summary>
	///<param name = "taskname">�O���[�v���E�^�X�N��</param>
	bool Init(const std::pair<std::string, std::string>& taskname);


	///<summary>
	///�X�V����
	///</summary>
	void Update()override;


	///<summary>
	///�`�揈�� �g�p���Ȃ�
	///</summary>
	void Render()override;


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

private:

	/// <summary>
	/// �}�E�X�ƑΏۂ̐}�`�Ƃ̓����蔻����s���܂�
	/// </summary>
	void MouseHitleftClicked_update();
private:
	ShapeMouseCursor* shapemouse;		//�}�E�X�J�[�\���}�`
};