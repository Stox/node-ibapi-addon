#include <cstring>
#include <sstream>
#include <node.h>
#include "NodeIbapi.h"
#include "import/Contract.h"
#include "import/Order.h"
#include "import/Execution.h"
#include "import/ScannerSubscription.h"

using namespace v8;

NodeIbapi::NodeIbapi() {
};
NodeIbapi::~NodeIbapi() {
};

void NodeIbapi::Init( Handle<Object> exports ) {
    // Prep constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New( New );
    tpl->SetClassName( String::NewSymbol( "NodeIbapi" ) );
    tpl->InstanceTemplate()->SetInternalFieldCount( 1 );

    // prototype
    // TODO need to write test, not sure what would be a good one..a
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "processMsg" ),
        FunctionTemplate::New( ProcessMsg )->GetFunction() );
    /// getters
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getTickPrice" ), 
        FunctionTemplate::New( TickPrice )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getTickSize" ), 
        FunctionTemplate::New( TickSize )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getTickOptionComputation" ), 
        FunctionTemplate::New( TickOptionComputation )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getTickGeneric" ), 
        FunctionTemplate::New( TickGeneric )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getTickString" ), 
        FunctionTemplate::New( TickString )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getTickEFP" ), 
        FunctionTemplate::New( TickEFP )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getOrderStatus" ), 
        FunctionTemplate::New( OrderStatus )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getOpenOrder" ), 
        FunctionTemplate::New( OpenOrder )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getOpenOrderEnd" ), 
        FunctionTemplate::New( OpenOrderEnd )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getWinError" ), 
        FunctionTemplate::New( WinError )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getConnectionClosed" ), 
        FunctionTemplate::New( ConnectionClosed )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getUpdateAccountValue" ), 
        FunctionTemplate::New( UpdateAccountValue )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getUpdatePortfolio" ), 
        FunctionTemplate::New( UpdatePortfolio )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getUpdateAccountTime" ), 
        FunctionTemplate::New( UpdateAccountTime )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getAccountDownloadEnd" ), 
        FunctionTemplate::New( AccountDownloadEnd )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getNextValidId" ), 
        FunctionTemplate::New( NextValidId )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getContractDetails" ), 
        FunctionTemplate::New( GetContractDetails )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getBondContractDetails" ), 
        FunctionTemplate::New( BondContractDetails )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getContractDetailsEnd" ), 
        FunctionTemplate::New( ContractDetailsEnd )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getExecDetails" ), 
        FunctionTemplate::New( ExecDetails )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getExecDetailsEnd" ), 
        FunctionTemplate::New( ExecDetailsEnd )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getError" ), 
        FunctionTemplate::New( Error )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getUpdateMktDepth" ), 
        FunctionTemplate::New( UpdateMktDepth )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getUpdateMktDepthL2" ), 
        FunctionTemplate::New( UpdateMktDepthL2 )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getUpdateNewsBulletin" ), 
        FunctionTemplate::New( UpdateNewsBulletin )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getManagedAccounts" ), 
        FunctionTemplate::New( ManagedAccounts )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getReceiveFA" ), 
        FunctionTemplate::New( ReceiveFA )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getHistoricalData" ), 
        FunctionTemplate::New( HistoricalData )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getScannerParameters" ), 
        FunctionTemplate::New( ScannerParameters )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getScannerData" ), 
        FunctionTemplate::New( ScannerData )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getScannerDataEnd" ), 
        FunctionTemplate::New( ScannerDataEnd )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getRealtimeBar" ), 
        FunctionTemplate::New( RealtimeBar )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getFundamentalData" ), 
        FunctionTemplate::New( FundamentalData )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getDeltaNeutralValidation" ), 
        FunctionTemplate::New( DeltaNeutralValidation )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getTickSnapshotEnd" ), 
        FunctionTemplate::New( TickSnapshotEnd )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getMarketDataType" ), 
        FunctionTemplate::New( MarketDataType )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getCommissionReport" ), 
        FunctionTemplate::New( CommissionReport )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getPosition" ), 
        FunctionTemplate::New( Position )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getPositionEnd" ), 
        FunctionTemplate::New( PositionEnd )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getAccountSummary" ), 
        FunctionTemplate::New( AccountSummary )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getAccountSummaryEnd" ), 
        FunctionTemplate::New( AccountSummaryEnd )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getNextValidId" ),
        FunctionTemplate::New( NextValidId )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getVerifyMessageAPI" ),
        FunctionTemplate::New( VerifyMessageAPI )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getVerifyCompleted" ),
        FunctionTemplate::New( VerifyCompleted )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getDisplayGroupList" ),
        FunctionTemplate::New( DisplayGroupList )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "getDisplayGroupUpdated" ),
        FunctionTemplate::New( DisplayGroupUpdated )->GetFunction() );

    /// EClientSocket
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "connect" ),
        FunctionTemplate::New( Connect )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "disconnect" ),
        FunctionTemplate::New( Disconnect )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "isConnected" ),
        FunctionTemplate::New( IsConnected )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "serverVersion" ),
        FunctionTemplate::New( ServerVersion )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "twsConnectionTime" ),
        FunctionTemplate::New( TwsConnectionTime )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqMktData" ),
        FunctionTemplate::New( ReqMktData )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "cancelMktData" ),
        FunctionTemplate::New( CancelMktData )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "placeOrder" ),
        FunctionTemplate::New( PlaceOrder )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "cancelOrder" ),
        FunctionTemplate::New( CancelOrder )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqOpenOrders" ),
        FunctionTemplate::New( ReqOpenOrders )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqAccountUpdates" ),
        FunctionTemplate::New( ReqAccountUpdates )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqExecutions" ),
        FunctionTemplate::New( ReqExecutions )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqIds" ),
        FunctionTemplate::New( ReqIds )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "checkMessages" ),
        FunctionTemplate::New( CheckMessages )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqContractDetails" ),
        FunctionTemplate::New( ReqContractDetails )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqMktDepth" ),
        FunctionTemplate::New( ReqMktDepth )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "cancelMktDepth" ),
        FunctionTemplate::New( CancelMktDepth )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqNewsBulletins" ),
        FunctionTemplate::New( ReqNewsBulletins )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "cancelNewsBulletins" ),
        FunctionTemplate::New( CancelNewsBulletins )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "setServerLogLevel" ),
        FunctionTemplate::New( SetServerLogLevel )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqAutoOpenOrders" ),
        FunctionTemplate::New( ReqAutoOpenOrders )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqAllOpenOrders" ),
        FunctionTemplate::New( ReqAllOpenOrders )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqManagedAccts" ),
        FunctionTemplate::New( ReqManagedAccts )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "requestFA" ),
        FunctionTemplate::New( RequestFA )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "replaceFA" ),
        FunctionTemplate::New( ReplaceFA )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqHistoricalData" ),
        FunctionTemplate::New( ReqHistoricalData )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "exerciseOptions" ),
        FunctionTemplate::New( ExerciseOptions )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "cancelHistoricalData" ),
        FunctionTemplate::New( CancelHistoricalData )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqRealtimeBars" ),
        FunctionTemplate::New( ReqRealTimeBars )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "cancelRealTimeBars" ),
        FunctionTemplate::New( CancelRealTimeBars )->GetFunction() );
    tpl->PrototypeTemplate()->Set( 
        String::NewSymbol( "cancelScannerSubscription" ),
        FunctionTemplate::New( CancelScannerSubscription )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqScannerParameters" ),
        FunctionTemplate::New( ReqScannerParameters )->GetFunction() );
    tpl->PrototypeTemplate()->Set( 
        String::NewSymbol( "reqScannerSubscription" ),
        FunctionTemplate::New( ReqScannerSubscription )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqCurrentTime" ),
        FunctionTemplate::New( ReqCurrentTime )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqFundamentalData" ),
        FunctionTemplate::New( ReqFundamentalData )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "cancelFundamentalData" ),
        FunctionTemplate::New( CancelFundamentalData )->GetFunction() );
    tpl->PrototypeTemplate()->Set( 
        String::NewSymbol( "calculateImpliedVolatility" ),
        FunctionTemplate::New( CalculateImpliedVolatility )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "calculateOptionPrice" ),
        FunctionTemplate::New( CalculateOptionPrice )->GetFunction() );
    tpl->PrototypeTemplate()->Set( 
        String::NewSymbol( "cancelCalculateImpliedVolatility" ),
        FunctionTemplate::
            New( CancelCalculateImpliedVolatility )->GetFunction() );
    tpl->PrototypeTemplate()->Set( 
        String::NewSymbol( "cancelCalculateOptionPrice" ),
        FunctionTemplate::New( CancelCalculateOptionPrice )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqGlobalCancel" ),
        FunctionTemplate::New( ReqGlobalCancel )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqMarketDataType" ),
        FunctionTemplate::New( ReqMarketDataType )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqPositions" ),
        FunctionTemplate::New( ReqPositions )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "cancelPositions" ),
        FunctionTemplate::New( CancelPositions )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "reqAccountSummary" ),
        FunctionTemplate::New( ReqAccountSummary )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "cancelAccountSummary" ),
        FunctionTemplate::New( CancelAccountSummary )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "verifyRequest" ),
        FunctionTemplate::New( VerifyRequest )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "verifyMessage" ),
        FunctionTemplate::New( VerifyMessage )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "queryDisplayGroups" ),
        FunctionTemplate::New( QueryDisplayGroups )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "subscribeToGroupEvents" ),
        FunctionTemplate::New( SubscribeToGroupEvents )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "updateDisplayGroup" ),
        FunctionTemplate::New( UpdateDisplayGroup )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "unsubscribeFromGroupEvents" ),
        FunctionTemplate::New( UnsubscribeFromGroupEvents )->GetFunction() );

    //
    Persistent<Function> constructor = 
        Persistent<Function>::New( tpl->GetFunction() );
    exports->Set( String::NewSymbol( "NodeIbapi" ), constructor );
}

Handle<Value> NodeIbapi::New( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = new NodeIbapi();
    obj->Wrap( args.This() );

    return args.This();
}

Handle<Value> NodeIbapi::Connect( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    if ( isWrongArgNumber( args, 3 ) || 
        isWrongType( !args[0]->IsString(), 0 ) ||
        isWrongType( !args[1]->IsUint32(), 1 ) || 
        isWrongType( !args[2]->IsInt32(), 2 ) ) {
        return scope.Close( Undefined() );
    }

    char * host = getChar( args[0], "" );
    bool conn = 
        obj->m_client.connect(
            host, args[1]->Uint32Value(), args[2]->Int32Value() );
    return scope.Close( Boolean::New( conn ) );
}

// TODO disconnect method should return something
Handle<Value> NodeIbapi::Disconnect( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    obj->m_client.disconnect();
    return scope.Close( Undefined() );
}

Handle<Value> NodeIbapi::IsConnected( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    return scope.Close( Boolean::New( obj->m_client.isConnected() ) );
}

