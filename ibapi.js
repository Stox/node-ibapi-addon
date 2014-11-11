// module for event driven methods
var addon = require('./build/Release/NodeIbapiAddon'),
    contract = require('./lib/contract'),
    order = require('./lib/order'),
    execution = require('./lib/execution'),
    contractDetails = require('./lib/contractDetails'),
    scannerSubscription = require('./lib/scannerSubscription'),
    messageIds = require('./messageIds'),
    async = require("async");

function NodeIBApi() {
    this.client = addon.NodeIbapi();
    this.handlers = {};

    this._messageQueue = async.queue(this._consumeMessage, 1);

    this._messageQueue.pause();
}

NodeIBApi.prototype = {

    _consumeMessage: function (callback) {

        var messages = this.processMessage();

        async.eachSeries(_.keys(messages), function (key, cb) {

            if (key in this.handlers) {
                var handler = this.handlers[key];

                var message = messages[key];

                handler(message, cb);
            }

        }.bind(this), callback);

    },

    processMessage: function () {
        var messages = {};
        this.checkMessages();
        this.processMsg();

        function checkMessage(messageId, objectData) {
            if (objectData.isValid) {
                messages[messageId] = objectData;
            }
        }

        checkMessage(messageIds.tickPrice, this.getTickPrice());
        checkMessage(messageIds.tickSize, this.getTickSize());
        checkMessage(messageIds.tickOptionComputation, this.getTickOptionComputation());
        checkMessage(messageIds.tickGeneric, this.getTickGeneric());
        checkMessage(messageIds.tickString, this.getTickString());
        checkMessage(messageIds.tickEFP, this.getTickEFP());
        checkMessage(messageIds.orderStatus, this.getOrderStatus());
        checkMessage(messageIds.openOrder, this.getOpenOrder());
        checkMessage(messageIds.openOrderEnd, this.getOpenOrderEnd());
        checkMessage(messageIds.clientError, this.getWinError());
        checkMessage(messageIds.connectionClosed, this.getConnectionClosed());
        checkMessage(messageIds.updateAccountValue, this.getUpdateAccountValue());
        checkMessage(messageIds.updatePortfolio, this.getUpdatePortfolio());
        checkMessage(messageIds.updateAccountTime, this.getUpdateAccountTime());
        checkMessage(messageIds.accountDownloadEnd, this.getAccountDownloadEnd());
        checkMessage(messageIds.nextValidId, this.getNextValidId());
        checkMessage(messageIds.contractDetails, this.getContractDetails());
        checkMessage(messageIds.retBondContractDetails, this.getBondContractDetails());
        checkMessage(messageIds.contractDetailsEnd, this.getContractDetailsEnd());
        checkMessage(messageIds.execDetails, this.getExecDetails());
        checkMessage(messageIds.execDetailsEnd, this.getExecDetailsEnd());
        checkMessage(messageIds.svrError, this.getError());
        checkMessage(messageIds.updateMktDepth, this.getUpdateMktDepth());
        checkMessage(messageIds.updateMktDepthL2, this.getUpdateMktDepthL2());
        checkMessage(messageIds.updateNewsBulletin, this.getUpdateNewsBulletin());
        checkMessage(messageIds.managedAccounts, this.getManagedAccounts());
        checkMessage(messageIds.receiveFA, this.getReceiveFA());
        checkMessage(messageIds.historicalData, this.getHistoricalData());
        checkMessage(messageIds.scannerParameters, this.getScannerParameters());
        checkMessage(messageIds.scannerData, this.getScannerData());
        checkMessage(messageIds.scannerDataEnd, this.getScannerDataEnd());
        checkMessage(messageIds.realtimeBar, this.getRealtimeBar());
        checkMessage(messageIds.fundamentalData, this.getFundamentalData());
        checkMessage(messageIds.deltaNeutralValidation, this.getDeltaNeutralValidation());
        checkMessage(messageIds.tickSnapshotEnd, this.getTickSnapshotEnd());
        checkMessage(messageIds.marketDataType, this.getMarketDataType());
        checkMessage(messageIds.commissionReport, this.getCommissionReport());
        checkMessage(messageIds.position, this.getPosition());
        checkMessage(messageIds.positionEnd, this.getPositionEnd());
        checkMessage(messageIds.accountSummary, this.getAccountSummary());
        checkMessage(messageIds.accountSummaryEnd, this.getAccountSummaryEnd());
        checkMessage(messageIds.verifyMessageAPI, this.getVerifyMessageAPI());
        checkMessage(messageIds.verifyCompleted, this.getVerifyCompleted());
        checkMessage(messageIds.displayGroupList, this.getDisplayGroupList());
        checkMessage(messageIds.displayGroupUpdated, this.getDisplayGroupUpdated());

        if (!this.isConnected()) {
            messages[messageIds.disconnected] = {};
        }

        return messages;
    },

    connect: function (host, port, clientId) {
        return this.client.connect(host, port, clientId)
    },

    beginProcessing: function () {
        this._messageQueue.resume()
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
