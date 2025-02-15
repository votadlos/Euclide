// Field.h: interface for the Field class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELD_H__9B9A420F_8530_11D5_A253_80542EFCACA3__INCLUDED_)
#define AFX_FIELD_H__9B9A420F_8530_11D5_A253_80542EFCACA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*  ласс пол€ элемнтов по простому модулю с операци€ми в поле */
class Field  
{
public: 
	long Module;//модуль
	long Data;//€чейка дл€ хранени€ числа
public:
	Field();
	Field(long m, long data);
	Field(Field &);
	CString toString();//строковое представление
	Field &operator +(Field &);
	Field &operator -(Field &);
	Field &operator *(Field &);
	Field &operator /(Field &);
	Field &field_pow(int);//возведение в целую степень
	void operator =(Field &);
	int operator ==(Field &);
	void setData(long);
	void setModule(long);
	void set(long,long);
	
	virtual ~Field();

};

#endif // !defined(AFX_FIELD_H__9B9A420F_8530_11D5_A253_80542EFCACA3__INCLUDED_)