Handle<Value> NodeIbapi::ProcessMsg( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    obj->m_client.processMessages();
    return scope.Close( Undefined() );
}


///////////////////////////////////////////////////////////////////////////////
// node implementation for EClientSocket methods
///////////////////////////////////////////////////////////////////////////////
Handle<Value> NodeIbapi::ServerVersion( const Arguments& args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    return scope.Close( Integer::New( obj->m_client.serverVersion() ) );
}
Handle<Value> NodeIbapi::TwsConnectionTime( const Arguments& args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    return scope.Close( String::New( 
                                obj->m_client.TwsConnectionTime().c_str() ) );
}
Handle<Value> NodeIbapi::ReqMktData( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    if ( isWrongArgNumber( args, 4 ) ) {
        return scope.Close( Undefined() );
    }

    TickerId tickerId = args[0]->Int32Value();
    Contract contract;
 
    Handle<Object> ibContract = Handle<Object>::Cast( args[1] );
    convertContractForIb( ibContract, contract ); 

    IBString genericTick = getChar( args[2] );

    bool snapShot = args[3]->BooleanValue();

    TagValueListSPtr mktDataOptions;

    obj->m_client.reqMktData( tickerId, contract, genericTick, snapShot, 
                              mktDataOptions );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CancelMktData( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    if ( isWrongArgNumber( args, 1 ) || 
        isWrongType( !args[0]->IsUint32(), 0 ) ) {
        return scope.Close( Undefined() );
    }

    TickerId tickerId = args[0]->Int32Value();

    obj->m_client.cancelMktData( tickerId );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::PlaceOrder( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    // TODO: Better way to handle arg num issue
    if ( args.Length() != 7 && args.Length() != 3 ) {
        ThrowException(
            Exception::TypeError(
                String::New( "Wrong number of arguments, must be 3 or 7" ) ) );
        return scope.Close( Undefined() );
    }

    OrderId orderId;
    Contract contract;
    Order order;

    orderId = args[0]->Int32Value();

    Handle<Object> ibContract = Handle<Object>::Cast( args[1] );
    convertContractForIb( ibContract, contract ); 

    if ( args.Length() == 7 ) {
        if ( isWrongType( !args[2]->IsString(), 2 ) )
            return scope.Close( Undefined() );

        order.action = getChar( args[2] );
        order.totalQuantity = args[3]->Int32Value();
        order.orderType = getChar( args[4] );
        order.lmtPrice = args[5]->NumberValue();
        order.auxPrice = args[6]->NumberValue();
    }
    else if ( args.Length() == 3 ) {
        if ( isWrongType( !args[2]->IsObject(), 2 ) )
            return scope.Close( Undefined() );

        Handle<Object> ibOrder = Handle<Object>::Cast( args[2] );
        convertOrderForIb( ibOrder, order );
    }

    obj->m_client.placeOrder( orderId, contract, order );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CancelOrder( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 1 ) || 
         isWrongType( !args[0]->IsUint32(), 0 ) ) {
        return scope.Close( Undefined() );
    }
    obj->m_client.cancelOrder( args[0]->Int32Value() );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqOpenOrders( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    obj->m_client.reqOpenOrders();
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqAccountUpdates( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 2 ) || 
         isWrongType( !args[0]->IsBoolean(), 0 ) || 
         isWrongType( !args[1]->IsString(), 1 ) ) {
        return scope.Close( Undefined() );
    }
    bool subscribe = args[0]->BooleanValue();;
    IBString acctCode = getChar( args[1] );

    obj->m_client.reqAccountUpdates( subscribe, acctCode );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqExecutions( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 8 ) ) {
        return scope.Close( Undefined() );
    }
    int reqId = args[0]->Int32Value();
    ExecutionFilter filter;
    filter.m_clientId = args[1]->Int32Value();
    filter.m_acctCode = getChar( args[2] );
    filter.m_time = getChar( args[3] );
    filter.m_symbol = getChar( args[4] );
    filter.m_secType = getChar( args[5] );
    filter.m_exchange = getChar( args[6] );
    filter.m_side = getChar( args[7] );

    obj->m_client.reqExecutions( reqId, filter );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqIds( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }
    int numIds = args[0]->Int32Value();
    obj->m_client.reqIds( numIds );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CheckMessages( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    obj->m_client.checkMessages();
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqContractDetails( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    int reqId = args[0]->Int32Value();

    if ( isWrongArgNumber( args, 2 ) ) {
        return scope.Close( Undefined() );
    }

    Contract contract;

    reqId = args[0]->Int32Value();
    Handle<Object> ibContract = Handle<Object>::Cast( args[1] );
    convertContractForIb( ibContract, contract ); 

    obj->m_client.reqContractDetails( reqId, contract );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqMktDepth( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    if ( isWrongArgNumber( args, 3 ) ) {
        return scope.Close( Undefined() );
    }

    TickerId tickerId = args[0]->Int32Value();
    Contract contract;
 
    Handle<Object> ibContract = Handle<Object>::Cast( args[1] );
    convertContractForIb( ibContract, contract ); 

    int numRows = args[2]->Int32Value();

    TagValueListSPtr mktDepthOptions;

    obj->m_client.reqMktDepth( tickerId, contract, numRows, mktDepthOptions );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CancelMktDepth( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    
    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }
    TickerId tickerId = args[0]->Int32Value();
    obj->m_client.cancelMktDepth( tickerId );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqNewsBulletins( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }
    bool allMsgs = args[0]->BooleanValue();
    obj->m_client.reqNewsBulletins( allMsgs );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CancelNewsBulletins( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    obj->m_client.cancelNewsBulletins();
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::SetServerLogLevel( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }
    int level = args[0]->Int32Value();
    obj->m_client.setServerLogLevel( level );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqAutoOpenOrders( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }
    bool bAutoBind = args[0]->BooleanValue();
    obj->m_client.reqAutoOpenOrders( bAutoBind );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqAllOpenOrders( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    obj->m_client.reqAllOpenOrders();
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqManagedAccts( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    obj->m_client.reqManagedAccts();
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::RequestFA( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    // TODO: placeholder

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReplaceFA( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    // TODO: placeholder

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqHistoricalData( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    if ( isWrongArgNumber( args, 8 ) ) {
        return scope.Close( Undefined() );
    }
    TickerId id;
    Contract contract;
    IBString endDateTime;
    IBString durationStr;
    IBString barSizeSetting;
    IBString whatToShow;
    int useRTH;
    int formatDate;

    id = args[0]->Int32Value();

    Handle<Object> ibContract = Handle<Object>::Cast( args[1] );
    convertContractForIb( ibContract, contract );

    endDateTime = getChar( args[2] );
    durationStr = getChar( args[3] );
    barSizeSetting = getChar( args[4] );
    whatToShow = getChar( args[5] );
    useRTH = args[6]->Int32Value();
    formatDate = args[7]->Int32Value();

    TagValueListSPtr chartOptions;

    obj->m_client.reqHistoricalData( id, contract, endDateTime, durationStr, 
                                     barSizeSetting, whatToShow, useRTH, 
                                     formatDate, chartOptions );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ExerciseOptions( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    
    if ( isWrongArgNumber( args, 6 ) ) {
        return scope.Close( Undefined() );
    }
    TickerId tickerId;
    Contract contract;
    int exerciseAction;
    int exerciseQuantity;
    IBString account;
    int override;

    tickerId = args[0]->Int32Value();
    Handle<Object> ibContract = Handle<Object>::Cast( args[1] );
    convertContractForIb( ibContract, contract );

    exerciseAction = args[2]->Int32Value();
    exerciseQuantity = args[3]->Int32Value();
    account = getChar( args[4] );
    override = args[5]->Int32Value();

    obj->m_client.exerciseOptions( tickerId, contract, exerciseAction, 
                                   exerciseQuantity, account, override );

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CancelHistoricalData( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }
    TickerId tickerId = args[0]->Int32Value();
    obj->m_client.cancelHistoricalData( tickerId );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqRealTimeBars( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 5 ) ) {
        return scope.Close( Undefined() );
    }

    TickerId tickerId = args[0]->Int32Value();
    Contract contract;
 
    Handle<Object> ibContract = Handle<Object>::Cast( args[1] );
    convertContractForIb( ibContract, contract );

    int barSize = args[2]->Int32Value();
    IBString whatToShow = getChar( args[3] );
    bool useRTH = args[4]->BooleanValue();

    TagValueListSPtr realTimeBarsOptions;
    obj->m_client.reqRealTimeBars( tickerId, contract, barSize, whatToShow, 
                                   useRTH, realTimeBarsOptions );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CancelRealTimeBars( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }

    TickerId tickerId = args[0]->Int32Value();
    obj->m_client.cancelRealTimeBars( tickerId );

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CancelScannerSubscription( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }

    TickerId tickerId = args[0]->Int32Value();
    obj->m_client.cancelScannerSubscription( tickerId );

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqScannerParameters( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    obj->m_client.reqScannerParameters();
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqScannerSubscription( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    if ( isWrongArgNumber( args, 2 ) ) {
        return scope.Close( Undefined() );
    }

    TickerId tickerId = args[0]->Int32Value();
    ScannerSubscription subscription;
    Handle<Object> ibsub = Handle<Object>::Cast( args[1] );
    convertSubForIb( ibsub, subscription );

    TagValueListSPtr scannerSubscriptionOptions;

    obj->m_client.reqScannerSubscription( tickerId, subscription,
                                        scannerSubscriptionOptions );

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqCurrentTime( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    obj->m_client.reqCurrentTime();
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqFundamentalData( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    if ( isWrongArgNumber( args, 3 ) ) {
        return scope.Close( Undefined() );
    }

    TickerId reqId = args[0]->Int32Value();
    Contract contract;
 
    Handle<Object> ibContract = Handle<Object>::Cast( args[1] );
    convertContractForIb( ibContract, contract );
    IBString reportType = getChar( args[2] );

    obj->m_client.reqFundamentalData( reqId, contract, reportType );

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CancelFundamentalData( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }

    TickerId reqId = args[0]->Int32Value();
    obj->m_client.cancelFundamentalData( reqId );

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CalculateImpliedVolatility( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 4 ) ) {
        return scope.Close( Undefined() );
    }

    TickerId reqId = args[0]->Int32Value();
    Contract contract;
 
    Handle<Object> ibContract = Handle<Object>::Cast( args[1] );
    convertContractForIb( ibContract, contract );
    double optionPrice = args[2]->NumberValue();
    double underPrice = args[3]->NumberValue();

    obj->m_client.calculateImpliedVolatility( reqId, contract, optionPrice, 
                                              underPrice );

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CalculateOptionPrice( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 4 ) ) {
        return scope.Close( Undefined() );
    }

    TickerId reqId = args[0]->Int32Value();
    Contract contract;
 
    Handle<Object> ibContract = Handle<Object>::Cast( args[1] );
    convertContractForIb( ibContract, contract );
    double volatility = args[2]->NumberValue();
    double underPrice = args[3]->NumberValue();

    obj->m_client.calculateOptionPrice( reqId, contract, volatility, 
                                        underPrice );

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CancelCalculateImpliedVolatility(
    const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }

    TickerId reqId = args[0]->Int32Value();
    obj->m_client.cancelCalculateImpliedVolatility( reqId );

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CancelCalculateOptionPrice( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }

    TickerId reqId = args[0]->Int32Value();
    obj->m_client.cancelCalculateOptionPrice( reqId );

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqGlobalCancel( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    obj->m_client.reqGlobalCancel();
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqMarketDataType( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }

    int marketDataType = args[0]->Int32Value();
    obj->m_client.reqMarketDataType( marketDataType );

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqPositions( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    obj->m_client.reqPositions();

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CancelPositions( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    obj->m_client.cancelPositions();

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::ReqAccountSummary( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 3 ) ) {
        return scope.Close( Undefined() );
    }

    int reqId = args[0]->Int32Value();
    IBString groupName = getChar( args[1] ); 
    IBString tags = getChar( args[2] );
    obj->m_client.reqAccountSummary( reqId, groupName, tags );

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::CancelAccountSummary( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }

    int reqId = args[0]->Int32Value();
    obj->m_client.cancelAccountSummary( reqId );

    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::VerifyRequest( const Arguments& args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 2 ) ) {
        return scope.Close( Undefined() );
    }

    if ( isWrongType( !args[0]->IsString(), 0) ||
         isWrongType( !args[1]->IsString(), 1) ) {
        return scope.Close( Undefined() );
    }

    IBString apiName = getChar( args[0] );
    IBString apiVersion = getChar( args[1] );

    obj->m_client.verifyRequest( apiName, apiVersion );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::VerifyMessage( const Arguments& args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }

    if ( isWrongType( !args[0]->IsString(), 0 ) ) {
        return scope.Close( Undefined() );
    }

    IBString apiData = getChar( args[0] );

    obj->m_client.verifyMessage( apiData );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::QueryDisplayGroups( const Arguments& args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }

    if ( isWrongType( !args[0]->IsInt32(), 0 ) ) {
        return scope.Close( Undefined() );
    }

    int reqId = args[0]->Int32Value();

    obj->m_client.queryDisplayGroups( reqId );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::SubscribeToGroupEvents( const Arguments& args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    if ( isWrongArgNumber( args, 2 ) ) {
        return scope.Close( Undefined() );
    }

    if ( isWrongType( !args[0]->IsInt32(), 0 ) ||
         isWrongType( !args[1]->IsInt32(), 1 ) ) {
        return scope.Close( Undefined() );
    }

    int reqId = args[0]->Int32Value();
    int groupId = args[1]->Int32Value();

    obj->m_client.subscribeToGroupEvents( reqId, groupId );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::UpdateDisplayGroup( const Arguments& args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    if ( isWrongArgNumber( args, 2 ) ) {
        return scope.Close( Undefined() );
    }

    if ( isWrongType( !args[0]->IsInt32(), 0 ) ||
         isWrongType( !args[1]->IsString(), 1 ) ) {
        return scope.Close( Undefined() );
    }

    int reqId = args[0]->Int32Value();
    IBString contractInfo = getChar( args[1] );

    obj->m_client.updateDisplayGroup( reqId, contractInfo );
    return scope.Close( Undefined() );
}
Handle<Value> NodeIbapi::UnsubscribeFromGroupEvents( const Arguments& args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    if ( isWrongArgNumber( args, 1 ) ) {
        return scope.Close( Undefined() );
    }

    if ( isWrongType( !args[0]->IsInt32(), 0 ) ) {
        return scope.Close( Undefined() );
    }

    int reqId = args[0]->Int32Value();

    obj->m_client.unsubscribeFromGroupEvents( reqId );
    return scope.Close( Undefined() );
}


///////////////////////////////////////////////////////////////////////////////
//  Getters
///////////////////////////////////////////////////////////////////////////////


// Handle<Value> NodeIbapi::CurrentTime( const Arguments &args ) {
//     HandleScope scope;
//     NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
//     return scope.Close( String::New( obj->m_client.getCurrentTime().c_str() ) );
// }

Handle<Value> NodeIbapi::TickPrice( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    TickPriceData newTickPrice;
    newTickPrice = obj->m_client.getTickPrice();

    Handle<Object> retTickPrice = Object::New();
    retTickPrice->Set( String::NewSymbol( "isValid" ), 
                       Boolean::New( newTickPrice.isValid ) );
    retTickPrice->Set( String::NewSymbol( "tickerId" ), 
                       Integer::New( newTickPrice.tickerId ) );
    retTickPrice->Set( String::NewSymbol( "field" ), 
                       Integer::New( newTickPrice.field ) );
    retTickPrice->Set( String::NewSymbol( "price" ), 
                       Number::New( newTickPrice.price ) );
    retTickPrice->Set( String::NewSymbol( "canAutoExecute" ), 
                       Integer::New( newTickPrice.canAutoExecute ) );
 
    return scope.Close( retTickPrice );
}
Handle<Value> NodeIbapi::TickSize( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    TickSizeData newTickSize;
    newTickSize = obj->m_client.getTickSize();

    Handle<Object> retTickSize = Object::New();
    retTickSize->Set( String::NewSymbol( "isValid" ), 
                      Boolean::New( newTickSize.isValid ) );
    retTickSize->Set( String::NewSymbol( "tickerId" ),
                      Integer::New( newTickSize.tickerId ) );
    retTickSize->Set( String::NewSymbol( "field" ), 
                      Integer::New( newTickSize.field ) );
    retTickSize->Set( String::NewSymbol( "size" ), 
                      Integer::New( newTickSize.size) );

    return scope.Close( retTickSize );
}
Handle<Value> NodeIbapi::TickOptionComputation( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    TickOptionComputationData newTickOpt;
    newTickOpt = obj->m_client.getTickOptionComputation();

    Handle<Object> retTickOpt = Object::New();
    retTickOpt->Set( String::NewSymbol( "isValid" ), 
                     Boolean::New( newTickOpt.isValid ) );
    retTickOpt->Set( String::NewSymbol( "tickerId" ), 
                     Integer::New( newTickOpt.tickerId ) );
    retTickOpt->Set( String::NewSymbol( "tickType" ), 
                     Integer::New( newTickOpt.tickType ) );
    retTickOpt->Set( String::NewSymbol( "impliedVol" ), 
                     Number::New( newTickOpt.impliedVol ) );
    retTickOpt->Set( String::NewSymbol( "delta" ), 
                     Number::New( newTickOpt.delta ) );
    retTickOpt->Set( String::NewSymbol( "optPrice" ), 
                     Number::New( newTickOpt.optPrice ) );
    retTickOpt->Set( String::NewSymbol( "pvDividend" ), 
                     Number::New( newTickOpt.pvDividend ) );
    retTickOpt->Set( String::NewSymbol( "gamma" ), 
                     Number::New( newTickOpt.gamma ) );
    retTickOpt->Set( String::NewSymbol( "vega" ),
                     Number::New( newTickOpt.vega ) );
    retTickOpt->Set( String::NewSymbol( "theta" ),
                     Number::New( newTickOpt.theta ) );
    retTickOpt->Set( String::NewSymbol( "undPrice" ), 
                     Number::New( newTickOpt.undPrice ) );
    return scope.Close( retTickOpt );
}
Handle<Value> NodeIbapi::TickGeneric( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    TickGenericData newTickGen;
    newTickGen = obj->m_client.getTickGeneric();

    Handle<Object> retTickGen = Object::New();
    retTickGen->Set( String::NewSymbol( "isValid" ), 
                     Boolean::New( newTickGen.isValid ) );
    retTickGen->Set( String::NewSymbol( "tickerId" ), 
                     Integer::New( newTickGen.tickerId ) );
    retTickGen->Set( String::NewSymbol( "tickType" ), 
                     Integer::New( newTickGen.tickType ) );
    retTickGen->Set( String::NewSymbol( "value" ), 
                     Number::New( newTickGen.value ) );
    return scope.Close( retTickGen );
}
Handle<Value> NodeIbapi::TickString( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    TickStringData newTickStr;
    newTickStr = obj->m_client.getTickString();

    Handle<Object> retTickStr = Object::New();
    retTickStr->Set( String::NewSymbol( "isValid" ), 
                     Boolean::New( newTickStr.isValid ) );
    retTickStr->Set( String::NewSymbol( "tickerId" ), 
                     Integer::New( newTickStr.tickerId ) );
    retTickStr->Set( String::NewSymbol( "tickType" ), 
                     Integer::New( newTickStr.tickType ) );
    retTickStr->Set( String::NewSymbol( "value" ), 
                     String::New( newTickStr.value.c_str() ) );
    return scope.Close( retTickStr );
}
Handle<Value> NodeIbapi::TickEFP( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    TickEFPData newTickEFP;
    newTickEFP = obj->m_client.getTickEFP();

    Handle<Object> retTickEFP = Object::New();
    retTickEFP->Set( String::NewSymbol( "isValid" ), 
                     Boolean::New( newTickEFP.isValid ) );
    retTickEFP->Set( String::NewSymbol( "tickerId" ), 
                     Integer::New( newTickEFP.tickerId ) );
    retTickEFP->Set( String::NewSymbol( "tickType" ), 
                     Integer::New( newTickEFP.tickType ) );
    retTickEFP->Set( String::NewSymbol( "basisPoints" ), 
                     Number::New( newTickEFP.basisPoints ) );
    retTickEFP->Set( String::NewSymbol( "formattedBasisPoints" ), 
                     String::New( newTickEFP.formattedBasisPoints.c_str() ) );
    retTickEFP->Set( String::NewSymbol( "totalDividends" ), 
                     Number::New( newTickEFP.totalDividends ) );
    retTickEFP->Set( String::NewSymbol( "holdDays" ), 
                     Integer::New( newTickEFP.holdDays ) );
    retTickEFP->Set( String::NewSymbol( "futureExpiry" ), 
                     String::New( newTickEFP.futureExpiry.c_str() ) );
    retTickEFP->Set( String::NewSymbol( "dividendImpact" ), 
                     Number::New( newTickEFP.dividendImpact ) );
    retTickEFP->Set( String::NewSymbol( "dividendsToExpiry" ), 
                     Number::New( newTickEFP.dividendsToExpiry ) );
    return scope.Close( retTickEFP );
}
Handle<Value> NodeIbapi::OrderStatus( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    OrderStatusData newOrderStatus;
    newOrderStatus = obj->m_client.getOrderStatus();

    Handle<Object> retOrderStatus = Object::New();
    retOrderStatus->Set( String::NewSymbol( "isValid" ), 
                     Boolean::New( newOrderStatus.isValid ) );
    retOrderStatus->Set( String::NewSymbol( "orderId" ), 
                         Integer::New( newOrderStatus.orderId ) );
    retOrderStatus->Set( String::NewSymbol( "status" ), 
                         String::New( newOrderStatus.status.c_str() ) );
    retOrderStatus->Set( String::NewSymbol( "filled" ), 
                         Integer::New( newOrderStatus.filled) );
    retOrderStatus->Set( String::NewSymbol( "remaining" ), 
                         Integer::New( newOrderStatus.remaining ) );
    retOrderStatus->Set( String::NewSymbol( "avgFillPrice" ), 
                         Number::New( newOrderStatus.avgFillPrice ) );
    retOrderStatus->Set( String::NewSymbol( "permId" ), 
                         Integer::New( newOrderStatus.permId ) );
    retOrderStatus->Set( String::NewSymbol( "parentId" ), 
                         Integer::New( newOrderStatus.parentId ) );
    retOrderStatus->Set( String::NewSymbol( "lastFillPrice" ), 
                         Number::New( newOrderStatus.lastFillPrice ) );
    retOrderStatus->Set( String::NewSymbol( "clientId" ), 
                         Integer::New( newOrderStatus.clientId ) );
    retOrderStatus->Set( String::NewSymbol( "whyHeld" ), 
                         String::New( newOrderStatus.whyHeld.c_str() ) );
    return scope.Close( retOrderStatus );
}
Handle<Value> NodeIbapi::OpenOrder( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    OpenOrderData newOpenOrder;
    newOpenOrder = obj->m_client.getOpenOrder();

    Handle<Object> retOpenOrder = Object::New();
    retOpenOrder->Set( String::NewSymbol( "isValid" ), 
                     Boolean::New( newOpenOrder.isValid ) );
    retOpenOrder->Set( String::NewSymbol( "orderId" ), 
                       Integer::New( newOpenOrder.orderId ) );
    retOpenOrder->Set( String::NewSymbol( "status" ), 
                       String::New( newOpenOrder.orderState.status.c_str() ) );
    retOpenOrder->Set( String::NewSymbol( "initMargin" ), 
        String::New( newOpenOrder.orderState.initMargin.c_str() ) );
    retOpenOrder->Set( String::NewSymbol( "maintMargin" ), 
        String::New( newOpenOrder.orderState.maintMargin.c_str() ) );
    retOpenOrder->Set( String::NewSymbol( "equityWithLoan" ), 
        String::New( newOpenOrder.orderState.equityWithLoan.c_str() ) );
    retOpenOrder->Set( String::NewSymbol( "commission" ), 
        Number::New( newOpenOrder.orderState.commission) );
    retOpenOrder->Set( String::NewSymbol( "minCommission" ), 
        Number::New( newOpenOrder.orderState.minCommission) );
    retOpenOrder->Set( String::NewSymbol( "maxCommission" ), 
        Number::New( newOpenOrder.orderState.maxCommission) );
    retOpenOrder->Set( String::NewSymbol( "commissionCurrency" ), 
        String::New( newOpenOrder.orderState.commissionCurrency.c_str() ) );
    retOpenOrder->Set( String::NewSymbol( "warningText" ), 
        String::New( newOpenOrder.orderState.warningText.c_str() ) );
    return scope.Close( retOpenOrder );
}
Handle<Value> NodeIbapi::OpenOrderEnd( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    OpenOrderEndData newOpenOrderEnd;
    newOpenOrderEnd = obj->m_client.getOpenOrderEnd();

    Handle<Object> retOpenOrderEnd = Object::New();
    retOpenOrderEnd->Set( String::NewSymbol( "isValid" ),
                          Boolean::New( newOpenOrderEnd.isValid ) );

    return scope.Close( retOpenOrderEnd );
}
Handle<Value> NodeIbapi::WinError( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    WinErrorData newWinError;
    newWinError = obj->m_client.getWinError();

    Handle<Object> retWinError = Object::New();
    retWinError->Set( String::NewSymbol( "isValid" ), 
                      Boolean::New( newWinError.isValid ) );
    retWinError->Set( String::NewSymbol( "str" ), 
                      String::New( newWinError.str.c_str() ) );
    retWinError->Set( String::NewSymbol( "lastError" ), 
                      Integer::New( newWinError.lastError ) );

    return scope.Close( retWinError );
}
Handle<Value> NodeIbapi::ConnectionClosed( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    ConnectionClosedData newConnectionClosed;
    newConnectionClosed = obj->m_client.getConnectionClosed();

    Handle<Object> retConnectionClosed = Object::New();
    retConnectionClosed->Set( String::NewSymbol( "isValid" ),
                          Boolean::New( newConnectionClosed.isValid ) );

    return scope.Close( retConnectionClosed );
}
Handle<Value> NodeIbapi::UpdateAccountValue( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    UpdateAccountValueData newUpdateAccountValue;
    newUpdateAccountValue = obj->m_client.getUpdateAccountValue();

    Handle<Object> retUpdateAccountValue = Object::New();
    retUpdateAccountValue->Set( String::NewSymbol( "isValid" ), 
                     Boolean::New( newUpdateAccountValue.isValid ) );
    retUpdateAccountValue->Set( String::NewSymbol( "key" ), 
        String::New( newUpdateAccountValue.key.c_str() ) );
    retUpdateAccountValue->Set( String::NewSymbol( "value" ), 
        String::New( newUpdateAccountValue.val.c_str() ) );
    retUpdateAccountValue->Set( String::NewSymbol( "currency" ), 
        String::New( newUpdateAccountValue.currency.c_str() ) );
    retUpdateAccountValue->Set( String::NewSymbol( "accountName" ), 
        String::New( newUpdateAccountValue.accountName.c_str() ) );
    return scope.Close( retUpdateAccountValue );
}
Handle<Value> NodeIbapi::UpdatePortfolio( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    UpdatePortfolioData newUpdatePortfolio;
    newUpdatePortfolio = obj->m_client.getUpdatePortfolio();

    Handle<Object> retUpdatePortfolio = Object::New();
    retUpdatePortfolio->Set( String::NewSymbol( "isValid" ),
                             Boolean::New( newUpdatePortfolio.isValid ) );
    retUpdatePortfolio->Set( String::NewSymbol( "contract" ), 
        convertContractForNode( newUpdatePortfolio.contract ) );
    retUpdatePortfolio->Set( String::NewSymbol( "position" ),
                             Integer::New( newUpdatePortfolio.position ) );
    retUpdatePortfolio->Set( String::NewSymbol( "marketPrice" ),
                             Number::New( newUpdatePortfolio.marketPrice ) );
    retUpdatePortfolio->Set( String::NewSymbol( "marketValue" ),
                             Number::New( newUpdatePortfolio.marketValue ) );
    retUpdatePortfolio->Set( String::NewSymbol( "averageCost" ),
                             Number::New( newUpdatePortfolio.averageCost ) );
    retUpdatePortfolio->Set( String::NewSymbol( "unrealizedPNL" ),
                             Number::New( newUpdatePortfolio.unrealizedPNL ) );
    retUpdatePortfolio->Set( String::NewSymbol( "realizedPNL" ),
                             Number::New( newUpdatePortfolio.realizedPNL ) );
    retUpdatePortfolio->Set( String::NewSymbol( "accountName" ),
                             String::New( 
                                newUpdatePortfolio.accountName.c_str() ) );
    return scope.Close( retUpdatePortfolio );
}
Handle<Value> NodeIbapi::UpdateAccountTime( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    UpdateAccountTimeData newAccountTime;
    newAccountTime = obj->m_client.getUpdateAccountTime();

    Handle<Object> retAccountTime = Object::New();
    retAccountTime->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newAccountTime.isValid ) );
    retAccountTime->Set( String::NewSymbol( "timeStamp" ),
                  String::New( newAccountTime.timeStamp.c_str() ) );

    return scope.Close( retAccountTime );
}
Handle<Value> NodeIbapi::AccountDownloadEnd( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    AccountDownloadEndData newAcctDownloadEnd;
    newAcctDownloadEnd = obj->m_client.getAccountDownloadEnd();

    Handle<Object> retAcctDownloadEnd = Object::New();
    retAcctDownloadEnd->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newAcctDownloadEnd.isValid ) );
    retAcctDownloadEnd->Set( String::NewSymbol( "accountName" ),
                  String::New( newAcctDownloadEnd.accountName.c_str() ) );

    return scope.Close( retAcctDownloadEnd );
}
Handle<Value> NodeIbapi::NextValidId( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    NextValidIdData newNextValidId;
    newNextValidId = obj->m_client.getNextValidId();

    Handle<Object> retNextValidId = Object::New();
    retNextValidId->Set( String::NewSymbol( "isValid" ), 
                         Boolean::New( newNextValidId.isValid ) );
    retNextValidId->Set( String::NewSymbol( "orderId" ),
                         Integer::New( newNextValidId.orderId ) );
    return scope.Close( retNextValidId );
}
Handle<Value> NodeIbapi::GetContractDetails( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    ContractDetailsData newContractDetails;
    newContractDetails = obj->m_client.getContractDetails();

    Handle<Object> retContractDetails = Object::New();
    retContractDetails->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newContractDetails.isValid ) );
    retContractDetails->Set( String::NewSymbol( "reqId" ),
                  Integer::New( newContractDetails.reqId ) );
    retContractDetails->Set( String::NewSymbol( "contractDetails" ),
        convertContDetailForNode( newContractDetails.contractDetails ) );

    return scope.Close( retContractDetails );
}
Handle<Value> NodeIbapi::BondContractDetails( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    BondContractDetailsData newBondContractDetails;
    newBondContractDetails = obj->m_client.getBondContractDetails();

    Handle<Object> retContractDetails = Object::New();
    retContractDetails->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newBondContractDetails.isValid ) );
    retContractDetails->Set( String::NewSymbol( "reqId" ),
                  Integer::New( newBondContractDetails.reqId ) );
    retContractDetails->Set( String::NewSymbol( "contractDetails" ),
        convertContDetailForNode( newBondContractDetails.contractDetails ) );

    return scope.Close( retContractDetails );
}
Handle<Value> NodeIbapi::ContractDetailsEnd( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    ContractDetailsEndData newContractDetailsEnd;
    newContractDetailsEnd = obj->m_client.getContractDetailsEnd();

    Handle<Object> retContractDetailsEnd = Object::New();
    retContractDetailsEnd->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newContractDetailsEnd.isValid ) );
    retContractDetailsEnd->Set( String::NewSymbol( "reqId" ),
                  Integer::New( newContractDetailsEnd.reqId ) );

    return scope.Close( retContractDetailsEnd );
}
Handle<Value> NodeIbapi::ExecDetails( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    ExecDetailsData newExecDetails;
    newExecDetails = obj->m_client.getExecDetails();

    Handle<Object> retExecDetails = Object::New();
    retExecDetails->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newExecDetails.isValid ) );
    retExecDetails->Set( String::NewSymbol( "reqId" ),
                  Integer::New( newExecDetails.reqId ) );
    retExecDetails->Set( String::NewSymbol( "contract" ),
                  convertContractForNode( newExecDetails.contract ) );
    retExecDetails->Set( String::NewSymbol( "execution" ),
                  convertExecForNode( newExecDetails.execution ) );
    return scope.Close( retExecDetails );
}
Handle<Value> NodeIbapi::ExecDetailsEnd( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    ExecDetailsEndData newExecDetailsEnd;
    newExecDetailsEnd = obj->m_client.getExecDetailsEnd();

    Handle<Object> retExecDetailsEnd = Object::New();
    retExecDetailsEnd->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newExecDetailsEnd.isValid ) );
    retExecDetailsEnd->Set( String::NewSymbol( "reqId" ),
                  Integer::New( newExecDetailsEnd.reqId ) );

    return scope.Close( retExecDetailsEnd );
}
Handle<Value> NodeIbapi::Error( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    ErrorData newError;
    newError = obj->m_client.getError();

    Handle<Object> retError = Object::New();
    retError->Set( String::NewSymbol( "isValid" ), 
                   Boolean::New( newError.isValid ) );
    retError->Set( String::NewSymbol( "id" ), Integer::New( newError.id ) );
    retError->Set( String::NewSymbol( "errorCode" ), 
                   Integer::New( newError.errorCode ) );
    retError->Set( String::NewSymbol( "errorString" ), 
                   String::New( newError.errorString.c_str() ) );

    return scope.Close( retError );
}
Handle<Value> NodeIbapi::UpdateMktDepth( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    UpdateMktDepthData newUpdateMktDepth;
    newUpdateMktDepth = obj->m_client.getUpdateMktDepth();

    Handle<Object> retUpdateMktDepth = Object::New();
    retUpdateMktDepth->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newUpdateMktDepth.isValid ) );
    retUpdateMktDepth->Set( String::NewSymbol( "id" ),
                  Integer::New( newUpdateMktDepth.id ) );
    retUpdateMktDepth->Set( String::NewSymbol( "position" ),
                  Integer::New( newUpdateMktDepth.position ) );
    retUpdateMktDepth->Set( String::NewSymbol( "operation" ),
                  Integer::New( newUpdateMktDepth.operation ) );
    retUpdateMktDepth->Set( String::NewSymbol( "side" ),
                  Integer::New( newUpdateMktDepth.side ) );
    retUpdateMktDepth->Set( String::NewSymbol( "price" ),
                  Number::New( newUpdateMktDepth.price ) );
    retUpdateMktDepth->Set( String::NewSymbol( "size" ),
                  Integer::New( newUpdateMktDepth.size ) );

    return scope.Close( retUpdateMktDepth );
}
Handle<Value> NodeIbapi::UpdateMktDepthL2( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    UpdateMktDepthL2Data newUpdateMktDepthL2;
    newUpdateMktDepthL2 = obj->m_client.getUpdateMktDepthL2();

    Handle<Object> retUpdateMktDepthL2 = Object::New();
    retUpdateMktDepthL2->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newUpdateMktDepthL2.isValid ) ); 
    retUpdateMktDepthL2->Set( String::NewSymbol( "id" ),
                  Integer::New( newUpdateMktDepthL2.id ) ); 
    retUpdateMktDepthL2->Set( String::NewSymbol( "position" ),
                  Integer::New( newUpdateMktDepthL2.position ) ); 
    retUpdateMktDepthL2->Set( String::NewSymbol( "marketMaker" ),
                  String::New( newUpdateMktDepthL2.marketMaker.c_str() ) ); 
    retUpdateMktDepthL2->Set( String::NewSymbol( "operation" ),
                  Integer::New( newUpdateMktDepthL2.operation ) ); 
    retUpdateMktDepthL2->Set( String::NewSymbol( "side" ),
                  Integer::New( newUpdateMktDepthL2.side ) ); 
    retUpdateMktDepthL2->Set( String::NewSymbol( "price" ),
                  Number::New( newUpdateMktDepthL2.price ) ); 
    retUpdateMktDepthL2->Set( String::NewSymbol( "size" ),
                  Integer::New( newUpdateMktDepthL2.size ) ); 

    return scope.Close( retUpdateMktDepthL2 );
}
Handle<Value> NodeIbapi::UpdateNewsBulletin( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    UpdateNewsBulletinData newUpdateNewsBulletin;
    newUpdateNewsBulletin = obj->m_client.getUpdateNewsBulletin();

    Handle<Object> retUpdateNewsBulletin = Object::New();
    retUpdateNewsBulletin->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newUpdateNewsBulletin.isValid ) ); 
    retUpdateNewsBulletin->Set( String::NewSymbol( "msgId" ),
                  Integer::New( newUpdateNewsBulletin.msgId ) ); 
    retUpdateNewsBulletin->Set( String::NewSymbol( "msgType" ),
                  Integer::New( newUpdateNewsBulletin.msgType ) ); 
    retUpdateNewsBulletin->Set( String::NewSymbol( "newsMessage" ),
                  String::New( newUpdateNewsBulletin.newsMessage.c_str() ) ); 
    retUpdateNewsBulletin->Set( String::NewSymbol( "originExch" ),
                  String::New( newUpdateNewsBulletin.originExch.c_str() ) ); 

    return scope.Close( retUpdateNewsBulletin );
}
Handle<Value> NodeIbapi::ManagedAccounts( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    ManagedAccountsData newManagedAccounts;
    newManagedAccounts = obj->m_client.getManagedAccounts();

    Handle<Object> retManagedAccounts = Object::New();
    retManagedAccounts->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newManagedAccounts.isValid ) );
    retManagedAccounts->Set( String::NewSymbol( "isValid" ),
                  String::New( newManagedAccounts.accountsList.c_str() ) );

    return scope.Close( retManagedAccounts );
}
Handle<Value> NodeIbapi::ReceiveFA( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    ReceiveFAData newData;
    newData = obj->m_client.getReceiveFA();

    Handle<Object> retData = Object::New();
    retData->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newData.isValid ) );

    // TODO

    return scope.Close( retData );
}
Handle<Value> NodeIbapi::HistoricalData( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    HistoricalDataData newHistoricalData;
    newHistoricalData = obj->m_client.getHistoricalData();

    Handle<Object> retHistoricalData = Object::New();
    retHistoricalData->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newHistoricalData.isValid ) ); 
    retHistoricalData->Set( String::NewSymbol( "reqId" ),
                  Integer::New( newHistoricalData.reqId ) ); 
    retHistoricalData->Set( String::NewSymbol( "date" ),
                  String::New( newHistoricalData.date.c_str() ) ); 
    retHistoricalData->Set( String::NewSymbol( "open" ),
                  Number::New( newHistoricalData.open ) ); 
    retHistoricalData->Set( String::NewSymbol( "high" ),
                  Number::New( newHistoricalData.high ) ); 
    retHistoricalData->Set( String::NewSymbol( "low" ),
                  Number::New( newHistoricalData.low ) ); 
    retHistoricalData->Set( String::NewSymbol( "close" ),
                  Number::New( newHistoricalData.close ) ); 
    retHistoricalData->Set( String::NewSymbol( "volume" ),
                  Integer::New( newHistoricalData.volume ) ); 
    retHistoricalData->Set( String::NewSymbol( "barCount" ),
                  Integer::New( newHistoricalData.barCount ) ); 
    retHistoricalData->Set( String::NewSymbol( "WAP" ),
                  Number::New( newHistoricalData.WAP ) ); 
    retHistoricalData->Set( String::NewSymbol( "hasGaps" ),
                  Integer::New( newHistoricalData.hasGaps ) ); 

    return scope.Close( retHistoricalData );
}
Handle<Value> NodeIbapi::ScannerParameters( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    ScannerParametersData newScannerParameters;
    newScannerParameters = obj->m_client.getScannerParameters();

    Handle<Object> retScannerParameters = Object::New();
    retScannerParameters->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newScannerParameters.isValid ) );
    retScannerParameters->Set( String::NewSymbol( "xml" ),
                  String::New( newScannerParameters.xml.c_str() ) );

    return scope.Close( retScannerParameters );
}
Handle<Value> NodeIbapi::ScannerData( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    ScannerDataData newScannerData;
    newScannerData = obj->m_client.getScannerData();

    Handle<Object> retScannerData = Object::New();

    retScannerData->Set( String::NewSymbol( "isValid" ) ,
                  Boolean::New( newScannerData.isValid ) ); 
    retScannerData->Set( String::NewSymbol( "reqId" ) ,
                  Integer::New( newScannerData.reqId ) ); 
    retScannerData->Set( String::NewSymbol( "rank" ) ,
                  Integer::New( newScannerData.rank ) ); 
    retScannerData->Set( String::NewSymbol( "contractDetails" ) ,
                  convertContDetailForNode( newScannerData.contractDetails ) ); 
    retScannerData->Set( String::NewSymbol( "distance" ) ,
                  String::New( newScannerData.distance.c_str() ) ); 
    retScannerData->Set( String::NewSymbol( "benchmark" ) ,
                  String::New( newScannerData.benchmark.c_str() ) ); 
    retScannerData->Set( String::NewSymbol( "projection" ) ,
                  String::New( newScannerData.projection.c_str() ) ); 
    retScannerData->Set( String::NewSymbol( "legsStr" ) ,
                  String::New( newScannerData.legsStr.c_str() ) ); 

    return scope.Close( retScannerData );
}
Handle<Value> NodeIbapi::ScannerDataEnd( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    ScannerDataEndData newScannerEnd;
    newScannerEnd = obj->m_client.getScannerDataEnd();

    Handle<Object> retScannerEnd = Object::New();
    retScannerEnd->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newScannerEnd.isValid ) );
    retScannerEnd->Set( String::NewSymbol( "reqId" ),
                  Integer::New( newScannerEnd.reqId ) );

    return scope.Close( retScannerEnd );
}
Handle<Value> NodeIbapi::RealtimeBar( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    RealtimeBarData newRealtimeBar;
    newRealtimeBar = obj->m_client.getRealtimeBar();

    Handle<Object> retRealtimeBar = Object::New();
    retRealtimeBar->Set( String::NewSymbol( "isValid" ), 
                     Boolean::New( newRealtimeBar.isValid ) );
    retRealtimeBar->Set( String::NewSymbol( "reqId" ), 
                         Integer::New( newRealtimeBar.reqId ) );
    retRealtimeBar->Set( String::NewSymbol( "time" ), 
                         Integer::New( newRealtimeBar.time ) );
    retRealtimeBar->Set( String::NewSymbol( "open" ), 
                         Number::New( newRealtimeBar.open ) );
    retRealtimeBar->Set( String::NewSymbol( "high" ), 
                         Number::New( newRealtimeBar.high ) );
    retRealtimeBar->Set( String::NewSymbol( "low" ), 
                         Number::New( newRealtimeBar.low ) );
    retRealtimeBar->Set( String::NewSymbol( "close" ), 
                         Number::New( newRealtimeBar.close ) );
    retRealtimeBar->Set( String::NewSymbol( "volume" ), 
                         Integer::New( newRealtimeBar.volume ) );
    retRealtimeBar->Set( String::NewSymbol( "wap" ), 
                         Number::New( newRealtimeBar.wap ) );
    retRealtimeBar->Set( String::NewSymbol( "count" ), 
                         Integer::New( newRealtimeBar.count ) );
    return scope.Close( retRealtimeBar );
}
// TODO currentTime
Handle<Value> NodeIbapi::FundamentalData( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    FundamentalDataData newFundamentalData;
    newFundamentalData = obj->m_client.getFundamentalData();

    Handle<Object> retFundamentalData = Object::New();
    retFundamentalData->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newFundamentalData.isValid ) );
    retFundamentalData->Set( String::NewSymbol( "reqId" ),
                  Integer::New( newFundamentalData.reqId ) );
    retFundamentalData->Set( String::NewSymbol( "data" ),
                  String::New( newFundamentalData.data.c_str() ) );

    return scope.Close( retFundamentalData );
}
Handle<Value> NodeIbapi::DeltaNeutralValidation( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    DeltaNeutralValidationData newDeltaNeutralValidation;
    newDeltaNeutralValidation = obj->m_client.getDeltaNeutralValidation();

    Handle<Object> retDeltaNeutralValidation = Object::New();
    retDeltaNeutralValidation->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newDeltaNeutralValidation.isValid ) );
    retDeltaNeutralValidation->Set( String::NewSymbol( "reqId" ),
                  Integer::New( newDeltaNeutralValidation.reqId ) );

    Handle<Object> underComp = Object::New();
    underComp->Set( String::NewSymbol( "conId" ),
                    Integer::New( newDeltaNeutralValidation.underComp.conId ) );
    underComp->Set( String::NewSymbol( "delta" ),
                    Number::New( newDeltaNeutralValidation.underComp.delta ) );
    underComp->Set( String::NewSymbol( "price" ),
                    Number::New( newDeltaNeutralValidation.underComp.price ) );
    retDeltaNeutralValidation->Set( String::NewSymbol( "underComp" ), 
                                    underComp );

    return scope.Close( retDeltaNeutralValidation );
}
Handle<Value> NodeIbapi::TickSnapshotEnd( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    TickSnapshotEndData newTickSnapshotEnd;
    newTickSnapshotEnd = obj->m_client.getTickSnapshotEnd();
    Handle<Object> retTickSnapshotEnd = Object::New();
    retTickSnapshotEnd->Set( String::NewSymbol( "isValid" ), 
                     Boolean::New( newTickSnapshotEnd.isValid ) );
    retTickSnapshotEnd->Set( String::NewSymbol( "reqId" ), 
                             Integer::New( newTickSnapshotEnd.reqId ) );
    return scope.Close( retTickSnapshotEnd );
}
Handle<Value> NodeIbapi::MarketDataType( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    MarketDataTypeData newMarketDataType;
    newMarketDataType = obj->m_client.getMarketDataType();
    Handle<Object> retMarketDataType = Object::New();
    retMarketDataType->Set( String::NewSymbol( "isValid" ), 
                     Boolean::New( newMarketDataType.isValid ) );
    retMarketDataType->Set( String::NewSymbol( "reqId" ), 
                            Integer::New( newMarketDataType.reqId ) );
    retMarketDataType->Set( String::NewSymbol( "marketDataType" ), 
                            Integer::New( newMarketDataType.marketDataType ) );
    return scope.Close( retMarketDataType );
}
Handle<Value> NodeIbapi::CommissionReport( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    CommissionReportData newCommRep;
    newCommRep = obj->m_client.getCommissionReport();

    Handle<Object> retCommRep = Object::New();
    retCommRep->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newCommRep.isValid ) );

    Handle<Object> commissionReport = Object::New();
    commissionReport->Set( String::NewSymbol( "execId" ),
        String::New( newCommRep.commissionReport.execId.c_str() ) );
    commissionReport->Set( String::NewSymbol( "commission" ),
        Number::New( newCommRep.commissionReport.commission ) );
    commissionReport->Set( String::NewSymbol( "currency" ),
        String::New( newCommRep.commissionReport.currency.c_str() ) );
    commissionReport->Set( String::NewSymbol( "realizedPNL" ),
        Number::New( newCommRep.commissionReport.realizedPNL ) );
    commissionReport->Set( String::NewSymbol( "yield" ),
        Number::New( newCommRep.commissionReport.yield ) );
    commissionReport->Set( String::NewSymbol( "yieldRedemptionDate" ),
        Integer::New( newCommRep.commissionReport.yieldRedemptionDate ) );

    retCommRep->Set( String::NewSymbol( "commissionReport" ), 
        commissionReport );

    return scope.Close( retCommRep );
}
Handle<Value> NodeIbapi::Position( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    PositionData newPosition;
    newPosition = obj->m_client.getPosition();

    Handle<Object> retPosition = Object::New();
    retPosition->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newPosition.isValid ) ); 
    retPosition->Set( String::NewSymbol( "account" ),
                  String::New( newPosition.account.c_str() ) ); 
    retPosition->Set( String::NewSymbol( "contract" ),
                  convertContractForNode( newPosition.contract ) ); 
    retPosition->Set( String::NewSymbol( "position" ),
                  Integer::New( newPosition.position ) );
    retPosition->Set( String::NewSymbol( "avgCost" ),
                  Number::New( newPosition.avgCost ) ); 
    return scope.Close( retPosition );
}
Handle<Value> NodeIbapi::PositionEnd( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    PositionEndData newPositionEnd;
    newPositionEnd = obj->m_client.getPositionEnd();

    Handle<Object> retPositionEnd = Object::New();
    retPositionEnd->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newPositionEnd.isValid ) );

    return scope.Close( retPositionEnd );
}
Handle<Value> NodeIbapi::AccountSummary( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    AccountSummaryData newAccountSummary;
    newAccountSummary = obj->m_client.getAccountSummary();

    Handle<Object> retAccountSummary = Object::New();
    retAccountSummary->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newAccountSummary.isValid ) );
    retAccountSummary->Set( String::NewSymbol( "reqId" ),
                  Integer::New( newAccountSummary.reqId ) );
    retAccountSummary->Set( String::NewSymbol( "account" ),
                  String::New( newAccountSummary.account.c_str() ) );
    retAccountSummary->Set( String::NewSymbol( "tag" ),
                  String::New( newAccountSummary.tag.c_str() ) );
    retAccountSummary->Set( String::NewSymbol( "value" ),
                  String::New( newAccountSummary.value.c_str() ) );
    retAccountSummary->Set( String::NewSymbol( "curency" ),
                  String::New( newAccountSummary.curency.c_str() ) );

    return scope.Close( retAccountSummary );
}
Handle<Value> NodeIbapi::AccountSummaryEnd( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );

    AccountSummaryEndData newAcctSumEnd;
    newAcctSumEnd = obj->m_client.getAccountSummaryEnd();

    Handle<Object> retAcctSumEnd = Object::New();
    retAcctSumEnd->Set( String::NewSymbol( "isValid" ),
                  Boolean::New( newAcctSumEnd.isValid ) );
    retAcctSumEnd->Set( String::NewSymbol( "reqId" ),
                  Integer::New( newAcctSumEnd.reqId ) );

    return scope.Close( retAcctSumEnd );
}
Handle<Value> NodeIbapi::VerifyMessageAPI( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    
    VerifyMessageAPIData newVerifyMessageAPI;
    newVerifyMessageAPI = obj->m_client.getVerifyMessageAPI();

    Handle<Object> retVerifyMessageAPI = Object::New();
    retVerifyMessageAPI->Set( String::NewSymbol( "isValid" ),
                        Boolean::New( newVerifyMessageAPI.isValid ) );
    retVerifyMessageAPI->Set( String::NewSymbol( "apiData" ),
                        String::New( newVerifyMessageAPI.apiData.c_str() ) );
    return scope.Close( retVerifyMessageAPI );
}
Handle<Value> NodeIbapi::VerifyCompleted( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    
    VerifyCompletedData newVerifyCompleted;
    newVerifyCompleted = obj->m_client.getVerifyCompleted();

    Handle<Object> retVerifyCompleted = Object::New();
    retVerifyCompleted->Set( String::NewSymbol( "isValid" ),
                        Boolean::New( newVerifyCompleted.isValid ) );
    retVerifyCompleted->Set( String::NewSymbol( "isSuccessful" ),
                        Boolean::New( newVerifyCompleted.isSuccessful ) );
    retVerifyCompleted->Set( String::NewSymbol( "errorText" ),
                        String::New( newVerifyCompleted.errorText.c_str() ) );

    return scope.Close( retVerifyCompleted );
}
Handle<Value> NodeIbapi::DisplayGroupList( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    
    DisplayGroupListData newDisplayGroupList;
    newDisplayGroupList = obj->m_client.getDisplayGroupList();

    Handle<Object> retDisplayGroupList = Object::New();
    retDisplayGroupList->Set( String::NewSymbol( "isValid" ),
                        Boolean::New( newDisplayGroupList.isValid ) );
    retDisplayGroupList->Set( String::NewSymbol( "reqId" ),
                        Integer::New( newDisplayGroupList.reqId ) );
    retDisplayGroupList->Set( String::NewSymbol( "groups" ),
                        String::New( newDisplayGroupList.groups.c_str() ) );

    return scope.Close( retDisplayGroupList );
}
Handle<Value> NodeIbapi::DisplayGroupUpdated( const Arguments &args ) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>( args.This() );
    
    DisplayGroupUpdatedData newDisplayGroupUpdated;
    newDisplayGroupUpdated = obj->m_client.getDisplayGroupUpdated();

    Handle<Object> retDisplayGroupUpdated = Object::New();
    retDisplayGroupUpdated->Set( String::NewSymbol( "isValid" ),
                        Boolean::New( newDisplayGroupUpdated.isValid ) );
    retDisplayGroupUpdated->Set( String::NewSymbol( "reqId" ),
                        Integer::New( newDisplayGroupUpdated.reqId ) );
    retDisplayGroupUpdated->Set( String::NewSymbol( "contractInfo" ),
                String::New( newDisplayGroupUpdated.contractInfo.c_str() ) );

    return scope.Close( retDisplayGroupUpdated );
}



