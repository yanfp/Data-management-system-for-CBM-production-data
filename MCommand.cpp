#include "stdafx.h"
#include "MCommand.h"
using namespace ADOCONST;


////////////////////////////////////////////////////////////////////////////////////////////////////
// Construction/Destruction                                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

MCommand::MCommand()
{
   CoInitialize(NULL);  
   m_pCmd.CreateInstance("ADODB.Command");
   //m_pCmd.CreateInstance(__uuidof(Command));

   //default set

}

MCommand::~MCommand()
{
	Release();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Property Get/Set Method                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////

//Property: ActiveConnection
void MCommand::SetActiveConnection(MConnection &ActiveConn)
{
	m_pCmd->PutActiveConnection(ActiveConn.GetConnection().GetInterfacePtr());
}

//Property: CommandText
void MCommand::SetCommandText(CString strCmd)
{
    m_pCmd->PutCommandText(_bstr_t(strCmd));
}

//Property: CommandTimeout
void MCommand::SetCommandTimeout(long time)
{
	m_pCmd->PutCommandTimeout(time);
}

//Property: State
ObjectStateEnum MCommand::GetState() const
{
	return (ObjectStateEnum)(m_pCmd->GetState());
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Core Method                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////

//ExecuteQuery
bool MCommand::ExecuteQuery(CommandTypeEnum CommandType,MRecordset &Rst)
{
    Rst.m_pRst=m_pCmd->Execute(NULL,NULL,CommandType);
	return true;	
}

//ExecuteUpdate
bool MCommand::ExecuteUpdate(long &AffectedRows,CommandTypeEnum CommandType,MRecordset &Rst)
{	
	VARIANT rows; 
    rows.vt = VT_I4; 
    Rst.m_pRst=m_pCmd->Execute(&rows,NULL,CommandType);
	AffectedRows=rows.lVal ;
	return true;		
}

//Release
void MCommand::Release()
{
	if(m_pCmd!=NULL)
	{
		try
		{
			m_pCmd.Release();
			m_pCmd=NULL;
		}
		catch(_com_error e)
		{
            throw e;
		}
	}
}

//Cancel
bool MCommand::Cancel()
{
	if(m_pCmd==NULL)
	{
		//m_sErrorMessage
        m_sErrorMessage=L"Command is not available!";
		return false;
	}
	
	try
	{
		HRESULT hRsut=m_pCmd->Cancel();
		if(SUCCEEDED(hRsut))
		{
			return true;
		}
		else
		{
			//m_sErrorMessage
			m_sErrorMessage=L"Failed to cancel!";
			return false;
		}
	}
	catch(_com_error e)
	{
		//m_sErrorMessage
		m_sErrorMessage=L"There is an error when called then function: Cancel()!";
		return false;	
	}
}