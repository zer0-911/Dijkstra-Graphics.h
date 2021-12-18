#include<iostream>
#include<windows.h>
#include<graphics.h>
#include<mmsystem.h>
#include<vector>
using namespace std;

bool Hubung(string Dari, string Ke, float Jarak);
int cari(string carikota);
struct KotaLanjut2
{
    string sKotaNext;
    float jarak;
};
struct KotaL
{
    float TitikK;
    float x;
    float y;
    string sNamaKota;
    vector<struct KotaLanjut2> LanjutKotaNext;
};
vector<KotaL> LanjutKota;
struct kotahubung
{
    string nama1;
    string nama2;
};
struct kotahubung kotah[99];
string kotadjikstra[99];
int indexkota;
int indexkotadjikstra;
void tambahkota()
{
    string NamaKota;
    float x, y;
    struct KotaL Kota;
    Kota.TitikK=100000000000;
    LanjutKota.push_back(Kota);
    cout << "====== KOTA =====" << endl;
    cout << "Nama Kota: " << endl;
    cin >> NamaKota;
    cout << "Kordinat X: " << endl;
    cin >> x;
    cout << "Kordinat Y: " << endl;
    cin >> y;
    Kota.sNamaKota = NamaKota;
    Kota.x = x;
    Kota.y = y;
    LanjutKota.push_back(Kota);
}
int CariIndeksKota(string sNamaKota)
{
    int ikota = -1;
    for (int i = 0; i<LanjutKota.size();i++)
    {
        string s =LanjutKota[i].sNamaKota;
        if (sNamaKota.compare(s)==0)
        {
            ikota = i;
            break;
        }

    }
    return ikota;
}
void hubungan()
{
    string namaasal, namatujuan;
    float jarakkota;

    cout << "====== KOTA =====" << endl;
    cout << "Asal Kota: " << endl;
    cin >> namaasal;
    cout << "Tujuan Kota: " << endl;
    cin >> namatujuan;
    cout << "Jarak: " << endl;
    cin >> jarakkota;
    bool b;
    b = Hubung(namaasal, namatujuan, jarakkota);
    b = Hubung(namatujuan, namaasal, jarakkota);
    indexkota++;
    kotah[indexkota].nama1 = namaasal;
    kotah[indexkota].nama2 = namatujuan;
}
bool Hubung(string Dari, string Ke, float Jarak)
{
    int Asal,Tujuan;
    Asal= CariIndeksKota(Dari);
    Tujuan = CariIndeksKota(Ke);
    bool bKetemu = true ;
    if ((Asal>=0)&&(Tujuan>=0))
    {
        struct KotaLanjut2 Kota;
        Kota.sKotaNext =Ke;
        Kota.jarak = Jarak;
        LanjutKota[Asal].LanjutKotaNext.push_back(Kota);
    }
    else
    {
        bKetemu = false;
    }

    return bKetemu;
}
void InitDjikstra()
{
    for (int i=0;i<LanjutKota.size();i++)
    {
        LanjutKota[i].TitikK =1000000000;
    }
}
void visual()
{
    for (int i = 0; i <= LanjutKota.size(); i++)
    {
        float xy,yy;
        xy = LanjutKota[i].x;
        yy = LanjutKota[i].y;
        if((xy>0)&&(yy>0))
        {
            circle(xy,yy,10);
        }
        for (int j = 0; j <= indexkota; j++)
        {
            int xy1, xy2;
            xy1 = CariIndeksKota(kotah[j].nama1);
            xy2 = CariIndeksKota(kotah[j].nama2);
            setcolor(3);
            line(LanjutKota[xy1].x,LanjutKota[xy1].y,LanjutKota[xy2].x,LanjutKota[xy2].y);
        }
    }
}

void djikstra(string DjKota,float TitikK)
{

    int n=CariIndeksKota(DjKota);

    if (TitikK > LanjutKota[n].TitikK)
    {
        return;
    }

    LanjutKota[n].TitikK = TitikK ;
    for (int i  = 0; i<LanjutKota[n].LanjutKotaNext.size();i++)
    {
        string snext = LanjutKota[n].LanjutKotaNext[i].sKotaNext;
        float jarak= LanjutKota[n].LanjutKotaNext[i].jarak;
        djikstra(snext,TitikK+jarak);
    }
}

void CariRute(string DjKota)
{
    cout << DjKota <<"-";
    indexkotadjikstra++;
    kotadjikstra[indexkotadjikstra] = DjKota;
    int n = CariIndeksKota(DjKota);
    float TitikK = LanjutKota[n].TitikK;

    if(TitikK==0)
    {
        return;
    }
    for(int i = 0; i < LanjutKota[n].LanjutKotaNext.size();i++)
    {
        string snext = LanjutKota[n].LanjutKotaNext[i].sKotaNext;
        int Nnext = CariIndeksKota(snext);
        float TKnext = LanjutKota[Nnext].TitikK;
        int JarakNext = LanjutKota[n].LanjutKotaNext[i].jarak;
        if(JarakNext+TKnext == TitikK)
        {
            CariRute(snext);
        }
    }
}

void Masuk()
{
    string nama1, nama2;
    cout<<"Dari Kota : ";
    cin>> nama1;
    cout<<"Ke Kota : ";
    cin>> nama2;
    djikstra(nama2, 0);
    CariRute(nama1);
}
void visualdjikstra()
{
    for(int i = 0; i < indexkotadjikstra; i++)
    {
        int xy, xy2;
        xy = CariIndeksKota(kotadjikstra[i]);
        xy2 = CariIndeksKota(kotadjikstra[i+1]);
        setcolor(5);
        line(LanjutKota[xy].x,LanjutKota[xy].y + 10,LanjutKota[xy2].x,LanjutKota[xy2].y + 10);
    }
}

int main ()
{
    indexkota = -1;
    indexkotadjikstra =-1;
    int pilih;
    do
    {
        cout << "\n";
        cout << "============Menu Kota============" << endl;
        cout << "1. Tambah Kota: " << endl;
        cout << "2. Hubungkan Kota" << endl;
        cout << "3. Djikstra" << endl;
        cout << "4. Bentuk Visual Kota" << endl;
        cin >> pilih;

        if(pilih ==1)
        {
            tambahkota();
        }
        else if(pilih == 2)
        {
            hubungan();
        }
        else if(pilih == 3)
        {
            InitDjikstra();
            Masuk();
        }
        else if(pilih == 4)
        {
             initwindow(700,900);
                while (1)
                {
                    visual();
                    visualdjikstra();
                    delay(10);
                    cleardevice();
                }
        }
    } while (pilih >= 1 && pilih <=5);
}