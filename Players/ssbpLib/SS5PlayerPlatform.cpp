// 
//  SS5Platform.cpp
//
#include "SS5PlayerPlatform.h"

/**
* �e�v���b�g�t�H�[���ɍ��킹�ď������쐬���Ă�������
* DX���C�u�����p�ɍ쐬����Ă��܂��B
*/
#include "DxLib.h"

namespace ss
{
	/**
	* �t�@�C���ǂݍ���
	*/
	unsigned char* SSFileOpen(const char* pszFileName, const char* pszMode, unsigned long * pSize)
	{
		unsigned char * pBuffer = NULL;
		SS_ASSERT2(pszFileName != NULL && pSize != NULL && pszMode != NULL, "Invalid parameters.");
		*pSize = 0;
		do
		{
		    // read the file from hardware
			FILE *fp = fopen(pszFileName, pszMode);
		    SS_BREAK_IF(!fp);
		    
		    fseek(fp,0,SEEK_END);
		    *pSize = ftell(fp);
		    fseek(fp,0,SEEK_SET);
		    pBuffer = new unsigned char[*pSize];
		    *pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
		    fclose(fp);
		} while (0);
		if (! pBuffer)
		{

			std::string msg = "Get data from file(";
		    msg.append(pszFileName).append(") failed!");
		    
		    SSLOG("%s", msg.c_str());

		}
		return pBuffer;
	}

	/**
	* �e�N�X�`���̓ǂݍ���
	*/
	long SSTextureLoad(const char* pszFileName )
	{
		/**
		* �e�N�X�`���Ǘ��p�̃��j�[�N�Ȓl��Ԃ��Ă��������B
		* �e�N�X�`���̊Ǘ��̓Q�[�����ōs���`�ɂȂ�܂��B
		* �e�N�X�`���ɃA�N�Z�X����n���h����A�e�N�X�`�������蓖�Ă��o�b�t�@�ԍ����ɂȂ�܂��B
		*
		* �v���C���[�͂����ŕԂ����l�ƃp�[�c�̃X�e�[�^�X�������ɕ`����s���܂��B
		*/
		long rc = 0;

		rc = (long)LoadGraph(pszFileName);

		return rc;
	}
	
	/**
	* �e�N�X�`���̉��
	*/
	bool SSTextureRelese(long handle)
	{
		/// �����������ԍ��ŉ��x������������Ă΂��̂ŁA��O���o�Ȃ��悤�ɍ쐬���Ă��������B
		bool rc = true;

		if ( DeleteGraph((int)handle) == -1 )
		{
			rc = false;
		}

		return rc ;
	}

	/**
	* �e�N�X�`���̃T�C�Y���擾
	* �e�N�X�`����UV��ݒ肷��̂Ɏg�p���܂��B
	*/
	bool SSGetTextureSize(long handle, int &w, int &h)
	{
		if (GetGraphSize(handle, &w, &h) == -1)
		{
			return false;
		}
		return true;
	}

