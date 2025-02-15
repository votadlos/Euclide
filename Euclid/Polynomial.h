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

#define LOG_DIR  "log"//директория лога

struct fac_rec{ //структура, исп при факторизации
		long q;//текущий фактор
		struct fac_rec *next;//следующий элемент списка
};

/* Класс реализующий полином с операциями над ним */
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
	void del_fict_coeff();//удаляет нулевые коефф. при старших
					//степенях
	void del_fict_coeff(int &deg, Field * & coeff);
	int isSimple(CProgressCtrl *progress = NULL);//проверяет на неприводимость
	int isSimpleB(CProgressCtrl *progress = NULL);//тест Берлекемпа
	int isPrime(CProgressCtrl *progress = NULL);//проверяет на примитивность
	Field &calculate(Field &);//вычисляет значение многочлена
						//на каком-лидо элементе поля
	static fac_rec* factor(long);//осуществляет факторизацию
	static BOOL isAdmissible(int deg);//проверяет степень на допустимость
	static void kill_factor(fac_rec *);
	static void endian_hdl(char *,int,BOOL);//преобразует строку из 
		//little-endian в big-endian формат и наоборот
public:
	int Deg;//степень
	int Err;//код ошибки
	Field *Coeff;//массив коэффициентов
	//считает общее число объектов этого класса
	static int counter;
	//лог куда пишутся все преобразования
	static FILE *log;
private:
	int was_new;
private:
	void add_coeff(int);//добавляет нулевые коефф. 
					//до указанной степени
	int make_compare(Polynomial &);//делает сравнимыми
					//при помощи add_coeff(int)
};

#endif // !defined(AFX_POLYNOMIAL_H__01D2DDC1_878E_11D5_A253_DD06F11FADA1__INCLUDED_)
