#pragma once
#include "EWrapper.h"
#include "EReaderOSSignal.h"
#include "EReader.h"

#include <boost/signals2.hpp>
#include <boost/asio.hpp> 

#include <vector>
#include <string>

class EClientSocket;

class IBWrapper : public EWrapper
{

public:

   IBWrapper();
   ~IBWrapper();

   /// Signal emitted when the instrument set changed
   boost::signals2::signal<void()> ConnectionStatusChanged;

   /// Periodically check if the reader has any messages to be processed
   void IBWrapper::CheckMessages(const boost::system::error_code& /*e*/);

   /// function to call from moodels
   bool Connect(const char * host, unsigned int port, int clientId = 0);
   void Disconnect() const;
   bool IsConnected() const;
   void SetConnectOptions(const std::string&);

   /// Overriden function from IB parent
   virtual void tickPrice(TickerId tickerId,
                          TickType field,
                          double price, 
                          const TickAttrib& attrib) override;

   virtual void tickSize(TickerId tickerId, TickType field, int size) override;

   virtual void tickOptionComputation(
      TickerId tickerId, TickType tickType, double impliedVol, double delta,
      double optPrice, double pvDividend, double gamma,
      double vega, double theta, double undPrice) override;

   virtual void tickGeneric(
      TickerId tickerId, TickType tickType, double value) override;

   virtual void tickString(
      TickerId tickerId, TickType tickType, const std::string& value) override;

   virtual void tickEFP(
      TickerId tickerId, TickType tickType, double basisPoints,
      const std::string& formattedBasisPoints,
      double totalDividends, int holdDays,
      const std::string& futureLastTradeDate,
      double dividendImpact, double dividendsToLastTradeDate) override;

   virtual void orderStatus(
      OrderId orderId, const std::string& status, double filled,
      double remaining, double avgFillPrice, int permId, int parentId,
      double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice) override;

   virtual void openOrder(
      OrderId orderId, const Contract&, const Order&, const OrderState&) override;

   virtual void openOrderEnd() override;

   virtual void winError(const std::string& str, int lastError) override;

   virtual void connectionClosed() override;

   virtual void updateAccountValue(
      const std::string& key, const std::string& val,
      const std::string& currency, const std::string& accountName) override;

   virtual void updatePortfolio(
      const Contract& contract, double position,
      double marketPrice, double marketValue, double averageCost,
      double unrealizedPNL, double realizedPNL, const std::string& accountName) override;

   virtual void updateAccountTime(const std::string& timeStamp) override;

   virtual void accountDownloadEnd(const std::string& accountName) override;

   virtual void nextValidId(OrderId orderId) override;

   virtual void contractDetails(int reqId, const ContractDetails& contractDetails) override;

   virtual void bondContractDetails(
      int reqId, const ContractDetails& contractDetails) override;

   virtual void contractDetailsEnd(int reqId) override;

   virtual void execDetails(
      int reqId, const Contract& contract, const Execution& execution) override;

   virtual void execDetailsEnd(int reqId) override;

   virtual void error(
      int id, int errorCode, const std::string& errorString) override;

   virtual void updateMktDepth(TickerId id, int position, int operation, int side,
                               double price, int size) override;

   virtual void updateMktDepthL2(TickerId id, int position, const std::string& marketMaker, int operation,
                                 int side, double price, int siz) override;

   virtual void updateNewsBulletin(
      int msgId, int msgType,
      const std::string& newsMessage, const std::string& originExch) override;

   virtual void managedAccounts(const std::string& accountsList) override;

   virtual void receiveFA(faDataType pFaDataType, const std::string& cxml) override;

   virtual void historicalData(
      TickerId reqId, const Bar& bar) override;

   virtual void historicalDataEnd(
      int reqId, const std::string& startDateStr, const std::string& endDateStr) override;

   virtual void scannerParameters(const std::string& xml);

   virtual void scannerData(int reqId, int rank, const ContractDetails& contractDetails,
                            const std::string& distance, const std::string& benchmark, const std::string& projection,
                            const std::string& legsStr) override;

   virtual void scannerDataEnd(int reqId) override;

