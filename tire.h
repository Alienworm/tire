#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std; 

struct chtrie{ // 字典树的结构体 
	chtrie(){
		count = 0;
	}
	int count; // 记录改字串个数 
	map<string, chtrie *> next; // 键值记录的是当前汉字,实值记录的为后面汉字节点的指针 
};

class trie{ // 字典树的类 
	public:
		trie();	
		~trie();
		void insertStr(string str); // 插入字符串 
		bool delectStr(string str); // 删除字符串 
		void clear(); // 清空树 
		chtrie *searchStr(string str); // 查询整个str字符串 
		chtrie *searchStrPre(string str); // 查询包含str的字符串 
		vector<string> getStr(string str); // 用vector保存查询到所有包含str的字符串 
	private:
		void addStr(chtrie *root, string preStr, vector<string> &ret); // 递归的将含有str的字符串保存到ret中 
		chtrie *root; // 字典树的根节点 
};

trie::trie(){ // 创建trie类 
	root = new chtrie();
}

trie::~trie(){ // 销毁trie类 

}

void trie::insertStr(string str){ // 插入字符串 
	chtrie *p;
	if(root == NULL || str == "") // 输入和根节点的值不能为空 
		return;
	p = root;
	for(int i = 0; i < str.size(); i++){
		string nowStr = str.substr(i, 1); // 每次从str中提取一个字符 
		map<string, chtrie *>::iterator it = p->next.find(nowStr);  
		if(it == p->next.end()){ // 如果没有找到该字符则创建一个新节点 
			chtrie *tmp = new chtrie(); // 新节点 
			p->next.insert(pair<string, chtrie *> (nowStr, tmp)); // 将该字符和新节点加入到map中 
			p = tmp; // 更新p
		}
		else // 找到的话 
			p = it->second; // 更新p 
	}
	p->count++; // 改字符串最后一个节点count++ 
}

bool trie::delectStr(string str){ // 删除字符串 
	chtrie *p = searchStr(str); // 先查找是否存在改字符串 
	if(p != NULL){ // 存在 
		p->count--;	// 该字符串的count-- 
		return true;
	}
	return false;
}

void trie::clear(){ // 清空树 
	vector<chtrie *> clr; 
	clr.push_back(root); // 将根节点加入到clr中 
	while(!clr.empty()){ // 当clr不为空时 
		map<string, chtrie *>::iterator it;
		for(it = root->next.begin(); it != root->next.end(); it++)
			clr.push_back(it->second); // 将根节点的实值加入到clr中;  
		chtrie *del = clr.front(); // 取clr第一个元素 
		clr.pop_back(); // 删除clr第一个元素 
		delete del; // 删除该节点实值 
	}
}

chtrie *trie::searchStrPre(string str){ // 查询包含str的字符串
	chtrie *p;  
	if(str == "" || root == NULL) // 当输入为空或者根节点为空时返回root的值 
		return root;
	p = root;
	int i;
	for(i = 0; i < str.size(); i++){
		string nowStr = str.substr(i, 1);// 每次从str中提取一个字符 
		map<string, chtrie *>::iterator it = p->next.find(nowStr);
		if(it == p->next.end()) // 没有找到该字符返回NULL 
			return NULL;
		else
			p = it->second; // 更新p 
	}
	if(i == str.size()) 
		return p;
	return NULL;
}

chtrie *trie::searchStr(string str){ // 查询整个str字符串 
	chtrie *p = searchStrPre(str); // 先判断是否存在str前缀的字符串 
	if(p != NULL){ // 如果存在 
		if(p->count != 0) // 且改字符串count != 0 
			return p; // 返回p  
		return NULL;
	} 
	return NULL;
}

void trie::addStr(chtrie *root, string preStr, vector<string> &ret){// 递归的将含有str的字符串保存到ret中 
	map<string, chtrie *>::iterator it;
	for(it = root->next.begin(); it != root->next.end(); it++)
		addStr(it->second, preStr + it->first, ret); // 每次加一个字符 
	if(root->count != 0) // 改字符串count != 0 
		ret.push_back(preStr); // 加入到ret中 
}

vector<string> trie::getStr(string str){ // 用vector保存查询到所有包含str的字符串 
	vector<string> ret;
	chtrie *p = searchStrPre(str); // 先判断是否存在str前缀的字符串 
	if(p != NULL) // 如果存在 
		addStr(p, str, ret); // 加入到ret中 
	return ret; // 返回ret集合 
}
