#include "bip_importable.hpp"

//--------------------------------------------------------------------------------
//Definitions generated from chips sources
//--------------------------------------------------------------------------------

void UserMachine_init([[maybe_unused]] chips_int& httpResponse, [[maybe_unused]] chips_int& startTime, [[maybe_unused]] chips_int& endTime, [[maybe_unused]] chips_int& id, [[maybe_unused]] chips_int& maxNbData, [[maybe_unused]] chips_bool& active, [[maybe_unused]] chips_int& currentRequest, [[maybe_unused]] chips_int& httpRequest, [[maybe_unused]] chips_int& lastRequest, [[maybe_unused]] chips_bool& newPage, [[maybe_unused]] chips_bool& requiresAuth, [[maybe_unused]] chips_int& time, [[maybe_unused]] chips_bool& waiting, [[maybe_unused]] chips_any& fromUserToInternet_out)
{
    active = chips_bool{false};
    waiting = chips_bool{false};
    time = chips_int{0};
    requiresAuth = chips_bool{false};
    newPage = chips_bool{false};
    currentRequest = chips_int{0};
    httpRequest = chips_int{0};
    lastRequest = chips_int{0};
}

void UserMachine_then([[maybe_unused]] chips_int& httpResponse, [[maybe_unused]] chips_int& startTime, [[maybe_unused]] chips_int& endTime, [[maybe_unused]] chips_int& id, [[maybe_unused]] chips_int& maxNbData, [[maybe_unused]] chips_bool& active, [[maybe_unused]] chips_any& computerID, [[maybe_unused]] chips_int& currentRequest, [[maybe_unused]] chips_int& httpRequest, [[maybe_unused]] chips_int& lastRequest, [[maybe_unused]] chips_bool& newPage, [[maybe_unused]] chips_bool& requiresAuth, [[maybe_unused]] chips_int& time, [[maybe_unused]] chips_bool& waiting, [[maybe_unused]] chips_any& fromUserToInternet_out)
{
    computerID = id;
    newPage = (httpResponse != chips_int{0}) && is_fresh(httpResponse);
    requiresAuth = (httpResponse < chips_int{0}) || requiresAuth;
    active = (time >= startTime) && (time < endTime);
    if (!active)
    {
        httpRequest = chips_int{0};
    }
    else
    {
        if (!waiting)
        {
            currentRequest = static_cast<chips_int>((randin01() * (static_cast<chips_float>((maxNbData - chips_int{1}))))) + chips_int{1};
            httpRequest = (maxNbData) * (computerID - chips_int{1}) + currentRequest;
            if (requiresAuth)
            {
                httpRequest = -httpRequest;
            }
            lastRequest = httpRequest;
            waiting = chips_bool{true};
        }
        else
        {
            if (newPage)
            {
                if (requiresAuth)
                {
                    currentRequest = static_cast<chips_int>((randin01() * (static_cast<chips_float>((maxNbData - chips_int{1}))))) + chips_int{1};
                    httpRequest = -(maxNbData * (computerID - chips_int{1}) + currentRequest);
                    waiting = chips_bool{true};
                }
                else
                {
                    waiting = chips_bool{false};
                    httpRequest = chips_int{0};
                }
            }
            else
            {
                waiting = chips_bool{true};
                httpRequest = chips_int{0};
            }
        }
    }
    time = time + chips_int{1};
    fromUserToInternet_out = httpRequest;
}

void ServerMachine_init([[maybe_unused]] chips_int& fromInternet, [[maybe_unused]] chips_int& wpServed, [[maybe_unused]] chips_int& maxNbData, [[maybe_unused]] chips_int& currentRequest, [[maybe_unused]] chips_int& httpResponse, [[maybe_unused]] chips_int& nbDataToOutput, [[maybe_unused]] chips_bool& requestFound, [[maybe_unused]] chips_int& requestList, [[maybe_unused]] chips_bool& userAuthToOutput, [[maybe_unused]] chips_int& userIDToOutput, [[maybe_unused]] chips_any& fromServerToInternet_out, [[maybe_unused]] chips_any& nbData_out, [[maybe_unused]] chips_any& userID_out, [[maybe_unused]] chips_any& userAuth_out)
{
    httpResponse = chips_int{0};
    currentRequest = chips_int{0};
    requestFound = chips_bool{false};
    requestList = zeros(chips_int{100});
}

