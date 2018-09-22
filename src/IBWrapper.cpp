#include "IBWrapper.h"

#include "EClientSocket.h"
#include "EReaderSignal.h"
#include "Contract.h"

#include <iostream>
#include <ctime>

namespace
{
   const int PING_DEADLINE = 2; // seconds
   const boost::posix_time::milliseconds TIMER_INTERVAL(250);
}

IBWrapper::IBWrapper() :
   mOsSignal(2000),//2-seconds timeout,
   mClient(new EClientSocket(this, &mOsSignal)),
   mSleepDeadline(0),
   mOrderId(0),
   mReader(nullptr),
   mExtraAuth(false)
{
   mTimerThread = std::make_unique<std::thread>([this]{
      mEventTimer = std::make_unique<boost::asio::deadline_timer>(mIOService, TIMER_INTERVAL);
      mEventTimer->async_wait([this](const boost::system::error_code &ec) {this->CheckMessages(ec); });
      mIOService.run(); });
   
}

IBWrapper::~IBWrapper()
{
   if (mReader)
      delete mReader;

   delete mClient;
}

void IBWrapper::CheckMessages(const boost::system::error_code& /*e*/)
{
   if (mReader != nullptr)
   {
      std::cout << "tick" << std::endl;
      mReader->processMsgs();
   }
   

   // Reschedule the timer for 1 second in the future:
   mEventTimer->expires_at(mEventTimer->expires_at() + TIMER_INTERVAL);
   // Posts the timer event
   mEventTimer->async_wait([this](const boost::system::error_code &ec) {this->CheckMessages(ec); });
}

bool IBWrapper::Connect(const char *host, unsigned int port, int clientId)
{
   // trying to connect
   printf("Connecting to %s:%d clientId:%d\n", !(host && *host) ? "127.0.0.1" : host, port, clientId);

   bool bRes = mClient->eConnect(host, port, clientId, mExtraAuth);
   printf("Connected to %s:%d clientId:%d\n", mClient->host().c_str(), mClient->port(), clientId);

   // Timeout needed to make sure the client connection has truly finished...
   Sleep(1000);

   mReader = new EReader(mClient, &mOsSignal);

   mReader->start();
   // Timeout needed to make sure the reader initialization has truly finished...
   Sleep(1000);

   //Contract contract;
   //contract.symbol = "IBKR";
   //contract.secType = "STK";
   //contract.currency = "USD";
   //In the API side, NASDAQ is always defined as ISLAND
   //contract.exchange = "ISLAND";
   //mClient->reqMktData(1004, contract, "233,236,258", false, TagValueListSPtr());
   //mClient->reqNewsProviders();
   //Sleep(40);
   //mReader->processMsgs();
   return bRes;
}

void IBWrapper::Disconnect() const
{
   mClient->eDisconnect();

   printf("Disconnected\n");
   ConnectionStatusChanged();
}

bool IBWrapper::IsConnected() const
{
   return mClient->isConnected();
}

void IBWrapper::SetConnectOptions(const std::string& connectOptions)
{
   mClient->setConnectOptions(connectOptions);
}

void IBWrapper::tickPrice(TickerId tickerId,
                          TickType field,
                          double price,
                          const TickAttrib& attrib)
{
   std::cout << "--- tickPrice Start ---" << std::endl;
   std::cout << "Ticker id : " << tickerId << std::endl;
   std::cout << "Field : " << field << std::endl;
   std::cout << "Price : " << price << std::endl;
   std::cout << "CanAutoExecute : " << attrib.askPastHigh << std::endl;
   std::cout << "..." << std::endl;
   std::cout << "--- tickPrice End ---" << std::endl;
}

void IBWrapper::tickSize(TickerId tickerId, TickType field, int size)
{
   std::cout << "--- tickSize Start ---" << std::endl;
   std::cout << "Ticker id : " << tickerId << std::endl;
   std::cout << "Field : " << field << std::endl;
   std::cout << "size : " << size << std::endl;
   std::cout << "--- tickSize End ---" << std::endl;
}

void IBWrapper::tickOptionComputation(
   TickerId tickerId, TickType tickType, double impliedVol, double delta,
   double optPrice, double pvDividend, double gamma,
   double vega, double theta, double undPrice)
{
   std::cout << "tickOptionComputation" << std::endl;
}

void IBWrapper::tickGeneric(TickerId tickerId, TickType tickType, double value)
{
   std::cout << "tickGeneric" << std::endl;
}

