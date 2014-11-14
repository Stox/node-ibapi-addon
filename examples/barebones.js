var ibapi = require('../ibapi');
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
client.on('connected', function () {
  console.log('connected');
  setInterval(processIbMsg,0.1);
  client.funcQueue.push(addReqId);

})
.once('nextValidId', function (data) {
      console.log('Server version ' + client.serverVersion().toString());
  orderId = data.orderId;
  console.log('nextValidId: ' + orderId);
      console.log(client.twsConnectionTime());
  setInterval(doReqFunc,100);
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

client.connectToIb('127.0.0.1', 7496, 0);
