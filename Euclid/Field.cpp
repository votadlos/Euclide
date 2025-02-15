// Field.cpp: implementation of the Field class.
//
//////////////////////////////////////////////////////////////////////
#include <math.h>
#include <stdlib.h>
#include "stdafx.h"
#include "Euclid.h"
#include "Field.h"
#include "Vect2.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

Field::Field()
{
	Module = 0;
	Data = 0;
}
Field::Field(long m, long data)
{
	Module = m;
	Data = data;
}
Field::Field(Field &a){
	Module = a.Module;
	Data = a.Data;
}
///////////////////////////////////////////////////////////
void Field::setData(long a){
	this->Data=a;
}
void Field::setModule(long m){
	this->Module=m;
}
void Field::set(long a, long m){
	this->Data = a;
	this->Module = m;
}
///////////////////////////////////////////////////////////
void Field::operator =(Field &a){
	Module = a.Module;
	Data = a.Data;
}
///////////////////////////////////////////////////////////
Field &Field::operator +(Field &a){
	long mod = this->Module; 
	Field *ret = new Field(mod, (a.Data + this->Data) % mod);
	return *ret;
}
///////////////////////////////////////////////////////////
Field &Field::operator -(Field &a){
	long mod = this->Module; 
	long tmp = (this->Data - a.Data) % mod;
	if (tmp<0) tmp = tmp + mod;
	Field *ret = new Field(mod, tmp);
	return *ret;
}
///////////////////////////////////////////////////////////
Field &Field::operator *(Field &a){
	long mod = this->Module; 
	Field *ret = new Field(mod, (a.Data * this->Data) % mod);
	return *ret;
}
///////////////////////////////////////////////////////////
int Field::operator ==(Field &a){
	/* 1 - если эквивалентны
	 * 0 - нет
	 */
	this->Data %= this->Module;
	a.Data %= a.Module;
	if ((this->Data == a.Data)&&(this->Module == a.Module)){
		return 1;
	}
	else{
		return 0;
	}
}
///////////////////////////////////////////////////////////
Field &Field::operator /(Field &a){
	/* для нахождения частного Data и a ищется обратное для а
	 * по алгоритму Евклида (ищется НОД для а и Module); 
	 * возвращается произведение обратного для а на Data
	 */
	Vect2 n1, n2, tmp, tmp1;
	long N1, N2, TMP, i, a_1;
	long mod = this->Module;
	ldiv_t res;
	
	//первое число всегда больше, т.к. в N1 модуль
	n1.set(1,0); n2.set(0,1);
	N2 = a.Data % mod; N1 = mod;
	//n11=N1; n22=N2;
	//n1.show(); n2.show();
	for (i=0;N2>0;i++){
		res = ldiv(N1,N2);
		N1 = N2;
		N2 = res.rem;//остаток
		TMP = res.quot;//частное
		tmp.set(n2.rize(TMP));//tmp = a*n2
		tmp1.set(n1.minus(tmp));//n1 = n1 - tmp == n3
		n1.set(n2); n2.set(tmp1);//n1 = n2; n2 = n3
	}
	//n1.show(n11,n22,N1);
	//n11 - первое число
	//n22 - второе число
	//N1 - найденный НОД
	//в n1 хранятся коэффициенты разложения: v1*n11+v2*n22=N1		
	//в n1.v2 хранится обратное для а
	if (n1.v2 < 0) n1.v2 = n1.v2 + mod;
	a_1 = n1.v2;//правильное обратное для а
	Field *ret = new Field(mod, (a_1 * this->Data) % mod);
	return *ret;
}
///////////////////////////////////////////////////////////
Field &Field::field_pow(int n){
	long mod = this->Module,
		data = this->Data,
		ret_data = data;

	if (n==0) return *(new Field(mod,1));
	if ((n==1)||(data==1)||(data==0)) return *this;
	if (n>1){
		if (data>=sqrt(LONG_MAX)){
			//data очень большое
			for (int i=2; i<=n; i++) 
				ret_data = (ret_data*data)%mod;
		}else{
			for(int i=2; i<=n; i++) ret_data = ret_data*data;
			ret_data %= mod;
		}
	}
	return *(new Field(mod,ret_data));
}
///////////////////////////////////////////////////////////
CString Field::toString(){
	char buffer[50];
	_ltoa(Data,buffer,10);
	CString ret(buffer);
	return ret;
}
///////////////////////////////////////////////////////////
Field::~Field()
{

}
