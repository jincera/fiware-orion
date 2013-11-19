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
#include <stdio.h>
#include <string>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "common/tag.h"
#include "ngsi/ContextElementVector.h"



/* ****************************************************************************
*
* ContextElementVector::push_back - 
*/
void ContextElementVector::push_back(ContextElement* item)
{
  vec.push_back(item);
}



/* ****************************************************************************
*
* ContextElementVector::render - 
*/
std::string ContextElementVector::render(Format format, std::string indent)
{
  std::string  out = "";
  std::string  tag = "contextElementList";

  if (vec.size() == 0)
    return "";

  out += startTag(indent, tag, format);

  for (unsigned int ix = 0; ix < vec.size(); ++ix)
    out += vec[ix]->render(format, indent + "  ");

  out += endTag(indent, tag, format);

  return out;
}



/* ****************************************************************************
*
* ContextElementVector::present - 
*/
void ContextElementVector::present(std::string indent)
{
   PRINTF("%lu ContextElements", (unsigned long) vec.size());

   for (unsigned int ix = 0; ix < vec.size(); ++ix)
      vec[ix]->present(indent, ix);
}



/* ****************************************************************************
*
* ContextElementVector::release - 
*/
void ContextElementVector::release(void)
{
  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
    vec[ix]->release();
    delete vec[ix];
  }

  vec.clear();
}



/* ****************************************************************************
*
* ContextElementVector::get - 
*/
ContextElement* ContextElementVector::get(int ix)
{
  return vec[ix];
}



/* ****************************************************************************
*
* ContextElementVector::size - 
*/
unsigned int ContextElementVector::size(void)
{
  return vec.size();
}



/* ****************************************************************************
*
* ContextElementVector::check - 
*/
std::string ContextElementVector::check(RequestType requestType, Format format, std::string indent, std::string predetectedError, int counter)
{
  if (requestType == UpdateContext)
  {
    if (vec.size() == 0)
      return "No context elements";
  }

  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
    std::string res;

    if ((res = vec[ix]->check(requestType, format, indent, predetectedError, counter)) != "OK")
      return res;
  }

  return "OK";
}