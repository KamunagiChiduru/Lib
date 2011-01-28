#ifndef	__CHASH_HPP__
#define	__CHASH_HPP__

#include	<string.h>
#include	"CBucket.hpp"

/**
 *	�n�b�V���p�N���X.
 *
 *	�ۑ�
 *	�`�F�C���@����������
 *
 *	@author	Chiduru
 *	@version	0.01
 */
template<class Ttype>
class CHash{
	public:
		/**
		 *	�f�t�H���g�R���X�g���N�^.
		 *	�n�b�V���e�[�u���̑傫��10�ŏ������B.
		 *
		 *	@since	0.01
		 */
		explicit CHash();
		
		/**
		 *	�R���X�g���N�^.
		 *	�n�b�V���e�[�u���̑傫�����w�肵�ď������B.
		 *
		 *	@since	0.01
		 *	@param	hash_table_size	�n�b�V���e�[�u���̑傫��
		 */
		explicit CHash(int hash_table_size);
		
		/**
		 *	�f�X�g���N�^.
		 *
		 *	@since	0.01
		 */
		~CHash();
		
		/**
		 *	key�ɑΉ�����f�[�^��Ԃ�.
		 *
		 *	@since	0.01
		 *	@param	key	�n�b�V���L�[
		 *	@return	�f�[�^
		 */
		const Ttype& Get(const char* key) const;
		
		/**
		 *	key�ɑΉ��Â��ăf�[�^���n�b�V���e�[�u���Ɋi�[.
		 *
		 *	@since	0.01
		 *	@param	key		�n�b�V���L�[
		 *	@param	data	�i�[����f�[�^
		 *	@return	�i�[�Ɏ��s�����ꍇ�̂�0
		 */
		int Set(const char* key, const Ttype& data);
		
	private:
		/**
		 *	�n�b�V���֐�.
		 *	�n�����L�[�ɑΉ������n�b�V���l�𐶐����ĕԂ��B.
		 *	ver0.01�ł́Akey�œn���ꂽ������̕��ϒl�����B.
		 *
		 *	@since	0.01
		 *	@param	key	�n�b�V���L�[
		 *	@return	�������ꂽ�n�b�V���l
		 */
		int CalculationHash(const char* key) const;
		
		/**
		 *	�f�t�H���g�̃n�b�V���e�[�u���T�C�Y.
		 *
		 *	@since	0.01
		 */
		static const int m_default_hash_table_size=	10;
		
		/**
		 *	�m�ۂ��ꂽ�n�b�V���e�[�u���̃T�C�Y.
		 *
		 *	@since	0.01
		 */
		int	m_hash_table_size;
		
		/**
		 *	�n�b�V���e�[�u��.
		 *
		 *	@since	0.01
		 */
		CBucket<Ttype>* m_hash_table;
		
};

/**
 *	�f�t�H���g�R���X�g���N�^.
 *	�n�b�V���e�[�u���̑傫��10�ŏ������B.
 *
 *	@since	0.01
 */
template<class Ttype> CHash<Ttype>::CHash(){
	m_hash_table=	new CBucket<Ttype>[m_default_hash_table_size];
	
	//	�n�b�V���e�[�u���̃T�C�Y��ۑ�
	m_hash_table_size=	m_default_hash_table_size;
}

/**
 *	�R���X�g���N�^.
 *	�n�b�V���e�[�u���̑傫�����w�肵�ď������B.
 *
 *	@since	0.01
 *	@param	hash_table_size	�n�b�V���e�[�u���̑傫��
 */
template<class Ttype> CHash<Ttype>::CHash(int hash_table_size){
	m_hash_table=	new CBucket<Ttype>[hash_table_size];
	
	//	�n�b�V���e�[�u���̃T�C�Y��ۑ�
	m_hash_table_size=	hash_table_size;
}

/**
 *	�f�X�g���N�^.
 *
 *	@since	0.01
 */
template<class Ttype> CHash<Ttype>::~CHash(){
	delete [] m_hash_table;
}

/**
 *	key�ɑΉ�����f�[�^��Ԃ�.
 *
 *	@since	0.01
 *	@param	key	�n�b�V���L�[
 *	@return	�f�[�^
 */
template<class Ttype> const Ttype& CHash<Ttype>::Get(const char* key) const{
	int	index=	CalculationHash(key) % m_hash_table_size;
	
	return m_hash_table[index].GetData();
}

/**
 *	key�ɑΉ��Â��ăf�[�^���n�b�V���e�[�u���Ɋi�[.
 *
 *	@since	0.01
 *	@param	key		�n�b�V���L�[
 *	@param	data	�i�[����f�[�^
 *	@return	�i�[�Ɏ��s�����ꍇ�̂�0
 */
template<class Ttype> int CHash<Ttype>::Set(const char* key, const Ttype& data){
	int	index=	CalculationHash(key) % m_hash_table_size;
	
	m_hash_table[index].Set(key, data);
	
	return 1;
}

/**
 *	�n�b�V���֐�.
 *	�n�����L�[�ɑΉ������n�b�V���l�𐶐����ĕԂ��B.
 *	ver0.01�ł́Akey�œn���ꂽ������̕��ϒl�����B.
 *
 *	@since	0.01
 *	@param	key	�n�b�V���L�[
 *	@return	�������ꂽ�n�b�V���l
 */
template<class Ttype> int CHash<Ttype>::CalculationHash(const char* key) const{
	int	average=	0;
	int	count=		0;
	
	while(*key){
		average+=	static_cast<int>(*key);
		++count;
		++key;
	}
	
	average/=	count;
	
	return average;
}

#endif	//	__CHASH_HPP__
