
// Grafica_lab1View.h: интерфейс класса CGraficalab1View
//

#pragma once


class CGraficalab1View : public CView
{
protected: // создать только из сериализации
	CGraficalab1View() noexcept;
	DECLARE_DYNCREATE(CGraficalab1View)

// Атрибуты
public:
	CGraficalab1Doc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CGraficalab1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в Grafica_lab1View.cpp
inline CGraficalab1Doc* CGraficalab1View::GetDocument() const
   { return reinterpret_cast<CGraficalab1Doc*>(m_pDocument); }
#endif

