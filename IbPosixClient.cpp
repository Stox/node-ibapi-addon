
#define IB_USE_STD_STRING

#include <iostream>

#include "IbPosixClient.h"

#include "import/EPosixClientSocket.h"
#include "import/EPosixClientSocketPlatform.h"

#include "import/Contract.h"
#include "import/Order.h"

IbPosixClient::IbPosixClient()
    : m_pClient( new EPosixClientSocket( this ) )
{
}

IbPosixClient::~IbPosixClient() 
{
}

/////////////////// Custom functions for node access //////////////////////////
bool IbPosixClient::connect( const char *host, unsigned int port, 
                             int clientId ) {
    bool isConnected = m_pClient->eConnect( host, port, clientId );
    return isConnected;
}

void IbPosixClient::disconnect() const {
    m_pClient->eDisconnect();
}

bool IbPosixClient::isConnected() const {
    return m_pClient->isConnected();
}

void IbPosixClient::processMessages() {
    fd_set readfds, writefds, errorfds;

    struct timeval tval;
    tval.tv_usec = 0;
    tval.tv_sec = 0;
    time_t now = time( NULL );

    if( m_pClient->fd() >= 0 ) {
        FD_ZERO( &readfds );
        errorfds = writefds = readfds;
        FD_SET( m_pClient->fd(), &readfds );

        if( !m_pClient->isOutBufferEmpty() )
            FD_SET( m_pClient->fd(), &writefds );

        FD_CLR( m_pClient->fd(), &errorfds );
        int ret = select( m_pClient->fd() + 1, &readfds, &writefds, &errorfds, 
                          &tval );
        
        if( ret == 0 ) // timeout
            return;
        if( ret < 0 ) // error
            disconnect();
            return;
        if( m_pClient->fd() < 0 )
            return;
        if ( FD_ISSET( m_pClient->fd(), &errorfds ) ) 
            m_pClient->onError();
        if( m_pClient->fd() < 0 )
            return;
        if ( FD_ISSET( m_pClient->fd(), &writefds ) ) 
            m_pClient->onSend();
        if( m_pClient->fd() < 0 )
            return;
        if ( FD_ISSET( m_pClient->fd(), &readfds ) ) 
            m_pClient->onReceive();
    }
}


/////////////////// API EPosixClientSocket method for node access /////////////
int IbPosixClient::serverVersion() {
    return m_pClient->serverVersion();
}
IBString IbPosixClient::TwsConnectionTime() {
    return m_pClient->TwsConnectionTime();
}
void IbPosixClient::reqMktData( TickerId tickerId, const Contract &contract, 
                                const IBString &genericTick, bool snapShot,
                                const TagValueListSPtr& mktDataOptions ) {
    m_pClient->reqMktData( tickerId, contract, genericTick, snapShot,
                            mktDataOptions );
}
void IbPosixClient::cancelMktData( TickerId tickerId ) {
    m_pClient->cancelMktData(tickerId);
}
void IbPosixClient::placeOrder( 
    OrderId id, const Contract &contract, const Order &order ) {
    m_pClient->placeOrder( id, contract, order );
}
void IbPosixClient::cancelOrder( OrderId orderId ) {
    m_pClient->cancelOrder( orderId );
}
void IbPosixClient::reqOpenOrders() {
    m_pClient->reqOpenOrders();
}
void IbPosixClient::reqAccountUpdates( bool subscribe, 
                                       const IBString& acctCode ) {
    m_pClient->reqAccountUpdates( subscribe, acctCode );
}
void IbPosixClient::reqExecutions( int reqId, const ExecutionFilter& filter ) {
    m_pClient->reqExecutions( reqId, filter );
}
void IbPosixClient::reqIds( int numIds ) {
    m_pClient->reqIds( numIds );
}
bool IbPosixClient::checkMessages(){
    return m_pClient->checkMessages();
}
void IbPosixClient::reqContractDetails( int reqId, const Contract &contract ) {
    m_pClient->reqContractDetails( reqId, contract );
}
void IbPosixClient::reqMktDepth( TickerId tickerId, const Contract &contract, 
                                 int numRows, 
                                 const TagValueListSPtr& mktDepthOptions ) {
    m_pClient->reqMktDepth( tickerId, contract, numRows, mktDepthOptions );
}
void IbPosixClient::cancelMktDepth( TickerId tickerId ) {
    m_pClient->cancelMktDepth( tickerId );
}
void IbPosixClient::reqNewsBulletins( bool allMsgs ) {
    m_pClient->reqNewsBulletins( allMsgs );
}
void IbPosixClient::cancelNewsBulletins() {
    m_pClient->cancelNewsBulletins();
}
void IbPosixClient::setServerLogLevel( int level ) {
    m_pClient->setServerLogLevel( level );
}

