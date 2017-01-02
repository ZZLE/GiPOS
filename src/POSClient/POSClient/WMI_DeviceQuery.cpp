#include "stdafx.h"
#include "WMI_DeviceQuery.h"
#include <comutil.h>
#include <Wbemidl.h>
#include <Winioctl.h>
#include <tchar.h>
#include <strsafe.h>
#include <algorithm>
#include <atlconv.h>
#include <ntddndis.h>

#pragma comment (lib, "comsuppw.lib")
#pragma comment (lib, "wbemuuid.lib")

typedef struct _T_WQL_QUERY
{
	CHAR*	szSelect;		// SELECT���
	WCHAR*	szProperty;		// �����ֶ�
} T_WQL_QUERY;

// WQL��ѯ���
const T_WQL_QUERY szWQLQuery[] = {
	// ����ԭ��MAC��ַ
	"SELECT * FROM Win32_NetworkAdapter WHERE (MACAddress IS NOT NULL) AND (PNPDeviceID LIKE 'PCI%')",
	L"PNPDeviceID",

	// Ӳ�����к�
	"SELECT * FROM Win32_PhysicalMedia WHERE Tag LIKE '%PHYSICALDRIVE0%'",
	L"SerialNumber",

	// �������к�
	"SELECT * FROM Win32_BaseBoard WHERE (SerialNumber IS NOT NULL)",
	L"SerialNumber",	

	// ������ID
	"SELECT * FROM Win32_Processor WHERE (ProcessorId IS NOT NULL)",
	L"ProcessorId",

	// BIOS���к�
	"SELECT * FROM Win32_BIOS WHERE (SerialNumber IS NOT NULL)",
	L"SerialNumber",

	// �����ͺ�
	"SELECT * FROM Win32_BaseBoard WHERE (Product IS NOT NULL)",
	L"Product",

	// ������ǰMAC��ַ
	"SELECT * FROM Win32_NetworkAdapter WHERE (MACAddress IS NOT NULL) AND (PNPDeviceID LIKE 'PCI%')",
	L"MACAddress",
};

