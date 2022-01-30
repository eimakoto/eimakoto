#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct packet
{
	unsigned long int orip;
	unsigned long int laip;
	int ord;
	int lad;
	int xie;
};//存放packet数据 
struct rule
{
	int oip1;
	int oip2;
	int oip3;
	int oip4;
	int lip1;
	int lip2;
	int lip3;
	int lip4;
	int od1;
	int od2;
	int ld1;
	int ld2;
	int w1;
	int w2;
	int x;
	char xie[3];
};//存放rule的数据 
int main()
{
	struct packet pac[10000];
	struct rule rule[1000];
	FILE *fp,*fp2,*re;
	fp=fopen("","r");//指向packet文件，务必填写电脑中存放packet文件的具体路径 
	fp2=fopen("","r");//指向rule文件，务必填写电脑中存放rule文件的具体路径 
	re=fopen("","w");//指向res文件，可自行选择存放路径 
	char ch1,ch2;
	int i=0,i2,i3;
	while(ch1!=EOF){
		fscanf(fp,"%lu %lu %d %d %d",&pac[i].orip,&pac[i].laip,&pac[i].ord,&pac[i].lad,&pac[i].xie);
		i++;
		ch1=fgetc(fp);
	}//填充packet结构体 
	i2=i;i=0;
	while(ch2!=EOF){
		fscanf(fp2,"@%d.%d.%d.%d/%d %d.%d.%d.%d/%d %d : %d %d : %d 0x%x/0x%s",&rule[i].oip1,&rule[i].oip2,&rule[i].oip3,&rule[i].oip4,&rule[i].w1,&rule[i].lip1,&rule[i].lip2,&rule[i].lip3,&rule[i].lip4,&rule[i].w2,&rule[i].od1,&rule[i].od2,&rule[i].ld1,&rule[i].ld2,&rule[i].x,rule[i].xie);
		i++;
		ch2=fgetc(fp2);
	}//填充rule结构体 
	i3=i;i=0;
	unsigned long int oip[1000],lip[1000];
	while(i<i3-1){
		oip[i]=rule[i].oip1*256*256*256+rule[i].oip2*256*256+rule[i].oip3*256+rule[i].oip4;
		lip[i]=rule[i].lip1*256*256*256+rule[i].lip2*256*256+rule[i].lip3*256+rule[i].lip4;
		i++;
	}//oip用于存放rule中转换为十进制的原ip，lip同理 
	i=0;
	int j=0;
	char x[3]="FF";
	while(i<i2-1){//将packet逐个进行匹配并输出到文件中 
		if(pac[i].orip==oip[j]){
			if(pac[i].laip==lip[j]){
				if(pac[i].ord>=rule[j].od1&&pac[i].ord<=rule[j].od2&&pac[i].lad>=rule[j].ld1&&pac[i].lad<=rule[j].ld2){
					if(strcmp(x,rule[j].xie)==0){
						if(rule[j].x==pac[i].xie){
							fprintf(re,"%d\n",j);
							i++;
							j=0;
						}
						else{
							j++;
						}
					}
					else{
						fprintf(re,"%d\n",j);
						i++;
						j=0;
					}
				}
				else{
					j++;
				}
			}
			else{
				j++;
			}
		}
		else{
			j++;
		}
		if(j==i3-1){
			fprintf(re,"-1\n");
			i++;
			j=0;
		}
	}
	fclose(fp);
	fclose(fp2);
	fclose(re);//关闭文件 
	return 0;
}
