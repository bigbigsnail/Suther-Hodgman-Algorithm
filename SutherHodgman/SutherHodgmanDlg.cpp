
// SutherHodgmanDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SutherHodgman.h"
#include "SutherHodgmanDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool RightClick, LeftDoubleClick;//�ж�������Ҽ��Ƿ���, �����Ƿ�պ�
CPoint m_StartNode, m_EndNode;//���ƴ��ڹ��������ϽǺ����½���������
CPoint RectTopLeft, RectTopRight, RectBottomLeft, RectBottomRight; //�����ĸ�����
CPoint Points[100], CutPoint1[100], CutPoint2[100], CutPoint3[100], CutPoint4[100];//�洢����εĵ���Ѵ���ĵ�
int NumberOfPoints = 0;
int NumCutPoints = 0;//�ü��������Ѵ��ڵĵ���

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSutherHodgmanDlg �Ի���



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


// CSutherHodgmanDlg ��Ϣ�������

BOOL CSutherHodgmanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSutherHodgmanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSutherHodgmanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//���������£���ȡ��ȡһ������εĵ㣬����������
//����ļ�������������ͬʱ����OnPaint����������
void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!LeftDoubleClick)
	{
		Points[NumberOfPoints] = point;
		NumberOfPoints++;
		OnPaint();
		Invalidate(FALSE);
	}
	else
	{
		MessageBox(_T("������Ѿ��պ�"));
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CSutherHodgmanDlg::OnBnClickedButton1()//�պϰ�ť
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	LeftDoubleClick = true;
	OnPaint();
	Invalidate(FALSE);
}




void CAboutDlg::OnRButtonDown(UINT nFlags, CPoint point)//����Ҽ���ס����׽�ƶ����Ķ���
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_StartNode = point;
	m_EndNode = point;
	RightClick = true;
	SetCapture();
	
	CDialogEx::OnRButtonDown(nFlags, point);
}



void CAboutDlg::OnRButtonUp(UINT nFlags, CPoint point)//����Ҽ��ɿ��ͷŶ�����׽
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (this == GetCapture())
	{
		ReleaseCapture();
	}
	RightClick = false;

	CDialogEx::OnRButtonUp(nFlags, point);
}


void CAboutDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}



void CSutherHodgmanDlg::OnBnClickedButton3()//�����ͼ����
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	LeftDoubleClick = false;
	RightClick = false;
	NumberOfPoints = 0;
	Invalidate(FALSE);
}


void CSutherHodgmanDlg::OnBnClickedButton2()//�ü������
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	POINT p1, p2, p3, p4, p;

	//��ü�
	p3 = RectTopLeft;
	p4 = RectBottomLeft;
	NumCutPoints = 0;
	for (int i = 0; i < NumberOfPoints; i++)
	{
		//������ʼ�߶�
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

		//�ж��Ƿ�ֱ
		if (p1.x == p2.x)
		{
			if (p1.x > p3.x)//�ѽ�������������
			{
				CutPoint1[NumCutPoints++] = p2;
			}
		}
		else//ͨ��б�ʼ����ӳ��߽���
		{
			int x = p3.x;
			int y = p2.y - (double)(p2.y - p1.y)*(double)(p2.x - x) / (double)(p2.x - p1.x);
			
			//�н���
			if (y > min(p1.y, p2.y) && y < max(p1.y, p2.y))
			{
				p.x = x;
				p.y = y;
				CutPoint1[NumCutPoints++] = p;
			}

			//�������ڻ��ߴ��ڵ���
			if (p2.x > p3.x)
			{
				CutPoint1[NumCutPoints++] = p2;
			}
		}
	}

	//�Ҳü�
	p3 = RectTopRight;
	p4 = RectBottomRight;
	NumberOfPoints = NumCutPoints;
	NumCutPoints = 0;
	for (int i = 0; i < NumberOfPoints; i++)
	{
		//�����߶���ʼ��
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
		//�жϴ�ֱ
		if (p1.x == p2.x)
		{
			if (p1.x<p3.x)
				CutPoint2[NumCutPoints++] = p2;
		}
		else
		{
			int x = p3.x;
			int y = p2.y - (double)(p2.y - p1.y)*(double)(p2.x - x) / (double)(p2.x - p1.x);
			//�н���
			if (y > min(p1.y, p2.y) && y < max(p1.y, p2.y))
			{
				p.x = x;
				p.y = y;
				CutPoint2[NumCutPoints++] = p;
			}
			if (p2.x < p3.x)//�������ڻ���ڵ���
			{
				CutPoint2[NumCutPoints++] = p2;
			}
		}
	}

	//�²ü�
	p3 = RectBottomLeft;
	p4 = RectBottomRight;
	NumberOfPoints = NumCutPoints;
	NumCutPoints = 0;
	for (int i = 0; i < NumberOfPoints; i++)
	{
		//�����߶���ʼ��
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

		//�ж�ƽ��
		if (p1.y == p2.y)//���ڵ���
		{
			if (p1.y<p3.y)
				CutPoint3[NumCutPoints++] = p2;
		}
		else
		{
			if (p1.x == p2.x)//��ֱֱ�Ӽ��㽻��
			{
				if (p3.y>min(p1.y, p2.y) && p3.y<max(p1.y, p2.y))//��������
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

			//��������
			if (p2.y < p3.y)
			{
				CutPoint3[NumCutPoints++] = p2;
			}
		}
	}

	//�ϲü�
	p3 = RectTopLeft;
	p4 = RectTopRight;
	NumberOfPoints = NumCutPoints;
	NumCutPoints = 0;
	for (int i = 0; i < NumberOfPoints; i++)
	{
		//�����߶���ʼ��
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

		//�ж�ƽ��
		if (p1.y == p2.y)
		{
			//���ڵ���
			if (p1.y>p3.y)
				CutPoint4[NumCutPoints++] = p2;
		}
		else
		{
			if (p1.x == p2.x)
			{
				//��ֱֱ�Ӽ��㽻��
				if (p3.y>min(p1.y, p2.y) && p3.y<max(p1.y, p2.y))
				{
					//��������
					p.x = p1.x;
					p.y = p3.y;
					CutPoint4[NumCutPoints++] = p;
				}
			}
			else
			{
				//�󽻵�
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
				//��������
				CutPoint4[NumCutPoints++] = p2;
			}
		}
	}

	//��ʼ����
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