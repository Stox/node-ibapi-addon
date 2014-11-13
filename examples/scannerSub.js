// In this example, we will request a scanner subscription and receive the
//  data from scanner sub.

var ibapi = require('../ibapi');
var scanner = ibapi.scannerSubscription;
var client = new ibapi.addon.NodeIbapi();

var orderId = -1;
var processIbMsg = function () {
  client.processIbMsg();
}
var addReqId = function () {
  client.addReqId(1);
}
var doReqFunc = function () {
  client.doReqFunc();
}

var impVolGainers = scanner.createScannerSub();
impVolGainers.instrument = "STK";
impVolGainers.scanCode = "TOP_OPT_IMP_VOLAT_GAIN";

var impVolGainerScan = function () {
  client.reqScannerSubscription(1, impVolGainers);  
}

client.on('connected', function () {
  console.log('connected');
  setInterval(processIbMsg,0.1);
  client.funcQueue.push(addReqId);
  client.funcQueue.push(impVolGainerScan);
})
.once('nextValidId', function (data) {
  orderId = data.orderId;
  console.log('nextValidId: ' + orderId);
  setInterval(doReqFunc,100);
})
.on('clientError', function (clientError) {
  console.log('Client error' + clientError.id.toString());
})
.on('svrError', function (svrError) {
  console.log('Error: ' + svrError.id.toString() + ' - ' + 
    svrError.errorCode.toString() + ' - ' + svrError.errorString.toString());
})
.on('scannerData', function (scannerData) {
  // start recording data
  console.log('ScannerData: ' + scannerData.reqId + " " + scannerData.contractDetails.summary.symbol.toString());
})
.on('scannerDataEnd', function () {
  // close the opened file
})
.on('disconnected', function () {
  console.log('disconnected');
  process.exit(1);
})

client.connectToIb('127.0.0.1',7496,0);
