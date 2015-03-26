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
#ifndef OPENDNP3_IDATABASE_H
#define OPENDNP3_IDATABASE_H

#include "opendnp3/app/MeasurementTypes.h"
#include "opendnp3/app/TimeAndInterval.h"

#include "opendnp3/gen/EventMode.h"

#include <openpal/executor/Function1.h>

namespace opendnp3
{

/**
@desc IDatabase is the interface used to load measurements into an outstation.

The outstation application is responsible for measuring or
calculating data and then pushing it into this interface when it is ready
to publish it. As with all ITransactable objects it should be used with the
exception-safe Transaction object.

\code
{
	Transaction t(pDatabase);
	pDatabase->Update(Analog(12), 3);
	pDatabase->Update(Binary(true), 1);
}
\endcode

*/

class IDatabase
{
public:

	virtual ~IDatabase() {}

	/**
	* Update a Binary measurement, must have transaction started
	* @param meas measurement to be processed
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Update(const Binary& meas, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Update a DoubleBitBinary measurement, must have transaction started
	* @param meas measurement to be processed
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Update(const DoubleBitBinary& meas, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Update an Analog measurement, must have transaction started
	* @param meas measurement to be processed
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Update(const Analog& meas, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Update a Counter measurement, must have transaction started
	* @param meas measurement to be processed
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Update(const Counter& meas, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Update a FrozenCounter measurement, must have transaction started
	* @param meas measurement to be processed
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Update(const FrozenCounter& meas, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Update a BinaryOutputStatus measurement, must have transaction started
	* @param meas measurement to be processed
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Update(const BinaryOutputStatus& meas, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Update a AnalogOutputStatus measurement, must have transaction started
	* @param meas measurement to be processed
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Update(const AnalogOutputStatus& meas, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Update a TimeAndInterval value, must have transaction started
	* @param meas measurement to be processed
	* @param index index of the measurement	
	* @return true if the value exists and it was updated
	*/
	virtual bool Update(const TimeAndInterval& meas, uint16_t index) = 0;

	/**
	* Modify a value using the current value, must have transaction started
	* @param modify Functor that takes a measurement and returns a new one based on the old value
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Modify(const openpal::Function1<const Binary&, Binary>& modify, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Modify a value using the current value, must have transaction started
	* @param modify Functor that takes a measurement and returns a new one based on the old value
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Modify(const openpal::Function1<const DoubleBitBinary&, DoubleBitBinary>& modify, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Modify a value using the current value, must have transaction started
	* @param modify Functor that takes a measurement and returns a new one based on the old value
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Modify(const openpal::Function1<const Analog&, Analog>& modify, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Modify a value using the current value, must have transaction started
	* @param modify Functor that takes a measurement and returns a new one based on the old value
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Modify(const openpal::Function1<const Counter&, Counter>& modify, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Modify a value using the current value, must have transaction started
	* @param modify Functor that takes a measurement and returns a new one based on the old value
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Modify(const openpal::Function1<const FrozenCounter&, FrozenCounter>& modify, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Modify a value using the current value, must have transaction started
	* @param modify Functor that takes a measurement and returns a new one based on the old value
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Modify(const openpal::Function1<const BinaryOutputStatus&, BinaryOutputStatus>& modify, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Modify a value using the current value, must have transaction started
	* @param modify Functor that takes a measurement and returns a new one based on the old value
	* @param index index of the measurement
	* @param mode Describes how event generation is handled for this method
	* @return true if the value exists and it was updated
	*/
	virtual bool Modify(const openpal::Function1<const AnalogOutputStatus&, AnalogOutputStatus>& modify, uint16_t index, EventMode mode = EventMode::Detect) = 0;

	/**
	* Modify a value using the current value, must have transaction started
	* @param modify Functor that takes a measurement and returns a new one based on the old value
	* @param index index of the measurement	
	* @return true if the value exists and it was updated
	*/
	virtual bool Modify(const openpal::Function1<const TimeAndInterval&, TimeAndInterval>& modify, uint16_t index) = 0;

};

}

#endif
