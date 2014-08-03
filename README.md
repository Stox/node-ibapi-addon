node-ibapi-addon
================

Interactive Brokers API addon for Node.js compatible with IB API 9.70

This addon uses the latest stable Interactive Brokers POSIX C++ API.

Author: Jae Yang - [dchem] (https://github.com/dchem/)

For direct JavaScript implementation of IB API for Node.js, please visit Pilwon Huh's [node-ib] (https://github.com/pilwon/node-ib).


### Change Notes:

* 2014-04-22 - 0.1.17 - Compatibility fix for API 9.70
* 2014-03-17 - 0.1.13 - Smoother installation to multiple OSes
* 2014-01-17 - 0.1.0  - all EWrapper events bound in ibapi.js
* 2014-01-09 - 0.0.4  - get commands output JS objects
* 2013-12-29 - 0.0.3  - Added EventEmitter support
* 2013-09-26 - 0.0.2  - EClientSocket hooks and EWrapper hooks
* 2013-09-02 - 0.0.1  - Initial commit - connect, disconnect, isConnected works

### Installation dependency
* Install Python 2.7
* Install node-gyp
```
npm install node-gyp -g
```
* Install unzip if Linux
```
sudo apt-get install unzip
```

### Additional installation dependency for Windows:
* Install MinGW
* Install msys-unzip instead of unzip
```
mingw-get install msys-unzip
```
* Install Microsoft Visual Studio

### Installation from NPM:
```
npm install ibapi
```

For Windows with MSVS 2013:
```
npm install ibapi --msvs_version=2013
```

For Windows with MSVS 2012:
```
npm install ibapi --msvs_version=2012
```

### Installation from git repo:

1. Make sure to have node-gyp installed
2. Run the preinstall.sh which does the following:
 * Download the latest stable IB API into /import
 * Copy the contents of IB API package's 
    IBJts/source/PosixClient/Shared into /import directory
 * Copy the contents of IB API package's
    IBJts/source/PosixClient/src into /import directory
 * Add #define IB_USE_STD_STRING into the following files in /import directory:
    EClientSocketBase.cpp
    EPosixClientSocket.cpp
3. ```node-gyp rebuild```
4. If build fails because you have VS2012, use ```node-gyp --msvs_version=2012 rebuild```

### Usage
1. Require ibapi
2. Bind processIbMsg to setInterval
3. Bind doReqFunc to setInterval once nextValidId is received
4. Define what happens in the callbacks for each events
5. Push request functions to function queue funcQueue
6. Invoke connectToIb
7. ...
8. Profit!

```js
var addon = require('ibapi');
var obj = new addon.NodeIbapi();

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
obj.on('connected', function () {
  console.log('connected');
  setInterval(processIbMsg,0.1);
  obj.funcQueue.push(addReqId);
})
.once('nextValidId', function (data) {
  orderId = data.orderId;
  console.log('nextValidId: ' + orderId);
  setInterval(doReqFunc,100);
})
.on('disconnected', function () {
  console.log('disconnected');
  process.exit(1);
})

obj.connectToIb('127.0.0.1',7496,0);

```
### Module Wrapper Commands
The following commands are extended commands in ibapi.js.
```js
.addReqId()     // requests nextValidId, wraps reqIds(1)
.doReqFunc()    // runs request functions in a function queue
.processIbMsg() // processes incoming and outgoing messages
.connectToIb()  // connects to IB and returns a connected or connectionFail event
```
### Client methods
```js
// Msg processor
//  a POSIX implementation of network message handler
.processMsg()

// IB API Commands
//  Following commands are used for requesting specific action 
//  through IB API
//  Whenever you need to input contract, it must be js object contract see
//  lib/contract.js
//  Likewise, for scanner subscription, see lib/scannerSubscription.js

.connect(host,port,clientId)
.disconnect()
.isConnected()
.reqMktData(reqId, contract, genericTickType, snapShot)
.cancelMktData(reqId)
.placeOrder(orderId, contract, action, quantity, orderType, price, auxPrice)
.cancelOrder(orderId)
.reqOpenOrders()
.reqAccountUpdates(subscribe, acctCode)
.reqExecutions(reqId, clientId, acctCode, time, symbol, secType, exchange, side)
.reqIds(1)
.checkMessages()
.reqContractDetails(reqId, contract)
.reqMktDepth(tickerId, contract, numRows ) 
.cancelMktDepth(tickerId)
.reqNewsBulletins(allMsgs)
.cancelNewsBulletins()
.setServerLogLevel(level)
.reqAutoOpenOrders(bAutoBind)
.reqAllOpenOrders()
.reqManagedAccts()
.requestFA( ) // not yet implemented
.replaceFA( ) // not yet implemented
.reqHistoricalData(id, contract, endDateTime, durationStr, barSizeSetting, whatToShow, useRTH, formatDate)
.exerciseOptions(tickerId, contract, exerciseAction, exerciseQuantity, account, override )
.cancelHistoricalData(tickerId)
.reqRealtimeBars(tickerId, contract, barSize, whatToShow, useRTH)
.cancelRealTimeBars(tickerId)
.cancelScannerSubscription(tickerId)
.reqScannerParameters()
.reqScannerSubscription(tickerId, subscription)
.reqCurrentTime() // not implemented
.reqFundamentalData( reqId, contract, reportType )
.cancelFundamentalData(reqId)
.calculateImpliedVolatility( reqId, contract, optionPrice, underPrice )
.calculateOptionPrice( reqId, contract, volatility, underPrice )
.cancelCalculateImpliedVolatility(reqId)
.cancelCalculateOptionPrice(reqId)
.reqGlobalCancel()
.reqMarketDataType(marketDataType)
.reqPositions()
.cancelPositions()
.reqAccountSummary( reqId, groupName, tags )
.cancelAccountSummary(reqId)
```

### EWrapper Events
```js
// processIbMsg events - returns arrays
.on('tickPrice', function( tickPrice ) )
.on('tickSize', function( tickSize ) )
.on('tickOptionComputation', function( tickOptionComputation ) )
.on('tickGeneric', function( tickGeneric ) )
.on('tickString', function( tickString ) )
.on('tickEFP', function( tickEFP ) )
.on('orderStatus', function( orderStatus ) )
.on('openOrder', function( openOrder ) )
.on('openOrderEnd', function( openOrderEnd ) )
.on('clientError', function( clientError ) )
.on('connectionClosed', function( connectionClosed ) )
.on('updateAccountValue', function( updateAccountValue ) )
.on('updatePortfolio', function( updatePortfolio ) )
.on('updateAccountTime', function( updateAccountTime ) )
.on('accountDownloadEnd', function( accountDownloadEnd ) )
.on('nextValidId', function( nextValidId ) )
.on('contractDetails', function( contractDetails ) )
.on('bondContractDetails', function( bondContractDetails ) )
.on('contractDetailsEnd', function( contractDetailsEnd ) )
.on('execDetails', function( execDetails ) )
.on('execDetailsEnd', function( execDetailsEnd ) )
.on('svrError', function( svrError ) )
.on('updateMktDepth', function( updateMktDepth ) )
.on('updateMktDepthL2', function( updateMktDepthL2 ) )
.on('updateNewsBulletin', function( updateNewsBulletin ) )
.on('managedAccounts', function( managedAccounts ) )
.on('receiveFA', function( receiveFA ) )
.on('historicalData', function( historicalData ) )
.on('scannerParameters', function( scannerParameters ) )
.on('scannerData', function( scannerData ) )
.on('scannerDataEnd', function( scannerDataEnd ) )
.on('realtimeBar', function( realtimeBar ) )
.on('fundamentalData', function( fundamentalData ) )
.on('deltaNeutralValidation', function( deltaNeutralValidation ) )
.on('tickSnapshotEnd', function( tickSnapshotEnd ) )
.on('marketDataType', function( marketDataType ) )
.on('commissionReport', function( commissionReport ) )
.on('position', function( position ) )
.on('positionEnd', function( positionEnd ) )
.on('accountSummary', function( accountSummary ) )
.on('accountSummaryEnd', function( accountSummaryEnd ) )
.on('nextValidId', function( nextValidId ) )

.on('disconnected', function ())

// connectToIb events
.on('connected', function())
.on('connectionFail' function())
```

### Tests:
Uses mocha, so install it.

### Issues:
* See issues list in https://github.com/dchem/node-ibapi-addon/issues?state=open

### License
Copyright (c) 2014 Jae Yang. See LICENSE file for license rights and limitations (MIT).
