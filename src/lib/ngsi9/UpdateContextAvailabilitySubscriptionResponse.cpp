/*
*
* Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* fermin at tid dot es
*
* Author: Ken Zangelin
*/
#include <string>
#include <vector>

#include "logMsg/traceLevels.h"
#include "logMsg/logMsg.h"
#include "common/Format.h"
#include "common/globals.h"
#include "common/tag.h"
#include "ngsi/ErrorCode.h"
#include "ngsi9/UpdateContextAvailabilitySubscriptionResponse.h"



/* ****************************************************************************
*
* UpdateContextAvailabilitySubscriptionResponse::UpdateContextAvailabilitySubscriptionResponse - 
*/
UpdateContextAvailabilitySubscriptionResponse::UpdateContextAvailabilitySubscriptionResponse()
{
}

/* ****************************************************************************
*
* UpdateContextAvailabilitySubscriptionResponse::UpdateContextAvailabilitySubscriptionResponse - 
*/
UpdateContextAvailabilitySubscriptionResponse::UpdateContextAvailabilitySubscriptionResponse(ErrorCode& _errorCode)
{
   errorCode = _errorCode;
}

/* ****************************************************************************
*
* UpdateContextAvailabilitySubscriptionResponse::~UpdateContextAvailabilitySubscriptionResponse -
*/
UpdateContextAvailabilitySubscriptionResponse::~UpdateContextAvailabilitySubscriptionResponse()
{
   subscriptionId.release();
   duration.release();
   errorCode.release();

   LM_T(LmtDestructor,("destroyed"));
}



/* ****************************************************************************
*
* UpdateContextAvailabilitySubscriptionResponse::render - 
*/
std::string UpdateContextAvailabilitySubscriptionResponse::render(RequestType requestType, Format format, std::string indent, int counter)
{
  std::string  out                = "";
  std::string  tag                = "updateContextAvailabilitySubscriptionResponse";
  bool         durationRendered   = !duration.isEmpty();
  bool         errorCodeRendered  = (errorCode.code != NO_ERROR_CODE);

  out += startTag(indent, tag, format, false);

  out += subscriptionId.render(format, indent + "  ", durationRendered || errorCodeRendered);
  out += duration.render(format, indent + "  ", errorCodeRendered);

  if (errorCodeRendered)
     out += errorCode.render(format, indent + "  ", false);

  out += endTag(indent, tag, format);

  return out;
}

/* ****************************************************************************
*
* UpdateContextAvailabilitySubscriptionResponse::check - 
*/
std::string UpdateContextAvailabilitySubscriptionResponse::check(RequestType requestType, Format format, std::string indent, std::string predetectedError, int counter)
{
  std::string  res;

  if (predetectedError != "")
  {
    errorCode.code         = SccBadRequest;
    errorCode.reasonPhrase = predetectedError;
  }
  else if (((res = subscriptionId.check(UpdateContextAvailabilitySubscription, format, indent, predetectedError, counter)) != "OK") ||
           ((res = duration.check(UpdateContextAvailabilitySubscription, format, indent, predetectedError, counter))       != "OK"))
  {
    errorCode.code         = SccBadRequest;
    errorCode.reasonPhrase = res;
  }
  else
    return "OK";

  return render(UpdateContextAvailabilitySubscription, format, indent, counter);
}