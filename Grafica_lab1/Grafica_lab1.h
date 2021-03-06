
// Grafica_lab1.h: основной файл заголовка для приложения Grafica_lab1
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CGraficalab1App:
// Сведения о реализации этого класса: Grafica_lab1.cpp
//

class CGraficalab1App : public CWinAppEx
{
public:
	CGraficalab1App() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraficalab1App theApp;
