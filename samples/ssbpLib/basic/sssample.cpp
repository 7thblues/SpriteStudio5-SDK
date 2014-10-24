#include "DxLib.h"
#include "SSPlayer\SS5Player.h"

static int previousTime;
static int waitTime;
int mGameExec;

#define WAIT_FRAME (16)

void init(void);
void update(float dt);
void relese(void);

/// SS5�v���C���[
ss::Player *ssplayer;
ss::ResourceManager *resman;

/**
* ���C���֐�
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//DX���C�u�����̏�����
	ChangeWindowMode(true);	//�E�C���h�E���[�h
	SetGraphMode(1280, 720, GetColorBitDepth() );
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);

	//���C�����[�v
	mGameExec = 1;
	previousTime = GetNowCount();
	
	/// �v���C���[������
	init( );
	
	while(mGameExec == 1){
		ClearDrawScreen();
		update((float)waitTime / 1000.0f );
		ScreenFlip();
		waitTime = GetNowCount() - previousTime;
		previousTime = GetNowCount();

		if (waitTime < WAIT_FRAME){
			WaitTimer((WAIT_FRAME - waitTime));
		}else{
			if(ProcessMessage() == -1) mGameExec = 0;
		}
	}

	/// �v���C���[�I������
	relese( );


	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

void init( void )
{
	/**********************************************************************************

	SS�A�j���\���̃T���v���R�[�h
	Visual Studio Express 2013 for Windows Desktop�ADX���C�u�����œ�����m�F���Ă��܂��B
	ssbp��png������΍Đ����鎖���ł��܂����AResources�t�H���_��sspj���܂܂�Ă��܂��B

	**********************************************************************************/

	//���\�[�X�}�l�[�W���̍쐬
	resman = ss::ResourceManager::getInstance();
	//�v���C���[�̍쐬
	ssplayer = ss::Player::create();

	//�A�j���f�[�^�����\�[�X�ɒǉ�

	//���ꂼ��̃v���b�g�t�H�[���ɍ��킹���p�X�֕ύX���Ă��������B
	resman->addData("character_template_comipo\\character_template1.ssbp");
	//�v���C���[�Ƀ��\�[�X�����蓖��
	ssplayer->setData("character_template1");        // ssbp�t�@�C�����i�g���q�s�v�j
	//�Đ����郂�[�V������ݒ�
	ssplayer->play("character_template_3head/stance");				 // �A�j���[�V���������w��(ssae��/�A�j���[�V���������\�A�ڂ����͌�q)

	//�\���ʒu��ݒ�
	ssplayer->setPosition(1280/2, 600);
	//�X�P�[���ݒ�
	ssplayer->setScale(0.5f, 0.5f);
	//��]��ݒ�
	ssplayer->setRotation(0.0f, 0.0f, 0.0f);
	//�����x��ݒ�
	ssplayer->setAlpha(255);

}

//���C�����[�v
//Z�{�^���ŃA�j�����|�[�Y�A�ĊJ��؂�ւ��ł��܂��B
//�|�[�Y���͍��E�L�[�ōĐ�����t���[����ύX�ł��܂��B
bool push = false;
int count = 0;
bool pause = false;
void update(float dt)
{

	int animax = ssplayer->getMaxFrame();
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		mGameExec = 0;
	}

	if (CheckHitKey(KEY_INPUT_Z))
	{
		if (push == false )
		{
			if (pause == false )
			{
				pause = true;
				count = 0;
				ssplayer->pause();
			}
			else
			{
				pause = false;
				ssplayer->resume();
			}
		}
		push = true;

	}
	else if (CheckHitKey(KEY_INPUT_UP))
	{
		if (push == false)
		{
			count += 20;
			if (count >= animax)
			{
				count = 0;
			}
		}
		push = true;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		if (push == false)
		{
			count -= 20;
			if (count < 0)
			{
				count = animax - 1;
			}
		}
		push = true;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		if (push == false)
		{
			count--;
			if (count < 0)
			{
				count = animax-1;
			}
		}
		push = true;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		if (push == false)
		{
			count++;
			if (count >= animax)
			{
				count = 0;
			}
		}
		push = true;
	}
	else
	{
		push = false;
	}

	if (pause == true)
	{
		ssplayer->setFrameNo(count % animax);
	}

	//�A�j���[�V�����̃t���[����\��
	char str[128];
	sprintf(str, "play:%d frame:%d", (int)pause, count );
	DrawString(100, 100, str, GetColor(255, 255, 255));

	//�v���C���[�̍X�V�A�����͑O��̍X�V��������o�߂�������
	ssplayer->update(dt);
	//�v���C���[�̕`��
	ssplayer->draw();

}

/**
* �v���C���[�I������
*/
void relese( void )
{

	//�e�N�X�`���̉��
	resman->releseTexture("character_template1");
	//SS5Player�̍폜
	delete (ssplayer);	
	delete (resman);
}









