#ifndef	LIB_CBUCKET_HPP
#define	LIB_CBUCKET_HPP

#include	<string.h>

namespace Lib{
	template<class Ttype>
	class CBucket{
		public:
			/**
			 *	�R���X�g���N�^.
			 *
			 *	@since	0.01
			 */
			explicit CBucket();
			
			/**
			 *	�f�X�g���N�^.
			 *
			 *	@since	0.01
			 */
			~CBucket();
			
			/**
			 *	�n�b�V���L�[�Z�b�g.
			 *
			 *	@since	0.01
			 *	@param	key		�n�b�V���L�[
			 */
			int Set(const char* key, const Ttype& data);
			
			/**
			 *	�f�[�^�Z�b�g.
			 *
			 *	@since	0.01
			 *	@param	data	�f�[�^
			 */
			int SetData(const Ttype& data);
			
			/**
			 *	�n�b�V���L�[�擾.
			 *
			 *	@since	0.01
			 *	@return	�n�b�V���L�[
			 */
			const char* GetKey() const;
			
			/**
			 *	�f�[�^�擾.
			 *
			 *	@since	0.01
			 *	@return	�f�[�^
			 */
			const Ttype& GetData() const;
			
		private:
			/**
			 *	�i�[����f�[�^.
			 *
			 *	@since	0.01
			 */
			Ttype	m_data;
			
			/**
			 *	�n�b�V���L�[.
			 *
			 *	@since	0.01
			 */
			char*	m_key;
			
	};

	/**
	 *	�R���X�g���N�^.
	 *
	 *	@since	0.01
	 */
	template<class Ttype>
	CBucket<Ttype>::CBucket(){
		m_key=	new char[0];
	}

	/**
	 *	�f�X�g���N�^.
	 *
	 *	@since	0.01
	 */
	template<class Ttype>
	CBucket<Ttype>::~CBucket(){
		delete [] m_key;
	}

	/**
	 *	�n�b�V���L�[�ƒl���Z�b�g.
	 *
	 *	@since	0.01
	 *	@param	key		�n�b�V���L�[
	 *	@param	data	�f�[�^
	 *	@return	�Z�b�g������������1�A���s������0
	 */
	template<class Ttype>
	int CBucket<Ttype>::Set(const char* key, const Ttype& data){
		int	length=	strlen(key) + 1;
		
		delete [] m_key;
		m_key=	new char[length];
		strcpy(m_key, key);
		
		m_data=	data;
		
		return 1;
	}

	/**
	 *	�n�b�V���L�[���Q�b�g.
	 *
	 *	@since	0.01
	 *	@return	�n�b�V���L�[
	 */
	template<class Ttype>
	const char* CBucket<Ttype>::GetKey() const{
		return m_key;
	}

	/**
	 *	�f�[�^���Q�b�g.
	 *
	 *	@since	0.01
	 *	@return	�f�[�^
	 */
	template<class Ttype>
	const Ttype& CBucket<Ttype>::GetData() const{
		return m_data;
	}
}

#endif	//	LIB_CBUCKET_HPP
