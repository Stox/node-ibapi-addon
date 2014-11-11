var addon = require('../ibapi'),
    messageIds = addon.messageIds,
    contract = addon.contract,
    order = addon.order;

var orderId = -1
function createMSFTOrder() {
    var msftContract1 = contract.createContract();
    msftContract1.symbol = 'AAPL';
    msftContract1.secType = 'STK';
    msftContract1.exchange = 'SMART';
    msftContract1.primaryExchange = 'NASDAQ';
    msftContract1.currency = 'USD';

    var newOrder = order.createOrder();
    newOrder.action = "BUY";
    newOrder.totalQuantity = 1000;
    newOrder.orderType = "LMT";
    newOrder.lmtPrice = 0.12;
    newOrder.auxPrice = 0.12;

    api.placeOrder(orderId, msftContract1, newOrder);
}

var handleValidOrderId = function (message, callback) {
    orderId = message.orderId;
    createMSFTOrder();
    console.log('next order Id is ' + orderId);
    callback()

};

var handleServerError = function (message, callback) {
    console.log('Error: ' + message.id.toString() + ' - ' +
                message.errorCode.toString() + ' - ' + message.errorString.toString());
    callback()

};

var handleOrderStatus = function (message, callback) {

    var orderStatus = message;
    console.log("OrderID, status, filled, remaining, avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld");
    console.log(
        orderStatus.orderId.toString() + " " + orderStatus.status.toString() + " " +
        orderStatus.filled.toString() + " " + orderStatus.remaining.toString() + " " +
        orderStatus.avgFillPrice.toString() + " " + orderStatus.permId.toString() + " " +
        orderStatus.parentId.toString() + " " + orderStatus.lastFillPrice.toString() + " " +
        orderStatus.clientId.toString() + " " + orderStatus.whyHeld.toString()
    );
    callback()
};

var api = new addon.NodeIBApi();

//add handlers to listen to messages
//each handler must have be a function (message, callback) signature
//each handler must call the callback() to signal that processing finished
api.handlers[messageIds.nextValidId] = handleValidOrderId;
api.handlers[messageIds.svrError] = handleServerError;
api.handlers[messageIds.orderStatus] = handleOrderStatus;

var connected = api.connect('127.0.0.1', 7496, 0);

if (connected) {
    api.beginProcessing();
}



















