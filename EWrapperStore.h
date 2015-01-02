#ifndef ewrapperstore_def
#define ewrapperstore_def


#include "import/Contract.h"
#include "import/Order.h"
#include "import/OrderState.h"
#include "import/Execution.h"
#include "import/CommissionReport.h"

struct TickPriceData {
    bool isValid;
    TickerId tickerId;
    TickType field;
    double price;
    int canAutoExecute;
};
struct TickSizeData {
    bool isValid;
    TickerId tickerId;
    TickType field;
    int size;
};
struct TickOptionComputationData {
    bool isValid;
   TickerId tickerId;
   TickType tickType;
   double impliedVol;
   double delta;
   double optPrice;
   double pvDividend;
   double gamma;
   double vega;
   double theta;
   double undPrice;
};
struct TickGenericData {
    bool isValid;
    TickerId tickerId;
    TickType tickType;
    double value;
};
struct TickStringData {
    bool isValid;
    TickerId tickerId;
    TickType tickType;
    IBString value;
};
struct TickEFPData {
    bool isValid;
    TickerId tickerId;
    TickType tickType;
    double basisPoints;
    IBString formattedBasisPoints;

    double totalDividends;
    int holdDays;
    IBString futureExpiry;
    double dividendImpact;
    double dividendsToExpiry;
};
struct OrderStatusData {
    bool isValid;
    OrderId orderId;
    IBString status;
    int filled;

    int remaining;
    double avgFillPrice;
    int permId;
    int parentId;

    double lastFillPrice;
    int clientId;
    IBString whyHeld;
};
struct OpenOrderData {
    bool isValid;
    OrderId orderId;
    Contract contract;
    Order order;
    OrderState orderState;
};
struct OpenOrderEndData {
    bool isValid;
};
struct WinErrorData {
    bool isValid;
    IBString str;
    int lastError;
};
struct ConnectionClosedData {
    bool isValid;
};
struct UpdateAccountValueData {
    bool isValid;
    IBString key;
    IBString val;
    IBString currency;
    IBString accountName;
};
struct UpdatePortfolioData {
    bool isValid;
    Contract contract;
    int position;
    double marketPrice;
    double marketValue;
    double averageCost;

    double unrealizedPNL;
    double realizedPNL;
    IBString accountName;
};
struct UpdateAccountTimeData {
    bool isValid;
    IBString timeStamp;
};
struct AccountDownloadEndData {
    bool isValid;
    IBString accountName;
};
struct NextValidIdData {
    bool isValid;
    OrderId orderId;
};
struct ContractDetailsData {
    bool isValid;
    int reqId;
    ContractDetails contractDetails;
};
struct BondContractDetailsData {
    bool isValid;
    int reqId;
    ContractDetails contractDetails;
};
struct ContractDetailsEndData {
    bool isValid;
    int reqId;
};
struct ExecDetailsData {
    bool isValid;
    int reqId;
    Contract contract;
    Execution execution;
};
struct ExecDetailsEndData {
    bool isValid;
    int reqId;
};
struct ErrorData {
    bool isValid;
    int id;
    int errorCode;
    IBString errorString;
};
struct UpdateMktDepthData {
    bool isValid;
    TickerId id;
    int position;
    int operation;
    int side;
    double price;
    int size;
};
struct UpdateMktDepthL2Data {
    bool isValid;
    TickerId id;
    int position;
    IBString marketMaker;
    int operation;
    int side;
    double price;
    int size;
};
struct UpdateNewsBulletinData {
    bool isValid;
    int msgId;
    int msgType;
    IBString newsMessage;
    IBString originExch;
};
struct ManagedAccountsData {
    bool isValid;
    IBString accountsList;
};
struct ReceiveFAData {
    bool isValid;
    faDataType pFaDataType;
    IBString cxml;
};
struct HistoricalDataData {
    bool isValid;
    TickerId reqId;
    IBString date;
    double open;
    double high;
    double low;
    double close;
    int volume;
    int barCount;
    double WAP;
    int hasGaps;
};
struct ScannerParametersData {
    bool isValid;
    IBString xml;
};
struct ScannerDataData {
    bool isValid;
    int reqId;
    int rank;
    ContractDetails contractDetails;
    IBString distance;
    IBString benchmark;
    IBString projection;
    IBString legsStr;
};
struct ScannerDataEndData {
    bool isValid;
    int reqId;
};
struct RealtimeBarData {
    bool isValid;
    TickerId reqId;
    long time;
    double open;
    double high;
    double low;
    double close;
    long volume;
    double wap;
    int count;
};
struct CurrentTimeData {
    bool isValid;
    long time;
};
struct FundamentalDataData {
    bool isValid;
    TickerId reqId;
    IBString data;
};
struct DeltaNeutralValidationData {
    bool isValid;
    int reqId;
    UnderComp underComp;
};
struct TickSnapshotEndData {
    bool isValid;
    int reqId;
};
struct MarketDataTypeData {
    bool isValid;
    TickerId reqId;
    int marketDataType;
};
struct CommissionReportData {
    bool isValid;
   CommissionReport commissionReport;
};
struct PositionData {
    bool isValid;
   IBString account;
   Contract contract;
   int position;
   double avgCost;
};
struct PositionEndData {
    bool isValid;
};
struct AccountSummaryData {
    bool isValid;
   int reqId;
   IBString account;
   IBString tag;
   IBString value;
   IBString curency;
};
struct AccountSummaryEndData {
    bool isValid;
   int reqId;
};
struct VerifyMessageAPIData {
    bool isValid;
    IBString apiData;    
};
struct VerifyCompletedData {
    bool isValid;
    bool isSuccessful;
    IBString errorText;
};
struct DisplayGroupListData {
    bool isValid;
    int reqId;
    IBString groups;
};
struct DisplayGroupUpdatedData {
    bool isValid;
    int reqId;
    IBString contractInfo;
};

#endif // ewrapperstore_def
