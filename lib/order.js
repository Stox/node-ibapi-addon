// Use this for placeOrder
function order() {
}

  // order identifier
order.prototype.orderId = 0;   //long     ;
order.prototype.clientId = 0;   //long     ;
order.prototype.permId = 0;   //long     ;

  // main order fields
order.prototype.action = '';   //IBString ;
order.prototype.totalQuantity = 0;   //long     ;
order.prototype.orderType = '';   //IBString ;
order.prototype.lmtPrice = Number.MAX_VALUE;    //double   ;
order.prototype.auxPrice = Number.MAX_VALUE;    //double   ;

  // extended order fields
order.prototype.tif = '';   //IBString ;           // "Time in Force" - DAY, GTC, etc.
order.prototype.ocaGroup = '';   //IBString ;      // one cancels all group name
order.prototype.ocaType = 0;   //int      ;       // 1 = CANCEL_WITH_BLOCK, 2 = REDUCE_WITH_BLOCK, 3 = REDUCE_NON_BLOCK
order.prototype.orderRef = '';   //IBString ;      // order reference
order.prototype.transmit = true;   //bool     ;      // if false, order will be created but not transmited
order.prototype.parentId = 0;   //long     ;      // Parent order Id, to associate Auto STP or TRAIL orders with the original order.
order.prototype.blockOrder = false;   //bool     ;
order.prototype.sweepToFill = false;   //bool     ;
order.prototype.displaySize = 0;   //int      ;
order.prototype.triggerMethod = 0;   //int      ; // 0=Default, 1=Double_Bid_Ask, 2=Last, 3=Double_Last, 4=Bid_Ask, 7=Last_or_Bid_Ask, 8=Mid-point
order.prototype.outsideRth = false;   //bool     ;
order.prototype.hidden = false;   //bool     ;
order.prototype.goodAfterTime = '';   //IBString ;    // Format: 20060505 08:00:00 {time zone}
order.prototype.goodTillDate = '';   //IBString ;     // Format: 20060505 08:00:00 {time zone}
order.prototype.rule80A = '';   //IBString ; // Individual = 'I', Agency = 'A', AgentOtherMember = 'W', IndividualPTIA = 'J', AgencyPTIA = 'U', AgentOtherMemberPTIA = 'M', IndividualPT = 'K', AgencyPT = 'Y', AgentOtherMemberPT = 'N'
order.prototype.allOrNone = false;   //bool     ;
order.prototype.minQty = Number.MAX_VALUE;   //int      ;
order.prototype.percentOffset = Number.MAX_VALUE;    //double   ; // REL orders only
order.prototype.overridePercentageConstraints = false;   //bool     ;
order.prototype.trailStopPrice = Number.MAX_VALUE;    //double   ; // TRAILLIMIT orders only
order.prototype.trailingPercent = Number.MAX_VALUE;    //double   ;

  // financial advisors only

  // institutional (ie non-cleared) only

  // SMART routing only
order.prototype.discretionaryAmt = 0;    //double   ;
order.prototype.eTradeOnly = true;   //bool     ;
order.prototype.firmQuoteOnly = true;   //bool     ;
order.prototype.nbboPriceCap = Number.MAX_VALUE;    //double   ;
order.prototype.optOutSmartRouting = false;   //bool     ;

  // BOX exchange orders only
order.prototype.auctionStrategy = 0   //int      ; // AUCTION_MATCH, AUCTION_IMPROVEMENT, AUCTION_TRANSPARENT
order.prototype.startingPrice = Number.MAX_VALUE;    //double   ;
order.prototype.stockRefPrice = Number.MAX_VALUE;    //double   ;
order.prototype.delta = Number.MAX_VALUE;    //double   ;

  // pegged to stock and VOL orders only
order.prototype.stockRangeLower = Number.MAX_VALUE;    //double   ;
order.prototype.stockRangeUpper = Number.MAX_VALUE;    //double   ;

  // VOLATILITY ORDERS ONLY
order.prototype.volatility = Number.MAX_VALUE;    //double   ;
order.prototype.volatilityType = Number.MAX_VALUE;   //int      ;     // 1=daily, 2=annual
order.prototype.deltaNeutralOrderType = '';   //IBString ;
order.prototype.deltaNeutralAuxPrice = Number.MAX_VALUE;    //double   ;
order.prototype.deltaNeutralConId = 0;   //long     ;
order.prototype.deltaNeutralSettlingFirm = '';   //IBString ;
order.prototype.deltaNeutralClearingAccount = '';   //IBString ;
order.prototype.deltaNeutralClearingIntent = '';   //IBString ;
order.prototype.deltaNeutralOpenClose = '';   //IBString ;
order.prototype.deltaNeutralShortSale = false;   //bool     ;
order.prototype.deltaNeutralShortSaleSlot = 0;   //int      ;
order.prototype.deltaNeutralDesignatedLocation = '';   //IBString ;
order.prototype.continuousUpdate = false;   //bool     ;
order.prototype.referencePriceType = Number.MAX_VALUE;   //int      ; // 1=Average, 2 = BidOrAsk

  // COMBO ORDERS ONLY

  // SCALE ORDERS ONLY
order.prototype.scaleInitLevelSize = Number.MAX_VALUE;   //int      ;
order.prototype.scaleSubsLevelSize = Number.MAX_VALUE;   //int      ;
order.prototype.scalePriceIncrement = Number.MAX_VALUE;    //double   ;
order.prototype.scalePriceAdjustValue = Number.MAX_VALUE;    //double   ;
order.prototype.scalePriceAdjustInterval = Number.MAX_VALUE;   //int      ;
order.prototype.scaleProfitOffset = Number.MAX_VALUE;    //double   ;
order.prototype.scaleAutoReset = false;   //bool     ;
order.prototype.scaleInitPosition = Number.MAX_VALUE;   //int      ;
order.prototype.scaleInitFillQty = Number.MAX_VALUE;   //int      ;
order.prototype.scaleRandomPercent = false;   //bool     ;

  // HEDGE ORDERS
order.prototype.hedgeType = '';   //IBString ;  // 'D' - delta, 'B' - beta, 'F' - FX, 'P' - pair
order.prototype.hedgeParam = '';   //IBString ; // 'beta=X' value for beta hedge, 'ratio=Y' for pair hedge

  // Clearing info
order.prototype.account = '';   //IBString ; // IB account
order.prototype.settlingFirm = '';   //IBString ;
order.prototype.clearingAccount = '';   //IBString ; // True beneficiary of the order
order.prototype.clearingIntent = '';   //IBString ; // "" (Default), "IB", "Away", "PTA" (PostTrade)

  // ALGO ORDERS ONLY

  // What-if
// order.prototype.whatIf =    //bool     ;

  // Not Held
// order.prototype.notHeld =    //bool     ;

exports.createOrder = function() {
  var newOrder = new order();
  return newOrder;
}