///////////////////////////////////////////////////////////////////////////////
//  Helper methods
///////////////////////////////////////////////////////////////////////////////
// see http://stackoverflow.com/questions/10507323/
//  shortest-way-one-liner-to-get-a-default-argument-out-of-a-v8-function
char *NodeIbapi::getChar( v8::Local<v8::Value> value, const char *fallback ) {
    if ( value->IsString() ) {
        v8::String::AsciiValue string( value );
        char *str  = ( char * ) malloc( string.length() + 1 );
        std::strcpy( str, *string );
        return str;
    }
    char *str = ( char * ) malloc( std::strlen( fallback ) + 1 );
    std::strcpy( str, fallback );
    return str;
}

bool NodeIbapi::isWrongArgNumber( const Arguments &args, int argNum ) {
    if ( args.Length() != argNum ) {
        ThrowException(
            Exception::TypeError(
                String::New( "Wrong number of arguments" ) ) );
        return true;
    }
    return false;
}

bool NodeIbapi::isWrongType( bool predicateRes, int argId ) {
    if ( predicateRes ) {
        std::ostringstream ss;
        ss << "Argument " << argId << " is of wrong type.";
        ThrowException(
            Exception::TypeError(
                String::New( ss.str().c_str() ) ) );
        return true;
    } 
    return false;
}