void IBWrapper::tickString(
   TickerId tickerId, TickType tickType, const std::string& value)
{
   std::cout << "--- tickString Start ---" << std::endl;
   std::cout << "Ticker id : " << tickerId << std::endl;
   std::cout << "Tick type : " << tickType << std::endl;
   std::cout << "Value : " << value << std::endl;
   std::cout << "--- tickString End ---" << std::endl;
}

void IBWrapper::tickEFP(
   TickerId tickerId, TickType tickType, double basisPoints,
   const std::string& formattedBasisPoints,
   double totalDividends, int holdDays,
   const std::string& futureLastTradeDate,
   double dividendImpact, double dividendsToLastTradeDate)
{
   std::cout << "tickEFP" << std::endl;
}

void IBWrapper::orderStatus(
   OrderId orderId, const std::string& status, double filled,
   double remaining, double avgFillPrice, int permId, int parentId,
   double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice)
{
   std::cout << "orderStatus" << std::endl;
}

void IBWrapper::openOrder(
   OrderId orderId, const Contract&, const Order&, const OrderState&)
{
   std::cout << "openOrder" << std::endl;
}

void IBWrapper::openOrderEnd()
{
   std::cout << "openOrderEnd" << std::endl;
}

void IBWrapper::winError(const std::string& str, int lastError)
{
   std::cout << "winError" << std::endl;
}

void IBWrapper::connectionClosed()
{
   std::cout << "connectionClosed" << std::endl;
   ConnectionStatusChanged();
}

void IBWrapper::updateAccountValue(
   const std::string& key, const std::string& val,
   const std::string& currency, const std::string& accountName)
{
   std::cout << "updateAccountValue" << std::endl;
}

void IBWrapper::updatePortfolio(
   const Contract& contract, double position,
   double marketPrice, double marketValue, double averageCost,
   double unrealizedPNL, double realizedPNL, const std::string& accountName)
{
   std::cout << "updatePortfolio" << std::endl;
}

void IBWrapper::updateAccountTime(const std::string& timeStamp)
{
   std::cout << "updateAccountTime" << std::endl;
}

void IBWrapper::accountDownloadEnd(const std::string& accountName)
{
   std::cout << "accountDownloadEnd" << std::endl;
}

void IBWrapper::nextValidId(OrderId orderId)
{
   std::cout << "nextValidId : " << orderId << std::endl;
}

void IBWrapper::contractDetails(int reqId, const ContractDetails& contractDetails)
{
   std::cout << "contractDetails" << std::endl;
}

void IBWrapper::bondContractDetails(int reqId, const ContractDetails& contractDetails)
{
   std::cout << "bondContractDetails" << std::endl;
}

void IBWrapper::contractDetailsEnd(int reqId)
{
   std::cout << "contractDetailsEnd" << std::endl;
}

void IBWrapper::execDetails(
   int reqId, const Contract& contract, const Execution& execution)
{
   std::cout << "execDetails" << std::endl;
}

void IBWrapper::execDetailsEnd(int reqId)
{
   std::cout << "execDetailsEnd" << std::endl;
}

void IBWrapper::error(
   int id, int errorCode, const std::string& errorString)
{
   std::cout << "error : " << errorString << std::endl;
}

void IBWrapper::updateMktDepth(TickerId id, int position, int operation, int side,
                               double price, int size)
{
   std::cout << "updateMktDepth" << std::endl;
}

void IBWrapper::updateMktDepthL2(TickerId id, int position, const std::string& marketMaker, int operation,
                                 int side, double price, int siz)
{
   std::cout << "updateMktDepthL2" << std::endl;
}

void IBWrapper::updateNewsBulletin(
   int msgId, int msgType,
   const std::string& newsMessage, const std::string& originExch)
{
   std::cout << "updateNewsBulletin" << std::endl;
}

void IBWrapper::managedAccounts(const std::string& accountsList)
{
   std::cout << "managedAccounts : " + accountsList << std::endl;
}

void IBWrapper::receiveFA(faDataType pFaDataType, const std::string& cxml)
{
   std::cout << "receiveFA" << std::endl;
}

void IBWrapper::historicalData(
   TickerId reqId, const Bar& bar)
{

   std::cout << " --- historicalData Start --- " << std::endl;
   std::cout << "Request id : " << reqId << std::endl;
   std::cout << "Close : " << bar.close << std::endl;
   std::cout << "Count : " << bar.count << std::endl;
   std::cout << "High : " << bar.high << std::endl;
   std::cout << "Low : " << bar.low << std::endl;
   std::cout << "Open : " << bar.open << std::endl;
   std::cout << "Volume : " << bar.volume << std::endl;
   std::cout << "Wap : " << bar.wap << std::endl;
   std::cout << " --- historicalData End --- " << std::endl;
}

