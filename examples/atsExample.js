var ibapi = require('../ibapi');
var ibcontract = ibapi.contract;
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

var eurusd = ibcontract.createContract();
eurusd.symbol = 'EUR';
eurusd.secType = 'CASH';
eurusd.exchange = 'IDEALPRO';
eurusd.primaryExchange = 'IDEALPRO';
eurusd.currency = 'USD';

var buyOrder = function () {
    console.log('Next valid order Id: %d',orderId);
    console.log("Placing order for EUR");
    client.placeOrder(orderId, eurusd, "BUY", 100, "MKT", 0.0, 0.0);
    orderId = orderId + 1;
    isOrderPlaced = true;
}
var sellOrder = function () {
    console.log('Next valid order Id: %d',orderId);
    console.log("Placing order for EUR");
    client.placeOrder(orderId, eurusd, "SELL", 100, "MKT", 1000.0, 0.0);
    orderId = orderId + 1;
    isOrderPlaced = true;
}
var subscribeEurUsd = function () {
  client.reqMktData(1,eurusd,"165",false);
}
var priceVec = [];

client.on('connected', function () {
  console.log('connected');
  setInterval(processIbMsg,0.1);
  client.funcQueue.push(addReqId);
})
.once('nextValidId', function (data) {
  orderId = data.orderId;
  console.log('nextValidId: ' + orderId);
  setInterval(doReqFunc,21);
  client.funcQueue.push(subscribeEurUsd);
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
      client.funcQueue.push(sellOrder);
    }
    else if (priceVec[2] < priceVec[1] && priceVec[1] < priceVec[0]) {
      // buy
      client.funcQueue.push(buyOrder);
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

client.connectToIb('127.0.0.1',7496,0);
