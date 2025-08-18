#include <stdio.h>
#include <math.h>
#include<stdbool.h>
#include <stdlib.h>
#include <conio.h>

int out[9][9], gtcd=81;

struct SUDOKU{
  int mang, sl, kn[10];
};

struct SUDOKU stu[3][3][3][3];
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
void Khoi_Tao (){
  int I,J,i,j;
  for(I=0;I<3;I++)
    for(J=0;J<3;J++)
      for(i=0;i<3;i++)
        for(j=0;j<3;j++){
          stu[I][J][i][j].sl=9;
          int u=1;
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
  //Điền giá trị
  stu[I][J][i][j].mang=gt;
  stu[I][J][i][j].sl=0;
  int u;
  for(u=1;u<=9;u++)
    stu[I][J][i][j].kn[u]=0;
  //Phủ toàn bộ ô
  int K,L,k,l;
  for(k=0;k<3;k++)
    for(l=0;l<3;l++)
      dkphu(I,J,k,l,gt);
  //Phủ hàng
  for(L=0;L<3;L++)
    for(l=0;l<3;l++)
      dkphu(I,L,i,l,gt);
  //Phủ cột
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
  int r[10];
  for(int p=0;p<10;p++)
    r[p]=0;
  for(J1=0;J1<3;J1++)
    for(j1=0;j1<3;j1++){
      if(stu[I][J1][i][j1].kn[u]==1) dem++;
      r[stu[I][J1][i][j1].mang]++;
    }
  if(dem==1)return true;
  dem = 0;
  for(I1=0;I1<3;I1++)
    for(i1=0;i1<3;i1++){
      if(stu[I1][J][i1][j].kn[u]==1) dem++;
      r[stu[I1][J][i1][j].mang]++;
    }
  if(dem==1) return true;
  // Trường hợp xét cả trên hàng, cột đều thiếu duy nhất 1 số
  for(int p=1; p<10; p++)
    if(p != u && r[p] == 0) return false;
  if(r[u] == 0) return true;
  return false;
}
void De_Xuat_Nhu_Nhau(){
  int stu_kn[3][3][3][3]; // Tạo biến lưu giá trị đề xuất chuyển từ mảng -> số
  // Chuyển giá trị đề xuất từ mảng thành số  
  for(int I=0;I<3;I++){
    for(int J=0;J<3;J++)
      for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
          stu_kn[I][J][i][j] = 0; // Khởi tạo bằng 0
          if (stu[I][J][i][j].sl == 2){ // Chỉ lấy vị trí có đề xuất 2 số
            for(int k=1;k<=9;k++){ // Lưu lại giá trị đề xuất 
              if(stu[I][J][i][j].kn[k] == 1)
                stu_kn[I][J][i][j] = stu_kn[I][J][i][j]*10 + k;
            }
          }  
        }
  }
  // Kiểm tra lại giá trị 
  // for(int I=0;I<3;I++)
  //   for(int J=0;J<3;J++){
  //     for(int i=0;i<3;i++){
  //       for(int j=0;j<3;j++)
  //         printf("%d ", stu_kn[I][J][i][j]);
  //       printf("\n");
  //     }
  //     printf("\n");
  //   }
  //   char c =getch();

  // Xét hàng
  int l[10];
  for(int I=0;I<3;I++)
    for(int i=0;i<3;i++){
      for(int m=0;m<10;m++) l[m]=0;
      // Quét từng hàng 
      for(int J=0;J<3;J++){
        for(int j=0;j<3;j++){
          l[J*3 + j + 1] = stu_kn[I][J][i][j];
        }
      }

      // Kiểm tra xem quét đúng chưa
      // for(int u=0;u<10;u++) printf("%d ",l[u]);
      // printf("\n");
      // char c =getch();

      // Tìm các cặp giống nhau 
      for(int i1=1;i1<9;i1++){
        if(l[i1] > 0)
        for(int j1 = i1+1;j1<=9;j1++){
          if(l[i1] == l[j1]) // Thực hiện loại bỏ đề xuất các ô khác nếu như phát hiện cặp
          {
            // Lấy lại tọa độ
            int a,b,a1,b1;
            a1 = (i1-1)%3;a = (i1-1-a1)/3;
            b1 = (j1-1)%3;b = (j1-1-b1)/3;
            // Đến từng vị trí ô trong hàng kiểm tra 
            for(int J=0;J<3;J++){
              for(int j=0;j<3;j++){
                if((J != a || j != a1) && (J != b || j != b1)){ // Kiểm tra xem có bị trùng vị trí cặp ko
                  if(stu[I][J][i][j].kn[l[i1]%10] > 0){ // Xóa lần 1
                    stu[I][J][i][j].kn[l[i1]%10] = 0;
                    stu[I][J][i][j].sl--;
                  }
                  if(stu[I][J][i][j].kn[l[i1]/10] > 0){ // Xóa lần 2
                    stu[I][J][i][j].kn[l[i1]/10] = 0;
                    stu[I][J][i][j].sl--;
                  }
                }
              }
            }
          }
        }
      }
    }
  // Xét cột
  for(int J=0;J<3;J++)
    for(int j=0;j<3;j++){
      for(int m=0;m<10;m++) l[m]=0;
      // Quét từng cột 
      for(int I=0;I<3;I++){
        for(int i=0;i<3;i++){
          l[I*3 + i + 1] = stu_kn[I][J][i][j];
        }
      }

      // Kiểm tra xem quét đúng chưa
      // for(int u=0;u<10;u++) printf("%d ",l[u]);
      // printf("\n");
      // char c =getch();

      // Tìm các cặp giống nhau 
      for(int i1=1;i1<9;i1++){
        if(l[i1] > 0)
        for(int j1 = i1+1;j1<=9;j1++){
          if(l[i1] == l[j1]) // Thực hiện loại bỏ đề xuất các ô khác nếu như phát hiện cặp
          {
            // Lấy lại tọa độ
            int a,b,a1,b1;
            a1 = (i1-1)%3;a = (i1-1-a1)/3;
            b1 = (j1-1)%3;b = (j1-1-b1)/3;
            // Đến từng vị trí ô trong hàng kiểm tra 
            for(int I=0;I<3;I++){
              for(int i=0;i<3;i++){
                if((I != a || i != a1) && (I != b || i != b1)){ // Kiểm tra xem có bị trùng vị trí cặp ko
                  if(stu[I][J][i][j].kn[l[i1]%10] > 0){ // Xóa lần 1
                    stu[I][J][i][j].kn[l[i1]%10] = 0;
                    stu[I][J][i][j].sl--;
                  }
                  if(stu[I][J][i][j].kn[l[i1]/10] > 0){ // Xóa lần 2
                    stu[I][J][i][j].kn[l[i1]/10] = 0;
                    stu[I][J][i][j].sl--;
                  }
                }
              }
            }
          }
        }
      }
    }
  // Xét ô
  for(int I=0;I<3;I++)
    for(int J=0;J<3;J++){
      for(int m=0;m<10;m++) l[m]=0;
      // Quét từng ô 
      for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
          l[i*3 + j + 1] = stu_kn[I][J][i][j];
        }
      }

      // Kiểm tra xem quét đúng chưa
      // for(int u=0;u<10;u++) printf("%d ",l[u]);
      // printf("\n");
      // char c =getch();

      // Tìm các cặp giống nhau 
      for(int i1=1;i1<9;i1++){
        if(l[i1] > 0)
        for(int j1 = i1+1;j1<=9;j1++){
          if(l[i1] == l[j1]) // Thực hiện loại bỏ đề xuất các ô khác nếu như phát hiện cặp
          {
            // Lấy lại tọa độ
            int a,b,a1,b1;
            a1 = (i1-1)%3;a = (i1-1-a1)/3;
            b1 = (j1-1)%3;b = (j1-1-b1)/3;
            // Đến từng vị trí ô trong ô lớn 
            for(int i=0;i<3;i++){
              for(int j=0;j<3;j++){
                if((i != a || j != a1) && (i != b || j != b1)){ // Kiểm tra xem có bị trùng vị trí cặp ko
                  if(stu[I][J][i][j].kn[l[i1]%10] > 0){ // Xóa lần 1
                    stu[I][J][i][j].kn[l[i1]%10] = 0;
                    stu[I][J][i][j].sl--;
                  }
                  if(stu[I][J][i][j].kn[l[i1]/10] > 0){ // Xóa lần 2
                    stu[I][J][i][j].kn[l[i1]/10] = 0;
                    stu[I][J][i][j].sl--;
                  }
                }
              }
            }
          }
        }
      }
    }
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
            l--;
            for(i=0;i<3;i++)
              for(j=0;j<3;j++)
                if(stu[I][J][i][j].kn[u]==1)
                {
                  printf("KT o: %d %d %d %d %d %d\n", I, J, i, j, u);
                  Nhap(I,J,i,j,u);
                  Chuyen_Qua_Out();
                  In_Ket_Qua();
                  gtcd--;
                }
          }
          else
          {
            for(i=0;i<3;i++)
              for(j=0;j<3;j++)
                if(stu[I][J][i][j].kn[u]>0 && Kiem_Tra_Hang_Cot(I,J,i,j,u)==true)
                {
                  l--;
                  printf("KT hang cot: %d %d %d %d %d\n", I, J, i, j, u);
                  Nhap(I,J,i,j,u);
                  Chuyen_Qua_Out();
                  In_Ket_Qua();
                  gtcd--;
                }
          }
        }
    // Không thể điền thêm do trường hợp: nếu trong hàng || cột || ô có 2 ô đều có duy nhất 2 giá trị đều xuất như nhau 
    if(l == 100){
      De_Xuat_Nhu_Nhau();
    }
    l = 100;
  }
}





int main(){
  Khoi_Tao();
  Nhap_Phan_Tu();
  // In_Ket_Qua();
  Dien_Cho_Trong();
  Chuyen_Qua_Out();
  In_Ket_Qua();
  return 0;
}