// In this example, we will try to place a limit order and to 
//  receive the orderStatus, as well as to poll for openOrders.
// This example will use Node.js's built in event handlers

var addon = require('../ibapi');
var obj = new addon.NodeIbapi();
var ibcontract = require('../lib/contract');

var orderId = -1;
var counter = 0;
var ready = false;

var isOrderPlaced = false;

var processIbMsg = function () {
  obj.processIbMsg();
}
var doReqFunc = function () {
  obj.doReqFunc();
}
var doOpenOrderReq = function () {
  obj.reqOpenOrders();
}
var disconnectClient = function () {
  obj.disconnect();
}
var msftContract = ibcontract.createContract();
msftContract.symbol = 'MSFT';
msftContract.secType = 'STK';
msftContract.exchange = 'SMART';
msftContract.primaryExchange = 'NASDAQ';
msftContract.currency = 'USD';

var placeThatOrder = function () {
    console.log('Next valid order Id: %d',orderId);
    console.log("Placing order for MSFT");
    obj.placeOrder(orderId, msftContract, "BUY", 1000, "LMT", 0.11, 0.11);
    orderId = orderId + 1;
    isOrderPlaced = true;
}
var cancelPrevOrder = function () {
  if (isOrderPlaced) {
    console.log('canceling order: %d', orderId-1);
    obj.cancelOrder(orderId-1);
    isOrderPlaced = false;
  }
}

obj.on('connected', function () {
  console.log('connected');
  setInterval(processIbMsg,0.1);
})
.once('nextValidId', function (data) {
  orderId = data.orderId;
  setInterval(function () {obj.funcQueue.push(doOpenOrderReq);},200);
  setInterval(function () {obj.funcQueue.push(placeThatOrder);},1000);
  setInterval(function () {obj.funcQueue.push(cancelPrevOrder);},1000);
  setInterval(doReqFunc,200);
  setTimeout(disconnectClient,9001);
})
.on('orderStatus',function (orderStatus) { 
  console.log("OrderID, status, filled, remaining, avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld");
  console.log( 
    orderStatus.orderId.toString() + " " + orderStatus.status.toString() + " " +
    orderStatus.filled.toString() + " " + orderStatus.remaining.toString() + " " +
    orderStatus.avgFillPrice.toString() + " " + orderStatus.permId.toString() + " " +
    orderStatus.parentId.toString() + " " + orderStatus.lastFillPrice.toString() + " " +
    orderStatus.clientId.toString() + " " + orderStatus.whyHeld.toString()
  );
})
.on('openOrder', function (openOrder) {
  console.log("OrderId, status, initMargin, maintMargin, equityWithLoan, Commission, minCommission, maxCommission, commissionCurrency, warningText");
  console.log(
      openOrder.orderId.toString() + " " + 
      openOrder.status.toString() + " " + 
      openOrder.initMargin.toString() + " " + 
      openOrder.maintMargin.toString() + " " + 
      openOrder.equityWithLoan.toString() + " " + 
      openOrder.commission.toString() + " " + 
      openOrder.minCommission.toString() + " " + 
      openOrder.maxCommission.toString() + " " + 
      openOrder.commissionCurrency.toString() + " " + 
      openOrder.warningText.toString() 
  );
})
.on('clientError', function (clientError) {
  console.log('Client error' + clientError.id.toString());
})
.on('svrError', function (svrError) {
  console.log('Error: ' + svrError.id.toString() + ' - ' + 
    svrError.errorCode.toString() + ' - ' + svrError.errorString.toString());
})
.on('disconnected', function () {
  console.log('disconnected');
  process.exit(1);
})

obj.connectToIb('127.0.0.1',7496,0);
