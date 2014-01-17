#ifndef __bind_SSXML__
#define __bind_SSXML__

#include "package_SpriteStudio.h"
#include "bind_AnimePack.h"


//ssLoader�ɂ���N���X�̃��b�p�[�N���X��Python�ւ̎Q�Ɠn�����s���֌W���烉�b�s���O����
//�f�[�^�̃X�N���v�g���ւ̎󂯓n���̂��ߊe�|�C���^��Bind_SsProject�ɂ���m_project�̃|�C���^�Q�ƂɂȂ�B
//SSXML��������ꂽ�^�C�~���O�ł����̎Q�Ƃ�������d�g�݂Ƃ���B
//�{���I�ɂ͏����Ȃ�����python�ł̗��p��K�؂ł͂��邪�A����^�C�~���O�̂킩��₷�����d�����Ă��̂悤�ɂ���B




class Bind_SsProject {
public:
	std::vector<Bind_SsAnimePack>	m_animepacklist;

	SsProject *m_project;
    Bind_SsProject();
	bool debug();

	void createAnimepack();

	///<�v���W�F�N�g�Ɋi�[���ꂽ�A�j���[�V�����̃t�@�C�������擾����
	int	getAnimePackNum(){ 
		if ( m_project )
			return m_project->getAnimePackNum();
		return 0;
	}

	///<�v���W�F�N�g�Ɋi�[���ꂽ�Z���}�b�v�̃t�@�C�������擾����
	int	getCellMapNum(){ 
		if ( m_project )
			return m_project->getCellMapNum();
		return 0;
	}
	
	Bind_SsAnimePack const& AnimePackAt( int at )
	{
		return m_animepacklist[at];
	}

};


class SSXML
{
private:
	Bind_SsProject*	m_bind_project;
public:
	SSXML();
	bool	Load( const char* name );

	Bind_SsProject	const& GetPrj()
	{
		return 	*m_bind_project;
	}

};



#endif