void ServerMachine_then([[maybe_unused]] chips_int& fromInternet, [[maybe_unused]] chips_int& wpServed, [[maybe_unused]] chips_int& maxNbData, [[maybe_unused]] chips_int& currentRequest, [[maybe_unused]] chips_int& httpResponse, [[maybe_unused]] chips_int& nbDataToOutput, [[maybe_unused]] chips_bool& requestFound, [[maybe_unused]] chips_int& requestList, [[maybe_unused]] chips_bool& userAuthToOutput, [[maybe_unused]] chips_int& userIDToOutput, [[maybe_unused]] chips_any& fromServerToInternet_out, [[maybe_unused]] chips_any& nbData_out, [[maybe_unused]] chips_any& userID_out, [[maybe_unused]] chips_any& userAuth_out)
{
    requestList[currentRequest] = chips_int{0};
    {
        auto i0 = range(100);
        for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
            if (fromInternet[i].to_chips() != chips_int{0})
            {
                requestList[i] = fromInternet[i].to_chips();
            }
        }
    }
    {
        auto i0 = range(100);
        for(chips_int reqShift{0}; reqShift < i0.size(); reqShift = reqShift+chips_int{1}) {
            if (!requestFound && (requestList[(currentRequest + reqShift) % chips_int{100}].to_chips() != chips_int{0}))
            {
                requestFound = chips_bool{true};
                currentRequest = (currentRequest + reqShift) % chips_int{100};
            }
        }
    }
    httpResponse = wpServed;
    if (requestFound)
    {
        userAuthToOutput = requestList[currentRequest].to_chips() < chips_int{0};
        if (userAuthToOutput)
        {
            nbDataToOutput = (-requestList[currentRequest].to_chips()) % (maxNbData);
            userIDToOutput = (-requestList[currentRequest].to_chips()) / (maxNbData) + chips_int{1};
        }
        else
        {
            nbDataToOutput = requestList[currentRequest].to_chips() % (maxNbData);
            userIDToOutput = requestList[currentRequest].to_chips() / (maxNbData) + chips_int{1};
        }
    }
    else
    {
        nbDataToOutput = chips_int{0};
        userIDToOutput = chips_int{0};
        userAuthToOutput = chips_bool{false};
    }
    fromServerToInternet_out = httpResponse;
    nbData_out = nbDataToOutput;
    userID_out = userIDToOutput;
    userAuth_out = userAuthToOutput;
}

void UserActionInterpreter_init([[maybe_unused]] chips_int& nbDataRcvd, [[maybe_unused]] chips_bool& authDataRcvd, [[maybe_unused]] chips_int& userIDRcvd, [[maybe_unused]] chips_any& nbData_out, [[maybe_unused]] chips_any& reqID_out, [[maybe_unused]] chips_any& authProvided_out)
{
}

void UserActionInterpreter_then([[maybe_unused]] chips_int& nbDataRcvd, [[maybe_unused]] chips_bool& authDataRcvd, [[maybe_unused]] chips_int& userIDRcvd, [[maybe_unused]] chips_any& nbData_out, [[maybe_unused]] chips_any& reqID_out, [[maybe_unused]] chips_any& authProvided_out)
{
    nbData_out = nbDataRcvd;
    reqID_out = userIDRcvd;
    authProvided_out = authDataRcvd;
}

void Authenticator_init([[maybe_unused]] chips_bool& authProvided, [[maybe_unused]] chips_any& isAuthenticated_out)
{
}

void Authenticator_then([[maybe_unused]] chips_bool& authProvided, [[maybe_unused]] chips_any& isAuthenticated_out)
{
    isAuthenticated_out = authProvided;
}

