#include <iostream>


class Frac {
private:
	long num; long den;
public:
	Frac(const long& = 0, const long& = 1);
	long getNum() const;
	long getDen() const;
	void setNum(const long&);
	void setDen(const long&);
	int operator<(const Frac&) const;
};

Frac::Frac(const long& n, const long& d) {
	num = n; den = d;
	if (den == 0) { den = 1; }
	if (den < 0) { den *= -1; num *= -1; }
}

long Frac::getNum() const { return num; }
long Frac::getDen() const { return den; }

void Frac::setNum(const long& n) { num = n; }

void Frac::setDen(const long& d) {
	den = d;
	if (den == 0) { den = 1; }
	if (den < -1) { num *= -1; den *= -1; }
}

int Frac::operator<(const Frac& b) const {
	if (num * (b.den) < den * (b.num)) {
		return 1;
	}
	return 0;
}

class TNode {
public:
	Frac content;
	TNode* aLeft;
	TNode* aRight;
};

TNode* addTerm(TNode* oldR, const Frac& x) {
	if (oldR == nullptr) {
		TNode* nR;
		nR = new TNode;
		(*nR).aLeft = nullptr;
		(*nR).aRight = nullptr;
		(*nR).content = x;
		return nR;
	}
	if (x < ((*oldR).content)) {
		(*oldR).aLeft = addTerm((*oldR).aLeft, x);
	}
	if (((*oldR).content) < x) {
		(*oldR).aRight = addTerm((*oldR).aRight, x);
	}
	return oldR;
}

TNode* search(TNode* aR, const Frac& x) {
	if (aR == nullptr) {
		return nullptr;
	}
	if (x < ((*aR).content)) {
		return search((*aR).aLeft, x);
	}
	if ((aR->content) < x) {
		return search((*aR).aRight, x);
	}
	return aR;
}

TNode* findMinimum(TNode* aR) {
	if (aR == nullptr) {
		return nullptr;
	}
	if ((*aR).aLeft == nullptr) {
		return aR;
	}
	return findMinimum((*aR).aLeft);
}

TNode* deleteMinimum(TNode* aR) {
	if (aR == nullptr) {
		return nullptr;
	}
	if ((*aR).aLeft == nullptr) {
		TNode* nRoot;
		nRoot = (*aR).aRight;
		(*aR).aRight = nullptr;
		delete aR;
		return nRoot;
	}
	(*aR).aLeft = deleteMinimum((*aR).aLeft);
	return aR;
}

TNode* removeElement(TNode* aR, const Frac& x) {
	if (aR == nullptr) {
		return nullptr;
	}
	if (x < ((*aR).content)) {
		(*aR).aLeft = removeElement((*aR).aLeft, x);
		return aR;
	}
	if (((*aR).content) < x) {
		(*aR).aRight = removeElement((*aR).aRight, x);
		return aR;
	}

	// We found out that aR->content is equal to x
	// Check if the right sub-tree is empty
	if ((*aR).aRight == nullptr) {
		TNode* nR = (*aR).aLeft;
		(*aR).aLeft = nullptr;
		delete aR;
		return nR;
	}

	// If the right sub-tree is not empty, then pick the smallest
	// member of the right subtree.
	TNode* aMin = findMinimum((*aR).aRight);
	// Swap: aMin->content with aR->content
	Frac tempSwap = (*aMin).content;
	(*aMin).content = (*aR).content;
	(*aR).content = tempSwap;
	// Delete the minimum from the right subtree
	(*aR).aRight = deleteMinimum((*aR).aRight);
	return aR;
}

void printTree(TNode* root) {
	if (root != nullptr) {
		printTree((*root).aLeft);
		std::cout << "\t" << ((*root).content).getNum();
		std::cout << "/" << ((*root).content).getDen();
		printTree((*root).aRight);
	}
}
//create SetOfFractions class
class SetOfFractions {
private:
	TNode* root;
public:
	SetOfFractions();
	SetOfFractions(const SetOfFractions&);
	SetOfFractions(SetOfFractions&&);
	void operator=(const SetOfFractions&);
	void operator=(SetOfFractions&&);
	long isElement(const Frac&) const;
	long insertInS(const Frac&);
	void printAllFractions() const;
	~SetOfFractions();
};
//default constructor 
SetOfFractions::SetOfFractions() {
	root = nullptr;
}
//copy constructor
SetOfFractions::SetOfFractions(const SetOfFractions& cF) {
	TNode* tR = cF.root;
	root = tR;
}
//copy assignment operator
void SetOfFractions::operator=(const SetOfFractions& copySet) {
	if (root != nullptr) {
		delete[] root;
	}
	root = copySet.root;
}
//move constructor
SetOfFractions::SetOfFractions(SetOfFractions&& mF) {
	root = mF.root;
	delete[] mF.root;
}
//move assignment operator
void SetOfFractions::operator=(SetOfFractions&& mF) {
	root = mF.root;
	delete[] mF.root;
}
//if search doesn't return nullptr, el is in the tree
long SetOfFractions::isElement(const Frac& el) const {
	if (search(root, el) != nullptr) {
		return 1;
	}
	return 0;
}
//if search returns nullptr, we can
//add fr, and return 1 as confirmation of insertion
long SetOfFractions::insertInS(const Frac& fr) {
	if (search(root, fr) == nullptr) {
		root = addTerm(root, fr);
		return 1;
	}
	return 0;
}
//we use the printTree function to print
void SetOfFractions::printAllFractions() const {
	if (root != nullptr) {
		printTree(root);
	}
}
//destructor 
SetOfFractions::~SetOfFractions() {
	if (root != nullptr) {
		delete[] root;
	}
}
//use given main function to test implementation
int main() {
	long a, b, c;
	Frac tempFr;
	SetOfFractions setF;
	a = 1;
	while (a != 0) {
		std::cout << "Choose one of: 0 (exit), 1 (add), 2 (check for element), ";
		std::cout << "or 3 (print all)" << std::endl;
		std::cin >> a;
		if (a == 1) {
			std::cout << "Insertion.";
			std::cout << " What are numerator and denominator? ";
			std::cin >> b >> c;
			tempFr.setNum(b);
			tempFr.setDen(c);
			setF.insertInS(tempFr);
		}
		if (a == 2) {
			std::cout << "Checking for element.";
			std::cout << " What are numerator and denominator? ";
			std::cin >> b >> c;
			tempFr.setNum(b);
			tempFr.setDen(c);
			std::cout << setF.isElement(tempFr) << std::endl;
		}
		if (a == 3) {
			std::cout << "Printing all fractions." << std::endl;
			setF.printAllFractions();
			std::cout << std::endl;
		}
	}
	return 0;
}