	/**
	* �X�v���C�g�̕\��
	*/
	void SSDrawSprite(State state)
	{
		//���Ή��@�\
		//�X�e�[�^�X��������擾���A�e�v���b�g�t�H�[���ɍ��킹�ċ@�\���������Ă��������B
		//X��]�AY��]�A�㉺���]�A�J���[�u�����h�i�ꕔ�̂݁j
		//���_�ό`�AX�T�C�Y�AY�T�C�Y


		float cx = (state.rect.size.width * state.anchorX);		/// ���_�I�t�Z�b�g
		float cy = (state.rect.size.height * state.anchorY);	/// ���_�I�t�Z�b�g
		float x = state.mat[12];								/// �\�����W�̓}�g���N�X����擾���܂��B
		float y = state.mat[13];								/// �\�����W�̓}�g���N�X����擾���܂��B
		float rotationZ = RadianToDegree(state.rotationZ);		/// ��]�l
		float scaleX = state.scaleX;							/// �g�嗦
		float scaleY = state.scaleY;							/// �g�嗦

		//�`��t�@���N�V����
		//
		switch (state.blendfunc)
		{
			case BLEND_MIX:		///< 0 �u�����h�i�~�b�N�X�j
				if (state.opacity == 255)
				{
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, state.opacity);
				}
				else
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, state.opacity);
				}
				break;
			case BLEND_MUL:		///< 1 ��Z
				SetDrawBlendMode(DX_BLENDMODE_MULA, state.opacity);
				break;
			case BLEND_ADD:		///< 2 ���Z
				SetDrawBlendMode(DX_BLENDMODE_ADD, state.opacity);
				break;
			case BLEND_SUB:		///< 3 ���Z
				SetDrawBlendMode(DX_BLENDMODE_SUB, state.opacity);
				break;

		}

		if (state.flags & PART_FLAG_COLOR_BLEND)
		{
			//RGB�̃J���[�u�����h��ݒ�
			//�����ɍČ�����ɂ͐�p�̃V�F�[�_�[���g���A�e�N�X�`���ɃJ���[�l����������K�v������
			//�쐬����ꍇ��ssShader_frag.h�ACustomSprite�̃R�����g�ƂȂ��Ă�V�F�[�_�[�������Q�l�ɂ��Ă��������B
			if (state.colorBlendType == VERTEX_FLAG_ONE)
			{
				//�P�F�J���[�u�����h
			}
			else
			{
				//���_�J���[�u�����h
				//���Ή�
			}
			switch (state.colorBlendFunc)
			{
			case BLEND_MIX:
				break;
			case BLEND_MUL:		///< 1 ��Z
				// �u�����h���@�͏�Z�ȊO���Ή�
				// �Ƃ肠��������̐F�𔽉f������
				SetDrawBright(state.quad.tl.colors.r, state.quad.tl.colors.g, state.quad.tl.colors.b);
				break;
			case BLEND_ADD:		///< 2 ���Z
				break;
			case BLEND_SUB:		///< 3 ���Z
				break;
			}

		}

		/**
		* DX���C�u������X��Y�����g��Ȃ̂ŁA�Ƃ肠����X�X�P�[�����g�p����
		* DX���C�u������Y���]�ł��Ȃ��̂Ŗ��Ή�
		* Y���]�AY�g����s���ꍇ�͂S���_���w�肵�A�㉺�̒��_�����ւ��ĕ`�悷��B
		*/
		DrawRectRotaGraph2(
			(int)x, (int)y,
			(int)state.rect.origin.x, (int)state.rect.origin.y, (int)state.rect.size.width, (int)state.rect.size.height,
			(int)cx, (int)cy,
			scaleX, rotationZ,
			state.texture, TRUE, state.flipX
			);

		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);	//�u�����h�X�e�[�g��ʏ�֖߂�
	}

	/**
	* ���[�U�[�f�[�^�̎擾
	*/
	void SSonUserData(Player *player, UserData *userData)
	{
		//�Q�[�����փ��[�U�[�f�[�^��ݒ肷��֐����Ăяo���Ă��������B
	}

	/**
	* ���[�U�[�f�[�^�̎擾
	*/
	void SSPlayEnd(Player *player)
	{
		//�Q�[�����փA�j���Đ��I����ݒ肷��֐����Ăяo���Ă��������B
	}


	/**
	* �����R�[�h�ϊ�
	*/ 
	std::string utf8Togbk(const char *src)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
		unsigned short * wszGBK = new unsigned short[len + 1];
		memset(wszGBK, 0, len * 2 + 2);
		MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)src, -1, (LPWSTR)wszGBK, len);

		len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
		char *szGBK = new char[len + 1];
		memset(szGBK, 0, len + 1);
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
		std::string strTemp(szGBK);
		if (strTemp.find('?') != std::string::npos)
		{
			strTemp.assign(src);
		}
		delete[]szGBK;
		delete[]wszGBK;
		return strTemp;
	}

	/**
	* windows�p�p�X�`�F�b�N
	*/ 
	bool isAbsolutePath(const std::string& strPath)
	{
		std::string strPathAscii = utf8Togbk(strPath.c_str());
		if (strPathAscii.length() > 2
			&& ((strPathAscii[0] >= 'a' && strPathAscii[0] <= 'z') || (strPathAscii[0] >= 'A' && strPathAscii[0] <= 'Z'))
			&& strPathAscii[1] == ':')
		{
			return true;
		}
		return false;
	}

};
