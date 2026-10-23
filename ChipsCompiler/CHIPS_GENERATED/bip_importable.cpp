#include "bip_importable.hpp"

//--------------------------------------------------------------------------------
//Definitions generated from chips sources
//--------------------------------------------------------------------------------

void init_UserMachine([[maybe_unused]] chips_int& endTime_in, [[maybe_unused]] chips_int& httpResponse_in, [[maybe_unused]] chips_int& id_in, [[maybe_unused]] chips_int& maxNbData_in, [[maybe_unused]] chips_int& startTime_in, [[maybe_unused]] chips_int& computerID_ctx, [[maybe_unused]] chips_bool& active_inner, [[maybe_unused]] chips_int& currentRequest_inner, [[maybe_unused]] chips_int& httpRequest_inner, [[maybe_unused]] chips_int& lastRequest_inner, [[maybe_unused]] chips_bool& newPage_inner, [[maybe_unused]] chips_bool& requiresAuth_inner, [[maybe_unused]] chips_int& time_inner, [[maybe_unused]] chips_bool& waiting_inner, [[maybe_unused]] chips_int& fromUserToInternet_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:9:5: bool active = false;");
    active_inner = chips_bool{false};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:10:5: bool waiting = false;");
    waiting_inner = chips_bool{false};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:11:5: int time = 0;");
    time_inner = chips_int{0};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:12:5: bool requiresAuth = false;");
    requiresAuth_inner = chips_bool{false};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:13:5: bool newPage = false;");
    newPage_inner = chips_bool{false};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:16:5: int currentRequest = 0;");
    currentRequest_inner = chips_int{0};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:19:5: int httpRequest = 0;");
    httpRequest_inner = chips_int{0};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:20:5: int lastRequest = 0;");
    lastRequest_inner = chips_int{0};
}

void then_UserMachine([[maybe_unused]] chips_int& endTime_in, [[maybe_unused]] chips_int& httpResponse_in, [[maybe_unused]] chips_int& id_in, [[maybe_unused]] chips_int& maxNbData_in, [[maybe_unused]] chips_int& startTime_in, [[maybe_unused]] chips_int& computerID_ctx, [[maybe_unused]] chips_bool& active_inner, [[maybe_unused]] chips_int& currentRequest_inner, [[maybe_unused]] chips_int& httpRequest_inner, [[maybe_unused]] chips_int& lastRequest_inner, [[maybe_unused]] chips_bool& newPage_inner, [[maybe_unused]] chips_bool& requiresAuth_inner, [[maybe_unused]] chips_int& time_inner, [[maybe_unused]] chips_bool& waiting_inner, [[maybe_unused]] chips_int& fromUserToInternet_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:23:5: ctx.computerID = id;");
    computerID_ctx = id_in;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:24:5: newPage = (httpResponse !=0) && is_fresh(httpResponse);");
    newPage_inner = (httpResponse_in != chips_int{0}) && is_fresh(httpResponse_in);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:25:5: requiresAuth = (httpResponse < 0) || requiresAuth;");
    requiresAuth_inner = (httpResponse_in < chips_int{0}) || requiresAuth_inner;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:26:5: active = (time>=startTime) && (time<endTime);");
    active_inner = (time_inner >= startTime_in) && (time_inner < endTime_in);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:27:5: if (!active)");
    if (!active_inner)
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:28:9: httpRequest = 0;");
        httpRequest_inner = chips_int{0};
    }
    else
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:31:9: if (!waiting)");
        if (!waiting_inner)
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:32:13: currentRequest = (int) (randin01()*((float)(maxNbData-1)))+1;");
            currentRequest_inner = static_cast<chips_int>((randin01() * (static_cast<chips_float>((maxNbData_in - chips_int{1}))))) + chips_int{1};
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:33:13: httpRequest = (maxNbData)*(ctx.computerID-1) + currentRequest;");
            httpRequest_inner = (maxNbData_in) * (computerID_ctx - chips_int{1}) + currentRequest_inner;
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:34:13: if (requiresAuth)");
            if (requiresAuth_inner)
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:35:17: httpRequest = -httpRequest;");
                httpRequest_inner = -httpRequest_inner;
            }
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:37:13: lastRequest = httpRequest;");
            lastRequest_inner = httpRequest_inner;
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:38:13: waiting = true;");
            waiting_inner = chips_bool{true};
        }
        else
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:40:13: if (newPage)");
            if (newPage_inner)
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:41:17: if (requiresAuth)");
                if (requiresAuth_inner)
                {
                    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:42:21: currentRequest = (int)(randin01()*((float)(maxNbData-1)))+1;");
                    currentRequest_inner = static_cast<chips_int>((randin01() * (static_cast<chips_float>((maxNbData_in - chips_int{1}))))) + chips_int{1};
                    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:43:21: httpRequest = -(maxNbData*(ctx.computerID-1) + currentRequest);");
                    httpRequest_inner = -(maxNbData_in * (computerID_ctx - chips_int{1}) + currentRequest_inner);
                    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:44:21: waiting = true;");
                    waiting_inner = chips_bool{true};
                }
                else
                {
                    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:46:21: waiting = false;");
                    waiting_inner = chips_bool{false};
                    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:47:21: httpRequest = 0;");
                    httpRequest_inner = chips_int{0};
                }
            }
            else
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:50:17: waiting = true;");
                waiting_inner = chips_bool{true};
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:51:17: httpRequest = 0;");
                httpRequest_inner = chips_int{0};
            }
        }
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:55:5: time = time+1;");
    time_inner = time_inner + chips_int{1};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:56:3: -> actuator fromUserToInternet(httpRequest)");
    chips_reset(fromUserToInternet_out, httpRequest_inner);
}

