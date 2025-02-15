// Polynomial.cpp: implementation of the Polynomial class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Euclid.h"
#include "Polynomial.h"
#include "EuclidDlg.h"
#include "Euclid_return.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//статитеские переменные
CProgressCtrl CEuclidDlg::m_Progress;
CStatic CEuclidDlg::m_What;
BOOL CEuclidDlg::m_NoLog;
//CProgressCtrl CEuclidDlg::m_MainProgress;

///////////////////////////////////////////////////////////////
Polynomial::Polynomial(Polynomial &a){
	Deg = a.Deg;
	time_t now = time(NULL);
	Coeff = new Field[Deg+1];
	was_new = 1;
	Err = a.Err;
	log = a.log;
	counter = a.counter;
	Polynomial::counter++;
	for(int i=0; i<=Deg; i++){
		Coeff[i]=a.Coeff[i];
		CEuclidDlg::showProgress();
	}
	if (!CEuclidDlg::m_NoLog){
		CString coeff = this->toString();
		fprintf(Polynomial::log,"%sPolynomial #%d (%s) successfully created\nmodule: %d\n-----\n", \
		ctime(&now), Polynomial::counter,coeff, Coeff[0].Module);
	}
}
///////////////////////////////////////////////////////////////////////////
Polynomial::Polynomial(char *coeff,int len, long mod, BOOL endian){
	// в строке coeff разделителем пробел (' ') 
	Polynomial::endian_hdl(coeff,len,endian);
	time_t now = time(NULL);
	Polynomial::counter++;//появился новый объект
	int i, flag;
	coeff[len] = NULL;
	Err = 0;//предварительный результат инициализации
	if (mod <=0 ){
		Err = 1;//неверный модуль
		fprintf(Polynomial::log,"%sError 1: Wrong module.\nCreation interrupted.\n-----\n", \
			ctime(&now));
		was_new = 0;//выход из конструктора => new не будет
		return;
	}
	if (coeff == ""){
		Err = 2;//неверный (пустой) коефф.
		fprintf(Polynomial::log,"%sError 2: Empty coefficient field.\nCreation interrupted.\n-----\n", \
			ctime(&now));
		was_new = 0;//выход из конструктора => new не будет
		return;
	}
	flag = 0;
	if (coeff[len - 1] != ' '){
		flag = 1;
	}
	//подсчитать степень = число пробелов
	int spaces=0;//число пробелов
	for(i=0; i<len; i++){
		if (coeff[i] == ' ')
			spaces++;
	}
	Deg = spaces - 1;//степень многочлена
	if (flag) Deg += 1;
	Coeff = new Field[Deg+1];//его коэффициенты
	was_new = 1;//new случилось
	CString tmp; 
	//tmp.Empty();
	int j=0;
	for(i=0; i<len; i++){
		CEuclidDlg::showProgress();
		if (coeff[i] != ' '){
			//накопление коэффициента в tmp
			tmp += coeff[i];
		}else{
			//в tmp накопился очередной коэффициент
			Coeff[j].set(atol(LPCTSTR(tmp)), mod);
			tmp.Empty(); j++;
		}
	}
	//строка не кончается пробелом
	if (flag){
		Coeff[j].set(atol(LPCTSTR(tmp)), mod);tmp.Empty();
	}
	if (!CEuclidDlg::m_NoLog) fprintf(Polynomial::log,"%sPolynomial #%d (%s) successfully created\nmodule: %d\n-----\n", \
		ctime(&now), Polynomial::counter,coeff, Coeff[0].Module);
}
//////////////////////////////////////////////////////////////
Polynomial::Polynomial(int deg, Field *coeff){
	was_new = 0;
	Err = 0;
	Deg = deg;
	Polynomial::counter++;
	int i;
	long mod;
	time_t now = time(NULL);
	Coeff = NULL;
	mod = 0;
	if (coeff != NULL){ 
		if(deg < 0){
			fprintf(Polynomial::log,"%sError 3: Wrong degree.\nCreation interrupted.\n-----\n", \
				ctime(&now));
			Err = 3;
			was_new = 0;//new не будет
			return;
		}
		Coeff = new Field[Deg+1];
		was_new = 1;//new случилось
		for(i=0; i<=deg; i++){
			CEuclidDlg::showProgress();
			Coeff[i] = coeff[i];
		}
		mod = Coeff[0].Module;
	}
	if (!CEuclidDlg::m_NoLog){
		CString thisp = this->toString();
		fprintf(Polynomial::log,"%sPolynomial #%d (%s) successfully created\nmodule: %d\n-----\n", \
		ctime(&now), Polynomial::counter, LPCTSTR(thisp), mod);
	}
}
//////////////////////////////////////////////////////////////
void Polynomial::set(int deg, Field *coeff){
	Err = 0;
	int i;
	time_t now = time(NULL);
	CString oldp = this->toString();
	if (was_new) delete [] Coeff;
	CString tmp("");
	for(i=0; i<=deg; i++){
		CEuclidDlg::showProgress();
		tmp += coeff[i].toString();
		tmp += " ";
	}
	if(deg < 0){
		fprintf(Polynomial::log,"%sError 3: Wrong degree.\nCreation interrupted.\n-----\n", \
			ctime(&now));
		Err = 3;
		was_new = 0;//new не будет
		return;
	}
	Deg = deg;
	Coeff = new Field[Deg+1];
	was_new = 1;//new случилось
	for(i=0; i<=deg; i++){
		CEuclidDlg::showProgress();
		Coeff[i] = coeff[i];
	}
	if (!CEuclidDlg::m_NoLog) {
		CString newp = this->toString();
		fprintf(Polynomial::log,"Polynomial (%s) set to (%s)\nmodule: %d\n-----\n", \
		LPCTSTR(oldp),LPCTSTR(newp),Coeff[0].Module);
	}
}
//////////////////////////////////////////////////////////////
void Polynomial::operator =(Polynomial &a){
	CString oldp = this->toString();
	if (was_new) delete [] Coeff;
	Deg = a.Deg;
	Coeff = new Field[Deg+1];
	was_new = 1;
	Err = a.Err;
	log = a.log;
	counter = a.counter;
	for(int i=0; i<=Deg; i++){
		CEuclidDlg::showProgress();
		Coeff[i]=a.Coeff[i];
	}
	if (!CEuclidDlg::m_NoLog) {
		CString newp = this->toString();
		fprintf(Polynomial::log,"Polynomial (%s) became new polynomial (%s)\nmodule: %d.\n-----\n", \
		LPCTSTR(oldp), LPCTSTR(newp), Coeff[0].Module);
	}
}
//////////////////////////////////////////////////////////////
Polynomial &Polynomial::operator +(Polynomial &a){
	int ret_deg = make_compare(a);
	Field *ret_coeff = new Field[ret_deg + 1];
	for(int i=0; i<=ret_deg; i++){
		CEuclidDlg::showProgress();
		ret_coeff[i] = Coeff[i] + a.Coeff[i];
	}
	Polynomial *ret = new Polynomial(ret_deg, ret_coeff);
	delete [] ret_coeff;
	//удалить нулев коэфф при старших степенях
	ret->del_fict_coeff();
	//запись в лог
	if (!CEuclidDlg::m_NoLog){
		CString ret_str = ret->toString();
		CString a_str = a.toString();
		CString this_str = this->toString();
		fprintf(Polynomial::log,"(%s) + (%s) = (%s)\n-----\n",LPCTSTR(this_str),LPCTSTR(a_str),LPCTSTR(ret_str));
	}
	return *ret;
}
//////////////////////////////////////////////////////////////
// Делает многочлен заданной степени, соотв. коефф делает нулевыми
void Polynomial::add_coeff(int new_deg){
	Field *coeff = new Field[new_deg + 1];
	int i;
	for(i=0; i<=Deg; i++){
		CEuclidDlg::showProgress();
		coeff[i] = Coeff[i];
	}
	for(i=Deg+1;i<=new_deg;i++){
		CEuclidDlg::showProgress();
		coeff[i].set(0,Coeff[0].Module);
	}
	delete [] Coeff;
	Coeff = coeff;
	Deg = new_deg;
}
//////////////////////////////////////////////////////////////
//делает многочлены одинаковой степени, возвращает эту степень
int Polynomial::make_compare(Polynomial &a){
	int ret_deg;
	if (Deg >= a.Deg){
		ret_deg = Deg;
		a.add_coeff(ret_deg);
	}
	else{
		ret_deg = a.Deg;
		add_coeff(ret_deg);
	}
	return ret_deg;
}
//////////////////////////////////////////////////////////////
Polynomial &Polynomial::operator -(Polynomial &a){
	int ret_deg = make_compare(a);
	Field *ret_coeff = new Field[ret_deg + 1];
	for(int i=0; i<=ret_deg; i++){
		CEuclidDlg::showProgress();
		ret_coeff[i] = Coeff[i] - a.Coeff[i];
	}
	Polynomial *ret = new Polynomial(ret_deg, ret_coeff);
	delete [] ret_coeff;
	//удалить нулев коэфф при старших степенях
	ret->del_fict_coeff();
	//запись в лог
	if (!CEuclidDlg::m_NoLog) {
		CString a_str = a.toString();
		CString this_str = this->toString();
		CString ret_str = ret->toString();
		fprintf(Polynomial::log,"(%s) - (%s) = (%s)\n-----\n",LPCTSTR(this_str),LPCTSTR(a_str),LPCTSTR(ret_str));
	}
	return *ret;	
}
//////////////////////////////////////////////////////////////
Polynomial &Polynomial::operator *(Polynomial &a){
	int i,j;
	int aDeg = a.Deg;
	int ret_deg = aDeg + Deg;
	long mod = Coeff[0].Module;
	Field *ret_coeff;
	Field **matr;
	Polynomial *ret;
	
	//возвр коефф
	if (ret_deg == 0) ret_coeff = new Field;
	else ret_coeff = new Field[ret_deg + 1];
	//временная матрица
	if (aDeg == 0) matr = new Field *;
	else matr = new Field *[aDeg+1];
	/* Заполнение вспомогательной матрицы, например:
	 * (2 3 4 2)*(1 2 3)=
	 *--------------------
	 *| 1* | 2 3 4 2 0 0 |
	 *| 2* | 0 2 3 4 2 0 | aDeg
	 *| 3* | 0 0 2 3 4 2 |
	 *--------------------
	 *      ret_deg
	 */
	//занулить временную матрицу

	if (ret_deg == 0){
		for(i=0;i<=aDeg;i++){
			matr[i] = new Field;
			for(j=0;j<=ret_deg;j++){
				CEuclidDlg::showProgress();
				matr[i][j].set(0,mod);
			}
		}
	}
	else{
		for(i=0;i<=aDeg;i++){
			matr[i] = new Field[ret_deg+1];
			for(j=0;j<=ret_deg;j++){
				CEuclidDlg::showProgress();
				matr[i][j].set(0,mod);
			}
		}
	}
	//заполнить временную матрицу
	for(i=0;i<=aDeg;i++)
		for(j=0;j<=Deg;j++){
			CEuclidDlg::showProgress();
			matr[i][j+i] = a.Coeff[i]*Coeff[j];
		}
	//просуммировать столбцы временной матрицы
	Field sum;
	for(i=0;i<=ret_deg;i++){//по столбцам
		sum.set(0,mod);
		for(j=0;j<=aDeg;j++){//по строкам
			CEuclidDlg::showProgress();
			sum = sum + matr[j][i];
		}
		ret_coeff[i] = sum;
	}
	
	ret = new Polynomial(ret_deg, ret_coeff);
	
	//убить возвр коефф
	if (ret_deg == 0) delete ret_coeff; 
	else delete [] ret_coeff;
	//убить врем матр
	if (ret_deg == 0){
		for (i=0;i<=aDeg;i++)
			delete matr[i];
	}
	else{
		for (i=0;i<=aDeg;i++)
			delete [] matr[i];	
	}
	
	if (aDeg == 0) delete matr;
	else delete [] matr;
	
	//удалить нулев коэфф при старших степенях
	ret->del_fict_coeff();
	//запись в лог
	if (!CEuclidDlg::m_NoLog){
		CString a_str = a.toString();
		CString this_str = this->toString();
		CString ret_str = ret->toString();
		fprintf(Polynomial::log,"(%s) * (%s) = (%s)\n-----\n",LPCTSTR(this_str),LPCTSTR(a_str),LPCTSTR(ret_str));
	}
	
	return *ret;	
}
//////////////////////////////////////////////////////////////
int Polynomial::operator ==(Polynomial &a){
	/* равны => 1; иначе 0
	 */
	int i;
	if(Deg != a.Deg) return 0;
	for(i=0; i<=Deg; i++){
		CEuclidDlg::showProgress();
		if(!(Coeff[i]==a.Coeff[i]))
			return 0;
	}
	return 1;
}
//////////////////////////////////////////////////////////////
Div_poly &Polynomial::div(Polynomial &a, CProgressCtrl *progress){
	//обязательно степень делимого больше степени делителя
	//иначе результат не определен!
	//число смещений прогресса: aDeg*aDeg+Deg+1
	Div_poly *ret;
	if (this->Deg < a.Deg){
		ret = new Div_poly(0, Deg, Coeff[0].Module);
		for(int i=0; i<=Deg; i++){
			if (progress) progress->StepIt();
			ret->Rem[i] = Coeff[i];
		}
		ret->Quot[0].Data = 0;
		//запись в лог
		if (!CEuclidDlg::m_NoLog) fprintf(Polynomial::log, \
		"(%s) / (%s) = (%s) + (%s)\n-----\n", \
		LPCTSTR(this->toString()),LPCTSTR(a.toString()), \
		LPCTSTR(ret->quotToString()),LPCTSTR(ret->remToString()));
		return *ret;
	}
	// убрать нулевые коэфф. при старших степенях
	a.del_fict_coeff();
	this->del_fict_coeff();
	int aDeg = a.Deg;
	int remDeg;
	remDeg = ((aDeg == 0) ? 0 : (aDeg-1));
	ret = new Div_poly(Deg-aDeg,remDeg,Coeff[0].Module);
	int i, j;
	Polynomial tmp(Deg, Coeff);//скопировали сюда текущий мн-лен
	for(i=Deg; i>=aDeg; i--){
		Field &k = tmp.Coeff[i]/a.Coeff[aDeg];
		ret->Quot[i-aDeg] = k;
		for(j=aDeg; j>=0; j--){
			CEuclidDlg::showProgress();
			if (progress) progress->StepIt();
			Field &t = tmp.Coeff[i+j-aDeg] - k*a.Coeff[j];
			tmp.Coeff[i+j-aDeg] = t;
		}
	}
	//затащить остаток
	for(i=remDeg; i>=0; i--){
		CEuclidDlg::showProgress();
		if (progress) progress->StepIt();
		ret->Rem[i]=tmp.Coeff[i];
	}
	//удалить фиктивные коэффициенты из остатка и частного
	this->del_fict_coeff(ret->Rem_deg, ret->Rem);
	this->del_fict_coeff(ret->Quot_deg, ret->Quot);
	//запись в лог
	if (!CEuclidDlg::m_NoLog){
		CString a_str = a.toString();
		CString this_str = this->toString();
		CString rem_str = ret->remToString();
		CString quot_str = ret->quotToString();
		fprintf(Polynomial::log, \
		"(%s) / (%s) = (%s) + (%s)\n-----\n", \
		LPCTSTR(this_str),LPCTSTR(a_str),LPCTSTR(quot_str),LPCTSTR(rem_str));
	}
	return *ret;
}
//////////////////////////////////////////////////////////////
void Polynomial::del_fict_coeff(){
	int i, s;
	s = 0;
	long mod = Coeff[0].Module;
	if (Deg<=0) return;
	for(i=Deg; i>0; i--){//число нулей при старших степенях
		if ((Coeff[i].Data%mod) == 0) s++;
		else break;
	}
	Deg = Deg - s;
	Field *coeff = Coeff;
	Coeff = new Field[Deg+1];
	for(i=0; i<=Deg; i++){
		CEuclidDlg::showProgress();
		Coeff[i] = coeff[i];
	}
	delete [] coeff;
}
//////////////////////////////////////////////////////////////
void Polynomial::del_fict_coeff(int &deg, Field * & coeff){
	/* Так как проделываются изменения с массивом, чтобы они были видны
	 * снаружи, необходимо организовать ссылку на указатель....
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 */
	int i, s;
	long mod = coeff[0].Module;
	s = 0;
	if (deg<=0) return;
	for(i=deg; i>0; i--){//число нулей при старших степенях
		if ((coeff[i].Data%mod) == 0) s++;
		else break;
	}
	deg = deg - s;
	//временное хранение ненулевых коэффициентов
	Field *coeff_tmp = coeff;//настроился на старые коэфф.
	coeff = new Field[deg+1];//новые коэффициенты
	for(i=0; i<=deg; i++){
		CEuclidDlg::showProgress();
		coeff[i] = coeff_tmp[i];
	}
	delete [] coeff_tmp;//убил старые коэфф.
}
//////////////////////////////////////////////////////////////
struct fac_rec *Polynomial::factor(long what){
	int cnt = 0;//считает простые множители степени
	//указатель на начало списка
	struct fac_rec *rec = new fac_rec;
	rec->next = NULL;
	//настроились на новую запись
	struct fac_rec *tmp = rec;
	long i, pred;
	pred = 0; 
	//факторизация степени
	while(what>1){
		for(i=2;i<=what;i++){
			CEuclidDlg::showProgress();
			if((what%i)==0){
				if (i != pred){
					tmp->q = i;
					tmp->next = new struct fac_rec;
					//настроились на новую запись
					tmp = tmp->next;
					//инициализация новой записи
					tmp->next = NULL;
				}
				what = what / i;
				pred = i;
				break;
			}
		}
	}
	return rec;
}
//////////////////////////////////////////////////////////////
void Polynomial::kill_factor(fac_rec *what){
	struct fac_rec *tmp, *tmp2;
	tmp = what;
	tmp2 = tmp;
	while(tmp->next != NULL){
		CEuclidDlg::showProgress();
		tmp = tmp2->next;
		delete tmp2;
		tmp2 = tmp;
	}
	delete tmp2;
}
//////////////////////////////////////////////////////////////
int Polynomial::isSimpleB(CProgressCtrl *progress){
	// Проверяет многочлен на неприводимость по критерию
	// Берлекемпа (см. стр 209 "Алгебраическая алгоритмика").

	//сразу вернуть 0, если коэфф при нулевой и старшей степени
	//отсутствуют
	CEuclidDlg::m_What.SetWindowText("Berlekemp's test...");		
	if (Coeff[0].Data==0) return 0;//не простой
	int cnt = 0;//считает простые множители степени
	int ret, i;
	int deg = this->Deg;
	fac_rec *tmp, *rec;
	//факторизация степени
	if (progress) progress->StepIt();
	rec = Polynomial::factor(deg);
	//реализация теста Берлекемпа
	long mod = this->Coeff[0].Module;
	long tst_deg = (long)pow(mod,Deg);//mod^Deg
	Euclid_return *er;//расчет алгоритма Евклида
	Field *tst_poly = new Field[tst_deg + 1];
	for(i=0;i<=tst_deg;i++){
		tst_poly[i].setModule(mod);
	}
	tst_poly[1].setData(1);
	tst_poly[tst_deg].setData(1);
	Polynomial *tst = new Polynomial(tst_deg,tst_poly);
	Div_poly &dp = tst->div(*this);
	ret = 1;//предполагаем поначалу, что он простой
	//сразу не простой многочлен если не разделился нацело
	if((dp.Rem_deg > 0) || (dp.Rem[0].Data != 0)) ret = 0;
	//многочлен, может быть, простой (нацело разделился)
	else{
		//пройти список разложения степени
		tmp = rec;//настоились на начало связного списка
		while(tmp->next != NULL){
			if (progress) progress->StepIt();
			tst_deg = (long)pow(mod,(Deg/tmp->q));//mod^(Deg/q)
			delete [] tst_poly;
			tst_poly = new Field[tst_deg + 1];
			for(i=0;i<=tst_deg;i++){
				tst_poly[i].setModule(mod);
			}
			tst_poly[1].setData(1);
			tst_poly[tst_deg].setData(1);
			tst->set(tst_deg,tst_poly);
			//поищем нод по алг. Евклида
			er = new Euclid_return(*tst,*this);
			//если НОД не равен 1, то не простой
			if((er->Nod->Deg>0)||(er->Nod->Coeff[0].Data!=1)){
				ret = 0;
				break;
			}
			delete er;
			tmp = tmp->next;//настроились на следующий элем списка
		}
	}
	delete [] tst_poly;	
	delete tst;
	//убить связный список
	Polynomial::kill_factor(rec);

	if (!CEuclidDlg::m_NoLog){
		if (ret){
			fprintf(Polynomial::log,"Polynomial (%s) is irreducible\n-----\n", \
				LPCTSTR(this->toString()));
		}else{
			fprintf(Polynomial::log,"Polynomial (%s) is not irreducible\n-----\n", \
				LPCTSTR(this->toString()));
		}
	}
	
	return ret;
}
//////////////////////////////////////////////////////////////
int Polynomial::isSimple(CProgressCtrl *progress){
	/* Реазизует тест на непрводимость Аланена и Кнута.
	 * 1-неприводимый, 0 - otherwise, -1 - прервано
	 * Представлен здесь поскольку тест Берлекемпа 
	 * работает глючно
	 * Число смещений прогресса: Mod+DIV(pow(mod,Deg),Deg)+Deg-1
	 */
	CEuclidDlg::m_What.SetWindowText("Alanen and Knuth test...");
	if(Coeff[0].Data == 0) return 0;//не простой
	int i;
	long mod = Coeff[0].Module;
	//1. проверить, что F(x) != 0 для всех x из простого поля
	for(i=0;i<mod; i++){
		if (progress) progress->StepIt();
		if (0 == (this->calculate(*(new Field(mod,i))).Data)){
			if (!CEuclidDlg::m_NoLog){
				fprintf(Polynomial::log,"Polynomial (%s) is not irredusible\n-----\n", \
					LPCTSTR(this->toString()));
			}
			return 0;
		}
	}
	//2. проверить x^(p^n) = x mod F(x), n=deg F
	char *p1_str = new char[4];
	strcpy(p1_str,"0 1");
	Polynomial p1(p1_str,3,mod);//сконстр х
	delete [] p1_str;
	long tst_deg = (long)pow(mod,Deg);//mod^Deg
	Field *tst_coeff = new Field[tst_deg + 1];
	for(i=0;i<=tst_deg;i++){
		tst_coeff[i].setModule(mod);
	}
	tst_coeff[tst_deg].setData(1);
	Polynomial *tst = new Polynomial(tst_deg,tst_coeff);//сконстр x^(p^n)
	Div_poly &dp = tst->div(*this,progress);
	if (!(p1 == *(new Polynomial(dp.Rem_deg,dp.Rem)))){
		delete [] tst_coeff;
		delete tst;
		if (!CEuclidDlg::m_NoLog){
			fprintf(Polynomial::log,"Polynomial (%s) is not irredusible\n-----\n", \
				LPCTSTR(this->toString()));
		}
		return 0;
	}
	delete [] tst_coeff;
	delete tst;
	
	//3. проверяется что x^(p^m) != x mod F(x) для любого 0<m<n
	int m;
	for(m=1; m < Deg; m++){
		if (progress) progress->StepIt();
		tst_deg = (long)pow(mod,m);//p^m
		Field *tst_coeff = new Field[tst_deg + 1];
		for(i=0;i<=tst_deg;i++){
			tst_coeff[i].setModule(mod);
		}
		tst_coeff[tst_deg].setData(1);
		tst = new Polynomial(tst_deg,tst_coeff);//сконстр x^(p^m)
		Div_poly &dp1 = tst->div(*this);
		if (p1 == *(new Polynomial(dp1.Rem_deg,dp1.Rem))){
			delete [] tst_coeff;
			delete tst;
			if (!CEuclidDlg::m_NoLog){
				fprintf(Polynomial::log,"Polynomial (%s) is not irredusible\n-----\n", \
					LPCTSTR(this->toString()));
			}
			return 0;
		}
		delete [] tst_coeff;
		delete tst;	
	}
	if (progress) progress->StepIt();
	if (!CEuclidDlg::m_NoLog){
		fprintf(Polynomial::log,"Polynomial (%s) is irredusible\n-----\n", \
			LPCTSTR(this->toString()));
	}
	
	return 1;
}
//////////////////////////////////////////////////////////////
Field &Polynomial::calculate(Field &a){
	Field *ret = new Field(this->Coeff[0]);
	int i;
	for (i=1; i<=Deg; i++){
		CEuclidDlg::showProgress();
		*ret = (*ret + (Coeff[i]*a.field_pow(i)));
	}
	if (!CEuclidDlg::m_NoLog){
		fprintf(Polynomial::log,"Polynomial (%s) on %s is %s\n-----\n",
			LPCTSTR(this->toString()),LPCTSTR(a.toString()),LPCTSTR(ret->toString()));
	}
	return *ret;
}
//////////////////////////////////////////////////////////////
int Polynomial::isPrime(CProgressCtrl *progress){
	/* Реазизует тест на примитивность Аланена и Кнута.
	 * 1-примитивный, 0 otherwise
	 * Смещений прогресса: Mod+DIV(pow(mod,Deg),Deg)+sqrt(pow(mod,Deg)-1)
	 */
	if(Coeff[0].Data == 0) return 0;//не простой
	int i;
	long mod = Coeff[0].Module;
	//1. проверить, что F(x) != 0 для всех x из простого поля
	for(i=0;i<mod; i++){
		if (progress) progress->StepIt();
		if (0 == (this->calculate(*(new Field(mod,i))).Data)){
			if (!CEuclidDlg::m_NoLog){
				fprintf(Polynomial::log,"Polynomial (%s) is not prime\n-----\n", \
					LPCTSTR(this->toString()));
			}
			return 0;
		}
	}
	//2. проверить x^(p^n) = x mod F(x), n=deg F
	char *p1_str = new char[4];
	strcpy(p1_str,"0 1");
	Polynomial p1(p1_str,3,mod);//сконстр х
	delete [] p1_str;
	long tst_deg = (long)pow(mod,Deg);//mod^Deg
	Field *tst_coeff = new Field[tst_deg + 1];
	for(i=0;i<=tst_deg;i++){
		tst_coeff[i].setModule(mod);
	}
	tst_coeff[tst_deg].setData(1);
	Polynomial *tst = new Polynomial(tst_deg,tst_coeff);//сконстр x^(p^n)
	Div_poly &dp = tst->div(*this, progress);
	if (!(p1 == *(new Polynomial(dp.Rem_deg,dp.Rem)))){
		delete [] tst_coeff;
		delete tst;
		if (!CEuclidDlg::m_NoLog){
			fprintf(Polynomial::log,"Polynomial (%s) is not prime\n-----\n", \
				LPCTSTR(this->toString()));
		}
		return 0;
	}
	delete [] tst_coeff;
	delete tst;
	//3. проверить, что x^d != d mod F(x), где d=(p^n-1)/p',p'-фактор p
	long pow_mod = (long)pow(mod, Deg); pow_mod -= 1;
	struct fac_rec *rec = Polynomial::factor(pow_mod);
	struct fac_rec *tmp_rec = rec;
	while (tmp_rec->next != NULL){
		if (progress) progress->StepIt();
		long d = pow_mod/tmp_rec->q;
		tst_coeff = new Field[d+1];
		for(i=0;i<=d;i++) tst_coeff[i].setModule(mod);
		tst_coeff[d].setData(1);
		tst = new Polynomial(d,tst_coeff);
		Div_poly &dp1 = tst->div(*this);
		//ppp->del_fict_coeff();
		if ((dp1.Rem_deg == 0)&&((dp1.Rem->Data % mod) == 1)){
			delete [] tst_coeff;
			delete tst;
			Polynomial::kill_factor(rec);
			if (!CEuclidDlg::m_NoLog){
				fprintf(Polynomial::log,"Polynomial (%s) is not prime\n-----\n", \
					LPCTSTR(this->toString()));
			}
			return 0;
		}
		delete [] tst_coeff;
		delete tst;	
		tmp_rec = tmp_rec->next;

	}//while
	Polynomial::kill_factor(rec);

	/* Далее реализован тест на неприводимость, как и тест Берлекемпа
	//проверяется что x^(p^m) != x mod F(x) для любого 0<m<n
	int m;
	for(m=1; m < Deg; m++){
		tst_deg = (long)pow(mod,m);//p^m
		Field *tst_coeff = new Field[tst_deg + 1];
		for(i=0;i<=tst_deg;i++){
			tst_coeff[i].setModule(mod);
		}
		tst_coeff[tst_deg].setData(1);
		tst = new Polynomial(tst_deg,tst_coeff);//сконстр x^(p^m)
		Div_poly &dp1 = tst->div(*this);
		if (p1 == *(new Polynomial(dp1.Rem_deg,dp1.Rem))){
			delete [] tst_coeff;
			delete tst;
			if (!CEuclidDlg::m_NoLog){
				fprintf(Polynomial::log,"Polynomial (%s) is not prime\n-----\n", \
					LPCTSTR(this->toString()));
			}
			return 0;
		}
		delete [] tst_coeff;
		delete tst;	
	}
	*/
	if (!CEuclidDlg::m_NoLog){
		fprintf(Polynomial::log,"Polynomial (%s) is prime\n-----\n", \
			LPCTSTR(this->toString()));
	}
	
	return 1;
}
//////////////////////////////////////////////////////////////
CString Polynomial::toString(BOOL endian){
	CString ret("");
	if (Coeff == NULL)
		ret = " ";
	else{
		if (endian){
			for(int i=Deg; i>=0; i--){
				CEuclidDlg::showProgress();
				ret += Coeff[i].toString();
				ret += " ";
			}
		}else{
			for(int i=0; i<=Deg; i++){
				CEuclidDlg::showProgress();
				ret += Coeff[i].toString();
				ret += " ";
			}
		}
	}
	return ret;
}
//////////////////////////////////////////////////////////////
void Polynomial::endian_hdl(char *str, int len, BOOL big){
	int i, p;
	CString tmp("");
	if (big){
		p = ((str[len-1] == ' ')? 1 : 0);
		for (i=len-1-p; i>=0; i--){
			tmp = tmp+str[i];
		}
		tmp += ' ';
		for(i=0; i<len; i++){
			str[i] = tmp[i];
		}
	}
}
//////////////////////////////////////////////////////////////
//проверяет на наличие в списке недопустимых
BOOL Polynomial::isAdmissible(int deg){
	//целое число допустимо ттогда, когда оно - степень простого
	//числа или произведение двух разных простых.
	long arr[100];
	fac_rec *rec = Polynomial::factor((long)deg);
	fac_rec *tmp = rec;
	int cnt = 0;
	while(tmp->next != NULL){
		arr[cnt++]=tmp->q;
		tmp = tmp->next;
	}
	Polynomial::kill_factor(rec);
	if ((cnt==1)||((cnt==2)&&(arr[0]*arr[1] == (long)deg))) return TRUE;
	else return FALSE;
}
//////////////////////////////////////////////////////////////
Polynomial::~Polynomial(){
	if (was_new) delete [] Coeff;
}
