
// SutherHodgmanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SutherHodgman.h"
#include "SutherHodgmanDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool RightClick, LeftDoubleClick;//判断鼠标左右键是否按下, 矩形是否闭合
CPoint m_StartNode, m_EndNode;//绘制窗口过程中左上角和右下角两个顶点
CPoint RectTopLeft, RectTopRight, RectBottomLeft, RectBottomRight; //窗口四个顶点
CPoint Points[100], CutPoint1[100], CutPoint2[100], CutPoint3[100], CutPoint4[100];//存储多边形的点和已处理的点
int NumberOfPoints = 0;
int NumCutPoints = 0;//裁剪队列中已存在的点数

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CSutherHodgmanDlg 对话框



CSutherHodgmanDlg::CSutherHodgmanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSutherHodgmanDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSutherHodgmanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSutherHodgmanDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON1, &CSutherHodgmanDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CSutherHodgmanDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CSutherHodgmanDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSutherHodgmanDlg 消息处理程序

BOOL CSutherHodgmanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSutherHodgmanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSutherHodgmanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC pDC(this);
		
		CRect Rectangle;
		GetClientRect(&Rectangle);
		CBrush myBrush(RGB(255, 255, 255));
		pDC.FillRect(&Rectangle, &myBrush);

		pDC.MoveTo(Points[0].x, Points[0].y);
		for (int i = 0; i < NumberOfPoints; i++)
		{
			pDC.LineTo(Points[i].x, Points[i].y);
		}

		if (LeftDoubleClick)
		{
			pDC.LineTo(Points[0].x, Points[0].y);
		}
		if (RightClick)
		{
			CRect rect(m_StartNode, m_EndNode);
			rect.NormalizeRect();
			CBrush myBrush(RGB(0, 0, 255));
			pDC.FrameRect(&rect, &myBrush);
		}

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSutherHodgmanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//鼠标左键按下，获取获取一个多边形的点，存入数组中
//若点的计数超过两个则同时调用OnPaint函数画出来
void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!LeftDoubleClick)
	{
		Points[NumberOfPoints] = point;
		NumberOfPoints++;
		OnPaint();
		Invalidate(FALSE);
	}
	else
	{
		MessageBox(_T("多边形已经闭合"));
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CSutherHodgmanDlg::OnBnClickedButton1()//闭合按钮
{
	// TODO:  在此添加控件通知处理程序代码
	LeftDoubleClick = true;
	OnPaint();
	Invalidate(FALSE);
}




void CAboutDlg::OnRButtonDown(UINT nFlags, CPoint point)//鼠标右键按住并捕捉移动鼠标的动作
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_StartNode = point;
	m_EndNode = point;
	RightClick = true;
	SetCapture();
	
	CDialogEx::OnRButtonDown(nFlags, point);
}



void CAboutDlg::OnRButtonUp(UINT nFlags, CPoint point)//鼠标右键松开释放动作捕捉
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (this == GetCapture())
	{
		ReleaseCapture();
	}
	RightClick = false;

	CDialogEx::OnRButtonUp(nFlags, point);
}


void CAboutDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (RightClick)
	{
		m_EndNode = point;
		Invalidate(FALSE);
	}

	RectTopLeft = CPoint(m_StartNode.x, m_StartNode.y);
	RectTopRight = CPoint(m_EndNode.x, m_StartNode.y);
	RectBottomLeft = CPoint(m_StartNode.x, m_EndNode.y);
	RectBottomRight = CPoint(m_EndNode.x, m_EndNode.y);

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CAboutDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}



void CSutherHodgmanDlg::OnBnClickedButton3()//清除绘图区域
{
	// TODO:  在此添加控件通知处理程序代码
	LeftDoubleClick = false;
	RightClick = false;
	NumberOfPoints = 0;
	Invalidate(FALSE);
}


