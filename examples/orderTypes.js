// In this example, we will submit orders with different methods
var addon = require('../ibapi');
var obj = new addon.NodeIbapi();
var ibcontract = require('../lib/contract');
var iborder = require('../lib/order');

var orderId = -1;

var processIbMsg = function () {
  obj.processIbMsg();
}
var addReqId = function () {
  obj.addReqId(1);
}
var doReqFunc = function () {
  obj.doReqFunc();
}
var disconnectClient = function () {
  obj.disconnect();
}

var msftContract1 = ibcontract.createContract();
msftContract1.symbol = 'MSFT';
msftContract1.secType = 'STK';
msftContract1.exchange = 'SMART';
msftContract1.primaryExchange = 'NASDAQ';
msftContract1.currency = 'USD';

var msftContract2 = ibcontract.createContract();
msftContract2.conId = 272093; // look this up from Contract Details in TWS
msftContract2.exchange = 'SMART';


// Must have lmtPrice and auxPrice in the arguments
var placeMsftLmtOrder = function (contract, oId) {
  console.log("Order %d: Placing LMT order for MSFT",oId);
  obj.placeOrder(oId,contract, 
    "BUY", 1000, "LMT", 0.11, 0.11);
}
var placeMsftMitOrder = function (contract, oId) {
  console.log("Order %d: Placing MIT order for MSFT",oId);
  obj.placeOrder(oId,contract, 
    "BUY", 1000, "MIT", 0.11, 0.11);
}
// Now supports using order.js
var placeOrderUsingLib = function (contract, oId) {
  console.log("Order %d: Placing LMT order for MSFT with order.js lib", oId);
  var newOrder = iborder.createOrder();
  newOrder.action = "BUY";
  newOrder.totalQuantity = 1000;
  newOrder.orderType = "LMT";
  newOrder.lmtPrice = 0.12;
  newOrder.auxPrice = 0.12;

  obj.placeOrder(oId,contract,newOrder);
}
var cancelPrevOrder = function (oId) {
  console.log('canceling order: %d', oId);
  obj.cancelOrder(oId);
}

obj.on('connected', function () {
  console.log('connected');
  setInterval(processIbMsg,0.1);
})
.on('clientError', function (clientError) {
  console.log('Client error' + clientError.id.toString());
})
.on('svrError', function (svrError) {
  console.log('Error: ' + svrError.id.toString() + ' - ' + 
    svrError.errorCode.toString() + ' - ' + svrError.errorString.toString());
})
.once('nextValidId', function (data) {
  orderId = data.orderId;
  setInterval(doReqFunc,100);
  obj.funcQueue.push(placeMsftLmtOrder(msftContract1, orderId));
  obj.funcQueue.push(cancelPrevOrder(orderId));
  orderId = orderId + 1;
  obj.funcQueue.push(placeMsftMitOrder(msftContract2, orderId));
  obj.funcQueue.push(cancelPrevOrder(orderId));
  orderId = orderId + 1;
  obj.funcQueue.push(placeOrderUsingLib(msftContract2, orderId));
  obj.funcQueue.push(cancelPrevOrder(orderId));
  orderId = orderId + 1;
  setTimeout(disconnectClient,9001);
})
.on('disconnected', function () {
  console.log('disconnected');
  process.exit(1);
})


obj.connectToIb('127.0.0.1',7496,0);
