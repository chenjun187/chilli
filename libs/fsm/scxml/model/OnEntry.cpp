#include "OnEntry.h"

namespace fsm{
namespace model{
	void OnEntry::execute(fsm::Context * ctx)
	{
		if (m_node == NULL) return;

		/*for (xmlNodePtr exeNode = _node->children ; exeNode !=  NULL; exeNode = exeNode->next)
		{
			if(exeNode->type == XML_ELEMENT_NODE &&
				xmlStrEqual(exeNode->name, BAD_CAST("script"))){
					model::Script spt(exeNode);
					spt.execute(evl,ctx);
			}else if(exeNode->type == XML_ELEMENT_NODE &&
				xmlStrEqual(exeNode->name, BAD_CAST("log"))){
					model::Log log(exeNode);
					log.execute(evl,ctx);
			}
			else if(exeNode->type == XML_ELEMENT_NODE &&
				xmlStrEqual(exeNode->name, BAD_CAST("transition"))){
					model::Transition tst(exeNode);
					tst.execute(evl,ctx);
					break;
			}
		}*/
	}

	bool OnEntry::isEnabledCondition(fsm::Context * ctx)
	{
		return true;
	}
}
}