void CSutherHodgmanDlg::OnBnClickedButton2()//裁剪多边形
{
	// TODO:  在此添加控件通知处理程序代码
	POINT p1, p2, p3, p4, p;

	//左裁剪
	p3 = RectTopLeft;
	p4 = RectBottomLeft;
	NumCutPoints = 0;
	for (int i = 0; i < NumberOfPoints; i++)
	{
		//设置起始线段
		if (i < NumberOfPoints - 1)
		{
			p1 = Points[i];
			p2 = Points[i + 1];
		}
		else if (i == NumberOfPoints - 1)
		{
			p1 = Points[i];
			p2 = Points[0];
		}

		//判断是否垂直
		if (p1.x == p2.x)
		{
			if (p1.x > p3.x)//把焦点加入输出序列
			{
				CutPoint1[NumCutPoints++] = p2;
			}
		}
		else//通过斜率计算延长线交点
		{
			int x = p3.x;
			int y = p2.y - (double)(p2.y - p1.y)*(double)(p2.x - x) / (double)(p2.x - p1.x);
			
			//有交点
			if (y > min(p1.y, p2.y) && y < max(p1.y, p2.y))
			{
				p.x = x;
				p.y = y;
				CutPoint1[NumCutPoints++] = p;
			}

			//从外向内或者从内到内
			if (p2.x > p3.x)
			{
				CutPoint1[NumCutPoints++] = p2;
			}
		}
	}

	//右裁剪
	p3 = RectTopRight;
	p4 = RectBottomRight;
	NumberOfPoints = NumCutPoints;
	NumCutPoints = 0;
	for (int i = 0; i < NumberOfPoints; i++)
	{
		//设置线段起始点
		if (i < NumberOfPoints - 1)
		{
			p1 = CutPoint1[i];
			p2 = CutPoint1[i + 1];
		}
		else if (i == NumberOfPoints - 1)
		{
			p1 = CutPoint1[i];
			p2 = CutPoint1[0];
		}
		//判断垂直
		if (p1.x == p2.x)
		{
			if (p1.x<p3.x)
				CutPoint2[NumCutPoints++] = p2;
		}
		else
		{
			int x = p3.x;
			int y = p2.y - (double)(p2.y - p1.y)*(double)(p2.x - x) / (double)(p2.x - p1.x);
			//有交点
			if (y > min(p1.y, p2.y) && y < max(p1.y, p2.y))
			{
				p.x = x;
				p.y = y;
				CutPoint2[NumCutPoints++] = p;
			}
			if (p2.x < p3.x)//从外向内或从内到内
			{
				CutPoint2[NumCutPoints++] = p2;
			}
		}
	}

	//下裁剪
	p3 = RectBottomLeft;
	p4 = RectBottomRight;
	NumberOfPoints = NumCutPoints;
	NumCutPoints = 0;
	for (int i = 0; i < NumberOfPoints; i++)
	{
		//设置线段起始点
		if (i < NumberOfPoints - 1)
		{
			p1 = CutPoint2[i];
			p2 = CutPoint2[i + 1];
		}
		else if (i == NumberOfPoints - 1)
		{
			p1 = CutPoint2[i];
			p2 = CutPoint2[0];
		}

		//判断平行
		if (p1.y == p2.y)//从内到内
		{
			if (p1.y<p3.y)
				CutPoint3[NumCutPoints++] = p2;
		}
		else
		{
			if (p1.x == p2.x)//垂直直接计算交点
			{
				if (p3.y>min(p1.y, p2.y) && p3.y<max(p1.y, p2.y))//从外向内
				{
					p.x = p1.x;
					p.y = p3.y;
					CutPoint3[NumCutPoints++] = p;
				}
			}
			else
			{
				int y = p3.y;
				int x = p2.x - (double)(p2.y - y)*(double)(p2.x - p1.x) / (double)(p2.y - p1.y);
				if (x > min(p1.x, p2.x) && x < max(p1.x, p2.x))
				{
					p.x = x;
					p.y = y;
					CutPoint3[NumCutPoints++] = p;
				}
			}

			//从外向内
			if (p2.y < p3.y)
			{
				CutPoint3[NumCutPoints++] = p2;
			}
		}
	}

	//上裁剪
	p3 = RectTopLeft;
	p4 = RectTopRight;
	NumberOfPoints = NumCutPoints;
	NumCutPoints = 0;
	for (int i = 0; i < NumberOfPoints; i++)
	{
		//设置线段起始点
		if (i < NumberOfPoints - 1)
		{
			p1 = CutPoint3[i];
			p2 = CutPoint3[i + 1];
		}
		else if (i == NumberOfPoints - 1)
		{
			p1 = CutPoint3[i];
			p2 = CutPoint3[0];
		}

		//判断平行
		if (p1.y == p2.y)
		{
			//从内到内
			if (p1.y>p3.y)
				CutPoint4[NumCutPoints++] = p2;
		}
		else
		{
			if (p1.x == p2.x)
			{
				//垂直直接计算交点
				if (p3.y>min(p1.y, p2.y) && p3.y<max(p1.y, p2.y))
				{
					//从外向内
					p.x = p1.x;
					p.y = p3.y;
					CutPoint4[NumCutPoints++] = p;
				}
			}
			else
			{
				//求交点
				int y = p3.y;
				int x = p2.x - (double)(p2.y - y)*(double)(p2.x - p1.x) / (double)(p2.y - p1.y);
				if (x > min(p1.x, p2.x) && x < max(p1.x, p2.x))
				{
					p.x = x;
					p.y = y;
					CutPoint4[NumCutPoints++] = p;
				}
			}

			if (p2.y > p3.y)
			{
				//从外向内
				CutPoint4[NumCutPoints++] = p2;
			}
		}
	}

	//开始绘制
	CClientDC dc(this);
	CPen pen(0, 2, RGB(45, 175, 233));
	dc.SelectObject(&pen);
	for (int i = 0; i < NumCutPoints - 1; i++)
	{
		dc.MoveTo(CutPoint4[i]);
		dc.LineTo(CutPoint4[i + 1]);
	}
	dc.MoveTo(CutPoint4[NumCutPoints - 1]);
	dc.LineTo(CutPoint4[0]);
}