void NodeIbapi::convertContractForIb( Handle<Object> ibContract, 
                                      Contract &contract ) {
    // checks if order is being submitted through Conract ID from 
    //  contract specification
    contract.conId = ibContract->Get( String::New( "conId" ) )->Int32Value();
    contract.exchange = 
        getChar( ibContract->Get( String::New( "exchange" ) ) );

    contract.symbol = getChar( ibContract->Get( String::New( "symbol" ) ) );
    contract.secType = getChar( ibContract->Get( String::New( "secType" ) ) );
    contract.expiry = getChar( ibContract->Get( String::New( "expiry" ) ) );
    contract.strike = ibContract->Get( String::New( "strike" ) )->NumberValue();
    contract.right = getChar( ibContract->Get( String::New( "right" ) ) );
    contract.multiplier = 
        getChar( ibContract->Get( String::New( "multiplier" ) ) );
    contract.primaryExchange = 
        getChar( ibContract->Get( String::New( "primaryExchange" ) ) );
    contract.currency = getChar( ibContract->Get( String::New( "currency" ) ) );
    contract.localSymbol = 
        getChar( ibContract->Get( String::New( "localSymbol" ) ) );
    contract.tradingClass = 
        getChar( ibContract->Get( String::New( "tradingClass" ) ) );
    contract.includeExpired = 
        ibContract->Get( String::New( "includeExpired" ) )->BooleanValue();
    contract.secIdType = 
        getChar( ibContract->Get( String::New( "secIdType" ) ) );
    contract.secId = getChar( ibContract->Get( String::New( "secId" ) ) );
}