void init_ServerMachine([[maybe_unused]] chips_int& fromInternet_in, [[maybe_unused]] chips_int& maxNbData_in, [[maybe_unused]] chips_int& wpServed_in, [[maybe_unused]] chips_int& currentRequest_inner, [[maybe_unused]] chips_int& httpResponse_inner, [[maybe_unused]] chips_int& nbDataToOutput_inner, [[maybe_unused]] chips_bool& requestFound_inner, [[maybe_unused]] chips_int& requestList_inner, [[maybe_unused]] chips_bool& userAuthToOutput_inner, [[maybe_unused]] chips_int& userIDToOutput_inner, [[maybe_unused]] chips_int& fromServerToInternet_out, [[maybe_unused]] chips_int& nbData_out, [[maybe_unused]] chips_bool& userAuth_out, [[maybe_unused]] chips_int& userID_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:65:5: int httpResponse = 0;");
    httpResponse_inner = chips_int{0};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:66:5: int currentRequest = 0;");
    currentRequest_inner = chips_int{0};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:67:5: bool requestFound = false;");
    requestFound_inner = chips_bool{false};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:69:5: int [100] requestList = zeros(100);");
    chips_reset(requestList_inner, chips_make_shaped<int>(0, {chips_int{100}}));
    requestList_inner = zeros(chips_int{100});
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:71:5: int nbDataToOutput;");
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:72:5: int userIDToOutput;");
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:73:5: bool userAuthToOutput;");
}

void then_ServerMachine([[maybe_unused]] chips_int& fromInternet_in, [[maybe_unused]] chips_int& maxNbData_in, [[maybe_unused]] chips_int& wpServed_in, [[maybe_unused]] chips_int& currentRequest_inner, [[maybe_unused]] chips_int& httpResponse_inner, [[maybe_unused]] chips_int& nbDataToOutput_inner, [[maybe_unused]] chips_bool& requestFound_inner, [[maybe_unused]] chips_int& requestList_inner, [[maybe_unused]] chips_bool& userAuthToOutput_inner, [[maybe_unused]] chips_int& userIDToOutput_inner, [[maybe_unused]] chips_int& fromServerToInternet_out, [[maybe_unused]] chips_int& nbData_out, [[maybe_unused]] chips_bool& userAuth_out, [[maybe_unused]] chips_int& userID_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:77:5: requestList[currentRequest] = 0;");
    requestList_inner[currentRequest_inner] = chips_int{0};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:79:5: for i in range(100)");
    {
        auto i0 = range(chips_int{100});
        for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:80:9: if (fromInternet[i]!=0)");
            if (fromInternet_in[i].to_chips() != chips_int{0})
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:81:13: requestList[i] = fromInternet[i];");
                requestList_inner[i] = fromInternet_in[i].to_chips();
            }
        }
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:85:5: for reqShift in range(100)");
    {
        auto i0 = range(chips_int{100});
        for(chips_int reqShift{0}; reqShift < i0.size(); reqShift = reqShift+chips_int{1}) {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:86:9: if (!requestFound && (requestList[(currentRequest + reqShift)%100] != 0))");
            if (!requestFound_inner && (requestList_inner[(currentRequest_inner + reqShift) % chips_int{100}].to_chips() != chips_int{0}))
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:87:13: requestFound = true;");
                requestFound_inner = chips_bool{true};
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:88:13: currentRequest = (currentRequest + reqShift)%100;");
                currentRequest_inner = (currentRequest_inner + reqShift) % chips_int{100};
            }
        }
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:93:5: httpResponse = wpServed;");
    httpResponse_inner = wpServed_in;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:96:5: if (requestFound)");
    if (requestFound_inner)
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:97:9: userAuthToOutput = requestList[currentRequest]<0;");
        userAuthToOutput_inner = requestList_inner[currentRequest_inner].to_chips() < chips_int{0};
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:98:9: if (userAuthToOutput)");
        if (userAuthToOutput_inner)
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:99:13: nbDataToOutput = (-requestList[currentRequest])%(maxNbData);");
            nbDataToOutput_inner = (-requestList_inner[currentRequest_inner].to_chips()) % (maxNbData_in);
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:100:13: userIDToOutput = (-requestList[currentRequest])/(maxNbData)+1;");
            userIDToOutput_inner = (-requestList_inner[currentRequest_inner].to_chips()) / (maxNbData_in) + chips_int{1};
        }
        else
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:102:13: nbDataToOutput = requestList[currentRequest]%(maxNbData);");
            nbDataToOutput_inner = requestList_inner[currentRequest_inner].to_chips() % (maxNbData_in);
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:103:13: userIDToOutput = requestList[currentRequest]/(maxNbData)+1;");
            userIDToOutput_inner = requestList_inner[currentRequest_inner].to_chips() / (maxNbData_in) + chips_int{1};
        }
    }
    else
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:106:9: nbDataToOutput = 0;");
        nbDataToOutput_inner = chips_int{0};
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:107:9: userIDToOutput = 0;");
        userIDToOutput_inner = chips_int{0};
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:108:9: userAuthToOutput = false;");
        userAuthToOutput_inner = chips_bool{false};
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:111:1: -> actuator fromServerToInternet(httpResponse)");
    chips_reset(fromServerToInternet_out, httpResponse_inner);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:112:1: -> nbData(nbDataToOutput)");
    chips_reset(nbData_out, nbDataToOutput_inner);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:113:1: -> userID(userIDToOutput)");
    chips_reset(userID_out, userIDToOutput_inner);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:114:1: -> userAuth(userAuthToOutput)");
    chips_reset(userAuth_out, userAuthToOutput_inner);
}

void init_UserActionInterpreter([[maybe_unused]] chips_bool& authDataRcvd_in, [[maybe_unused]] chips_int& nbDataRcvd_in, [[maybe_unused]] chips_int& userIDRcvd_in, [[maybe_unused]] chips_bool& authProvided_out, [[maybe_unused]] chips_int& nbData_out, [[maybe_unused]] chips_int& reqID_out)
{
    chips_diag::function_scope chips_function_scope_guard;
}

