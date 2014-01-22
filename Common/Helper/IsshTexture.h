#ifndef __ISSGraphTexture__
#define __ISSGraphTexture__


class ISSTexture
{
public:
	virtual int	getWidth() = 0;
	virtual int	getHeight() = 0;

	virtual bool	Load( const char* filename ) = 0;
	virtual ISSTexture* create() = 0;
};

class	SSTextureFactory
{
private:
	static ISSTexture*			m_texture_base_class;
	static SSTextureFactory*		m_myInst;

public:
	SSTextureFactory(){}
	SSTextureFactory(ISSTexture* texture_base_class){ m_myInst = this ; m_texture_base_class = texture_base_class;}
	virtual ~SSTextureFactory()
	{
		if ( m_texture_base_class )
			delete m_texture_base_class;
	}

	static bool	isExist(){ return m_myInst != 0; }
	
	static ISSTexture*	create(){ return m_texture_base_class->create(); }
};


// n��2�ׂ̂��悩�ǂ����`�F�b�N����
inline bool SsUtTextureisPow2(int n)
{
	for (int i = 0; i < 16; i++)
	{
		if (n == (1 << i)) return true;
	}
	return false;
}


#endif //ifdef __ISSGraphTexture__