Handle<Object> NodeIbapi::convertContractForNode( Contract &contract ) {
    Handle<Object> retContract = Object::New();
    retContract->Set( String::NewSymbol( "conId" ), 
                      Integer::New( contract.conId ) );
    retContract->Set( String::NewSymbol( "symbol" ),
                      String::New( contract.symbol.c_str() ) );
    retContract->Set( String::NewSymbol( "secType" ),
                      String::New( contract.secType.c_str() ) ); //IBString
    retContract->Set( String::NewSymbol( "expiry" ),
                      String::New( contract.expiry.c_str() ) ); //IBString
    retContract->Set( String::NewSymbol( "strike" ),
                      Number::New( contract.strike ) ); //double
    retContract->Set( String::NewSymbol( "right" ),
                      String::New( contract.right.c_str() ) ); //IBString
    retContract->Set( String::NewSymbol( "multiplier" ),
                      String::New( contract.multiplier.c_str() ) ); //IBString
    retContract->Set( String::NewSymbol( "exchange" ),
                      String::New( contract.exchange.c_str() ) ); //IBString
    retContract->Set( String::NewSymbol( "primaryExchange" ),
                      String::New( contract.primaryExchange.c_str() ) ); //IBString
    retContract->Set( String::NewSymbol( "currency" ),
                      String::New( contract.currency.c_str() ) ); //IBString
    retContract->Set( String::NewSymbol( "localSymbol" ),
                      String::New( contract.localSymbol.c_str() ) ); //IBString
    retContract->Set( String::NewSymbol( "tradingClass" ),
                      String::New( contract.tradingClass.c_str() ) ); //IBString
    retContract->Set( String::NewSymbol( "includeExpired" ),
                      Boolean::New( contract.includeExpired ) ); //bool
    retContract->Set( String::NewSymbol( "secIdType" ),
                      String::New( contract.secIdType.c_str() ) ); //IBString
    retContract->Set( String::NewSymbol( "secId" ),
                      String::New( contract.secId.c_str() ) ); //IBString
    return retContract;
}

