#ifndef SHARED
#define SHARED
#include <memory>
#include "NetworkServer.h"
#include "Symbol.h"
#include <vector>
#include "Message.h"

using namespace std;

class NetworkServer;
class Symbol;

class SharedEditor
{
public:
	SharedEditor(NetworkServer& server);
	~SharedEditor();
private:
	int _siteid;
	NetworkServer& _server;
	weak_ptr<SharedEditor> sThis;
	vector<Symbol> _symbols;
	int _counter;
public:
	int GetSiteid() { return _siteid; };
	vector<char> GetFractional(int index);
	float TranslateFractional(vector<char> index);
	void Process(const Message &M);
	void LocalInsert(int index, char value);
};
#endif