void then_UserActionInterpreter([[maybe_unused]] chips_bool& authDataRcvd_in, [[maybe_unused]] chips_int& nbDataRcvd_in, [[maybe_unused]] chips_int& userIDRcvd_in, [[maybe_unused]] chips_bool& authProvided_out, [[maybe_unused]] chips_int& nbData_out, [[maybe_unused]] chips_int& reqID_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:118:17: -> nbData(nbDataRcvd)");
    chips_reset(nbData_out, nbDataRcvd_in);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:119:1: -> reqID(userIDRcvd)");
    chips_reset(reqID_out, userIDRcvd_in);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:120:1: -> authProvided(authDataRcvd)");
    chips_reset(authProvided_out, authDataRcvd_in);
}

void init_Authenticator([[maybe_unused]] chips_bool& authProvided_in, [[maybe_unused]] chips_bool& isAuthenticated_out)
{
    chips_diag::function_scope chips_function_scope_guard;
}

void then_Authenticator([[maybe_unused]] chips_bool& authProvided_in, [[maybe_unused]] chips_bool& isAuthenticated_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:124:17: -> isAuthenticated(authProvided)");
    chips_reset(isAuthenticated_out, authProvided_in);
}

void init_RequestValidator([[maybe_unused]] chips_bool& isAuthenticated_in, [[maybe_unused]] chips_int& nbData_in, [[maybe_unused]] chips_int& requestID_in, [[maybe_unused]] chips_int& nbDataToFetch_inner, [[maybe_unused]] chips_bool& needRedirection_inner, [[maybe_unused]] chips_int& nbDataRequested_out, [[maybe_unused]] chips_bool& redirection_out, [[maybe_unused]] chips_int& userID_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:129:5: int nbDataToFetch;");
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:130:5: bool needRedirection;");
}

void then_RequestValidator([[maybe_unused]] chips_bool& isAuthenticated_in, [[maybe_unused]] chips_int& nbData_in, [[maybe_unused]] chips_int& requestID_in, [[maybe_unused]] chips_int& nbDataToFetch_inner, [[maybe_unused]] chips_bool& needRedirection_inner, [[maybe_unused]] chips_int& nbDataRequested_out, [[maybe_unused]] chips_bool& redirection_out, [[maybe_unused]] chips_int& userID_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:132:5: needRedirection = (nbData > 5) && (!isAuthenticated);");
    needRedirection_inner = (nbData_in > chips_int{5}) && (!isAuthenticated_in);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:133:5: if (!needRedirection)");
    if (!needRedirection_inner)
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:134:9: nbDataToFetch = nbData;");
        nbDataToFetch_inner = nbData_in;
    }
    else
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:136:9: nbDataToFetch = 0;");
        nbDataToFetch_inner = chips_int{0};
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:138:3: -> nbDataRequested(nbDataToFetch)");
    chips_reset(nbDataRequested_out, nbDataToFetch_inner);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:139:1: -> userID(requestID)");
    chips_reset(userID_out, requestID_in);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:140:1: -> redirection(needRedirection)");
    chips_reset(redirection_out, needRedirection_inner);
}

void init_RequestLimiter([[maybe_unused]] chips_int& maxRequests_in, [[maybe_unused]] chips_int& nbAnsweredReqs_in, [[maybe_unused]] chips_int& nbDataToFetch_in, [[maybe_unused]] chips_bool& redirection_in, [[maybe_unused]] chips_int& userID_in, [[maybe_unused]] chips_int& currentNbRequests_inner, [[maybe_unused]] chips_int& dataQty_out, [[maybe_unused]] chips_bool& redirection_out, [[maybe_unused]] chips_int& userID_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:145:5: int currentNbRequests = 0;");
    currentNbRequests_inner = chips_int{0};
}

void then_RequestLimiter([[maybe_unused]] chips_int& maxRequests_in, [[maybe_unused]] chips_int& nbAnsweredReqs_in, [[maybe_unused]] chips_int& nbDataToFetch_in, [[maybe_unused]] chips_bool& redirection_in, [[maybe_unused]] chips_int& userID_in, [[maybe_unused]] chips_int& currentNbRequests_inner, [[maybe_unused]] chips_int& dataQty_out, [[maybe_unused]] chips_bool& redirection_out, [[maybe_unused]] chips_int& userID_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:147:5: currentNbRequests = currentNbRequests - nbAnsweredReqs;");
    currentNbRequests_inner = currentNbRequests_inner - nbAnsweredReqs_in;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:148:5: if (!redirection)");
    if (!redirection_in)
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:149:9: if ((currentNbRequests + 1) <= maxRequests)");
        if ((currentNbRequests_inner + chips_int{1}) <= maxRequests_in)
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:150:13: currentNbRequests = currentNbRequests + 1;");
            currentNbRequests_inner = currentNbRequests_inner + chips_int{1};
        }
        else
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:152:13: redirection = true;");
            redirection_in = chips_bool{true};
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:153:13: nbDataToFetch = 0;");
            nbDataToFetch_in = chips_int{0};
        }
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:156:3: -> redirection(redirection)");
    chips_reset(redirection_out, redirection_in);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:157:1: -> userID(userID)");
    chips_reset(userID_out, userID_in);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:158:1: -> dataQty(nbDataToFetch)");
    chips_reset(dataQty_out, nbDataToFetch_in);
}

