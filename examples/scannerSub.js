// In this example, we will request a scanner subscription and receive the
//  data from scanner sub.

var addon = require('../ibapi'),
  messageIds = addon.messageIds,
  contract = addon.contract,
  order = addon.order,
  scanner = addon.scannerSubscription;

var api = new addon.NodeIbapi();
var orderId = -1;

var impVolGainers = scanner.createScannerSub();
impVolGainers.instrument = "STK";
impVolGainers.scanCode = "TOP_OPT_IMP_VOLAT_GAIN";

var impVolGainerScan = function () {
  setImmediate(api.reqScannerSubscription.bind(api, 1, impVolGainers));  
};

var handleValidOrderId = function (message, callback) {
  orderId = message.orderId;
  console.log('next order Id is ' + orderId);
  impVolGainerScan();
  callback();
};

var handleServerError = function (message, callback) {
  console.log('Error: ' + message.id.toString() + '-' +
              message.errorCode.toString() + '-' +
              message.errorString.toString());
  callback();
};

var handleClientError = function (message, callback) {
  console.log('clientError');
  console.log(JSON.stringify(message));
  callback();
};

var handleDisconnected = function (message, callback) {
  console.log('disconnected');
  callback();
  process.exit(1);
};

var handleScannerData = function (scannerData, callback) {
  console.log('ScannerData: ' + scannerData.reqId + " " + 
    scannerData.contractDetails.summary.symbol.toString());
  callback();
};

var handleScannerDataEnd = function (message, callback) {
  console.log('End of scannerData');
  callback();
};

api.handlers[messageIds.nextValidId] = handleValidOrderId;
api.handlers[messageIds.svrError] = handleServerError;
api.handlers[messageIds.clientError] = handleClientError;
api.handlers[messageIds.disconnected] = handleDisconnected;
api.handlers[messageIds.scannerData] = handleScannerData;
api.handlers[messageIds.scannerDataEnd] = handleScannerDataEnd;

var connected = api.connect('127.0.0.1', 7496, 0);

if (connected) {
  api.beginProcessing();
}