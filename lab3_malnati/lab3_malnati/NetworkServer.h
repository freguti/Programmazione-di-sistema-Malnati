#ifndef NETWORK
#define NETWORK
#include "SharedEditor.h"
#include "Message.h"
#include <vector>
#include <list>
#include <memory>

using namespace std;

class SharedEditor;

class NetworkServer
{
public:
	NetworkServer();
	~NetworkServer();
protected:
	vector<shared_ptr<SharedEditor>> vEditor;
	vector<Message> vMessage;
public:
	int Connect(weak_ptr<SharedEditor> pClient);
	void Disconnect(weak_ptr<SharedEditor> pClient);
	bool Check_code(int unique_code);
	void Send(const Message& M);
	void DispatchMessages();
};
#endif