void IBWrapper::historicalDataEnd(
   int reqId, const std::string& startDateStr, const std::string& endDateStr) 
{
   std::cout << " historicalDataEnd  " << std::endl;
}

void IBWrapper::scannerParameters(const std::string& xml)
{
   std::cout << "scannerParameters" << std::endl;
}

void IBWrapper::scannerData(
   int reqId, int rank, const ContractDetails& contractDetails,
   const std::string& distance, const std::string& benchmark, const std::string& projection,
   const std::string& legsStr)
{
   std::cout << "scannerData" << std::endl;
}

void IBWrapper::scannerDataEnd(int reqId)
{
   std::cout << "scannerDataEnd" << std::endl;
}

void IBWrapper::realtimeBar(
   TickerId reqId, long time, double open, double high, double low, double close,
   long volume, double wap, int count)
{
   std::cout << "realtimeBar" << std::endl;
}

void IBWrapper::currentTime(long time)
{
   std::cout << "currentTime : " << time << std::endl;
}

void IBWrapper::fundamentalData(TickerId reqId, const std::string& data)
{
   std::cout << "fundamentalData" << std::endl;
}

void IBWrapper::deltaNeutralValidation(int reqId, const DeltaNeutralContract& deltaNeutralContract)
{
   std::cout << "deltaNeutralValidation" << std::endl;
}

void IBWrapper::tickSnapshotEnd(int reqId)
{
   std::cout << "tickSnapshotEnd" << std::endl;
}

void IBWrapper::marketDataType(TickerId reqId, int marketDataType)
{
   std::cout << "marketDataType" << std::endl;
}

void IBWrapper::commissionReport(const CommissionReport& commissionReport)
{
   std::cout << "commissionReport" << std::endl;
}

void IBWrapper::position(
   const std::string& account, const Contract& contract,
   double position, double avgCost)
{
   std::cout << "position" << std::endl;
}

void IBWrapper::positionEnd()
{
   std::cout << "positionEnd" << std::endl;
}

void IBWrapper::accountSummary(
   int reqId, const std::string& account,
   const std::string& tag, const std::string& value,
   const std::string& curency)
{
   std::cout << "accountSummary" << std::endl;
}

void IBWrapper::accountSummaryEnd(int reqId)
{
   std::cout << "accountSummaryEnd" << std::endl;
}

void IBWrapper::verifyMessageAPI(const std::string& apiData)
{
   std::cout << "verifyMessageAPI" << std::endl;
}

void IBWrapper::verifyCompleted(
   bool isSuccessful, const std::string& errorText)
{
   std::cout << "verifyCompleted" << std::endl;
}

void IBWrapper::displayGroupList(int reqId, const std::string& groups)
{
   std::cout << "displayGroupList" << std::endl;
}

void IBWrapper::displayGroupUpdated(int reqId, const std::string& contractInfo)
{
   std::cout << "displayGroupUpdated" << std::endl;
}

void IBWrapper::verifyAndAuthMessageAPI(
   const std::string& apiData, const std::string& xyzChallange)
{
   std::cout << "verifyAndAuthMessageAPI" << std::endl;
}

void IBWrapper::verifyAndAuthCompleted(
   bool isSuccessful, const std::string& errorText)
{
   std::cout << "verifyAndAuthCompleted" << std::endl;
}

void IBWrapper::connectAck()
{
   std::cout << "connectAck" << std::endl;
   ConnectionStatusChanged();
}

void IBWrapper::positionMulti(
   int reqId, const std::string& account,
   const std::string& modelCode, const Contract& contract,
   double pos, double avgCost)
{
   std::cout << "positionMulti" << std::endl;
}

void IBWrapper::positionMultiEnd(int reqId)
{
   std::cout << "positionMultiEnd" << std::endl;
}

void IBWrapper::accountUpdateMulti(
   int reqId, const std::string& account,
   const std::string& modelCode, const std::string& key,
   const std::string& value, const std::string& currency)
{
   std::cout << "accountUpdateMulti" << std::endl;
}

void IBWrapper::accountUpdateMultiEnd(int reqId)
{
   std::cout << "accountUpdateMultiEnd" << std::endl;
}

void IBWrapper::securityDefinitionOptionalParameter(
   int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass,
   const std::string& multiplier, const std::set<std::string>& expirations, const std::set<double>& strikes)
{
   std::cout << "securityDefinitionOptionalParameter" << std::endl;
}

