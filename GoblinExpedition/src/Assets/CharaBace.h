#pragma once
#include <Siv3D.hpp>

//�ǉ��������@�\�͂����ɋL�q����
#include "../TaskSystem/TaskObject.h"
#include "../InterFace/DrawInterFace.hpp"
#include "../InterFace/ObjectType.h"

///<summary>
///�I�u�W�F�N�g�N���X
///</summary>
class CharaBace : public TaskObject
{
public:
	typedef std::shared_ptr<CharaBace> SP;


	///<summary>
	///�R���X�g���N�^
	///</summary>
	CharaBace();


	///<summary>
	///�f�X�g���N�^
	///</summary>
	virtual ~CharaBace();


	///<summary>
	///<para>����������</para>
	///<para>�O���[�v���E�^�X�N�� , �ΏۃI�u�W�F�N�g , �������W�ʒu , �`��T�C�Y , �`��D�揇�� </para>
	///<returns>�������@����/���s true : false</returns>
	///</summary>
	bool Init(std::pair<std::string, std::string>& taskname, Type type, Point& pos, Point& scale,float order);


	///<summary>
	///<para>�I�u�W�F�N�g�̐��������܂�</para>
	///<para>�O���[�v���E�^�X�N�� , �`�悷��Ώ�,�������W�ʒu ,�`�悷��T�C�Y ,(�^�X�N�V�X�e���ɓo�^���邩 true : false) </para>
	///</summary>
	static CharaBace::SP Create(std::pair<std::string, std::string>& taskname, Type type, Point pos, Point scale, float order, bool flag = true);


private:
	DrawInterFace* draw;		//�`��@�\
	Type           type;		//�����Ă���Ώ�
	Point          position;	//���݈ʒu
	Point          scale;		//�傫��

	///<summary>
	///�X�V����
	///</summary>
	void UpDate()override;


	///<summary>
	///�`�揈��
	///</summary>
	void Render()override;


	///<summary>
	///�������
	///</summary>
	bool Finalize()override;


	///<summary>
	///�e�N�X�`����ResourceManager����擾���đΏۂ̃I�u�W�F�N�g�^�C�v�ɂ���ăe�N�X�`����Ԃ��܂�
	///</summary>
	///<returns>�e�N�X�`���̃A�h���X�l</returns>
	Texture getResoruceManagerTexture()const;

//=================================================================================================
};