// module for event driven methods
var addon = require('./build/Release/NodeIbapiAddon'),
    contract = require('./lib/contract'),
    order = require('./lib/order'),
    execution = require('./lib/execution'),
    contractDetails = require('./lib/contractDetails'),
    scannerSubscription = require('./lib/scannerSubscription'),
    messageIds = require('./messageIds'),
    async = require("async"),
    RateLimiter = require("limiter").RateLimiter;

function NodeIBApi() {
    this.client = new addon.NodeIbapi();
    this.limiter = new RateLimiter(50, 'second');
    this.handlers = {};
}

NodeIBApi.prototype = {

    _consumeMessages: function () {
        var messages = this.processMessage();

        async.eachSeries(Object.keys(messages), function (key, cb) {

            if (key in this.handlers) {
                var handler = this.handlers[key];

                var message = messages[key];

                return handler(message, cb);
            }

            return cb();

        }.bind(this), function (err) {
            if (err) {
                console.error(err);
                throw err;
            }

            setImmediate(this._consumeMessages.bind(this));

        }.bind(this));
    },

    processMessage: function () {
        var messages = {};
        this.client.checkMessages();
        this.client.processMsg();

        function checkMessage(messageId, objectData) {
            if (objectData.isValid) {
                messages[messageId] = objectData;
            }
        }

        checkMessage(messageIds.tickPrice, this.client.getTickPrice());
        checkMessage(messageIds.tickSize, this.client.getTickSize());
        checkMessage(messageIds.tickOptionComputation, this.client.getTickOptionComputation());
        checkMessage(messageIds.tickGeneric, this.client.getTickGeneric());
        checkMessage(messageIds.tickString, this.client.getTickString());
        checkMessage(messageIds.tickEFP, this.client.getTickEFP());
        checkMessage(messageIds.orderStatus, this.client.getOrderStatus());
        checkMessage(messageIds.openOrder, this.client.getOpenOrder());
        checkMessage(messageIds.openOrderEnd, this.client.getOpenOrderEnd());
        checkMessage(messageIds.clientError, this.client.getWinError());
        checkMessage(messageIds.connectionClosed, this.client.getConnectionClosed());
        checkMessage(messageIds.updateAccountValue, this.client.getUpdateAccountValue());
        checkMessage(messageIds.updatePortfolio, this.client.getUpdatePortfolio());
        checkMessage(messageIds.updateAccountTime, this.client.getUpdateAccountTime());
        checkMessage(messageIds.accountDownloadEnd, this.client.getAccountDownloadEnd());
        checkMessage(messageIds.nextValidId, this.client.getNextValidId());
        checkMessage(messageIds.contractDetails, this.client.getContractDetails());
        checkMessage(messageIds.retBondContractDetails, this.client.getBondContractDetails());
        checkMessage(messageIds.contractDetailsEnd, this.client.getContractDetailsEnd());
        checkMessage(messageIds.execDetails, this.client.getExecDetails());
        checkMessage(messageIds.execDetailsEnd, this.client.getExecDetailsEnd());
        checkMessage(messageIds.svrError, this.client.getError());
        checkMessage(messageIds.updateMktDepth, this.client.getUpdateMktDepth());
        checkMessage(messageIds.updateMktDepthL2, this.client.getUpdateMktDepthL2());
        checkMessage(messageIds.updateNewsBulletin, this.client.getUpdateNewsBulletin());
        checkMessage(messageIds.managedAccounts, this.client.getManagedAccounts());
        checkMessage(messageIds.receiveFA, this.client.getReceiveFA());
        checkMessage(messageIds.historicalData, this.client.getHistoricalData());
        checkMessage(messageIds.scannerParameters, this.client.getScannerParameters());
        checkMessage(messageIds.scannerData, this.client.getScannerData());
        checkMessage(messageIds.scannerDataEnd, this.client.getScannerDataEnd());
        checkMessage(messageIds.realtimeBar, this.client.getRealtimeBar());
        checkMessage(messageIds.fundamentalData, this.client.getFundamentalData());
        checkMessage(messageIds.deltaNeutralValidation, this.client.getDeltaNeutralValidation());
        checkMessage(messageIds.tickSnapshotEnd, this.client.getTickSnapshotEnd());
        checkMessage(messageIds.marketDataType, this.client.getMarketDataType());
        checkMessage(messageIds.commissionReport, this.client.getCommissionReport());
        checkMessage(messageIds.position, this.client.getPosition());
        checkMessage(messageIds.positionEnd, this.client.getPositionEnd());
        checkMessage(messageIds.accountSummary, this.client.getAccountSummary());
        checkMessage(messageIds.accountSummaryEnd, this.client.getAccountSummaryEnd());
        checkMessage(messageIds.verifyMessageAPI, this.client.getVerifyMessageAPI());
        checkMessage(messageIds.verifyCompleted, this.client.getVerifyCompleted());
        checkMessage(messageIds.displayGroupList, this.client.getDisplayGroupList());
        checkMessage(messageIds.displayGroupUpdated, this.client.getDisplayGroupUpdated());

        if (!this.client.isConnected()) {
            messages[messageIds.disconnected] = {};
        }

        return messages;
    },

    connect: function (host, port, clientId) {
        return this.client.connect(host, port, clientId)
    },

    beginProcessing: function () {
        this._consumeMessages();
    },

    disconnect: function () {
        this.doAction(function () { this.client.disconnect();});
    },

    isConnected: function () {
        return this.client.isConnected();
    },

    serverVersion: function () {
        return this.client.serverVersion();
    },

    twsConnectionTime: function () {
        return this.client.twsConnectionTime();
    },

    reqMktData: function (reqId, contract, genericTickType, snapShot) {
        this.doAction(function () { this.client.reqMktData(reqId, contract, genericTickType, snapShot);});
    },

    cancelMktData: function (reqId) {
        this.doAction(function () { this.client.cancelMktData(reqId);}.bind(this));
    },

    placeOrder: function (orderId, contrct, order) {
        this.doAction(function () { this.client.placeOrder(orderId, contrct, order); }.bind(this));
    },

    placeOrderDetailed: function (orderId, contract, action, quantity, orderType, price, auxPrice) {
        this.doAction(function () { this.client.placeOrder(orderId, contract, action, quantity, orderType, price, auxPrice); });
    },

    cancelOrder: function (orderId) {
        this.doAction(function () { this.client.cancelOrder(orderId); });
    },

    reqOpenOrders: function () {
        this.doAction(function () { this.client.reqOpenOrders(); });
    },

    reqAccountUpdates: function (subscribe, acctCode) {
        this.doAction(function () { this.client.reqAccountUpdates(subscribe, acctCode); });
    },

    reqExecutions: function (reqId, clientId, acctCode, time, symbol, secType, exchange, side) {
        this.doAction(function () { this.client.reqExecutions(reqId, clientId, acctCode, time, symbol, secType, exchange, side); });
    },

    //
    //.reqIds(1)
    //.checkMessages()
    //.reqContractDetails(reqId, contract)
    //.reqMktDepth(tickerId, contract, numRows )
    //.cancelMktDepth(tickerId)
    //.reqNewsBulletins(allMsgs)
    //.cancelNewsBulletins()
    //.setServerLogLevel(level)
    //.reqAutoOpenOrders(bAutoBind)
    //.reqAllOpenOrders()
    //.reqManagedAccts()
    //.requestFA( ) // not yet implemented
    //.replaceFA( ) // not yet implemented
    //.reqHistoricalData(id, contract, endDateTime, durationStr, barSizeSetting, whatToShow, useRTH, formatDate)
    //.exerciseOptions(tickerId, contract, exerciseAction, exerciseQuantity, account, override )
    //.cancelHistoricalData(tickerId)
    //.reqRealtimeBars(tickerId, contract, barSize, whatToShow, useRTH)
    //.cancelRealTimeBars(tickerId)
    //.cancelScannerSubscription(tickerId)
    //.reqScannerParameters()
    //.reqScannerSubscription(tickerId, subscription)
    //.reqCurrentTime() // not implemented
    //.reqFundamentalData( reqId, contract, reportType )
    //.cancelFundamentalData(reqId)
    //.calculateImpliedVolatility( reqId, contract, optionPrice, underPrice )
    //.calculateOptionPrice( reqId, contract, volatility, underPrice )
    //.cancelCalculateImpliedVolatility(reqId)
    //.cancelCalculateOptionPrice(reqId)
    //.reqGlobalCancel()
    //.reqMarketDataType(marketDataType)
    //.reqPositions()
    //.cancelPositions()
    //.reqAccountSummary( reqId, groupName, tags )
    //.cancelAccountSummary(reqId)
    //.verifyRequest( apiName, apiVersion )
    //.verifyMessage( apiData )
    //.queryDisplayGroups( reqId )
    //.subscribeToGroupEvents( reqId, groupId )
    //.updateDisplayGroup( reqId, contractInfo )
    //.unsubscribeFromGroupEvents( reqId )

    doAction: function (action) {
        this.limiter.removeTokens(1, function (err, remainingRequests) {
            action()
        });
    },

    addReqId: function () {
        this.client.reqIds(1);
    }

};

exports = module.exports = {
    "NodeIBApi": NodeIBApi,
    "messageIds": messageIds,
    "contract": contract,
    "execution": execution,
    "scannerSubscription": scannerSubscription,
    "contractDetails": contractDetails,
    "order": order
};
