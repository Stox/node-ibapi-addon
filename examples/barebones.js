// This file shows you one example of a barebones program that handles
//  server error messages.

// Required package name is 'ibapi' If you use your own project path,
//  just use require('ibapi') from your project root as you would 
//  normally do.
var addon = require('../ibapi'),
  messageIds = addon.messageIds,
  contract = addon.contract,
  order = addon.order;

// The api object handles the client methods. For details, refer to 
//  IB API documentation.
var api = new addon.NodeIbapi();

// Interactive Broker requires that you use orderId for every new order
//  inputted. The orderId is incremented everytime you submit an order.
//  Make sure you keep track of this.
var orderId = -1;

// Here we specify the event handlers.
//  Please follow this guideline for event handlers:
//  1. Add handlers to listen to messages
//  2. Each handler must have be a function (message, callback) signature
//  3. Each handler must call the callback() to signal that processing
//     finished
var handleValidOrderId = function (message, callback) {
  orderId = message.orderId;
  console.log('next order Id is ' + orderId);
  callback();
};

var handleServerError = function (message, callback) {
  console.log('Error: ' + message.id.toString() + '-' +
              message.errorCode.toString() + '-' +
              message.errorString.toString());
  callback();
};

var handleClientError = function (message, callback) {
  console.log('clientError');
  console.log(JSON.stringify(message));
  callback();
};

var handleDisconnected = function (message, callback) {
  console.log('disconnected');
  callback();
  process.exit(1);
};

// After that, you must register the event handler with a messageId
//  For list of valid messageIds, see messageIds.js file.
api.handlers[messageIds.nextValidId] = handleValidOrderId;
api.handlers[messageIds.svrError] = handleServerError;
api.handlers[messageIds.clientError] = handleClientError;
api.handlers[messageIds.disconnected] = handleDisconnected;

// Connect to the TWS client or IB Gateway
var connected = api.connect('127.0.0.1', 7496, 0);

// Once connected, start processing incoming and outgoing messages
if (connected) {
  api.beginProcessing();
}