   virtual void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
                            long volume, double wap, int count) override;

   virtual void currentTime(long time) override;

   virtual void fundamentalData(TickerId reqId, const std::string& data) override;

   virtual void deltaNeutralValidation(int reqId, const DeltaNeutralContract& deltaNeutralContract) override;

   virtual void tickSnapshotEnd(int reqId) override;

   virtual void marketDataType(TickerId reqId, int marketDataType) override;

   virtual void commissionReport(const CommissionReport& commissionReport) override;

   virtual void position(
      const std::string& account, const Contract& contract,
      double position, double avgCost) override;

   virtual void positionEnd() override;

   virtual void accountSummary(
      int reqId, const std::string& account,
      const std::string& tag, const std::string& value,
      const std::string& curency) override;

   virtual void accountSummaryEnd(int reqId) override;

   /////////////////////////////
   virtual void verifyMessageAPI(const std::string& apiData) override;

   virtual void verifyCompleted(
      bool isSuccessful, const std::string& errorText) override;

   virtual void displayGroupList(int reqId, const std::string& groups) override;

   virtual void displayGroupUpdated(int reqId, const std::string& contractInfo) override;

   virtual void verifyAndAuthMessageAPI(
      const std::string& apiData, const std::string& xyzChallange) override;

   virtual void verifyAndAuthCompleted(
      bool isSuccessful, const std::string& errorText) override;

   virtual void connectAck() override;

   virtual void positionMulti(
      int reqId, const std::string& account,
      const std::string& modelCode, const Contract& contract,
      double pos, double avgCost) override;

   virtual void positionMultiEnd(int reqId) override;

   virtual void accountUpdateMulti(int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency) override;

   virtual void accountUpdateMultiEnd(int reqId) override;

   virtual void securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass,
                                                    const std::string& multiplier, const std::set<std::string>& expirations, const std::set<double>& strikes) override;
   virtual void securityDefinitionOptionalParameterEnd(int reqId) override;

   virtual void softDollarTiers(int reqId, const std::vector<SoftDollarTier> &tiers) override;

   virtual void familyCodes(const std::vector<FamilyCode> &familyCodes) override;
   virtual void symbolSamples(int reqId, const std::vector<ContractDescription> &contractDescriptions) override;
   virtual void mktDepthExchanges(const std::vector<DepthMktDataDescription> &depthMktDataDescriptions) override;
   virtual void tickNews(int tickerId, time_t timeStamp, const std::string& providerCode, const std::string& articleId, const std::string& headline, const std::string& extraData) override;
   virtual void smartComponents(int reqId, const SmartComponentsMap& theMap) override;
   virtual void tickReqParams(int tickerId, double minTick, const std::string& bboExchange, int snapshotPermissions) override;
   virtual void newsProviders(const std::vector<NewsProvider> &newsProviders) override;
   virtual void newsArticle(int requestId, int articleType, const std::string& articleText) override;
   virtual void historicalNews(int requestId, const std::string& time, const std::string& providerCode, const std::string& articleId, const std::string& headline) override;
   virtual void historicalNewsEnd(int requestId, bool hasMore) override;
   virtual void headTimestamp(int reqId, const std::string& headTimestamp) override;
   typedef std::vector<HistogramEntry> HistogramDataVector;
   virtual void histogramData(int reqId, const HistogramDataVector& data) override;
   virtual void historicalDataUpdate(TickerId reqId, const Bar& bar) override;
   virtual void rerouteMktDataReq(int reqId, int conid, const std::string& exchange) override;
   virtual void rerouteMktDepthReq(int reqId, int conid, const std::string& exchange) override;
   virtual void marketRule(int marketRuleId, const std::vector<PriceIncrement> &priceIncrements) override;
   virtual void pnl(int reqId, double dailyPnL, double unrealizedPnL, double realizedPnL) override;
   virtual void pnlSingle(int reqId, int pos, double dailyPnL, double unrealizedPnL, double realizedPnL, double value) override;
   virtual void historicalTicks(int reqId, const std::vector<HistoricalTick> &ticks, bool done) override;
   virtual void historicalTicksBidAsk(int reqId, const std::vector<HistoricalTickBidAsk> &ticks, bool done) override;
   virtual void historicalTicksLast(int reqId, const std::vector<HistoricalTickLast> &ticks, bool done) override;
   virtual void tickByTickAllLast(int reqId, int tickType, time_t time, double price, int size, const TickAttrib& attribs, const std::string& exchange, const std::string& specialConditions) override;
   virtual void tickByTickBidAsk(int reqId, time_t time, double bidPrice, double askPrice, int bidSize, int askSize, const TickAttrib& attribs) override;
   virtual void tickByTickMidPoint(int reqId, time_t time, double midPoint) override;

protected:
   EClientSocket* mClient;
   EReaderOSSignal mOsSignal;

   time_t mSleepDeadline;

   OrderId mOrderId;
   EReader *mReader;
   bool mExtraAuth;

   /// Timer to handle all ib thread events
   std::unique_ptr <std::thread> mTimerThread;
   boost::asio::io_service mIOService;
   std::unique_ptr<boost::asio::deadline_timer> mEventTimer;
};