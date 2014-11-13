var contract = require('./contract').createContract();

function contractDetails() {
}

contractDetails.prototype.summary = contract; // Contract  
contractDetails.prototype.marketName = ''; // IBString  
contractDetails.prototype.minTick = 0.0; // double    
contractDetails.prototype.orderTypes = ''; // IBString  
contractDetails.prototype.validExchanges = ''; // IBString  
contractDetails.prototype.priceMagnifier = 0; // long    
contractDetails.prototype.underConId = 0; // int     
contractDetails.prototype.longName = ''; // IBString  
contractDetails.prototype.contractMonth = ''; // IBString  
contractDetails.prototype.industry = ''; // IBString  
contractDetails.prototype.category = ''; // IBString  
contractDetails.prototype.subcategory = ''; // IBString  
contractDetails.prototype.timeZoneId = ''; // IBString  
contractDetails.prototype.tradingHours = ''; // IBString  
contractDetails.prototype.liquidHours = ''; // IBString  
contractDetails.prototype.evRule = ''; // IBString  
contractDetails.prototype.evMultiplier = 0.0; // double 

// Bond values   
contractDetails.prototype.cusip = ''; // IBString  
contractDetails.prototype.ratings = ''; // IBString  
contractDetails.prototype.descAppend = ''; // IBString  
contractDetails.prototype.bondType = ''; // IBString  
contractDetails.prototype.couponType = ''; // IBString  
contractDetails.prototype.callable = false; // bool    
contractDetails.prototype.putable = false; // bool    
contractDetails.prototype.coupon = 0.0; // double    
contractDetails.prototype.convertible = false; // bool    
contractDetails.prototype.maturity = ''; // IBString  
contractDetails.prototype.issueDate = ''; // IBString  
contractDetails.prototype.nextOptionDate = ''; // IBString  
contractDetails.prototype.nextOptionType = ''; // IBString  
contractDetails.prototype.nextOptionPartial = false; // bool    
contractDetails.prototype.notes = ''; // IBString

// TODO make surpport for tagvaluelist

exports.createContractDetails = function () {
  var newContractDetails = new contractDetails();
  return newContractDetails;
}
