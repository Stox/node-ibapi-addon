function scannerSubscription() {
}

scannerSubscription.prototype.numberOfRows = -1; //int 
scannerSubscription.prototype.instrument = ''; //IBString 
scannerSubscription.prototype.locationCode = ''; //IBString 
scannerSubscription.prototype.scanCode = ''; //IBString 
scannerSubscription.prototype.abovePrice = Number.MAX_VALUE; //double 
scannerSubscription.prototype.belowPrice = Number.MAX_VALUE; //double 
scannerSubscription.prototype.aboveVolume = Number.MAX_VALUE; //int 
scannerSubscription.prototype.marketCapAbove = Number.MAX_VALUE; //double 
scannerSubscription.prototype.marketCapBelow = Number.MAX_VALUE; //double 
scannerSubscription.prototype.moodyRatingAbove = ''; //IBString 
scannerSubscription.prototype.moodyRatingBelow = ''; //IBString 
scannerSubscription.prototype.spRatingAbove = ''; //IBString 
scannerSubscription.prototype.spRatingBelow = ''; //IBString 
scannerSubscription.prototype.maturityDateAbove = ''; //IBString 
scannerSubscription.prototype.maturityDateBelow = ''; //IBString 
scannerSubscription.prototype.couponRateAbove = Number.MAX_VALUE; //double 
scannerSubscription.prototype.couponRateBelow = Number.MAX_VALUE; //double 
scannerSubscription.prototype.excludeConvertible = 0; //int 
scannerSubscription.prototype.averageOptionVolumeAbove = 0; //int 
scannerSubscription.prototype.scannerSettingPairs = ''; //IBString 
scannerSubscription.prototype.stockTypeFilter = ''; //IBString 

exports.createScannerSub = function() {
  var newScanSub = new scannerSubscription();
  return newScanSub;
}