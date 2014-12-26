// In this example, we will try to submit a market data subscription
//  to EUR/USD and get the TickPrice and TickSize events from the
//  IB Cash Data Server
// Also, in this example we will submit a market data subscription 
//  to MSFT.

var addon = require('../ibapi'),
  messageIds = addon.messageIds,
  contract = addon.contract,
  order = addon.order;

var requestToInstrument={
    1:"EURUSD",
    2:"GBPUSD"
}

var eurusd = contract.createContract();
eurusd.symbol = 'EUR';
eurusd.secType = 'CASH';
eurusd.exchange = 'IDEALPRO';
eurusd.primaryExchange = 'IDEALPRO';
eurusd.currency = 'USD';

var gbpusd = contract.createContract();
gbpusd.symbol = 'GBP';
gbpusd.secType = 'CASH';
gbpusd.exchange = 'IDEALPRO';
gbpusd.primaryExchange = 'IDEALPRO';
gbpusd.currency = 'USD';

var msftContract = contract.createContract();
msftContract.symbol = 'MSFT';
msftContract.secType = 'STK';
msftContract.exchange = 'SMART';
msftContract.primaryExchange = 'NASDAQ';
msftContract.currency = 'USD';

var api = new addon.NodeIbapi();

var handleValidOrderId = function (message, callback) {
  orderId = message.orderId;
  console.log('next order Id is ' + orderId);
  callback()

};
var handleServerError = function (message, callback) {
  console.log('Error: ' + message.id.toString() + ' - ' +
              message.errorCode.toString() + ' - ' + message.errorString.toString());
  callback()
};

var tickTypes={
    1:"bid",
    2:"ask",
    4:"last",
    6:"high",
    7:"low",
    9:"close"
};

var handleTickPrice = function (tickPrice, callback) {
  console.log("TickPrice: " + requestToInstrument[tickPrice.tickerId]+ " " +
              tickTypes[tickPrice.field] + " " + tickPrice.price.toString() + " " +
              tickPrice.canAutoExecute.toString());
  callback()
};
var handleTickSize = function (tickSize, callback) {
  console.log("TickSize: " + tickSize.tickerId.toString() + " " +
              tickSize.field.toString() + " " + tickSize.size.toString());
  callback()
};
var handleExecutions = function (message, callback) {
  console.log('execDetails');
  console.log(JSON.stringify(message));
  callback()
};

var handleClientError = function (message, callback) {
  console.log('clientError');
  console.log(JSON.stringify(message));
  callback()
};

var handleDisconnected = function (message, callback) {
  console.log('disconnected');
  callback();
  process.exit(1);
};

api.handlers[messageIds.nextValidId] = handleValidOrderId;
api.handlers[messageIds.svrError] = handleServerError;
api.handlers[messageIds.tickPrice] = handleTickPrice;
//api.handlers[messageIds.tickSize] = handleTickSize;
api.handlers[messageIds.execDetails] = handleExecutions;
api.handlers[messageIds.clientError] = handleClientError;
api.handlers[messageIds.disconnected] = handleDisconnected;

var connected = api.connect('127.0.0.1', 7496, 0);

if (connected) {
  api.beginProcessing();
  setTimeout(api.reqMktData.bind(api,1, eurusd, "165", false), 300);
  setTimeout(api.reqMktData.bind(api,2, gbpusd, "165", false), 300);
  //setTimeout(api.reqMktData.bind(api,3, msftContract, "165", false), 300)
  //setTimeout(api.disconnect.bind(api),20000)
}