void init_Cache([[maybe_unused]] chips_int& cacheSize_in, [[maybe_unused]] chips_int& requestedData_in, [[maybe_unused]] chips_int& cache_inner, [[maybe_unused]] chips_bool& found_inner, [[maybe_unused]] chips_int& foundIndex_inner, [[maybe_unused]] chips_int& maxCacheSize_inner, [[maybe_unused]] chips_int& minCacheSize_inner, [[maybe_unused]] chips_int& newestDataIndex_inner, [[maybe_unused]] chips_bool& foundInCache_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:161:5: int maxCacheSize = 100;");
    maxCacheSize_inner = chips_int{100};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:162:5: int minCacheSize = 10;");
    minCacheSize_inner = chips_int{10};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:163:5: int [maxCacheSize] cache = zeros(maxCacheSize);");
    chips_reset(cache_inner, chips_make_shaped<int>(0, {maxCacheSize_inner}));
    cache_inner = zeros(maxCacheSize_inner);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:164:5: int newestDataIndex=0;");
    newestDataIndex_inner = chips_int{0};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:165:5: bool found = false;");
    found_inner = chips_bool{false};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:166:5: int foundIndex = 0;");
    foundIndex_inner = chips_int{0};
}

void then_Cache([[maybe_unused]] chips_int& cacheSize_in, [[maybe_unused]] chips_int& requestedData_in, [[maybe_unused]] chips_int& cache_inner, [[maybe_unused]] chips_bool& found_inner, [[maybe_unused]] chips_int& foundIndex_inner, [[maybe_unused]] chips_int& maxCacheSize_inner, [[maybe_unused]] chips_int& minCacheSize_inner, [[maybe_unused]] chips_int& newestDataIndex_inner, [[maybe_unused]] chips_bool& foundInCache_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:168:5: if (cacheSize > maxCacheSize)");
    if (cacheSize_in > maxCacheSize_inner)
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:169:9: cacheSize = maxCacheSize;");
        cacheSize_in = maxCacheSize_inner;
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:171:5: if (cacheSize < minCacheSize)");
    if (cacheSize_in < minCacheSize_inner)
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:172:9: cacheSize = minCacheSize;");
        cacheSize_in = minCacheSize_inner;
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:174:5: if (newestDataIndex >= cacheSize)");
    if (newestDataIndex_inner >= cacheSize_in)
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:175:9: newestDataIndex = 0;");
        newestDataIndex_inner = chips_int{0};
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:178:5: found = false;");
    found_inner = chips_bool{false};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:179:5: if (requestedData > 0)");
    if (requestedData_in > chips_int{0})
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:180:9: for i in range(cacheSize)");
        {
            auto i0 = range(cacheSize_in);
            for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:181:13: if ((!found) && (cache[i] == requestedData))");
                if ((!found_inner) && (cache_inner[i].to_chips() == requestedData_in))
                {
                    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:182:17: found = true;");
                    found_inner = chips_bool{true};
                    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:183:17: foundIndex = i;");
                    foundIndex_inner = i;
                }
            }
        }
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:187:9: if (!found)");
        if (!found_inner)
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:188:13: newestDataIndex = (newestDataIndex + 1) % cacheSize;");
            newestDataIndex_inner = (newestDataIndex_inner + chips_int{1}) % cacheSize_in;
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:189:13: cache [newestDataIndex] = requestedData;");
            cache_inner[newestDataIndex_inner] = requestedData_in;
        }
        else
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:191:13: if (foundIndex < newestDataIndex)");
            if (foundIndex_inner < newestDataIndex_inner)
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:192:17: int temp;");
                chips_int temp = chips_make_shaped<int>(0, {});
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:193:17: for i in range(newestDataIndex-foundIndex)");
                {
                    auto i0 = range(newestDataIndex_inner - foundIndex_inner);
                    for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
                        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:194:21: temp = cache[foundIndex+i+1];");
                        temp = cache_inner[foundIndex_inner + i + chips_int{1}].to_chips();
                        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:195:21: cache[foundIndex+i+1] = cache[foundIndex+i];");
                        cache_inner[foundIndex_inner + i + chips_int{1}] = cache_inner[foundIndex_inner + i].to_chips();
                        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:196:21: cache[foundIndex+i] = temp;");
                        cache_inner[foundIndex_inner + i] = temp;
                    }
                }
            }
            else
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:199:17: int temp;");
                chips_int temp = chips_make_shaped<int>(0, {});
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:200:17: for i in range( cacheSize-foundIndex + newestDataIndex)");
                {
                    auto i0 = range(cacheSize_in - foundIndex_inner + newestDataIndex_inner);
                    for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
                        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:201:21: temp = cache[(foundIndex+i+1)%cacheSize];");
                        temp = cache_inner[(foundIndex_inner + i + chips_int{1}) % cacheSize_in].to_chips();
                        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:202:21: cache[(foundIndex+i+1)%cacheSize] = cache[(foundIndex+i)%cacheSize];");
                        cache_inner[(foundIndex_inner + i + chips_int{1}) % cacheSize_in] = cache_inner[(foundIndex_inner + i) % cacheSize_in].to_chips();
                        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:203:21: cache[(foundIndex+i)%cacheSize] = temp;");
                        cache_inner[(foundIndex_inner + i) % cacheSize_in] = temp;
                    }
                }
            }
        }
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:209:1: -> foundInCache(found)");
    chips_reset(foundInCache_out, found_inner);
}

