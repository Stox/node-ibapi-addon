#ifndef NODEIBAPI_H
#define NODEIBAPI_H

#define IB_USE_STD_STRING

#include <node.h>
#include "IbPosixClient.h"
#include "import/EWrapper.h"

using namespace v8;

class NodeIbapi : public node::ObjectWrap{
public:
    static void Init( Handle<Object> exports );

private:
    NodeIbapi();
    ~NodeIbapi();

    static Handle<Value> New( const Arguments& args );
    static Handle<Value> ProcessMsg( const Arguments& args );

    // Getters
    static Handle<Value> GetNextValidId( const Arguments& args );

    // EClientSocket
    static Handle<Value> Connect( const Arguments& args );
    static Handle<Value> Disconnect( const Arguments& args );
    static Handle<Value> IsConnected( const Arguments& args );
    static Handle<Value> ServerVersion( const Arguments& args );
    static Handle<Value> TwsConnectionTime( const Arguments& args );
    static Handle<Value> ReqMktData( const Arguments& args );
    static Handle<Value> CancelMktData( const Arguments& args );
    static Handle<Value> PlaceOrder( const Arguments& args );
    static Handle<Value> CancelOrder( const Arguments& args );
    static Handle<Value> ReqOpenOrders( const Arguments& args ); 
    static Handle<Value> ReqAccountUpdates( const Arguments& args );
    static Handle<Value> ReqExecutions( const Arguments& args );
    static Handle<Value> ReqIds( const Arguments& args );
    static Handle<Value> CheckMessages( const Arguments& args ); 
    static Handle<Value> ReqContractDetails( const Arguments& args );
    static Handle<Value> ReqMktDepth( const Arguments& args );
    static Handle<Value> CancelMktDepth( const Arguments& args );
    static Handle<Value> ReqNewsBulletins( const Arguments& args );
    static Handle<Value> CancelNewsBulletins( const Arguments& args ); 
    static Handle<Value> SetServerLogLevel( const Arguments& args );
    static Handle<Value> ReqAutoOpenOrders( const Arguments& args );
    static Handle<Value> ReqAllOpenOrders( const Arguments& args ); 
    static Handle<Value> ReqManagedAccts( const Arguments& args ); 
    static Handle<Value> RequestFA( const Arguments& args );
    static Handle<Value> ReplaceFA( const Arguments& args );
    static Handle<Value> ReqHistoricalData( const Arguments& args ); 
    static Handle<Value> ExerciseOptions( const Arguments& args );
    static Handle<Value> CancelHistoricalData( const Arguments& args );
    static Handle<Value> ReqRealTimeBars( const Arguments& args );
    static Handle<Value> CancelRealTimeBars( const Arguments& args );
    static Handle<Value> CancelScannerSubscription( const Arguments& args );
    static Handle<Value> ReqScannerParameters( const Arguments& args ); 
    static Handle<Value> ReqScannerSubscription( const Arguments& args );
    static Handle<Value> ReqCurrentTime( const Arguments& args ); 
    static Handle<Value> ReqFundamentalData( const Arguments& args );
    static Handle<Value> CancelFundamentalData( const Arguments& args );
    static Handle<Value> CalculateImpliedVolatility( const Arguments& args );
    static Handle<Value> CalculateOptionPrice( const Arguments& args );
    static Handle<Value> CancelCalculateImpliedVolatility( const Arguments& args );
    static Handle<Value> CancelCalculateOptionPrice( const Arguments& args );
    static Handle<Value> ReqGlobalCancel( const Arguments& args ); 
    static Handle<Value> ReqMarketDataType( const Arguments& args );
    static Handle<Value> ReqPositions( const Arguments& args ); 
    static Handle<Value> CancelPositions( const Arguments& args ); 
    static Handle<Value> ReqAccountSummary( const Arguments& args ); 
    static Handle<Value> CancelAccountSummary( const Arguments& args );
    static Handle<Value> VerifyRequest( const Arguments& args );
    static Handle<Value> VerifyMessage( const Arguments& args );
    static Handle<Value> QueryDisplayGroups( const Arguments& args );
    static Handle<Value> SubscribeToGroupEvents( const Arguments& args );
    static Handle<Value> UpdateDisplayGroup( const Arguments& args );
    static Handle<Value> UnsubscribeFromGroupEvents( const Arguments& args );


