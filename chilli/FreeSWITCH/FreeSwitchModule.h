#pragma once
#include <log4cplus/logger.h>
#include "../model/ProcessModule.h"
#include <esl.h>
#include <thread>

namespace chilli{
namespace FreeSwitch{

	class FreeSwitchModule :public model::ProcessModule
	{
	public:
		explicit FreeSwitchModule(const std::string & id);
		virtual ~FreeSwitchModule(void);
		virtual int Start() override;
		virtual int Stop() override;
		virtual bool LoadConfig(const std::string & config) override;
	protected:
		//inherit from SendInterface
		virtual void fireSend(const std::string &strContent, const void * param) override;
		void processSend(Json::Value &jsonData, const void * param, bool & bHandled, log4cplus::Logger & log);
		bool MakeCall(Json::Value & param, log4cplus::Logger & log);
		bool MakeConnection(Json::Value & param, log4cplus::Logger & log);
		bool ClearConnection(Json::Value & param, log4cplus::Logger & log);
		bool StartRecord(Json::Value & param, log4cplus::Logger & log);
		bool Divert(Json::Value &param, log4cplus::Logger & log);
		bool PlayFile(Json::Value & param, log4cplus::Logger & log);
	private:
		std::thread m_Thread;
		std::string m_Host;
		int m_Port = 0;
		std::string m_User;
		std::string m_Password;
		esl_handle_t m_Handle = { { 0 } };
		void ConnectFS();
		std::map<std::string, std::string>m_Session_DeviceId;
		std::map<std::string, std::string>m_device_StateMachine;
		virtual void run() override;
		friend class FreeSwitchDevice;
	};

}
}