void NodeIbapi::convertSubForIb( Handle<Object> scannerSub,
                                 ScannerSubscription &subscription ) {

    subscription.numberOfRows =  
        scannerSub->Get( String::New( "numberOfRows" ) )->Int32Value();
    subscription.abovePrice =  
        scannerSub->Get( String::New( "abovePrice" ) )->NumberValue();
    subscription.belowPrice =  
        scannerSub->Get( String::New( "belowPrice" ) )->NumberValue();
    subscription.aboveVolume =  
        scannerSub->Get( String::New( "aboveVolume" ) )->Int32Value();
    subscription.marketCapAbove = 
        scannerSub->Get( String::New( "marketCapAbove" ) )->NumberValue();
    subscription.marketCapBelow = 
        scannerSub->Get( String::New( "marketCapBelow" ) )->NumberValue();
    subscription.couponRateAbove = 
        scannerSub->Get( String::New( "couponRateAbove" ) )->NumberValue();
    subscription.couponRateBelow = 
        scannerSub->Get( String::New( "couponRateBelow" ) )->NumberValue();

    subscription.instrument = 
        getChar( scannerSub->Get( String::New( "instrument" ) ) );
    subscription.locationCode = 
        getChar( scannerSub->Get( String::New( "locationCode" ) ) );
    subscription.scanCode = 
        getChar( scannerSub->Get( String::New( "scanCode" ) ) );
    subscription.moodyRatingAbove = 
        getChar( scannerSub->Get( String::New( "moodyRatingAbove" ) ) );
    subscription.moodyRatingBelow = 
        getChar( scannerSub->Get( String::New( "moodyRatingBelow" ) ) );
    subscription.spRatingAbove = 
        getChar( scannerSub->Get( String::New( "spRatingAbove" ) ) );
    subscription.spRatingBelow = 
        getChar( scannerSub->Get( String::New( "spRatingBelow" ) ) );
    subscription.maturityDateAbove = 
        getChar( scannerSub->Get( String::New( "maturityDateAbove" ) ) );
    subscription.maturityDateBelow = 
        getChar( scannerSub->Get( String::New( "maturityDateBelow" ) ) );
    subscription.excludeConvertible = 
        scannerSub->Get( String::New( "excludeConvertible" ) )->Int32Value();
    subscription.averageOptionVolumeAbove = 
        scannerSub->Get( String::New( "averageOptionVolumeAbove" ) )->Int32Value();
    subscription.scannerSettingPairs = 
        getChar( scannerSub->Get( String::New( "scannerSettingPairs" ) ) );
    subscription.stockTypeFilter = 
        getChar( scannerSub->Get( String::New( "stockTypeFilter" ) ) );
}