void RequestValidator_init([[maybe_unused]] chips_int& nbData, [[maybe_unused]] chips_int& requestID, [[maybe_unused]] chips_bool& isAuthenticated, [[maybe_unused]] chips_int& nbDataToFetch, [[maybe_unused]] chips_bool& needRedirection, [[maybe_unused]] chips_any& nbDataRequested_out, [[maybe_unused]] chips_any& userID_out, [[maybe_unused]] chips_any& redirection_out)
{
}

void RequestValidator_then([[maybe_unused]] chips_int& nbData, [[maybe_unused]] chips_int& requestID, [[maybe_unused]] chips_bool& isAuthenticated, [[maybe_unused]] chips_int& nbDataToFetch, [[maybe_unused]] chips_bool& needRedirection, [[maybe_unused]] chips_any& nbDataRequested_out, [[maybe_unused]] chips_any& userID_out, [[maybe_unused]] chips_any& redirection_out)
{
    needRedirection = (nbData > chips_int{5}) && (!isAuthenticated);
    if (!needRedirection)
    {
        nbDataToFetch = nbData;
    }
    else
    {
        nbDataToFetch = chips_int{0};
    }
    nbDataRequested_out = nbDataToFetch;
    userID_out = requestID;
    redirection_out = needRedirection;
}

void RequestLimiter_init([[maybe_unused]] chips_bool& redirection, [[maybe_unused]] chips_int& maxRequests, [[maybe_unused]] chips_int& userID, [[maybe_unused]] chips_int& nbDataToFetch, [[maybe_unused]] chips_int& nbAnsweredReqs, [[maybe_unused]] chips_int& currentNbRequests, [[maybe_unused]] chips_any& redirection_out, [[maybe_unused]] chips_any& userID_out, [[maybe_unused]] chips_any& dataQty_out)
{
    currentNbRequests = chips_int{0};
}

void RequestLimiter_then([[maybe_unused]] chips_bool& redirection, [[maybe_unused]] chips_int& maxRequests, [[maybe_unused]] chips_int& userID, [[maybe_unused]] chips_int& nbDataToFetch, [[maybe_unused]] chips_int& nbAnsweredReqs, [[maybe_unused]] chips_int& currentNbRequests, [[maybe_unused]] chips_any& redirection_out, [[maybe_unused]] chips_any& userID_out, [[maybe_unused]] chips_any& dataQty_out)
{
    currentNbRequests = currentNbRequests - nbAnsweredReqs;
    if (!redirection)
    {
        if ((currentNbRequests + chips_int{1}) <= maxRequests)
        {
            currentNbRequests = currentNbRequests + chips_int{1};
        }
        else
        {
            redirection = chips_bool{true};
            nbDataToFetch = chips_int{0};
        }
    }
    redirection_out = redirection;
    userID_out = userID;
    dataQty_out = nbDataToFetch;
}

void Cache_init([[maybe_unused]] chips_int& requestedData, [[maybe_unused]] chips_int& cacheSize, [[maybe_unused]] chips_int& cache, [[maybe_unused]] chips_bool& found, [[maybe_unused]] chips_int& foundIndex, [[maybe_unused]] chips_int& maxCacheSize, [[maybe_unused]] chips_int& minCacheSize, [[maybe_unused]] chips_int& newestDataIndex, [[maybe_unused]] chips_any& foundInCache_out)
{
    maxCacheSize = chips_int{100};
    minCacheSize = chips_int{10};
    cache = zeros(maxCacheSize);
    newestDataIndex = chips_int{0};
    found = chips_bool{false};
    foundIndex = chips_int{0};
}

