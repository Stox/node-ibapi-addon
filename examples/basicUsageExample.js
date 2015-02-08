var addon = require('../ibapi'),
    messageIds = addon.messageIds,
    contract = addon.contract,
    order = addon.order;

var orderId = -1;
function createMarketOrder() {
    var msftContract1 = contract.createContract();
    msftContract1.secType = 'STK';
    //msftContract1.secIdType = 'ISIN';
    //msftContract1.secId='US8725901040';
    msftContract1.exchange = 'SMART';
    msftContract1.currency = 'EUR';
    msftContract1.symbol = "FB";

    var newOrder = order.createOrder();
    newOrder.action = "BUY";
    newOrder.totalQuantity = 3000;
    newOrder.orderType = "MKT";

    api.placeOrder(orderId, msftContract1, newOrder);
}
function createMarketOnOpenOrder() {
    var msftContract1 = contract.createContract();
    msftContract1.symbol = 'HIG';
    msftContract1.secType = 'STK';
    msftContract1.exchange = 'SMART';
    msftContract1.primaryExchange = 'NYSE';
    msftContract1.currency = 'USD';

    var newOrder = order.createOrder();
    newOrder.action = "BUY";
    newOrder.totalQuantity = 100;
    newOrder.orderType = "MKT";
    newOrder.tif = "OPG";

    api.placeOrder(orderId, msftContract1, newOrder);
}

function createReplaceOrder() {
    createLimitOrder();

    setTimeout(function () {
        var msftContract1 = contract.createContract();
        msftContract1.symbol = 'AAPL';
        msftContract1.secType = 'STK';
        msftContract1.exchange = 'SMART';
        msftContract1.primaryExchange = 'NASDAQ';
        msftContract1.currency = 'USD';

        var newOrder = order.createOrder();
        newOrder.action = "BUY";
        newOrder.totalQuantity = 100;
        newOrder.orderType = "LMT";
        newOrder.lmtPrice = 109;

        api.placeOrder(orderId, msftContract1, newOrder);
    }, 3000)

}

function createIocOrder() {
    var msftContract1 = contract.createContract();
    msftContract1.symbol = 'AAPL';
    msftContract1.secType = 'STK';
    msftContract1.exchange = 'SMART';
    msftContract1.primaryExchange = 'NASDAQ';
    msftContract1.currency = 'USD';

    var newOrder = order.createOrder();
    newOrder.action = "BUY";
    newOrder.totalQuantity = 100;
    newOrder.orderType = "LMT";
    newOrder.tif = "IOC";
    newOrder.lmtPrice = 111.65;

    api.placeOrder(orderId, msftContract1, newOrder);
}

function createFokOrder() {
    var msftContract1 = contract.createContract();
    msftContract1.symbol = 'AAPL';
    msftContract1.secType = 'STK';
    msftContract1.exchange = 'ISLAND';
    msftContract1.currency = 'USD';

    var newOrder = order.createOrder();
    newOrder.action = "BUY";
    newOrder.totalQuantity = 20000;
    newOrder.orderType = "LMT";
    newOrder.lmtPrice = 111.65;
    newOrder.allOrNone = true;

    api.placeOrder(orderId, msftContract1, newOrder);
}

function createLimitOrder() {
    var msftContract1 = contract.createContract();
    msftContract1.symbol = '6758';
    msftContract1.secType = 'STK';
    msftContract1.exchange = 'TSEJ';
    //msftContract1.primaryExchange = 'LSE';
    msftContract1.currency = 'JPY';

    var newOrder = order.createOrder();
    newOrder.action = "BUY";
    newOrder.totalQuantity = 100;
    newOrder.orderType = "MOC";
    //newOrder.lmtPrice = 200;
    //newOrder.tif = "OPG";

    api.placeOrder(orderId, msftContract1, newOrder);
}

function reqExecutions() {

    api.reqExecutions(2);
}

function reqCurrentTime() {

    api.reqCurrentTime();
}

var handleValidOrderId = function (message, callback) {
    orderId = message.orderId;
    createMarketOrder();
    console.log('next order Id is ' + orderId);
    callback()

};

var handleServerError = function (message, callback) {
    console.log('Error: ' + message.id.toString() + ' - ' +
                message.errorCode.toString() + ' - ' + message.errorString.toString());
    callback()

};

var handleOrderStatus = function (message, callback) {
    console.log('orderStatus');
    console.log(JSON.stringify(message));

    callback()
};

var handleOpenOrder = function (message, callback) {

    console.log('openOrder:');
    console.log('orderId: ' + JSON.stringify(message.orderId));
    console.log('orderState: ' + JSON.stringify(message.orderState));
    console.log('order: ' + JSON.stringify(message.order));
    console.log('contract: ' + JSON.stringify(message.contract));

    callback()
};

var handlePosition = function (message, callback) {

    console.log('position');
    console.log(JSON.stringify(message));

    callback()
};

var handleCurrentTime = function (message, callback) {

    console.log('currentTime');
    console.log(JSON.stringify(message));

    callback()
};

var handleExecutions = function (message, callback) {

    console.log('execDetails');
    console.log(JSON.stringify(message));

    callback()
};

var handleDisconnected = function (message, callback) {

    console.log('Disconnected');

    api.connect('127.0.0.1', 7496, 0);

    callback();
};

var handleConnectionClosed = function (message, callback) {

    console.log('Connection closed');
    console.log(JSON.stringify(message));

    api.connect('127.0.0.1', 7496, 0);

    callback();
};

var handleClientError = function (message, callback) {

    console.log('client error');
    console.log(JSON.stringify(message));

    callback();
};

var api = new addon.NodeIBApi();

//add handlers to listen to messages
//each handler must have be a function (message, callback) signature
//each handler must call the callback() to signal that processing finished
api.handlers[messageIds.nextValidId] = handleValidOrderId;
api.handlers[messageIds.svrError] = handleServerError;
api.handlers[messageIds.clientError] = handleClientError;
api.handlers[messageIds.orderStatus] = handleOrderStatus;
api.handlers[messageIds.openOrder] = handleOpenOrder;
api.handlers[messageIds.currentTime] = handleCurrentTime;
//api.handlers[messageIds.position] = handlePosition;
//api.handlers[messageIds.execDetails] = handleExecutions;
api.handlers[messageIds.disconnected] = handleDisconnected;
api.handlers[messageIds.connectionClosed] = handleConnectionClosed;

var connected = api.connect('127.0.0.1', 7496, 0);

if (connected) {
    api.beginProcessing();

}