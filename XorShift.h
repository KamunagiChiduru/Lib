#ifndef	XORSHIFT_H
#define	XORSHIFT_H

#include <stdlib.h>
#include <time.h>

#ifdef	__cplusplus
extern "C"{
#endif

typedef struct{
	unsigned long x;
	unsigned long y;
	unsigned long z;
	unsigned long w;
}XorShift, *lpXorShift;

//	�v���g�^�C�v
void XorShift_New(lpXorShift*);
void XorShift_NewWith(lpXorShift*, unsigned long);
void XorShift_Delete(lpXorShift*);
unsigned long XorShift_Generate(lpXorShift);

/**
 *	�\���̏�����.
 *
 *	@param	lpxs	XorShift�\���̂ւ̃|�C���^�̃|�C���^
 */
void XorShift_New(lpXorShift* lpxs){
	XorShift_NewWith(lpxs, (unsigned long)time(NULL));
}

/**
 *	�\���̏�����.
 *
 *	@param	lpxs	XorShift�\���̂ւ̃|�C���^�̃|�C���^
 *	@param	s		�����̎�
 */
void XorShift_NewWith(lpXorShift* lpxs, unsigned long s){
	*lpxs= (lpXorShift)calloc(1, sizeof(XorShift));
	
	(*lpxs)->x= s;
	(*lpxs)->y= (1234 * (*lpxs)->x + 5678);
	(*lpxs)->z= (1234 * (*lpxs)->y + 5678);
	(*lpxs)->w= (1334 * (*lpxs)->z + 5678);
}

/**
 *	�\���̔j��.
 *
 *	@param	lpxs	XorShift�\���̂ւ̃|�C���^�̃|�C���^
 */
void XorShift_Delete(lpXorShift* lpxs){
	free(*lpxs);
	*lpxs= NULL;
}

/**
 *	��������.
 *
 *	@param	lpxs	XorShift�\���̂ւ̃|�C���^
 *	@return	32bit�̗���
 */
unsigned long XorShift_Generate(lpXorShift lpxs){
	unsigned long t;
	
	t= lpxs->x ^ (lpxs->x << 11);
	lpxs->x= lpxs->y;
	lpxs->y= lpxs->z;
	lpxs->z= lpxs->w;
	
	lpxs->w= (lpxs->w ^ (lpxs->w >> 19)) ^ (t ^ (t >> 8));
	
	return lpxs->w;
}

#ifdef	__cplusplus
}
#endif

#endif	//	#ifndef	XORSHIFT_H