void Cache_then([[maybe_unused]] chips_int& requestedData, [[maybe_unused]] chips_int& cacheSize, [[maybe_unused]] chips_int& cache, [[maybe_unused]] chips_bool& found, [[maybe_unused]] chips_int& foundIndex, [[maybe_unused]] chips_int& maxCacheSize, [[maybe_unused]] chips_int& minCacheSize, [[maybe_unused]] chips_int& newestDataIndex, [[maybe_unused]] chips_any& foundInCache_out)
{
    if (cacheSize > maxCacheSize)
    {
        cacheSize = maxCacheSize;
    }
    if (cacheSize < minCacheSize)
    {
        cacheSize = minCacheSize;
    }
    if (newestDataIndex >= cacheSize)
    {
        newestDataIndex = chips_int{0};
    }
    found = chips_bool{false};
    if (requestedData > chips_int{0})
    {
        {
            auto i0 = range(cacheSize);
            for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
                if ((!found) && (cache[i].to_chips() == requestedData))
                {
                    found = chips_bool{true};
                    foundIndex = i;
                }
            }
        }
        if (!found)
        {
            newestDataIndex = (newestDataIndex + chips_int{1}) % cacheSize;
            cache[newestDataIndex] = requestedData;
        }
        else
        {
            if (foundIndex < newestDataIndex)
            {
                chips_int temp;
                {
                    auto i0 = range(newestDataIndex-foundIndex);
                    for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
                        temp = cache[foundIndex + i + chips_int{1}].to_chips();
                        cache[foundIndex + i + chips_int{1}] = cache[foundIndex + i].to_chips();
                        cache[foundIndex + i] = temp;
                    }
                }
            }
            else
            {
                chips_int temp;
                {
                    auto i0 = range(cacheSize-foundIndex+newestDataIndex);
                    for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
                        temp = cache[(foundIndex + i + chips_int{1}) % cacheSize].to_chips();
                        cache[(foundIndex + i + chips_int{1}) % cacheSize] = cache[(foundIndex + i) % cacheSize].to_chips();
                        cache[(foundIndex + i) % cacheSize] = temp;
                    }
                }
            }
        }
    }
    foundInCache_out = found;
}

void DataProvider_init([[maybe_unused]] chips_bool& redirection, [[maybe_unused]] chips_int& userID, [[maybe_unused]] chips_int& dataQty, [[maybe_unused]] chips_bool& cacheResponse, [[maybe_unused]] chips_bool& cacheSearching, [[maybe_unused]] chips_int& currentlyTreatedUserRequest, [[maybe_unused]] chips_int& dataPerUserID, [[maybe_unused]] chips_int& dataToFetch, [[maybe_unused]] chips_int& httpResponse, [[maybe_unused]] chips_int& maxDifferentData, [[maybe_unused]] chips_int& maxUserID, [[maybe_unused]] chips_bool& oneLessPendingRequest, [[maybe_unused]] chips_float& time, [[maybe_unused]] chips_any& userID_out, [[maybe_unused]] chips_any& cacheRequest_out, [[maybe_unused]] chips_any& oneLessPendingRequest_out, [[maybe_unused]] chips_any& timeSpentOnReq_out, [[maybe_unused]] chips_any& enableTimeReading_out)
{
    maxDifferentData = chips_int{40};
    maxUserID = chips_int{100};
    dataPerUserID = zeros(maxUserID);
    currentlyTreatedUserRequest = -chips_int{1};
    httpResponse = chips_int{0};
    dataToFetch = chips_int{0};
    time = chips_float{0.0};
    cacheSearching = chips_bool{false};
    oneLessPendingRequest = chips_bool{false};
}