void init_DataProvider([[maybe_unused]] chips_bool& cacheResponse_in, [[maybe_unused]] chips_int& dataQty_in, [[maybe_unused]] chips_bool& redirection_in, [[maybe_unused]] chips_int& userID_in, [[maybe_unused]] chips_bool& cacheSearching_inner, [[maybe_unused]] chips_int& currentlyTreatedUserRequest_inner, [[maybe_unused]] chips_int& dataPerUserID_inner, [[maybe_unused]] chips_int& dataToFetch_inner, [[maybe_unused]] chips_int& httpResponse_inner, [[maybe_unused]] chips_int& maxDifferentData_inner, [[maybe_unused]] chips_int& maxUserID_inner, [[maybe_unused]] chips_bool& oneLessPendingRequest_inner, [[maybe_unused]] chips_float& time_inner, [[maybe_unused]] chips_int& cacheRequest_out, [[maybe_unused]] chips_bool& enableTimeReading_out, [[maybe_unused]] chips_bool& oneLessPendingRequest_out, [[maybe_unused]] chips_float& timeSpentOnReq_out, [[maybe_unused]] chips_int& userID_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:214:5: int maxDifferentData = 40;");
    maxDifferentData_inner = chips_int{40};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:215:5: int maxUserID = 100;");
    maxUserID_inner = chips_int{100};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:216:5: int [maxUserID] dataPerUserID = zeros(maxUserID);");
    chips_reset(dataPerUserID_inner, chips_make_shaped<int>(0, {maxUserID_inner}));
    dataPerUserID_inner = zeros(maxUserID_inner);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:217:5: int currentlyTreatedUserRequest = -1;");
    currentlyTreatedUserRequest_inner = -chips_int{1};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:222:5: int httpResponse = 0;");
    httpResponse_inner = chips_int{0};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:223:5: int dataToFetch = 0;");
    dataToFetch_inner = chips_int{0};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:225:5: float time = 0.0;");
    time_inner = chips_float{0.0};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:226:5: bool cacheSearching = false;");
    cacheSearching_inner = chips_bool{false};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:227:5: bool oneLessPendingRequest = false;");
    oneLessPendingRequest_inner = chips_bool{false};
}

void then_DataProvider([[maybe_unused]] chips_bool& cacheResponse_in, [[maybe_unused]] chips_int& dataQty_in, [[maybe_unused]] chips_bool& redirection_in, [[maybe_unused]] chips_int& userID_in, [[maybe_unused]] chips_bool& cacheSearching_inner, [[maybe_unused]] chips_int& currentlyTreatedUserRequest_inner, [[maybe_unused]] chips_int& dataPerUserID_inner, [[maybe_unused]] chips_int& dataToFetch_inner, [[maybe_unused]] chips_int& httpResponse_inner, [[maybe_unused]] chips_int& maxDifferentData_inner, [[maybe_unused]] chips_int& maxUserID_inner, [[maybe_unused]] chips_bool& oneLessPendingRequest_inner, [[maybe_unused]] chips_float& time_inner, [[maybe_unused]] chips_int& cacheRequest_out, [[maybe_unused]] chips_bool& enableTimeReading_out, [[maybe_unused]] chips_bool& oneLessPendingRequest_out, [[maybe_unused]] chips_float& timeSpentOnReq_out, [[maybe_unused]] chips_int& userID_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:229:5: if (oneLessPendingRequest)");
    if (oneLessPendingRequest_inner)
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:230:9: time = 0.0;");
        time_inner = chips_float{0.0};
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:232:5: oneLessPendingRequest = false;");
    oneLessPendingRequest_inner = chips_bool{false};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:233:5: httpResponse = 0;");
    httpResponse_inner = chips_int{0};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:234:5: if ((userID != 0) && is_fresh(userID))");
    if ((userID_in != chips_int{0}) && is_fresh(userID_in))
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:235:9: if (redirection)");
        if (redirection_in)
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:236:13: httpResponse = -userID;");
            httpResponse_inner = -userID_in;
        }
        else
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:238:13: dataPerUserID[userID-1] = dataQty;");
            dataPerUserID_inner[userID_in - chips_int{1}] = dataQty_in;
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:239:13: if (currentlyTreatedUserRequest < 0)");
            if (currentlyTreatedUserRequest_inner < chips_int{0})
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:240:17: currentlyTreatedUserRequest = userID-1;");
                currentlyTreatedUserRequest_inner = userID_in - chips_int{1};
            }
        }
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:246:5: if ((currentlyTreatedUserRequest >=0) && (httpResponse==0))");
    if ((currentlyTreatedUserRequest_inner >= chips_int{0}) && (httpResponse_inner == chips_int{0}))
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:248:9: if (cacheSearching)");
        if (cacheSearching_inner)
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:249:13: if (cacheResponse)");
            if (cacheResponse_in)
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:252:17: time = time + 0.03;");
                time_inner = time_inner + chips_float{0.03};
            }
            else
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:256:17: time = time + 2.0;");
                time_inner = time_inner + chips_float{2.0};
            }
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:258:13: dataPerUserID[currentlyTreatedUserRequest] = dataPerUserID[currentlyTreatedUserRequest] -1;");
            dataPerUserID_inner[currentlyTreatedUserRequest_inner] = dataPerUserID_inner[currentlyTreatedUserRequest_inner].to_chips() - chips_int{1};
        }
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:261:9: if (dataPerUserID[currentlyTreatedUserRequest]>0)");
        if (dataPerUserID_inner[currentlyTreatedUserRequest_inner].to_chips() > chips_int{0})
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:262:13: dataToFetch = (int) (randin01()*((float)maxDifferentData))+1;");
            dataToFetch_inner = static_cast<chips_int>((randin01() * (static_cast<chips_float>(maxDifferentData_inner)))) + chips_int{1};
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:263:13: cacheSearching = true;");
            cacheSearching_inner = chips_bool{true};
        }
        else
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:266:13: httpResponse = currentlyTreatedUserRequest +1;");
            httpResponse_inner = currentlyTreatedUserRequest_inner + chips_int{1};
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:267:13: oneLessPendingRequest = true;");
            oneLessPendingRequest_inner = chips_bool{true};
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:269:13: bool foundNewRequestPending = false;");
            chips_bool foundNewRequestPending = chips_make_shaped<bool>(false, {});
            foundNewRequestPending = chips_bool{false};
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:270:13: for userReqShift in range(maxUserID)");
            {
                auto i0 = range(maxUserID_inner);
                for(chips_int userReqShift{0}; userReqShift < i0.size(); userReqShift = userReqShift+chips_int{1}) {
                    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:271:17: if ((!foundNewRequestPending) && (dataPerUserID[(currentlyTreatedUserRequest + userReqShift)%maxUserID] > 0))");
                    if ((!foundNewRequestPending) && (dataPerUserID_inner[(currentlyTreatedUserRequest_inner + userReqShift) % maxUserID_inner].to_chips() > chips_int{0}))
                    {
                        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:272:21: foundNewRequestPending = true;");
                        foundNewRequestPending = chips_bool{true};
                        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:273:21: currentlyTreatedUserRequest = (currentlyTreatedUserRequest + userReqShift)%maxUserID;");
                        currentlyTreatedUserRequest_inner = (currentlyTreatedUserRequest_inner + userReqShift) % maxUserID_inner;
                    }
                }
            }
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:276:13: if (!foundNewRequestPending)");
            if (!foundNewRequestPending)
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:277:17: cacheSearching = false;");
                cacheSearching_inner = chips_bool{false};
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:278:17: currentlyTreatedUserRequest = -1;");
                currentlyTreatedUserRequest_inner = -chips_int{1};
            }
            else
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:280:17: dataToFetch = (int) (randin01()*((float)maxDifferentData))+1;");
                dataToFetch_inner = static_cast<chips_int>((randin01() * (static_cast<chips_float>(maxDifferentData_inner)))) + chips_int{1};
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:281:17: cacheSearching = true;");
                cacheSearching_inner = chips_bool{true};
            }
        }
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:285:2: -> userID(httpResponse)");
    chips_reset(userID_out, httpResponse_inner);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:286:1: -> cacheRequest(dataToFetch)");
    chips_reset(cacheRequest_out, dataToFetch_inner);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:287:1: -> oneLessPendingRequest(oneLessPendingRequest)");
    chips_reset(oneLessPendingRequest_out, oneLessPendingRequest_inner);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:288:1: -> timeSpentOnReq(time)");
    chips_reset(timeSpentOnReq_out, time_inner);
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:289:1: -> enableTimeReading(oneLessPendingRequest)");
    chips_reset(enableTimeReading_out, oneLessPendingRequest_inner);
}

