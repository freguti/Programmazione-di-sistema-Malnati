#ifndef NETWORK
#define NETWORK
#include "SharedEditor.h"
#include "Message.h"
#include <vector>
#include <list>
#include <memory>

using namespace std;

class SharedEditor;

enum action
{
	eTypeNull = 0,
	eTypeWrite,
	eTypeDelete
};

class NetworkServer
{
public:
	NetworkServer();
	~NetworkServer();
protected:
	vector<SharedEditor*> vEditor;
	vector<Message> vMessage;
public:
	int Connect(SharedEditor* pClient);
	void Disconnect(SharedEditor* pClient);
	bool Check_code(int unique_code);
	void Send(const Message& M);
	void DispatchMessages();
};
#endif