void IbPosixClient::reqAutoOpenOrders( bool bAutoBind ) {
    m_pClient->reqAutoOpenOrders( bAutoBind );
}
void IbPosixClient::reqAllOpenOrders() {
    m_pClient->reqAllOpenOrders();
}
void IbPosixClient::reqManagedAccts() {
    m_pClient->reqManagedAccts();
}
void IbPosixClient::requestFA( faDataType pFaDataType ) {
    m_pClient->requestFA( pFaDataType );
}
void IbPosixClient::replaceFA( faDataType pFaDataType, const IBString& cxml ) {
    m_pClient->replaceFA( pFaDataType, cxml );
}
void IbPosixClient::reqHistoricalData( TickerId id, const Contract &contract, 
                                       const IBString &endDateTime, 
                                       const IBString &durationStr, 
                                       const IBString &barSizeSetting, 
                                       const IBString &whatToShow, 
                                       int useRTH, int formatDate,
                                       const TagValueListSPtr& chartOptions ) {
    m_pClient->reqHistoricalData( id, contract, endDateTime, durationStr, 
                                  barSizeSetting, whatToShow, useRTH, 
                                  formatDate, chartOptions );
}
void IbPosixClient::exerciseOptions( TickerId tickerId, 
                                     const Contract &contract, 
                                     int exerciseAction, int exerciseQuantity, 
                                     const IBString &account, int override ) {
    m_pClient->exerciseOptions( tickerId, contract, exerciseAction, 
                                exerciseQuantity, account, override );
}
void IbPosixClient::cancelHistoricalData( TickerId tickerId ) {
    m_pClient->cancelHistoricalData( tickerId );
}
void IbPosixClient::reqRealTimeBars( TickerId id, const Contract &contract, 
                                     int barSize, const IBString &whatToShow, 
                                     bool useRTH,
                                     const TagValueListSPtr& realTimeBarsOptions
                                      ) {
    m_pClient->reqRealTimeBars( id, contract, barSize, whatToShow, useRTH,
                                realTimeBarsOptions );
}
void IbPosixClient::cancelRealTimeBars( TickerId tickerId ) {
    m_pClient->cancelRealTimeBars( tickerId );
}
void IbPosixClient::cancelScannerSubscription( int tickerId ) {
    m_pClient->cancelScannerSubscription( tickerId );
}
void IbPosixClient::reqScannerParameters() {
    m_pClient->reqScannerParameters();
}
void IbPosixClient::reqScannerSubscription( int tickerId, 
                        const ScannerSubscription &subscription,
                        const TagValueListSPtr& scannerSubscriptionOptions ) {
    m_pClient->reqScannerSubscription( tickerId, subscription,
                                        scannerSubscriptionOptions );
}
void IbPosixClient::reqCurrentTime() {
    m_pClient->reqCurrentTime();
}
void IbPosixClient::reqFundamentalData( TickerId reqId, 
                                        const Contract &contract, 
                                        const IBString &reportType ) {
    m_pClient->reqFundamentalData( reqId, contract, reportType );
}
void IbPosixClient::cancelFundamentalData( TickerId reqId ) {
    m_pClient->cancelFundamentalData( reqId );
}
void IbPosixClient::calculateImpliedVolatility( TickerId reqId, 
                                                const Contract &contract, 
                                                double optionPrice, 
                                                double underPrice ) {
    m_pClient->calculateImpliedVolatility( reqId, contract, optionPrice, 
                                           underPrice );
}
void IbPosixClient::calculateOptionPrice( TickerId reqId, 
                                          const Contract &contract, 
                                          double volatility, 
                                          double underPrice ) {
    m_pClient->calculateOptionPrice( reqId, contract, volatility, underPrice );
}
void IbPosixClient::cancelCalculateImpliedVolatility( TickerId reqId ) {
    m_pClient->cancelCalculateImpliedVolatility( reqId );
}
void IbPosixClient::cancelCalculateOptionPrice( TickerId reqId ) {
    m_pClient->cancelCalculateOptionPrice( reqId );
}
void IbPosixClient::reqGlobalCancel() {
    m_pClient->reqGlobalCancel();
}
void IbPosixClient::reqMarketDataType( int marketDataType ) {
    m_pClient->reqMarketDataType( marketDataType );
}
void IbPosixClient::reqPositions() {
    m_pClient->reqPositions();
}
void IbPosixClient::cancelPositions() {
    m_pClient->cancelPositions();
}
void IbPosixClient::reqAccountSummary( int reqId, const IBString& groupName, 
                                       const IBString& tags ) {
    m_pClient->reqAccountSummary( reqId, groupName, tags );
}
void IbPosixClient::cancelAccountSummary( int reqId ) {
    m_pClient->cancelAccountSummary( reqId );
}
void IbPosixClient::verifyRequest( const IBString& apiName, 
                                   const IBString& apiVersion ) {
    m_pClient->verifyRequest( apiName, apiVersion );
}
void IbPosixClient::verifyMessage( const IBString& apiData) {
    m_pClient->verifyMessage( apiData );
}
void IbPosixClient::queryDisplayGroups( int reqId ) {
    m_pClient->queryDisplayGroups( reqId );
}
void IbPosixClient::subscribeToGroupEvents( int reqId, int groupId ) {
    m_pClient->subscribeToGroupEvents( reqId, groupId );
}
void IbPosixClient::updateDisplayGroup( int reqId, 
                                        const IBString& contractInfo ) {
    m_pClient->updateDisplayGroup( reqId, contractInfo );
}
void IbPosixClient::unsubscribeFromGroupEvents( int reqId ) {
    m_pClient->unsubscribeFromGroupEvents( reqId );
}


