// In this example, we will try to submit a realtimeBar request

var ibapi = require('../ibapi');
var ibcontract = ibapi.contract;
var client = new ibapi.addon.NodeIbapi();

var processIbMsg = function () {
  client.processIbMsg();
}
var doReqFunc = function () {
  client.doReqFunc();
}

var addEurUsd = function () {
  var eurusd = ibcontract.createContract();
  eurusd.symbol = 'EUR';
  eurusd.secType = 'CASH';
  eurusd.exchange = 'IDEALPRO';
  eurusd.primaryExchange = 'IDEALPRO';
  eurusd.currency = 'USD';
  client.reqRealtimeBars(1,eurusd,5,"TRADES",false);
};

var addMsft = function () {
  var msftContract = ibcontract.createContract();
  msftContract.symbol = 'MSFT';
  msftContract.secType = 'STK';
  msftContract.exchange = 'SMART';
  msftContract.primaryExchange = 'NASDAQ';
  msftContract.currency = 'USD';
  client.reqRealtimeBars(1,msftContract,5,"TRADES",false);
};

client.on('connected', function () {
  console.log('connected');
  client.funcQueue.push(addEurUsd);
  client.funcQueue.push(addMsft);
  setInterval(processIbMsg,0.1);
})
.once('nextValidId', function (data) {
  orderId = data.orderId;
  setInterval(doReqFunc,100);
})
.on('realtimeBar', function (realtimeBar) {
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
