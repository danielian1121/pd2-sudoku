#include <iostream>
#include <cstdlib>
#include <ctime> 
#include "Sudoku.h"
using namespace std;

void Sudoku::giveQuestion(){
	int question[81]={0,4,0,2,5,0,0,0,8,0,3,0,4,0,9,1,7,0,0,0,0,0,8,1,2,0,0,0,0,6,0,0,0,7,2,0,0,0,0,6,4,0,0,0,0,1,2,0,0,0,3,0,0,0,0,3,8,1,0,0,0,0,0,6,4,9,0,2,0,1,0,7,0,0,0,4,5,0,9,0};
	int i;
	for(i=0;i<81;i++){
		cout << question[i];
		if((i+1)%9==0) cout << "\n";
		else cout << " ";
	}
	return;
}

void Sudoku::readIn(){
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			cin >> map[i][j];
		}
	}
	return;
}
void Sudoku::solve(){
	bool answer[9][9][9];
	int i,j,k,m,sum,ans,flag;
	int row,col;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(map[i][j]){
				for(k=0;k<9;k++)
					answer[i][j][k]=false;
				answer[i][j][map[i][j]-1]=true;
			}
			else{
				for(k=0;k<9;k++)
					answer[i][j][k]=true;
			}
		}
	}	
	int hole=82,pre_hole=0,find;
	while(pre_hole != hole && hole!=0){
		pre_hole=hole;
		for(row=0;row<9;row++){
			for(col=0;col<9;col++){
				if(map[row][col]){
					for(i=0;i<9;i++) answer[row][col][i]=false;
					answer[row][col][map[row][col]-1]=true;
				}
				else{
					for(i=0;i<9;i++)
						if(map[i][col])
							answer[row][col][map[i][col]-1]=false;
					for(i=0;i<9;i++)
						if(map[row][i])
							answer[row][col][map[row][i]-1]=false;
					for(i=0;i<3;i++)
						for(j=0;j<3;j++)
							if(map[row-(row%3)+i][col-(col%3)+j])
								answer[row][col][map[row-(row%3)+i][col-(col%3)+j]-1]=false;
				}
			}
		}
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				sum=0;
				for(k=0;k<9;k++){
					if(answer[i][j][k]){
						sum++;
						ans=k+1;
					}
				}
				if(sum==1){
					map[i][j]=ans;
				}
			}
		}
		for(row=0;row<9;row++){
			for(col=0;col<9;col++){
				find=0;
				if(map[row][col]==0){
					for(k=0;k<9;k++){
						if(answer[row][col][k]){
							find=0;
							for(i=0;i<9;i++){
								if(answer[i][col][k]){
									find++;
								}
							}
							if(find==1)map[row][col]=k+1;
							find=0;
							for(j=0;j<9;j++){
								if(answer[row][j][k]){
									find++;
								}
							}	
							if(find==1)map[row][col]=k+1;
							find=0;
							for(i=0;i<3;i++){
								for(j=0;j<3;j++){
									if(answer[row-(row%3)+i][col-(col%3)+j][k]){
										find++;			
									}
								}
							}
							if(find==1)map[row][col]=k+1;
						}
					}
				}	
			}
		}
		for(row=0;row<9;row++){
			for(k=0;k<9;k++){
				find=0;
				for(i=0;i<9;i++){
					if(answer[row][i][k])find++;
				}
				if(find==0){
					cout << "0\n";
					return;
				}
			}
		}
		for(col=0;col<9;col++){
			for(k=0;k<9;k++){
				find=0;
				for(i=0;i<9;i++){
					if(answer[i][col][k])find++;
				}
				if(find==0){
					cout<<"0\n";
					return;
				}
			}
		}
		for(row=0;row<9;row++){
			for(col=0;col<9;col++){
				for(k=0;k<9;k++){
					find=0;
					for(i=0;i<3;i++){
						for(j=0;j<3;j++){
							if(answer[row-(row%3)+i][col-(col%3)+j][k])find++;
						}
					}
					if(find==0){
						cout << "0\n";
						return;
					}
				}
			}
		}

		hole=0;
		for(i=0;i<9;i++)
			for(j=0;j<9;j++)
				if(map[i][j]==0)hole++;
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				if(map[i][j]>0){
					for(k=0;k<9;k++){
						if(map[i][j]==map[k][j] && i!=k){
							cout << "0\n";
							return;
						}
					}
					for(k=0;k<9;k++){
						if(map[i][j]==map[i][k] && j!=k){
							cout << "0\n";
							return;
						}
					}
					for(k=0;k<3;k++){
						for(m=0;m<3;m++){
							if(map[i-(i%3)+k][j-(j%3)+m]==map[i][j] && i!=i-(i%3)+k && j!=j-(j%3)+m){
								cout << "0\n";
								return;
							}
						}
					}
				}	
			}
		}
	}