Handle<Object> NodeIbapi::convertContDetailForNode( ContractDetails &contDet ) {
    Handle<Object> retContDet = Object::New();

    retContDet->Set( String::NewSymbol( "summary" ) , 
                     convertContractForNode( contDet.summary ) );
    retContDet->Set( String::NewSymbol( "marketName" ) , 
                     String::New( contDet.marketName.c_str() ) );  
    retContDet->Set( String::NewSymbol( "minTick" ) , 
                     Number::New( contDet.minTick ) );    
    retContDet->Set( String::NewSymbol( "orderTypes" ) , 
                     String::New( contDet.orderTypes.c_str() ) );  
    retContDet->Set( String::NewSymbol( "validExchanges" ) , 
                     String::New( contDet.validExchanges.c_str() ) );  
    retContDet->Set( String::NewSymbol( "priceMagnifier" ) , 
                     Integer::New( contDet.priceMagnifier ) ); ;    
    retContDet->Set( String::NewSymbol( "underConId" ) , 
                     Integer::New( contDet.underConId ) ); ;     
    retContDet->Set( String::NewSymbol( "longName" ) , 
                     String::New( contDet.longName.c_str() ) );  
    retContDet->Set( String::NewSymbol( "contractMonth" ) , 
                     String::New( contDet.contractMonth.c_str() ) );  
    retContDet->Set( String::NewSymbol( "industry" ) , 
                     String::New( contDet.industry.c_str() ) );  
    retContDet->Set( String::NewSymbol( "category" ) , 
                     String::New( contDet.category.c_str() ) );  
    retContDet->Set( String::NewSymbol( "subcategory" ) , 
                     String::New( contDet.subcategory.c_str() ) );  
    retContDet->Set( String::NewSymbol( "timeZoneId" ) , 
                     String::New( contDet.timeZoneId.c_str() ) );  
    retContDet->Set( String::NewSymbol( "tradingHours" ) , 
                     String::New( contDet.tradingHours.c_str() ) );  
    retContDet->Set( String::NewSymbol( "liquidHours" ) , 
                     String::New( contDet.liquidHours.c_str() ) );  
    retContDet->Set( String::NewSymbol( "evRule" ) , 
                     String::New( contDet.evRule.c_str() ) );  
    retContDet->Set( String::NewSymbol( "evMultiplier" ) , 
                     Number::New( contDet.evMultiplier ) ); 

    // Bond values   
    retContDet->Set( String::NewSymbol( "cusip" ) , 
                     String::New( contDet.cusip.c_str() ) );  
    retContDet->Set( String::NewSymbol( "ratings" ) , 
                     String::New( contDet.ratings.c_str() ) );  
    retContDet->Set( String::NewSymbol( "descAppend" ) , 
                     String::New( contDet.descAppend.c_str() ) );  
    retContDet->Set( String::NewSymbol( "bondType" ) , 
                     String::New( contDet.bondType.c_str() ) );  
    retContDet->Set( String::NewSymbol( "couponType" ) , 
                     String::New( contDet.couponType.c_str() ) );  
    retContDet->Set( String::NewSymbol( "callable" ) , 
                     Boolean::New( contDet.callable ) );    
    retContDet->Set( String::NewSymbol( "putable" ) , 
                     Boolean::New( contDet.putable ) );    
    retContDet->Set( String::NewSymbol( "coupon" ) , 
                     Number::New( contDet.coupon ) );    
    retContDet->Set( String::NewSymbol( "convertible" ) , 
                     Boolean::New( contDet.convertible ) );    
    retContDet->Set( String::NewSymbol( "maturity" ) , 
                     String::New( contDet.maturity.c_str() ) );  
    retContDet->Set( String::NewSymbol( "issueDate" ) , 
                     String::New( contDet.issueDate.c_str() ) );  
    retContDet->Set( String::NewSymbol( "nextOptionDate" ) , 
                     String::New( contDet.nextOptionDate.c_str() ) );  
    retContDet->Set( String::NewSymbol( "nextOptionType" ) , 
                     String::New( contDet.nextOptionType.c_str() ) );  
    retContDet->Set( String::NewSymbol( "nextOptionPartial" ) , 
                     Boolean::New( contDet.nextOptionPartial ) );    
    retContDet->Set( String::NewSymbol( "notes" ) , 
                     String::New( contDet.notes.c_str() ) );

    return retContDet;
}