/////////////////// API EWrapper event methods ////////////////////////////////

void IbPosixClient::tickPrice( TickerId tickerId, TickType field, double price,
                               int canAutoExecute ) {
    TickPriceData newData;
    newData.isValid = true;
    newData.tickerId = tickerId;
    newData.field = field;
    newData.price = price;
    newData.canAutoExecute = canAutoExecute;
    this->m_tickPrices.push( newData );
}
void IbPosixClient::tickSize( TickerId tickerId, TickType field, int size ) {
    TickSizeData newData;
    newData.isValid = true;
    newData.tickerId = tickerId;
    newData.field = field;
    newData.size = size;
    this->m_tickSizes.push( newData );
}
// TODO NOT TESTED
void IbPosixClient::tickOptionComputation( TickerId tickerId, 
                                           TickType tickType, 
                                           double impliedVol, double delta, 
                                           double optPrice, double pvDividend, 
                                           double gamma, double vega, 
                                           double theta, double undPrice ) {
    TickOptionComputationData newData;
    newData.isValid = true;
    newData.tickerId = tickerId;
    newData.tickType = tickType;
    newData.impliedVol = impliedVol;
    newData.delta = delta;
    newData.optPrice = optPrice;
    newData.pvDividend = pvDividend;
    newData.gamma = gamma;
    newData.vega = vega;
    newData.theta = theta;
    newData.undPrice = undPrice;
    this->m_tickOptionComps.push( newData );
}
// TODO NOT TESTED
void IbPosixClient::tickGeneric( TickerId tickerId, TickType tickType, 
                                 double value ) {
    TickGenericData newData;
    newData.isValid = true;
    newData.tickerId = tickerId;
    newData.tickType = tickType;
    newData.value = value;
    this->m_tickGenerics.push( newData );
}
// TODO NOT TESTED
void IbPosixClient::tickString( TickerId tickerId, TickType tickType, 
                                const IBString& value ) {
    TickStringData newData;
    newData.isValid = true;
    newData.tickerId = tickerId;
    newData.tickType = tickType;
    newData.value = value;
    this->m_tickStrings.push( newData );
}
// TODO NOT TESTED
void IbPosixClient::tickEFP( TickerId tickerId, TickType tickType, 
                             double basisPoints, 
                             const IBString& formattedBasisPoints, 
                             double totalDividends, int holdDays, 
                             const IBString& futureExpiry, 
                             double dividendImpact, 
                             double dividendsToExpiry ) {
    TickEFPData newData;
    newData.isValid = true;
    newData.tickerId = tickerId;
    newData.tickType = tickType;
    newData.basisPoints = basisPoints;
    newData.formattedBasisPoints = formattedBasisPoints;
    newData.totalDividends = totalDividends;
    newData.holdDays = holdDays;
    newData.futureExpiry = futureExpiry;
    newData.dividendImpact = dividendImpact;
    newData.dividendsToExpiry = dividendsToExpiry;
    this->m_tickEFPs.push( newData );
}
// TODO NOT TESTED
void IbPosixClient::orderStatus( OrderId orderId, const IBString &status, 
                                 int filled, int remaining, 
                                 double avgFillPrice, int permId, int parentId,
                                 double lastFillPrice, int clientId, 
                                 const IBString& whyHeld ) {
    OrderStatusData newData;
    newData.isValid = true;
    newData.orderId = orderId;
    newData.status = status;
    newData.filled = filled;
    newData.remaining = remaining;
    newData.avgFillPrice = avgFillPrice;
    newData.permId = permId;
    newData.parentId = parentId;
    newData.lastFillPrice = lastFillPrice;
    newData.clientId = clientId;
    newData.whyHeld = whyHeld;
    this->m_orderStatuses.push( newData );
}
// No idea how to handle contract and order
void IbPosixClient::openOrder( OrderId orderId, const Contract&, const Order&, 
                               const OrderState& ostate ) {
    OpenOrderData newData;
    newData.isValid = true;
    newData.orderId = orderId;
    newData.orderState = ostate;
    this->m_openOrders.push( newData );
}
void IbPosixClient::openOrderEnd() {
    OpenOrderEndData newData;
    newData.isValid = true;
    this->m_openOrderEnd.push( newData );
}
void IbPosixClient::winError( const IBString &str, int lastError ) {
    WinErrorData newData;
    newData.isValid = true;
    newData.str = str;
    newData.lastError = lastError;
    this->m_winErrors.push( newData );
}
void IbPosixClient::connectionClosed() {
    ConnectionClosedData newData;
    newData.isValid = true;
    this->m_connectionClosed.push( newData );
}
void IbPosixClient::updateAccountValue( const IBString& key, 
                                        const IBString& val,
                                        const IBString& currency, 
                                        const IBString& accountName ) {
    UpdateAccountValueData newData;
    newData.isValid = true;
    newData.key = key;
    newData.val = val;
    newData.currency = currency;
    newData.accountName = accountName;
    this->m_updateAccountValues.push( newData );
}
void IbPosixClient::updatePortfolio( const Contract& contract, int position, 
                                     double marketPrice, double marketValue,
                                     double averageCost, double unrealizedPNL,
                                     double realizedPNL, 
                                     const IBString& accountName ) {
    UpdatePortfolioData newData;
    newData.isValid = true;
    newData.contract = contract;
    newData.position = position;
    newData.marketPrice = marketPrice;
    newData.marketValue = marketValue;
    newData.averageCost = averageCost;
    newData.unrealizedPNL = unrealizedPNL;
    newData.realizedPNL = realizedPNL;
    newData.accountName = accountName;
    this->m_updatePortfolios.push( newData );
}
void IbPosixClient::updateAccountTime( const IBString& timeStamp ) {
    UpdateAccountTimeData newData;
    newData.isValid = true;
    newData.timeStamp = timeStamp;
    this->m_updateAccountTimes.push( newData );
}
void IbPosixClient::accountDownloadEnd( const IBString& accountName ) {
    AccountDownloadEndData newData;
    newData.isValid = true;
    newData.accountName = accountName;
    this->m_accountDownloadEnds.push( newData );
}
void IbPosixClient::nextValidId( OrderId orderId ) {
    NextValidIdData newData;
    newData.isValid = true;
    newData.orderId = orderId;
    this->m_validId.push( newData );
}
void IbPosixClient::contractDetails( int reqId, 
                                     const ContractDetails& contractDetails ) {
    ContractDetailsData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    newData.contractDetails = contractDetails;
    this->m_contractDetails.push( newData );
}
void IbPosixClient::bondContractDetails( int reqId, 
                                      const ContractDetails& contractDetails ) {
    BondContractDetailsData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    newData.contractDetails = contractDetails;
    this->m_bondContractDetails.push( newData );
}
void IbPosixClient::contractDetailsEnd( int reqId ) {
    ContractDetailsEndData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    this->m_contractDetailsEnd.push( newData );
}
void IbPosixClient::execDetails( int reqId, const Contract& contract, 
                                 const Execution& execution ) {
    ExecDetailsData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    newData.contract = contract;
    newData.execution = execution;
    this->m_execDetails.push( newData );
}
void IbPosixClient::execDetailsEnd( int reqId ) {
    ExecDetailsEndData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    this->m_execDetailsEnd.push( newData );
}
void IbPosixClient::error( const int id, const int errorCode, 
                           const IBString errorString ) {
    ErrorData newData;
    newData.isValid = true;
    newData.id = id;
    newData.errorCode = errorCode;
    newData.errorString = errorString;
    this->m_errors.push( newData );
    if ( id == -1 && errorCode == 1100 )
        disconnect();
}
void IbPosixClient::updateMktDepth( TickerId id, int position, int operation, 
                                    int side, double price, int size ) {
    UpdateMktDepthData newData;
    newData.isValid = true;
    newData.id = id;
    newData.position = position;
    newData.operation = operation;
    newData.side = side;
    newData.price = price;
    newData.size = size;
    this->m_updateMktDepths.push( newData );
}
void IbPosixClient::updateMktDepthL2( TickerId id, int position, 
                                      IBString marketMaker, int operation, 
                                      int side, double price, int size ) {
    UpdateMktDepthL2Data newData;
    newData.isValid = true;
    newData.id = id;
    newData.position = position;
    newData.marketMaker = marketMaker;
    newData.operation = operation;
    newData.side = side;
    newData.price = price;
    newData.size = size;
    this->m_updateMktDepthL2s.push( newData );
}
void IbPosixClient::updateNewsBulletin( int msgId, int msgType, 
                                        const IBString& newsMessage, 
                                        const IBString& originExch ) {
    UpdateNewsBulletinData newData;
    newData.isValid = true;
    newData.msgId = msgId;
    newData.msgType = msgType;
    newData.newsMessage = newsMessage;
    newData.originExch = originExch;
    this->m_updateNewsBulletins.push( newData );
}
void IbPosixClient::managedAccounts( const IBString& accountsList ) {
    ManagedAccountsData newData;
    newData.isValid = true;
    newData.accountsList = accountsList;
    this->m_managedAccounts.push( newData );
}
void IbPosixClient::receiveFA( faDataType pFaDataType, const IBString& cxml ) {
    ReceiveFAData newData;
    newData.isValid = true;
    newData.pFaDataType = pFaDataType;
    newData.cxml = cxml;
    this->m_receiveFAs.push( newData );
}
void IbPosixClient::historicalData( TickerId reqId, const IBString& date, 
                                    double open, double high, double low, 
                                    double close, int volume, int barCount, 
                                    double WAP, int hasGaps ) {
    HistoricalDataData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    newData.date = date;
    newData.open = open;
    newData.high = high;
    newData.low = low;
    newData.close = close;
    newData.volume = volume;
    newData.barCount = barCount;
    newData.WAP = WAP;
    newData.hasGaps = hasGaps;
    this->m_historicalData.push( newData );
}
void IbPosixClient::scannerParameters( const IBString &xml ) {
    ScannerParametersData newData;
    newData.isValid = true;
    newData.xml = xml;
    this->m_scannerParameters.push( newData );
}
void IbPosixClient::scannerData( int reqId, int rank, 
                                 const ContractDetails &contractDetails, 
                                 const IBString &distance, 
                                 const IBString &benchmark, 
                                 const IBString &projection, 
                                 const IBString &legsStr ) {
    ScannerDataData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    newData.rank = rank;
    newData.contractDetails = contractDetails;
    newData.distance = distance;
    newData.benchmark = benchmark;
    newData.projection = projection;
    newData.legsStr = legsStr;
    this->m_scannerData.push( newData );
}
void IbPosixClient::scannerDataEnd( int reqId ) {
    ScannerDataEndData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    this->m_scannerDataEnd.push( newData );
}
void IbPosixClient::realtimeBar( TickerId reqId, long itime, double open, 
                                 double high, double low, double close, 
                                 long volume, double wap, int count ) {
    RealtimeBarData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    newData.time = itime;
    newData.open = open;
    newData.high = high;
    newData.low = low;
    newData.close = close;
    newData.volume = volume;
    newData.wap = wap;
    newData.count = count;
    this->m_realtimeBars.push( newData );
}
void IbPosixClient::currentTime( long time ) {
    time_t t = ( time_t )time;
    struct tm * timeinfo = localtime ( &t );
    // this->m_currentTime.clear();
    std::string currTime( asctime( timeinfo ) );
    // this->m_currentTime.append( currTime );
    time_t now = ::time( NULL );
}
void IbPosixClient::fundamentalData( TickerId reqId, const IBString& data ) {
    FundamentalDataData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    newData.data = data;
    this->m_fundamentalData.push( newData );
}
void IbPosixClient::deltaNeutralValidation( int reqId, 
                                            const UnderComp& underComp ) {
    DeltaNeutralValidationData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    newData.underComp = underComp;
    this->m_deltaNeutralValidations.push( newData );
}
void IbPosixClient::tickSnapshotEnd( int reqId ) {
    TickSnapshotEndData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    this->m_tickSnapshotEnds.push( newData );
}
void IbPosixClient::marketDataType( TickerId reqId, int marketDataType ) {
    MarketDataTypeData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    newData.marketDataType = marketDataType;
    this->m_marketDataTypes.push( newData );
}
void IbPosixClient::commissionReport( 
        const CommissionReport& commissionReport ) {
    CommissionReportData newData;
    newData.isValid = true;
    newData.commissionReport = commissionReport;
    this->m_commissionReports.push( newData );
}
void IbPosixClient::position( const IBString& account, 
                              const Contract& contract, int position,
                              double avgCost ) {
    PositionData newData;
    newData.isValid = true;
    newData.account = account;
    newData.contract = contract;
    newData.position = position;
    newData.avgCost = avgCost;
    this->m_positions.push( newData );
}
void IbPosixClient::positionEnd() {
    PositionEndData newData;
    newData.isValid = true;
    this->m_positionEnd.push( newData );
}
void IbPosixClient::accountSummary( int reqId, const IBString& account, 
                                    const IBString& tag, const IBString& value,
                                    const IBString& curency ) {
    AccountSummaryData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    newData.account = account;
    newData.tag = tag;
    newData.value = value;
    newData.curency = curency;
    this->m_accountSummaries.push( newData );
}
void IbPosixClient::accountSummaryEnd( int reqId ) {
    AccountSummaryEndData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    this->m_accountSummaryEnd.push( newData );
}
void IbPosixClient::verifyMessageAPI( const IBString& apiData ) {
    VerifyMessageAPIData newData;
    newData.isValid = true;
    newData.apiData = apiData;
    this->m_verifyMessageAPIs.push( newData );
}
void IbPosixClient::verifyCompleted( bool isSuccessful, const IBString& errorText) {
    VerifyCompletedData newData;
    newData.isValid = true;
    newData.isSuccessful = isSuccessful;
    newData.errorText = errorText;
    this->m_verifyCompleted.push( newData );
}
void IbPosixClient::displayGroupList( int reqId, const IBString& groups) {
    DisplayGroupListData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    newData.groups = groups;
    this->m_displayGroupLists.push( newData );
}
void IbPosixClient::displayGroupUpdated( int reqId, const IBString& contractInfo) {
    DisplayGroupUpdatedData newData;
    newData.isValid = true;
    newData.reqId = reqId;
    newData.contractInfo = contractInfo;
    this->m_displayGroupUpdated.push( newData );
}

