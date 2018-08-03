#pragma once
#include "../TaskSystem/TaskObject.h"
class Title : public TaskObject
{
public:
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
};