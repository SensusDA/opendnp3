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

#include "OutstationSolicitedStates.h"

#include "opendnp3/LogLevels.h"
#include "opendnp3/outstation/OutstationContext.h"
#include "opendnp3/app/FunctionHelpers.h"


#include <openpal/logging/LogMacros.h>

namespace opendnp3
{

// --------------------- OutstationSolicitedStateBase ----------------------

OutstationSolicitedStateBase* OutstationSolicitedStateBase::OnConfirm(OutstationContext* pContext, const APDUHeader& header)
{
	FORMAT_LOG_BLOCK(pContext->logger, flags::WARN, "Unexpected solicted confirm with sequence: %u", header.control.SEQ);
	return this;
}

OutstationSolicitedStateBase* OutstationSolicitedStateBase::OnSendResult(OutstationContext* pContext, bool isSucccess)
{
	SIMPLE_LOG_BLOCK(pContext->logger, flags::WARN, "Unexpected send result callback");
	return this;
}

OutstationSolicitedStateBase* OutstationSolicitedStateBase::OnConfirmTimeout(OutstationContext* pContext)
{
	SIMPLE_LOG_BLOCK(pContext->logger, flags::WARN, "Unexpected confirm timeout");
	return this;
}

OutstationSolicitedStateBase* OutstationSolicitedStateBase::OnNewReadRequest(OutstationContext* pContext, const APDUHeader& header, const openpal::ReadBufferView& objects)
{
	pContext->deferredRequest.Set(DeferredRequest(header, false, false));
	return this;
}

OutstationSolicitedStateBase* OutstationSolicitedStateBase::OnNewNonReadRequest(OutstationContext* pContext, const APDUHeader& header, const openpal::ReadBufferView& objects, bool headersEqualToLast)
{
	pContext->deferredRequest.Set(DeferredRequest(header, false, headersEqualToLast));
	return this;
}

OutstationSolicitedStateBase* OutstationSolicitedStateBase::OnRepeatNonReadRequest(OutstationContext* pContext, const APDUHeader& header, const openpal::ReadBufferView& objects)
{
	pContext->deferredRequest.Set(DeferredRequest(header, true, false));
	return this;
}

// --------------------- OutstationStateIdle ----------------------


OutstationSolicitedStateIdle OutstationSolicitedStateIdle::instance;

OutstationSolicitedStateBase& OutstationSolicitedStateIdle::Inst()
{
	return instance;
}

OutstationSolicitedStateBase* OutstationSolicitedStateIdle::OnNewReadRequest(OutstationContext* pContext, const APDUHeader& header, const openpal::ReadBufferView& objects)
{
	if (!pContext->isTransmitting && pContext->pUnsolicitedState == &OutstationUnsolicitedStateIdle::Inst())
	{
		return pContext->RespondToReadRequest(header.control.SEQ, objects);
	}
	else
	{
		pContext->deferredRequest.Set(DeferredRequest(header, false, false));
		return this;
	}
}

OutstationSolicitedStateBase* OutstationSolicitedStateIdle::OnNewNonReadRequest(OutstationContext* pContext, const APDUHeader& header, const openpal::ReadBufferView& objects, bool lastHeadersEqual)
{
	if (pContext->isTransmitting)
	{
		pContext->deferredRequest.Set(DeferredRequest(header, false, lastHeadersEqual));
		return this;		
	}
	else
	{
		if (IsNoAckCode(header.function))
		{
			pContext->ProcessNoResponseFunction(header, objects);
			return this;
		}
		else
		{
			return pContext->RespondToNonReadRequest(header, objects, lastHeadersEqual);
		}		
	}
}

OutstationSolicitedStateBase* OutstationSolicitedStateIdle::OnRepeatNonReadRequest(OutstationContext* pContext, const APDUHeader& header, const openpal::ReadBufferView& objects)
{
	if (pContext->isTransmitting)
	{
		pContext->deferredRequest.Set(DeferredRequest(header, true, false));
		return this;		
	}
	else
	{
		if (IsNoAckCode(header.function))
		{
			return this;
		}
		else
		{
			if (header.function == FunctionCode::SELECT)
			{
				// repeat selects are allowed, but they do not reset the select timer
				pContext->operateExpectedFragCount = pContext->rxFragCount + 1;
			}

			pContext->BeginResponseTx(pContext->lastResponse);
			return this;
		}		
	}	
}

// --------------------- OutstationStateSolConfirmWait ----------------------

OutstationStateSolicitedConfirmWait OutstationStateSolicitedConfirmWait::instance;

OutstationSolicitedStateBase& OutstationStateSolicitedConfirmWait::Inst()
{
	return instance;
}

OutstationSolicitedStateBase* OutstationStateSolicitedConfirmWait::OnNewReadRequest(OutstationContext* pContext, const APDUHeader& header, const openpal::ReadBufferView& objects)
{	
	pContext->deferredRequest.Set(DeferredRequest(header, false, false));
	return Abort(pContext);
			
}

OutstationSolicitedStateBase* OutstationStateSolicitedConfirmWait::OnNewNonReadRequest(OutstationContext* pContext, const APDUHeader& header, const openpal::ReadBufferView& objects, bool headersEqual)
{
	pContext->deferredRequest.Set(DeferredRequest(header, false, headersEqual));
	return Abort(pContext);
}

OutstationSolicitedStateBase* OutstationStateSolicitedConfirmWait::Abort(OutstationContext* pContext)
{
	// abandon the confirmed response sequence
	pContext->CancelConfirmTimer();	
	return &OutstationSolicitedStateIdle::Inst();
}

OutstationSolicitedStateBase* OutstationStateSolicitedConfirmWait::OnConfirm(OutstationContext* pContext, const APDUHeader& header)
{	
	if (header.control.SEQ == pContext->expectedSolConfirmSeq)
	{
		pContext->CancelConfirmTimer();			
		pContext->eventBuffer.ClearWritten();

		if (pContext->rspContext.HasSelection())
		{						
			return pContext->ContinueMultiFragResponse(AppControlField::NextSeq(header.control.SEQ));			
		}
		else 
		{
			return &OutstationSolicitedStateIdle::Inst();
		}
	}
	else
	{
		FORMAT_LOG_BLOCK(pContext->logger, flags::WARN, "Confirm with wrong seq: %u", header.control.SEQ);
		return this;
	}			
}

OutstationSolicitedStateBase* OutstationStateSolicitedConfirmWait::OnConfirmTimeout(OutstationContext* pContext)
{	
	SIMPLE_LOG_BLOCK(pContext->logger, flags::WARN, "Solicited confirm timeout");
	pContext->pConfirmTimer = nullptr;	
	return &OutstationSolicitedStateIdle::Inst();	
}

}

