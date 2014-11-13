// module for event driven methods
var addon = require('./build/Release/NodeIbapiAddon');
var contract = require('./lib/contract');
var order = require('./lib/order');
var execution = require('./lib/execution');
var contractDetails = require('./lib/contractDetails');
var scannerSubscription = require('./lib/scannerSubscription');
var events = require ("events");
var util = require ("util");

for (var key in events.EventEmitter.prototype) {
  addon.NodeIbapi.prototype[key] = events.EventEmitter.prototype[key];
}

addon.NodeIbapi.prototype.funcQueue = [];

addon.NodeIbapi.prototype.addReqId = function () {
  this.reqIds(1);
}

addon.NodeIbapi.prototype.doReqFunc = function () {
  if (this.funcQueue[0] != null) {
      (this.funcQueue.shift())();
  } 
}

addon.NodeIbapi.prototype.processIbMsg = function () {
  this.checkMessages();
  this.processMsg();

  retTickPrice = this.getTickPrice();
  retTickSize = this.getTickSize();
  retTickOptionComputation = this.getTickOptionComputation();
  retTickGeneric = this.getTickGeneric();
  retTickString = this.getTickString();
  retTickEFP = this.getTickEFP();
  retOrderStatus = this.getOrderStatus();
  retOpenOrder = this.getOpenOrder();
  retOpenOrderEnd = this.getOpenOrderEnd();
  retWinError = this.getWinError();
  retConnectionClosed = this.getConnectionClosed();
  retUpdateAccountValue = this.getUpdateAccountValue();
  retUpdatePortfolio = this.getUpdatePortfolio();
  retUpdateAccountTime = this.getUpdateAccountTime();
  retAccountDownloadEnd = this.getAccountDownloadEnd();
  retNextValidId = this.getNextValidId();
  retContractDetails = this.getContractDetails();
  retBondContractDetails = this.getBondContractDetails();
  retContractDetailsEnd = this.getContractDetailsEnd();
  retExecDetails = this.getExecDetails();
  retExecDetailsEnd = this.getExecDetailsEnd();
  retError = this.getError();
  retUpdateMktDepth = this.getUpdateMktDepth();
  retUpdateMktDepthL2 = this.getUpdateMktDepthL2();
  retUpdateNewsBulletin = this.getUpdateNewsBulletin();
  retManagedAccounts = this.getManagedAccounts();
  retReceiveFA = this.getReceiveFA();
  retHistoricalData = this.getHistoricalData();
  retScannerParameters = this.getScannerParameters();
  retScannerData = this.getScannerData();
  retScannerDataEnd = this.getScannerDataEnd();
  retRealtimeBar = this.getRealtimeBar();
  retFundamentalData = this.getFundamentalData();
  retDeltaNeutralValidation = this.getDeltaNeutralValidation();
  retTickSnapshotEnd = this.getTickSnapshotEnd();
  retMarketDataType = this.getMarketDataType();
  retCommissionReport = this.getCommissionReport();
  retPosition = this.getPosition();
  retPositionEnd = this.getPositionEnd();
  retAccountSummary = this.getAccountSummary();
  retAccountSummaryEnd = this.getAccountSummaryEnd();
  retVerifyMessageAPI = this.getVerifyMessageAPI();
  retVerifyCompleted = this.getVerifyCompleted();
  retDisplayGroupList = this.getDisplayGroupList();
  retDisplayGroupUpdated = this.getDisplayGroupUpdated();

  if (retTickPrice.isValid) {
    this.emit('tickPrice', retTickPrice);
  }
  if (retTickSize.isValid) {
    this.emit('tickSize', retTickSize);
  }
  if (retTickOptionComputation.isValid) {
    this.emit('tickOptionComputation', retTickOptionComputation);
  }
  if (retTickGeneric.isValid) {
    this.emit('tickGeneric', retTickGeneric);
  }
  if (retTickString.isValid) {
    this.emit('tickString', retTickString);
  }
  if (retTickEFP.isValid) {
    this.emit('tickEFP', retTickEFP);
  }
  if (retOrderStatus.isValid) {
    this.emit('orderStatus', retOrderStatus);
  }
  if (retOpenOrder.isValid) {
    this.emit('openOrder', retOpenOrder);
  }
  if (retOpenOrderEnd.isValid) {
    this.emit('openOrderEnd', retOpenOrderEnd);
  }
  if (retWinError.isValid) {
    this.emit('clientError', retWinError);
  }
  if (retConnectionClosed.isValid) {
    this.emit('connectionClosed', retConnectionClosed);
  }
  if (retUpdateAccountValue.isValid) {
    this.emit('updateAccountValue', retUpdateAccountValue);
  }
  if (retUpdatePortfolio.isValid) {
    this.emit('updatePortfolio', retUpdatePortfolio);
  }
  if (retUpdateAccountTime.isValid) {
    this.emit('updateAccountTime', retUpdateAccountTime);
  }
  if (retAccountDownloadEnd.isValid) {
    this.emit('accountDownloadEnd', retAccountDownloadEnd);
  }
  if (retNextValidId.isValid) {
    this.emit('nextValidId', retNextValidId);
  }
  if (retContractDetails.isValid) {
    this.emit('contractDetails', retContractDetails);
  }
  if (retBondContractDetails.isValid) {
    this.emit('bondContractDetails', retBondContractDetails);
  }
  if (retContractDetailsEnd.isValid) {
    this.emit('contractDetailsEnd', retContractDetailsEnd);
  }
  if (retExecDetails.isValid) {
    this.emit('execDetails', retExecDetails);
  }
  if (retExecDetailsEnd.isValid) {
    this.emit('execDetailsEnd', retExecDetailsEnd);
  }
  if (retError.isValid) {
    this.emit('svrError', retError);
  }
  if (retUpdateMktDepth.isValid) {
    this.emit('updateMktDepth', retUpdateMktDepth);
  }
  if (retUpdateMktDepthL2.isValid) {
    this.emit('updateMktDepthL2', retUpdateMktDepthL2);
  }
  if (retUpdateNewsBulletin.isValid) {
    this.emit('updateNewsBulletin', retUpdateNewsBulletin);
  }
  if (retManagedAccounts.isValid) {
    this.emit('managedAccounts', retManagedAccounts);
  }
  if (retReceiveFA.isValid) {
    this.emit('receiveFA', retReceiveFA);
  }
  if (retHistoricalData.isValid) {
    this.emit('historicalData', retHistoricalData);
  }
  if (retScannerParameters.isValid) {
    this.emit('scannerParameters', retScannerParameters);
  }
  if (retScannerData.isValid) {
    this.emit('scannerData', retScannerData);
  }
  if (retScannerDataEnd.isValid) {
    this.emit('scannerDataEnd', retScannerDataEnd);
  }
  if (retRealtimeBar.isValid) {
    this.emit('realtimeBar', retRealtimeBar);
  }
  if (retFundamentalData.isValid) {
    this.emit('fundamentalData', retFundamentalData);
  }
  if (retDeltaNeutralValidation.isValid) {
    this.emit('deltaNeutralValidation', retDeltaNeutralValidation);
  }
  if (retTickSnapshotEnd.isValid) {
    this.emit('tickSnapshotEnd', retTickSnapshotEnd);
  }
  if (retMarketDataType.isValid) {
    this.emit('marketDataType', retMarketDataType);
  }
  if (retCommissionReport.isValid) {
    this.emit('commissionReport', retCommissionReport);
  }
  if (retPosition.isValid) {
    this.emit('position', retPosition);
  }
  if (retPositionEnd.isValid) {
    this.emit('positionEnd', retPositionEnd);
  }
  if (retAccountSummary.isValid) {
    this.emit('accountSummary', retAccountSummary);
  }
  if (retAccountSummaryEnd.isValid) {
    this.emit('accountSummaryEnd', retAccountSummaryEnd);
  }
  if (retNextValidId.isValid) {
    this.emit('nextValidId', retNextValidId);
  }
  if (retVerifyMessageAPI.isValid) {
    this.emit('verifyMessageAPI', retVerifyMessageAPI);
  }
  if (retVerifyCompleted.isValid) {
    this.emit('verifyCompleted', retVerifyCompleted);
  }
  if (retDisplayGroupList.isValid) {
    this.emit('displayGroupList', retDisplayGroupList);
  }
  if (retDisplayGroupUpdated.isValid) {
    this.emit('displayGroupUpdated', retDisplayGroupUpdated);
  }

  if (!this.isConnected())
    this.emit('disconnected');
}

addon.NodeIbapi.prototype.connectToIb = function (host,port,clientId) {
  if (this.connect(host,port,clientId))
    this.emit('connected');
  else
    this.emit('connectionFail');
}

exports = module.exports = {
  NodeIbapi: function() {
    console.log("DEPRECATED: calling NodeIbapi() directly from " + 
      "package is being deprecated. Please call it from " + 
      "'addon'. See barebones.js in examples folder.");
    return addon.NodeIbapi;}(),
  addon: addon,
  contract: contract,
  execution: execution,
  scannerSubscription: scannerSubscription,
  contractDetails: contractDetails,
  order: order
};
