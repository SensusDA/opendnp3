/**
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */
#ifndef __I_APDU_HANDLER_H_
#define __I_APDU_HANDLER_H_

#include "LazyCollection.h"
#include <opendnp3/IndexedValue.h>

#include "objects/Group1.h"
#include "objects/Group2.h"

#include "objects/Group30.h"
#include "objects/Group32.h"


namespace opendnp3
{

class IAPDUHeaderHandler 
{
	public:

		virtual void Handle(const LazyCollection<IndexedValue<Group1Var2>>& meas) = 0;

		virtual void Handle(const LazyCollection<IndexedValue<Group2Var1>>& meas) = 0;
		virtual void Handle(const LazyCollection<IndexedValue<Group2Var2>>& meas) = 0;
		virtual void Handle(const LazyCollection<IndexedValue<Group2Var3>>& meas) = 0;

		virtual void Handle(const LazyCollection<IndexedValue<Group30Var1>>& meas) = 0;
		virtual void Handle(const LazyCollection<IndexedValue<Group30Var2>>& meas) = 0;
		virtual void Handle(const LazyCollection<IndexedValue<Group30Var3>>& meas) = 0;
		virtual void Handle(const LazyCollection<IndexedValue<Group30Var4>>& meas) = 0;
		virtual void Handle(const LazyCollection<IndexedValue<Group30Var5>>& meas) = 0;
		virtual void Handle(const LazyCollection<IndexedValue<Group30Var6>>& meas) = 0;			
};

}

#endif