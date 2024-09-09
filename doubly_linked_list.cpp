#include <iostream>
using namespace std;

typedef struct dNode
{
    int data;
    struct dNode *prev;
    struct dNode *next;

    dNode(int data)
    {
        this->data = data;
        this->prev = NULL;
        this->next = NULL;
    }
} DNode;

typedef struct dList
{
    DNode *pHead;
    DNode *pTail;

    dList()
    {
        this->pHead = NULL;
        this->pTail = NULL;
    }

    // Thêm node vào đầu danh sách
    void addToHead(DNode *p)
    {
        if (pHead == NULL)
        {
            pHead = p;
            pTail = p;
        }
        else
        {
            p->next = pHead;
            pHead->prev = p;
            pHead = p;
        }
    }

    // Thêm node vào cuối danh sách
    void addToTail(DNode *p)
    {
        if (pTail == NULL)
        {
            pHead = p;
            pTail = p;
        }
        else
        {
            p->prev = pTail;
            pTail->next = p;
            pTail = p;
        }
    }

    // Chèn node tại vị trí idx, trả về vị trí node được chèn vào
    int insert(DNode *p, int idx)
    {
        if (idx < 0) return -1; // Vị trí không hợp lệ

        if (idx == 0)
        {
            addToHead(p);
            return 0;
        }

        DNode *current = pHead;
        int position = 0;

        while (current != NULL && position < idx - 1)
        {
            current = current->next;
            position++;
        }

        if (current == NULL)
            return -1; // Vị trí ngoài phạm vi

        p->next = current->next;
        p->prev = current;

        if (current->next != NULL)
            current->next->prev = p;
        else
            pTail = p; // Cập nhật pTail nếu chèn ở cuối

        current->next = p;
        return idx;
    }

    // Chèn node trước node pDelNode, trả về vị trí node được chèn vào
    int insertBefore(DNode *pDelNode, DNode *pNode)
    {
        if (pDelNode == NULL) return -1;

        if (pDelNode == pHead)
        {
            addToHead(pNode);
            return 0;
        }

        pNode->next = pDelNode;
        pNode->prev = pDelNode->prev;
        pDelNode->prev->next = pNode;
        pDelNode->prev = pNode;

        return 1;
    }

    // Chèn node sau node pDelNode, trả về vị trí node được chèn vào
    int insertAfter(DNode *pDelNode, DNode *pNode)
    {
        if (pDelNode == NULL) return -1;

        pNode->prev = pDelNode;
        pNode->next = pDelNode->next;

        if (pDelNode->next != NULL)
            pDelNode->next->prev = pNode;
        else
            pTail = pNode; // Cập nhật pTail nếu chèn ở cuối

        pDelNode->next = pNode;
        return 1;
    }

    // Xóa node đầu tiên
    DNode* removeHead()
    {
        if (pHead == NULL) return NULL; // Danh sách rỗng

        DNode *temp = pHead;

        if (pHead == pTail) // Chỉ có một phần tử
        {
            pHead = NULL;
            pTail = NULL;
        }
        else
        {
            pHead = pHead->next;
            pHead->prev = NULL;
        }

        temp->next = NULL;
        return temp;
    }

    // Xóa node cuối cùng
    DNode* removeTail()
    {
        if (pTail == NULL) return NULL; // Danh sách rỗng

        DNode *temp = pTail;

        if (pHead == pTail) // Chỉ có một phần tử
        {
            pHead = NULL;
            pTail = NULL;
        }
        else
        {
            pTail = pTail->prev;
            pTail->next = NULL;
        }

        temp->prev = NULL;
        return temp;
    }

    // Xóa node tại vị trí idx
    DNode* remove(int idx)
    {
        if (idx < 0) return NULL; // Chỉ số không hợp lệ

        if (idx == 0) return removeHead();

        DNode *current = pHead;
        int position = 0;

        while (current != NULL && position < idx)
        {
            current = current->next;
            position++;
        }

        if (current == NULL) return NULL; // Vị trí ngoài phạm vi

        if (current == pTail) return removeTail();

        current->prev->next = current->next;
        current->next->prev = current->prev;

        current->next = NULL;
        current->prev = NULL;
        return current;
    }

    // Xóa tất cả các node
    void removeAll()
    {
        while (pHead != NULL)
        {
            delete removeHead();
        }
    }

    // Tìm kiếm node theo giá trị, trả về node tìm thấy hoặc NULL
    DNode* Find(int data)
    {
        DNode *current = pHead;
        while (current != NULL)
        {
            if (current->data == data)
                return current;
            current = current->next;
        }
        return NULL;
    }

    // Xuất danh sách ra màn hình
    void output()
    {
        cout << "[";
        for (DNode *p = this->pHead; p != NULL; p = p->next)
        {
            cout << p->data;
            if (p->next != NULL) cout << ", ";
        }
        cout << "]" << endl;
    }

} DLinkList;

int main()
{
    DLinkList danhSach;

    // Kiểm tra chức năng của danh sách liên kết đôi
    DNode *n1 = new DNode(1);
    DNode *n2 = new DNode(2);
    DNode *n3 = new DNode(3);

    danhSach.addToHead(n1);
    danhSach.addToTail(n2);
    danhSach.insertAfter(n1, n3);

    danhSach.output(); // Dự kiến đầu ra: [1, 3, 2]

    DNode *nutXoa = danhSach.remove(1);
    delete nutXoa;

    danhSach.output(); // Dự kiến đầu ra: [1, 2]

    DNode *nutTimThay = danhSach.Find(2);
    if (nutTimThay)
        cout << "Tìm thấy: " << nutTimThay->data << endl;

    danhSach.removeAll();
    danhSach.output(); // Dự kiến đầu ra: []

    return 0;
}
