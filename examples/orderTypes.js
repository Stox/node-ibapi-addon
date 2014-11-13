// In this example, we will submit orders with different methods
var ibapi = require('../ibapi');
var ibcontract = ibapi.contract;
var iborder = ibapi.order;
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
var disconnectClient = function () {
  client.disconnect();
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
  client.placeOrder(oId,contract, 
    "BUY", 1000, "LMT", 0.11, 0.11);
}
var placeMsftMitOrder = function (contract, oId) {
  console.log("Order %d: Placing MIT order for MSFT",oId);
  client.placeOrder(oId,contract, 
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

  client.placeOrder(oId,contract,newOrder);
}
var cancelPrevOrder = function (oId) {
  console.log('canceling order: %d', oId);
  client.cancelOrder(oId);
}

client.on('connected', function () {
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
  client.funcQueue.push(placeMsftLmtOrder(msftContract1, orderId));
  client.funcQueue.push(cancelPrevOrder(orderId));
  orderId = orderId + 1;
  client.funcQueue.push(placeMsftMitOrder(msftContract2, orderId));
  client.funcQueue.push(cancelPrevOrder(orderId));
  orderId = orderId + 1;
  client.funcQueue.push(placeOrderUsingLib(msftContract2, orderId));
  client.funcQueue.push(cancelPrevOrder(orderId));
  orderId = orderId + 1;
  setTimeout(disconnectClient,9001);
})
.on('disconnected', function () {
  console.log('disconnected');
  process.exit(1);
})


client.connectToIb('127.0.0.1',7496,0);
