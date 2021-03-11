#include <iostream>
#include <utility>
#include <string>

template<typename InfoType>
struct Node {
    Node *prev = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    InfoType Info;
};
template<typename InfoType>
struct AVL_tree {
    Node<InfoType> *First;
};

template<typename InfoType>
void constructor(AVL_tree<InfoType> &Tree) {
    Tree.First = nullptr;
}

template<typename InfoType>
void destructor(AVL_tree<InfoType> &Tree) {
    Node<InfoType> *Element = Tree.First;
    bool IsRight;
    while ((Element->right != nullptr) && (Element->left != nullptr) && (Element->prev != nullptr)) {
        if (Element->right != nullptr) {
            Element = Element->right;
            IsRight = true;
        } else if (Element->left != nullptr) {
            Element = Element->left;
            IsRight = false;
        } else {
            Node<InfoType> *TempElement = Element->prev;
            if (IsRight) TempElement->right = nullptr;
            else TempElement->left = nullptr;
            delete Element;
            Element = TempElement;
        }
    }
    delete Element;
    Tree.First = nullptr;
}

template<typename InfoType>
void push(AVL_tree<InfoType> &Tree, InfoType Value) {
    if (Tree.First == nullptr) {
        Tree.First = new Node<InfoType>;
        Tree.First->Info = Value;
    } else {
        Node<InfoType> *Element = Tree.First;
        Node<InfoType> *TempElement;
        while (true) {
            if (Value > Element->Info) {
                TempElement = Element->right;
                if (TempElement == nullptr) {
                    Node<InfoType> *NewNode = new Node<InfoType>;
                    NewNode->prev = Element;
                    Element->right = NewNode;
                    NewNode->Info = Value;
                    while (Element != nullptr) {
                        check(Element, Tree);
                        Element = Element->prev;
                    }
                    check(Tree.First, Tree);
                    break;
                } else {
                    Element = TempElement;
                    continue;
                }
            } else {
                TempElement = Element->left;
                if (TempElement == nullptr) {
                    Node<InfoType> *NewNode = new Node<InfoType>;
                    NewNode->prev = Element;
                    Element->left = NewNode;
                    NewNode->Info = Value;
                    while (Element != nullptr) {
                        check(Element, Tree);
                        Element = Element->prev;
                    }
                    check(Tree.First, Tree);
                    break;
                } else {
                    Element = TempElement;
                    continue;
                }
            }
        }
    }
}


