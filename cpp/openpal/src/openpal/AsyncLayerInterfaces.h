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
#ifndef __ASYNC_LAYER_INTERFACES_H_
#define __ASYNC_LAYER_INTERFACES_H_

#include "openpal/BufferWrapper.h"

namespace openpal
{

class IUpDown
{

public:	
	
	virtual ~IUpDown() {}

	// Called by a lower Layer when it is available to this layer
	virtual void OnLowerLayerUp() = 0;

	// Called by a lower layer when it is no longer available to this layer
	virtual void OnLowerLayerDown() = 0;	
};


class ILowerLayer;

class IUpperLayer : public IUpDown
{

public:

	IUpperLayer() : pLowerLayer(nullptr) {}
	
	virtual ~IUpperLayer() {}

	// Called by the lower layer when data arrives

	virtual void OnReceive(const ReadOnlyBuffer&) = 0;

	// Called by lower layer when a previously requested send operation succeeds or fails.
	// Layers can only have 1 outstanding send operation. The callback is guaranteed
	// unless the the OnLowerLayerDown() function is called beforehand
	virtual void OnSendResult(bool isSucccess) = 0;	

	// Used to set the pointer to the lower layer
	void SetLowerLayer(ILowerLayer*);

protected:

	ILowerLayer* pLowerLayer;	
};

class ILowerLayer
{

public:

	ILowerLayer() : pUpperLayer(nullptr) {}
	
	virtual ~ILowerLayer() {}

	virtual void Send(const ReadOnlyBuffer&) = 0;

	void SetUpperLayer(IUpperLayer*);

protected:

	IUpperLayer* pUpperLayer;	
};

}

#endif