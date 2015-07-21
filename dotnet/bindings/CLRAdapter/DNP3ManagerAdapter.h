#ifndef __CLR_DNP3_MANAGER_ADAPTER_H_
#define __CLR_DNP3_MANAGER_ADAPTER_H_

using namespace System;
using namespace Automatak::DNP3::Interface;

namespace asiodnp3
{
	class DNP3Manager;
}

namespace Automatak
{
	namespace DNP3
	{
		namespace Adapter
		{
			/// <summary>
			/// Factory class used to get the root DNP3 object
			/// </summary>
			public ref class DNP3ManagerFactory
			{
			public:
				/// <summary>
				/// Create a new IDNP3Manager using the specified concurrency
				/// </summary>
				/// <param name="concurrency">how many threads are allocated to the thread pool</param>
				/// <returns>IDNP3Manager interface</returns>
				static IDNP3Manager^ CreateManager(System::Int32 concurrency);

				/// <summary>
				/// Create a new IDNP3Manager using the default concurrency
				/// </summary>
				/// <returns>IDNP3Manager interface</returns>
				static IDNP3Manager^ CreateManager();

			private:
				DNP3ManagerFactory() {}
			};


			ref class DNP3ManagerAdapter : public Automatak::DNP3::Interface::IDNP3Manager
			{
			public:
				DNP3ManagerAdapter(System::Int32 aConcurrency);
				~DNP3ManagerAdapter();

				virtual void Shutdown() sealed;

				virtual IChannel^ AddTCPClient(System::String^ id, System::UInt32 filters, System::TimeSpan minRetryDelay, System::TimeSpan maxRetryDelay, System::String^ address, System::UInt16 port)  sealed;
				virtual IChannel^ AddTCPClient(System::String^ id, System::UInt32 filters, System::TimeSpan minRetryDelay, System::TimeSpan maxRetryDelay, System::String^ local, System::String^ address, System::UInt16 port)  sealed;
				virtual IChannel^ AddTCPServer(System::String^ id, System::UInt32 filters, System::TimeSpan minRetryDelay, System::TimeSpan maxRetryDelay, System::String^ endpoint, System::UInt16 port) sealed;
				virtual IChannel^ AddSerial(System::String^ id, System::UInt32 filters, System::TimeSpan minRetryDelay, System::TimeSpan maxRetryDelay, Automatak::DNP3::Interface::SerialSettings^ settings)  sealed;

				virtual void AddLogHandler(ILogHandler^ logHandler);

			private:
				asiodnp3::DNP3Manager* pManager;
			};

		}
	}
}

#endif
