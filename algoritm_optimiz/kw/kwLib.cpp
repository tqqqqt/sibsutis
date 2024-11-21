#include <iostream>
#include <cmath>
#include "structs.h"
using namespace std;

void DrobMathSum(struct drobi *resNum, struct drobi num1, struct drobi num2){
	if(num1.down==0 && num2.down==0){
		resNum->up=0;
		resNum->down=0;
		resNum->drob=false;
		return;
	}
	if(num1.drob==false && num2.drob==false){
		resNum->up=num1.up+num2.up;
		if(resNum->up==0){
			resNum->down=0;
			resNum->drob=false;
			return;
		}
		resNum->down=1;
		resNum->drob=false;
		return;
	}
	if(num1.drob==false && num2.drob==true){
		resNum->up=(num1.up*abs(num2.down))+num2.up;
		if(resNum->up==0){
			resNum->down=0;
			resNum->drob=false;
			return;
		}
		resNum->down=abs(num2.down);
		resNum->drob=true;
		return;
	}
	if(num1.drob==true && num2.drob==false){
		resNum->up=num1.up+(num2.up*abs(num1.down));
		if(resNum->up==0){
			resNum->down=0;
			resNum->drob=false;
			return;
		}
		resNum->down=abs(num1.down);
		resNum->drob=true;
		return;
	}
	if(num1.drob==true && num2.drob==true){
		if(num1.down!=num2.down){
			resNum->up=(num1.up*abs(num2.down))+(num2.up*abs(num1.down));
			if(resNum->up==0){
				resNum->down=0;
				resNum->drob=false;
				return;
			}
			resNum->down=num1.down*num2.down;
		}
		else{
			resNum->up=num1.up+num2.up;
			if(resNum->up==0){
				resNum->down=0;
				resNum->drob=false;
				return;
			}
			resNum->down=num1.down;
		}
		resNum->drob=true;
		return;
	}
}

void DrobMathRaz(struct drobi *resNum, struct drobi num1, struct drobi num2){
	if(num1.down==0 && num2.down==0){
		resNum->up=0;
		resNum->down=0;
		resNum->drob=false;
		return;
	}
	if(num1.drob==false && num2.drob==false){
		resNum->up=num1.up-num2.up;
		if(resNum->up==0){
			resNum->down=0;
			resNum->drob=false;
			return;
		}
		resNum->down=1;
		resNum->drob=false;
		return;
	}
	if(num1.drob==false && num2.drob==true){
		resNum->up=(num1.up*abs(num2.down))-num2.up;
		if(resNum->up==0){
			resNum->down=0;
			resNum->drob=false;
			return;
		}
		resNum->down=abs(num2.down);
		resNum->drob=true;
		return;
	}
	if(num1.drob==true && num2.drob==false){
		resNum->up=num1.up-(num2.up*abs(num1.down));
		if(resNum->up==0){
			resNum->down=0;
			resNum->drob=false;
			return;
		}
		resNum->down=abs(num1.down);
		resNum->drob=true;
		return;
	}
	if(num1.drob==true && num2.drob==true){
		if(num1.down!=num2.down){
			resNum->up=(num1.up*abs(num2.down))-(num2.up*abs(num1.down));
			if(resNum->up==0){
				resNum->down=0;
				resNum->drob=false;
				return;
			}
			resNum->down=num1.down*num2.down;
		}
		else{
			resNum->up=num1.up-num2.up;
			if(resNum->up==0){
				resNum->down=0;
				resNum->drob=false;
				return;
			}
			resNum->down=num1.down;
		}
		resNum->drob=true;
		return;
	}
}

void DrobMathMul(struct drobi *resNum, struct drobi num1, struct drobi num2){
	if(num1.up==0 || num2.up==0){
		resNum->up=0;
		resNum->down=0;
		resNum->drob=false;
		return;
	}
	if(num1.drob==false && num2.drob==false){
		resNum->up=num1.up*num2.up;
		resNum->down=1;
		resNum->drob=false;
		return;
	}
	resNum->up=num1.up*num2.up;
	resNum->down=num1.down*num2.down;
	resNum->drob=true;
}

void DrobMathDel(struct drobi *resNum, struct drobi num1, struct drobi num2){
	if(num1.up==0 || num2.up==0){
		resNum->up=0;
		resNum->down=0;
		resNum->drob=false;
		return;
	}
	struct drobi tempNum;
	tempNum.up=num2.down;
	tempNum.down=num2.up;
	if(tempNum.down!=1) tempNum.drob=true;
	else tempNum.drob=false;
	DrobMathMul(resNum,num1,tempNum);
	if(resNum->down<0){
		resNum->up=resNum->up*-1;
		resNum->down=resNum->down*-1;
	}
}

long long FindDel(long long a, long long b){
	if(b==0) return a;
	return FindDel(b,a%b);
}

void CheckDrob(struct drobi *num){
	if(num->up==0) return;
	if(num->up%num->down==0){
		num->up/=num->down;
		num->down=1;
		num->drob=false;
		return;
	}
	long long delNum=FindDel(abs(num->up),abs(num->down));
	if(delNum==0) return;
	num->up/=delNum;
	num->down/=delNum;
}