void allDataProvidersOutputs([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrAnswers_t _accumulator, [[maybe_unused]] AggrAnswers_t next_acc, [[maybe_unused]] AggrAnswers_t prev_acc, [[maybe_unused]] chips_int input, [[maybe_unused]] chips_any allDataProvidersOutputs_target)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:301:5: if (input!=0)");
    if (input != chips_int{0})
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:302:9: if (input>0)");
        if (input > chips_int{0})
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:303:13: answers[input-1] = input;");
            _accumulator.answers[input - chips_int{1}] = input;
        }
        else
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:305:13: answers[-input-1] = input;");
            _accumulator.answers[-input - chips_int{1}] = input;
        }
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:308:5: for i in range(100)");
    {
        auto i0 = range(100);
        for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:309:9: if (prev.answers[i]!=0)");
            if (prev_acc.answers[i].to_chips() != chips_int{0})
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:310:13: answers[i] = prev.answers[i];");
                _accumulator.answers[i] = prev_acc.answers[i].to_chips();
            }
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:312:9: if (next.answers[i]!=0)");
            if (next_acc.answers[i].to_chips() != chips_int{0})
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:313:13: answers[i] = next.answers[i];");
                _accumulator.answers[i] = next_acc.answers[i].to_chips();
            }
        }
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:317:1: -> default(answers)");
    next_acc.answers = _accumulator.answers;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:317:1: -> default(answers)");
    prev_acc.answers = _accumulator.answers;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:316:8: -> @(answers)");
    allDataProvidersOutputs_target = _accumulator.answers;
}

void init_WebPageService([[maybe_unused]] chips_int& respondToThisIDs_in, [[maybe_unused]] chips_int& currentRequestAnswered_inner, [[maybe_unused]] chips_bool& requestFound_inner, [[maybe_unused]] chips_int& requestsToAnswerTo_inner, [[maybe_unused]] chips_int& httpResponse_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:321:5: int currentRequestAnswered = 0;");
    currentRequestAnswered_inner = chips_int{0};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:322:5: int [100] requestsToAnswerTo = zeros(100);");
    chips_reset(requestsToAnswerTo_inner, chips_make_shaped<int>(0, {chips_int{100}}));
    requestsToAnswerTo_inner = zeros(chips_int{100});
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:323:5: bool requestFound = false;");
    requestFound_inner = chips_bool{false};
}

void then_WebPageService([[maybe_unused]] chips_int& respondToThisIDs_in, [[maybe_unused]] chips_int& currentRequestAnswered_inner, [[maybe_unused]] chips_bool& requestFound_inner, [[maybe_unused]] chips_int& requestsToAnswerTo_inner, [[maybe_unused]] chips_int& httpResponse_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:325:5: requestsToAnswerTo[currentRequestAnswered] = 0;");
    requestsToAnswerTo_inner[currentRequestAnswered_inner] = chips_int{0};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:326:5: requestFound = false;");
    requestFound_inner = chips_bool{false};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:327:5: for i in range(100)");
    {
        auto i0 = range(chips_int{100});
        for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:328:9: if (respondToThisIDs[i]!=0)");
            if (respondToThisIDs_in[i].to_chips() != chips_int{0})
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:329:13: requestsToAnswerTo[i] = respondToThisIDs[i];");
                requestsToAnswerTo_inner[i] = respondToThisIDs_in[i].to_chips();
            }
        }
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:333:5: for reqShift in range(100)");
    {
        auto i0 = range(chips_int{100});
        for(chips_int reqShift{0}; reqShift < i0.size(); reqShift = reqShift+chips_int{1}) {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:334:9: if (!requestFound && (requestsToAnswerTo[(currentRequestAnswered + reqShift)%100] != 0))");
            if (!requestFound_inner && (requestsToAnswerTo_inner[(currentRequestAnswered_inner + reqShift) % chips_int{100}].to_chips() != chips_int{0}))
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:335:13: currentRequestAnswered = (currentRequestAnswered + reqShift)%100;");
                currentRequestAnswered_inner = (currentRequestAnswered_inner + reqShift) % chips_int{100};
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:336:13: requestFound = true;");
                requestFound_inner = chips_bool{true};
            }
        }
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:340:1: -> httpResponse(requestsToAnswerTo[currentRequestAnswered])");
    chips_reset(httpResponse_out, requestsToAnswerTo_inner[currentRequestAnswered_inner].to_chips());
}

