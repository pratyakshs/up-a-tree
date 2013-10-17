#include<stdio.h>


int main(){
	int a[6];
	for(a[0]=0; a[0]<3; a[0]++){
		for (a[1] = 0; a[1] < 3; ++a[1])
		{
			for (a[2] = 0; a[2] < 3; ++a[2])
			{
				for (a[3] = 0; a[3] < 3; ++a[3])
				{
					for (a[4]= 0; a[4] < 3; ++a[4])
					{
						for (a[5] = 0; a[5] < 3; ++a[5])
						{
									int count[]={0,0,0};
									for(int i=0; i<6; i++){
										count[a[i]]++;
									}
									if(count[0]==2 && count[1]==2 && count[2]==2){
										printf("{%i, %i, %i, %i, %i, %i},\n", a[0], a[1], a[2], a[3], a[4], a[5]);
									}
						}
					}
				}
			}
		}
	}
}
