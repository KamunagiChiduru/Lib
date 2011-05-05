#ifndef LIB_CSTOPWATCH_HPP
#define LIB_CSTOPWATCH_HPP

#include <tchar.h>
#include <windows.h>
#include "CException.hpp"

namespace Lib{

	/**
	 *	������\�p�t�H�[�}���X�J�E���^��p�����A���Ԍv���p�N���X.
	 *
	 *	StopWatch.h ver0.2���x�[�X�ɍ���Ă���B
	 *	�g�p�֐��̐��\��AStopWatch::Precision()�ȏ�̐��x�͕ۏ؂���Ȃ��B
	 *
	 *	@author	Chiduru
	 *	@version	0.02
	 */
	class CStopWatch{
		public:
			explicit CStopWatch(double unit);
			explicit CStopWatch(CStopWatch const& obj);
			~CStopWatch();
		public:
			void Start();
			void Stop();
			double Time() const;
			double Precision() const;
			double Unit() const;
		private:
			double _unit;
			LARGE_INTEGER* _freq;
			LARGE_INTEGER* _start_time;
			LARGE_INTEGER* _stop_time;
	};
	
	/**
	 *	�R���X�g���N�^.
	 *
	 *	@since	0.01
	 *	@param	unit	�g�p�P�ʁB1ms�Ȃ�1.0e-3�A1us�Ȃ�1.0e-6�A1ns�Ȃ�1.0e-9�Ǝw�肷��B
	 */
	CStopWatch::CStopWatch(double unit= 1.0e-3) : _unit(unit){
		BOOL supported;
		
		try{
			_freq= new LARGE_INTEGER;
			_start_time= new LARGE_INTEGER;
			_stop_time= new LARGE_INTEGER;
		}
		catch(std::bad_alloc const&){
			CException e(_T("�������̊m�ۂɎ��s���܂����B"));
			throw e;
		}
		
		supported= QueryPerformanceFrequency(_freq);
		
		if(_unit <= 0){
			CException e(_T("�P�ʂɂ́A���̎������w�肵�Ă��������B"));
			throw e;
		}
		if(!supported){
			CException e(_T("�G���[���N���܂����B�n�[�h�E�F�A��������\�p�t�H�[�}���X�J�E���^���T�|�[�g���Ă��Ȃ��\��������܂��B"));
			throw e;
		}
	}
	
	/**
	 *	�R�s�[�R���X�g���X�^.
	 *
	 *	@since	0.01
	 *	@param	obj	��R�s�[�I�u�W�F�N�g
	 */
	CStopWatch::CStopWatch(CStopWatch const& obj){
		_unit= obj._unit;
		
		try{
			_freq= new LARGE_INTEGER;
			_start_time= new LARGE_INTEGER;
			_stop_time= new LARGE_INTEGER;
		}
		catch(std::bad_alloc const&){
			CException e(_T("�������̊m�ۂɎ��s���܂����B"));
			throw e;
		}
		
		*_freq= *(obj._freq);
		*_start_time= *(obj._start_time);
		*_stop_time= *(obj._stop_time);
	}
	
	/**
	 *	�f�X�g���N�^.
	 *
	 *	@since	0.01
	 */
	inline
	CStopWatch::~CStopWatch(){
		delete _freq;
		_freq= NULL;
		
		delete _start_time;
		_start_time= NULL;
		
		delete _stop_time;
		_stop_time= NULL;
	}
	
	/**
	 *	�v���J�n.
	 *
	 *	@since	0.01
	 */
	inline
	void CStopWatch::Start(){
		QueryPerformanceCounter(_start_time);
	}
	
	/**
	 *	�v����~.
	 *
	 *	@since	0.01
	 */
	inline
	void CStopWatch::Stop(){
		QueryPerformanceCounter(_stop_time);
	}
	
	/**
	 *	���߂̌v������.
	 *
	 *	@since	0.01
	 *	@return	���߂̌v�����Ԃ�\��double�^�̒l
	 */
	inline
	double CStopWatch::Time() const{
		double time, unit;
		
		unit= 1.0 / (_unit * _freq->QuadPart);
		time= static_cast<double>(_stop_time->QuadPart - _start_time->QuadPart);
		
		return time * unit;
	}
	
	/**
	 *	�v�����x.
	 *
	 *	[1�b������̌o�߃J�E���g��]^-1�̂��ƁB
	 *	1�J�E���g�����艽�b�ɑ������邩�B
	 *
	 *	@since	0.01
	 *	@return	�v�����x
	 */
	double CStopWatch::Precision() const{
		return 1.0 / (_freq->QuadPart * _unit);
	}
	
	/**
	 *	�P��.
	 *
	 *	Time()�ŕԂ����l�̌��B
	 *
	 *	@since	0.02
	 *	@return	�P��
	 */
	double CStopWatch::Unit() const{
		return _unit;
	}

}

#endif
