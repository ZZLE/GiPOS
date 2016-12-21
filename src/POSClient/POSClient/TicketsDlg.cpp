// DiscountDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "POSClient.h"
#include "TicketsDlg.h"
#include "OrderDlg.h"
#include "NumberInputDlg.h"


// DiscountDlg �Ի���

IMPLEMENT_DYNAMIC(TicketsDlg, CDialog)

TicketsDlg::TicketsDlg(CWnd* pParent /*=NULL*/)
: CDialog(TicketsDlg::IDD, pParent)
{
	ITEM_COLUMNSIZE=4;
	ITEM_LINESIZE=8;
	m_fTax=0;
	pParentWnd=NULL;
}

TicketsDlg::~TicketsDlg()
{
	for (CPbuttonIter iter = m_itemButtons.begin(); iter!= m_itemButtons.end();iter++)
	{
		CRoundButton2 *b = (*iter);
		b->DestroyWindow();
		delete b;
	}
	m_itemButtons.clear();
	delete m_bpButtonItem[0];
	delete m_bpButtonItem[1];
}

void TicketsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DISCOUNT, m_editDiscount);
	DDX_Control(pDX, IDC_BUTTON_PREPAGE, m_btnPrepage);
}


BEGIN_MESSAGE_MAP(TicketsDlg, CDialog)
	ON_COMMAND_RANGE(IDC_DYNAMIC_CTRL,IDC_DYNAMIC_CTRL+MAX_ITEMS,OnItemBnClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREPAGE, &TicketsDlg::OnBnClickedButtonPre)
END_MESSAGE_MAP()


// DiscountDlg ��Ϣ�������

