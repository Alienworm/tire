#include "tire.h"

int main(){
	trie t;
	int n, com;
	vector<string> ret;
	cout << "Please input the num of dictionary:" << endl;
	cin >> n;
	for(int i = 0; i < n; i++){
		string str;
		cin >> str;
		t.insertStr(str);
	}
	while(1){
		cout << "Please input command:" << endl;
		cin >> com;
		if(com == 1){ // 插入字串 
			cout << "Begin to insert, input the num:" << endl;
			cin >> n;
			for(int i = 0; i < n; i++){
				string str;
				cin >> str;
				t.insertStr(str);
			}
		}
		else if(com == 2){ // 查询字串 
			cout << "Start the query" << endl;
			string str;
			cin >> str;
			ret = t.getStr(str);
			vector<string>::iterator it;
			if(ret.empty()) // 当ret为空时 
				cout << "Query failed" << endl;
			else{ 
				for(it = ret.begin(); it != ret.end(); it++)
					cout << *it << endl;
				cout << "Query completed" << endl;
			} 
		}
		else if(com == 3){ // 删除字串 
			cout << "Start deleting" << endl;
			string str;
			cin >> str;	
			if(t.delectStr(str)) 
				cout << "Successfully deleted" << endl;
			else
				cout << "Failed to delect" << endl;
		}
	}
 	t.clear();
}
