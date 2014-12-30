var assert = require("assert")
var addon = require('../build/Release/NodeIbapiAddon');


var obj = new addon.NodeIbapi();

describe('obj', function() {
  describe('#connect()', function() {
    it('should return true when successfully connected', function() {
      assert.equal(true, obj.connect('127.0.0.1',7496,0));
    })
  })
})

describe('obj', function() {
  describe('#isConnected()', function() {
    it('should return true when client is currently connected', function() {
      assert.equal(true, obj.isConnected());
    })
  })
})

// test is not correct
describe('obj', function() {
  describe('#disconnect()', function() {
    it('should return false when successfully disconnected', function() {
      obj.disconnect();
      assert.equal(false, obj.isConnected());
    })
  })
})


// write the test for purchase by sending purchase order
//  and then checking the order status`