BOOL TicketsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	int x=(int)(CreatButton::m_nFullWidth*0.356);
	CRect rect;
	CString str2;
	if(pParentWnd==NULL)
		pParentWnd= GetParent();
	pParentWnd->GetClientRect(&rect);
	pParentWnd->ClientToScreen(&rect);
	MoveWindow(rect.left+x,rect.top+15,(int)(CreatButton::m_nFullWidth*0.635),CreatButton::m_nFullHeight-30);
	int width=(int)(CreatButton::m_nFullWidth*0.4);
	m_editDiscount.MoveWindow(0,0,(int)(CreatButton::m_nFullWidth*0.45),CreatButton::m_nFullHeight/10);
	{
		theLang.LoadString(str2,IDS_COUPON);
		m_editDiscount.SetWindowText(str2);
	}
	m_btnPrepage.MoveWindow((int)(CreatButton::m_nFullWidth*0.45),0,(int)(CreatButton::m_nFullWidth*0.18),CreatButton::m_nFullHeight/10);
	theLang.LoadString(str2,IDS_PREPAGE);
	m_btnPrepage.SetWindowText(str2);
	m_btnPrepage.SetImage(_T("Picture\\class\\prepage_.png"));
	
	m_bpButtonItem[0]=Gdiplus::Image::FromFile(_T("Picture\\class\\class2.png"));
	m_bpButtonItem[1]=Gdiplus::Image::FromFile(_T("Picture\\class\\class2_.png"));
	CreatButtons();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void TicketsDlg::CreatButtons()
{
	try{
		//��ȡλ��
		CRect   rect;
		GetWindowRect(rect);
		ScreenToClient(&rect);
		rect.top=CreatButton::m_nFullHeight/10;
		SIZE buttonSize;
		buttonSize.cx=(rect.right-rect.left)/ITEM_COLUMNSIZE;
		buttonSize.cy=(rect.bottom-rect.top)/ITEM_LINESIZE;
		OpenDatabase();
		CRecordset rs( &theDB);
		CString strSQL,strName,strId;
		strSQL.Format(_T("SELECT * FROM tickets WHERE ticket_id IN(SELECT ticket_id FROM ticket_relation);"));
		
		rs.Open( CRecordset::forwardOnly,strSQL);
		for(int i=0;i<ITEM_LINESIZE;i++)
		{
			POINT topleft;
			topleft.y=rect.top+i*buttonSize.cy;
			for(int j=0;j<ITEM_COLUMNSIZE;j++)
			{
				if (rs.IsEOF())
					return;
				int count=i*ITEM_COLUMNSIZE+j;
				topleft.x=rect.left+j*buttonSize.cx;
				TicketItem item={0};
				rs.GetFieldValue(_T("ticket_name"),item.name);
				rs.GetFieldValue(_T("short_name"),item.display_name);
				CRoundButton2* pBtn = new CRoundButton2;
				pBtn->Create(item.name,WS_CHILD|WS_VISIBLE ,CRect(topleft,buttonSize),this,IDC_DYNAMIC_CTRL+count);
				pBtn->SetImages(m_bpButtonItem[0],m_bpButtonItem[1],false);
				pBtn->SetTextColor(DEFALUT_TXT_COLOR);
				m_itemButtons.push_back(pBtn);

				CDBVariant variant;
				variant.m_iVal=0;
				rs.GetFieldValue(_T("ticket_id"), variant);
				item.id=variant.m_lVal;
				CString strVal;
				rs.GetFieldValue(_T("amount"), strVal);
				item.amount=_wtof(strVal);

				m_Items.push_back(item);
				rs.MoveNext();
			}
		}
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
		return;
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
void TicketsDlg::OnItemBnClicked(UINT uID)
{
	try{
		int index=(uID-IDC_DYNAMIC_CTRL);
		selectedItem=m_Items[index];
		//�������ȯʵ���ܵ��õĽ��
		POSITION pos=NULL;
		double total=0;
		CString strSQL;
		CRecordset rs( &theDB);
		for(pos=theApp.m_orderList.GetHeadPosition();pos!=NULL;)
		{
			OrderDetail* item=theApp.m_orderList.GetNext(pos);
			//�۳����Ѿ�ʹ�õĴ���ȯ
			if (item->item_id==ITEM_ID_PAYINFO)
			{
				strSQL.Format(_T("SELECT ticket_id,total FROM payment WHERE order_detail_id=%d"),item->order_id);
				if(rs.Open(CRecordset::forwardOnly,strSQL))
				{
					if (!rs.IsEOF())
					{//����û�м�¼
						CDBVariant variant;
						CString strVal;
						rs.GetFieldValue(_T("total"), strVal);
						double amount=_wtof(strVal);
						rs.GetFieldValue(_T("ticket_id"), variant);
						rs.Close();
						//�뵱ǰ��ȯ��ͬһ��?
						if (variant.m_lVal==selectedItem.id)
						{
							total-=amount;
						}
						else
						{
							strSQL.Format(_T("SELECT ticket_class_id FROM ticket_relation WHERE (ticket_id=%d OR ticket_id=%d) GROUP BY ticket_class_id HAVING count(ticket_class_id)>=2;")
								,variant.m_lVal,selectedItem.id);
							rs.Open(CRecordset::forwardOnly,strSQL);
							if (rs.GetRecordCount()>0)
								total-=amount;
						}
						if (total<0)
						{
							total=0;
						}
					}
				}
				rs.Close();
			}
			//�ǲ�Ʒ����ʾ
			if (item->item_id<=0)
				continue;
			strSQL.Format(_T("SELECT ticket_id FROM ticket_relation WHERE ticket_class_id IN(SELECT ticket_class FROM menu_item WHERE item_id=%d) AND ticket_id=%d;")
				,item->item_id,selectedItem.id);
			if(rs.Open(CRecordset::forwardOnly,strSQL))
			{
				if (rs.GetRecordCount()>0)
				{//�ò�Ʒ��ʹ�ô���ȯ
					total+=item->total_price;
				}
			}
			rs.Close();
		}
		total+=m_fTax;
		//���¿��õĽ��
		if (total<selectedItem.amount)
		{
			selectedItem.amount=total;
		}
		CDialog::OnOK();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
void TicketsDlg::OnBnClickedButtonPre()
{
	CDialog::OnCancel();
}