    // events
    static Handle<Value> TickPrice( const Arguments& args );
    static Handle<Value> TickSize( const Arguments& args );
    static Handle<Value> TickOptionComputation( const Arguments& args );
    static Handle<Value> TickGeneric( const Arguments& args );
    static Handle<Value> TickString( const Arguments& args );
    static Handle<Value> TickEFP( const Arguments& args );
    static Handle<Value> OrderStatus( const Arguments& args );
    static Handle<Value> OpenOrder( const Arguments& args );
    static Handle<Value> OpenOrderEnd( const Arguments& args );
    static Handle<Value> WinError( const Arguments& args );
    static Handle<Value> ConnectionClosed( const Arguments& args );
    static Handle<Value> UpdateAccountValue( const Arguments& args );
    static Handle<Value> UpdatePortfolio( const Arguments& args );
    static Handle<Value> UpdateAccountTime( const Arguments& args );
    static Handle<Value> AccountDownloadEnd( const Arguments& args );
    static Handle<Value> NextValidId( const Arguments& args );
    static Handle<Value> GetContractDetails( const Arguments& args );
    static Handle<Value> BondContractDetails( const Arguments& args );
    static Handle<Value> ContractDetailsEnd( const Arguments& args );
    static Handle<Value> ExecDetails( const Arguments& args );
    static Handle<Value> ExecDetailsEnd( const Arguments& args );
    static Handle<Value> Error( const Arguments& args );
    static Handle<Value> UpdateMktDepth( const Arguments& args );
    static Handle<Value> UpdateMktDepthL2( const Arguments& args );
    static Handle<Value> UpdateNewsBulletin( const Arguments& args );
    static Handle<Value> ManagedAccounts( const Arguments& args );
    static Handle<Value> ReceiveFA( const Arguments& args );
    static Handle<Value> HistoricalData( const Arguments& args );
    static Handle<Value> ScannerParameters( const Arguments& args );
    static Handle<Value> ScannerData( const Arguments& args );
    static Handle<Value> ScannerDataEnd( const Arguments& args );
    static Handle<Value> RealtimeBar( const Arguments& args );
    // static Handle<Value> CurrentTime( const Arguments& args );
    static Handle<Value> FundamentalData( const Arguments& args );
    static Handle<Value> DeltaNeutralValidation( const Arguments& args );
    static Handle<Value> TickSnapshotEnd( const Arguments& args );
    static Handle<Value> MarketDataType( const Arguments& args );
    static Handle<Value> CommissionReport( const Arguments& args );
    static Handle<Value> Position( const Arguments& args );
    static Handle<Value> PositionEnd( const Arguments& args );
    static Handle<Value> AccountSummary( const Arguments& args );
    static Handle<Value> AccountSummaryEnd( const Arguments& args );
    static Handle<Value> VerifyMessageAPI( const Arguments& args );
    static Handle<Value> VerifyCompleted( const Arguments& args );
    static Handle<Value> DisplayGroupList( const Arguments& args );
    static Handle<Value> DisplayGroupUpdated( const Arguments& args );

private:
    static char *getChar( Local<Value> value, const char *fallback = "" );

    static bool isWrongArgNumber( const Arguments& args, int argNum );
    static bool isWrongType( bool predicateRes, int argId );
    static void convertContractForIb( Handle<Object> ibContract, 
                                      Contract &contract );
    static Handle<Object> convertContractForNode( Contract &contract );
    static void convertSubForIb( Handle<Object> scannerSub, 
                                 ScannerSubscription &subscription );
    static Handle<Object> convertContDetailForNode( ContractDetails &contDet );
    static Handle<Object> convertExecForNode( Execution &execution );
    static void convertOrderForIb( Handle<Object> ibOrder, Order &order );

    IbPosixClient m_client;

};

#endif