// ͨ����PNPDeviceID����ȡ����ԭ��MAC��ַ
static BOOL WMI_DoWithPNPDeviceID( const TCHAR *PNPDeviceID, TCHAR *MacAddress, UINT uSize )
{
	TCHAR	DevicePath[MAX_PATH];
	HANDLE	hDeviceFile;	
	BOOL	isOK = FALSE;

	// �����豸·����
	StringCchCopy( DevicePath, MAX_PATH, TEXT("\\\\.\\") );
	StringCchCat( DevicePath, MAX_PATH, PNPDeviceID );
	StringCchCat( DevicePath, MAX_PATH, TEXT("#{ad498944-762f-11d0-8dcb-00c04fc3358c}") );

	// ����PNPDeviceID���еġ�\���滻�ɡ�#�����Ի���������豸·����
	std::replace( DevicePath + 4, DevicePath + 4 + _tcslen(PNPDeviceID), TEXT('\\'), TEXT('#') ); 

	// ��ȡ�豸���
	hDeviceFile = CreateFile( DevicePath,
		0,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if( hDeviceFile != INVALID_HANDLE_VALUE )
	{	
		ULONG	dwID;
		BYTE	ucData[8];
		DWORD	dwByteRet;		

		// ��ȡ����ԭ��MAC��ַ
		dwID = OID_802_3_PERMANENT_ADDRESS;
		isOK = DeviceIoControl(hDeviceFile,IOCTL_NDIS_QUERY_GLOBAL_STATS, &dwID, sizeof(dwID), ucData, sizeof(ucData), &dwByteRet, NULL );
		if( isOK )
		{	// ���ֽ�����ת����16�����ַ���
			for( DWORD i = 0; i < dwByteRet; i++ )
			{
				StringCchPrintf( MacAddress + (i << 1), uSize - (i << 1), TEXT("%02X"), ucData[i] );
			}
			MacAddress[dwByteRet<<1] =_T('\0');  // д���ַ����������  
		}

		CloseHandle( hDeviceFile );
	}

	return isOK;
}

static BOOL WMI_DoWithProperty( INT iQueryType, TCHAR *szProperty, UINT uSize )
{
	BOOL isOK = TRUE;

	switch( iQueryType )
	{
	case 0:		// ����ԭ��MAC��ַ		
		isOK = WMI_DoWithPNPDeviceID( szProperty, szProperty, uSize );
		break;

	case 1:		// Ӳ�����к�
		//isOK = WMI_DoWithHarddiskSerialNumber( szProperty, uSize );
		break;

	case 6:		// ������ǰMAC��ַ
		// ȥ��ð��
		std::remove( szProperty, szProperty + _tcslen(szProperty) + 1, L':' );
		break;

	default:
		// ȥ���ո�
		std::remove( szProperty, szProperty + _tcslen(szProperty) + 1, L' ' );
	}

	return isOK;
}

// ����Windows Management Instrumentation��Windows����淶��
INT WMI_DeviceQuery( INT iQueryType, T_DEVICE_PROPERTY *properties, INT iSize )
{
	HRESULT hres;
	INT	iTotal = 0;
	
	// �жϲ�ѯ�����Ƿ�֧��
	if( (iQueryType < 0) || (iQueryType >= sizeof(szWQLQuery)/sizeof(T_WQL_QUERY)) )
	{
		return -1;	// ��ѯ���Ͳ�֧��
	}

    // ��ʼ��COM
    hres = CoInitialize(NULL); 
    if( FAILED(hres) )
    {
        return -2;
    }

    // ����COM�İ�ȫ��֤����
	hres = CoInitializeSecurity(  
		NULL, 
		-1, 
		NULL, 
		NULL, 
		RPC_C_AUTHN_LEVEL_DEFAULT, 
		RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL
		);
	if( FAILED(hres)&&hres!=RPC_E_TOO_LATE)
    {
        CoUninitialize();
        return -3;
    }
    
	// ���WMI����COM�ӿ�
    IWbemLocator *pLoc = NULL;
    hres = CoCreateInstance( 
		CLSID_WbemLocator, 
        NULL, 
        CLSCTX_INPROC_SERVER, 
        IID_IWbemLocator,
		reinterpret_cast<LPVOID*>(&pLoc)
		); 
    if( FAILED(hres) )
    {
		CoUninitialize();
        return -4;
    }

    // ͨ�����ӽӿ�����WMI���ں˶�����"ROOT\\CIMV2"
	IWbemServices *pSvc = NULL;
	hres = pLoc->ConnectServer(
         _bstr_t( L"ROOT\\CIMV2" ),
         NULL,
         NULL,
         NULL,
         0,
         NULL,
         NULL,
         &pSvc
		 );    
    if( FAILED(hres) )
    {
		pLoc->Release(); 
        CoUninitialize();
        return -5;
    }

	// �����������İ�ȫ����
    hres = CoSetProxyBlanket(
		pSvc,
		RPC_C_AUTHN_WINNT,
		RPC_C_AUTHZ_NONE,
		NULL,
		RPC_C_AUTHN_LEVEL_CALL,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL,
		EOAC_NONE
		);
	if( FAILED(hres) )
    {
        pSvc->Release();
        pLoc->Release();     
        CoUninitialize();
        return -6;
    }

    // ͨ�������������WMI��������
    IEnumWbemClassObject *pEnumerator = NULL;
    hres = pSvc->ExecQuery(
		bstr_t("WQL"), 
		bstr_t( szWQLQuery[iQueryType].szSelect ),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
        NULL,
        &pEnumerator
		);
	if( FAILED(hres) )
    {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return -7;
    }
USES_CONVERSION;
    // ѭ��ö�����еĽ������  
    while( pEnumerator )
    {
		IWbemClassObject *pclsObj = NULL;
		ULONG uReturn = 0;

// 		if( (properties != NULL) && (iTotal >= iSize) )
// 		{
// 			break;
// 		}

        pEnumerator->Next(
			WBEM_INFINITE,
			1, 
            &pclsObj,
			&uReturn
			);

        if( uReturn == 0 )
        {
            break;
        }

		if( properties != NULL )
		{	// ��ȡ����ֵ
			VARIANT vtProperty;
			VariantInit( &vtProperty );	
			pclsObj->Get( szWQLQuery[iQueryType].szProperty, 0, &vtProperty, NULL, NULL );
			
			StringCchCopy( properties[iTotal].szProperty, PROPERTY_MAX_LEN, W2T(vtProperty.bstrVal) );
			VariantClear( &vtProperty );

			// ������ֵ����һ���Ĵ���
			if( WMI_DoWithProperty( iQueryType, properties[iTotal].szProperty, PROPERTY_MAX_LEN ) )
			{
				iTotal++;
			}
		}
		else
		{
			iTotal++;
		}

		pclsObj->Release();
    } // End While

    // �ͷ���Դ
	pEnumerator->Release();
    pSvc->Release();
    pLoc->Release();    
    CoUninitialize();

    return iTotal;
}
