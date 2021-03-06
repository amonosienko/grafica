
// Grafica_lab1View.cpp: реализация класса CGraficalab1View
//

#include "stdafx.h"
#include "math.h"
#include <iostream>
#include <fstream>
#include "stdio.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Grafica_lab1.h"
#endif

#include "Grafica_lab1Doc.h"
#include "Grafica_lab1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
// CGraficalab1View

IMPLEMENT_DYNCREATE(CGraficalab1View, CView)

BEGIN_MESSAGE_MAP(CGraficalab1View, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraficalab1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CGraficalab1View

CGraficalab1View::CGraficalab1View() noexcept
{
	// TODO: добавьте код создания

}

CGraficalab1View::~CGraficalab1View()
{
}

BOOL CGraficalab1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CGraficalab1View
// Создаем собственную функцию

long double my_function(long double x, long double e)
{
	int temp = 1;
	long double numerator = pow((x - 1), 2);
	long double denominator = pow((x + 1), 2);
	long double previous = (x - 1) / (x + 1);
	long double sum = previous;

	for (int k = 2; e < fabs(previous); k++)
	{
		temp += 2;
		previous *= numerator / denominator;
		sum += previous;
	}

	return sum;

	 
	/*double previous = (x - 1) / (x + 1);
	double sum = previous;
	double current = pow(x - 1, 3) / (3 * pow(x + 1, 3));
	sum += current;
	for (int k = 3; fabs(current - previous) > e; k++)
	{
		previous = current;
		current = pow(x - 1, 2 * k - 1) / ((2 * k - 1) * pow(x + 1, 2 * k - 1));
		sum += current;
	}
	return sum;*/


}

void CGraficalab1View::OnDraw(CDC* pDC)
{
	CGraficalab1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	ofstream file1("file1.txt");
	ofstream file2("file2.txt");

	long double a = 0.1, b = 20;
	long double eps = 0.000001; //эпсилон
	int nsegm = 300; //сегмент для шага
	long double scalex = 80.0, scaley = 100.0;
	long double x, y, z;
	long double step; //шаг
	//step = 0.025;
	step = (b - a) / nsegm;
	// создаем перо для координатных осей
	CPen penAxe(PS_SOLID, 2, RGB(0, 0, 255));
	// создаем перо для рисования графика
	CPen penSin(PS_SOLID, 1, RGB(255, 0, 0));
	// сохраняем адрес старого пера (стандартного для windows)
	CPen *pOldPen = NULL;
	// создаем пустой прямоугольник (область рисования)
	CRect rcClient;
	// подключаемся ОС windows записывая параметры рабочей зоны в объект
	GetClientRect(&rcClient);
	// рисуем оси
	pOldPen = pDC->SelectObject(&penAxe);
	pDC->MoveTo(0, rcClient.CenterPoint().y);
	pDC->LineTo(rcClient.Width(), rcClient.CenterPoint().y);
	pDC->LineTo(rcClient.Width() - 8, rcClient.CenterPoint().y - 8);
	pDC->MoveTo(rcClient.Width(), rcClient.CenterPoint().y);
	pDC->LineTo(rcClient.Width() - 8, rcClient.CenterPoint().y + 8);
	pDC->MoveTo(rcClient.CenterPoint().x, 0);
	pDC->LineTo(rcClient.CenterPoint().x - 8, 8);
	pDC->MoveTo(rcClient.CenterPoint().x, 0);
	pDC->LineTo(rcClient.CenterPoint().x + 8, 8);
	pDC->MoveTo(rcClient.CenterPoint().x, 0);
	pDC->LineTo(rcClient.CenterPoint().x, rcClient.Height());
	pDC->SelectObject(&penSin);

	// рисуем график собственной функции
	x = a;
	y = my_function(x, eps);
	file1 << x << " " << y << " " << log(x) << endl;
	file2 << x << " " << y << endl;
	pDC->MoveTo(rcClient.CenterPoint().x + (int)(x * scalex), rcClient.CenterPoint().y -
		(int)(y * scaley));
	for (int i = 1; i <= nsegm; i++)
	{
		z = my_function(x, eps);
		x += step;
		y = my_function(x, eps);
		double ln = log(x);
		file1 << x << " " << y << " " << log(x) << " " << y - z << endl;
		file2 << x << " " << y << endl;
		pDC->LineTo(rcClient.CenterPoint().x + (int)(x*scalex), rcClient.CenterPoint().y -
			(int)(y*scaley));
	}
	// установим имя собственной функции в правом верхнем углу
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->SetTextAlign(TA_TOP + TA_RIGHT);
	//pDC -> TextOut(rcClient.Width() - 1, 0, " y = funtie(x, e)");
	// рисуем стандартную функцию log(x)
	step = 0.025;
	for (x = a; x <= b; x += step)
	{
		y = log(x);
		pDC->SetPixel(rcClient.CenterPoint().x + (int)(x*scalex) + 1, rcClient.CenterPoint().y -
			(int)(y*scaley) + 1, RGB(0, 255, 0));

	}
	// установим в правом нижнем углу название стандартной функции
	pDC->SetTextColor(RGB(0, 255, 0));
	pDC->SetTextAlign(TA_BOTTOM + TA_RIGHT);
	//pDC->TextOut(rcClient.Width() - 1, rcClient.Height() - 1, " y = sin(x) / x");


	file1.close();
	file2.close();

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CGraficalab1View


void CGraficalab1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraficalab1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CGraficalab1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CGraficalab1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CGraficalab1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraficalab1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CGraficalab1View

#ifdef _DEBUG
void CGraficalab1View::AssertValid() const
{
	CView::AssertValid();
}

void CGraficalab1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraficalab1Doc* CGraficalab1View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraficalab1Doc)));
	return (CGraficalab1Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CGraficalab1View