void DataProvider_then([[maybe_unused]] chips_bool& redirection, [[maybe_unused]] chips_int& userID, [[maybe_unused]] chips_int& dataQty, [[maybe_unused]] chips_bool& cacheResponse, [[maybe_unused]] chips_bool& cacheSearching, [[maybe_unused]] chips_int& currentlyTreatedUserRequest, [[maybe_unused]] chips_int& dataPerUserID, [[maybe_unused]] chips_int& dataToFetch, [[maybe_unused]] chips_int& httpResponse, [[maybe_unused]] chips_int& maxDifferentData, [[maybe_unused]] chips_int& maxUserID, [[maybe_unused]] chips_bool& oneLessPendingRequest, [[maybe_unused]] chips_float& time, [[maybe_unused]] chips_any& userID_out, [[maybe_unused]] chips_any& cacheRequest_out, [[maybe_unused]] chips_any& oneLessPendingRequest_out, [[maybe_unused]] chips_any& timeSpentOnReq_out, [[maybe_unused]] chips_any& enableTimeReading_out)
{
    if (oneLessPendingRequest)
    {
        time = chips_float{0.0};
    }
    oneLessPendingRequest = chips_bool{false};
    httpResponse = chips_int{0};
    if ((userID != chips_int{0}) && is_fresh(userID))
    {
        if (redirection)
        {
            httpResponse = -userID;
        }
        else
        {
            dataPerUserID[userID - chips_int{1}] = dataQty;
            if (currentlyTreatedUserRequest < chips_int{0})
            {
                currentlyTreatedUserRequest = userID - chips_int{1};
            }
        }
    }
    if ((currentlyTreatedUserRequest >= chips_int{0}) && (httpResponse == chips_int{0}))
    {
        if (cacheSearching)
        {
            if (cacheResponse)
            {
                time = time + chips_float{0.03};
            }
            else
            {
                time = time + chips_float{2.0};
            }
            dataPerUserID[currentlyTreatedUserRequest] = dataPerUserID[currentlyTreatedUserRequest].to_chips() - chips_int{1};
        }
        if (dataPerUserID[currentlyTreatedUserRequest].to_chips() > chips_int{0})
        {
            dataToFetch = static_cast<chips_int>((randin01() * (static_cast<chips_float>(maxDifferentData)))) + chips_int{1};
            cacheSearching = chips_bool{true};
        }
        else
        {
            httpResponse = currentlyTreatedUserRequest + chips_int{1};
            oneLessPendingRequest = chips_bool{true};
            chips_bool foundNewRequestPending;
            foundNewRequestPending = chips_bool{false};
            {
                auto i0 = range(maxUserID);
                for(chips_int userReqShift{0}; userReqShift < i0.size(); userReqShift = userReqShift+chips_int{1}) {
                    if ((!foundNewRequestPending) && (dataPerUserID[(currentlyTreatedUserRequest + userReqShift) % maxUserID].to_chips() > chips_int{0}))
                    {
                        foundNewRequestPending = chips_bool{true};
                        currentlyTreatedUserRequest = (currentlyTreatedUserRequest + userReqShift) % maxUserID;
                    }
                }
            }
            if (!foundNewRequestPending)
            {
                cacheSearching = chips_bool{false};
                currentlyTreatedUserRequest = -chips_int{1};
            }
            else
            {
                dataToFetch = static_cast<chips_int>((randin01() * (static_cast<chips_float>(maxDifferentData)))) + chips_int{1};
                cacheSearching = chips_bool{true};
            }
        }
    }
    userID_out = httpResponse;
    cacheRequest_out = dataToFetch;
    oneLessPendingRequest_out = oneLessPendingRequest;
    timeSpentOnReq_out = time;
    enableTimeReading_out = oneLessPendingRequest;
}

void allDataProvidersOutputs([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrAnswers_t _accumulator, [[maybe_unused]] AggrAnswers_t next_acc, [[maybe_unused]] AggrAnswers_t prev_acc, [[maybe_unused]] chips_int input, [[maybe_unused]] chips_any allDataProvidersOutputs_target)
{
    if (input != chips_int{0})
    {
        if (input > chips_int{0})
        {
            _accumulator.answers[input - chips_int{1}] = input;
        }
        else
        {
            _accumulator.answers[-input - chips_int{1}] = input;
        }
    }
    {
        auto i0 = range(100);
        for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
            if (prev_acc.answers[i].to_chips() != chips_int{0})
            {
                _accumulator.answers[i] = prev_acc.answers[i].to_chips();
            }
            if (next_acc.answers[i].to_chips() != chips_int{0})
            {
                _accumulator.answers[i] = next_acc.answers[i].to_chips();
            }
        }
    }
    next_acc.answers = _accumulator.answers;
    prev_acc.answers = _accumulator.answers;
    allDataProvidersOutputs_target = _accumulator.answers;
}

void WebPageService_init([[maybe_unused]] chips_int& respondToThisIDs, [[maybe_unused]] chips_int& currentRequestAnswered, [[maybe_unused]] chips_bool& requestFound, [[maybe_unused]] chips_int& requestsToAnswerTo, [[maybe_unused]] chips_any& httpResponse_out)
{
    currentRequestAnswered = chips_int{0};
    requestsToAnswerTo = zeros(chips_int{100});
    requestFound = chips_bool{false};
}