void responseToTheRightUser([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrFromInternet_t _accumulator, [[maybe_unused]] AggrFromInternet_t next_acc, [[maybe_unused]] AggrFromInternet_t prev_acc, [[maybe_unused]] const chips_int& ctx_computerID, [[maybe_unused]] chips_any responseToTheRightUser_target)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:352:5: int id = fromInternet;");
    chips_int id = chips_make_shaped<int>(0, {});
    id = _accumulator.fromInternet;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:353:5: if (fromInternet < 0)");
    if (_accumulator.fromInternet < chips_int{0})
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:354:9: id = -id;");
        id = -id;
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:356:5: int returned;");
    chips_int returned = chips_make_shaped<int>(0, {});
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:357:5: int transmitted;");
    chips_int transmitted = chips_make_shaped<int>(0, {});
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:358:5: if ((fromInternet==0) || (id != ctx.computerID))");
    if ((_accumulator.fromInternet == chips_int{0}) || (id != ctx_computerID))
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:359:9: returned = 0;");
        returned = chips_int{0};
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:360:9: transmitted = fromInternet;");
        transmitted = _accumulator.fromInternet;
    }
    else
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:362:9: returned = fromInternet;");
        returned = _accumulator.fromInternet;
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:363:9: transmitted = stop;");
        transmitted.stopFlag = true;
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:366:1: -> default(transmitted)");
    next_acc.fromInternet = transmitted;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:366:1: -> default(transmitted)");
    prev_acc.fromInternet = transmitted;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:365:8: -> @(returned)");
    responseToTheRightUser_target = returned;
}

void aggregatingRequests([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrRequests_t _accumulator, [[maybe_unused]] AggrRequests_t next_acc, [[maybe_unused]] AggrRequests_t prev_acc, [[maybe_unused]] chips_int input, [[maybe_unused]] chips_any aggregatingRequests_target)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:370:5: if (input!=0)");
    if (input != chips_int{0})
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:371:9: if (input<0)");
        if (input < chips_int{0})
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:372:13: requests[-input] = input;");
            _accumulator.requests[-input] = input;
        }
        else
        {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:374:13: requests[input] = input;");
            _accumulator.requests[input] = input;
        }
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:378:5: for i in range(100)");
    {
        auto i0 = range(100);
        for(chips_int i{0}; i < i0.size(); i = i+chips_int{1}) {
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:379:9: if (prev.requests[i]!=0)");
            if (prev_acc.requests[i].to_chips() != chips_int{0})
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:380:13: requests[i] = prev.requests[i];");
                _accumulator.requests[i] = prev_acc.requests[i].to_chips();
            }
            chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:382:9: if (next.requests[i]!=0)");
            if (next_acc.requests[i].to_chips() != chips_int{0})
            {
                chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:383:13: requests[i] = next.requests[i];");
                _accumulator.requests[i] = next_acc.requests[i].to_chips();
            }
        }
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:388:1: -> default(requests)");
    next_acc.requests = _accumulator.requests;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:388:1: -> default(requests)");
    prev_acc.requests = _accumulator.requests;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:387:6: -> @(requests)");
    aggregatingRequests_target = _accumulator.requests;
}

void init_PidController([[maybe_unused]] chips_bool& enabled_in, [[maybe_unused]] chips_float& requested_time_in, [[maybe_unused]] chips_float& resulting_time_in, [[maybe_unused]] chips_float& d_inner, [[maybe_unused]] chips_float& derivative_inner, [[maybe_unused]] chips_float& dt_inner, [[maybe_unused]] chips_float& error_inner, [[maybe_unused]] chips_float& i_inner, [[maybe_unused]] chips_float& integral_inner, [[maybe_unused]] chips_int& knob_value_inner, [[maybe_unused]] chips_int& max_knob_value_inner, [[maybe_unused]] chips_int& min_knob_value_inner, [[maybe_unused]] chips_float& p_inner, [[maybe_unused]] chips_int& knob_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:393:5: float derivative = 0.;");
    derivative_inner = chips_float{0.};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:394:5: float integral = 0.;");
    integral_inner = chips_float{0.};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:395:5: float error = 0.;");
    error_inner = chips_float{0.};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:396:5: float dt = 0.;");
    dt_inner = chips_float{0.};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:398:5: float p = -1.;");
    p_inner = -chips_float{1.};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:399:5: float i = -0.01;");
    i_inner = -chips_float{0.01};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:400:5: float d = 0.;");
    d_inner = chips_float{0.};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:402:5: int knob_value = 20;");
    knob_value_inner = chips_int{20};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:403:5: int min_knob_value = 20;");
    min_knob_value_inner = chips_int{20};
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:404:5: int max_knob_value = 100;");
    max_knob_value_inner = chips_int{100};
}