/*	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(map[i][j]){
				for(k=0;k<9;k++)
					if(map[k][j]==map[i][j] && i!=k)return 0;
				for(k=0;k<9;k++)
					if(map[i][k]==map[i][j] && j!=k)return 0;
				for(k=0;k<3;k++){
					for(int m=0;m<3;m++)
						if(map[i-(i%3)+k][j-(j%3)+m]==map[i][j] && i!=(i-(i%3)+k) && j!=(j-(j%3)+m))return 0;
				}
			}
		}
	}*/	
	if(hole==0){
		cout << "1\n";
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				cout << map[i][j] << " ";
			}
			cout << "\n";
		}
		return ;
	}
	int min=0,count=0,count1,flag2,map2[9][9],i1,j1,k1;
	bool possible[9][9][9];
	while(1){
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				for(k=0;k<9;k++){
					possible[i][j][k]=answer[i][j][k];
				}
				map2[i][j]=map[i][j];
			}
		}
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				if(map2[i][j]==0){
					for(k=0;k<9;k++){
						if(possible[i][j][k]){
							map2[i][j]=k+1;
							i1=i;
							j1=j;
							k1=k;
							goto stop;
						}
					}
				}
			}
		}
		stop:
		hole=82;
		pre_hole=81;
		flag2=0;
		while(flag2==0 && hole!=0){
			if(pre_hole==hole){
				for(i=0;i<9;i++){
					for(j=0;j<9;j++){
						if(map2[i][j]==0){
							for(k=0;k<9;k++){
								if(possible[i][j][k]){
									map2[i][j]=k+1;
									goto sop;
								}
							}
						}
					}
				}
			}
			sop:
			pre_hole=hole;
			for(row=0;row<9;row++){
				for(col=0;col<9;col++){
					if(map2[row][col]){
						for(i=0;i<9;i++) possible[row][col][i]=false;
						possible[row][col][map2[row][col]-1]=true;
					}
					else{
						for(i=0;i<9;i++)
							if(map2[i][col])
								possible[row][col][map2[i][col]-1]=false;
						for(i=0;i<9;i++)
							if(map2[row][i])
								possible[row][col][map2[row][i]-1]=false;
						for(i=0;i<3;i++)
							for(j=0;j<3;j++)
								if(map2[row-(row%3)+i][col-(col%3)+j])
									possible[row][col][map2[row-(row%3)+i][col-(col%3)+j]-1]=false;
					}
				}
			}
			for(i=0;i<9;i++){
				for(j=0;j<9;j++){
					sum=0;
					for(k=0;k<9;k++){
						if(possible[i][j][k]){
							sum++;
							ans=k+1;
						}
					}
					if(sum==1){
						map2[i][j]=ans;
					}
				}
			}
			for(row=0;row<9;row++){
				for(col=0;col<9;col++){
					flag=1;
					if(map2[row][col]==0){
						for(k=0;k<9;k++){
							if(possible[row][col][k]){
								flag=1;
								for(i=0;i<9;i++){
									if(possible[i][col][k] && row!=i){
										flag=0;
									}
								}
								for(j=0;j<9;j++){
									if(possible[row][j][k] && col!=j){
										flag=0;
									}
								}
								for(i=0;i<3;i++){
									for(j=0;j<3;j++){
										if(possible[row-(row%3)+i][col-(col%3)+j][k] && row!=row-(row%3)+i && col!=col-(col%3)+j){
											flag=0;			
										}
									}
								}
								if(flag==1){
									map2[row][col]=k+1;
								}
							}
						}
					}	
				}	
			}
			hole=0;
			for(i=0;i<9;i++)
				for(j=0;j<9;j++)
					if(map2[i][j]==0)hole++;
			for(i=0;i<9;i++){
				for(j=0;j<9;j++){
					count1=0;
					if(map2[i][j]==0){
						for(k=0;k<9;k++){
							if(possible[i][j][k]){
								count1++;
							}
						}
						if(count1==0){
							flag2=1;
						}
					}
				}
			}
		}
		if(hole==0){
			count++;
		}
		else if(flag2==1)answer[i1][j1][k1]=false;
		if(count>1){
			cout << "2\n";
			return ;
		}
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				int flag3=0;
				for(k=0;k<9;k++){
					if(answer[i][j][k])flag3=1;
				}
				if(flag3==0){
					cout << "0\n";
					return ;
				}
			}
		}
	}
/*	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(map[i][j]==0){
				count=0;
				for(k=0;k<9;k++){
					if(answer[i][j][k])count++;
				}
				num=count;
				if(max==0)max=num;
				else if(num!=max){
					return 0;
				}
			}
		}
	}
	return 2;*/
}

void Sudoku::changeNum(int a,int b){
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(map[i][j]==a)map[i][j]=b;
			else if(map[i][j]==b)map[i][j]=a;
		}
	}
	return;
}
void Sudoku::changeRow(int a,int b){
	int i,j,buffer[9];
	for(i=0;i<3;i++){
		for(j=0;j<9;j++){
			buffer[j]=map[a*3+i][j];
			map[a*3+i][j]=map[b*3+i][j];
			map[b*3+i][j]=buffer[j];
		}
	}
	return;
}
void Sudoku::changeCol(int a,int b){
	int i,j,buffer[9];
	for(i=0;i<3;i++){
		for(j=0;j<9;j++){
			buffer[j]=map[j][a*3+i];
			map[j][a*3+i]=map[j][b*3+i];
			map[j][b*3+i]=buffer[j];
		}
	}
	return;
}
void Sudoku::rotate(int n){
	int i,j,buffer[9][9];
	while(n){	
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				buffer[i][j]=map[i][j];
			}
		}
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				map[j][8-i]=buffer[i][j];
			}
		}
		n--;
	}
	return;
}
void Sudoku::flip(int n){
	int i,j,k;
	if(n){
		for(i=0;i<9;i++){
			for(j=0;j<4;j++){
				k=map[i][j];
				map[i][j]=map[i][8-j];
				map[i][8-j]=k;
			}
		}
	}
	else{
		for(i=0;i<4;i++){
			for(j=0;j<9;j++){
				k=map[i][j];
				map[i][j]=map[8-i][j];
				map[8-i][j]=k;
			}
		}
	}
	return;
}
void Sudoku::transform(){
	int i,j;
	readIn();
	change();
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
	return;
}
void Sudoku::change(){
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
	return;
}
