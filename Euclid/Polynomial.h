// Polynomial.h: interface for the Polynomial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYNOMIAL_H__01D2DDC1_878E_11D5_A253_DD06F11FADA1__INCLUDED_)
#define AFX_POLYNOMIAL_H__01D2DDC1_878E_11D5_A253_DD06F11FADA1__INCLUDED_

#include "Field.h"	// Added by ClassView
#include "Div_poly.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define LOG_DIR  "log"//���������� ����

struct fac_rec{ //���������, ��� ��� ������������
		long q;//������� ������
		struct fac_rec *next;//��������� ������� ������
};

/* ����� ����������� ������� � ���������� ��� ��� */
class Polynomial  
{
public:
	Polynomial(char *coeff,int len, long mod, BOOL endian = FALSE);
	Polynomial(int deg = 0, Field *coeff = NULL);
	void set(int deg = 0, Field *coeff = NULL);
	Polynomial(Polynomial &);
	Polynomial &operator +(Polynomial &);
	Polynomial &operator -(Polynomial &);
	Polynomial &operator *(Polynomial &);
	void operator =(Polynomial &);
	Div_poly &div(Polynomial &p, CProgressCtrl *progress = NULL);
	int operator ==(Polynomial &);
	CString toString(BOOL endian = FALSE);
	virtual ~Polynomial();
	void del_fict_coeff();//������� ������� �����. ��� �������
					//��������
	void del_fict_coeff(int &deg, Field * & coeff);
	int isSimple(CProgressCtrl *progress = NULL);//��������� �� ��������������
	int isSimpleB(CProgressCtrl *progress = NULL);//���� ����������
	int isPrime(CProgressCtrl *progress = NULL);//��������� �� �������������
	Field &calculate(Field &);//��������� �������� ����������
						//�� �����-���� �������� ����
	static fac_rec* factor(long);//������������ ������������
	static BOOL isAdmissible(int deg);//��������� ������� �� ������������
	static void kill_factor(fac_rec *);
	static void endian_hdl(char *,int,BOOL);//����������� ������ �� 
		//little-endian � big-endian ������ � ��������
public:
	int Deg;//�������
	int Err;//��� ������
	Field *Coeff;//������ �������������
	//������� ����� ����� �������� ����� ������
	static int counter;
	//��� ���� ������� ��� ��������������
	static FILE *log;
private:
	int was_new;
private:
	void add_coeff(int);//��������� ������� �����. 
					//�� ��������� �������
	int make_compare(Polynomial &);//������ ����������
					//��� ������ add_coeff(int)
};

#endif // !defined(AFX_POLYNOMIAL_H__01D2DDC1_878E_11D5_A253_DD06F11FADA1__INCLUDED_)
