#include <iostream>
using namespace std;

typedef struct dNode
{
    int duLieu;
    struct dNode *truoc;
    struct dNode *sau;

    dNode(int duLieu)
    {
        this->duLieu = duLieu;
        this->truoc = NULL;
        this->sau = NULL;
    }
} NutDLienKet;

typedef struct dDanhSachLienKet
{
    NutDLienKet *pDau;
    NutDLienKet *pCuoi;

    dDanhSachLienKet()
    {
        this->pDau = NULL;
        this->pCuoi = NULL;
    }

    void themVaoDau(NutDLienKet *p)
    {
        if (pDau == NULL)
        {
            pDau = p;
            pCuoi = p;
            pDau->sau = pDau; // Liên kết vòng
            pDau->truoc = pDau; // Liên kết vòng
        }
        else
        {
            p->sau = pDau;
            p->truoc = pCuoi;
            pCuoi->sau = p;
            pDau->truoc = p;
            pDau = p;
        }
    }

    void themVaoCuoi(NutDLienKet *p)
    {
        if (pCuoi == NULL)
        {
            pDau = p;
            pCuoi = p;
            pDau->sau = pDau; // Liên kết vòng
            pDau->truoc = pDau; // Liên kết vòng
        }
        else
        {
            p->truoc = pCuoi;
            p->sau = pDau;
            pCuoi->sau = p;
            pDau->truoc = p;
            pCuoi = p;
        }
    }

    int chenNut(NutDLienKet *p, int chiSo)
    {
        if (chiSo < 0)
            return -1; // Chỉ số không hợp lệ

        if (chiSo == 0)
        {
            themVaoDau(p);
            return 0;
        }

        NutDLienKet *hienTai = pDau;
        int viTri = 0;

        while (hienTai->sau != pDau && viTri < chiSo - 1)
        {
            hienTai = hienTai->sau;
            viTri++;
        }

        if (viTri == chiSo - 1)
        {
            p->sau = hienTai->sau;
            p->truoc = hienTai;
            hienTai->sau->truoc = p;
            hienTai->sau = p;
            return chiSo;
        }

        return -1; // Chỉ số ngoài phạm vi
    }

    int chenTruoc(NutDLienKet *pNutXoa, NutDLienKet *pNut)
    {
        if (pNutXoa == NULL || pDau == NULL)
            return -1; // Nút cần chèn trước không hợp lệ hoặc danh sách rỗng

        NutDLienKet *hienTai = pDau;
        int chiSo = 0;

        do
        {
            if (hienTai == pNutXoa)
            {
                if (hienTai == pDau)
                {
                    themVaoDau(pNut);
                }
                else
                {
                    pNut->sau = hienTai;
                    pNut->truoc = hienTai->truoc;
                    hienTai->truoc->sau = pNut;
                    hienTai->truoc = pNut;
                }
                return chiSo;
            }
            hienTai = hienTai->sau;
            chiSo++;
        } while (hienTai != pDau);

        return -1; // Không tìm thấy nút
    }

    int chenSau(NutDLienKet *pNutXoa, NutDLienKet *pNut)
    {
        if (pNutXoa == NULL || pDau == NULL)
            return -1; // Nút cần chèn sau không hợp lệ hoặc danh sách rỗng

        NutDLienKet *hienTai = pDau;
        int chiSo = 0;

        do
        {
            if (hienTai == pNutXoa)
            {
                pNut->truoc = hienTai;
                pNut->sau = hienTai->sau;
                hienTai->sau->truoc = pNut;
                hienTai->sau = pNut;
                return chiSo + 1;
            }
            hienTai = hienTai->sau;
            chiSo++;
        } while (hienTai != pDau);

        return -1; // Không tìm thấy nút
    }

    NutDLienKet* xoaDau()
    {
        if (pDau == NULL)
            return NULL; // Danh sách rỗng

        NutDLienKet *tam = pDau;

        if (pDau == pCuoi) // Chỉ có một phần tử
        {
            pDau = NULL;
            pCuoi = NULL;
        }
        else
        {
            pDau = pDau->sau;
            pDau->truoc = pCuoi;
            pCuoi->sau = pDau;
        }

        tam->sau = NULL;
        tam->truoc = NULL;
        return tam;
    }

    NutDLienKet* xoaCuoi()
    {
        if (pCuoi == NULL)
            return NULL; // Danh sách rỗng

        NutDLienKet *tam = pCuoi;

        if (pDau == pCuoi) // Chỉ có một phần tử
        {
            pDau = NULL;
            pCuoi = NULL;
        }
        else
        {
            pCuoi = pCuoi->truoc;
            pCuoi->sau = pDau;
            pDau->truoc = pCuoi;
        }

        tam->sau = NULL;
        tam->truoc = NULL;
        return tam;
    }

    NutDLienKet* xoaNut(int chiSo)
    {
        if (chiSo < 0 || pDau == NULL)
            return NULL; // Chỉ số không hợp lệ hoặc danh sách rỗng

        NutDLienKet *hienTai = pDau;
        int viTri = 0;

        while (hienTai->sau != pDau && viTri < chiSo)
        {
            hienTai = hienTai->sau;
            viTri++;
        }

        if (viTri == chiSo)
        {
            if (hienTai == pDau)
                return xoaDau();
            else if (hienTai == pCuoi)
                return xoaCuoi();
            else
            {
                hienTai->truoc->sau = hienTai->sau;
                hienTai->sau->truoc = hienTai->truoc;
                hienTai->sau = NULL;
                hienTai->truoc = NULL;
                return hienTai;
            }
        }

        return NULL; // Chỉ số ngoài phạm vi
    }

    void xoaTatCa()
    {
        while (pDau != NULL)
        {
            xoaDau();
        }
    }

    NutDLienKet* timKiem(int duLieu)
    {
        NutDLienKet *hienTai = pDau;

        do
        {
            if (hienTai->duLieu == duLieu)
                return hienTai;
            hienTai = hienTai->sau;
        } while (hienTai != pDau);

        return NULL; // Không tìm thấy nút
    }

    void xuatDanhSach()
    {
        if (pDau == NULL)
        {
            cout << "[]" << endl;
            return;
        }

        cout << "[";
        NutDLienKet *hienTai = pDau;
        do
        {
            cout << hienTai->duLieu;
            hienTai = hienTai->sau;
            if (hienTai != pDau)
                cout << ", ";
        } while (hienTai != pDau);
        cout << "]" << endl;
    }
} DanhSachLienKet;

int main()
{
    DanhSachLienKet danhSach;

    // Kiểm tra chức năng của danh sách
    NutDLienKet *n1 = new NutDLienKet(1);
    NutDLienKet *n2 = new NutDLienKet(2);
    NutDLienKet *n3 = new NutDLienKet(3);

    danhSach.themVaoDau(n1);
    danhSach.themVaoCuoi(n2);
    danhSach.chenSau(n1, n3);

    danhSach.xuatDanhSach(); // Dự kiến đầu ra: [1, 3, 2]

    NutDLienKet *nutDaXoa = danhSach.xoaNut(1);
    delete nutDaXoa;

    danhSach.xuatDanhSach(); // Dự kiến đầu ra: [1, 2]

    NutDLienKet *nutTimThay = danhSach.timKiem(2);
    if (nutTimThay)
        cout << "Tìm thấy: " << nutTimThay->duLieu << endl;

    danhSach.xoaTatCa();
    danhSach.xuatDanhSach(); // Dự kiến đầu ra: []

    return 0;
}