Handle<Object> NodeIbapi::convertExecForNode( Execution &execution ) {
    Handle<Object> retExecution = Object::New();

    retExecution->Set( String::NewSymbol( "execId" ),
                       String::New( execution.execId.c_str() ) );
    retExecution->Set( String::NewSymbol( "time" ),
                       String::New( execution.time.c_str() ) );
    retExecution->Set( String::NewSymbol( "acctNumber" ),
                       String::New( execution.acctNumber.c_str() ) );
    retExecution->Set( String::NewSymbol( "exchange" ),
                       String::New( execution.exchange.c_str() ) );
    retExecution->Set( String::NewSymbol( "side" ),
                       String::New( execution.side.c_str() ) );
    retExecution->Set( String::NewSymbol( "shares" ),
                       Integer::New( execution.shares ) );
    retExecution->Set( String::NewSymbol( "price" ),
                       Number::New( execution.price ) );
    retExecution->Set( String::NewSymbol( "permId" ),
                       Integer::New( execution.permId ) );
    retExecution->Set( String::NewSymbol( "clientId" ),
                       Integer::New( execution.clientId ) );
    retExecution->Set( String::NewSymbol( "orderId" ),
                       Integer::New( execution.orderId ) );
    retExecution->Set( String::NewSymbol( "liquidation" ),
                       Integer::New( execution.liquidation ) );
    retExecution->Set( String::NewSymbol( "cumQty" ),
                       Integer::New( execution.cumQty ) );
    retExecution->Set( String::NewSymbol( "avgPrice" ),
                       Number::New( execution.avgPrice ) );
    retExecution->Set( String::NewSymbol( "orderRef" ),
                       String::New( execution.orderRef.c_str() ) );
    retExecution->Set( String::NewSymbol( "evRule" ),
                       String::New( execution.evRule.c_str() ) );
    retExecution->Set( String::NewSymbol( "evMultiplier" ),
                       Number::New( execution.evMultiplier ) );

    return retExecution;
}

void NodeIbapi::convertOrderForIb( Handle<Object> ibOrder, Order &order ) {
        // order identifier
    order.orderId = ibOrder->Get( String::New( "orderId" ) )->Int32Value();
    order.clientId = ibOrder->Get( String::New( "clientId" ) )->Int32Value();
    order.permId = ibOrder->Get( String::New( "permId" ) )->Int32Value();

    // main order fields
    order.action = getChar( ibOrder->Get( String::New( "action" ) ) );
    order.totalQuantity = ibOrder->Get( String::New( "totalQuantity" ) )->Int32Value();
    order.orderType = getChar( ibOrder->Get( String::New( "orderType" ) ) );
    order.lmtPrice = ibOrder->Get( String::New( "lmtPrice" ) )->NumberValue();
    order.auxPrice = ibOrder->Get( String::New( "auxPrice" ) )->NumberValue();

    // extended order fields
    order.tif = getChar( ibOrder->Get( String::New( "tif" ) ) );
    order.ocaGroup = getChar( ibOrder->Get( String::New( "ocaGroup" ) ) );
    order.ocaType = ibOrder->Get( String::New( "ocaType" ) )->Int32Value();
    order.orderRef = getChar( ibOrder->Get( String::New( "orderRef" ) ) );
    order.transmit = ibOrder->Get( String::New( "transmit" ) )->BooleanValue();
    order.parentId = ibOrder->Get( String::New( "parentId" ) )->Int32Value();
    order.blockOrder = ibOrder->Get( String::New( "blockOrder" ) )->BooleanValue();
    order.sweepToFill = ibOrder->Get( String::New( "sweepToFill" ) )->BooleanValue();
    order.displaySize = ibOrder->Get( String::New( "displaySize" ) )->Int32Value();
    order.triggerMethod = ibOrder->Get( String::New( "triggerMethod" ) )->Int32Value();
    order.outsideRth = ibOrder->Get( String::New( "outsideRth" ) )->BooleanValue();
    order.hidden = ibOrder->Get( String::New( "hidden" ) )->BooleanValue();
    order.goodAfterTime = getChar( ibOrder->Get( String::New( "goodAfterTime" ) ) );
    order.goodTillDate = getChar( ibOrder->Get( String::New( "goodTillDate" ) ) );
    order.rule80A = getChar( ibOrder->Get( String::New( "rule80A" ) ) );
    order.allOrNone = ibOrder->Get( String::New( "allOrNone" ) )->BooleanValue();
    order.minQty = ibOrder->Get( String::New( "minQty" ) )->Int32Value();
    order.percentOffset = ibOrder->Get( String::New( "percentOffset" ) )->NumberValue();
    order.overridePercentageConstraints = ibOrder->Get( String::New( "overridePercentageConstraints" ) )->BooleanValue();
    order.trailStopPrice = ibOrder->Get( String::New( "trailStopPrice" ) )->NumberValue();
    order.trailingPercent = ibOrder->Get( String::New( "trailingPercent" ) )->NumberValue();

    // financial advisors only

    // institutional (ie non-cleared) only

    // SMART routing only
    order.discretionaryAmt = ibOrder->Get( String::New( "discretionaryAmt" ) )->NumberValue();
    order.eTradeOnly = ibOrder->Get( String::New( "eTradeOnly" ) )->BooleanValue();
    order.firmQuoteOnly = ibOrder->Get( String::New( "firmQuoteOnly" ) )->BooleanValue();
    order.nbboPriceCap = ibOrder->Get( String::New( "nbboPriceCap" ) )->NumberValue();
    order.optOutSmartRouting = ibOrder->Get( String::New( "optOutSmartRouting" ) )->BooleanValue();

    // BOX exchange orders only
    order.auctionStrategy = ibOrder->Get( String::New( "auctionStrategy" ) )->Int32Value();
    order.startingPrice = ibOrder->Get( String::New( "startingPrice" ) )->NumberValue();
    order.stockRefPrice = ibOrder->Get( String::New( "stockRefPrice" ) )->NumberValue();
    order.delta = ibOrder->Get( String::New( "delta" ) )->NumberValue();

    // pegged to stock and VOL orders only
    order.stockRangeLower = ibOrder->Get( String::New( "stockRangeLower" ) )->NumberValue();
    order.stockRangeUpper = ibOrder->Get( String::New( "stockRangeUpper" ) )->NumberValue();

    // VOLATILITY ORDERS ONLY
    order.volatility = ibOrder->Get( String::New( "volatility" ) )->NumberValue();
    order.volatilityType = ibOrder->Get( String::New( "volatilityType" ) )->Int32Value();
    order.deltaNeutralOrderType = getChar( ibOrder->Get( String::New( "deltaNeutralOrderType" ) ) );
    order.deltaNeutralAuxPrice = ibOrder->Get( String::New( "deltaNeutralAuxPrice" ) )->NumberValue();
    order.deltaNeutralConId = ibOrder->Get( String::New( "deltaNeutralConId" ) )->Int32Value();
    order.deltaNeutralSettlingFirm = getChar( ibOrder->Get( String::New( "deltaNeutralSettlingFirm" ) ) );
    order.deltaNeutralClearingAccount = getChar( ibOrder->Get( String::New( "deltaNeutralClearingAccount" ) ) );
    order.deltaNeutralClearingIntent = getChar( ibOrder->Get( String::New( "deltaNeutralClearingIntent" ) ) );
    order.deltaNeutralOpenClose = getChar( ibOrder->Get( String::New( "deltaNeutralOpenClose" ) ) );
    order.deltaNeutralShortSale = ibOrder->Get( String::New( "deltaNeutralShortSale" ) )->BooleanValue();
    order.deltaNeutralShortSaleSlot = ibOrder->Get( String::New( "deltaNeutralShortSaleSlot" ) )->Int32Value();
    order.deltaNeutralDesignatedLocation = getChar( ibOrder->Get( String::New( "deltaNeutralDesignatedLocation" ) ) );
    order.continuousUpdate = ibOrder->Get( String::New( "continuousUpdate" ) )->BooleanValue();
    order.referencePriceType = ibOrder->Get( String::New( "referencePriceType" ) )->Int32Value();

    // COMBO ORDERS ONLY

    // SCALE ORDERS ONLY
    order.scaleInitLevelSize = ibOrder->Get( String::New( "scaleInitLevelSize" ) )->Int32Value();
    order.scaleSubsLevelSize = ibOrder->Get( String::New( "scaleSubsLevelSize" ) )->Int32Value();
    order.scalePriceIncrement = ibOrder->Get( String::New( "scalePriceIncrement" ) )->NumberValue();
    order.scalePriceAdjustValue = ibOrder->Get( String::New( "scalePriceAdjustValue" ) )->NumberValue();
    order.scalePriceAdjustInterval = ibOrder->Get( String::New( "scalePriceAdjustInterval" ) )->Int32Value();
    order.scaleProfitOffset = ibOrder->Get( String::New( "scaleProfitOffset" ) )->NumberValue();
    order.scaleAutoReset = ibOrder->Get( String::New( "scaleAutoReset" ) )->BooleanValue();
    order.scaleInitPosition = ibOrder->Get( String::New( "scaleInitPosition" ) )->Int32Value();
    order.scaleInitFillQty = ibOrder->Get( String::New( "scaleInitFillQty" ) )->Int32Value();
    order.scaleRandomPercent = ibOrder->Get( String::New( "scaleRandomPercent" ) )->BooleanValue();

    // HEDGE ORDERS
    order.hedgeType = getChar( ibOrder->Get( String::New( "hedgeType" ) ) );
    order.hedgeParam = getChar( ibOrder->Get( String::New( "hedgeParam" ) ) );

    // Clearing info
    order.account = getChar( ibOrder->Get( String::New( "account" ) ) );
    order.settlingFirm = getChar( ibOrder->Get( String::New( "settlingFirm" ) ) );
    order.clearingAccount = getChar( ibOrder->Get( String::New( "clearingAccount" ) ) );
    order.clearingIntent = getChar( ibOrder->Get( String::New( "clearingIntent" ) ) );

    // ALGO ORDERS ONLY

    // What-if

    // Not Held
}

