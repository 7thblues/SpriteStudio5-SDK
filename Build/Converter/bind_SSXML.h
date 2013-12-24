#ifndef __bind_SSXML__
#define __bind_SSXML__

#define BOOST_PYTHON_STATIC_LIB
#include    <stdio.h>
#include    <Python.h>
#include    <boost/python.hpp>

#include	<fstream>
#include	<iostream>
#include	<sstream>

using namespace boost::python;
using namespace std;

#include "bind_Animation.h"
#include "ssloader.h"



class Bind_SsAnimePack
{
public:
	SsAnimePack*	m_animepack;

	Bind_SsAnimePack(){}
	bool debug(){ return true; }
};


class Bind_SsProject {
public:
	std::vector<Bind_SsAnimePack>	m_animepacklist;

	SsProject *m_project;
    Bind_SsProject(){ puts("construct Animation"); }
	bool debug();

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