void IBWrapper::securityDefinitionOptionalParameterEnd(int reqId)
{
   std::cout << "securityDefinitionOptionalParameterEnd" << std::endl;
}

void IBWrapper::softDollarTiers(
   int reqId, const std::vector<SoftDollarTier> &tiers)
{
   std::cout << "softDollarTiers" << std::endl;
}

void IBWrapper::familyCodes(const std::vector<FamilyCode> &familyCodes) 
{
   std::cout << "familyCodes" << std::endl;
}

void IBWrapper::symbolSamples(int reqId, const std::vector<ContractDescription> &contractDescriptions)
{
   std::cout << "symbolSamples" << std::endl;
}
void IBWrapper::mktDepthExchanges(const std::vector<DepthMktDataDescription> &depthMktDataDescriptions)
{
   std::cout << "mktDepthExchanges" << std::endl;
}
void IBWrapper::tickNews(int tickerId, time_t timeStamp, const std::string& providerCode, const std::string& articleId, const std::string& headline, const std::string& extraData)
{
   std::cout << "tickNews" << std::endl;
}
void IBWrapper::smartComponents(int reqId, const SmartComponentsMap& theMap)
{
   std::cout << "smartComponents" << std::endl;
}
void IBWrapper::tickReqParams(int tickerId, double minTick, const std::string& bboExchange, int snapshotPermissions)
{
   std::cout << "tickReqParams" << std::endl;
}
void IBWrapper::newsProviders(const std::vector<NewsProvider> &newsProviders)
{
   std::cout << "newsProviders" << std::endl;
}
void IBWrapper::newsArticle(int requestId, int articleType, const std::string& articleText)
{
   std::cout << "newsArticle" << std::endl;
}
void IBWrapper::historicalNews(int requestId, const std::string& time, const std::string& providerCode, const std::string& articleId, const std::string& headline)
{
   std::cout << "historicalNews" << std::endl;
}
void IBWrapper::historicalNewsEnd(int requestId, bool hasMore)
{
   std::cout << "historicalNewsEnd" << std::endl;
}
void IBWrapper::headTimestamp(int reqId, const std::string& headTimestamp)
{
   std::cout << "headTimestamp" << std::endl;
}
void IBWrapper::histogramData(int reqId, const HistogramDataVector& data)
{
   std::cout << "histogramData" << std::endl;
}
void IBWrapper::historicalDataUpdate(TickerId reqId, const Bar& bar)
{
   std::cout << "historicalDataUpdate" << std::endl;
}
void IBWrapper::rerouteMktDataReq(int reqId, int conid, const std::string& exchange)
{
   std::cout << "rerouteMktDataReq" << std::endl;
}
void IBWrapper::rerouteMktDepthReq(int reqId, int conid, const std::string& exchange)
{
   std::cout << "rerouteMktDepthReq" << std::endl;
}
void IBWrapper::marketRule(int marketRuleId, const std::vector<PriceIncrement> &priceIncrements)
{
   std::cout << "marketRule" << std::endl;
}
void IBWrapper::pnl(int reqId, double dailyPnL, double unrealizedPnL, double realizedPnL)
{
   std::cout << "pnl" << std::endl;
}
void IBWrapper::pnlSingle(int reqId, int pos, double dailyPnL, double unrealizedPnL, double realizedPnL, double value)
{
   std::cout << "pnlSingle" << std::endl;
}
void IBWrapper::historicalTicks(int reqId, const std::vector<HistoricalTick> &ticks, bool done)
{
   std::cout << "historicalTicks" << std::endl;
}
void IBWrapper::historicalTicksBidAsk(int reqId, const std::vector<HistoricalTickBidAsk> &ticks, bool done)
{
   std::cout << "historicalTicksBidAsk" << std::endl;
}
void IBWrapper::historicalTicksLast(int reqId, const std::vector<HistoricalTickLast> &ticks, bool done)
{
   std::cout << "historicalTicksLast" << std::endl;
}
void IBWrapper::tickByTickAllLast(int reqId, int tickType, time_t time, double price, int size, const TickAttrib& attribs, const std::string& exchange, const std::string& specialConditions)
{
   std::cout << "tickByTickAllLast" << std::endl;
}
void IBWrapper::tickByTickBidAsk(int reqId, time_t time, double bidPrice, double askPrice, int bidSize, int askSize, const TickAttrib& attribs)
{
   std::cout << "tickByTickBidAsk" << std::endl;
}
void IBWrapper::tickByTickMidPoint(int reqId, time_t time, double midPoint)
{
   std::cout << "tickByTickMidPoint" << std::endl;
}