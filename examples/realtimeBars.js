// In this example, we will try to submit a realtimeBar request
var addon = require('../ibapi'),
  messageIds = addon.messageIds,
  contract = addon.contract,
  order = addon.order;

var api = new addon.NodeIbapi();
var orderId = -1;

var addEurUsd = function () {
  var eurusd = contract.createContract();
  eurusd.symbol = 'EUR';
  eurusd.secType = 'CASH';
  eurusd.exchange = 'IDEALPRO';
  eurusd.primaryExchange = 'IDEALPRO';
  eurusd.currency = 'USD';
  api.reqRealtimeBars(1,eurusd,5,"TRADES",false);
};

var addMsft = function () {
  var msftContract = contract.createContract();
  msftContract.symbol = 'MSFT';
  msftContract.secType = 'STK';
  msftContract.exchange = 'SMART';
  msftContract.primaryExchange = 'NASDAQ';
  msftContract.currency = 'USD';
  api.reqRealtimeBars(1,msftContract,5,"TRADES",false);
};

var handleValidOrderId = function (message) {
  orderId = message.orderId;
  console.log('next order Id is ' + orderId);
  addEurUsd();
  addMsft();
};

var handleServerError = function (message) {
  console.log('Error: ' + message.id.toString() + '-' +
              message.errorCode.toString() + '-' +
              message.errorString.toString());
};

var handleClientError = function (message) {
  console.log('clientError');
  console.log(JSON.stringify(message));
};

var handleDisconnected = function (message) {
  console.log('disconnected');
  process.exit(1);
};

var handleRealTimeBar = function (realtimeBar) {
  console.log( "RealtimeBar: " + 
                realtimeBar.reqId.toString() + " " +
                realtimeBar.time.toString() + " " +
                realtimeBar.open.toString() + " " +
                realtimeBar.high.toString() + " " +
                realtimeBar.low.toString() + " " +
                realtimeBar.close.toString() + " " +
                realtimeBar.volume.toString() + " " +
                realtimeBar.wap.toString() + " " +
                realtimeBar.count.toString()
  );
};

// After that, you must register the event handler with a messageId
//  For list of valid messageIds, see messageIds.js file.
api.handlers[messageIds.nextValidId] = handleValidOrderId;
api.handlers[messageIds.svrError] = handleServerError;
api.handlers[messageIds.clientError] = handleClientError;
api.handlers[messageIds.disconnected] = handleDisconnected;
api.handlers[messageIds.realtimeBar] = handleRealTimeBar;

// Connect to the TWS client or IB Gateway
var connected = api.connect('127.0.0.1', 7496, 0);

// Once connected, start processing incoming and outgoing messages
if (connected) {
  api.beginProcessing();
}
