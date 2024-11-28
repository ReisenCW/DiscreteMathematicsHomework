#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <queue>

using std::cout;
using std::cin;
using std::endl;

#define _DEBUG_ 0

struct Code {
	std::string code;
	int frequency;
	Code(std::string code, int frequency) :code(code), frequency(frequency) {};
};

void InputVertexNumber(int& vertexNum) {
	while (1) {
		cout << "请输入节点个数:";
		cin >> vertexNum;
		if (cin.good() && vertexNum > 0)
			break;
		else
			cout << "输入错误，请重新输入" << endl;
	}
}

void InputFrequency(std::vector<int>& frequency, int vertexNum) {
	while (1) {
		cout << "请输入节点频率:";
		for (int i = 0; i < vertexNum; i++) {
			cin >> frequency[i];
		}
		bool flag = true;
		for (int i = 0; i < vertexNum; i++) {
			if (frequency[i] < 0) {
				flag = false;
				break;
			}
		}
		if (flag)
			break;
		else
			cout << "输入错误，请重新输入" << endl;
	}
}

void InitVertices(std::vector<int>& frequency, int& vertexNum) {
	InputVertexNumber(vertexNum);
	frequency.resize(vertexNum);
	InputFrequency(frequency, vertexNum);
}

class HaffmanTree;
class TreeNode {
	friend class HaffmanTree;
private:
	int frequency;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int frequency) :frequency(frequency), left(nullptr), right(nullptr) {};
};

class HaffmanTree {
private:
	TreeNode* root;
public:
	HaffmanTree() : root(nullptr) {}
	HaffmanTree(const std::vector<int>& frequency) : root(nullptr) {
		GenerateHaffmanTree(frequency);
	}
	~HaffmanTree();
	void GenerateHaffmanTree(const std::vector<int>& frequency);
	std::vector<Code> GenerateCodes();
#if _DEBUG_
	void PrintTree() const;
#endif
private:
	HaffmanTree(const HaffmanTree& other) = delete;
	HaffmanTree& operator=(const HaffmanTree& other) = delete;

	void GenerateCodesWithDFS(const TreeNode* const root, std::string& code, std::vector<Code>& codes);
};
#if _DEBUG_
void HaffmanTree::PrintTree() const {
	cout << "------------Print HaffmanTree-------------" << endl;
	if (root == nullptr)
		return;
	std::queue<TreeNode*> q;
	q.push(root);
	//广搜遍历
	while (!q.empty()) {
		TreeNode* currentNode = q.front();
		q.pop();
		if (currentNode->left != nullptr) {
			q.push(currentNode->left);
		}
		if (currentNode->right != nullptr) {
			q.push(currentNode->right);
		}
		cout << currentNode->frequency << " ";
	}
	cout << endl;
	cout << "------------Complete HaffmanTree-------------" << endl;
	cout << endl;
}
#endif
HaffmanTree::~HaffmanTree() {
	if (root == nullptr)
		return;
	std::queue<TreeNode*> q;
	q.push(root);
	//广搜遍历
	while (!q.empty()) {
		TreeNode* currentNode = q.front();
		q.pop();
		if (currentNode->left != nullptr) {
			q.push(currentNode->left);
		}
		if (currentNode->right != nullptr) {
			q.push(currentNode->right);
		}
		delete currentNode;
	}
}

void HaffmanTree::GenerateHaffmanTree(const std::vector<int>& frequency) {
	auto compare = [](TreeNode* left, TreeNode* right) {
		return left->frequency > right->frequency;
		};
	std::priority_queue<TreeNode*, std::vector<TreeNode*>, decltype(compare)> pq(compare);

	for (int freq : frequency) {
		pq.push(new TreeNode(freq));
	}

	while (pq.size() > 1) {
		TreeNode* left = pq.top();
		pq.pop();
		TreeNode* right = pq.top();
		pq.pop();
		TreeNode* sumNode = new TreeNode(left->frequency + right->frequency);
		sumNode->left = left;
		sumNode->right = right;
		pq.push(sumNode);
	}

	root = pq.top();
}

void HaffmanTree::GenerateCodesWithDFS(const TreeNode* const root, std::string& code, std::vector<Code>& codes) {
	if (root == nullptr)
		return;
	if (root->left == nullptr && root->right == nullptr) {
		codes.push_back(Code(code, root->frequency));
		return;
	}
	code.push_back('0');
	GenerateCodesWithDFS(root->left, code, codes);
	code.pop_back();
	code.push_back('1');
	GenerateCodesWithDFS(root->right, code, codes);
	code.pop_back();
}

std::vector<Code> HaffmanTree::GenerateCodes() {
	std::vector<Code> codes;
	std::string code;
	GenerateCodesWithDFS(root, code, codes);
	return codes;
}

int main() {
	int vertexNum = 0;
	std::vector<int> frequency;
	InitVertices(frequency, vertexNum);

	HaffmanTree haffmanTree;
	haffmanTree.GenerateHaffmanTree(frequency);
#if _DEBUG_
	haffmanTree.PrintTree();
#endif
	std::vector<Code> codes = haffmanTree.GenerateCodes();
	for (const auto& code : codes) {
		printf("%-5d %s\n", code.frequency, code.code.c_str());
	}
	return 0;
}

/*
test:
13
2 3 5 7 11 13 17 19 23 29 31 37 41
*/