var addon = require('../ibapi');
var obj = new addon.NodeIbapi();
var ibcontract = require('../lib/contract');

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

var eurusd = ibcontract.createContract();
eurusd.symbol = 'EUR';
eurusd.secType = 'CASH';
eurusd.exchange = 'IDEALPRO';
eurusd.primaryExchange = 'IDEALPRO';
eurusd.currency = 'USD';

var buyOrder = function () {
    console.log('Next valid order Id: %d',orderId);
    console.log("Placing order for EUR");
    obj.placeOrder(orderId, eurusd, "BUY", 100, "MKT", 0.0);
    orderId = orderId + 1;
    isOrderPlaced = true;
}
var sellOrder = function () {
    console.log('Next valid order Id: %d',orderId);
    console.log("Placing order for EUR");
    obj.placeOrder(orderId, eurusd, "SELL", 100, "MKT", 1000.0);
    orderId = orderId + 1;
    isOrderPlaced = true;
}
var subscribeEurUsd = function () {
  obj.reqMktData(1,eurusd,"165",false);
}
var priceVec = [];

obj.on('connected', function () {
  console.log('connected');
  setInterval(processIbMsg,0.1);
  obj.funcQueue.push(addReqId);
})
.once('nextValidId', function (data) {
  orderId = data.orderId;
  console.log('nextValidId: ' + orderId);
  setInterval(doReqFunc,21);
  obj.funcQueue.push(subscribeEurUsd);
})
.on('tickPrice', function (tickPrice) {
  console.log( "TickPrice: " + tickPrice.tickerId.toString() + " " + 
    tickPrice.field.toString() + " " + tickPrice.price.toString() + " " +
    tickPrice.canAutoExecute.toString());
  // buy 
  if (priceVec.length < 3) {
    // push
    priceVec.push(tickPrice.price);
  }
  else if (priceVec.length === 3) {
    priceVec[0] = priceVec[1];
    priceVec[1] = priceVec[2];
    priceVec[2] = tickPrice.price;

    // make  a buy/sell decision
    if (priceVec[2] > priceVec[1] && priceVec[1] > priceVec[0]) {
      // sell
      obj.funcQueue.push(sellOrder);
    }
    else if (priceVec[2] < priceVec[1] && priceVec[1] < priceVec[0]) {
      // buy
      obj.funcQueue.push(buyOrder);
    }
  }
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