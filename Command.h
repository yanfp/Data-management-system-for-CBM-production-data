#ifndef YXB_CCOMMAND_H_H
#define YXB_CCOMMAND_H_H

////////////////////////////////////////////////////////////////////////////////////////////////////
// include flies                                                                                  //      
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <afx.h>
#include "AdoConst.h"

#include "Connection.h"
#include "Recordset.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace ADOCONST;

class CCommand  
{
private:
	_CommandPtr m_pCmd;
    CString m_sErrorMessage;

public:
	CCommand();
	virtual ~CCommand();


////////////////////////////////////////////////////////////////////////////////////////////////////
// Property Get/Set Method                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	//Property: ActiveConnection
	void SetActiveConnection(CConnection &ActiveConn);
	
    //Property: CommandText
	void SetCommandText(CString strCmd);
	
	//Property: CommandTimeout
	void SetCommandTimeout(long time);
	
	//Property: CommandType
	//void SetCommandType(CommandTypeEnum CommandType);

	//Property: State
    ObjectStateEnum GetState() const;


////////////////////////////////////////////////////////////////////////////////////////////////////
// Other Method                                                                                   //
////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	bool ExecuteQuery(CommandTypeEnum CommandType,CRecordset &Rst);
	bool ExecuteUpdate(long &AffectedRows,CommandTypeEnum CommandType,CRecordset &Rst);
	void Release();
	bool Cancel();
};

#endif //#ifndef YXB_COMMAND_H_H