template<typename InfoType>
void extract(AVL_tree<InfoType> &Tree, InfoType Value) {
    Node<InfoType> *Element = Tree.First;
    Node<InfoType> *TempElement;
    bool IsRight;
    while (true) {
        if (Value > Element->Info) {
            IsRight = true;
            Element = Element->right;
        } else if (Value < Element->Info) {
            Element = Element->left;
            IsRight = false;
        } else {
            if ((Element->left == nullptr) && (Element->right == nullptr)) {
                if (Element == Tree.First) {
                    delete Element;
                    Tree.First = nullptr;
                    break;
                } else {
                    if (IsRight) {
                        Element->prev->right = nullptr;
                        TempElement = Element->prev;
                        delete Element;
                        while (TempElement != nullptr) {
                            check(TempElement, Tree);
                            TempElement = TempElement->prev;
                        }
                        check(Tree.First, Tree);
                        break;
                    } else {
                        Element->prev->left = nullptr;
                        TempElement = Element->prev;
                        delete Element;
                        while (TempElement != nullptr) {
                            check(TempElement, Tree);
                            TempElement = TempElement->prev;
                        }
                        check(Tree.First, Tree);
                        break;
                    }
                }
                break;
            } else if (Element->left == nullptr) {
                if (Element == Tree.First) {
                    Tree.First = Element->right;
                    Tree.First->prev = nullptr;
                    TempElement = Element->prev;
                    delete Element;
                    while (TempElement != nullptr) {
                        check(TempElement, Tree);
                        TempElement = TempElement->prev;
                    }
                    check(Tree.First, Tree);
                    break;
                } else {
                    if (IsRight) {
                        Element->prev->right = Element->right;
                        Element->right->prev = Element->prev;
                        TempElement = Element->prev;
                        delete Element;
                        while (TempElement != nullptr) {
                            check(TempElement, Tree);
                            TempElement = TempElement->prev;
                        }
                        check(Tree.First, Tree);
                        break;
                    } else {
                        Element->prev->left = Element->right;
                        Element->right->prev = Element->prev;
                        TempElement = Element->prev;
                        delete Element;
                        while (TempElement != nullptr) {
                            check(TempElement, Tree);
                            TempElement = TempElement->prev;
                        }
                        check(Tree.First, Tree);
                        break;
                    }

                }
            } else if (Element->right == nullptr) {
                if (Element == Tree.First) {
                    Tree.First = Element->left;
                    Tree.First->prev = nullptr;
                    TempElement = Element->prev;
                    delete Element;
                    while (TempElement != nullptr) {
                        check(TempElement, Tree);
                        TempElement = TempElement->prev;
                    }
                    check(Tree.First, Tree);
                    break;
                } else {
                    if (IsRight) {
                        Element->prev->right = Element->left;
                        Element->left->prev = Element->prev;
                        TempElement = Element->prev;
                        delete Element;
                        while (TempElement != nullptr) {
                            check(TempElement, Tree);
                            TempElement = TempElement->prev;
                        }
                        check(Tree.First, Tree);
                        break;
                    } else {
                        Element->prev->left = Element->left;
                        Element->left->prev = Element->prev;
                        TempElement = Element->prev;
                        delete Element;
                        while (TempElement != nullptr) {
                            check(TempElement, Tree);
                            TempElement = TempElement->prev;
                        }
                        check(Tree.First, Tree);
                        break;
                    }
                }
            } else {
                Node<InfoType> *NearestElement = Element->left;
                bool IsChildren = true;
                while (NearestElement->right != nullptr) {
                    NearestElement = NearestElement->right;
                    IsChildren = false;
                }
                if (Element == Tree.First) {
                    if (!IsChildren) {
                        Tree.First = NearestElement;
                        Tree.First->right = Element->right;
                        Tree.First->right->prev = Tree.First;
                        if (NearestElement->left != nullptr) {
                            NearestElement->prev->right = NearestElement->left;
                            NearestElement->left->prev = NearestElement->prev;
                        } else NearestElement->prev->right = nullptr;
                        Tree.First->left = Element->left;
                        Element->left->prev = Tree.First;
                        TempElement = NearestElement->prev;
                        NearestElement->prev = nullptr;
                        delete Element;
                        while (TempElement != nullptr) {
                            check(TempElement, Tree);
                            TempElement = TempElement->prev;
                        }
                        check(Tree.First, Tree);
                        break;
                    } else {
                        Tree.First = NearestElement;
                        Tree.First->right = Element->right;
                        Tree.First->right->prev = Tree.First;
                        Tree.First->prev = nullptr;
                        TempElement = Element->prev;
                        delete Element;
                        while (TempElement != nullptr) {
                            check(TempElement, Tree);
                            TempElement = TempElement->prev;
                        }
                        check(Tree.First, Tree);
                        break;
                    }
                } else {
                    /*Node<InfoType> *NearestElement = Element->left;
                    bool IsChildren = true;
                    while (NearestElement->right != nullptr) {
                        NearestElement = NearestElement->right;
                        IsChildren = false;
                    }*/
                    if (IsChildren) {
                        NearestElement->right = Element->right;
                        NearestElement->right->prev = NearestElement;
                        TempElement = NearestElement;
                        NearestElement->prev = Element->prev;
                        if (IsRight)
                            NearestElement->prev->right = NearestElement;
                        else NearestElement->prev->left = NearestElement;
                        delete Element;
                        while (TempElement != nullptr) {
                            check(TempElement, Tree);
                            TempElement = TempElement->prev;
                        }
                        check(Tree.First, Tree);
                        break;
                    } else {
                        NearestElement->right = Element->right;
                        NearestElement->right->prev = NearestElement;
                        TempElement = NearestElement->prev;
                        if (NearestElement->left != nullptr) {
                            NearestElement->prev->right = NearestElement->left;
                            NearestElement->left->prev = NearestElement->prev;
                        } else NearestElement->prev->right = nullptr;
                        NearestElement->left = Element->left;
                        NearestElement->left->prev = NearestElement;
                        NearestElement->prev = Element->prev;
                        if (IsRight)
                            NearestElement->prev->right = NearestElement;

                        else NearestElement->prev->left = NearestElement;
                        delete Element;
                        while (TempElement != nullptr) {
                            check(TempElement, Tree);
                            TempElement = TempElement->prev;
                        }
                        check(Tree.First, Tree);
                        break;
                    }
                }
            }
        }
    }
}

template<typename InfoType>
int height(Node<InfoType> *branch) {
    if (branch == nullptr)
        return 0;
    else {
        int left = height(branch->left);
        int right = height(branch->right);
        if (right > left)
            return ++right;
        else return ++left;
    }
}

template<typename InfoType>
void LittleLeftReverse(Node<InfoType> *branch, AVL_tree<InfoType> &Tree) {
    Node<InfoType> *A = branch,
            *B = branch->right,
            *C = branch->left,
            *D = branch->right->left,
            *E = branch->right->right;
    if (A->prev != nullptr) {
        if (A->Info > A->prev->Info) {
            A->prev->right = B;
            B->prev = A->prev;
        } else {
            A->prev->left = B;
            B->prev = A->prev;
        }

    } else {
        B->prev = nullptr;
        Tree.First = B;
    }
    B->left = A;
    A->prev = B;
    A->right = D;
    if (D != nullptr)
        D->prev = A;
}

