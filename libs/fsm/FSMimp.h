#ifndef _INTERPRETERIMP_HEADER_
#define _INTERPRETERIMP_HEADER_
#include "common/xmlHelper.h"
#include "common/CEventBuffer.h"
#include <string>
#include <map>
#include <queue>
#include <log4cplus/logger.h>
#include "scxml/TriggerEvent.h"
#include "scxml/SendInterface.h"
#include "scxml/model/Transition.h"


using namespace std;


namespace fsm{

	//template class INTERPRETER_EXPORT std::map<std::string, Send *>;
	class Context;
	class  StateMachineimp {
		friend class StateMachine;
		friend class MyTimer;
	protected:
		StateMachineimp(const std::string &sessionid, const string &xml, int xtype);
		virtual ~StateMachineimp();

		StateMachineimp(const StateMachineimp &other) = delete;
		StateMachineimp & operator=(const StateMachineimp & other) = delete;

		//开始进入初始化状态
		void go();
		//停止运行
		void termination();
		//const xmlNodePtr getCurrentState(void) const;
		const std::string getCurrentStateID(void) const;

		//void setName(const string &strName);
		const std::string& getName() const;

		void setSessionID(const std::string &strSessionid);
		const std::string& getSessionId()const;

		bool setVar(const std::string &name, const Json::Value &value);
		Json::Value getVar(const std::string &name) const;

		bool addSendImplement( SendInterface * evtDsp);
		void setLog(log4cplus::Logger log);

		void pushEvent(const TriggerEvent & Evt);
		void mainEventLoop();
	private:
		std::string m_strStateFile;
		std::string m_strStateContent;
		uint32_t m_xmlType = 0;
		helper::xml::CXmlDocumentPtr m_xmlDocPtr = nullptr;
		helper::xml::CXPathContextPtr xpathCtx = nullptr;
		//xmlHelper::xmlDocumentPtr _docPtr2;
		xmlNodePtr  m_initState = nullptr;
		xmlNodePtr m_currentStateNode = nullptr;
		xmlNodePtr m_rootNode = nullptr;
		Context *  m_Context = nullptr;
		std::string m_strSessionID;
		std::string m_strName;

	private:
		TriggerEvent m_currentEvt;

		std::atomic_bool m_Running = false;
		std::queue<TriggerEvent> m_internalQueue;
		helper::CEventBuffer<TriggerEvent> m_externalQueue;
		std::map<std::string, Json::Value> m_globalVars;
		std::map<std::string, SendInterface *> m_mapSendObject;
		log4cplus::Logger  log;
	private:
		//加载状态机
		bool Init(void);
		void normalize(const xmlNodePtr &rootNode);
		//将文件解析成xml文档。
		bool parse();

		static bool isState(const xmlNodePtr &xmlNode) ;
		static bool isTransition(const xmlNodePtr &Node) ;
		static bool isLog(const xmlNodePtr &Node) ;
		static bool isEvent(const xmlNodePtr &Node) ;
		static bool isEntry(const xmlNodePtr &Node) ;
		static bool isExit(const xmlNodePtr &Node) ;
		static bool isSend(const xmlNodePtr &Node) ;
		static bool isScript(const xmlNodePtr &Node) ;
		static bool isTimer(const xmlNodePtr &Node) ;
		static bool isRaise(const xmlNodePtr &Node) ;
		static bool isSleep(const xmlNodePtr &Node);

		bool processEvent(const TriggerEvent &event);

		bool processEvent( const xmlNodePtr &eventNode) const;
		bool processTransition(const xmlNodePtr &node) const;
		bool processExit(const xmlNodePtr &node) const;

		//处理entry节点函数，传入entry节点指针，返回值表示是否继续执行余下的entry节点。
		bool processEntry(const xmlNodePtr &node)const;
		bool processSend(const xmlNodePtr &node)const;
		bool processScript(const xmlNodePtr &node)const;
		bool processTimer(const xmlNodePtr &node)const;
		bool processLog(const xmlNodePtr &node) const;
		bool processRaise(const xmlNodePtr &node)const;
		bool processSleep(const xmlNodePtr &node)const;

		void enterStates(const xmlNodePtr &stateNode) const;
		void exitStates() const;

		Context * getRootContext() const; 
		xmlNodePtr getState(const string& stateId) const;
		const ::xmlNodePtr getParentState(const xmlNodePtr &currentState)const;

	public:
		/****************************************************  
		@describle   应用XML Schema模板文件验证案例文档 
		@param schema_filename  模式文件  
		@param xml           XML格式的案例文档 
		@param xmlType		案例文档是磁盘文件还是内存字符串。
		@ErrorMsg		返回的错误内容
		@retval  ==0  验证成功 
				>0  验证失败  
		****************************************************/  
		static int is_valid(const std::string &schema_filename, const std::string & xml, int xtype, std::string &ErrorMsg);
		static void XMLCALL myXmlStructuredErrorFunc (void *userData, xmlErrorPtr error)
		{
			fprintf(stderr,"%s file'%s',line:%d\n",error->message,error->file,error->line);
			return;
		}
	};
}
#endif