void WebPageService_then([[maybe_unused]] chips_int& respondToThisIDs, [[maybe_unused]] chips_int& currentRequestAnswered, [[maybe_unused]] chips_bool& requestFound, [[maybe_unused]] chips_int& requestsToAnswerTo, [[maybe_unused]] chips_any& httpResponse_out)
{
    requestsToAnswerTo[currentRequestAnswered] = chips_int{0};
    requestFound = chips_bool{false};
    {
        auto i0 = range(100);
        for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
            if (respondToThisIDs[i].to_chips() != chips_int{0})
            {
                requestsToAnswerTo[i] = respondToThisIDs[i].to_chips();
            }
        }
    }
    {
        auto i0 = range(100);
        for(chips_int reqShift{0}; reqShift < i0.size(); reqShift = reqShift+chips_int{1}) {
            if (!requestFound && (requestsToAnswerTo[(currentRequestAnswered + reqShift) % chips_int{100}].to_chips() != chips_int{0}))
            {
                currentRequestAnswered = (currentRequestAnswered + reqShift) % chips_int{100};
                requestFound = chips_bool{true};
            }
        }
    }
    httpResponse_out = requestsToAnswerTo[currentRequestAnswered].to_chips();
}

void responseToTheRightUser([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrFromInternet_t _accumulator, [[maybe_unused]] AggrFromInternet_t next_acc, [[maybe_unused]] AggrFromInternet_t prev_acc, [[maybe_unused]] const chips_int& ctx_computerID, [[maybe_unused]] chips_any responseToTheRightUser_target)
{
    chips_int id;
    id = _accumulator.fromInternet;
    if (_accumulator.fromInternet < chips_int{0})
    {
        id = -id;
    }
    chips_int returned;
    chips_int transmitted;
    if ((_accumulator.fromInternet == chips_int{0}) || (id != ctx_computerID))
    {
        returned = chips_int{0};
        transmitted = _accumulator.fromInternet;
    }
    else
    {
        returned = _accumulator.fromInternet;
        transmitted.stopFlag = true;
    }
    next_acc.fromInternet = transmitted;
    prev_acc.fromInternet = transmitted;
    responseToTheRightUser_target = returned;
}

void aggregatingRequests([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrRequests_t _accumulator, [[maybe_unused]] AggrRequests_t next_acc, [[maybe_unused]] AggrRequests_t prev_acc, [[maybe_unused]] const chips_int& ctx_computerID, [[maybe_unused]] chips_int input, [[maybe_unused]] chips_any aggregatingRequests_target)
{
    if (input != chips_int{0})
    {
        if (input < chips_int{0})
        {
            _accumulator.requests[-input] = input;
        }
        else
        {
            _accumulator.requests[input] = input;
        }
    }
    {
        auto i0 = range(100);
        for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
            if (prev_acc.requests[i].to_chips() != chips_int{0})
            {
                _accumulator.requests[i] = prev_acc.requests[i].to_chips();
            }
            if (next_acc.requests[i].to_chips() != chips_int{0})
            {
                _accumulator.requests[i] = next_acc.requests[i].to_chips();
            }
        }
    }
    next_acc.requests = _accumulator.requests;
    prev_acc.requests = _accumulator.requests;
    aggregatingRequests_target = _accumulator.requests;
}

void PidController_init([[maybe_unused]] chips_float& requested_time, [[maybe_unused]] chips_float& resulting_time, [[maybe_unused]] chips_bool& enabled, [[maybe_unused]] chips_float& d, [[maybe_unused]] chips_float& derivative, [[maybe_unused]] chips_float& dt, [[maybe_unused]] chips_float& error, [[maybe_unused]] chips_float& i, [[maybe_unused]] chips_float& integral, [[maybe_unused]] chips_int& knob_value, [[maybe_unused]] chips_int& max_knob_value, [[maybe_unused]] chips_int& min_knob_value, [[maybe_unused]] chips_float& p, [[maybe_unused]] chips_any& knob_out)
{
    derivative = chips_float{0.};
    integral = chips_float{0.};
    error = chips_float{0.};
    dt = chips_float{0.};
    p = -chips_float{1.};
    i = -chips_float{0.01};
    d = chips_float{0.};
    knob_value = chips_int{20};
    min_knob_value = chips_int{20};
    max_knob_value = chips_int{100};
}

void PidController_then([[maybe_unused]] chips_float& requested_time, [[maybe_unused]] chips_float& resulting_time, [[maybe_unused]] chips_bool& enabled, [[maybe_unused]] chips_float& d, [[maybe_unused]] chips_float& derivative, [[maybe_unused]] chips_float& dt, [[maybe_unused]] chips_float& error, [[maybe_unused]] chips_float& i, [[maybe_unused]] chips_float& integral, [[maybe_unused]] chips_int& knob_value, [[maybe_unused]] chips_int& max_knob_value, [[maybe_unused]] chips_int& min_knob_value, [[maybe_unused]] chips_float& p, [[maybe_unused]] chips_any& knob_out)
{
    if (enabled)
    {
        dt = resulting_time;
        error = requested_time - resulting_time;
        integral = integral + error * dt;
        derivative = error / dt;
        knob_value = static_cast<chips_int>((p * error + i * integral + d * derivative));
        knob_value = imin(max_knob_value, knob_value);
        knob_value = imax(min_knob_value, knob_value);
    }
    knob_out = knob_value;
}

void numberOfRespondedRequests([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrSum_t _accumulator, [[maybe_unused]] AggrSum_t next_acc, [[maybe_unused]] AggrSum_t prev_acc, [[maybe_unused]] chips_bool input, [[maybe_unused]] chips_any numberOfRespondedRequests_target)
{
    _accumulator.sum = _accumulator.sum + prev_acc.sum + next_acc.sum;
    if (input)
    {
        _accumulator.sum = _accumulator.sum + chips_int{1};
    }
    next_acc.sum = _accumulator.sum;
    prev_acc.sum = _accumulator.sum;
    numberOfRespondedRequests_target = _accumulator.sum;
}

void broadcastRedirection([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrRedirection_t _accumulator, [[maybe_unused]] AggrRedirection_t next_acc, [[maybe_unused]] AggrRedirection_t prev_acc, [[maybe_unused]] chips_any broadcastRedirection_target)
{
    next_acc.redirection = _accumulator.redirection;
    prev_acc.redirection = _accumulator.redirection;
    broadcastRedirection_target = _accumulator.redirection;
}

void broadcastDataQty([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrDataQtyToFind_t _accumulator, [[maybe_unused]] AggrDataQtyToFind_t next_acc, [[maybe_unused]] AggrDataQtyToFind_t prev_acc, [[maybe_unused]] chips_any broadcastDataQty_target)
{
    next_acc.dataQtyToFind = _accumulator.dataQtyToFind;
    prev_acc.dataQtyToFind = _accumulator.dataQtyToFind;
    broadcastDataQty_target = _accumulator.dataQtyToFind;
}

void findRightDataProvider([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrUserIDNbJumps_t _accumulator, [[maybe_unused]] AggrUserIDNbJumps_t next_acc, [[maybe_unused]] AggrUserIDNbJumps_t prev_acc, [[maybe_unused]] chips_any findRightDataProvider_target)
{
    chips_int currentBackendTransmittedID;
    chips_int nextBackendData;
    if (_accumulator.nbJumps == _accumulator.userID % chips_int{4})
    {
        currentBackendTransmittedID = _accumulator.userID;
        nextBackendData.stopFlag = true;
    }
    else
    {
        _accumulator.nbJumps = _accumulator.nbJumps + chips_int{1};
        currentBackendTransmittedID = chips_int{0};
        nextBackendData = _accumulator.userID;
    }
    next_acc.userID = nextBackendData;
    next_acc.nbJumps = _accumulator.nbJumps;
    prev_acc.userID.stopFlag = true;
    prev_acc.nbJumps.stopFlag = true;
    findRightDataProvider_target = currentBackendTransmittedID;
}