void then_PidController([[maybe_unused]] chips_bool& enabled_in, [[maybe_unused]] chips_float& requested_time_in, [[maybe_unused]] chips_float& resulting_time_in, [[maybe_unused]] chips_float& d_inner, [[maybe_unused]] chips_float& derivative_inner, [[maybe_unused]] chips_float& dt_inner, [[maybe_unused]] chips_float& error_inner, [[maybe_unused]] chips_float& i_inner, [[maybe_unused]] chips_float& integral_inner, [[maybe_unused]] chips_int& knob_value_inner, [[maybe_unused]] chips_int& max_knob_value_inner, [[maybe_unused]] chips_int& min_knob_value_inner, [[maybe_unused]] chips_float& p_inner, [[maybe_unused]] chips_int& knob_out)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:406:5: if (enabled)");
    if (enabled_in)
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:407:9: dt = resulting_time;");
        dt_inner = resulting_time_in;
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:408:9: error = requested_time - resulting_time;");
        error_inner = requested_time_in - resulting_time_in;
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:409:9: integral = integral + error * dt;");
        integral_inner = integral_inner + error_inner * dt_inner;
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:410:9: derivative = error / dt;");
        derivative_inner = error_inner / dt_inner;
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:411:9: knob_value = (int) (p*error + i*integral + d*derivative);");
        knob_value_inner = static_cast<chips_int>((p_inner * error_inner + i_inner * integral_inner + d_inner * derivative_inner));
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:413:9: knob_value = imin(max_knob_value, knob_value);");
        knob_value_inner = imin(max_knob_value_inner, knob_value_inner);
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:414:9: knob_value = imax(min_knob_value, knob_value);");
        knob_value_inner = imax(min_knob_value_inner, knob_value_inner);
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:416:3: -> knob(knob_value)");
    chips_reset(knob_out, knob_value_inner);
}

void numberOfRespondedRequests([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrSum_t _accumulator, [[maybe_unused]] AggrSum_t next_acc, [[maybe_unused]] AggrSum_t prev_acc, [[maybe_unused]] chips_bool input, [[maybe_unused]] chips_any numberOfRespondedRequests_target)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:422:5: sum = sum + prev.sum + next.sum;");
    _accumulator.sum = _accumulator.sum + prev_acc.sum + next_acc.sum;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:423:5: if (input)");
    if (input)
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:424:9: sum = sum+1;");
        _accumulator.sum = _accumulator.sum + chips_int{1};
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:427:1: -> default(sum)");
    next_acc.sum = _accumulator.sum;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:427:1: -> default(sum)");
    prev_acc.sum = _accumulator.sum;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:426:7: -> @(sum)");
    numberOfRespondedRequests_target = _accumulator.sum;
}

void broadcastRedirection([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrRedirection_t _accumulator, [[maybe_unused]] AggrRedirection_t next_acc, [[maybe_unused]] AggrRedirection_t prev_acc, [[maybe_unused]] chips_any broadcastRedirection_target)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:435:1: -> default(redirection)");
    next_acc.redirection = _accumulator.redirection;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:435:1: -> default(redirection)");
    prev_acc.redirection = _accumulator.redirection;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:434:5: -> @(redirection)");
    broadcastRedirection_target = _accumulator.redirection;
}

void broadcastDataQty([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrDataQtyToFind_t _accumulator, [[maybe_unused]] AggrDataQtyToFind_t next_acc, [[maybe_unused]] AggrDataQtyToFind_t prev_acc, [[maybe_unused]] chips_any broadcastDataQty_target)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:440:1: -> default(dataQtyToFind)");
    next_acc.dataQtyToFind = _accumulator.dataQtyToFind;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:440:1: -> default(dataQtyToFind)");
    prev_acc.dataQtyToFind = _accumulator.dataQtyToFind;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:439:6: -> @(dataQtyToFind)");
    broadcastDataQty_target = _accumulator.dataQtyToFind;
}

void findRightDataProvider([[maybe_unused]] chips_int channel_indicator, [[maybe_unused]] AggrUserIDNbJumps_t _accumulator, [[maybe_unused]] AggrUserIDNbJumps_t next_acc, [[maybe_unused]] AggrUserIDNbJumps_t prev_acc, [[maybe_unused]] chips_any findRightDataProvider_target)
{
    chips_diag::function_scope chips_function_scope_guard;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:448:5: int currentBackendTransmittedID;");
    chips_int currentBackendTransmittedID = chips_make_shaped<int>(0, {});
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:449:5: int nextBackendData;");
    chips_int nextBackendData = chips_make_shaped<int>(0, {});
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:450:5: if (nbJumps == userID%4)");
    if (_accumulator.nbJumps == _accumulator.userID % chips_int{4})
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:451:9: currentBackendTransmittedID = userID;");
        currentBackendTransmittedID = _accumulator.userID;
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:452:9: nextBackendData = stop;");
        nextBackendData.stopFlag = true;
    }
    else
    {
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:454:9: nbJumps = nbJumps+1;");
        _accumulator.nbJumps = _accumulator.nbJumps + chips_int{1};
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:455:9: currentBackendTransmittedID = 0;");
        currentBackendTransmittedID = chips_int{0};
        chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:456:9: nextBackendData = userID;");
        nextBackendData = _accumulator.userID;
    }
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:459:1: -> next(nextBackendData, nbJumps)");
    next_acc.userID = nextBackendData;
    next_acc.nbJumps = _accumulator.nbJumps;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:460:1: -> prev(stop)");
    prev_acc.userID.stopFlag = true;
    prev_acc.nbJumps.stopFlag = true;
    chips_diag::at("/home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/testfiles/TeaStoreVariation.chips:458:8: -> @(currentBackendTransmittedID)");
    findRightDataProvider_target = currentBackendTransmittedID;
}

chips_int int_init_ctx(const std::string &ctx_name)
{
    if (ctx_name == "UserMachine.computerID")
    {
        chips_int value = chips_make_shaped<int>(0, {});
        return value;
    }
    throw std::invalid_argument("int_init_ctx: unknown contextual variable '" + ctx_name + "'");
}

chips_float float_init_ctx(const std::string &ctx_name)
{
    throw std::invalid_argument("float_init_ctx: unknown contextual variable '" + ctx_name + "'");
}

chips_bool bool_init_ctx(const std::string &ctx_name)
{
    throw std::invalid_argument("bool_init_ctx: unknown contextual variable '" + ctx_name + "'");
}