TickPriceData IbPosixClient::getTickPrice() {
    TickPriceData popped;
    if ( !this->m_tickPrices.empty() ) {
        popped = this->m_tickPrices.front();
        this->m_tickPrices.pop();
        return popped;
    }
    popped.isValid = false;
    return popped; 
}
TickSizeData IbPosixClient::getTickSize() {
    TickSizeData popped;
    if ( !this->m_tickSizes.empty() ) {
        popped = this->m_tickSizes.front();
        this->m_tickSizes.pop();
        return popped;
    }
    popped.isValid = false;
    return popped; 
}
TickOptionComputationData IbPosixClient::getTickOptionComputation() {
    TickOptionComputationData popped;
    if ( !this->m_tickOptionComps.empty() ) {
        popped = this->m_tickOptionComps.front();
        this->m_tickOptionComps.pop();
        return popped;
    }
    popped.isValid = false;
    return popped; 
}
TickGenericData IbPosixClient::getTickGeneric() {
    TickGenericData popped;
    if ( !this->m_tickGenerics.empty() ) {
        popped = this->m_tickGenerics.front();
        this->m_tickGenerics.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;     
}
TickStringData IbPosixClient::getTickString() {
    TickStringData popped;
    if ( !this->m_tickStrings.empty() ) {
        popped = this->m_tickStrings.front();
        this->m_tickStrings.pop();
        return popped;
    }
    popped.isValid = false;
    return popped; 
}
TickEFPData IbPosixClient::getTickEFP() {
    TickEFPData popped;
    if ( !this->m_tickEFPs.empty() ) {
        popped = this->m_tickEFPs.front();
        this->m_tickEFPs.pop();
        return popped;
    }
    popped.isValid = false;
    return popped; 
}
OrderStatusData IbPosixClient::getOrderStatus() {
    OrderStatusData popped;
    if ( !this->m_orderStatuses.empty() ) {
        popped = this->m_orderStatuses.front();
        this->m_orderStatuses.pop();
        return popped;
    }
    popped.isValid = false;
    return popped; 
}
OpenOrderData IbPosixClient::getOpenOrder() {
    OpenOrderData popped;
    if ( !this->m_openOrders.empty() ) {
        popped = this->m_openOrders.front();
        this->m_openOrders.pop();
        return popped;
    }
    popped.isValid = false;
    return popped; 
}
OpenOrderEndData IbPosixClient::getOpenOrderEnd() {
    OpenOrderEndData popped;
    if ( !this->m_openOrderEnd.empty() ) {
        popped = this->m_openOrderEnd.front();
        this->m_openOrderEnd.pop();
        return popped;
    }
    popped.isValid = false;
    return popped; 
}
WinErrorData IbPosixClient::getWinError() {
    WinErrorData popped;
    if ( !this->m_winErrors.empty() ) {
        popped = this->m_winErrors.front();
        this->m_winErrors.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
ConnectionClosedData IbPosixClient::getConnectionClosed() {
    ConnectionClosedData popped;
    if ( !this->m_connectionClosed.empty() ) {
        popped = this->m_connectionClosed.front();
        this->m_connectionClosed.pop();
        return popped;
    }
    popped.isValid = false;
    return popped; 
}
UpdateAccountValueData IbPosixClient::getUpdateAccountValue() {
    UpdateAccountValueData popped;
    if ( !this->m_updateAccountValues.empty() ) {
        popped = this->m_updateAccountValues.front();
        this->m_updateAccountValues.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
UpdatePortfolioData IbPosixClient::getUpdatePortfolio() {
    UpdatePortfolioData popped;
    if ( !this->m_updatePortfolios.empty() ) {
        popped = this->m_updatePortfolios.front();
        this->m_updatePortfolios.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
UpdateAccountTimeData IbPosixClient::getUpdateAccountTime() {
    UpdateAccountTimeData popped;
    if ( !this->m_updateAccountTimes.empty() ) {
        popped = this->m_updateAccountTimes.front();
        this->m_updateAccountTimes.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
AccountDownloadEndData IbPosixClient::getAccountDownloadEnd() {
    AccountDownloadEndData popped;
    if ( !this->m_accountDownloadEnds.empty() ) {
        popped = this->m_accountDownloadEnds.front();
        this->m_accountDownloadEnds.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
NextValidIdData IbPosixClient::getNextValidId() {
    NextValidIdData popped;
    if ( !this->m_validId.empty() ) {
        popped = this->m_validId.front();
        this->m_validId.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
ContractDetailsData IbPosixClient::getContractDetails() {
    ContractDetailsData popped;   
    if ( !this->m_contractDetails.empty() ) {
        popped = this->m_contractDetails.front();
        this->m_contractDetails.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
BondContractDetailsData IbPosixClient::getBondContractDetails() {
    BondContractDetailsData popped;
    if ( !this->m_bondContractDetails.empty() ) {
        popped = this->m_bondContractDetails.front();
        this->m_bondContractDetails.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
ContractDetailsEndData IbPosixClient::getContractDetailsEnd() {
    ContractDetailsEndData popped;
    if ( !this->m_contractDetailsEnd.empty() ) {
        popped = this->m_contractDetailsEnd.front();
        this->m_contractDetailsEnd.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
ExecDetailsData IbPosixClient::getExecDetails() {
    ExecDetailsData popped;
    if ( !this->m_execDetails.empty() ) {
        popped = this->m_execDetails.front();
        this->m_execDetails.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
ExecDetailsEndData IbPosixClient::getExecDetailsEnd() {
    ExecDetailsEndData popped;
    if ( !this->m_execDetailsEnd.empty() ) {
        popped = this->m_execDetailsEnd.front();
        this->m_execDetailsEnd.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
ErrorData IbPosixClient::getError() {
    ErrorData popped;
    if ( !this->m_errors.empty() ) {
        popped = this->m_errors.front();
        this->m_errors.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
UpdateMktDepthData IbPosixClient::getUpdateMktDepth() {
    UpdateMktDepthData popped;
    if ( !this->m_updateMktDepths.empty() ) {
        popped = this->m_updateMktDepths.front();
        this->m_updateMktDepths.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
UpdateMktDepthL2Data IbPosixClient::getUpdateMktDepthL2() {
    UpdateMktDepthL2Data popped;
    if ( !this->m_updateMktDepthL2s.empty() ) {
        popped = this->m_updateMktDepthL2s.front();
        this->m_updateMktDepthL2s.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
UpdateNewsBulletinData IbPosixClient::getUpdateNewsBulletin() {
    UpdateNewsBulletinData popped;
    if ( !this->m_updateNewsBulletins.empty() ) {
        popped = this->m_updateNewsBulletins.front();
        this->m_updateNewsBulletins.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
ManagedAccountsData IbPosixClient::getManagedAccounts() {
    ManagedAccountsData popped;
    if ( !this->m_managedAccounts.empty() ) {
        popped = this->m_managedAccounts.front();
        this->m_managedAccounts.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
ReceiveFAData IbPosixClient::getReceiveFA() {
    ReceiveFAData popped;
    if ( !this->m_receiveFAs.empty() ) {
        popped = this->m_receiveFAs.front();
        this->m_receiveFAs.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
HistoricalDataData IbPosixClient::getHistoricalData() {
    HistoricalDataData popped;
    if ( !this->m_historicalData.empty() ) {
        popped = this->m_historicalData.front();
        this->m_historicalData.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
ScannerParametersData IbPosixClient::getScannerParameters() {
    ScannerParametersData popped;
    if ( !this->m_scannerParameters.empty() ) {
        popped = this->m_scannerParameters.front();
        this->m_scannerParameters.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
ScannerDataData IbPosixClient::getScannerData() {
    ScannerDataData popped;
    if ( !this->m_scannerData.empty() ) {
        popped = this->m_scannerData.front();
        this->m_scannerData.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
ScannerDataEndData IbPosixClient::getScannerDataEnd() {
    ScannerDataEndData popped;
    if ( !this->m_scannerDataEnd.empty() ) {
        popped = this->m_scannerDataEnd.front();
        this->m_scannerDataEnd.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
RealtimeBarData IbPosixClient::getRealtimeBar() {
    RealtimeBarData popped;
    if ( !this->m_realtimeBars.empty() ) {
        popped = this->m_realtimeBars.front();
        this->m_realtimeBars.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
FundamentalDataData IbPosixClient::getFundamentalData() {
    FundamentalDataData popped;
    if ( !this->m_fundamentalData.empty() ) {
        popped = this->m_fundamentalData.front();
        this->m_fundamentalData.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
DeltaNeutralValidationData IbPosixClient::getDeltaNeutralValidation() {
    DeltaNeutralValidationData popped;
    if ( !this->m_deltaNeutralValidations.empty() ) {
        popped = this->m_deltaNeutralValidations.front();
        this->m_deltaNeutralValidations.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
TickSnapshotEndData IbPosixClient::getTickSnapshotEnd() {
    TickSnapshotEndData popped;
    if ( !this->m_tickSnapshotEnds.empty() ) {
        popped = this->m_tickSnapshotEnds.front();
        this->m_tickSnapshotEnds.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
MarketDataTypeData IbPosixClient::getMarketDataType() {
    MarketDataTypeData popped;
    if ( !this->m_marketDataTypes.empty() ) {
        popped = this->m_marketDataTypes.front();
        this->m_marketDataTypes.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
CommissionReportData IbPosixClient::getCommissionReport() {
    CommissionReportData popped;
    if ( !this->m_commissionReports.empty() ) {
        popped = this->m_commissionReports.front();
        this->m_commissionReports.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
PositionData IbPosixClient::getPosition() {
    PositionData popped;
    if ( !this->m_positions.empty() ) {
        popped = this->m_positions.front();
        this->m_positions.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
PositionEndData IbPosixClient::getPositionEnd() {
    PositionEndData popped;
    if ( !this->m_positionEnd.empty() ) {
        popped = this->m_positionEnd.front();
        this->m_positionEnd.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
AccountSummaryData IbPosixClient::getAccountSummary() {
    AccountSummaryData popped;
    if ( !this->m_accountSummaries.empty() ) {
        popped = this->m_accountSummaries.front();
        this->m_accountSummaries.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
AccountSummaryEndData IbPosixClient::getAccountSummaryEnd() {
    AccountSummaryEndData popped;
    if ( !this->m_accountSummaryEnd.empty() ) {
        popped = this->m_accountSummaryEnd.front();
        this->m_accountSummaryEnd.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
VerifyMessageAPIData IbPosixClient::getVerifyMessageAPI() {
    VerifyMessageAPIData popped;
    if ( !this->m_verifyMessageAPIs.empty() ) {
        popped = this->m_verifyMessageAPIs.front();
        this->m_verifyMessageAPIs.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
VerifyCompletedData IbPosixClient::getVerifyCompleted() {
    VerifyCompletedData popped;
    if ( !this->m_verifyCompleted.empty() ) {
        popped = this->m_verifyCompleted.front();
        this->m_verifyCompleted.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
DisplayGroupListData IbPosixClient::getDisplayGroupList() {
    DisplayGroupListData popped;
    if ( !this->m_displayGroupLists.empty() ) {
        popped = this->m_displayGroupLists.front();
        this->m_displayGroupLists.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}
DisplayGroupUpdatedData IbPosixClient::getDisplayGroupUpdated() {
    DisplayGroupUpdatedData popped;
    if ( !this->m_displayGroupUpdated.empty() ) {
        popped = this->m_displayGroupUpdated.front();
        this->m_displayGroupUpdated.pop();
        return popped;
    }
    popped.isValid = false;
    return popped;
}