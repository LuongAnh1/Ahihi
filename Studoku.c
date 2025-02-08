#include <stdio.h>
#include <math.h>
#include<stdbool.h>
int out[9][9], gtcd=81;
struct SUDOKU{
  int mang, sl, kn[10];
};
struct SUDOKU stu[3][3][3][3];
void Khoi_Tao (){
  int I,J,i,j;
  for(I=0;I<3;I++)
    for(J=0;J<3;J++)
      for(i=0;i<3;i++)
        for(j=0;j<3;j++){
          stu[I][J][i][j].sl=9;
          int u=0;
          for(;u<=9;u++)
          stu[I][J][i][j].kn[u]=1;
          stu[I][J][i][j].mang=0;
        }
}
void dkphu (int I, int J, int i, int j, int gt){
  if(stu[I][J][i][j].kn[gt]==1){
    stu[I][J][i][j].kn[gt]=0;
    stu[I][J][i][j].sl--;
  }
}
void Nhap(int I, int J, int i, int j, int gt){
  //Dien gia tri
  stu[I][J][i][j].mang=gt;
  stu[I][J][i][j].sl=0;
  int u=0;
  for(u=1;u<=9;u++)
    stu[I][J][i][j].kn[u]=0;
  //Phu toan bo o
  int K,L,k,l;
  for(k=0;k<3;k++)
    for(l=0;l<3;l++)
      dkphu(I,J,k,l,gt);
  //Phu hang
  for(L=0;L<3;L++)
    for(l=0;l<3;l++)
      dkphu(I,L,i,l,gt);
  //Phu cot
  for(K=0;K<3;K++)
    for(k=0;k<3;k++)
      dkphu(K,J,k,j,gt);
}
void Nhap_Phan_Tu (){
  printf("Nhap mang:\n");
  int i,j;
  for(i=0;i<9;i++)
    for(j=0;j<9;j++)
    {
      scanf("%d",&out[i][j]);
      if(out[i][j]!=0){
        gtcd--;
        Nhap(i/3,j/3,i%3,j%3,out[i][j]);
      }
    }
}
bool Kiem_Tra_O (int I, int J, int u){
  int i,j,dem=0;
  for(i=0;i<3;i++)
    for(j=0;j<3;j++)
      if(stu[I][J][i][j].kn[u]==1) dem++;
  if(dem==1) return true;
  return false;
}
bool Kiem_Tra_Hang_Cot (int I,int J,int i,int j,int u){
  int dem=0,I1,J1,i1,j1;
  for(J1=0;J1<3;J1++)
    for(j1=0;j1<3;j1++)
     if(J1!=J||j1!=j&&stu[I][J1][i][j1].kn[u]==1) dem++;
  for(I1=0;I1<3;I1++)
    for(i1=0;i1<3;i1++)
     if(I1!=I||i1!=i&&stu[I1][J][i1][j].kn[u]==1) dem++;
  if(dem==0)return true;
  return false;
}
void Dien_Cho_Trong (){
  int l=100;
  while(gtcd>0){
    int I,J,i,j,u;
    for(u=1;u<=9;u++)
      for(I=0;I<3;I++)
        for(J=0;J<3;J++)
        {
          if(Kiem_Tra_O(I,J,u)==true)
          {
            for(i=0;i<3;i++)
              for(j=0;j<3;j++)
                if(stu[I][J][i][j].kn[u]==1)
                {
                  Nhap(I,J,i,j,u);
                  gtcd--;
                }
          }
          else
          {
            for(i=0;i<3;i++)
              for(j=0;j<3;j++)
                if(stu[I][J][i][j].kn[u]>0&&Kiem_Tra_Hang_Cot(I,J,i,j,u)==true)
                {
                  Nhap(I,J,i,j,u);
                  gtcd--;
                }
          }
        }
  }
}
void Chuyen_Qua_Out(){
  int I,J,i,j;
  for(I=0;I<3;I++)
    for(J=0;J<3;J++)
      for(i=0;i<3;i++)
        for(j=0;j<3;j++)
          out[I*3+i][J*3+j]=stu[I][J][i][j].mang;
}
void In_Ket_Qua(){
  int i,j;
  printf("Ketqua:\n");
  for(i=0;i<9;i++){
    for(j=0;j<9;j++)
      printf("%d ",out[i][j]);
    printf("\n");
  }
}
int main(){
  Khoi_Tao();
  Nhap_Phan_Tu();
  Dien_Cho_Trong();
  Chuyen_Qua_Out();
  In_Ket_Qua();
  return 0;
}