template<typename InfoType>
void LittleRightReverse(Node<InfoType> *branch, AVL_tree<InfoType> &Tree) {
    Node<InfoType> *A = branch,
            *E = branch->right,
            *B = branch->left,
            *C = branch->left->left,
            *D = branch->left->right;
    if (A->prev != nullptr) {
        if (A->Info > A->prev->Info) {
            A->prev->right = B;
            B->prev = A->prev;
        } else {
            A->prev->left = B;
            B->prev = A->prev;
        }

    } else {
        B->prev = nullptr;
        Tree.First = B;
    }
    B->right = A;
    A->prev = B;
    if (D != nullptr)
        D->prev = A;
    A->left = D;
}

template<typename InfoType>
void BigLeftReverse(Node<InfoType> *branch, AVL_tree<InfoType> &Tree) {
    Node<InfoType> *A = branch,
            *B = branch->right,
            *D = branch->left,
            *C = branch->right->left,
            *G = branch->right->right,
            *E = branch->right->left->left,
            *F = branch->right->left->right;
    if (A->prev != nullptr) {
        if (A->Info > A->prev->Info) {
            A->prev->right = C;
            C->prev = A->prev;
        } else {
            A->prev->left = C;
            C->prev = A->prev;
        }

    } else {
        C->prev = nullptr;
        Tree.First = C;
    }
    C->left = A;
    A->prev = C;
    C->right = B;
    B->prev = C;
    A->right = E;
    if (E != nullptr)
        E->prev = A;
    B->left = F;
    if (F != nullptr)
        F->prev = B;
}

template<typename InfoType>
void BigRightReverse(Node<InfoType> *branch, AVL_tree<InfoType> &Tree) {
    Node<InfoType> *A = branch,
            *G = branch->right,
            *B = branch->left,
            *D = branch->left->left,
            *C = branch->left->right,
            *E = branch->left->right->left,
            *F = branch->left->right->right;
    if (A->prev != nullptr) {
        if (A->Info > A->prev->Info) {
            A->prev->right = C;
            C->prev = A->prev;
        } else {
            A->prev->left = C;
            C->prev = A->prev;
        }

    } else {
        C->prev = nullptr;
        Tree.First = C;
    }
    C->right = A;
    A->prev = C;
    C->left = B;
    B->prev = C;
    B->right = E;
    E->prev = B;
    A->left = F;
    F->prev = A;
}

template<typename InfoType>
void check(Node<InfoType> *branch, AVL_tree<InfoType> &Tree) {
    int R = height(branch->right);
    int L = height(branch->left);
    if (R - L == 2) {
        int RL = height(branch->right->left);
        int RR = height(branch->right->right);
        if (RL <= RR) {
            LittleLeftReverse(branch, Tree);
            return;
        } else {
            BigLeftReverse(branch, Tree);
            return;
        }
    } else if (L - R == 2) {
        int LL = height(branch->left->left);
        int LR = height(branch->left->right);
        if (LR <= LL) {
            LittleRightReverse(branch, Tree);
            return;
        } else {
            BigRightReverse(branch, Tree);
            return;
        }
    }
}

int main() {
    AVL_tree<int> Test1;
    constructor(Test1);
    //[4, 5, 8, 15, 2, 1, 3, 7, 12, 10]
    push(Test1, 4);
    push(Test1, 5);
    push(Test1, 8);
    push(Test1, 15);
    push(Test1, 2);
    push(Test1, 1);
    push(Test1, 3);
    push(Test1, 7);
    push(Test1, 12);
    push(Test1, 10);
    push(Test1, 11);
    extract(Test1, 5);
    extract(Test1, 7);
    extract(Test1, 10);

    destructor(Test1);

    AVL_tree<std::pair<int, std::string>> Test2;
    constructor(Test2);
    std::pair<int, std::string> ForPush = std::make_pair(0, "A");
    push(Test2, ForPush);
    ForPush=std::make_pair(15, "B");
    push(Test2, ForPush);
    ForPush=std::make_pair(20, "C");
    push(Test2, ForPush);
    ForPush=std::make_pair(30, "D");
    push(Test2, ForPush);
    ForPush=std::make_pair(39, "E");
    push(Test2, ForPush);
    ForPush=std::make_pair(42, "F");
    push(Test2, ForPush);
    ForPush=std::make_pair(43, "G");
    push(Test2, ForPush);
    ForPush=std::make_pair(50, "H");
    push(Test2, ForPush);
    ForPush=std::make_pair(36, "I");
    push(Test2, ForPush);
    ForPush=std::make_pair(25, "J");
    push(Test2, ForPush);
    ForPush=std::make_pair(23, "K");
    push(Test2, ForPush);
    ForPush=std::make_pair(28, "L");
    push(Test2, ForPush);
    std::pair<int, std::string> ForExtract = std::make_pair(23, "K");
    extract(Test2,ForExtract);
    ForExtract = std::make_pair(42, "F");
    extract(Test2,ForExtract);
    ForExtract = std::make_pair(43, "G");
    extract(Test2,ForExtract);
    ForExtract = std::make_pair(0, "A");
    extract(Test2,ForExtract);
    ForExtract = std::make_pair(30, "D");
    extract(Test2,ForExtract);
    destructor(Test2);
    return 0;

}
